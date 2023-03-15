#include "Oscillo.hpp"
#include "qmath.h"
#include <qt6/QtCore/qmath.h>

template <typename T>
void Oscillo::DEBUG(T msg) { qDebug() << msg; }

Oscillo::Oscillo(QWidget *parent) : QMainWindow(parent)
{
    SetupUI();
    SetupChart();
    SetupSerial();
}

void Oscillo::SetupChart()
{
    customPlot->addGraph();
    customPlot->graph(0)->addData(0, 0);
    customPlot->xAxis->setRange(0, x_range);
    customPlot->yAxis->setRange(0, y_range);
    customPlot->graph(0)->setLineStyle(QCPGraph::LineStyle::lsLine);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void Oscillo::SetupUI()
{
    mainLayout->addWidget(customPlot);
    mainWidget->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);
}

void Oscillo::GetBoardInfo()
{
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        portName = serialPortInfo.portName();
        if(serialPortInfo.hasVendorIdentifier())
            vendor_id = serialPortInfo.vendorIdentifier();
        if(serialPortInfo.hasProductIdentifier())
            product_id = serialPortInfo.productIdentifier();
    }
}

void Oscillo::SetupSerial()
{
    GetBoardInfo();
    serialPort = new QSerialPort();
    serialPort->setPortName(portName);
    serialPort->open(QSerialPort::ReadWrite);
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    connect(serialPort, serialPort->readyRead, this, [this]() { this->analogRead(); });
}

void Oscillo::analogRead()
{
    QByteArray serialData = serialPort->readLine();
    QString voltage = QString::fromStdString(serialData.toStdString());
    qDebug() << voltage;
}

Oscillo::~Oscillo()
{
    if(serialPort->isOpen())
        serialPort->close();
}
