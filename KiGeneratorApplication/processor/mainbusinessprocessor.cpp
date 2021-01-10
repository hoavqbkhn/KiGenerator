#include "mainbusinessprocessor.h"


MainBusinessProcessor::MainBusinessProcessor(const QString& processorName)
    : ProcessorAbstract(processorName)
{
}

MainBusinessProcessor::~MainBusinessProcessor()
{
}




void MainBusinessProcessor::processAction(QSharedPointer<Action> action)
{
    switch (action->getType<ActionType>())
    {
        case ActionType::ExitApplication:
            {
                emit signalQuit();
                break;
            }

        case ActionType::ProcessDataKiFile:
            {
                LOG_DEBUG("ProcessDataKiFile")
                processActionWorkOnDataKiFile(action);
                break;
            }

        case ActionType::Export:
            {
                LOG_DEBUG("Export")
                processActionExport(action);
                break;
            }

        case ActionType::Generate:
            {
                LOG_DEBUG("Generate")
                processActionGenerate(action);
                break;
            }

        case ActionType::Review:
            {
                LOG_DEBUG("ProcessDataKiFile")
                break;
            }

        case ActionType::UpdateFixingList:
            {
                LOG_DEBUG("UpdateFixingList")
                processActionUpdateFixingList(action);
                break;
            }

        case ActionType::AdjustKi:
            {
                LOG_DEBUG("AdjustKi")
                processActionAdjustKi(action);
                break;
            }

        case ActionType::AccessAdjustMode:
            {
                mKiGeneratorHelper = QSharedPointer<AdjustKiMethod>(new AdjustKiMethod());
                mKiGeneratorHelper->setOfficialListOfficer(mDataProcessor->getListOfficer());
                mKiGeneratorHelper->setUpMode();
                mMiddlewareInterface->dispatchActionUpdateThisQuarter(mKiGeneratorHelper->getThisQuarter());
                break;
            }

        case ActionType::AccessCreateMode:
            {
                mKiGeneratorHelper = QSharedPointer<CreateKiMethod>(new CreateKiMethod());
                mKiGeneratorHelper->setOfficialListOfficer(mDataProcessor->getListOfficer());
                mKiGeneratorHelper->setUpMode();
                mMiddlewareInterface->dispatchActionUpdateThisQuarter(mKiGeneratorHelper->getThisQuarter());
                break;
            }

        default:
            break;
    }
}
void MainBusinessProcessor::slotReceiveActionFromMiddleware(QSharedPointer<Action> actionFromMiddleware)
{
    processAction(actionFromMiddleware);
}

void MainBusinessProcessor::processActionWorkOnDataKiFile(QSharedPointer<vtx::flux::Action> action)
{
    mDataProcessor = QSharedPointer<DataProcessor>(new DataProcessor());
    QString filePath = action->getPayload<QVariant>().toString();

    if (filePath.length() > 9)
    {
#ifdef linux
        filePath = filePath.remove(0, 7); //remove file:///
#else
        filePath = filePath.remove(0, 8); //remove file:///
#endif
    }

    LOG_DEBUG("file path = %s", filePath.toStdString().c_str())
    mDataProcessor->setDataFileUrl(filePath);

    if (mDataProcessor->parseData())
    {
        LOG_DEBUG("Successfully Parsing")
        mMiddlewareInterface->dispatchActionUpdateListOfficer(mDataProcessor);
        mMiddlewareInterface->dispatchActionNotifyIssue("Đã tải xong!");
    }
}

void MainBusinessProcessor::processActionGenerate(QSharedPointer<vtx::flux::Action> action)
{
    QMap<QString, QVariant> map = action->getPayload<QVariant>().toMap();
    LOG_DEBUG("factorA = %f, factorB = %f, factorD = %f, percentMode = %d",
              map.value("factorA").toFloat(), map.value("factorB").toFloat(),
              map.value("factorD").toFloat(),
              map.value("isPercentMode").toBool());

    mMapKiTypeAndRatio.clear();
    mMapKiTypeAndRatio.insert("A", map.value("factorA").toFloat());
    mMapKiTypeAndRatio.insert("B", map.value("factorB").toFloat());
    mMapKiTypeAndRatio.insert("D", map.value("factorD").toFloat());

    if (map.value("isPercentMode").toBool())
    {
        mKiGeneratorHelper->setKiPercent(mMapKiTypeAndRatio[KiConfig::getInstance()->getKiType1Symbol()], mMapKiTypeAndRatio[KiConfig::getInstance()->getKiType2Symbol()],
                mMapKiTypeAndRatio[KiConfig::getInstance()->getKiType3Symbol()], mMapKiTypeAndRatio[KiConfig::getInstance()->getKiType4Symbol()]);
    }
    else
    {
        mKiGeneratorHelper->setKiPeople(mMapKiTypeAndRatio[KiConfig::getInstance()->getKiType1Symbol()], mMapKiTypeAndRatio[KiConfig::getInstance()->getKiType2Symbol()],
                mMapKiTypeAndRatio[KiConfig::getInstance()->getKiType3Symbol()], mMapKiTypeAndRatio[KiConfig::getInstance()->getKiType4Symbol()]);
    }

    mKiGeneratorHelper->setIsPercentMode(map.value("isPercentMode").toBool());
    QString issue;

    if (mKiGeneratorHelper->process(issue))
    {
        mMiddlewareInterface->dispatchActionUpdateResult(mKiGeneratorHelper);
        mMiddlewareInterface->dispatchActionNotifyIssue("Tạo thành công!");
    }
    else
    {
        mMiddlewareInterface->dispatchActionNotifyIssue(issue);
    }
}

