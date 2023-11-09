/* Copyright 2021 Adobe Systems Incorporated (http://www.adobe.com/). All Rights Reserved.
 * This software is licensed as OpenSource, under the Apache License, Version 2.0.
 * This license is available at: http://opensource.org/licenses/Apache-2.0.
 */

#ifndef ADDFEATURES_HOTCONV_FEATCTX_H_
#define ADDFEATURES_HOTCONV_FEATCTX_H_

#include <algorithm>
#include <cassert>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>

#include "FeatParser.h"
#include "hotmap.h"

// Debugging message support
#if HOT_DEBUG
inline int DF_LEVEL(hotCtx g) {
    if (g->font.debug & HOT_DB_FEAT_2)
        return 2;
    else if (g->font.debug & HOT_DB_FEAT_1)
        return 1;
    else
        return 0;
}
#define DF(L, p)             \
    do {                     \
        if (DF_LEVEL(g) >= L) { \
            fprintf p;       \
        }                    \
    } while (0)
#else
#define DF(L, p)
#endif

/* Preferred to 0 for proper otl sorting. This can't conflict with a valid
   tag since tag characters must be in ASCII 32-126. */
#define TAG_UNDEF 0xFFFFFFFF
#define TAG_STAND_ALONE 0x01010101  // Feature, script. language tags used for stand-alone lookups

#define MAX_FEAT_PARAM_NUM 256

/* Labels: Each lookup is identified by a label. There are 2 kinds of hotlib
   lookups:

   1. Named: these are named by the font editor in the feature file. e.g.
      "lookup ZERO {...} ZERO;"
   2. Anonymous: all other lookups. They are automatically generated.

   You can tell which kind of lookup a label refers to by the value of the
   label: use the macros IS_NAMED_LAB() and IS_ANON_LAB().

   Both kinds of lookups can be referred to later on, when sharing them; e.g.
   specified by the font editor explicitly by "lookup ZERO;" or implicitly by
   "language DEU;" where the hotlib includes the default lookups. These lookup
   "references" are stored as the original lookup's label with bit 15 set.
 */

#define FEAT_NAMED_LKP_BEG 0
#define FEAT_NAMED_LKP_END 0x1FFF
#define FEAT_ANON_LKP_BEG (FEAT_NAMED_LKP_END + 1)
#define FEAT_ANON_LKP_END 0x7FFE

#define LAB_UNDEF 0xFFFF

#define REF_LAB (1 << 15)
#define IS_REF_LAB(L) ((L) != LAB_UNDEF && (L)&REF_LAB)
#define IS_NAMED_LAB(L) (((L) & ~REF_LAB) >= FEAT_NAMED_LKP_BEG && \
                         ((L) & ~REF_LAB) <= FEAT_NAMED_LKP_END)
#define IS_ANON_LAB(L) (((L) & ~REF_LAB) >= FEAT_ANON_LKP_BEG && \
                        ((L) & ~REF_LAB) <= FEAT_ANON_LKP_END)

// number of possible entries in list of Unicode blocks
#define kLenUnicodeList 128
// number of possible entries in list of code page numbers
#define kLenCodePageList 64

typedef uint16_t Label;

struct MetricsInfo {
    MetricsInfo() {}
    MetricsInfo(const MetricsInfo &o) : metrics(o.metrics) {}
    MetricsInfo(MetricsInfo &&o) : metrics(std::move(o.metrics)) {}
    MetricsInfo & operator=(const MetricsInfo &o) {
        metrics = o.metrics;
        return *this;
    }
    void reset() { metrics.clear(); }
    std::vector<int16_t> metrics;
};

