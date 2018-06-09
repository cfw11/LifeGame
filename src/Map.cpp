#include "Map.h"
#include<string>

Map::Map(int height, int width)
{
    if(height <= 0 || width <= 0) {
        throw std::string("illegal");
    }

    this->mHeight = height;
    this->mWidth = width;

    // 外围增加一层作为边界
    this->pCellMap = new Cell*[this->mHeight + 2];
    for(int i = 0; i < this->mHeight + 2; ++ i)
    {
        this->pCellMap[i] = new Cell[this->mWidth + 2];
    }
}

int Map::getHeight()
{
    return this->mHeight;
}

int Map::getWidth()
{
    return this->mWidth;
}

void Map::initCellStatus(int **initCellMap)
{
    for(int i = 0; i < this->getHeight() + 2; ++ i)
    {
        this->pCellMap[i][0].setCellStatus(false);
        this->pCellMap[i][this->getWidth() + 1].setCellStatus(false);
    }
    for(int j = 0; j < this->getWidth() + 2; ++ j)
    {
        this->pCellMap[0][j].setCellStatus(false);
        this->pCellMap[this->getHeight() + 1][j].setCellStatus(false);
    }

    for(int i = 1; i <= this->getHeight(); ++ i)
    {
        for(int j = 1; j <= this->getWidth(); ++ j)
        {
            if(initCellMap[i - 1][j - 1] != 0 && initCellMap[i - 1][j - 1] != 1) {
                throw std::string("illegal");
            }
            this->pCellMap[i][j].setCellStatus((bool)initCellMap[i - 1][j - 1]);
        }
    }
}

Cell Map::getCell(int row, int col)
{
    return this->pCellMap[row][col];
}

Map::~Map()
{
    for(int i = 0; i < this->mHeight + 2; ++ i)
    {
        delete[] this->pCellMap[i];
    }
    delete[] this->pCellMap;
}
