#include "monitorThread.h"

MonitorThread::MonitorThread(QObject *parent) : QThread(parent)
{

}

MonitorThread::~MonitorThread()
{

}

/**
 *函数介绍：线程start()之后,默认执行run()函数
 *输入参数：无
 *返回值：
 */
void MonitorThread::run()
{
    this->exec();
}