struct AnchorMarkInfo {
    bool operator < (const AnchorMarkInfo &rhs) const {
        if (componentIndex != rhs.componentIndex)
            return componentIndex < rhs.componentIndex;
        if (markClassIndex != rhs.markClassIndex)
            return markClassIndex < rhs.markClassIndex;
        if (format != rhs.format)
            return format < rhs.format;
        if (x != rhs.x)
            return x < rhs.x;
        if (y != rhs.y)
            return y < rhs.y;
        if (format == 2 && contourpoint != rhs.contourpoint)
            return contourpoint < rhs.contourpoint;
        return false;
    }
    bool operator == (const AnchorMarkInfo &rhs) const {
        return componentIndex == rhs.componentIndex &&
               markClassIndex == rhs.markClassIndex &&
               format == rhs.format &&
               x == rhs.x && y == rhs.y &&
               (format != 2 || contourpoint == rhs.contourpoint);
    }
    void reset() {
        format = 0;
        markClassIndex = componentIndex = 0;
        x = y = 0;
        contourpoint = 0;
        markClassName.clear();
    }
    uint32_t format {0};
    int32_t markClassIndex {0};
    int32_t componentIndex {0};
    int16_t x {0};
    int16_t y {0};
    uint16_t contourpoint {0};
    std::string markClassName;
};

class FeatCtx;

struct GPat {
    struct GlyphRec {
        explicit GlyphRec(GID g) : gid(g) {}
        GlyphRec(const GlyphRec &gr) : gid(gr.gid),
                     markClassAnchorInfo(gr.markClassAnchorInfo) {}
        GlyphRec(GlyphRec &&gr) : gid(gr.gid),
                     markClassAnchorInfo(std::move(gr.markClassAnchorInfo)) {}
        GlyphRec &operator=(const GlyphRec &o) {
            gid = o.gid;
            markClassAnchorInfo = o.markClassAnchorInfo;
            return *this;
        }
        operator GID() const { return gid; }
        bool operator<(const GlyphRec &gr) const { return gid < gr.gid; }
        bool operator==(const GlyphRec &gr) const { return gid == gr.gid; }
        bool operator==(GID g) const { return g == gid; }
        GID gid {GID_UNDEF};
        AnchorMarkInfo markClassAnchorInfo;
    };
    struct ClassRec {
        ClassRec() : marked(false), gclass(false), backtrack(false), input(false),
                     lookahead(false), basenode(false), marknode(false),
                     used_mark_class(false) {}
        explicit ClassRec(GID gid) : ClassRec() { glyphs.emplace_back(gid); }
        ClassRec(const ClassRec &o) : glyphs(o.glyphs), lookupLabels(o.lookupLabels),
                                      metricsInfo(o.metricsInfo),
                                      markClassName(o.markClassName),
                                      marked(o.marked), gclass(o.gclass),
                                      backtrack(o.backtrack), input(o.input),
                                      lookahead(o.lookahead), basenode(o.basenode),
                                      marknode(o.marknode),
                                      used_mark_class(o.used_mark_class) {}
        ClassRec(ClassRec &&o) : glyphs(std::move(o.glyphs)),
                                 lookupLabels(std::move(o.lookupLabels)),
                                 metricsInfo(std::move(o.metricsInfo)),
                                 markClassName(std::move(o.markClassName)),
                                 marked(o.marked), gclass(o.gclass), backtrack(o.backtrack),
                                 input(o.input), lookahead(o.lookahead), basenode(o.basenode),
                                 marknode(o.marknode), used_mark_class(o.used_mark_class) {}
        ClassRec & operator=(const ClassRec &other) {
            glyphs = other.glyphs;
            lookupLabels = other.lookupLabels;
            metricsInfo = other.metricsInfo;
            markClassName = other.markClassName;
            marked = other.marked;
            gclass = other.gclass;
            backtrack = other.backtrack;
            input = other.input;
            lookahead = other.lookahead;
            basenode = other.basenode;
            marknode = other.marknode;
            used_mark_class = other.used_mark_class;
            return *this;
        }
        bool operator==(const ClassRec &rhs) const { return glyphs == rhs.glyphs; }
        void reset() {
            glyphs.clear();
            lookupLabels.clear();
            metricsInfo.reset();
            markClassName.clear();
            marked = gclass = backtrack = input = false;
            lookahead = basenode = marknode = used_mark_class = false;
        }
        bool glyphInClass(GID gid) const {
            return std::find(glyphs.begin(), glyphs.end(), gid) != glyphs.end();
        }
        bool is_glyph() const { return glyphs.size() == 1 && !gclass; }
        bool is_multi_class() const { return glyphs.size() > 1; }
        bool is_class() const { return is_multi_class() || gclass; }
        bool has_lookups() const { return lookupLabels.size() > 0; }
        int classSize() const { return glyphs.size(); }
        void addGlyph(GID gid) { glyphs.emplace_back(gid); }
        void sort() { std::sort(glyphs.begin(), glyphs.end()); }
        void makeUnique(hotCtx g, bool report = false);
        void concat(const ClassRec &other) {
            glyphs.insert(glyphs.end(), other.glyphs.begin(), other.glyphs.end());
        }
        std::vector<GlyphRec> glyphs;
        std::vector<int> lookupLabels;
        MetricsInfo metricsInfo;
        // XXX would like to get rid of this
        std::string markClassName;
        bool marked : 1;      // Sequence element is marked
        bool gclass : 1;      // Sequence element is glyph class
        bool backtrack : 1;   // Part of a backtrack sub-sequence
        bool input : 1;       // Part of an input sub-sequence
        bool lookahead : 1;   // Part of a lookhead sub-sequence
        bool basenode : 1;    // Sequence element is base glyph in mark attachment lookup
        bool marknode : 1;    // Sequence element is mark glyph in mark attachment lookup
        bool used_mark_class : 1;  // This marked class is used in a pos statement (can't add new glyphs)
    };
    class CrossProductIterator {
     public:
        CrossProductIterator() = delete;
        explicit CrossProductIterator(const std::vector<GPat::ClassRec *> &c) :
                     classes(c), indices(classes.size(), 0) {}
        explicit CrossProductIterator(std::vector<GPat::ClassRec *> &&c) :
                     classes(std::move(c)), indices(classes.size(), 0) {}
        bool next(std::vector<GID> &gids) {
            size_t i;
            assert(classes.size() == indices.size());
            if (!first) {
                for (i = 0; i < classes.size(); i++) {
                    if (++indices[i] < classes[i]->glyphs.size())
                        break;
                    indices[i] = 0;
                }
                if (i == classes.size())
                    return false;
            }
            first = false;
            gids.clear();
            for (i = 0; i < classes.size(); i++)
                gids.push_back(classes[i]->glyphs[indices[i]].gid);
            return true;
        }

