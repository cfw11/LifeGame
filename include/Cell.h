#ifndef CELL_H
#define CELL_H


class Cell
{
    public:
        Cell();
        virtual ~Cell();
        void setCellStatus(bool isAlive);
        bool getCellStatus();
        bool evolveStatus(int aroundLiveCells);

    protected:

    private:
        bool mIsAlive;
};

#endif // CELL_H
