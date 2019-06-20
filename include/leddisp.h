




#ifndef LED_DISP
#define LED_DISP

#include <stdint.h>
#include <string>
#include <vector>

#include "gpio.h"
#include "canvas.h"
#include "thread.h"
#include "pmapper.h"

namespace display{

    class RGBMatrix;
    class FrameCanvas;

    namespace internal {
        class FrameBuffer;
        class PixelDesignatorMap;
    }



    class RGBMatrix : public Canvas{

        public:

        struct Options{
            
            Options();


            // true : errorless options
            bool validate(std::string *msg) const;

            const char *hw_mapping;

            // rows & cols per panel
            // chain_size : # panels connected
            // pwm_bits : 11
            // lsb_ns : 
            // dither_bits : refresh rate
            // brightness : 1-100
            // scan_mode : 0=progressive | 1=interlaced 
            int rows, cols, chain_size, chains,
                pwm_bits, pwm_lsb_ns, pwm_dither_bits,
                brightness, scan_mode, row_addr_type,
                multiplexing;

            bool disable_hw_pulsing, show_refresh_rate,
                inverse_colours;

            const char* led_rgb_sequence, 
                *pixel_mapper_config;

        };

        // with control over refresher thread
        RGBMatrix(GPIO* io, const Options &options);

        // default ctor
        RGBMatrix(GPIO* io, int rows = 32, int chained_disps = 1,
                int parallel_disps = 1);

        virtual ~RGBMatrix();








    };














}









#endif // LED_DISP