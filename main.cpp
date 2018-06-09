#include <iostream>
#include <cassert>

using namespace std;

int gHeight = -1, gWidth = -1;


void initMapSize(int H, int W)
{
    gHeight = H;
    gWidth = W;
}

void testShouldReturnAMapWhenInitiateWithWidthAndHeight()
{
    int height;
    int width;
    // case 1  1x1
    height = 1;
    width = 1;

    initMapSize(height, width);

    assert(gHeight == height && gWidth == width);

    // case 2 20x20
    height = 20;
    width = 20;

    initMapSize(height, width);

    assert(gHeight == height && gWidth == width);

    // case 3 100x50
    height = 100;
    width = 50;

    initMapSize(height, width);

    assert(gHeight == height && gWidth == width);

    // case 4 50x100
    height = 50;
    width = 100;

    initMapSize(height, width);

    assert(gHeight == height && gWidth == width);
}



int main()
{

    testShouldReturnAMapWhenInitiateWithWidthAndHeight();


    return 0;
}
