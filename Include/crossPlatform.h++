#if !defined( CROSS_PLATFORM_HPP )
#define CROSS_PLATFORM_HPP

    #if defined( _WIN32 ) || defined( WIN32 ) 
        #define OS_Windows
    #else
        #define OS_Linux
    #endif


    #if defined( OS_Windows )
        #include <windows.h>
    #elif defined( OS_Linux )
        #include <time.h>   // for nanosleep
    #else
        #include <unistd.h> // for usleep
    #endif

    //https://stackoverflow.com/questions/13397571/precise-thread-sleep-needed-max-1ms-error/13397866#13397866
    #ifdef OS_Windows
        bool windowsSleep( int microseconds )
        {
            
            HANDLE timerHandle;
            LARGE_INTEGER time;
            if ( !(timerHandle = CreateWaitableTimer( NULL, true, NULL ) ) )
                return false;

            time.QuadPart = -microseconds * 10;
            timeBeginPeriod(1);
            if ( !SetWaitableTimer( timerHandle, &time, 0, NULL, NULL, false ) )
            {
                CloseHandle( timerHandle );
                return false;
            }
            timeEndPeriod(1);

            WaitForSingleObject( timerHandle, INFINITE );
            CloseHandle( timerHandle );

            return true;
        }
    #endif
    
    void sleepFor( long long int microseconds )
    {
        #ifdef OS_Windows
            if ( !windowsSleep( microseconds ) )
                Sleep( microseconds*1000 );
        #elif defined( OS_Linux )
            struct timespec ts;
            ts.tv_sec = microseconds / 1000000;
            ts.tv_nsec = (microseconds % 1000000) * 1000;
            nanosleep(&ts, NULL);
        #else
            usleep(microseconds);
        #endif
    }

#endif /* CROSS_PLATFORM_HPP */