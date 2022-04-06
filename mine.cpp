#include "mine.h"
#include<QDebug>
#include <Qt>
#include <QRandomGenerator>


Mine::Mine(QWidget *parent)
    : QLabel{parent}
{
    this->setMaximumHeight(25);
    this->setMaximumWidth(25);

    this->setGeometry(10, 10, 25, 25);
    this->setText("[ ]");
    this->state = Qt::CheckState::Unchecked;

    quint32 v = QRandomGenerator::global()->bounded(256);
    if (v % 10 == 0)
        isMine = true;
}


void
Mine::updateState()
{
    if(state == Qt::CheckState::Unchecked)
    {
        this->setText("[!]");
        state = Qt::CheckState::Checked;
    }
    else if (state == Qt::CheckState::Checked)
    {
        this->setText("[ ]");
        state = Qt::CheckState::Unchecked;
    }
}

void
Mine::mousePressEvent(QMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton)
    {
        if(!isOpen)
            this->updateState();
    }
    else if (mouseEvent->buttons() == Qt::LeftButton)
    {
        isOpen = true;

        if (isMine)
        {
            this->setText("*");
            emit gameOver();
        }
        else
        {
            if (neighborsWithMines != 0)
                this->setText(QString::number(neighborsWithMines));
            else
            {
                this->setText(" ");
                emit emptyField(boardIndex.x(), boardIndex.y());
            }
        }
    }
}

void
Mine::setPosition(int x, int y)
{
    this->setGeometry(x, y, 25, 25);
}

void
Mine::setNeighborsWithMines(const unsigned int neighbors)
{
    neighborsWithMines = neighbors;
}

bool
Mine::isAMine()
{
    return isMine;
}


void
Mine::setBoardIndex(int x, int y)
{
    boardIndex = QPoint(x, y);
}


void
Mine::openField()
{
    if (isOpen)
        return;

    isOpen = true;

    if (neighborsWithMines == 0)
    {
        this->setText(" ");
        emit emptyField(boardIndex.x(), boardIndex.y());
    }
    else
    {
        this->setText(QString::number(neighborsWithMines));
    }
}

QPoint
Mine::getBoardIndex()
{
    return boardIndex;
}
