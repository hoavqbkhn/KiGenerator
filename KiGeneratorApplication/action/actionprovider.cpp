#include "actionprovider.h"
#include "flux/action.h"
#include "flux/dispatcher.h"
#include "actionprovider.h"
#include "actiontype.h"
#include "logger/logger.h"


void ActionProvider::openFileKiData()
{
    LOG_DEBUG("[USER] OPEN DATA KI FILE");
    vtx::flux::Dispatcher::instance().dispatch(new vtx::flux::Action(ActionType::OpenDataKiFile, QVariant()));
}



void ActionProvider::updatePercentMode(QVariantMap data)
{
    vtx::flux::Dispatcher::instance().dispatch(new vtx::flux::Action(ActionType::UpdatePercentMode, QVariant(data)));
}

void ActionProvider::generate(QVariantMap preData)
{
    vtx::flux::Dispatcher::instance().dispatch(new vtx::flux::Action(ActionType::Generate, QVariant(preData)));
}

void ActionProvider::exportData()
{
    vtx::flux::Dispatcher::instance().dispatch(new vtx::flux::Action(ActionType::OpenFileForExport, QVariant()));
}

void ActionProvider::review()
{
    vtx::flux::Dispatcher::instance().dispatch(new vtx::flux::Action(ActionType::Review, QVariant()));
}

void ActionProvider::updateFixingKiList(QVariantMap fixingData)
{
    vtx::flux::Dispatcher::instance().dispatch(new vtx::flux::Action(ActionType::UpdateFixingList, QVariant(fixingData)));
}

void ActionProvider::adjustKi(QVariantMap adjustData)
{
    vtx::flux::Dispatcher::instance().dispatch(new vtx::flux::Action(ActionType::AdjustKi, QVariant(adjustData)));
}

void ActionProvider::accessCreateMode()
{
    vtx::flux::Dispatcher::instance().dispatch(new vtx::flux::Action(ActionType::AccessCreateMode, QVariant()));
}

void ActionProvider::accessAdjustMode()
{
    vtx::flux::Dispatcher::instance().dispatch(new vtx::flux::Action(ActionType::AccessAdjustMode, QVariant()));
}

void ActionProvider::config(QVariantMap config)
{
    vtx::flux::Dispatcher::instance().dispatch(new vtx::flux::Action(ActionType::Config, QVariant(config)));
}
