#include <iostream>
#include <cassert>
#include <cstdlib>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "Map.h"

using namespace std;

int gHeight = -1, gWidth = -1;
int **gCellMap;
int gIteratorTimes = -1;


void initMapSize(int H, int W)
{
    Map mapObj(H, W);

    gHeight = mapObj.getHeight();
    gWidth = mapObj.getWidth();
}

void initCellStatus(int **initCellMap)
{
    Map mapObj(gHeight, gWidth);
    mapObj.initCellStatus(initCellMap);

    // 外围增加一层作为边界
    gCellMap = new int*[gHeight + 2];
    for(int i = 0; i < gHeight + 2; ++ i)
    {
        gCellMap[i] = new int[gWidth + 2];
    }


    for(int i = 0; i <= gHeight + 1; ++ i)
    {
        for(int j = 0; j <= gWidth + 1; ++ j)
        {
            Cell cellObj = mapObj.getCell(i, j);
            gCellMap[i][j] = (int)cellObj.getCellStatus();
        }
    }
}

bool evolveStatus(bool currentCellStatus, int aroundLiveCells)
{
    Cell cellObj;
    cellObj.setCellStatus(currentCellStatus);

    return cellObj.evolveStatus(aroundLiveCells);
}

void iterate(int times)
{
    Map mapObj(gHeight, gWidth);

    int **cellMap = new int*[gHeight];
    for(int i = 0; i < gHeight; ++ i)
    {
        cellMap[i] = new int[gWidth];
    }

    for(int i = 0; i < gHeight; ++ i)
    {
        for(int j = 0; j < gWidth; ++ j)
        {
            cellMap[i][j] = gCellMap[i + 1][j + 1];
        }
    }

    mapObj.initCellStatus(cellMap);
    mapObj.iterate(times);

    for(int i = 0; i <= gHeight + 1; ++ i)
    {
        for(int j = 0; j <= gWidth + 1; ++ j)
        {
            Cell cellObj = mapObj.getCell(i, j);
            gCellMap[i][j] = (int)cellObj.getCellStatus();
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
//    testShouldReturnAMapWhenInitiateWithWidthAndHeight();
//    testShouldThrowExceptionWhenInitiateWithWidthAndHeightIsIllegal();
//
//    testShouldReturnACellMapWhenInitialteWithInitalCellMap();
//    testShouldThrowExceptionWhenInitialteWithInitalCellMapIllegal();
//
//    testShouldReturnCellEvolveStatusWithFalseWhenGivenCurrentStatusWithTrueAndAroundLiveCellsWithOne();
//    testShouldReturnCellEvolveStatusWithFalseWhenGivenCurrentStatusWithTrueAndAroundLiveCellsWithFour();
//    testShouldReturnCellEvolveStatusWithTrueWhenGivenCurrentStatusWithFalseAndAroundLiveCellsWithThree();
//    testShouldReturnCellEvolveStatusWithTrueWhenGivenCurrentStatusWithTrueAndAroundLiveCellsWithThree();
//    testShouldReturnCellEvolveStatusWithTrueWhenGivenCurrentStatusWithTrueAndAroundLiveCellsWithTwo();
//    testShouldReturnCellEvolveStatusWithFalseWhenGivenCurrentStatusWithFalseAndAroundLiveCellsWithTwo();
//
//    testShouldReturnAFinalCellMapWhenGivenInitialCellMapTwoMultiplyTwoAndIteratorTimesThree();
//    testShouldReturnAFinalCellMapWhenGivenInitialCellMapFourMultiplyFourAndIteratorTimesThree();

    printf("输入地图高度：");
    int height;
    scanf("%d", &height);
    printf("输入地图宽度：");
    int width;
    scanf("%d", &width);

    Map mapObj(height, width);
    srand((unsigned int)time(0));
    int **pInitCellMap = new int*[height];
    for(int i = 0; i < height; ++ i)
    {
        pInitCellMap[i] = new int[width];
        for(int j = 0; j < width; ++ j)
        {
            pInitCellMap[i][j] = rand()%2;
        }
    }

    mapObj.initCellStatus(pInitCellMap);

    for(int i = 0; i < height; ++ i)
    {
        for(int j = 0; j < width; ++ j)
        {
            if(mapObj.getCell(i, j).getCellStatus()) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }

    printf("输入迭代次数：");
    int times;
    scanf("%d", &times);
    system("cls");
    bool flag = false;
    char ch;
    for(int i = 0; i < times; ++ i)
    {
        if(kbhit()) {
            ch = getch();
            if(27 == ch) {
                if(flag) flag = false;
                else flag = true;
            }
        }

        while(flag) {
            if(kbhit()) {
                ch = getch();
                if(27 == ch) {
                    if(flag) flag = false;
                    else flag = true;
                }
            }
        }

        mapObj.iterate(1);
        system("cls");
        for(int i = 0; i < height; ++ i)
        {
            for(int j = 0; j < width; ++ j)
            {
                if(mapObj.getCell(i, j).getCellStatus()) {
                    cout << "*";
                } else {
                    cout << " ";
                }
            }
            cout << endl;
        }
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "PS:按下ESC暂停/继续\n";
        Sleep(300);
    }


    return 0;
}
