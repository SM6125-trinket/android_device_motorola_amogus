/*
 * Copyright (C) 2026 The PixelOS Project
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

#include <cstddef>
#include <cstdlib>
#include <new>
#include <utils/Looper.h>

namespace {

#ifdef __LP64__
constexpr std::size_t kLegacyLooperSize = 0xe0;
#else
constexpr std::size_t kLegacyLooperSize = 0x70;
#endif

static_assert(sizeof(android::Looper) > kLegacyLooperSize,
              "Expected Android 14 android::Looper to be larger than legacy blob size");

}  // namespace

// Prebuilt sensors.moto.so (Android 11 ABI) allocates kLegacyLooperSize bytes
// before calling Looper::Looper(bool), causing out-of-bounds corruption in
// Android 14 libutils. Ensure Looper allocations have full sizeof(Looper).
__attribute__((visibility("default")))
void* operator new(std::size_t size) {
    if (size == kLegacyLooperSize) {
        size = sizeof(android::Looper);
    }
    if (size == 0) {
        size = 1;
    }
    void* ptr = std::malloc(size);
    if (!ptr) {
        std::abort();
    }
    return ptr;
}
