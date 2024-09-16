#include "sim.h"
#include <assert.h>

#define STEPS 400

void app()
{
    simPutSpring(10, 2, SPRING, 3);
    simPutSpring(50, 30, SPRING, 2);
    simPutSpring(100, 10, SPRING, 3);
    simFlush();

    for (int step = 0; step < STEPS; ++step) {
        for (int y = 0; y < SIM_Y_SIZE; ++y)
        for (int x = 0; x < SIM_X_SIZE; ++x) {
            int curValue = simGetPixel(x, y);
            int curLen = simGetLength(x, y);

            if (curValue == SPRING &&  curLen > 0) {
                simPutPixel(x, y, BRANCH);
                int dx = simRand(-1, 1);
                int dy = simRand(1, 1);

                for (int i = 1; i < curLen; ++i) {
                    simPutPixel(x + i * dx, y + i * dy, BRANCH);
                }
                simPutSpring(x + curLen * dx, y + curLen * dy, simMixColors(SPRING, OLD_SPRING, y, SIM_Y_SIZE - y), curLen / 2);

                dx = simRand(-1, 1);
                for (int i = 1; i < curLen; ++i) {
                    simPutPixel(x + i * dx, y + i * dy, BRANCH);
                }
                simPutSpring(x + curLen * dx, y + curLen * dy, SPRING, simRand(1, curLen));
            }
        } 
        simFlush();
    }
}
