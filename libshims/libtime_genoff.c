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

#include <stdint.h>
#include <time.h>

typedef enum {
    TIME_STAMP = 0,
    TIME_MSEC,
    TIME_SECS,
    TIME_JULIAN,
    TIME_20MS_FRAME,
} time_unit_type;

typedef enum {
    TGO_SET = 0,
    TGO_GET,
} time_genoff_opr_type;

typedef struct {
    int base;
    void* ts_val;
    int unit;
    int operation;
} time_genoff_info_type;

/* Minimal QTI libtime_genoff implementation backed by CLOCK_REALTIME. */
__attribute__((visibility("default")))
int time_genoff_operation(time_genoff_info_type* pargs) {
    if (!pargs) {
        return -1;
    }

    if (pargs->operation == TGO_SET) {
        return 0;
    }

    if (pargs->operation != TGO_GET || !pargs->ts_val) {
        return -1;
    }

    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) != 0) {
        return -1;
    }

    switch (pargs->unit) {
        case TIME_MSEC:
            *(uint64_t*)pargs->ts_val =
                    (uint64_t)ts.tv_sec * 1000ULL + (uint64_t)ts.tv_nsec / 1000000ULL;
            return 0;
        case TIME_SECS:
            *(uint64_t*)pargs->ts_val = (uint64_t)ts.tv_sec;
            return 0;
        case TIME_JULIAN:
            return gmtime_r(&ts.tv_sec, (struct tm*)pargs->ts_val) ? 0 : -1;
        default:
            return -1;
    }
}
