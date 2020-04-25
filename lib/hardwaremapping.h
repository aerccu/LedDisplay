/*
 * -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: 4; -*-
 * Author        : aerccu
 * Created       : 16.08.19
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HARDWARE_MAPPING_H
#define HARDWARE_MAPPING_H

#ifndef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef uint32_t gpio_bits_t;

struct HardwareMapping
{
    const char* name;
    int max_nr_chains;

    gpio_bits_t clock;
    gpio_bits_t strobe;
    gpio_bits_t out_enable;

    gpio_bits_t a, b, c, d, e;
    gpio_bits_t p0_r1, p0_g1, p0_b1;
    gpio_bits_t p0_r2, p0_g2, p0_b2;
    gpio_bits_t p1_r1, p1_g1, p1_b1;
    gpio_bits_t p1_r2, p1_g2, p1_b2;
    gpio_bits_t p2_r1, p2_g1, p2_b1;
    gpio_bits_t p2_r2, p2_g2, p2_b2;
};

extern struct HardwareMapping hardware_mapping_mat[];

#ifndef __cplusplus
} // extern "C"
#endif

#endif // HARDWARE_MAPPING_H
