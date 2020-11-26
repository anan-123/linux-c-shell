#include"headers.h"

void overkill()
{
    for (int i = 1; i <= bjob_count; i++)
    {
        kill(bjob[i].pid, 9);
    }
}