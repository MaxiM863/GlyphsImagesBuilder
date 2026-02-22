#include <vector>
#include <fstream>

#include "../GIB/GIB.hpp"

int main(void)
{
    unsigned int startChar = 0;
    unsigned int endChar = 256;

    const char* fontFilename = "C:\\Windows\\Fonts\\arial.ttf";

    GIB::build(fontFilename);    

    return 0;
}