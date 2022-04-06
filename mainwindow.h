#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mine.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void openNextField(int x, int y);
    void restartGame();
    void gameOver();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::vector<std::vector<Mine*>> board;

private slots:
    void on_actionRestart_triggered();

private:
    Ui::MainWindow *ui;
    QWidget *boardWidget;
    int totalMines = 0;

    void setNeighboars(const unsigned int rows, const unsigned int cols);
    void newBoard();
    void cleanBoard();
    void initBoardWidget();

};
#endif // MAINWINDOW_H
