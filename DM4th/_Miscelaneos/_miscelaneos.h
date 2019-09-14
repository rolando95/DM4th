#ifdef _WIN32
    #include <windows.h>

    void sleep(double seconds)
    {
        Sleep(seconds*1000);
    }
#else
    #include <unistd.h>

    void sleep(double seconds)
    {
        usleep(seconds * 1000 * 1000); // takes microseconds
    }
#endif