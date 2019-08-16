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


#ifndef THREADEDCANVAS_H
#define THREADEDCANVAS_H

#include "thread.h"
#include "canvas.h"

namespace display {

    class ThreadedCanvas : public Thread {

        public:

        ThreadedCanvas(Canvas* canvas) : running_(false), canvas_(canvas) {}
        virtual ~ThreadedCanvas() {}

        virtual void start(int rt_priority = 0, uint32_t affinity_mask = 0)
        {
            {
                Mutexlock mLock(&mutex_);
                running_ = true;
            }
            Thread::start(rt_priority, affinity_mask);
        }

        void stop()
        {
            Mutexlock mLock(&mutex_);
            running_ = false;
        }

        virtual void run() = 0;

        protected:

        inline Canvas* canvas() { return canvas_; }
        inline bool running() 
        { 
            Mutexlock mLock(&mutex_);
            return running_; 
        }

        private:

        Mutex mutex_;
        bool running_;
        Canvas* const canvas_;
    };

}
#endif // THEADEDCANVAS_H
