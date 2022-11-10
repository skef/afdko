/* Copyright 2014 Adobe Systems Incorporated (http://www.adobe.com/). All Rights Reserved.
   This software is licensed as OpenSource, under the Apache License, Version 2.0.
   This license is available at: http://opensource.org/licenses/Apache-2.0. */

#include <string.h>

#include "BLND.h"
#include "sfnt_BLND.h"
#include "sfnt.h"

static BLNDTbl *BLND = NULL;
static int loaded = 0;

/* Read Pascal string. Beware, these strings padded to an even boundary. */
static uint8_t *readString(void) {
    uint8_t pad;
    uint8_t length;
    uint8_t *new;

    IN1(length);
    new = sMemNew(length + 1);
    IN_BYTES(length, new);
    new[length] = '\0';

    if (~length & 1)
        IN1(pad); /* Read pad byte */

    return new;
}

/* Read design to weight vector subroutine */
static uint8_t *readD2WVSubr(uint16_t num, uint16_t length) {
    if (num != MAX_UINT16) {
        uint8_t *subr = sMemNew(length);
        IN_BYTES(length, subr);
        return subr;
    } else
        return NULL;
}

void BLNDRead(int32_t start, uint32_t length) {
    int i;
    int j;
    int size;

    if (loaded)
        return;
    BLND = sMemNew(sizeof(BLNDTbl));

    SEEK_ABS(start);

    /* Read header */
    IN1(BLND->version);
    IN1(BLND->flags);
    IN1(BLND->nAxes);
    IN1(BLND->nMasters);
    IN1(BLND->languageId);
    IN1(BLND->iRegular);
    IN1(BLND->nOffsets);

    /* Read offsets */
    BLND->axisOffset = sMemNew(sizeof(BLND->axisOffset[0]) * BLND->nAxes);
    for (i = 0; i < BLND->nAxes; i++)
        IN1(BLND->axisOffset[i]);

    IN1(BLND->masterNameOffset);
    IN1(BLND->styleOffset);
    IN1(BLND->instanceOffset);
    IN1(BLND->instanceNameOffset);

    if (BLND->version > 2)
        IN1(BLND->d2wvOffset);

    /* Read axis information table */
    BLND->axisInfo = sMemNew(sizeof(AxisInfo) * BLND->nAxes);
    for (i = 0; i < BLND->nAxes; i++) {
        AxisInfo *info = &BLND->axisInfo[i];

        SEEK_ABS(BLND->axisOffset[i] + start);

        IN1(info->flags);
        IN1(info->minRange);
        IN1(info->maxRange);

        info->type = readString();
        info->longLabel = readString();
        info->shortLabel = readString();

        if (info->flags & FLAG_MAP) {
            IN1(info->nMaps);

            info->map = sMemNew(sizeof(Map) * info->nMaps);
            for (j = 0; j < info->nMaps; j++) {
                IN1(info->map[j].designCoord);
                IN1(info->map[j].normalizedValue);
            }
        } else
            info->nMaps = 0;
    }

    /* Compute length of master FOND name table by adding string lengths */
    SEEK_ABS(BLND->masterNameOffset + start);
    size = 0;
    for (i = 0; i < BLND->nMasters; i++) {
        uint8_t len;
        IN1(len);
        size += 1 + len + (~len & 1);
        SEEK_REL(len + (~len & 1));
    }

    /* Read master FOND name table */
    BLND->masterNames = sMemNew(size);
    SEEK_ABS(BLND->masterNameOffset + start);
    IN_BYTES(size, BLND->masterNames);

    /* Read style table */
    SEEK_ABS(BLND->styleOffset + start);
    IN1(BLND->nStyles);
    BLND->style = sMemNew(sizeof(SPOT_Style) * BLND->nStyles);
    for (i = 0; i < BLND->nStyles; i++) {
        SPOT_Style *style = &BLND->style[i];

        IN1(style->code);
        IN1(style->flags);
        IN1(style->axis);
        IN1(style->nDeltas);

        style->delta = sMemNew(sizeof(Delta) * style->nDeltas);
        for (j = 0; j < style->nDeltas; j++) {
            IN1(style->delta[j].start);
            IN1(style->delta[j].delta);
        }
    }

    /* Read primary instance table */
    SEEK_ABS(BLND->instanceOffset + start);
    IN1(BLND->nInstances);
    BLND->instance = sMemNew(sizeof(Instance) * BLND->nInstances);
    for (i = 0; i < BLND->nInstances; i++) {
        Instance *instance = &BLND->instance[i];

        instance->coord = sMemNew(sizeof(instance->coord[0]) * BLND->nAxes);
        for (j = 0; j < BLND->nAxes; j++)
            IN1(instance->coord[j]);

        IN1(instance->offset);
        IN1(instance->FONDId);
        IN1(instance->NFNTId);
    }

    /* Read primary instance name table */
    size = length - BLND->instanceNameOffset;
    BLND->instanceNames = sMemNew(size);
    SEEK_ABS(BLND->instanceNameOffset + start);
    IN_BYTES(size, BLND->instanceNames);

    if (BLND->d2wvOffset != 0) {
        /* Read design to weight vector subroutines */
        SEEK_ABS(BLND->d2wvOffset + start);
        IN1(BLND->d2wv.CDVNum);
        IN1(BLND->d2wv.CDVLength);
        IN1(BLND->d2wv.NDVNum);
        IN1(BLND->d2wv.NDVLength);
        IN1(BLND->d2wv.lenBuildCharArray);
        BLND->d2wv.CDVSubr =
            readD2WVSubr(BLND->d2wv.CDVNum, BLND->d2wv.CDVLength);
        BLND->d2wv.NDVSubr =
            readD2WVSubr(BLND->d2wv.NDVNum, BLND->d2wv.NDVLength);
    }

    loaded = 1;
}

