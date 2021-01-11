#include "kiappmiddleware.h"

KiAppMiddleware:: KiAppMiddleware()
{
}

KiAppMiddleware::~ KiAppMiddleware()
{
}

QSharedPointer<vtx::flux::Action>  KiAppMiddleware::process(const QSharedPointer<vtx::flux::Action>& action)
{
    switch (action->getType<ActionType>())
    {
        case ActionType::ExitApplication:
            emit signalDispatchActionToBusiness(action);
            return QSharedPointer<vtx::flux::Action>(new vtx::flux::Action(ActionType::None_Action, QVariant()));

        case ActionType::ProcessDataKiFile:
            emit signalDispatchActionToBusiness(action);
            return QSharedPointer<vtx::flux::Action>(new vtx::flux::Action(ActionType::None_Action, QVariant()));

        case ActionType::Review:
            emit signalDispatchActionToBusiness(action);
            return QSharedPointer<vtx::flux::Action>(new vtx::flux::Action(ActionType::None_Action, QVariant()));

        case ActionType::Export:
            emit signalDispatchActionToBusiness(action);
            return QSharedPointer<vtx::flux::Action>(new vtx::flux::Action(ActionType::None_Action, QVariant()));

        case ActionType::Generate:
            emit signalDispatchActionToBusiness(action);
            return QSharedPointer<vtx::flux::Action>(new vtx::flux::Action(ActionType::None_Action, QVariant()));

        case ActionType::UpdateFixingList:
            emit signalDispatchActionToBusiness(action);
            return QSharedPointer<vtx::flux::Action>(new vtx::flux::Action(ActionType::None_Action, QVariant()));

        case ActionType::AdjustKi:
            emit signalDispatchActionToBusiness(action);
            return QSharedPointer<vtx::flux::Action>(new vtx::flux::Action(ActionType::None_Action, QVariant()));

        case ActionType::AccessAdjustMode:
            emit signalDispatchActionToBusiness(action);
            return QSharedPointer<vtx::flux::Action>(new vtx::flux::Action(ActionType::None_Action, QVariant()));

        case ActionType::AccessCreateMode:
            emit signalDispatchActionToBusiness(action);
            return QSharedPointer<vtx::flux::Action>(new vtx::flux::Action(ActionType::None_Action, QVariant()));

        case ActionType::Config:
            emit signalDispatchActionToBusiness(action);
            return QSharedPointer<vtx::flux::Action>(new vtx::flux::Action(ActionType::None_Action, QVariant()));

        default:
            return action;
    }
}

void KiAppMiddleware::dispatchActionUpdateListOfficer(QSharedPointer<InnerMessage> officerData)
{
    vtx::flux::Action* msg = new vtx::flux::Action(ActionType::UpdateOfficerData, QVariant());
    msg->setInnerMessage(officerData);
    vtx::flux::Dispatcher::instance().dispatch(msg);
}

void KiAppMiddleware::dispatchActionUpdateResult(QSharedPointer<InnerMessage> data)
{
    vtx::flux::Action* msg = new vtx::flux::Action(ActionType::UpdateResult, QVariant());
    msg->setInnerMessage(data);
    vtx::flux::Dispatcher::instance().dispatch(msg);
}

void KiAppMiddleware::dispatchActionNotifyIssue(const QString& issue)
{
    vtx::flux::Dispatcher::instance().dispatch(new vtx::flux::Action(ActionType::NotifyIssue, QVariant(issue)));
}

void KiAppMiddleware::dispatchActionUpdateFixingKiOnDoneScreen(const QString& id, const QString& ki)
{
    QMap<QString, QVariant> map;
    map.insert("id", id);
    map.insert("ki", ki);
    vtx::flux::Dispatcher::instance().dispatch(new vtx::flux::Action(ActionType::UpdateFixingListOk, QVariant(map)));
}

void KiAppMiddleware::dispatchActionUpdateThisQuarter(int quarter)
{
    vtx::flux::Dispatcher::instance().dispatch(new vtx::flux::Action(ActionType::UpdateQuarter, QVariant(quarter)));
}



