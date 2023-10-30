
/* Copyright 2014 Adobe Systems Incorporated (http://www.adobe.com/). All Rights Reserved.
   This software is licensed as OpenSource, under the Apache License, Version 2.0. This license is available at: http://opensource.org/licenses/Apache-2.0. */

/*
 * Glyph substitution table.
 */
#include "GSUB.h"

#include <cassert>
#include <algorithm>

#include <assert.h>

#include "OS_2.h"
#include "hotmap.h"
#include "vmtx.h"
#include "name.h"

/* --------------------------- Standard Functions -------------------------- */

static void check_overflow(hotCtx g, const char* offsetType, long offset,
                           const char* subType) {
    if (offset > 0xFFFF) {
        hotMsg(g, hotFATAL,
               "In %s %s rules cause an offset overflow (0x%lx) to a %s",
               g->error_id_text, subType, offset, offsetType);
    }
}

void GSUBNew(hotCtx g) {
    g->ctx.GSUBp = new GSUB(g);
}

int GSUBFill(hotCtx g) {
    return g->ctx.GSUBp->Fill();
}

int GSUB::Fill() {
    if (subtables.size() == 0) {
        if (g->convertFlags & HOT_ALLOW_STUB_GSUB) {
            return 1;
        } else {
            return 0;
        }
    }

    createAnonLookups();

    if (h->otl == NULL) {
        return 0;
    }

    /* Add OTL features */

    /* The font tables are in the order:
     ScriptList
     FeatureList
     FeatureParams
     LookupList
     lookup subtables (with aalt subtables written last)
     anon subtables (lookup subtables created by contextual rules)
     coverage definition tables
     class definition tables
     extension sections.
     Notes:
     All directly defined lookup subtables are added in the order that they are
     created by the feature file. The only exceptions are the subtables for
     the aalt lookups, and anonymous subtables. 'aalt'subtables' are created
     after the end of feature file parsing, in feat.c:featFill(), since the
     aalt feature references can be used only after all the other features are
     defined. Anonymous subtables, those implied by contextual rules rather
     than being explicitly defined, are added at the end of the subtable list,
     in createAnonLookups() above.

     coverage and class subtables are seperately accumulated in otlTable
     t->coverage.tables and t->class.tables, and are written after all the
     lookup subtables, first coverage, then class subtables.

     For featparams and lookup subtables, there are two parallel sets of arrays
     of subtables. The GSUB arrays (h->*) contain the actual data to be
     written, and is where the offsets are set. The other set is in the otl
     table, and exists so that the GPOS and GSUB can share code for ordering
     and writing feature and lookup indices. The latter inherit offset and
     other data from the GSUB arrays. The GSUB arrays are created when the
     feature file is processed, by all the fill* functions.  The otl table
     arrays are created below.
    */
    for (auto &sub: subtables) {
        int isExt = sub->extension.use;
        bool hasFeatureParam = ((sub->lkpType == GSUBFeatureNameParam) ||
                                (sub->lkpType == GSUBCVParam));

        otl.subtableAdd(sub->script, sub->language, sub->feature,
                        isExt ? GSUBExtension : sub->lkpType,
                        sub->lkpFlag, sub->markSetIndex,
                        isExt ? sub->lkpType : 0,
                        IS_REF_LAB(sub->label) ? 0 : sub->offset,
                        sub->label,
                        (uint16_t)(IS_REF_LAB(sub->label) ? 0 : isExt ? sub->extension.tbl.SubstFormat : sub->subformat()),
                        hasFeatureParam);
    }
    DF(1, (stderr, "### GSUB:\n"));

    otl.fill(offset.featParam);

    offset.extensionSection = offset.subtable + otl.getCoverageSize() + otl.getClassSize();
#if HOT_DEBUG
    otl.dumpSizes(offset.subtable, offset.extension);
#endif /* HOT_DEBUG */

    /* setAnonLookupIndices marks as used not only the anonymous lookups, */
    /* but also all lookups that were referenced from chain sub rules,    */
    /* including the stand-alone lookups. This is why                     */
    /* checkStandAloneTablRefs has to follow setAnonLookupIndices.        */
    setAnonLookupIndices();

    otl.checkStandAloneRefs();

    OS_2SetMaxContext(g, maxContext);

    return 1;
}

void GSUB::featParamsWrite() {
    for (auto &sub : subtables) {
        if (IS_REF_LAB(sub->label))
            continue;

        switch (sub->lkpType) {
                /* I am keep the case switch from GPOS Write in case
                 we ever have new GPOS feature param. */
                case GSUBFeatureNameParam:
                case GSUBCVParam:
                    sub->write(this);
                    break;
        }
    }
}

void GSUBWrite(hotCtx g) {
    g->ctx.GSUBp->Write();
}

void GSUB::Write() {
    /* Write OTL features */
    otl.write();
    featParamsWrite();
    otl.lookupListWrite();

    /* Write main subtable section */
    for (auto &sub : subtables) {
        STRCPY_S(g->error_id_text, sizeof(g->error_id_text), sub->id_text);

        if (IS_REF_LAB(sub->label)) {
            continue;
        }

        if (sub->extension.use) {
            writeExtension(*sub);
            continue;
        }

        switch (sub->lkpType) {
            case GSUBSingle:
            case GSUBMultiple:
            case GSUBLigature:
            case GSUBAlternate:
            case GSUBChain:
            case GSUBReverse:
                sub->write(this);
                break;

            /* We no longer write the feature param subtables as part of the LookupList
             they are instead written above in featParamsWrite().*/
        }
    }

    /* Write main coverage and class tables */
    otl.coverageWrite();
    otl.classWrite();

    /* Write extension subtables section. Each subtable is immediately  */
    /* followed by its coverages and classes                            */
    for (auto &sub : subtables) {
        if (IS_REF_LAB(sub->label) || !sub->extension.use) {
            continue;
        }

        switch (sub->lkpType) {
            case GSUBSingle:
            case GSUBMultiple:
            case GSUBLigature:
            case GSUBAlternate:
            case GSUBChain:
            case GSUBReverse:
                sub->write(this);
                break;
        }
    }
}

void GSUBReuse(hotCtx g) {
    delete g->ctx.GSUBp;
    g->ctx.GSUBp = new GSUB(g);
}

void GSUBFree(hotCtx g) {
    delete g->ctx.GSUBp;
    g->ctx.GSUBp = nullptr;
}

/* ------------------------ Supplementary Functions ------------------------ */

/* Begin new feature (can be called multiple times for same feature) */

void GSUB::FeatureBegin(Tag script, Tag language, Tag feature) {
    DF(2, (stderr, "\n"));
#if 1
    DF(1, (stderr, "{ GSUB '%c%c%c%c', '%c%c%c%c', '%c%c%c%c'\n",
           TAG_ARG(script), TAG_ARG(language), TAG_ARG(feature)));
#endif
    nw.script = script;
    nw.language = language;
    nw.feature = feature;
}