static uint8_t *dumpString(uint8_t *p, uint8_t *base, int level) {
    int length = *p;
    DL(2, (OUTPUTBUFF, "[%02x]={%u,<%.*s>}\n", (unsigned)(p - base), length, length, p + 1));
    return p + 1 + length + (~length & 1);
}

/* Dump array of coordinates */
static void dumpCoord(int8_t *name, uint16_t *coord, int level) {
    if (BLND->nAxes == 1)
        DL(2, (OUTPUTBUFF, "%s%hu\n", name, coord[0]));
    else {
        int i;
        DL(2, (OUTPUTBUFF, "%s{", name));
        for (i = 0; i < BLND->nAxes; i++)
            DL(2, (OUTPUTBUFF, "%hu%s", coord[i], (i + 1 == BLND->nAxes) ? "}\n" : ","));
    }
}

/* Dump design to weight vector subroutine */
static void dumpD2WVSubr(int8_t *name, uint8_t *subr, uint16_t length, int level) {
    if (subr != NULL) {
        int i;
        DL(3, (OUTPUTBUFF, "--- %s\n", name));
        if (length < 27)
            for (i = 0; i < length; i++)
                DL(3, (OUTPUTBUFF, "%02x ", subr[i]));
        else {
            for (i = 0; i < 12; i++)
                DL(3, (OUTPUTBUFF, "%02x ", subr[i]));
            DL(3, (OUTPUTBUFF, "... "));
            for (i = length - 12; i < length; i++)
                DL(3, (OUTPUTBUFF, "%02x ", subr[i]));
        }
        DL(3, (OUTPUTBUFF, "\n"));
    }
}

