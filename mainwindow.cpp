#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFont>
#include <QMessageBox>


const int WIDTH = 25;
const int HEIGHT = 25;
const int START_X = 50;
const int START_Y = 50;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initBoardWidget();
    newBoard();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::setNeighboars(const unsigned int rows, const unsigned int cols)
{
    for (unsigned int i = 0; i < rows; ++i)
    {
        for(unsigned int j = 0; j < cols; ++j)
        {
            Mine *current = board[i][j];
            current->setBoardIndex(i, j);
            unsigned int neighborsWithMines = 0;

            try
            {
                // upper left
                Mine *neighboar = board.at(i + 1).at(j - 1);
                if (neighboar->isAMine()) ++neighborsWithMines;
            }
            catch (...)
            {
            }

            try
            {
                // upper
                Mine *neighboar = board.at(i + 1).at(j);
                if (neighboar->isAMine()) ++neighborsWithMines;
            }
            catch (...)
            {

            }

            try
            {
                // upper right
                Mine *neighboar = board.at(i + 1).at(j + 1);
                if (neighboar->isAMine()) ++neighborsWithMines;
            }
            catch (...)
            {

            }

            try
            {
                // left
                Mine *neighboar = board.at(i).at(j - 1);
                if (neighboar->isAMine()) ++neighborsWithMines;
            }
            catch (...)
            {

            }

            try
            {
                // right
                Mine *neighboar = board.at(i).at(j + 1);
                if (neighboar->isAMine()) ++neighborsWithMines;
            }
            catch (...)
            {

            }

            try
            {
                // down left
                Mine *neighboar = board.at(i - 1).at(j - 1);
                if (neighboar->isAMine()) ++neighborsWithMines;
            }
            catch (...)
            {

            }

            try
            {
                // down
                Mine *neighboar = board.at(i - 1).at(j);
                if (neighboar->isAMine()) ++neighborsWithMines;
            }
            catch (...)
            {

            }

            try
            {
                // down right
                Mine *neighboar = board.at(i - 1).at(j + 1);
                if (neighboar->isAMine()) ++neighborsWithMines;
            }
            catch (...)
            {

            }

            current->setNeighborsWithMines(neighborsWithMines);
        }
    }
}

void
MainWindow::openNextField(int x, int y)
{

    try
    {
        // upper left
        Mine *neighboar = board.at(x + 1).at(y - 1);
        neighboar->openField();
    }
    catch (...)
    {
    }

    try
    {
        // upper
        Mine *neighboar = board.at(x + 1).at(y);
        neighboar->openField();
    }
    catch (...)
    {

    }

    try
    {
        // upper right
        Mine *neighboar = board.at(x + 1).at(y + 1);
        neighboar->openField();
    }
    catch (...)
    {

    }

    try
    {
        // left
        Mine *neighboar = board.at(x).at(y - 1);
        neighboar->openField();
    }
    catch (...)
    {

    }

    try
    {
        // right
        Mine *neighboar = board.at(x).at(y + 1);
        neighboar->openField();
    }
    catch (...)
    {

    }

    try
    {
        // down left
        Mine *neighboar = board.at(x - 1).at(y - 1);
        neighboar->openField();
    }
    catch (...)
    {

    }

    try
    {
        // down
        Mine *neighboar = board.at(x - 1).at(y);
        neighboar->openField();
    }
    catch (...)
    {

    }

    try
    {
        // down right
        Mine *neighboar = board.at(x - 1).at(y + 1);
        neighboar->openField();
    }
    catch (...)
    {

    }
}

void
MainWindow::newBoard()
{
    const unsigned int rows = 15;
    const unsigned int cols = 15;

    const unsigned int endPosRows = (WIDTH * rows) + START_X;
    const unsigned int endPosCols = (HEIGHT * cols) + START_Y;

    board.reserve(rows);

    for (unsigned int i = START_X; i < endPosRows; i+=WIDTH)
    {

        std::vector<Mine*> tmp;
        tmp.reserve(cols);

        for(unsigned int j = START_Y; j < endPosCols; j+=HEIGHT )
        {
            Mine *mine = new Mine(boardWidget);
            totalMines += mine->isAMine();

            mine->setPosition(i, j);
            tmp.push_back(mine);

            connect(mine, &Mine::emptyField, this, &MainWindow::openNextField);
            connect(mine, &Mine::gameOver, this, &MainWindow::gameOver);
        }
        board.push_back(tmp);
    }

    ui->lcdTotalMines->display(QString::number(totalMines));
    setNeighboars(rows, cols);
}

void
MainWindow::cleanBoard()
{
    for (std::vector<Mine *> row : board)
    {
        for (Mine* col : row)
        {
            col->deleteLater();
        }
    }
    board = std::vector<std::vector<Mine*>>();
    totalMines = 0;
}

void
MainWindow::restartGame()
{
    cleanBoard();
    initBoardWidget();
    newBoard();
    boardWidget->show();
}


void
MainWindow::on_actionRestart_triggered()
{
    restartGame();
}

void
MainWindow::initBoardWidget()
{
    auto font = QFont();
    font.setPixelSize(20);

    boardWidget = new QWidget(this);
    boardWidget->setGeometry(20, 80, 731, 451);
    boardWidget->setFont(font);
}

void
MainWindow::gameOver()
{
    boardWidget->setDisabled(true);
    QMessageBox::information(this, "Game Over", "Game Over", QMessageBox::Default);
}

