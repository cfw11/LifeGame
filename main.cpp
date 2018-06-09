#include <iostream>
#include <cassert>
#include "Map.h"

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
        gCellMap[i][0] = 0;
        gCellMap[i][gWidth + 1] = 0;
    }
    for(int j = 0; j < gWidth + 2; ++ j)
    {
        gCellMap[0][j] = 0;
        gCellMap[gHeight + 1][j] = 0;
    }

    for(int i = 1; i <= gHeight; ++ i)
    {
        for(int j = 1; j <= gWidth; ++ j)
        {
            if(initCellMap[i - 1][j - 1] != 0 && initCellMap[i - 1][j - 1] != 1) {
                throw string("illegal");
            }
            gCellMap[i][j] = initCellMap[i - 1][j - 1];
        }
    }
}

bool evolveStatus(bool currentCellStatus, int aroundLiveCells)
{
    if(currentCellStatus) {
        if(aroundLiveCells < 2) {
            return false;
        }
        if(aroundLiveCells > 3) {
            return false;
        }
        if(aroundLiveCells == 3) {
            return true;
        }
        if(aroundLiveCells == 2) {
            return currentCellStatus;
        }
    } else {
        if(aroundLiveCells == 3) {
            return true;
        }
    }

    return false;
}

void iterate(int times)
{
    int **countMap = new int*[gHeight + 2];
    for(int i = 0; i < gHeight + 2; ++ i)
    {
        countMap[i] = new int[gWidth + 2];
    }

    if(times < 0) times = 0;

//    for(int i = 1; i <= gHeight; ++ i)
//    {
//        for(int j = 1; j <= gWidth; ++ j)
//        {
//            cout << gCellMap[i][j] << endl;
//        }
//    }

    while(times --) {
        for(int i = 1; i <= gHeight; ++ i)
        {
            for(int j = 1; j <= gWidth; ++ j)
            {
                countMap[i][j] = 0;
                for(int k = i - 1; k <= i + 1; ++ k)
                {
                    countMap[i][j] += gCellMap[k][j - 1];
                    countMap[i][j] += gCellMap[k][j];
                    countMap[i][j] += gCellMap[k][j + 1];
                }
                countMap[i][j] -= gCellMap[i][j];
            }
        }

        for(int i = 1; i <= gHeight; ++ i)
        {
            for(int j = 1; j <= gWidth; ++ j)
            {
                gCellMap[i][j] = evolveStatus(gCellMap[i][j], countMap[i][j]);
            }
        }
    }
}

void testShouldReturnAFinalCellMapWhenGivenInitialCellMapTwoMultiplyTwoAndIteratorTimesThree()
{
    int **pInitCellMap = new int*[2];
    pInitCellMap[0] = new int[2];
    pInitCellMap[1] = new int[2];
    pInitCellMap[0][0] = 0;
    pInitCellMap[0][1] = 1;
    pInitCellMap[1][0] = 1;
    pInitCellMap[1][1] = 0;
    int finalCellMap[2][2] = {0, 0, 0, 0};

    initMapSize(2, 2);
    initCellStatus(pInitCellMap);
    iterate(3);

    for(int i = 1; i <= 2; ++ i)
    {
        for(int j = 1; j <= 2; ++ j)
        {
            assert(gCellMap[i][j] == finalCellMap[i - 1][j - 1]);
        }
    }
}

