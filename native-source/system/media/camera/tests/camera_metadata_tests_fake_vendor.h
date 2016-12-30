/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Fake vendor extensions for testing
 */

#ifndef TESTING_CAMERA_METADATA_FAKEVENDOR_H
#define TESTING_CAMERA_METADATA_FAKEVENDOR_H

enum vendor_extension_section {
    FAKEVENDOR_SENSOR = VENDOR_SECTION,
    FAKEVENDOR_SENSOR_INFO,
    FAKEVENDOR_COLORCORRECTION,
    FAKEVENDOR_SCALER,
    FAKEVENDOR_SECTION_END
};

const int FAKEVENDOR_SECTION_COUNT = FAKEVENDOR_SECTION_END - VENDOR_SECTION;

enum vendor_extension_section_ranges {
    FAKEVENDOR_SENSOR_START          = FAKEVENDOR_SENSOR << 16,
    FAKEVENDOR_SENSOR_I_START        = FAKEVENDOR_SENSOR_INFO << 16,
    FAKEVENDOR_COLORCORRECTION_START = FAKEVENDOR_COLORCORRECTION << 16,
    FAKEVENDOR_SCALER_START          = FAKEVENDOR_SCALER << 16
};

enum vendor_extension_tags {
    FAKEVENDOR_SENSOR_SUPERMODE = FAKEVENDOR_SENSOR_START,
    FAKEVENDOR_SENSOR_DOUBLE_EXPOSURE,
    FAKEVENDOR_SENSOR_END,

    FAKEVENDOR_SENSOR_AVAILABLE_SUPERMODES = FAKEVENDOR_SENSOR_I_START,
    FAKEVENDOR_SENSOR_I_END,

    FAKEVENDOR_COLORCORRECTION_3DLUT_MODE = FAKEVENDOR_COLORCORRECTION_START,
    FAKEVENDOR_COLORCORRECTION_3DLUT_TABLES,
    FAKEVENDOR_COLORCORRECTION_END,

    FAKEVENDOR_SCALER_DOWNSCALE_MODE = FAKEVENDOR_SCALER_START,
    FAKEVENDOR_SCALER_DOWNSCALE_COEFF,
    FAKEVENDOR_SCALER_END
};

typedef struct vendor_tag_info {
    const char *tag_name;
    uint8_t     tag_type;
} vendor_tag_info_t;

const char *fakevendor_section_names[FAKEVENDOR_SECTION_COUNT] = {
    "com.fakevendor.sensor",
    "com.fakevendor.sensor.info",
    "com.fakevendor.colorCorrection",
    "com.fakevendor.scaler"
};

unsigned int fakevendor_section_bounds[FAKEVENDOR_SECTION_COUNT][2] = {
    { FAKEVENDOR_SENSOR_START,          FAKEVENDOR_SENSOR_END },
    { FAKEVENDOR_SENSOR_I_START,        FAKEVENDOR_SENSOR_I_END },
    { FAKEVENDOR_COLORCORRECTION_START, FAKEVENDOR_COLORCORRECTION_END },
    { FAKEVENDOR_SCALER_START,          FAKEVENDOR_SCALER_END}
};

vendor_tag_info_t fakevendor_sensor[FAKEVENDOR_SENSOR_END -
        FAKEVENDOR_SENSOR_START] = {
    { "superMode",       TYPE_BYTE },
    { "doubleExposure",  TYPE_INT64 }
};

vendor_tag_info_t fakevendor_sensor_info[FAKEVENDOR_SENSOR_I_END -
        FAKEVENDOR_SENSOR_I_START] = {
    { "availableSuperModes",   TYPE_BYTE }
};

vendor_tag_info_t fakevendor_color_correction[FAKEVENDOR_COLORCORRECTION_END -
        FAKEVENDOR_COLORCORRECTION_START] = {
    { "3dLutMode",   TYPE_BYTE },
    { "3dLutTables", TYPE_FLOAT }
};

vendor_tag_info_t fakevendor_scaler[FAKEVENDOR_SCALER_END -
        FAKEVENDOR_SCALER_START] = {
    { "downscaleMode",  TYPE_BYTE },
    { "downscaleCoefficients", TYPE_FLOAT }
};

vendor_tag_info_t *fakevendor_tag_info[FAKEVENDOR_SECTION_COUNT] = {
    fakevendor_sensor,
    fakevendor_sensor_info,
    fakevendor_color_correction,
    fakevendor_scaler
};

const char *get_fakevendor_section_name(const vendor_tag_query_ops_t *v,
        uint32_t tag);
const char *get_fakevendor_tag_name(const vendor_tag_query_ops_t *v,
        uint32_t tag);
int get_fakevendor_tag_type(const vendor_tag_query_ops_t *v,
        uint32_t tag);

static const vendor_tag_query_ops_t fakevendor_query_ops = {
    get_fakevendor_section_name,
    get_fakevendor_tag_name,
    get_fakevendor_tag_type
};

const char *get_fakevendor_section_name(const vendor_tag_query_ops_t *v,
        uint32_t tag) {
    if (v != &fakevendor_query_ops) return NULL;
    int tag_section = (tag >> 16) - VENDOR_SECTION;
    if (tag_section < 0 ||
            tag_section >= FAKEVENDOR_SECTION_COUNT) return NULL;

    return fakevendor_section_names[tag_section];
}

const char *get_fakevendor_tag_name(const vendor_tag_query_ops_t *v,
        uint32_t tag) {
    if (v != &fakevendor_query_ops) return NULL;
    int tag_section = (tag >> 16) - VENDOR_SECTION;
    if (tag_section < 0
            || tag_section >= FAKEVENDOR_SECTION_COUNT
            || tag >= fakevendor_section_bounds[tag_section][1]) return NULL;
    int tag_index = tag & 0xFFFF;
    return fakevendor_tag_info[tag_section][tag_index].tag_name;
}

int get_fakevendor_tag_type(const vendor_tag_query_ops_t *v,
        uint32_t tag) {
    if (v != &fakevendor_query_ops) return -1;
    int tag_section = (tag >> 16) - VENDOR_SECTION;
    if (tag_section < 0
            || tag_section >= FAKEVENDOR_SECTION_COUNT
            || tag >= fakevendor_section_bounds[tag_section][1]) return -1;
    int tag_index = tag & 0xFFFF;
    return fakevendor_tag_info[tag_section][tag_index].tag_type;
}


#endif
