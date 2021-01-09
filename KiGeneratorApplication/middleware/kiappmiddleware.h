#ifndef DTC1MIDDLEWARE_H
#define DTC1MIDDLEWARE_H

#include <QObject>
#include <QString>
#include "logger/logger.h"
#include "flux/action.h"
#include "flux/middleware.h"
#include "flux/dispatcher.h"
#include "action/actiontype.h"
#include "flux/action.h"
#include "middleware/kiappmiddlewareinterface.h"

using vtx::flux::Action;

class  KiAppMiddleware : public QObject, public vtx::flux::Middleware, public KiAppMiddlewareInterface
{
        Q_OBJECT
    public:
        KiAppMiddleware();
        virtual ~ KiAppMiddleware();
        QSharedPointer<vtx::flux::Action> process(const QSharedPointer<vtx::flux::Action>& action) override;
        void dispatchActionUpdateListOfficer(QSharedPointer<InnerMessage> officerData) override;
        void dispatchActionUpdateResult(QSharedPointer<InnerMessage> data) override;
        void dispatchActionNotifyIssue(const QString& issue) override;
        void dispatchActionUpdateFixingKiOnDoneScreen(const QString& id, const QString& ki) override;
        void dispatchActionUpdateThisQuarter(int quarter);

    signals:
        void signalDispatchActionToBusiness(QSharedPointer<Action> actionFromMiddleware);

    private:

};

#endif // DTC1MIDDLEWARE_H
