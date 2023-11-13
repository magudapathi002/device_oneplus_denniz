/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <libinit_dalvik_heap.h>
#include <libinit_variant.h>
#include <libinit_utils.h>

#include <sys/stat.h>

#include "vendor_init.h"

static const variant_info_t global_info = {
    .prjname_value = "20831",

    .model = "DN2103",
    .name = "DN2103EEA",
    .build_fingerprint = "OnePlus/DN2103EEA/OP515BL1:11/RP1A.200720.011/1629889893415:user/release-keys",
    .hw = "20831",
};

static const variant_info_t india_info = {
    .prjname_value = "20827",

    .model = "DN2101",
    .name = "DN2101IND",
    .build_fingerprint = "OnePlus/DN2101IND/OP515BL1:11/RP1A.200720.011/1627567766349:user/release-keys",
    .hw = "20827",
};

static const std::vector<variant_info_t> variants = {
    global_info,
    india_info,
};

/* From Magisk@jni/magiskhide/hide_utils.c */
static const char *snet_prop_key[] = {
    "ro.boot.vbmeta.device_state",
    "ro.boot.verifiedbootstate",
    "ro.boot.flash.locked",
    "ro.boot.selinux",
    "ro.boot.veritymode",
    "ro.boot.warranty_bit",
    "ro.warranty_bit",
    "ro.debuggable",
    "ro.secure",
    "ro.build.type",
    "ro.build.tags",
    "ro.build.selinux",
    "sys.oem_unlock_allowed",
    NULL
};

static const char *snet_prop_value[] = {
    "locked",
    "green",
    "1",
    "enforcing",
    "enforcing",
    "0",
    "0",
    "0",
    "1",
    "user",
    "release-keys",
    "1",
    "0",
    NULL
};

static void workaround_snet_properties() {

    // Hide all sensitive props
    for (int i = 0; snet_prop_key[i]; ++i) {
        property_override(snet_prop_key[i], snet_prop_value[i]);
    }

    chmod("/sys/fs/selinux/enforce", 0640);
    chmod("/sys/fs/selinux/policy", 0440);
}

void vendor_load_properties() {
    search_variant(variants);
    set_dalvik_heap();

    // Workaround SafetyNet
    workaround_snet_properties();
}
