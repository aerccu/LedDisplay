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

#ifndef INTERNAL_FRAMEBUFFER_H
#define INTERNAL_FRAMEBUFFER_H

#include <stdint.h>
#include <stdlib.h>

#include "hardwaremapping.h"

namespace display {
    class GPIO;
    class Pinpulser;

    namespace internal {
        class RowAddress;

        struct PixelDesignator {
            PixelDesignator() :
                gpio_word(-1), r_bit(0),
                g_bit(0), b_bit(0), mask(~0) {}
            int gpio_word;
            uint32_t r_bit;
            uint32_t g_bit;
            uint32_t b_bit;
            uint32_t mask;
        };

        class PixelDesignatorMap {
            public:
            PixelDesignatorMap(int width, int height, 
                const PixelDesignator &fill_bits);
            ~PixelDesignatorMap();

            PixelDesignator* get_at(int x, int y);

            const PixelDesignator& get_fillBits(){
                return fill_bits_;
            }

            inline int get_width() const {
                return width_;
            }

            inline int get_height() const {
                return height_;
            }

            private:
            const int width_;
            const int height_;
            const PixelDesignator fill_bits_;
            PixelDesignator* const buffer_;
        };

        class FrameBuffer {
            public:
            FrameBuffer(int rows, int columns, int parallel,
                    int scan_mode, const char* led_sequence,
                    bool inverse_colour, PixelDesignatorMap** mapper);
            ~FrameBuffer();

            static void initialiseHWMapping(const char* hw_name);
            static void initialisePanels(GPIO* io, const char* panel_type, 
                            int columns);
            static void initialiseGPIO(GPIO* io, int rows, int parallel,
                            bool allow_hardware_pulsing,
                            int pwm_lsb_nanoseconds,
                            int row_address_type);

            uint32_t getPWMBits() { return pwm_bits; }
            bool setPWMBits(uint8_t val);
            



            private:
            uint32_t pwm_bits;


                            
            
            
            
        };







    }
}




#endif // INTERNAL_FRAMEBUFFER_H