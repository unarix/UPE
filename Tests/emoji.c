#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "en_US.utf8");
    
    const wchar_t martini_emoji = 0x1F378;

    printf("Vallamos a tomar un %lc\n", martini_emoji);

    return 0;
}