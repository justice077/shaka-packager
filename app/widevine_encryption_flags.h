// Copyright 2014 Google Inc. All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd
//
// Defines command line flags for widevine_encryption.

#ifndef APP_WIDEVINE_ENCRYPTION_FLAGS_H_
#define APP_WIDEVINE_ENCRYPTION_FLAGS_H_

#include <gflags/gflags.h>

DECLARE_bool(enable_widevine_encryption);
DECLARE_string(key_server_url);
DECLARE_string(content_id);
DECLARE_string(policy);
DECLARE_int32(max_sd_pixels);
DECLARE_string(signer);
DECLARE_string(aes_signing_key);
DECLARE_string(aes_signing_iv);
DECLARE_string(rsa_signing_key_path);
DECLARE_int32(crypto_period_duration);

#endif  // APP_WIDEVINE_ENCRYPTION_FLAGS_H_