     private:
        std::vector<GPat::ClassRec *> classes;
        std::vector<uint16_t> indices;
        bool first {true};
    };

    GPat() : has_marked(false), ignore_clause(false), lookup_node(false),
             enumerate(false) {}
    explicit GPat(GID gid) : GPat() { classes.emplace_back(gid); }
    explicit GPat(const GPat &o) : classes(o.classes),
                                   has_marked(o.has_marked),
                                   ignore_clause(o.ignore_clause),
                                   lookup_node(o.lookup_node),
                                   enumerate(o.enumerate) {}
    GPat & operator=(GPat other) {
        classes = other.classes;
        has_marked = other.has_marked;
        ignore_clause = other.ignore_clause;
        lookup_node = other.lookup_node;
        enumerate = other.enumerate;
        return *this;
    }
    bool is_glyph() const { return classes.size() == 1 && classes[0].is_glyph(); }
    bool is_class() const { return classes.size() == 1 && classes[0].is_class(); }
    bool is_mult_class() const { return classes.size() == 1 && classes[0].is_multi_class(); }
    bool is_unmarked_glyph() const { return is_glyph() && !has_marked; }
    bool is_unmarked_class() const { return is_class() && !has_marked; }
    uint16_t patternLen() const { return classes.size(); }
    void addClass(ClassRec &cr) { classes.push_back(cr); }
    void addClass(ClassRec &&cr) { classes.emplace_back(std::move(cr)); }
    bool glyphInClass(GID gid, uint16_t idx = 0) const {
        assert(idx < classes.size());
        if (idx >= classes.size())
            return false;
        return classes[idx].glyphInClass(gid);
    }
    void sortClass(uint16_t idx = 0) {
        assert(idx < classes.size());
        if (idx >= classes.size())
            return;
        classes[idx].sort();
    }
    void makeClassUnique(hotCtx g, uint16_t idx = 0, bool report = false) {
        assert(idx < classes.size());
        if (idx >= classes.size())
            return;
        classes[idx].makeUnique(g, report);
    }
    int classSize(uint16_t idx = 0) const {
        assert(idx < classes.size());
        if (idx >= classes.size())
            return 0;
        return classes[idx].classSize();
    }
    std::vector<ClassRec> classes;
    bool has_marked : 1;       // Sequence has at least one marked node
    bool ignore_clause : 1;    // Sequence is an ignore clause
    bool lookup_node : 1;      // Pattern uses direct lookup reference
    bool enumerate : 1;        // Class should be enumerated
};

