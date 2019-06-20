



#ifndef THREAD_H
#define THREAD_H

#include <stdint.h>
#include <pthread.h>

namespace display
{
    class Thread{
        public:
        
        Thread();
        virtual ~Thread();

        void waitEnded();
        virtual void start(int rt_prio = 0,
                           uint32_t cpu_affinity = 0);



        virtual void run() = 0;

        private:

        static void *pThreadCallrun(void *tobject);
        
        bool started_;
        pthread_t thread_;
    };

    class Mutex{
        public:

        Mutex() { pthread_mutex_init(&mutex_, NULL); }
        ~Mutex() { pthread_mutex_destroy(&mutex_);  }

        void lock() {pthread_mutex_lock(&mutex_); }
        void unlock() {pthread_mutex_unlock(&mutex_); }

        bool waitOnCondition(pthread_cond_t *condition,
                             long timeout_ms = -1);


        private:

        pthread_mutex_t mutex_;
    };

    class Mutexlock{
        public:
        Mutexlock(Mutex *m) : mutex_(m) { mutex_->lock(); }
        ~Mutexlock() { mutex_->unlock(); }

        private:

        Mutex *const mutex_;
    };
}

#endif // THEAD_H