GSUB::Subtable::Subtable(GSUB &h, SubtableInfo &si) {
    bool hasFeatureParam = ((si.lkpType == GSUBFeatureNameParam) ||
                            (si.lkpType == GSUBCVParam));

    if (hasFeatureParam) {
        offset = h.offset.featParam;
    } else {
        offset = h.offset.subtable;
    }
    script = si.script;
    language = si.language;
    feature = si.feature;
    STRCPY_S(id_text, sizeof(id_text), h.g->error_id_text);  // save feature and lookup names for writing phase
    lkpType = si.lkpType;
    lkpFlag = si.lkpFlag;
    markSetIndex = si.markSetIndex;
    label = si.label;

    extension.use = si.useExtension;
    if (si.useExtension && (!IS_REF_LAB(si.label)) && (!hasFeatureParam)) {
        extension.otl = std::make_unique<otlTbl>(h.g);
        extension.offset = h.offset.extension; /* Not needed */
        h.fillExtensionSubst(si.lkpType, extension.tbl);
    }
}

void GSUB::AddSubtable(std::unique_ptr<Subtable> s) {
    subtables.push_back(std::move(s));
}

#if HOT_DEBUG

static void rulesDump(hotCtx g, GSUB::SubtableInfo &si) {
    fprintf(stderr, "# Dump lookupType %d rules:\n", si.lkpType);
    for (uint32_t i = 0; i < si.rules.size(); i++) {
        auto &rule = si.rules[i];

        fprintf(stderr, "  [%d] ", i);
        featPatternDump(g, rule.targ, ' ', 1);
    }
}

#endif

/* Begin new lookup */

void GSUB::LookupBegin(uint32_t lkpType, uint32_t lkpFlag, Label label,
                       bool useExtension, uint16_t useMarkSetIndex) {
    DF(2, (stderr,
           " { GSUB lkpType=%s%d lkpFlag=%d label=%x\n",
           useExtension ? "EXTENSION:" : "", lkpType, lkpFlag, label));

    nw.reset(lkpType, lkpFlag, label, useExtension, useMarkSetIndex);
}

/* End lookup */

void GSUB::LookupEnd(SubtableInfo *si) {
    DF(2, (stderr, " } GSUB\n"));

    if (si == nullptr)
        si = &nw;

    /* Return if simply a reference */
    if (IS_REF_LAB(si->label)) {
        AddSubtable(std::make_unique<Subtable>(*this, *si));
        return;
    }

    if (g->hadError)
        return;

    switch (si->lkpType) {
        case GSUBSingle:
            SingleSubst::fill(*this, *si);
            break;

        case GSUBMultiple:
            MultipleSubst::fill(*this, *si);
            break;

        case GSUBAlternate:
            AlternateSubst::fill(*this, *si);
            break;

        case GSUBLigature:
            LigatureSubst::fill(*this, *si);
            break;

        case GSUBChain:
            ChainSubst::fill(*this, *si);
            break;

        case GSUBReverse:
            ReverseSubst::fill(*this, *si);
            break;

        case GSUBFeatureNameParam:
            FeatureNameParam::fill(*this, *si);
            break;

        case GSUBCVParam:
            CVParam::fill(*this, *si);
            break;

        default:
            /* Can't get here, but it is a useful check for future development. */
            hotMsg(g, hotFATAL, "unknown GSUB lkpType <%d> in %s.", si->lkpType, g->error_id_text);
    }

    check_overflow(g, "lookup subtable", offset.subtable, "substitution");
    // XXX recycle rules
    /* This prevents the rules from being re-used unintentionally in the  */
    /* case where an empty GSUB feature is called for; because it is      */
    /* empty, the table type doesn't get correctly assigned, and the code */
    /* comes through here.                                                */
    si->rules.clear();
}

/* Performs no action but brackets feature calls */
void GSUB::FeatureEnd() {
    DF(2, (stderr, "} GSUB\n"));
}

/* Add rule (enumerating if necessary) to subtable si */

void GSUB::addSubstRule(SubtableInfo &si, GNode *targ, GNode *repl) {
#if HOT_DEBUG
    if (DF_LEVEL >= 2) {
        DF(2, (stderr, "  * GSUB RuleAdd "));
        featPatternDump(g, targ, ' ', 1);
        if (repl != NULL) {
            featPatternDump(g, repl, '\n', 1);
        }
    }
#endif

    /* Add rule(s), enumerating if not supported by the OT format */
    if (si.lkpType == GSUBSingle) {
        GNode *r = repl, *t = targ;
        for (; t != NULL; t = t->nextCl) {
            auto [i, b] = si.singles.insert({t->gid, r->gid});
            if (!b) {
                if (i->second == r->gid) {
                    featGlyphDump(g, t->gid, ',', 0);
                    *dnaNEXT(g->note) = ' ';
                    featGlyphDump(g, r->gid, '\0', 0);
                    hotMsg(g, hotNOTE,
                           "Removing duplicate single substitution "
                           "in %s: %s",
                           g->error_id_text,
                           g->note.array);
                } else {
                    featGlyphDump(g, t->gid, '\0', 0);
                    hotMsg(g, hotFATAL,
                           "Duplicate target glyph for single "
                           "substitution in %s: %s",
                           g->error_id_text, g->note.array);
                }

            }
            // If repl is a glyph use it for all entries in targ
            if (r->nextCl != nullptr)
                r = r->nextCl;
        }
        featRecycleNodes(g, targ);
        featRecycleNodes(g, repl);
        return;
    } else if (si.lkpType == GSUBLigature) {
        uint32_t length = featGetPatternLen(g, targ);
        GNode *t;
        for (t = targ; t != NULL; t = t->nextSeq) {
            if (t->nextCl != NULL) {
                break;
            }
        }

        if (t != NULL) {
            uint16_t i;
            uint32_t nSeq;
            GNode **prod = featMakeCrossProduct(g, targ, &nSeq);

            featRecycleNodes(g, targ);
            for (i = 0; i < nSeq; i++) {
#if HOT_DEBUG
                if (DF_LEVEL >= 2) {
                    fprintf(stderr, "               > ");
                    featPatternDump(g, prod[i], '\n', 1);
                }
#endif
                si.rules.emplace_back(prod[i], i == 0 ? repl : featSetNewNode(g, repl->gid), length);
            }
            return;
        } else {
            si.rules.emplace_back(targ, repl, length);
        }
    } else {
        /* Add whole rule intact (no enumeration needed) */
        si.rules.emplace_back(targ, repl);
    }
}

/* Stores input GNodes; they are recycled at GSUBLookupEnd. */

void GSUB::RuleAdd(GNode *targ, GNode *repl) {
    if (g->hadError)
        return;

    addSubstRule(nw, targ, repl);
}

/* Break the subtable at this point. Return 0 if successful, else 1. */

bool GSUB::SubtableBreak() {
    return true;
}

void GSUB::SetFeatureNameID(Tag feat, uint16_t nameID) {
    featNameID.insert({feat, nameID});
}

void GSUB::AddFeatureNameParam(uint16_t nameID) {
    nw.paramNameID = nameID;
}

