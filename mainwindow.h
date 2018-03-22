#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MyCOM;
class MonitorThread;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_PB_OpenCOM_clicked();

    void on_PB_CloseCOM_clicked();

    void on_PB_SendSend_clicked();

    void on_PB_ReceiveClear_clicked();

    void on_PB_SendClear_clicked();

    void serialOpenFalse();

    void serialOpenSuccess();

    void showSerialReceiveData(QString receiveData);


private:
    Ui::MainWindow *ui;
    MyCOM * myCOM;
    MonitorThread * monitorThread;
    //QSerialPort * serialPort;
    quint64 receiveNum = 0;
    quint64 sendNum = 0;

signals:
    void serialOpenSignal(QString portName,quint32 baudRate);

    void serialCloseSignal();

    void serialSendSignal(QByteArray sendData);
};

#endif // MAINWINDOW_H
