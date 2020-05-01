#include "main.h"

int main(void)
{
    gameMain();

    return 0;
}

double LERP(float start, float stop, float weight) { // for smooth transition
    return start + weight * (stop - start);
}