GSUB::FeatureNameParam::FeatureNameParam(GSUB &h, SubtableInfo &si,
                                         uint16_t nameID) :
                                         Subtable(h, si), nameID(nameID) {}

void GSUB::FeatureNameParam::fill(GSUB &h, SubtableInfo &si) {
    uint16_t ssNumber = ((si.feature >> 8 & 0xFF) - (int)'0') * 10;
    ssNumber += (si.feature & 0xFF) - (int)'0';
    if (((si.feature >> 24 & 0xFF) == (int)'s') &&
        ((si.feature >> 16 & 0xFF) == (int)'s') &&
        (ssNumber <= 99)) {
        if (si.paramNameID != 0) {
            uint16_t nameIDPresent = nameVerifyDefaultNames(h.g, si.paramNameID);
            if (nameIDPresent && (nameIDPresent & MISSING_WIN_DEFAULT_NAME)) {
                hotMsg(h.g, hotFATAL,
                       "Missing Windows default name for 'featureNames' nameid %i in %s.",
                       si.paramNameID, h.g->error_id_text);
            }
        }
    } else {
        hotMsg(h.g, hotFATAL,
               "A 'featureNames' block is only allowed in Stylistic Set (ssXX) features; it is being used in %s.",
               h.g->error_id_text);
    }
    std::unique_ptr<GSUB::Subtable> s = std::make_unique<FeatureNameParam>(h, si, si.paramNameID);
    h.offset.featParam += FeatureNameParam::size();
    h.AddSubtable(std::move(s));
}

void GSUB::FeatureNameParam::write(GSUB *h) {
    OUT2(subformat());
    OUT2(nameID);
}

GSUB::CVParam::CVParam(GSUB &h, SubtableInfo &si, CVParameterFormat &&p) :
                                   Subtable(h, si), params(std::move(p)) {}

void GSUB::CVParam::fill(GSUB &h, SubtableInfo &si) {
    uint16_t nameIDs[4];
    uint16_t cvNumber = ((si.feature >> 8 & 0xFF) - (int)'0') * 10;
    cvNumber += (si.feature & 0xFF) - (int)'0';
    if (((si.feature >> 24 & 0xFF) == (int)'c') &&
        ((si.feature >> 16 & 0xFF) == (int)'v') &&
        (cvNumber <= 99)) {
        nameIDs[0] = si.cvParams.FeatUILabelNameID;
        nameIDs[1] = si.cvParams.FeatUITooltipTextNameID;
        nameIDs[2] = si.cvParams.SampleTextNameID;
        nameIDs[3] = si.cvParams.FirstParamUILabelNameID;
        for (int i = 0; i < 4; i++) {
            uint16_t nameid = nameIDs[i];
            if (nameid != 0) {
                uint16_t nameIDPresent = nameVerifyDefaultNames(h.g, nameid);
                if (nameIDPresent && nameIDPresent & MISSING_WIN_DEFAULT_NAME) {
                    hotMsg(h.g, hotFATAL,
                           "Missing Windows default name for 'cvParameters' nameid %i in %s.",
                           nameid, h.g->error_id_text);
                }
            }
        }
    } else {
        hotMsg(h.g, hotFATAL,
               "A 'cvParameters' block is only allowed in Character Variant (cvXX) features; it is being used in %s.",
               h.g->error_id_text);
    }
    auto sz = si.cvParams.size();
    h.AddSubtable(std::make_unique<CVParam>(h, si, std::move(si.cvParams)));
    h.offset.featParam += sz;
}

void GSUB::CVParam::write(GSUB *h) {
    OUT2(subformat());
    OUT2(params.FeatUILabelNameID);
    OUT2(params.FeatUITooltipTextNameID);
    OUT2(params.SampleTextNameID);
    OUT2(params.NumNamedParameters);
    OUT2(params.FirstParamUILabelNameID);
    OUT2((uint16_t)params.charValues.size());
    for (auto cv: params.charValues) {
        uint32_t uv = cv;
        int8_t val1 = (int8_t)(uv >> 16);
        uint16_t val2 = (uint16_t)(uv & 0x0000FFFF);
        OUT1(val1);
        OUT2(val2);
    }
}

void GSUB::AddCVParam(CVParameterFormat &&params) {
    nw.cvParams.swap(std::move(params));
}

/* -------------------------- Single Substitution -------------------------- */

GSUB::SingleSubst::SingleSubst(GSUB &h, SubtableInfo &si) : Subtable(h, si) {}

Offset GSUB::SingleSubst::fillSingleCoverage(SubtableInfo &si, otlTbl &otl) {
    otl.coverageBegin();
    for (auto [t, _]: si.singles) {
        otl.coverageAddGlyph(t);
    }
    return otl.coverageEnd();
}

SingleSubstFormat1::SingleSubstFormat1(GSUB &h, GSUB::SubtableInfo &si, int delta) : SingleSubst(h, si) {
    LOffset sz = size();
    otlTbl &otl = getOtl(h);
    Coverage = fillSingleCoverage(si, otl); /* Adjusted later */
    DeltaGlyphID = delta;

    if (extension.use) {
        Coverage += sz; /* Final value */
        h.offset.extension += sz + otl.getCoverageSize();
    } else {
        h.offset.subtable += sz;
    }
}

SingleSubstFormat2::SingleSubstFormat2(GSUB &h, GSUB::SubtableInfo &si) : SingleSubst(h, si) {
    LOffset sz = size(si.singles.size());
    otlTbl &otl = getOtl(h);

    Coverage = fillSingleCoverage(si, otl); /* Adjusted later */
    for (auto [_, r]: si.singles)
        gids.push_back(r);

    if (extension.use) {
        Coverage += sz; /* Final value */
        h.offset.extension += sz + otl.getCoverageSize();
    } else {
        h.offset.subtable += sz;
    }
}

void GSUB::SingleSubst::fill(GSUB &h, SubtableInfo &si) {
    h.maxContext = MAX(h.maxContext, 1);

    if (si.feature == vrt2_) {
        h.g->convertFlags |= HOT_SEEN_VERT_ORIGIN_OVERRIDE;

        for (auto [t, r]: si.singles) {
            auto &hotgi = h.g->glyphs[r];
            if (hotgi.vAdv == SHRT_MAX) {
                /* don't set it if it has already been set, as with vmtx overrides */
                hotgi.vAdv = -(h.g->glyphs[t].hAdv);
            }
        }
    }

    /* Determine format and fill subtable */
    bool first = true;
    long delta;
    for (auto [t, r]: si.singles) {
        if (first) {
            delta = r - t;
            first = false;
        } else if (delta != r - t) {
            h.AddSubtable(std::make_unique<SingleSubstFormat2>(h, si));
            return;
        }
    }
    h.AddSubtable(std::make_unique<SingleSubstFormat1>(h, si, delta));
}

void SingleSubstFormat1::write(GSUB *h) {
    if (!extension.use)
        Coverage += h->offset.subtable - offset; /* Adjust offset */

    check_overflow(h->g, "coverage table", Coverage, "single substitution");

    OUT2(subformat());
    OUT2((Offset)Coverage);
    OUT2(DeltaGlyphID);

    if (extension.use)
        extension.otl->coverageWrite();
}

