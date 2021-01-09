#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H


#include <QThread>

/**
 * @brief The WorkerThread class
 * This is a wrapped worker thread
 * An event loop run inside it
 */
class WorkerThread : public QThread
{
        Q_OBJECT
    public:
        WorkerThread() = default;
        ~WorkerThread() = default;

    private:
        WorkerThread(const WorkerThread&) = delete;
        WorkerThread(WorkerThread&&) = delete;
        WorkerThread& operator=(const WorkerThread&) = delete;
        WorkerThread& operator=(WorkerThread&&) = delete;
        void run() override;
};

#endif // WORKERTHREAD_H