void BLNDDump(int level, int32_t offset) {
    int i;
    int j;
    uint8_t *p;

    DL(1, (OUTPUTBUFF, "### [BLND] (%08lx)\n", offset));

    /* Dump header */
    DLu(2, "version   =", BLND->version);
    DLx(2, "flags     =", BLND->flags);
    DLu(2, "nAxes     =", BLND->nAxes);
    DLu(2, "nMasters  =", BLND->nMasters);
    DLu(2, "languageId=", BLND->languageId);
    DLu(2, "iRegular  =", BLND->iRegular);
    DLu(2, "nOffsets  =", BLND->nOffsets);

    /* Dump offsets */
    DL(2, (OUTPUTBUFF, "--- offsets\n"));
    for (i = 0; i < BLND->nAxes; i++)
        DL(2, (OUTPUTBUFF, "axisOffset[%d]     =%08x\n", i, BLND->axisOffset[i]));

    DLX(2, "masterNameOffset  =", BLND->masterNameOffset);
    DLX(2, "styleOffset       =", BLND->styleOffset);
    DLX(2, "instanceOffset    =", BLND->instanceOffset);
    DLX(2, "instanceNameOffset=", BLND->instanceNameOffset);
    DLX(2, "d2wvOffset        =", BLND->d2wvOffset);

    /* Dump axis information table */
    for (i = 0; i < BLND->nAxes; i++) {
        AxisInfo *info = &BLND->axisInfo[i];

        DL(2, (OUTPUTBUFF, "--- axisInfo[%d]\n", i));
        DLx(2, "flags     =", info->flags);
        DLu(2, "minRange  =", info->minRange);
        DLu(2, "maxRange  =", info->maxRange);
        DLP(2, "type      =", info->type);
        DLP(2, "longLabel =", info->longLabel);
        DLP(2, "shortLabel=", info->shortLabel);

        if (info->flags & FLAG_MAP) {
            /* Dump coordinate maps */
            DLu(2, "nMaps     =", info->nMaps);
            DL(2, (OUTPUTBUFF, "--- map[index]={designCoord,normalizedValue}\n"));
            for (j = 0; j < info->nMaps; j++)
                DL(2, (OUTPUTBUFF, "[%d]={%hu,%1.3f (%08x)} ", j,
                       info->map[j].designCoord,
                       FIXED_ARG(info->map[j].normalizedValue)));
            DL(2, (OUTPUTBUFF, "\n"));
        }
    }

    /* Dump master FOND name table */
    DL(2, (OUTPUTBUFF, "--- masterNames[offset]={length,<name>}\n"));
    p = BLND->masterNames;
    for (i = 0; i < BLND->nMasters; i++)
        p = dumpString(p, BLND->masterNames - BLND->masterNameOffset, level);

    /* Dump style table */
    DL(2, (OUTPUTBUFF, "nStyles=%hu\n", BLND->nStyles));
    for (i = 0; i < BLND->nStyles; i++) {
        SPOT_Style *style = &BLND->style[i];

        DL(2, (OUTPUTBUFF, "--- style[%d]\n", i));
        DLu(2, "code   =", (uint16_t)style->code);
        DL(2, (OUTPUTBUFF, "flags  =%02x\n", style->flags));
        DLu(2, "axis   =", style->axis);
        DLu(2, "nDeltas=", style->nDeltas);

        DL(2, (OUTPUTBUFF, "--- delta[index]={start,delta}\n"));
        for (j = 0; j < style->nDeltas; j++)
            DL(2, (OUTPUTBUFF, "[%d]={%1.3f (%08x),%1.3f (%08x)}\n", j,
                   FIXED_ARG(style->delta[j].start),
                   FIXED_ARG(style->delta[j].delta)));
    }

    /* Dump primary instance table */
    DL(2, (OUTPUTBUFF, "nInstances=%hu\n", BLND->nInstances));
    for (i = 0; i < BLND->nInstances; i++) {
        Instance *instance = &BLND->instance[i];

        DL(2, (OUTPUTBUFF, "--- instance[%d]\n", i));
        dumpCoord("coord =", instance->coord, level);
        DLX(2, "offset=", instance->offset);
        DLu(2, "FONDId=", instance->FONDId);
        DLu(2, "NFNTId=", instance->NFNTId);
    }

    /* Dump instance name table */
    DL(2, (OUTPUTBUFF, "--- instanceNames[offset]={length,name}\n"));
    p = BLND->instanceNames;
    for (i = 0; i < BLND->nInstances + 1; i++)
        p = dumpString(p, BLND->instanceNames - BLND->instanceNameOffset, level);

    if (BLND->d2wvOffset != 0) {
        /* Dump design to weight vector subroutines */
        DL(2, (OUTPUTBUFF, "--- d2wv\n"));
        DLu(2, "CDVNum           =", BLND->d2wv.CDVNum);
        DLu(2, "CDVLength        =", BLND->d2wv.CDVLength);
        DLu(2, "NDVNum           =", BLND->d2wv.NDVNum);
        DLu(2, "NDVLength        =", BLND->d2wv.NDVLength);
        DLu(2, "lenBuildCharArray=", BLND->d2wv.lenBuildCharArray);
        dumpD2WVSubr("CDVSubr", BLND->d2wv.CDVSubr, BLND->d2wv.CDVLength, level);
        dumpD2WVSubr("NDVSubr", BLND->d2wv.NDVSubr, BLND->d2wv.NDVLength, level);
    }
}

void BLNDFree(void) {
    int i;

    if (!loaded)
        return;

    /* Free instance names */
    sMemFree(BLND->instanceNames);

    /* Free primary instance table */
    for (i = 0; i < BLND->nInstances; i++)
        sMemFree(BLND->instance[i].coord);
    sMemFree(BLND->instance);

    /* Free style table */
    for (i = 0; i < BLND->nStyles; i++)
        sMemFree(BLND->style[i].delta);
    sMemFree(BLND->style);

    /* Free master FOND name table */
    sMemFree(BLND->masterNames);

    /* Free axis info table */
    for (i = 0; i < BLND->nAxes; i++) {
        AxisInfo *info = &BLND->axisInfo[i];

        sMemFree(info->type);
        sMemFree(info->longLabel);
        sMemFree(info->shortLabel);

        if (info->nMaps > 2)
            sMemFree(info->map);
    }
    sMemFree(BLND->axisInfo);

    /* Free axis offsets */
    sMemFree(BLND->axisOffset);

    if (BLND->d2wvOffset != 0) {
        if (BLND->d2wv.CDVSubr != NULL)
            sMemFree(BLND->d2wv.CDVSubr);
        if (BLND->d2wv.NDVSubr != NULL)
            sMemFree(BLND->d2wv.NDVSubr);
    }

    sMemFree(BLND);
    BLND = NULL;
    loaded = 0;
}

/* Return BLND->nMasters */
int BLNDGetNMasters(void) {
    if (!loaded) {
        if (sfntReadTable(BLND_))
            return 1; /* Return 1 if no BLND table in font */
    }
    return BLND->nMasters;
}