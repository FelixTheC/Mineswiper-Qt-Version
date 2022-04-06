#ifndef MINE_H
#define MINE_H

#include <QCheckBox>
#include <QMouseEvent>
#include <QLabel>

class Mine : public QLabel
{
    Q_OBJECT

signals:
    void emptyField(int currentX, int currentY);
    void openNeighbors(int currentX, int currentY);
    void gameOver();

public:
    explicit Mine(QWidget *parent = nullptr);
    void setPosition(int x, int y);
    void setBoardIndex(int x, int y);

    QPoint getBoardIndex();

    void setNeighborsWithMines(const unsigned int neighbors);
    bool isAMine();
    void openField();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    bool isOpen = false;
    bool isMine = false;
    unsigned int neighborsWithMines = 0;
    Qt::CheckState state = Qt::CheckState::Unchecked;
    QPoint boardIndex = QPoint(0, 0);

    void updateState();
};

#endif // MINE_H
