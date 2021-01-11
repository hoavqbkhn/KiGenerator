#ifndef MAINBUSINESSPROCESSOR_H
#define MAINBUSINESSPROCESSOR_H

#include <QObject>
#include <QSharedPointer>
#include <QTimer>
#include "common.h"
#include "flux/action.h"
#include "action/actiontype.h"
#include <QDateTime>
#include <QMap>
#include "middleware/kiappmiddlewareinterface.h"
#include <QDateTime>
#include <QMap>
#include "processorabstract.h"
#include "model/dataprocessor.h"
#include "model/createkimethod.h"
#include "model/adjustkimethod.h"
using vtx::flux::Action;
class MainBusinessProcessor: public ProcessorAbstract
{
        Q_OBJECT
    public:
        MainBusinessProcessor(const QString& processorName);

        virtual ~MainBusinessProcessor();

        /**
         * @brief processAction
         * @param action
         * process action from user in worker thread
         */
        void processAction(QSharedPointer<Action> action);

        void setMiddlewareInterface(KiAppMiddlewareInterface* middlewareInterface);

    public slots:
        void slotReceiveActionFromMiddleware(QSharedPointer<Action> actionFromMiddleware);

    signals:
        void signalQuit();

    private:
        KiAppMiddlewareInterface* mMiddlewareInterface;
        QSharedPointer<DataProcessor> mDataProcessor {nullptr};
        QSharedPointer<KiGeneratorHelper> mKiGeneratorHelper {nullptr};
        QMap<QString, float> mMapKiTypeAndRatio;
        //function
        void processActionWorkOnDataKiFile(QSharedPointer<vtx::flux::Action> action);
        void processActionGenerate(QSharedPointer<vtx::flux::Action> action);
        void processActionExport(QSharedPointer<vtx::flux::Action> action);
        void processActionUpdateFixingList(QSharedPointer<vtx::flux::Action> action);
        void processActionAdjustKi(QSharedPointer<vtx::flux::Action> action);
        void processActionConfig(QSharedPointer<vtx::flux::Action> action);
};

#endif // MAINBUSINESSPROCESSOR_H
