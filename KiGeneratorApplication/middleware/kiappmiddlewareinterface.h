#ifndef DTC1MIDDLEWAREINTERFACE_H
#define DTC1MIDDLEWAREINTERFACE_H

#include <QVariant>
#include "flux/dispatcher.h"
#include "action/actiontype.h"
#include "flux/action.h"
#include "model/dataprocessor.h"
class KiAppMiddlewareInterface
{
    public:
        virtual void dispatchActionUpdateListOfficer(QSharedPointer<InnerMessage> data) = 0;
        virtual void dispatchActionUpdateResult(QSharedPointer<InnerMessage> data) = 0;
        virtual void dispatchActionNotifyIssue(const QString& issue) = 0;
        virtual void dispatchActionUpdateFixingKiOnDoneScreen(const QString& id, const QString& ki) = 0;
        virtual void dispatchActionUpdateThisQuarter(int quarter) = 0;
};

#endif // DTC1MIDDLEWAREINTERFACE_H
