/*
 * Copyright (C) 2022 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/strings.h>


#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "util.h"

using android::base::GetProperty;

/*
 * SetProperty does not allow updating read only properties and as a result
 * does not work for our use case. Write "OverrideProperty" to do practically
 * the same thing as "SetProperty" without this restriction.
 */
void OverrideProperty(const char* name, const char* value) {
    size_t valuelen = strlen(value);

    prop_info* pi = (prop_info*)__system_property_find(name);
    if (pi != nullptr) {
        __system_property_update(pi, value, valuelen);
    } else {
        __system_property_add(name, strlen(name), value, valuelen);
    }
}

/*
 * Spoof properties for SafetyNet check
 */
void vendor_load_properties() {
    if (!android::init::IsRecoveryMode()) {
        OverrideProperty("ro.boot.flash.locked", "1");
        OverrideProperty("ro.boot.vbmeta.device_state", "locked");
        OverrideProperty("ro.boot.verifiedbootstate", "green");
        OverrideProperty("ro.boot.veritymode", "enforcing");
        OverrideProperty("ro.boot.warranty_bit", "0");
        OverrideProperty("ro.warranty_bit", "0");
        OverrideProperty("ro.debuggable", "0");
        OverrideProperty("ro.secure", "1");
        OverrideProperty("ro.build.type", "user");
        OverrideProperty("ro.build.keys", "release-keys");
        OverrideProperty("ro.build.tags", "release-keys");
        OverrideProperty("ro.system.build.tags", "release-keys");
        OverrideProperty("ro.vendor.boot.warranty_bit", "0");
        OverrideProperty("ro.vendor.warranty_bit", "0");
        OverrideProperty("vendor.boot.vbmeta.device_state", "locked");
        OverrideProperty("vendor.boot.verifiedbootstate", "green");
        OverrideProperty("ro.product.first_api_level", "32");
    }
}
