#
# Copyright (C) 2022 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

BUILD_BROKEN_DUP_RULES := true
DISABLE_ARTIFACT_PATH_REQUIREMENTS := true

DEVICE_PATH := device/google/pantah

# Init
TARGET_INIT_VENDOR_LIB := //$(DEVICE_PATH):libinit_pantah
