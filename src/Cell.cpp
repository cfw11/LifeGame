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

Cell::~Cell()
{
    //dtor
}
