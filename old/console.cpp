#include "console.h"

#ifdef WIN
    void setTextColor(int value)
    {
        WORD wColor;
        //This handle is needed to get the current background attribute

        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        //csbi is used for wAttributes word

        if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
        {
            //To mask out all but the background attribute, and to add the color
            wColor = (csbi.wAttributes & 0xF0) + (value & 0x0F);
            SetConsoleTextAttribute(hStdOut, wColor);
        }
        return;
    }
#else
    void setTextColor(int value){}
#endif