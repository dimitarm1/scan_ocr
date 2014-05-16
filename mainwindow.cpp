#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "QPixmap"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene.addText("Open image to view here");
    ui->graphicsView->setScene(&scene);
    graphicsItem = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    exit(0);
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open image", "~/", "Image files (*.tif *.jpg *.jpeg); All files (*.*)");
    image.load(fileName);
    pixelsMap = QPixmap::fromImage(image);
    graphicsItem = scene.addPixmap(pixelsMap);
}

void MainWindow::on_actionFilter_1_triggered()
{
    unsigned char hist[26];
    //if (graphicsItem) scene.removeItem(graphicsItem);
    scene.clear();
    int w = image.width();
    int h = image.height();
    unsigned int thr = 0, thr2 = 0;

    unsigned char *data = (unsigned char *) image.bits();
    for (int y = 0; y < h; y++){
        thr = 0;
        for (int x = 0; x < w; x++){
            if ((x%50 == 0)&& x<(w-100)) {

                unsigned char max = 0;
                unsigned char min = 255;
                memset(hist, 0, sizeof(hist));
                for (unsigned int z = 0; z<100; z++){
                    hist[data[z*4]/10]++;
                }
                for (unsigned int z = 0; z<26; z++){

                    if (max < hist[z]) max = hist[z];
                    if ((max >1) && hist[z]< (max-1)){
                        if(min> hist[z]) min = hist[z];
                        else {
                            thr = (thr *20 + (z-1) * 100)/20;
                            break;
                            z = 26;
                        }
                    }
                }

            }
            thr2 = thr / 10;
            if (thr2 <50) thr2 = 100;
            if( thr2 > 180) thr2 = 100;
            for (int i = 0; i<4; i++){
                if (i >1){
                    if(*data< thr2) *data = 0;
                    else *data = 255;
                }
                if (i == 1){
                    *data = thr2;
                }
                data++;
            }
        }
    }

    pixelsMap = QPixmap::fromImage(image);
    graphicsItem = scene.addPixmap(pixelsMap);
}
