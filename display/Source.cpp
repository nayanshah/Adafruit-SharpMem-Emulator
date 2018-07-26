#include "NexusClock.h"

tm getCurrentTime()
{
    time_t now = std::time(0);
    tm time;
    localtime_s(&time, &now);
    return time;
}

int main()
{
    auto display_time = getCurrentTime();
    NexusClock* clk  = GetNexusClock(display_time, 1);

    clk->setup();

    for (;;)
    {
        printf("Drawing...\n");
        clk->loop();
    }

    return 0;
}
