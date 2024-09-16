
constexpr int X_WIDTH = 400;
constexpr int Y_WIDTH = 300;

constexpr int BRANCH_VAL = 255;

void PutPixel(int x, int y, int val);
int GetPixel(int x, int y);

void renderFrame()
{
    for (int y = 0; y < X_WIDTH; ++y) {
        for (int x = 0; x < X_WIDTH; ++x) {
            int output = 0;
            
            int curVal = GetPixel(x, y);

            if (curVal == BRANCH_VAL) {

                PutPixel(x + 1, y + 1, BRANCH_VAL);
                PutPixel(x - 1, y - 1, BRANCH_VAL);
                PutPixel(x, y, BRANCH_VAL);
            }
        }
    }
}