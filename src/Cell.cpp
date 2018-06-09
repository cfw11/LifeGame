#include "Cell.h"

Cell::Cell()
{

}

void Cell::setCellStatus(bool isAlive)
{
    this->mIsAlive = isAlive;
}

bool Cell::getCellStatus()
{
    return this->mIsAlive;
}

bool Cell::evolveStatus(int aroundLiveCells)
{
    bool currentCellStatus = this->mIsAlive;

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

Cell::~Cell()
{
    //dtor
}
