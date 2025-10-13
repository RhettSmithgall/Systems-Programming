#include "headers.h"

//COLORS!!!
#define KNRM  "\x27[0m"
#define KRED  "\x27[31m"
#define KGRN  "\x27[32m"
#define KYEL  "\x27[33m"
#define KBLU  "\x27[34m"
#define KMAG  "\x27[35m"
#define KCYN  "\x27[36m"
#define KWHT  "\x27[37m"


void autograph()
{
    printf("This program was created by...                                               \n");
    char text[] = {
        "    ____  __         __  __     _____           _ __  __                ____\n"
        "   / __ \\/ /_  ___  / /_/ /_   / ___/____ ___  (_) /_/ /_  ____ _____ _/ / /\n"
        "  / /_/ / __ \\/ _ \\/ __/ __/   \\__ \\/ __ `__ \\/ / __/ __ \\/ __ `/ __ `/ / / \n"
        " / _, _/ / / /  __/ /_/ /_    ___/ / / / / / / / /_/ / / / /_/ / /_/ / / /  \n"
        "/_/ |_/_/ /_/\\___/\\__/\\__/   /____/_/ /_/ /_/_/\\__/_/ /_/\\__, /\\__,_/_/_/   \n"
        "                                                        /____/            \n"
    };
    const char *colors[] = {KNRM, KRED, KGRN, KYEL, KBLU, KMAG, KCYN, KWHT};
    int num_colors = sizeof(colors) / sizeof(colors[0]);

    for (int i = 0; text[i] != '\0'; i++) {
        printf("%s%c", colors[i % num_colors], text[i]);
    }

    printf("%s", KNRM); // reset to normal at the end
}
