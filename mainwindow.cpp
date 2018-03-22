#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include "myCOM.h"
#include "monitorThread.h"
#include <QMessageBox>
#include <QString>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->PB_CloseCOM->setDisabled(true);
    ui->PB_SendSend->setDisabled(true);
    //在Combox里显示可用串口号和可选波特率
    QStringList infoList,baudrateList;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        infoList<<info.portName();
    }
    if(infoList.isEmpty()==true)
    {
        infoList<<"Unavailable";
    }
    ui->CBB_COM->addItems(infoList);
    baudrateList<<"1200"<<"4800"<<"9600"<<"57600"<<"115200";
    ui->CBB_Baudrate->addItems(baudrateList);

    myCOM = new MyCOM();
    monitorThread = new MonitorThread();
    myCOM->moveToThread(monitorThread);
    monitorThread->start();
    //monitorThread->start();

    connect(this,SIGNAL(serialOpenSignal(QString,quint32)),
            myCOM,SLOT(serialOpen(QString,quint32)));
    connect(myCOM,SIGNAL(serialOpenFalseSignal()),
            this,SLOT(serialOpenFalse()));
    connect(myCOM,SIGNAL(serialOpenSuccessSignal()),
            this,SLOT(serialOpenSuccess()));
    connect(this,SIGNAL(serialCloseSignal()),
            myCOM,SLOT(serialClose()));
    connect(myCOM,SIGNAL(serialReceiveUpdateSignal(QString)),
            this,SLOT(showSerialReceiveData(QString)));
    connect(this,SIGNAL(serialSendSignal(QByteArray)),
            myCOM,SLOT(serialSend(QByteArray)));
}

MainWindow::~MainWindow()
{
    if(monitorThread->isRunning())
    {
        monitorThread->wait();
        monitorThread->exit();
        delete myCOM;
        delete monitorThread;
    }
    delete ui;
}

void MainWindow::on_PB_OpenCOM_clicked()
{
    QString portName = ui->CBB_COM->currentText();
    quint32 baudRate = ui->CBB_Baudrate->currentText().toInt();
    emit(serialOpenSignal(portName,baudRate));
}

void MainWindow::on_PB_CloseCOM_clicked()
{
    emit(serialCloseSignal());
    ui->PB_CloseCOM->setDisabled(true);
    ui->PB_OpenCOM->setEnabled(true);
    ui->PB_SendSend->setDisabled(true);
}

void MainWindow::on_PB_SendSend_clicked()
{
    QString sendDataString = ui->LE_Send->text();
    QByteArray sendData = sendDataString.toLatin1();
    emit(serialSendSignal(sendData));
    sendNum += sendData.length();
}

void MainWindow::on_PB_ReceiveClear_clicked()
{
    ui->TB_Receive->clear();
}

void MainWindow::on_PB_SendClear_clicked()
{
    ui->LE_Send->clear();
}

void MainWindow::serialOpenFalse()
{
    QMessageBox::warning(this, tr("Warning"), tr("COM is occupied"), QMessageBox::Yes);
}

void MainWindow::serialOpenSuccess()
{
    ui->PB_OpenCOM->setDisabled(true);
    ui->PB_CloseCOM->setEnabled(true);
    ui->PB_SendSend->setEnabled(true);
}

void MainWindow::showSerialReceiveData(QString receiveData)
{
    ui->TB_Receive->moveCursor(QTextCursor::End);
    ui->TB_Receive->insertPlainText(receiveData);
    receiveNum += receiveData.length();
    ui->statusBar->showMessage(QString::number(receiveNum,10));
}