void SingleSubstFormat2::write(GSUB *h) {
    if (!extension.use)
        Coverage += h->offset.subtable - offset; /* Adjust offset */

    check_overflow(h->g, "coverage table", Coverage, "single substitution");

    OUT2(subformat());
    OUT2((Offset)(Coverage));
    OUT2((uint16_t)gids.size());
    for (auto g: gids)
        OUT2((GID)g);

    if (extension.use)
        extension.otl->coverageWrite();
}

/* ------------------------- Multiple Substitution ------------------------- */

GSUB::MultipleSubst::MultipleSubst(GSUB &h, SubtableInfo &si, long beg,
                                   long end, long sz, uint32_t nSubs) : Subtable(h, si) {
#define AALT_STATS 1 /* Print aalt statistics with debug output */
#if HOT_DEBUG
    auto g = h.g;
    if (beg != 0 || end != si.rules.size() - 1) {
        DF(1, (stderr, "fillMultiple1() from %ld->%ld; totNumRules=%ld\n", beg, end,
               si.rules.size()));
    }
#endif /* HOT_DEBUG */

    otlTbl &otl = getOtl(h);

    int nSequences = end - beg + 1;

    LOffset offst = headerSize(nSequences);
    otl.coverageBegin();
    for (int i = 0; i < nSequences; i++) {
        auto &rule = si.rules[i + beg];
        MultSequence seq;

        otl.coverageAddGlyph(rule.targ->gid);

        for (GNode *node = rule.repl; node != NULL; node = node->nextSeq)
            seq.gids.push_back(node->gid);

        seq.offset = offst;
        offst += seq.size();
        sequences.emplace_back(std::move(seq));
    }

#if HOT_DEBUG
    if (offst != sz) {
        hotMsg(h.g, hotFATAL, "[internal] fillSubstitute() size miscalculation");
    }
#if AALT_STATS
    if (si.feature == aalt_) {
        DF(1, (stderr,
               "# aalt lkptype 3 subtbl: average %.2f repl gids "
               "per rule for %ld rules. subtbl size: %hx\n",
               (double)nSubs / nSequences, nSequences, offset));
    }
#endif
#endif /* HOT_DEBUG */

    Coverage = otl.coverageEnd(); /* Adjusted later */
    if (extension.use) {
        Coverage += offst; /* Final value */
        h.offset.extension += offst + otl.getCoverageSize();
    } else {
        h.offset.subtable += offst;
    }
    h.maxContext = MAX(h.maxContext, 1);
}

#if HOT_DEBUG
/* Dump accumulated aalt rules */
static void aaltDump(GSUB &h, GSUB::SubtableInfo &si) {
    if (si.feature == aalt_) {
        fprintf(stderr, "--- aalt GSUBAlternate --- %ld rules\n",
                si.rules.size());
        for (auto &rule: si.rules) {
            fprintf(stderr, "sub ");
            featGlyphDump(h.g, rule.targ->gid, -1, 1);
            fprintf(stderr, " from ");
            featPatternDump(h.g, rule.repl, '\n', 1);
        }
    }
}

#endif

/* Fill the currently accumulated alternate substitution subtable, auto-
   breaking into several subtables if needed. */

void GSUB::MultipleSubst::fill(GSUB &h, SubtableInfo &si) {
    long sz = 0;
    uint32_t nSubs = 0;

    std::sort(si.rules.begin(), si.rules.end());
#if 0
    aaltDump(h, si);
#endif
    int i = 0;
    for (size_t j = 0; j < si.rules.size(); j++) {
        auto &rule = si.rules[j];
        /* Check for duplicates */
        if (j != 0 && rule.targ->gid == si.rules[j-1].targ->gid) {
            featGlyphDump(h.g, rule.targ->gid, '\0', 0);
            hotMsg(h.g, hotFATAL,
                   "Duplicate target glyph for multiple substitution in "
                   "%s: %s",
                   h.g->error_id_text,
                   h.g->note.array);
        }

        /* Calculate nw size if this rule were included: */
        uint32_t nSubsNew = nSubs;
        for (GNode *node = rule.repl; node != NULL; node = node->nextSeq)
            nSubsNew++;

        long sizeNew = size(j - i + 1, nSubsNew);

        if (sizeNew > 0xFFFF) {
            /* Just overflowed size; back up one rule */
            h.AddSubtable(std::make_unique<MultipleSubst>(h, si, i, j-1, sz, nSubs));
            /* Initialize for next subtable */
            sz = nSubs = 0;
            i = j--;
        } else if (j == si.rules.size() - 1) {
            /* At end of array */
            h.AddSubtable(std::make_unique<MultipleSubst>(h, si, i, j, sizeNew, nSubsNew));
        } else {
            /* Not ready for a subtable break yet */
            sz = sizeNew;
            nSubs = nSubsNew;
        }
    }
}

void GSUB::MultipleSubst::write(GSUB *h) {
    if (!extension.use)
        Coverage += h->offset.subtable - offset; /* Adjust offset */

    check_overflow(h->g, "coverage table", Coverage, "multiple substitution");

    OUT2(subformat());
    OUT2((Offset)(Coverage));
    OUT2((uint32_t)sequences.size());

    for (auto &seq: sequences)
        OUT2((uint16_t)seq.offset);
    for (auto &seq: sequences) {
        OUT2((uint16_t)seq.gids.size());
        for (auto g: seq.gids)
            OUT2(g);
    }

    if (extension.use)
        extension.otl->coverageWrite();
}

/* ------------------------- Alternate Substitution ------------------------ */

/* Create a subtable with rules from index [beg] to [end]. size: total size
   (excluding actual coverage). numAlts: total number of replacement glyphs. */

GSUB::AlternateSubst::AlternateSubst(GSUB &h, SubtableInfo &si,
                                     long beg, long end, long size,
                                     uint16_t numAlts) : Subtable(h, si) {
#define AALT_STATS 1 /* Print aalt statistics with debug output */

#if HOT_DEBUG
    auto g = h.g;
    if (beg != 0 || end != si.rules.size() - 1) {
        DF(1, (stderr, "fillAlt() from %ld->%ld; totNumRules=%ld\n", beg, end,
               si.rules.size()));
    }
#endif /* HOT_DEBUG */

    otlTbl &otl = getOtl(h);

    uint32_t nAltSets = end - beg + 1;

    LOffset offst = headerSize(nAltSets);
    otl.coverageBegin();
    for (uint32_t i = 0; i < nAltSets; i++) {
        auto &rule = si.rules[i + beg];
        AlternateSet altSet;

        otl.coverageAddGlyph(rule.targ->gid);

        /* --- Fill an AlternateSet --- */
        for (GNode *node = rule.repl; node != NULL; node = node->nextCl)
            altSet.gids.push_back(node->gid);

        altSet.offset = offst;
        offst += altSet.size();
        altSets.emplace_back(std::move(altSet));
    }

#if HOT_DEBUG
    if (offst != size) {
        hotMsg(h.g, hotFATAL, "[internal] fillAlternate() size miscalculation");
    }
#if AALT_STATS
    if (si.feature == aalt_) {
        DF(1, (stderr,
               "# aalt lkptype 3 subtbl: average %.2f repl gids "
               "per rule for %ld rules. subtbl size: %hx\n",
               (double)numAlts / nAltSets, nAltSets, offst));
    }
#endif
#endif /* HOT_DEBUG */

    Coverage = otl.coverageEnd(); /* Adjusted later */
    if (extension.use) {
        Coverage += offst; /* Final value */
        h.offset.extension += offst + otl.getCoverageSize();
    } else {
        h.offset.subtable += offst;
    }
    h.maxContext = MAX(h.maxContext, 1);
}