void testShouldReturnAFinalCellMapWhenGivenInitialCellMapFourMultiplyFourAndIteratorTimesThree()
{
    int **pInitCellMap = new int*[4];
    for(int i = 0; i < 4; ++ i)
    {
        pInitCellMap[i] = new int[4];
    }
    pInitCellMap[0][0] = 0;
    pInitCellMap[0][1] = 1;
    pInitCellMap[0][2] = 0;
    pInitCellMap[0][3] = 1;
    pInitCellMap[1][0] = 1;
    pInitCellMap[1][1] = 0;
    pInitCellMap[1][2] = 1;
    pInitCellMap[1][3] = 0;
    pInitCellMap[2][0] = 1;
    pInitCellMap[2][1] = 1;
    pInitCellMap[2][2] = 0;
    pInitCellMap[2][3] = 0;
    pInitCellMap[3][0] = 1;
    pInitCellMap[3][1] = 1;
    pInitCellMap[3][2] = 1;
    pInitCellMap[3][3] = 0;

    int finalCellMap[4][4] = {0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    initMapSize(4, 4);
    initCellStatus(pInitCellMap);
    iterate(3);

    for(int i = 1; i <= 4; ++ i)
    {
        for(int j = 1; j <= 4; ++ j)
        {
            assert(gCellMap[i][j] == finalCellMap[i - 1][j - 1]);
        }
    }
}

void testShouldReturnCellEvolveStatusWithFalseWhenGivenCurrentStatusWithTrueAndAroundLiveCellsWithOne()
{
    int liveCells;
    bool currentStatus;
    bool res;

    liveCells = 1;
    currentStatus = true;
    res = evolveStatus(currentStatus, liveCells);
    assert(false == res);
}

void testShouldReturnCellEvolveStatusWithFalseWhenGivenCurrentStatusWithTrueAndAroundLiveCellsWithFour()
{
    int liveCells;
    bool currentStatus;
    bool res;

    liveCells = 4;
    currentStatus = true;
    res = evolveStatus(currentStatus, liveCells);
    assert(false == res);
}

void testShouldReturnCellEvolveStatusWithTrueWhenGivenCurrentStatusWithFalseAndAroundLiveCellsWithThree()
{
    int liveCells;
    bool currentStatus;
    bool res;

    liveCells = 3;
    currentStatus = false;
    res = evolveStatus(currentStatus, liveCells);
    assert(true == res);
}

void testShouldReturnCellEvolveStatusWithTrueWhenGivenCurrentStatusWithTrueAndAroundLiveCellsWithThree()
{
    int liveCells;
    bool currentStatus;
    bool res;

    liveCells = 3;
    currentStatus = true;
    res = evolveStatus(currentStatus, liveCells);
    assert(true == res);
}

void testShouldReturnCellEvolveStatusWithTrueWhenGivenCurrentStatusWithTrueAndAroundLiveCellsWithTwo()
{
    int liveCells;
    bool currentStatus;
    bool res;

    liveCells = 2;
    currentStatus = true;
    res = evolveStatus(currentStatus, liveCells);
    assert(true == res);
}

void testShouldReturnCellEvolveStatusWithFalseWhenGivenCurrentStatusWithFalseAndAroundLiveCellsWithTwo()
{
    int liveCells;
    bool currentStatus;
    bool res;

    liveCells = 2;
    currentStatus = false;
    res = evolveStatus(currentStatus, liveCells);
    assert(false == res);
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
    int **pInitCellMap = new int*[2];
    pInitCellMap[0] = new int[2];
    pInitCellMap[1] = new int[2];
    pInitCellMap[0][0] = 0;
    pInitCellMap[0][1] = 1;
    pInitCellMap[1][0] = 1;
    pInitCellMap[1][1] = 0;

    initMapSize(2, 2);
    initCellStatus(pInitCellMap);

    for(int i = 1; i <= 2; ++ i)
    {
        for(int j = 1; j <= 2; ++ j)
        {
            assert(gCellMap[i][j] == pInitCellMap[i - 1][j - 1]);
        }
    }
}

void testShouldThrowExceptionWhenInitialteWithInitalCellMapIllegal()
{
    // case 1 2x2
    int **pInitCellMap = new int*[2];
    pInitCellMap[0] = new int[2];
    pInitCellMap[1] = new int[2];
    pInitCellMap[0][0] = 0;
    pInitCellMap[0][1] = -1;
    pInitCellMap[1][0] = 1;
    pInitCellMap[1][1] = 0;
    string exceptionString = "";

    initMapSize(2, 2);
    try {
        initCellStatus(pInitCellMap);
    } catch(string e) {
        exceptionString = e;
    }

    assert(exceptionString == "illegal");
}


int main()
{
    testShouldReturnAMapWhenInitiateWithWidthAndHeight();
    testShouldThrowExceptionWhenInitiateWithWidthAndHeightIsIllegal();

    testShouldReturnACellMapWhenInitialteWithInitalCellMap();
    testShouldThrowExceptionWhenInitialteWithInitalCellMapIllegal();

    testShouldReturnCellEvolveStatusWithFalseWhenGivenCurrentStatusWithTrueAndAroundLiveCellsWithOne();
    testShouldReturnCellEvolveStatusWithFalseWhenGivenCurrentStatusWithTrueAndAroundLiveCellsWithFour();
    testShouldReturnCellEvolveStatusWithTrueWhenGivenCurrentStatusWithFalseAndAroundLiveCellsWithThree();
    testShouldReturnCellEvolveStatusWithTrueWhenGivenCurrentStatusWithTrueAndAroundLiveCellsWithThree();
    testShouldReturnCellEvolveStatusWithTrueWhenGivenCurrentStatusWithTrueAndAroundLiveCellsWithTwo();
    testShouldReturnCellEvolveStatusWithFalseWhenGivenCurrentStatusWithFalseAndAroundLiveCellsWithTwo();

    testShouldReturnAFinalCellMapWhenGivenInitialCellMapTwoMultiplyTwoAndIteratorTimesThree();
    testShouldReturnAFinalCellMapWhenGivenInitialCellMapFourMultiplyFourAndIteratorTimesThree();



    return 0;
}
