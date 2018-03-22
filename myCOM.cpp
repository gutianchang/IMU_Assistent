#include "myCOM.h"
#include <QDebug>
#include <QSerialPort>
#include "mainwindow.h"
#include <QMessageBox>

MyCOM::MyCOM(QObject *parent) : QObject(parent)
{

}

MyCOM::~MyCOM()
{

}

void MyCOM::serialOpen(QString portName,quint32 baudRate)
{
    serialPort = new QSerialPort();
    serialPort->setPortName(portName);
    if(serialPort->open(QIODevice::ReadWrite))
    {
        serialPort->setBaudRate(baudRate);
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setFlowControl(QSerialPort::NoFlowControl);
        connect(serialPort, SIGNAL(readyRead()), this, SLOT(serialReceiveUpdate()));
        emit(serialOpenSuccessSignal());
    }
    else
    {
        emit(serialOpenFalseSignal());
    }
}

void MyCOM::serialClose()
{
    serialPort->close();
    delete serialPort;
}

void MyCOM::serialReceiveUpdate()
{
    QString receiveData = serialPort->readAll();
    if(!receiveData.isEmpty())
    {
        emit(serialReceiveUpdateSignal(receiveData));
    }
}

void MyCOM::serialSend(QByteArray sendData)
{
    serialPort->write(sendData);
}