// This should technically be in GSUB but it's easier this way
struct CVParameterFormat {
    CVParameterFormat() {}
    CVParameterFormat(const CVParameterFormat &other) = delete;
    explicit CVParameterFormat(CVParameterFormat &&other) {
        FeatUILabelNameID = other.FeatUILabelNameID;
        FeatUITooltipTextNameID = other.FeatUITooltipTextNameID;
        SampleTextNameID = other.SampleTextNameID;
        NumNamedParameters = other.NumNamedParameters;
        FirstParamUILabelNameID = other.FirstParamUILabelNameID;
        other.FeatUILabelNameID = 0;
        other.FeatUITooltipTextNameID = 0;
        other.SampleTextNameID = 0;
        other.NumNamedParameters = 0;
        other.FirstParamUILabelNameID = 0;
        charValues.swap(other.charValues);
    };
    void swap(CVParameterFormat &other) {
        std::swap(FeatUILabelNameID, other.FeatUILabelNameID);
        std::swap(FeatUITooltipTextNameID, other.FeatUITooltipTextNameID);
        std::swap(SampleTextNameID, other.SampleTextNameID);
        std::swap(NumNamedParameters, other.NumNamedParameters);
        std::swap(FirstParamUILabelNameID, other.FirstParamUILabelNameID);
        charValues.swap(other.charValues);
    }
    void reset() {
        FeatUILabelNameID = 0;
        FeatUITooltipTextNameID = 0;
        SampleTextNameID = 0;
        NumNamedParameters = 0;
        FirstParamUILabelNameID = 0;
        charValues.clear();
    }
    int size() { return 7 * sizeof(uint16_t) + 3 * charValues.size(); }
    uint16_t FeatUILabelNameID {0};
    uint16_t FeatUITooltipTextNameID {0};
    uint16_t SampleTextNameID {0};
    uint16_t NumNamedParameters {0};
    uint16_t FirstParamUILabelNameID {0};
    std::vector<uint32_t> charValues;
};

class FeatVisitor;

class FeatCtx {
    friend class FeatVisitor;

 public:
    FeatCtx() = delete;
    explicit FeatCtx(hotCtx g) : g(g) {}

    void fill();

    void dumpGlyph(GID gid, int ch, bool print);
    void dumpGlyphClass(const GPat::ClassRec &cr, int ch, bool print);
    void dumpPattern(const GPat *pat, int ch, bool print);

    std::string msgPrefix();
    bool validateGPOSChain(GPat *targ, int lookupType);
    Label getNextAnonLabel();
    const GPat::ClassRec &lookupGlyphClass(const std::string &gcname);