/* Fill the currently accumulated alternate substitution subtable, auto-
   breaking into several subtables if needed. */

void GSUB::AlternateSubst::fill(GSUB &h, SubtableInfo &si) {
    long sz = 0;
    uint32_t numAlts = 0;

    /* Sort by target glyph */
    std::sort(si.rules.begin(), si.rules.end());
#if 0
    aaltDump(h, si);
#endif
    int i = 0;
    for (size_t j = 0; j < si.rules.size(); j++) {
        auto &rule = si.rules[j];

        /* Check for duplicates */
        if (j != 0 && rule.targ->gid == si.rules[j-1].targ->gid) {
            featGlyphDump(h.g, rule.targ->gid, '\0', 0);
            hotMsg(h.g, hotFATAL,
                   "Duplicate target glyph for alternate substitution in "
                   "%s: %s",
                   h.g->error_id_text,
                   h.g->note.array);
        }

        /* Calculate new size if this rule were included: */
        uint32_t numAltsNew = numAlts;
        for (GNode *node = rule.repl; node != NULL; node = node->nextCl)
            numAltsNew++;
        long sizeNew = size(j - i + 1, numAltsNew);

        if (sizeNew > 0xFFFF) {
            /* Just overflowed size; back up one rule */
            h.AddSubtable(std::make_unique<AlternateSubst>(h, si, i, j-1, sz, numAlts));
            /* Initialize for next subtable */
            sz = numAlts = 0;
            i = j--;
        } else if (j == si.rules.size() - 1) {
            /* At end of array */
            h.AddSubtable(std::make_unique<AlternateSubst>(h, si, i, j, sizeNew, numAltsNew));
        } else {
            /* Not ready for a subtable break yet */
            sz = sizeNew;
            numAlts = numAltsNew;
        }
    }
}

void GSUB::AlternateSubst::write(GSUB *h) {
    if (!extension.use)
        Coverage += h->offset.subtable - offset; /* Adjust offset */

    check_overflow(h->g, "coverage table", Coverage, "alternate substitution");
    OUT2(subformat());
    OUT2((Offset)(Coverage));
    OUT2((uint16_t)altSets.size());

    for (auto &set: altSets)
        OUT2((uint16_t)set.offset);
    for (auto &set: altSets) {
        OUT2((uint16_t)set.gids.size());
        for (auto g: set.gids) 
            OUT2(g);
    }

    if (extension.use)
        extension.otl->coverageWrite();
}

/* ------------------------- Ligature Substitution ------------------------- */

/* Sort by targ's first gid, targ's length (decr), then all of targ's GIDs.
   Deleted duplicates (targ == NULL) sink to the bottom */

static bool cmpLigature(const GSUB::SubstRule &a, const GSUB::SubstRule &b) {

    if (a.targ->gid != b.targ->gid)
        return a.targ->gid < b.targ->gid;
    else if (a.data != b.data)
        return a.data > b.data;   // Longer patterns sort earlier
    else {
        // Lengths have to be the same now
        GNode *ga = a.targ, *gb = b.targ;
        for (; ga != NULL; ga = ga->nextSeq, gb = gb->nextSeq) {
            if (ga->gid != gb->gid)
                return ga->gid < gb->gid;
        }
    }
    return false;
}

/* Check for duplicate ligatures; sort */

void GSUB::LigatureSubst::checkAndSort(GSUB &h, SubtableInfo &si) {
    std::sort(si.rules.begin(), si.rules.end(), cmpLigature);

    size_t i = 1;
    while (i < si.rules.size()) {
        SubstRule &curr = si.rules[i];
        SubstRule &prev = si.rules[i-1];

        if (!cmpLigature(curr, prev) && !cmpLigature(prev, curr)) {
            if (curr.repl->gid == prev.repl->gid) {
                featPatternDump(h.g, curr.targ, ',', 0);
                *dnaNEXT(h.g->note) = ' ';
                featGlyphDump(h.g, curr.repl->gid, '\0', 0);
                hotMsg(h.g, hotNOTE,
                       "Removing duplicate ligature substitution"
                       " in %s: %s",
                       h.g->error_id_text,
                       h.g->note.array);

                /* Set prev duplicates to NULL */
                featRecycleNodes(h.g, curr.targ);
                featRecycleNodes(h.g, prev.repl);
            } else {
                featPatternDump(h.g, curr.targ, '\0', 0);
                hotMsg(h.g, hotFATAL,
                       "Duplicate target sequence but different "
                       "replacement glyphs in ligature substitutions in "
                       "%s: %s",
                       h.g->error_id_text,
                       h.g->note.array);
            }
            si.rules.erase(si.rules.begin() + i);
        } else {
            i++;
        }
    }
}

/* Fill ligature substitution subtable */

GSUB::LigatureSubst::LigatureSubst(GSUB &h, SubtableInfo &si) : Subtable(h, si) {
    unsigned nLigSets = 0;

    otlTbl &otl = getOtl(h);

#if 0
    fprintf(stderr, "--- Final sorted lig list (%ld els): \n",
            si.rules.cnt);
    rulesDump(h.g, si);
#endif

    otl.coverageBegin();
    for (size_t i = 0; i < si.rules.size(); i++) {
        SubstRule &curr = si.rules[i];

        if (i == 0 || curr.targ->gid != si.rules[i-1].targ->gid) {
            nLigSets++;
            otl.coverageAddGlyph(curr.targ->gid);
        }
    }
    LOffset offst = headerSize(nLigSets);

    int iLigSet = 0;
    for (size_t i = 1; i <= si.rules.size(); i++) {
        if (i == si.rules.size() || si.rules[i].targ->gid != (si.rules[i - 1]).targ->gid) {
            /* --- Fill a LigatureSet --- */
            LigatureSet ligSet;
            LOffset offLig = ligSet.size(i - iLigSet);

            for (size_t k = iLigSet; k < i; k++) {
                /* --- Fill a Ligature --- */
                auto &rule = si.rules[k];
                LigatureGlyph lg;

                lg.ligGlyph = rule.repl->gid;

                for (GNode *node = rule.targ->nextSeq; node != NULL;
                     node = node->nextSeq)
                    lg.components.push_back(node->gid);
                lg.offset = offLig;
                offLig += lg.size();
                h.maxContext = MAX(h.maxContext, lg.size());
                ligSet.ligatures.emplace_back(std::move(lg));
            }
            ligSet.offset = offst;
            ligatureSets.emplace_back(std::move(ligSet));
            offst += offLig;
            iLigSet = i;
        }
    }

    check_overflow(h.g, "lookup subtable", offst, "ligature substitution");
    Coverage = otl.coverageEnd(); /* Adjusted later */
    if (extension.use) {
        Coverage += offst; /* Final value */
        h.offset.extension += offst + otl.getCoverageSize();
    } else {
        h.offset.subtable += offst;
    }
}

