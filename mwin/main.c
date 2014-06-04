#include <stdio.h>
#include <stdlib.h>

#include "mwin.h"

int main()
{
    mwin_init();
    while (mwin_step()==1);
    mwin_done();
    return 0;
}