    // Utility
    Tag str2tag(const std::string &tagName);

#if HOT_DEBUG
    void tagDump(Tag);
#endif
    static const int kMaxCodePageValue;
    static const int kCodePageUnSet;

 private:
    // Console message hooks
    struct {
        unsigned short numExcept {0};
    } syntax;
    std::string tokenStringBuffer;

    void CTL_CDECL featMsg(int msgType, const char *fmt, ...);
    void CTL_CDECL featMsg(int msgType, FeatVisitor *v,
                           antlr4::Token *t, const char *fmt, ...);
    const char *tokstr();
    void setIDText();
    void reportOldSyntax();

    // State flags
    enum gFlagValues { gNone = 0, seenFeature = 1<<0, seenLangSys = 1<<1,
                       seenGDEFGC = 1<<2, seenIgnoreClassFlag = 1<<3,
                       seenMarkClassFlag = 1<<4,
                       seenNonDFLTScriptLang = 1<<5 };
    unsigned int gFlags {gNone};

    enum fFlagValues { fNone = 0, seenScriptLang = 1<<0,
                       langSysMode = 1<<1 };
    unsigned int fFlags {fNone};

    // Glyphs
    GID mapGName2GID(const char *gname, bool allowNotdef);
    inline GID mapGName2GID(const std::string &gname, bool allowNotdef) {
        return mapGName2GID(gname.c_str(), allowNotdef);
    }
    GID cid2gid(const std::string &cidstr);

    // Glyph Classes
    void sortGlyphClass(GPat *gp, bool unique, bool reportDups, uint16_t idx = 0);
    GPat::ClassRec curGC;
    std::string curGCName;
    std::unordered_map<std::string, GPat::ClassRec> namedGlyphClasses;

    void resetCurrentGC();
    void defineCurrentGC(const std::string &gcname);
    bool openAsCurrentGC(const std::string &gcname);
    void finishCurrentGC();
    void finishCurrentGC(GPat::ClassRec &cr);
    void addGlyphToCurrentGC(GID gid);
    void addGlyphClassToCurrentGC(const GPat::ClassRec &cr, bool init = false);
    void addGlyphClassToCurrentGC(const std::string &gcname);
    void addAlphaRangeToCurrentGC(GID first, GID last,
                                  const char *firstname, const char *p,
                                  char q);
    void addNumRangeToCurrentGC(GID first, GID last, const char *firstname,
                                const char *p1, const char *p2,
                                const char *q1, int numLen);
    void addRangeToCurrentGC(GID first, GID last,
                             const std::string &firstName,
                             const std::string &lastName);
    bool compareGlyphClassCount(int targc, int replc, bool isSubrule);

    // Tag management
    enum TagType { featureTag, scriptTag, languageTag, tableTag };
    typedef std::unordered_set<Tag> TagArray;
    TagArray script, language, feature, table;

    inline bool addTag(TagArray &a, Tag t) {
        if ( a.find(t) == a.end() )
            return false;
        a.emplace(t);
        return true;
    }
    bool tagAssign(Tag tag, enum TagType type, bool checkIfDef);

    // Scripts and languages
    struct LangSys {
        LangSys() = delete;
        LangSys(Tag script, Tag lang) : script(script), lang(lang) {}
        Tag script;
        Tag lang;
        bool operator<(const LangSys &b) const;
        bool operator==(const LangSys &b) const;
    };

    std::map<LangSys, bool> langSysMap;
    bool include_dflt = true, seenOldDFLT = false;

    int startScriptOrLang(TagType type, Tag tag);
    void includeDFLT(bool includeDFLT, int langChange, bool seenOD);
    void addLangSys(Tag script, Tag language, bool checkBeforeFeature,
                    FeatParser::TagContext *langctx = nullptr);
    void registerFeatureLangSys();

