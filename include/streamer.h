


#include <stdint.h>
#include <stdlib.h>
#include <string>

namespace display{

    class FrameCanvas;

    class Streamer{
        public:

        virtual ~Streamer() {}

        virtual void rewind() = 0;
        virtual ssize_t read(void* buffer, size_t count) = 0;
        virtual ssize_t append(const void* buffer, size_t count) = 0;
    };

    class DataStreamer : public Streamer {
        public:
        explicit DataStreamer(int f);
        ~DataStreamer();

        virtual void rewind();
        virtual ssize_t read(void* buffer, size_t count);
        virtual ssize_t append(const void* buffer, size_t count);

        private:
        const int f_;
    };

    class MemoryStreamer : public Streamer {
        public:
        virtual void rewind();
        virtual ssize_t read(void* buffer, size_t count);
        virtual ssize_t append(const void* buffer, size_t count);

        private:
        std::string buffer_;
        size_t pos_;

    };

    class StreamWriter{
        public:
        
        StreamWriter(Streamer* io);

        bool stream(const FrameCanvas &fc, uint32_t display_time_us);

        private:
        void injectFileHeader(const FrameCanvas &fc, size_t l);

        bool header_writer_;
        Streamer* const io_;
    };

    class StreamReader{
        public:

        StreamReader(Streamer* io);
        ~StreamReader();

        void rewind();
        bool getNextFrame(FrameCanvas* fc, uint32_t* display_time_us);

        private:
        enum eState{
            STREAM_FROM_ZERO,
            STREAM_READING,
            STREAM_ERROR,
        };

        bool readFileHeader(const FrameCanvas &fc);

        Streamer* io_;
        size_t buffer_size_;
        eState state_;
        char* buffer_;
    };
}