#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, const char * argv[])
{
    
    sleep(1);
    time_t tm;
    struct tm *t_struct;
    tm = time(NULL);
    printf("%ld",tm);

    t_struct = localtime(&tm);

    printf("%.2d:%.2d:%.2d", t_struct->tm_hour, t_struct->tm_min, t_struct->tm_sec);
    
    return 0;
}