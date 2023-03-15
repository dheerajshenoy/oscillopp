#include <qt6/QtWidgets/QLabel>
#include <qt6/QtWidgets/QApplication>
#include <qt6/QtWidgets/QPushButton>
#include <qt6/QtWidgets/QDial>
#include <qt6/QtWidgets/QMainWindow>
#include <qt6/QtWidgets/QVBoxLayout>
#include <qt6/QtWidgets/QHBoxLayout>

#include <qt6/QtCharts/QChart>
#include <qt6/QtCharts/QChartView>
#include <qt6/QtCharts/QValueAxis>
#include <qt6/QtCharts/QLineSeries>
#include <qt6/QtCharts/QSplineSeries>

#include <qt6/QtSerialPort/QSerialPort>
#include <qt6/QtSerialPort/QSerialPortInfo>
#include <qt6/QtCore/QDebug>
#include <qt6/QtCore/QString>
#include <qt6/QtCore/QtMath>
#include <qt6/QtCore/QRandomGenerator>

#include "qcustomplot.h"

class Oscillo : public QMainWindow
{
    public:
        Oscillo(QWidget *parent = nullptr);
        ~Oscillo();

    private:
        void SetupUI();
        void SetupChart();
        void SetupSerial();
        template <typename T>
        void DEBUG(T msg);
        void GetBoardInfo();
        void analogRead();

        QWidget *mainWidget = new QWidget();
        QVBoxLayout *mainLayout = new QVBoxLayout();
        QLabel *testLabel = new QLabel("HELLO WORLD");
        QSerialPort *serialPort;
        quint16 vendor_id;
        quint16 product_id;
        QString portName;
        qint64 x_range = 5, y_range = 2;
        QCustomPlot *customPlot = new QCustomPlot();
        int i = 0;

};
