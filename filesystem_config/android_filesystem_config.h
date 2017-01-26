/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

/* This file is used to define the properties of the filesystem
** images generated by build tools (eg: mkbootfs) and
** by the device side of adb.
*/

/*
 * Reserve OEM AIDs here, but note that you cannot use a friendly name
 * like "foobar" because their is no mapping support like built in
 * AIDs. However, work in progress attempts to resolve the mess that
 * is android_filesystem_config.h:
 *   * https://android-review.googlesource.com/#/q/topic:fsconfig-2
 *
 * YOU MUST SELECT AIDs THAT ARE WITHIN THE RESERVED SLOTS FOR OEMS
 * defined in system/core/include/private/android_filesystem_config.h
 */
#define AID_PSTORE 5001
#define AID_INTEL_PROP 5002
#define AID_WLAN_PROV 5003

#ifndef AID_TELEMETRY
#warning AID_TELEMETRY not defined, omitting telemetry entries from filesystem_config. The patch: https://android.intel.com/#/c/319973 may be missing."
#endif

static const struct fs_path_config android_device_dirs[] = {
    {	00755, AID_ROOT,   AID_SHELL,	0, "system/vendor/gfx/ufo_byt/bin" },
#ifdef AID_TELEMETRY
    {	00550, AID_ROOT,   AID_TELEMETRY,	0, "system/etc/tm" },
#endif
};

/* Rules for files.
** These rules are applied based on "first match", so they
** should start with the most specific path and work their
** way up to the root. Prefixes ending in * denotes wildcard
** and will allow partial matches.
*/
static const struct fs_path_config android_device_files[] = {
	{ 00755, AID_SYSTEM,	AID_SYSTEM,	CAP_MASK_LONG(CAP_SYS_RAWIO), "system/vendor/bin/intelstorageproxyd" },
	{ 00755, AID_SYSTEM,    AID_SYSTEM,     CAP_MASK_LONG(CAP_SYS_RAWIO), "vendor/bin/intelstorageproxyd" },
	{ 00755, AID_KEYSTORE,  AID_KEYSTORE,   CAP_MASK_LONG(CAP_BLOCK_SUSPEND), "system/bin/keymaster_meid" },
	{ 00755, AID_ROOT,      AID_SHELL,     0, "system/vendor/wifi/aosp/wpa_*" },
	{ 00755, AID_ROOT,      AID_SHELL,     0, "system/vendor/gfx/ufo_byt/bin/*" },
#ifdef AID_TELEMETRY
	{ 00440, AID_ROOT,      AID_TELEMETRY, 0, "system/etc/tm/*" },
#endif
	{ 00755, AID_ROOT,      AID_SHELL,     0, "system/vendor/wifi/brcm/wpa_*" },
	{ 00755, AID_ROOT,      AID_SHELL,     0, "system/vendor/wifi/rtk/wpa_*" },
	{ 00755, AID_SYSTEM,    AID_SYSTEM,     (1ULL << CAP_NET_RAW | 1ULL << CAP_SYS_BOOT), "vendor/bin/esif_ufd" },
	{ 00755, AID_ROOT,     AID_SHELL,     CAP_MASK_LONG(CAP_SYS_NICE), "system/vendor/bin/coreu" },
	{ 00755, AID_ROOT,     AID_SHELL,     CAP_MASK_LONG(CAP_SYS_NICE), "vendor/bin/coreu" },
        { 00755, AID_ROOT,     AID_SHELL,     CAP_MASK_LONG(CAP_SYS_NICE), "system/bin/audioserver" },
};
