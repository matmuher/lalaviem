#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "sim.h"

#define FRAME_TICKS 50
#define RAND_MAX 2147483647
#define SEED 52U
#define DEF_R 0
#define DEF_G 40
#define DEF_B 0
#define DEF_A 255

static SDL_Renderer *Renderer = NULL;
static SDL_Window *Window = NULL;
static Uint32 Ticks = 0;

void simInit()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SIM_X_SIZE * CELL_SIZE, SIM_Y_SIZE * CELL_SIZE,
        0, &Window, &Renderer);
    SDL_SetRenderDrawColor(Renderer, DEF_R, DEF_G, DEF_B, DEF_A);
    SDL_RenderClear(Renderer);
    srand(SEED);
    simFlush();
}

void closeLogs();

static void processEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_KEYDOWN &&
        event.key.keysym.sym == SDLK_ESCAPE) {
        closeLogs();
        SDL_DestroyRenderer(Renderer);
        SDL_DestroyWindow(Window);
        SDL_Quit();
        exit(0);
    }    
}

void simExit()
{
    while (1) {processEvents();}
}

typedef struct {
    int color;
    int length;
} TreeInfo;

static TreeInfo buffer1[SIM_Y_SIZE * SIM_X_SIZE] = {0};
static TreeInfo buffer2[SIM_Y_SIZE * SIM_X_SIZE] = {0};
static TreeInfo* writeBuffer = buffer1;
static TreeInfo* readBuffer = buffer2;

static void swapBuffers()
{
    TreeInfo* tmp = writeBuffer;
    writeBuffer = readBuffer;
    readBuffer = tmp;

    memcpy(writeBuffer, readBuffer, sizeof(buffer1));
}

void simFlush()
{
    Uint32 cur_ticks = SDL_GetTicks() - Ticks;
    if (cur_ticks < FRAME_TICKS) {SDL_Delay(FRAME_TICKS - cur_ticks);}
    SDL_RenderPresent(Renderer);
    processEvents();
    swapBuffers();
}

typedef struct
{
    int x;
    int y;
} Point;

static Point mapCoords(int x, int y)
{
    Point point = {0};

    x %= SIM_X_SIZE;
    x = x < 0 ? x + SIM_X_SIZE : x;
    point.x = x;

    y %= SIM_Y_SIZE;
    y = y < 0 ? 0 : y;
    y = (SIM_Y_SIZE - 1) - y;
    point.y = y;

    if (!(x >= 0 && x < SIM_X_SIZE)) {
        printf("x = %d\n", point.x);
        assert(x >= 0 && x < SIM_X_SIZE);
    }

    if (!(y >= 0 && y < SIM_Y_SIZE)) {
        printf("y = %d\n", point.y);
        assert(y >= 0 && y < SIM_Y_SIZE);
    }

    return point;
}

typedef struct
{
    Uint8 a;
    Uint8 r;
    Uint8 g;
    Uint8 b;
} Color;

static Color hexToColor(int argb)
{
    Uint8 a = (argb >> 24) & 0xFF;;
    Uint8 r = (argb >> 16) & 0xFF;
    Uint8 g = (argb >> 8) & 0xFF;
    Uint8 b = argb & 0xFF;

    Color color = {a, r, g, b};
    return color;
}

void simPutPixel(int x, int y, int argb)
{    
    Point point = mapCoords(x, y);
    Color color = hexToColor(argb);

    SDL_SetRenderDrawColor(Renderer,color.r, color.g, color.b, color.a);
 
    SDL_Rect rect;
    rect.x = point.x * CELL_SIZE;
    rect.y = point.y * CELL_SIZE;
    rect.w = CELL_SIZE;
    rect.h = CELL_SIZE;
    SDL_RenderFillRect(Renderer, &rect);
    Ticks = SDL_GetTicks();

    assert(point.x >= 0 && point.x < SIM_X_SIZE);
    assert(point.y >= 0 && point.y < SIM_Y_SIZE);
    writeBuffer[point.y * SIM_X_SIZE + point.x].color = argb;
}

void simPutBranchLength(int x, int y, int branchLength)
{
    Point point = mapCoords(x, y);

    assert(point.x >= 0 && point.x < SIM_X_SIZE);
    assert(point.y >= 0 && point.y < SIM_Y_SIZE);
    writeBuffer[point.y * SIM_X_SIZE + point.x].length = branchLength;
}

void simPutSpring(int x, int y, int argb, int length) {
    simPutBranchLength(x, y, length);
    simPutPixel(x, y, argb);
}

int simGetLength(int user_x, int user_y)
{
    Point point = mapCoords(user_x, user_y);

    assert(point.x >= 0 && point.x < SIM_X_SIZE);
    assert(point.y >= 0 && point.y < SIM_Y_SIZE);
    return readBuffer[point.y * SIM_X_SIZE + point.x].length;
}

int simGetPixel(int x, int y) {

    Point point = mapCoords(x, y);

    assert(point.x >= 0 && point.x < SIM_X_SIZE);
    assert(point.y >= 0 && point.y < SIM_Y_SIZE);
    return readBuffer[point.y * SIM_X_SIZE + point.x].color;
}

static int makeColor(Color color)
{
    int argb = 0;

    argb |= color.a << 24;
    argb |= color.r << 16;
    argb |= color.g << 8;
    argb |= color.b;

    return argb;
}

int simMakeDarker(int argb, int k) {

    if (k <= 0) {
        return argb;
    }

    Color color = hexToColor(argb);

    color.r /= k;
    color.g /= k;
    color.b /= k;

    return makeColor(color);
}

int simMakeBrighter(int argb, int k)
{
    if (k <= 0) {
        return argb;
    }

    Color color = hexToColor(argb);

    color.r *= k;
    color.g *= k;
    color.b *= k;

    return makeColor(color);
}

int simMixColors(int lhs, int rhs, int lhsWeight, int rhsWight)
{
    Color lhsColor = hexToColor(lhs);
    Color rhsColor = hexToColor(rhs);
    float mixRate = ((float) lhsWeight) / (lhsWeight + rhsWight);

    Color mixColor;
    mixColor.a = lhsColor.a;
    mixColor.r = mixRate * lhsColor.r + (1 - mixRate) * rhsColor.r;
    mixColor.g = mixRate * lhsColor.g + (1 - mixRate) * rhsColor.g;
    mixColor.b = mixRate * lhsColor.b + (1 - mixRate) * rhsColor.b;

    return makeColor(mixColor);
}

int simRand(int from, int to)
{
    if (!(to >= from)) {
        printf("%d %d\n", from, to);
        assert(to >= from);
    }
    int diff = to - from + 1;
    return (rand() % diff) + from;
}
