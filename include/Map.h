#ifndef MAP_H
#define MAP_H
#include "Cell.h"

class Map
{
    public:
        Map(int height, int width);
        virtual ~Map();


    protected:

    private:
        int mHeight;
        int mWidth;
        Cell **pCellMap;
};

#endif // MAP_H
