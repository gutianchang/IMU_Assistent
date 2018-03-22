#ifndef MONITORTHREAD_H
#define MONITORTHREAD_H

#include <QObject>
#include <QThread>

class MonitorThread : public QThread
{
    Q_OBJECT
public:
    explicit MonitorThread(QObject *parent = 0);
    ~MonitorThread();
    void run();

signals:

public slots:
};

#endif // MONITORTHREAD_H
