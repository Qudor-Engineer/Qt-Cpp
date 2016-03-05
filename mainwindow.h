///**************** include the libraries *********************************************************************///
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTimer>
#include "qcustomplot.h"
#include <math.h>
#include <QFile>
#include <QTextStream>
#include <QString>

///******************* START THE HEADER *********************************************************************///
using namespace std;
namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow   //inherit from "QMainWindow"
{
    Q_OBJECT      //object macro to activate signal and slots

//****************** PUBLIC MEMBERS ***********************************************************************//
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int record = 0;
    int record1 = 0;
    QString rx;
    QString test;
    bool stop = false;
    QButtonGroup *button;

//***************** PUBLIC SLOTS ************************************************************************//
public slots:
    void on_pushButton_2_clicked();
    void readResponse();

//***************** PRIVATE SLOTS **********************************************************************//
private slots:

    void on_pushButton_clicked();

    void plotting();

//**************** SIGNALS ***************************************************************************//
signals:
    void clicked1(bool x);

    void plottingData(QString rxget);

//*************** PRIVATE MEMBERS *******************************************************************//
private:
    Ui::MainWindow *ui;
    QTimer dataTimer, Timer;
    double rxplot;
    int fileData[];
    int j=0;

};
///************** THE END OF HEADER ***************************************************************///
#endif // MAINWINDOW_H
