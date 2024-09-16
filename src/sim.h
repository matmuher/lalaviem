// [Window]
#define CELL_SIZE 4
#define SIM_X_SIZE 128
#define SIM_Y_SIZE 64

// [Colors]
#define SPRING 0xFF00FF00
#define OLD_SPRING 0xFF002200
#define BRANCH 0xffCD853F

// [Interface]
void simFlush();
void simPutPixel(int x, int y, int argb);
void simPutLength(int x, int y, int length);
void simPutSpring(int x, int y, int argb, int length);
int simGetPixel(int x, int y);
int simGetLength(int x, int y);
int simRand(int from, int to);
int simMakeDarker(int color, int k);
int simMakeBrighter(int color, int k);
int simMixColors(int lhs, int rhs, int lhs_weigth, int rhs_weight);

// [Service]
extern void simInit();
extern void app();
extern void simExit();
