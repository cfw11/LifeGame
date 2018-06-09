#ifndef MAP_H
#define MAP_H
#include "Cell.h"

class Map
{
    public:
        Map(int height, int width);
        virtual ~Map();
        int getHeight();
        int getWidth();
        void initCellStatus(int **initCellMap);
        Cell getCell(int row, int col);
        void iterate(int times);

    protected:

    private:
        int mHeight;
        int mWidth;
        Cell **pCellMap;
};

#endif // MAP_H
