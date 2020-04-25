#include <stdio.h>
#include <time.h>
#include <stdlib.h>
  
void setTimeout(int milliseconds)
{

    int milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;

    int end = milliseconds_since + milliseconds;

    do {
        milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;
    } while (milliseconds_since <= end);
}


int main()
{

    int delay = 120;

    do {
        printf("%d\n", delay);
        setTimeout(1000);
        delay--;

    } while (delay >= 0);

    
    return 0;
}