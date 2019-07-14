




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


        void setGPIO(GPIO *io, bool initThread = true);

        void startRefresh();

        void ApplyPmapper(const Pmapper *pmapper);

        bool setPWMBits(uint8_t val);
        uint8_t getPWMBits();

        void setAdjustedLuminance(bool on);
        bool getAdjustedLuminance();

        void setBrightness(uint8_t val);
        uint8_t getBrightness();

        GPIO* getGPIO() { return io_; }

        uint32_t onTimedInputChange(int timeout_ms);

        // frameCanvas : canvas
        FrameCanvas* createFrameCanvas();

        FrameCanvas* swapOnVSync(FrameCanvas* fcan, unsigned framerate_fraction = 1);


        // interface
        virtual int width() const;
        virtual int height() const;
        virtual void fill(uint8_t r, uint8_t g, uint8_t b);
        virtual void setPix(int x, int y, uint8_t r, uint8_t g, uint8_t b);
        virtual void clear();

        
        

        private:
        class UpdateThread;
        friend class UpdateThread;

        void applyNamedPmappers(const char* pmapper_conf, int chain, int parallel);

        Options params_;
        bool luminance_correction_;

        FrameCanvas* active_;

        GPIO* io_;
        Mutex active_frame_sync;

        UpdateThread* update_;
        std::vector<FrameCanvas*> created_frames_;
        internal::PixelDesignatorMap* shared_pmapper_;
    };



    class FrameCanvas : public Canvas {

        public:

        // true on success
        bool setPWMBits(uint8_t val);
        uint8_t pwmbits();

        
        void setLumixCorrect(bool on);
        bool getLumixCorrect() const;

        void setBrightness(uint8_t brightness);
        uint8_t getBrightness();

        // storage & loading (true on success)
        void serialise(const char** data, size_t* len) const;
        bool deserialise(const char *data, size_t len);

        void copyFrom(const FrameCanvas &other);

        // interface
        virtual int width() const;
        virtual int height() const;
        virtual void setPix(int x, int y,
                            uint8_t r,
                            uint8_t g,
                            uint8_t b);

        virtual void fill(uint8_t r,
                          uint8_t g,
                          uint8_t b);

        virtual void clear();

        private:
        friend class RGBMatrix;

        FrameCanvas(internal::FrameBuffer* frame) : frame_(frame) {}
        virtual ~FrameCanvas();
        internal::FrameBuffer* framebuffer() { return frame_; }

        internal::FrameBuffer* const frame_;
    };

    struct RuntimeOptions {
        RuntimeOptions();

        int gpio_slowdown;
        int daemon;
        int invalidate_privileges;
        bool do_gpio_init;
    };

    // parse and update Options Struct
    bool parseOptions(int* argc, char*** argv, 
                        RGBMatrix::Options* default_options,
                        RuntimeOptions* rt_op,
                        bool remove_processed_flags = true);

    // initialising matrix from options
    RGBMatrix* createMatrixFromOptions(const RGBMatrix::Options &options,
                                        const RuntimeOptions &rt_options);

    // matrix creation from parsed flags and from passed flags
    RGBMatrix* createMatrix(int* argc, char*** argv,
                            RGBMatrix::Options* default_ops = NULL,
                            RuntimeOptions* default_rt_opts = NULL,
                            bool remove_processed_flags = true);

    // display options
    void printMatrixOptions(FILE* out, const RGBMatrix::Options* default_ops = NULL,
                            RuntimeOptions* default_rt_ops = NULL,
                            bool remove_processed_flags = true);
}
#endif // LED_DISP