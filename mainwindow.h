#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGraphicsScene"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    QGraphicsScene scene;
    QPixmap pixelsMap;
    QImage image;
    QGraphicsPixmapItem *graphicsItem;
    ~MainWindow();
    
private slots:
    void on_actionQuit_triggered();

    void on_actionOpen_triggered();

    void on_actionFilter_1_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