void GSUB::LigatureSubst::fill(GSUB &h, SubtableInfo &si) {
    checkAndSort(h, si);

    h.AddSubtable(std::make_unique<LigatureSubst>(h, si));
}
void GSUB::LigatureSubst::write(GSUB *h) {
    if (!extension.use)
        Coverage += h->offset.subtable - offset; /* Adjust offset */

    check_overflow(h->g, "coverage table", Coverage, "ligature substitution");
    OUT2(subformat());
    OUT2((Offset)Coverage);
    OUT2((uint16_t)ligatureSets.size());

    for (auto &ls: ligatureSets)
        OUT2((Offset)ls.offset);
    for (auto &ls: ligatureSets) {
        OUT2((uint16_t)ls.ligatures.size());
        for (auto &l: ls.ligatures)
            OUT2(l.offset);
        for (auto &l: ls.ligatures) {
            OUT2(l.ligGlyph);
            OUT2((uint16_t)l.components.size() + 1);  // first component in Coverage
            for (auto g: l.components)
                OUT2(g);
        }
    }

    if (extension.use) {
        extension.otl->coverageWrite();
    }
}

/* ------------------ Chaining Contextual Substitution --------------------- */

void GSUB::recycleProd(GNode **prod, int count) {
    for (int i = 0; i < count; i++)
        featRecycleNodes(g, prod[i]);
}

/* Tries to add rule to current anon subtbl. If successful, returns 1, else 0.
   If rule already exists in subtbl, recycles targ and repl */

bool GSUB::addSingleToAnonSubtbl(SubtableInfo &si, GNode *targ, GNode *repl) {
    GNode *t = targ;
    GNode *r = repl;
    std::map<GID, GID> needed;

    assert(si.lkpType == GSUBSingle);
    /* Determine which rules already exist in the subtable */
    for (; t != NULL; t = t->nextCl) {
        t->flags &= ~FEAT_MISC; /* Clear "found" flag */
        auto i = si.singles.find(t->gid);
        if (i != si.singles.end()) {
            if (i->second != r->gid)
                return false;
        } else {
            // XXX warn about dups?
            needed.insert({t->gid, r->gid});
        }
        if (r->nextCl != nullptr)
            r = r->nextCl;
    }

    for (auto [tgid, rgid]: needed)
        si.singles.insert({tgid, rgid});

    featRecycleNodes(g, targ);
    featRecycleNodes(g, repl);

    return true;
}

bool GSUB::addLigatureToAnonSubtbl(SubtableInfo &si, GNode *targ, GNode *repl) {
    uint32_t nSeq;

    assert(si.lkpType == GSUBLigature);
    GNode **prod = featMakeCrossProduct(g, targ, &nSeq);

    for (uint32_t i = 0; i < nSeq; i++) {
        GNode *t = prod[i];

        t->flags &= ~FEAT_MISC; /* Clear "found" flag */
        for (auto &rule: si.rules) {
            if (t->gid != rule.targ->gid)
                continue;

            GNode *pI = t;
            GNode *pJ = rule.targ;

            for (; pI->nextSeq != NULL && pJ->nextSeq != NULL &&
                   pI->nextSeq->gid == pJ->nextSeq->gid;
                 pI = pI->nextSeq, pJ = pJ->nextSeq) {
            }
            /* pI and pJ now point at the last identical node */

            if (pI->nextSeq == NULL && pJ->nextSeq == NULL) {
                /* Identical targets */
                if (repl->gid == rule.repl->gid) {
                    /* Identical targ and repl */
                    t->flags |= FEAT_MISC;
                    continue;
                } else {
                    recycleProd(prod, nSeq);
                    return false;
                }
            } else if (pI->nextSeq == NULL || pJ->nextSeq == NULL) {
                /* One is a subset of the other */
                recycleProd(prod, nSeq);
                return false;
            }
        }
    }

    /* Add any rules that were not found */
    featRecycleNodes(g, targ);
    for (uint32_t i = 0; i < nSeq; i++) {
        GNode *t = prod[i];
        if (!(t->flags & FEAT_MISC)) {
            addSubstRule(si, t, featSetNewNode(g, repl->gid));
        } else {
            featRecycleNodes(g, t);
        }
    }
    featRecycleNodes(g, repl);
    return true;
}

/* Add the "anonymous" rule that occurs in a substitution within a chaining
   contextual rule. Return the label of the anonymous lookup */

Label GSUB::addAnonRule(SubtableInfo &cur_si, GNode *pMarked,
                        uint32_t nMarked, GNode *repl) {
    GNode *targCp;
    GNode *replCp;
    int lkpType;

    if (nMarked == 1) {
        if (repl->nextSeq != NULL) {
            lkpType = GSUBMultiple;
        } else {
            lkpType = GSUBSingle;
        }
    } else {
        lkpType = GSUBLigature;
    }

    /* Make copies in targCp, replCp */
    featPatternCopy(g, &targCp, pMarked, nMarked);
    featPatternCopy(g, &replCp, repl, -1);

    if (anonSubtable.size() > 0) {
        auto &si = anonSubtable.back();
        if ((si.lkpType == lkpType) && (si.lkpFlag == cur_si.lkpFlag) &&
            (si.markSetIndex == cur_si.markSetIndex) &&
            (si.parentFeatTag == cur_si.feature)) {
            if (lkpType == GSUBSingle && addSingleToAnonSubtbl(si, targCp, replCp))
                return si.label;
            else if (lkpType == GSUBLigature && addLigatureToAnonSubtbl(si, targCp, replCp))
                return si.label;
        }
    }

    SubtableInfo asi;

    /* Must create new anon subtable */
    asi.script = cur_si.script;
    asi.language = cur_si.language;
    asi.lkpType = lkpType;
    asi.lkpFlag = cur_si.lkpFlag;
    asi.markSetIndex = cur_si.markSetIndex;
    asi.label = featGetNextAnonLabel(g);
    asi.parentFeatTag = nw.feature;
    asi.useExtension = cur_si.useExtension;

    addSubstRule(asi, targCp, replCp);

    anonSubtable.emplace_back(std::move(asi));

    return anonSubtable.back().label;
}

/* Create anonymous lookups (referred to only from within chain ctx lookups) */

