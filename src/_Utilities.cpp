#include "../DM4th/_Utilities/_Utilities.h"
#include "../DM4th/_Number/_Number.h"

namespace DM4th
{

void _handleIstreamSpacesAndNewLines(std::istream &stream)
{
    while(stream.peek()==' ' || stream.peek()=='\n')
    {
        if(stream.peek()==' ') stream>>std::ws;
        if(stream.peek()=='\n') stream.get();
        if(stream.peek()==' ') stream>>std::ws;
    }
}

void _handleStringInQuotes(std::istream &stream, std::string &value)
{
    char delimeter('"');
    _handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()=='"') stream.get();
    else assert(false);
    std::getline(stream, value, delimeter);
    _handleIstreamSpacesAndNewLines(stream);
}

}