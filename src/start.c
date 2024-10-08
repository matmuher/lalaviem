#include "sim.h"
void initLogs() ;

int main(void)
{
    initLogs();
    simInit();
    app();
    simExit();
    return 0;
}
