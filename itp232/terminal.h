#ifndef TERMINAL_SETUP
#ifdef _WIN32
#include <windows.h>
//complained that I wasn't capturing the output. So this is just here for that.
bool test = SetConsoleMode(GetStdHandle(-11),7);
#endif
//text styles.
enum TEXT_STYLES{RESET,BOLD,ITALIC,UNDERLINE,UNBOLD=21,UN_ITALIC,UN_UNDERLINE};
//the colors.
enum TEXT_COLORS{RESET_COLOR,
//foreground colors.
BLACK_TXT = 30,RED_TXT,GREEN_TXT,YELLOW_TXT,BLUE_TXT,MAGENTA_TXT,CYAN_TXT,WHITE_TXT, 
//background colors.
BLACK_BG = 40,RED_BG,GREEN_BG,YELLOW_BG,BLUE_BG,MAGENTA_BG,CYAN_BG,WHITE_BG
};
#endif