    // Features
    struct State {
        Tag script {TAG_UNDEF};
        Tag language {TAG_UNDEF};
        Tag feature {TAG_UNDEF};
        Tag tbl {TAG_UNDEF};  // GSUB_ or GPOS_
        int lkpType {0};     // GSUBsingle, GPOSSingle, etc.
        unsigned int lkpFlag {0};
        unsigned short markSetIndex {0};
        Label label {LAB_UNDEF};
        bool operator==(const State &b) const;
    };
    State curr, prev;
    std::vector<State> DFLTLkps;

#ifdef HOT_DEBUG
    void stateDump(State &st);
#endif
    void startFeature(Tag tag);
    void endFeature();
    void flagExtension(bool isLookup);
    void closeFeatScriptLang(State &st);
    void addFeatureParam(const std::vector<uint16_t> &params);
    void subtableBreak();

    // Lookups
    struct LookupInfo {
        LookupInfo(Tag t, int lt, unsigned int lf, unsigned short msi,
                   Label l, bool ue) : tbl(t), lkpType(lt), lkpFlag(lf),
                                       markSetIndex(msi), label(l),
                                       useExtension(ue) {}
        Tag tbl;          // GSUB_ or GPOS_
        int lkpType;      // GSUBsingle, GPOSSingle, etc.
        unsigned int lkpFlag;
        unsigned short markSetIndex;
        Label label;
        bool useExtension;
    };
    std::vector<LookupInfo> lookup;

    void startLookup(const std::string &name, bool isTopLevel);
    void endLookup();
    uint16_t setLkpFlagAttribute(uint16_t val, unsigned int attr,
                                 uint16_t markAttachClassIndex);
    void setLkpFlag(uint16_t flagVal);
    void callLkp(State &st);
    void useLkp(const std::string &name);

    struct NamedLkp {
        NamedLkp() = delete;
        NamedLkp(const std::string &name, bool tl) : name(name),
                                                     isTopLevel(tl) {}
        std::string name;
        State state;
        bool useExtension {false}, isTopLevel;
    };
    static_assert(FEAT_NAMED_LKP_BEG == 0,
                  "Named label values must start at zero");
    std::vector<NamedLkp> namedLkp;
    Label currNamedLkp {LAB_UNDEF};
    bool endOfNamedLkpOrRef {false};
    Label anonLabelCnt = FEAT_ANON_LKP_BEG;

    NamedLkp *name2NamedLkp(const std::string &lkpName);
    NamedLkp *lab2NamedLkp(Label lab);
    Label getNextNamedLkpLabel(const std::string &name, bool isa);
    Label getLabelIndex(const std::string &name);

    // Tables
    uint16_t featNameID;
    bool sawSTAT {false};
    bool sawFeatNames {false};
    struct STAT {
        uint16_t flags, format, prev;
        std::vector<Tag> axisTags;
        std::vector<Fixed> values;
        Fixed min, max;
    } stat;
    bool axistag_vert {false}, sawBASEvert {false}, sawBASEhoriz {false};
    size_t axistag_count {0};
    antlr4::Token *axistag_token {nullptr};
    FeatVisitor *axistag_visitor {nullptr};
    void (FeatCtx::*addNameFn)(long platformId, long platspecId,
                               long languageId, const std::string &str);

    void startTable(Tag tag);
    void setGDEFGlyphClassDef(GPat::ClassRec &simple, GPat::ClassRec &ligature,
                              GPat::ClassRec &mark, GPat::ClassRec &component);
    void createDefaultGDEFClasses();
    void setFontRev(const std::string &rev);
    void addNameString(long platformId, long platspecId,
                       long languageId, long nameId,
                       const std::string &str);
    void addSizeNameString(long platformId, long platspecId,
                           long languageId, const std::string &str);
    void addFeatureNameString(long platformId, long platspecId,
                              long languageId, const std::string &str);
    void addFeatureNameParam();
    void addUserNameString(long platformId, long platspecId,
                           long languageId, const std::string &str);
    void addVendorString(std::string str);

