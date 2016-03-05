///****** include the libraries **********************************************************************///
#include "mainwindow.h"
#include "ui_mainwindow.h"


///*********** STARTING THE CLASS ****************************************************************///
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    MainWindow::plotting();
//****************************** Reasd File *****************************************************************//
    QFile inputFile("Data.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       int i=0;
       while (!in.atEnd())
       {
          QString line = in.readLine();
          fileData[i]=line.toDouble();
          i++;
       }
       inputFile.close();
    }

}


///*************************** START BUTTON ***********************************************************///
void MainWindow::on_pushButton_clicked()
{
    stop= true;
}
///*************************** STOP BUTTON **************************************************************///
void MainWindow::on_pushButton_2_clicked()
{
    stop = false;

}

///*************************** PLOTTING ***************************************************************///
void MainWindow::plotting()
{
//***** set plot parameters *******************************************************************************//
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::yellow)); //set plot line color
    ui->customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->customPlot->xAxis->setAutoTickStep(false);
    ui->customPlot->xAxis->setTickStep(2);
    ui->customPlot->axisRect()->setupFullAxesBox();

//***** set plot background color ************************************************************************//
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0); //set start point
    plotGradient.setFinalStop(0, 350); //set final point
    plotGradient.setColorAt(1, QColor(100, 100, 100)); // set background color
    ui->customPlot->setBackground(plotGradient);

//***** creat connection for plot Axes *************************************************************//
    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));


//***** creat connection for plot founction *******************************************//
    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot();
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(readResponse()));
    dataTimer.start(10); // Interval 0 means to refresh as fast as possible

}

///**************** REAL TIME PLOTTING SLOT ************************************************************///
void MainWindow::readResponse()

{ if(j==500){j=0;}

    double value0 = fileData[j];
    if (stop)
    {j++;
//***** calculate two new data points: *********************************************************************//
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0; //first data point of plot from time
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    { //emit plottingData(rx);
    //  double value0 = rxplot; // convert string data of serial port to Double to be the second data point of plot

//***** add data to lines: *********************************************************************************//
      ui->customPlot->graph(0)->addData(key, value0);
      // remove data of lines that's outside visible range:
      ui->customPlot->graph(0)->removeDataBefore(key-2);
      ui->customPlot->graph(0)->rescaleValueAxis();
      lastPointKey = key;
    }
//***** make key axis range scroll with the data (at a constant range size of 8):******************************//
    ui->customPlot->xAxis->setRange(key+0.25, 2, Qt::AlignRight);
    ui->customPlot->replot();

//***** calculate frames per second: ****************************************************************************//
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
     if (key-lastFpsKey > 2) // average fps over 2 seconds
     { ui->statusBar->showMessage(QString("%1 FPS, Total Data points: %2").arg(frameCount/(key-lastFpsKey), 0, 'f', 0).arg(ui->customPlot->graph(0)->data()->count()), 0 );
      lastFpsKey = key;
      frameCount = 0;
     }
     }

}

///****************** DESTRUCTOR ***********************************************************************************///
MainWindow::~MainWindow()
{
    delete ui;

}
///********************* End of The class **************************************************************************///