void GSUB::createAnonLookups() {
    for (auto &si: anonSubtable) {
        // so that these will sort to the end of the subtable array
        // and will not be considered for adding to the FeatureList table
        si.script = si.language = si.feature = TAG_UNDEF;
        snprintf(g->error_id_text, sizeof(g->error_id_text), "feature '%c%c%c%c'", TAG_ARG(si.parentFeatTag));
#if HOT_DEBUG
        for (auto &rule: si.rules) {
            if (DF_LEVEL >= 2) {
                DF(2, (stderr, "  * GSUB RuleAdd "));
                featPatternDump(g, rule.targ, ' ', 1);
                if (rule.repl != NULL) {
                    featPatternDump(g, rule.repl, '\n', 1);
                }
            }
        }
#endif
        LookupEnd(&si);
        FeatureEnd();
    }
}

/* Change anon SubstLookupRecord labels to lookup indices, now that they've been
   calculated by otlFill() */

void GSUB::setAnonLookupIndices() {
    for (auto &sub: subtables) {
        auto slv = sub->getSubstLookups();
        if (slv == nullptr)
            continue;
        for (auto &slr: *slv) {
            DF(2, (stderr, "slr: Label 0x%x", slr.LookupListIndex));
            slr.LookupListIndex = otl.label2LookupIndex(slr.LookupListIndex);
            DF(2, (stderr, " -> LookupListIndex %u\n", slr.LookupListIndex));
        }
    }
}

/* p points to an input sequence; return new array of num coverages */

void GSUB::setCoverages(std::vector<LOffset> &covs, otlTbl &otl, GNode *p, uint32_t num) {
    if (num == 0)
        return;

    covs.reserve(num);
    for (uint32_t i = 0; i != num; i++, p = p->nextSeq) {
        otl.coverageBegin();
        for (GNode *q = p; q != NULL; q = q->nextCl) {
            otl.coverageAddGlyph(q->gid);
        }
        covs.push_back(otl.coverageEnd());
    }
}

/* Fill chaining contextual subtable format 3 */

GSUB::ChainSubst::ChainSubst(GSUB &h, SubtableInfo &si, SubstRule &rule) : Subtable(h, si) {
    LOffset size;
    unsigned nBack = 0;
    unsigned nInput = 0;
    unsigned nLook = 0;
    unsigned nMarked = 0;
    unsigned seqCnt = 0;
    GNode *pBack = NULL;
    GNode *pInput = NULL;
    GNode *pLook = NULL;
    GNode *pMarked = NULL;
    int iSeq = 0; /* Suppress optimizer warning */
    uint32_t nSubst = (rule.repl != nullptr) ? 1 : 0;

    GNode *p;

    otlTbl &otl = getOtl(h);

    /* Set counts of and pointers to Back, Input, Look, Marked areas */
    pBack = rule.targ;
    for (p = rule.targ; p != NULL; p = p->nextSeq) {
        if (p->flags & FEAT_BACKTRACK) {
            nBack++;
        } else if (p->flags & FEAT_INPUT) {
            if (pInput == NULL) {
                pInput = p;
            }
            nInput++;
            if (p->flags & FEAT_MARKED) {
                /* Marked must be within Input */
                if (pMarked == NULL) {
                    pMarked = p;
                    iSeq = seqCnt;
                }
                nMarked++;
                nSubst += p->lookupLabelCount;
            }
            seqCnt++;
        } else if (p->flags & FEAT_LOOKAHEAD) {
            if (pLook == NULL) {
                pLook = p;
            }
            nLook++;
        }
    }

    /* Fill table */
    h.setCoverages(backtracks, otl, pBack, nBack);
    h.setCoverages(inputGlyphs, otl, pInput, nInput);
    h.setCoverages(lookaheads, otl, pLook, nLook);
    if (nSubst > 0) {
        substLookupRecords.reserve(nSubst);
        if (rule.repl != NULL) {
            /* There is only a single replacement rule, not using direct lookup references */
            SubstLookupRecord slr;
            slr.SequenceIndex = iSeq;
            slr.LookupListIndex = h.addAnonRule(si, pMarked, nMarked, rule.repl);
            substLookupRecords.push_back(slr);
        } else {
            GNode *nextNode = pMarked;
            for (uint32_t i = 0; i < nMarked; i++) {
                if (nextNode->lookupLabelCount > 0) {
                    for (int j = 0; j < nextNode->lookupLabelCount; j++) {
                        SubstLookupRecord slr;
                        slr.SequenceIndex = i;
                        slr.LookupListIndex = nextNode->lookupLabels[j];
                        substLookupRecords.push_back(slr);
                    }
                }
                nextNode = nextNode->nextSeq;
            }
        }
    }

    h.maxContext = MAX(h.maxContext, nInput + nLook);

    size = chain3size(nBack, nInput, nLook, nSubst);
    if (extension.use) {
        /* Set final values for coverages */
        for (auto &bt: backtracks)
            bt += size;
        for (auto &ig: inputGlyphs)
            ig += size;
        for (auto &la: lookaheads)
            la += size;
        h.offset.extension += size + otl.getCoverageSize();
        /* h->offset.subtable already incr in fillExtension() */
    } else {
        h.offset.subtable += size;
    }
    featRecycleNodes(h.g, rule.targ);
}

void GSUB::ChainSubst::fill(GSUB &h, SubtableInfo &si) {
    for (auto &rule: si.rules) {
        h.AddSubtable(std::make_unique<ChainSubst>(h, si, rule));
        check_overflow(h.g, "lookup subtable", h.offset.subtable, "chain contextual substitution");
    }
}

void GSUB::ChainSubst::write(GSUB *h) {
    LOffset adjustment = 0; /* (Linux compiler complains) */
    bool isExt = extension.use;

    if (!isExt)
        adjustment = (h->offset.subtable - offset);

    OUT2(subformat());

    OUT2((uint16_t)backtracks.size());

    if (h->g->convertFlags & HOT_ID2_CHAIN_CONTXT3) {
        /* do it per OpenType spec 1.4 and earlier,as In Design 2.0 and earlier requires. */
        for (auto &bt: backtracks) {
            if (!isExt)
                bt += adjustment;
            check_overflow(h->g, "backtrack coverage table", bt, "chain contextual substitution");
            OUT2((uint16_t)bt);
        }
    } else {
        /* do it per OpenType spec 1.5 */
        for (auto ri = backtracks.rbegin(); ri != backtracks.rend(); ri++) {
            if (!isExt)
                *ri += adjustment;
            check_overflow(h->g, "backtrack coverage table", *ri, "chain contextual substitution");
            OUT2((uint16_t)*ri);
        }
    }

    OUT2((uint16_t)inputGlyphs.size());
    for (auto &ig: inputGlyphs) {
        if (!isExt)
            ig += adjustment;
        check_overflow(h->g, "input coverage table", ig, "chain contextual substitution");
        OUT2((uint16_t)ig);
    }

    OUT2((uint16_t)lookaheads.size());
    for (auto &la: lookaheads) {
        if (!isExt)
            la += adjustment;
        check_overflow(h->g, "lookahead coverage table", la, "chain contextual substitution");
        OUT2((uint16_t)la);
    }

    OUT2((uint16_t)substLookupRecords.size());
    for (auto &slr: substLookupRecords) {
        OUT2(slr.SequenceIndex);
        OUT2(slr.LookupListIndex);
    }

    if (isExt) 
        extension.otl->coverageWrite();
}

