#pragma Once
#ifdef _WIN32
#include <windows.h>
//complained that I wasn't capturing the output. So this is just here for that.
bool test = SetConsoleMode(GetStdHandle(-11),7);
#endif