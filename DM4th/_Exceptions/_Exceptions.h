#ifdef NDEBUG
    #define DM4thAssert(...) {}
#else
    #include <cassert>
    #if defined __MINGW32__ || defined __MINGW64__
        #define DM4thAssert(expression, ...) if( !(expression) ){ asm("int $3"); assert(expression); }
    #else
        #define DM4thAssert(expression) assert(expression)
    #endif


#endif
namespace DM4th
{
namespace DM4thInternal
{

inline void __DM4thAssert(bool expression)
{
    asm("int $3");
}

}

}