void MainBusinessProcessor::processActionExport(QSharedPointer<vtx::flux::Action> action)
{
    QString filePath = action->getPayload<QVariant>().toString();

    if (filePath.length() > 9)
    {
#ifdef linux
        filePath = filePath.remove(0, 7); //remove file:///
#else
        filePath = filePath.remove(0, 8); //remove file:///
#endif
    }

    if (!filePath.contains(".xlsx"))
    {
        filePath += ".xlsx";
    }

    mDataProcessor->exportData(mKiGeneratorHelper->getResult(), filePath);
    mMiddlewareInterface->dispatchActionNotifyIssue("Xuất file thành công!");
}

void MainBusinessProcessor::processActionUpdateFixingList(QSharedPointer<vtx::flux::Action> action)
{
    QMap<QString, QVariant> map = action->getPayload<QVariant>().toMap();
    LOG_DEBUG("Fix ki information: id = %s, ki = %s",
              map.value("id").toString().toStdString().c_str(), map.value("ki").toString().toStdString().c_str());
    mKiGeneratorHelper->updateFixingList(map.value("id").toString(), map.value("ki").toString());
    mMiddlewareInterface->dispatchActionUpdateFixingKiOnDoneScreen(map.value("id").toString(), map.value("ki").toString());
}

void MainBusinessProcessor::processActionAdjustKi(QSharedPointer<vtx::flux::Action> action)
{
    QMap<QString, QVariant> map = action->getPayload<QVariant>().toMap();
    LOG_DEBUG("factorA = %f, factorB = %f, factorD = %f, percentMode = %d",
              map.value("factorA").toFloat(), map.value("factorB").toFloat(),
              map.value("factorD").toFloat(),
              map.value("isPercentMode").toBool());
    mMapKiTypeAndRatio.clear();
    mMapKiTypeAndRatio.insert("A", map.value("factorA").toFloat());
    mMapKiTypeAndRatio.insert("B", map.value("factorB").toFloat());
    mMapKiTypeAndRatio.insert("D", map.value("factorD").toFloat());

    if (map.value("isPercentMode").toBool())
    {
        mKiGeneratorHelper->setKiPercent(mMapKiTypeAndRatio[KiConfig::getInstance()->getKiType1Symbol()], mMapKiTypeAndRatio[KiConfig::getInstance()->getKiType2Symbol()],
                mMapKiTypeAndRatio[KiConfig::getInstance()->getKiType3Symbol()], mMapKiTypeAndRatio[KiConfig::getInstance()->getKiType4Symbol()]);
    }
    else
    {
        mKiGeneratorHelper->setKiPeople(mMapKiTypeAndRatio[KiConfig::getInstance()->getKiType1Symbol()], mMapKiTypeAndRatio[KiConfig::getInstance()->getKiType2Symbol()],
                mMapKiTypeAndRatio[KiConfig::getInstance()->getKiType3Symbol()], mMapKiTypeAndRatio[KiConfig::getInstance()->getKiType4Symbol()]);
    }

    mKiGeneratorHelper->setIsPercentMode(map.value("isPercentMode").toBool());
    QString issue;

    if (mKiGeneratorHelper->process(issue))
    {
        LOG_DEBUG("Adjust ok")
        mMiddlewareInterface->dispatchActionUpdateResult(mKiGeneratorHelper);
        mMiddlewareInterface->dispatchActionNotifyIssue("Điều chỉnh thành công!");
    }
    else
    {
        mMiddlewareInterface->dispatchActionNotifyIssue(issue);
    }
}




void MainBusinessProcessor::setMiddlewareInterface(KiAppMiddlewareInterface* middlewareInterface)
{
    mMiddlewareInterface = middlewareInterface;
}
