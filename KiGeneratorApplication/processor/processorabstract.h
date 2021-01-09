#ifndef PROCESSORABSTRACT_H
#define PROCESSORABSTRACT_H

#include <QObject>
#include <QSharedPointer>
#include <memory>
#include "workerthread.h"
#include "logger/logger.h"
#include <QTimer>
#include <QVector>
#include <QSharedPointer>


/**
     * @brief ProcessorAbstract
     * @param processorName
     * abstract class for all processor
     */
class ProcessorAbstract: public QObject
{
        Q_OBJECT
    public:


        ProcessorAbstract(const QString& processorName);
        virtual ~ProcessorAbstract();
        QString getProcessorName() const;


    signals:


        /**
         * @brief startProcess: this signal connected to onStartProcess() then we can call onStartProcess()
         * from another thread
         */
        void startProcess();
        /**
         * @brief stopProcess: this signal connected to onStopProcess() then we can call onStopProcess()
         * from another thread
         */
        void stopProcess();
    public slots:

        /**
         * @brief onStartProcess
         * start this processor and allocate resourcers of this class in this processor's thread
         */
        virtual void onStartProcess() {}
        /**
         * @brief onStopProcess
         * stop this processor and free resourcers of this class in this processor's thread
         */
        virtual void onStopProcess() {}

    private:
        ProcessorAbstract(const ProcessorAbstract&) = delete;
        ProcessorAbstract(ProcessorAbstract&&) = delete;
        ProcessorAbstract& operator=(const ProcessorAbstract&) = delete;
        ProcessorAbstract& operator=(ProcessorAbstract&&) = delete;

    private:
        QString mProcessorName;
        QSharedPointer<WorkerThread> mThread;
        QVector<QSharedPointer<QTimer>> mTimerVector;

};


#endif // PROCESSORABSTRACT_H
