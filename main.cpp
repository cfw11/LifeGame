#include <iostream>
#include <cassert>

using namespace std;

int gHeight = -1, gWidth = -1;
int **gCellMap;
int gIteratorTimes = -1;


void initMapSize(int H, int W)
{
    if(H <= 0 || W <= 0) {
        throw string("illegal");
    }

    gHeight = H;
    gWidth = W;
}

void initCellStatus(int **initCellMap)
{
    // 外围增加一层作为边界
    gCellMap = new int*[gHeight + 2];
    for(int i = 0; i < gHeight + 2; ++ i)
    {
        gCellMap[i] = new int[gWidth + 2];
    }

    for(int i = 0; i < gHeight + 2; ++ i)
    {
        gCellMap[i][0] = -1;
        gCellMap[i][gWidth + 1] = -1;
    }
    for(int j = 0; j < gWidth + 2; ++ j)
    {
        gCellMap[0][j] = -1;
        gCellMap[gHeight + 1][j] = -1;
    }

    for(int i = 1; i <= gHeight; ++ i)
    {
        for(int j = 1; j <= gWidth; ++ j)
        {
            gCellMap[i][j] = initCellMap[i][j];
        }
    }
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

void testShouldThrowExceptionWhenInitiateWithWidthAndHeightIsIllegal()
{
    int height = 0;
    string exceptionstring = "";
    int width = 0;
    try{
    initMapSize(height,width);
    }
    catch(string e){
        exceptionstring = e;
    }
    assert(exceptionstring == "illegal");
}

void testShouldReturnACellMapWhenInitialteWithInitalCellMap()
{
    // case 1 2x2
    int initCellMap[2][2] = {1, 0, 1, 0};

    initMapSize(2, 2);
    initCellStatus((int **)initCellMap);

    for(int i = 0; i < 2; ++ i)
    {
        for(int j = 0; j < 2; ++ j)
        {
            assert(gCellMap[i][j] == initCellMap[i][j]);
        }
    }

}


int main()
{

    testShouldReturnAMapWhenInitiateWithWidthAndHeight();
    testShouldThrowExceptionWhenInitiateWithWidthAndHeightIsIllegal();

    testShouldReturnACellMapWhenInitialteWithInitalCellMap();



    return 0;
}
