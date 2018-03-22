#ifndef MYCOM_H
#define MYCOM_H

#include <QObject>

class QSerialPort;
class MainWindow;

class MyCOM : public QObject
{
    Q_OBJECT
public:
    explicit MyCOM(QObject *parent = 0);
    ~MyCOM();

signals:
    void serialOpenFalseSignal();

    void serialOpenSuccessSignal();

    void serialReceiveUpdateSignal(QString receiveData);

public slots:
    void serialOpen(QString portName,quint32 baudRate);

    void serialClose();

    void serialReceiveUpdate();

    void serialSend(QByteArray sendData);

private:
    QSerialPort * serialPort;

};

#endif // MYCOM_H
