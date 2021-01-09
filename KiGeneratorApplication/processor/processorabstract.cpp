#include "processorabstract.h"

ProcessorAbstract::ProcessorAbstract(const QString& processorName)
    : mProcessorName(processorName)
{
    //    LOG_DEBUG("[%s] Threadid = %s", mServiceName.toStdString().c_str(), QThread::currentThreadId());
    mThread = QSharedPointer<WorkerThread>(new WorkerThread());
    this->moveToThread(mThread.data());
    QObject::connect(mThread.data(), &QThread::finished, this, &ProcessorAbstract::deleteLater);
    mThread->start(QThread::Priority::NormalPriority);
    connect(this, &ProcessorAbstract::startProcess, this, &ProcessorAbstract::onStartProcess, Qt::QueuedConnection);
    connect(this, &ProcessorAbstract::stopProcess, this, &ProcessorAbstract::onStopProcess, Qt::BlockingQueuedConnection);
}

ProcessorAbstract::~ProcessorAbstract()
{
    //    LOG_DEBUG("[%s] Destructor", mProcessorName.toStdString().c_str());
    mThread->quit();
    mThread->wait();
}

QString ProcessorAbstract::getProcessorName() const
{
    return mProcessorName;
}
