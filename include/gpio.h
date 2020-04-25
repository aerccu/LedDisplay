


#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <vector>

namespace display
{
    class GPIO{
        public:

        GPIO();

        static const uint32_t legitbits;
        
        bool init(int 
                    #if RGB_SLOWDOWN_GPIO
                    slowdown = RGB_SLOWDOWN_GPIO
                    #else slowdown = 1
                    #endif
        );

        uint32_t initOutputs(uint32_t outputs);
        uint32_t getInputs(uint32_t inputs);

        inline void setBits(uint32_t value){
            if (!value) return;
            *gpio_set_bits_ = value;
            for (int i = 0; i < slowdown_; ++i)
            {
                *gpio_set_bits_ = value;
            }
        }

        inline void clearBits(uint32_t value){
            if (!value) return;
            *gpio_clear_bits_ = value;
            for (int i = 0; i < slowdown_; ++i)
            {
                *gpio_clear_bits_ = value;
            }
        }

        inline void writeMaskedbits(uint32_t value, uint32_t mask){
            clearBits(~value & mask);
            setBits(value & mask);
        }

        inline void write(uint32_t value) { writeMaskedbits(value, output_bits_); }
        inline uint16_t read() const { return *gpio_read_bits_ & input_bits_; }


        private:

        volatile uint32_t *gpio_set_bits_;
        volatile uint32_t *gpio_read_bits_;
        volatile uint32_t *gpio_clear_bits_;   

        int slowdown_;

        uint32_t output_bits_;
        uint32_t input_bits_;
        uint32_t reserved_bits_;
    };


    class Pinpulser{
        public:

        static Pinpulser *create(GPIO *io, uint32_t gpio_mask,
                                bool allow_hw_pulsing,
                                const std::vector<int> &wait);

        virtual ~Pinpulser() {}

        virtual void sendPulse(int time) = 0;

        virtual void waitUntillFinished() {}
    };

    uint32_t GetCounterValUS();
}

#endif // GPO_H