    // Anchors
    struct AnchorDef {
        short x {0};
        short y {0};
        unsigned int contourpoint {0};
        bool hasContour {false};
    };
    std::map<std::string, AnchorDef> anchorDefs;
    std::vector<AnchorMarkInfo> anchorMarkInfo;
    void addAnchorDef(const std::string &name, const AnchorDef &a);
    void addAnchorByName(const std::string &name, int componentIndex);
    void addAnchorByValue(const AnchorDef &a, bool isNull,
                          int componentIndex);
    void addMark(const std::string &name, GPat::ClassRec &cr);

    // Metrics
    std::map<std::string, MetricsInfo> valueDefs;
    void addValueDef(const std::string &name, const MetricsInfo &mi);
    void getValueDef(const std::string &name, MetricsInfo &mi);

    // Substitutions
    void prepRule(Tag newTbl, int newlkpType, GPat *targ, GPat *repl);
    void addGSUB(int lkpType, GPat *targ, GPat *repl);
    bool validateGSUBSingle(GPat::ClassRec &targcr, GPat *repl, bool isSubrule);
    bool validateGSUBSingle(GPat *targ, GPat *repl);
    bool validateGSUBMultiple(GPat::ClassRec &targcr, GPat *repl, bool isSubrule);
    bool validateGSUBMultiple(GPat *targ, GPat *repl);
    bool validateGSUBAlternate(GPat *targ, GPat *repl, bool isSubrule);
    bool validateGSUBLigature(GPat *targ, GPat *repl, bool isSubrule);
    bool validateGSUBReverseChain(GPat *targ, GPat *repl);
    bool validateGSUBChain(GPat *targ, GPat *repl);
    void addSub(GPat *targ, GPat *repl, int lkpType);
    void wrapUpRule();

    // Positions
    void addMarkClass(const std::string &markClassName);
    void addGPOS(int lkpType, GPat *targ);
    void addBaseClass(GPat *targ, const std::string &defaultClassName);
    void addPos(GPat *targ, int type, bool enumerate);

    // CVParameters
    enum { cvUILabelEnum = 1, cvToolTipEnum, cvSampleTextEnum,
           kCVParameterLabelEnum };
    CVParameterFormat cvParameters;
    bool sawCVParams {false};
    void clearCVParameters();
    void addCVNameID(int labelID);
    void addCVParametersCharValue(unsigned long uv);
    void addCVParam();

    // Ranges
    void setUnicodeRange(short unicodeList[kLenUnicodeList]);
    void setCodePageRange(short codePageList[kLenCodePageList]);

    // AALT
    struct AALT {
        State state;
        short useExtension {false};
        struct FeatureRecord {
            Tag feature;
            bool used;
            bool operator==(const FeatureRecord &b) const;
            bool operator==(const Tag &b) const;
        };
        std::vector<FeatureRecord> features;
        struct RuleInfo {
            struct GlyphInfo {
                GlyphInfo(GID g, int16_t a) : rgid(g), aaltIndex(a) {}
                bool operator==(const GlyphInfo &b) const {
                    return aaltIndex == b.aaltIndex;
                }
                bool operator<(const GlyphInfo &b) const {
                    return aaltIndex < b.aaltIndex;
                }
                GID rgid {0};
                int16_t aaltIndex {0};
            };
            explicit RuleInfo(GID gid) : targid(gid) {}
            GID targid;
            std::vector<GlyphInfo> glyphs;
        };
        std::map<GID, RuleInfo> rules;
    } aalt;

    void aaltAddFeatureTag(Tag tag);
    void reportUnusedaaltTags();
    void aaltAddAlternates(GPat::ClassRec &targcr, GPat::ClassRec &replcr);
    void aaltCreate();
    bool aaltCheckRule(int type, GPat *targ, GPat *repl);
    void storeRuleInfo(GPat *targ, GPat *repl);

    hotCtx g;
    FeatVisitor *root_visitor {nullptr}, *current_visitor {nullptr};
};

#endif  // ADDFEATURES_HOTCONV_FEATCTX_H_