static bool CTL_CDECL cmpNode(GNode *an, GNode *bn) {
    return an->gid < bn->gid;
}

static void sortInputList(GNode *&list) {
    std::vector<GNode *> tmp;

    for (GNode *p = list; p != NULL; p = p->nextCl)
        tmp.push_back(p);

    std::sort(tmp.begin(), tmp.end(), cmpNode);

    /* Move pointers around */
    for (size_t i = 0; i < tmp.size() - 1; i++) {
        tmp[i]->nextCl = tmp[i + 1];
    }
    tmp.back()->nextCl = NULL;

    list = tmp[0];
}

GSUB::ReverseSubst::ReverseSubst(GSUB &h, SubtableInfo &si, SubstRule &rule) : Subtable(h, si) {
    LOffset size;
    unsigned nBack = 0;
    unsigned nInput = 0;
    unsigned nLook = 0;
    GNode *pBack = NULL;
    GNode *pInput = NULL;
    GNode *pLook = NULL;
    GNode *p, *r;
    unsigned subCount = 0;

    otlTbl &otl = getOtl(h);

    /* Set counts of and pointers to Back, Input, Look, Marked areas */
    pBack = rule.targ;
    for (p = rule.targ; p != NULL; p = p->nextSeq) {
        if (p->flags & FEAT_BACKTRACK) {
            nBack++;
        } else if (p->flags & FEAT_INPUT) {
            /* Note: we validate that there is only one Input glyph in feat.c */
            if (pInput == NULL) {
                pInput = p;
            }
            nInput++;
        } else if (p->flags & FEAT_LOOKAHEAD) {
            if (pLook == NULL) {
                pLook = p;
            }
            nLook++;
        }
    }

    /* When we call otlCoverageEnd, the input coverage will be sorted in   */
    /* GID order. The replacement glyph list must also be sorted in that   */
    /* order. So, I copy the replacement glyph gids into the target Gnodes */
    /* as the nextSeq value. We can then sort the target list, and get the */
    /* Substitutions values back out in that order. Since the target list  */
    /* is then sorted in GID order, otlCoverageEnd won't change the order  */
    /* again.                                                              */
    if (rule.repl != NULL) {
        /* No need for this whole block, if subCount === 0. */
        for (p = pInput, r = rule.repl; p != NULL; p = p->nextCl, r = r->nextCl) {
            /* I require in feat.c that pInput and repl lists have the same length */
            p->nextSeq = r;
            subCount++;
        }
        sortInputList(pInput);
    }

    otl.coverageBegin();
    for (p = pInput; p != NULL; p = p->nextCl)
        otl.coverageAddGlyph(p->gid);

    InputCoverage = otl.coverageEnd(); /* Adjusted later */

    h.setCoverages(backtracks, otl, pBack, nBack);
    h.setCoverages(lookaheads, otl, pLook, nLook);

    /* When parsing the feat file, I enforced that the targ and repl glyph */
    /* or glyph classes be the same length, except in the case of the      */
    /* 'ignore' statement. In the latter case, repl is NULL                */
    if (subCount > 0 && rule.repl != NULL) {
        for (p = pInput; p != NULL; p = p->nextCl) {
            substitutes.push_back(p->nextSeq->gid);
            p->nextSeq = NULL; /* Remove this reference to the repl node from the target node, else      */
                               /* featRecycleNodes will add it to the free list twice, once when freeing */
                               /* the targ nodes, and once when freeing the repl nodes.                  */
        }
    }

    h.maxContext = MAX(h.maxContext, nInput + nLook);

    size = rchain1size(nBack, nLook, subCount);
    if (extension.use) {
        for (auto &bt: backtracks)
            bt += size;
        for (auto &la: lookaheads)
            la += size;
        h.offset.extension += size + otl.getCoverageSize();
        /* h->offset.subtable already incr in fillExtension() */
    } else {
        h.offset.subtable += size;
    }
}

void GSUB::ReverseSubst::fill(GSUB &h, SubtableInfo &si) {
    for (auto &rule: si.rules) {
        h.AddSubtable(std::make_unique<ReverseSubst>(h, si, rule));
        check_overflow(h.g, "lookup subtable", h.offset.subtable, "reverse chain contextual substitution");
    }
}

void GSUB::ReverseSubst::write(GSUB *h) {
    LOffset adjustment = 0; /* (Linux compiler complains) */
    bool isExt = extension.use;

    if (!isExt)
        adjustment = (h->offset.subtable - offset);

    OUT2(subformat());

    if (!isExt)
        InputCoverage += adjustment;

    OUT2((uint16_t)InputCoverage);

    OUT2((uint16_t)backtracks.size());

    if (h->g->convertFlags & HOT_ID2_CHAIN_CONTXT3) {
        /* do it per OpenType spec 1.4 and earlier,as In Design 2.0 and earlier requires. */
        for (auto &bt: backtracks) {
            if (!isExt)
                bt += adjustment;
            check_overflow(h->g, "backtrack coverage table", bt, "reverse chain contextual substitution");
            OUT2((uint16_t)bt);
        }
    } else {
        /* do it per OpenType spec 1.5 */
        for (auto ri = backtracks.rbegin(); ri != backtracks.rend(); ri++) {
            if (!isExt)
                *ri += adjustment;
            check_overflow(h->g, "backtrack coverage table", *ri, "reverse chain contextual substitution");
            OUT2((uint16_t)*ri);
        }
    }

    OUT2((uint16_t)lookaheads.size());
    for (auto &la: lookaheads) {
        if (!isExt)
            la += adjustment;
        check_overflow(h->g, "lookahead coverage table", la, "reverse chain contextual substitution");
        OUT2((uint16_t)la);
    }

    OUT2((uint16_t)substitutes.size());
    for (auto g: substitutes) 
        OUT2(g);

    if (isExt)
        extension.otl->coverageWrite();
}

/* ------------------------ Extension Substitution ------------------------- */

/* Fill extension substitution subtable */

void GSUB::fillExtensionSubst(uint32_t ExtensionLookupType, ExtensionSubstFormat1 &tbl) {
    tbl.SubstFormat = 1;
    tbl.ExtensionLookupType = ExtensionLookupType;
    tbl.ExtensionOffset = offset.extension; /* Adjusted later */

    offset.subtable += tbl.size();
}

void GSUB::writeExtension(Subtable &sub) {
    auto &tbl = sub.extension.tbl;
    GSUB *h = this;

    /* Adjust offset */
    tbl.ExtensionOffset += offset.extensionSection - sub.offset;

    DF(1, (stderr, "  GSUB Extension: fmt=%1d, lkpType=%2d, offset=%08ux\n",
           tbl.SubstFormat, tbl.ExtensionLookupType, tbl.ExtensionOffset));

    OUT2(tbl.SubstFormat);
    OUT2(tbl.ExtensionLookupType);
    OUT4(tbl.ExtensionOffset);
}