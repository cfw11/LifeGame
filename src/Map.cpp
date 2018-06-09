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

Map::~Map()
{
    for(int i = 0; i < this->mHeight + 2; ++ i)
    {
        delete[] this->pCellMap[i];
    }
    delete[] this->pCellMap;
}
