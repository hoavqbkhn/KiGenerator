#include "kiappstore.h"
#include "model/kigeneratorhelper.h"
KiAppStore* KiAppStore::instance = NULL;
KiAppStore::KiAppStore()
{
    mListOfficerModel = QSharedPointer<SetDefaultOfficerKiModel>(new SetDefaultOfficerKiModel());
    mResultModelOrderStyle = QSharedPointer<ResultModelOrderStyle>(new ResultModelOrderStyle());
    mResultModelKiGroupStyle = QSharedPointer<ResultModelKiGroupStyle>(new ResultModelKiGroupStyle());
}

int KiAppStore::getThisQuarter() const
{
    return mThisQuarter;
}

QSharedPointer<ResultModelKiGroupStyle> KiAppStore::getResultModelKiGroupStyle() const
{
    return mResultModelKiGroupStyle;
}

QString KiAppStore::getIssue() const
{
    return mIssue;
}

QSharedPointer<ResultModelOrderStyle> KiAppStore::getResultModel() const
{
    return mResultModelOrderStyle;
}

void KiAppStore::setResultModel(const QSharedPointer<ResultModelOrderStyle>& resultModel)
{
    mResultModelOrderStyle = resultModel;
}

bool KiAppStore::getIsPercentMode() const
{
    return mIsPercentMode;
}

int KiAppStore::getKiDPeople() const
{
    return mKiDPeople;
}

int KiAppStore::getKiCPeople() const
{
    return mKiCPeople;
}

int KiAppStore::getKiBPeople() const
{
    return mKiBPeople;
}

int KiAppStore::getKiAPeople() const
{
    return mKiAPeople;
}


QSharedPointer<SetDefaultOfficerKiModel> KiAppStore::getListOfficerModel() const
{
    return mListOfficerModel;
}

void KiAppStore::processActionOpenDataKiFile(const QSharedPointer<vtx::flux::Action>& action)
{
    LOG_DEBUG("OpenDataKiFile")
    QMap<QString, QVariant> map = action->getPayload<QVariant>().toMap();
    QFileDialog fileFolderDialog;
    QString selectedFilter("");
    QString fileUrl;
    QString url = fileFolderDialog.getOpenFileUrl(Q_NULLPTR, tr("Tải file dữ liệu KI"), fileUrl, tr("*.xlsx"), &selectedFilter, QFileDialog::DontUseNativeDialog).toString();

    if (url == "")//when select no file or cancel
    {
        return;
    }

    LOG_DEBUG("ProcessDataKiFile1")
    vtx::flux::Dispatcher::instance().dispatch(new vtx::flux::Action(ActionType::ProcessDataKiFile, QVariant(url)));
}

void KiAppStore::processActionUpdateOfficerData(const QSharedPointer<vtx::flux::Action>& action)
{
    LOG_DEBUG("UpdateOfficerData")
    mListOfficerModel->clearListOfficer();
    QSharedPointer<DataProcessor> data = qSharedPointerDynamicCast<DataProcessor>(action->getInnerMessage());
    mListOfficerModel->setOfficerModel(data);

    if (data->getListOfficer().size() > 0)
    {
        mFileIsLoaded = true;
    }

    emit loadingFileChanged();
    emit officerModelChanged();
}

void KiAppStore::processActionUpdateResult(const QSharedPointer<vtx::flux::Action>& action)
{
    LOG_DEBUG("UpdateOfficerData")
    mResultModelOrderStyle->clearListOfficer();
    mResultModelKiGroupStyle->clearListOfficer();
    QSharedPointer<KiGeneratorHelper> data = qSharedPointerDynamicCast<KiGeneratorHelper>(action->getInnerMessage());
    mResultModelOrderStyle->setOfficerModel(data);
    mResultModelKiGroupStyle->setOfficerModel(data);
    mKiAPeople = mResultModelKiGroupStyle->numberOfPeopleGetKiA();
    mKiBPeople = mResultModelKiGroupStyle->numberOfPeopleGetKiB();
    mKiCPeople = mResultModelKiGroupStyle->numberOfPeopleGetKiC();
    mKiDPeople = mResultModelKiGroupStyle->numberOfPeopleGetKiD();
    mNumberOfOfficer = mResultModelKiGroupStyle->numberOfOfficer();
    emit kiScaleChanged();
    emit officerModelChanged();
}

void KiAppStore::processActionUpdateIssue(const QSharedPointer<vtx::flux::Action>& action)
{
    mIssue = action->getPayload<QVariant>().toString();
    emit issueChanged();
}

void KiAppStore::processActionUpdateFixingKiListOk(const QSharedPointer<vtx::flux::Action>& action)
{
    QMap<QString, QVariant> map = action->getPayload<QVariant>().toMap();
    mListOfficerModel->updateFixingData(map.value("id").toString(), map.value("ki").toString());
}

void KiAppStore::processActionOpenFileForExport(const QSharedPointer<vtx::flux::Action>& action)
{
    (void) action;
    LOG_DEBUG("OpenFileForExport")
    QMap<QString, QVariant> map = action->getPayload<QVariant>().toMap();
    QFileDialog fileFolderDialog;
    QString selectedFilter("");
    QString fileUrl;
    QString url = fileFolderDialog.getSaveFileUrl(Q_NULLPTR, tr("Lưu file dữ liệu KI"), fileUrl, tr("*.xlsx"), &selectedFilter, QFileDialog::DontUseNativeDialog).toString();

    if (url == "")//when select no file or cancel
    {
        return;
    }

    vtx::flux::Dispatcher::instance().dispatch(new vtx::flux::Action(ActionType::Export, QVariant(url)));
}

void KiAppStore::processActionUpdatePercentMode(const QSharedPointer<vtx::flux::Action>& action)
{
    QMap<QString, QVariant> map = action->getPayload<QVariant>().toMap();
    mIsPercentMode = map.value("isPercentMode").toBool();
    emit kiScaleChanged();
}



bool KiAppStore::getFileIsLoaded() const
{
    return mFileIsLoaded;
}

void KiAppStore::setFileIsLoaded(bool fileIsLoaded)
{
    mFileIsLoaded = fileIsLoaded;
}

KiAppStore::~KiAppStore()
{
}

KiAppStore* KiAppStore::getInstance()
{
    if (instance == NULL)
    {
        instance = new KiAppStore();
    }

    return instance;
}

void KiAppStore::process(const QSharedPointer<vtx::flux::Action>& action)
{
    switch (action->getType<ActionType>())
    {
        case ActionType::OpenDataKiFile:
            {
                processActionOpenDataKiFile(action);
                break;
            }

        case ActionType::UpdateOfficerData:
            {
                processActionUpdateOfficerData(action);
                break;
            }

        case ActionType::UpdateResult:
            {
                processActionUpdateResult(action);
                break;
            }

        case ActionType::NotifyIssue:
            {
                processActionUpdateIssue(action);
                break;
            }

        case ActionType::UpdateFixingListOk:
            {
                processActionUpdateFixingKiListOk(action);
                break;
            }

        case ActionType::OpenFileForExport:
            {
                processActionOpenFileForExport(action);
                break;
            }

        case ActionType::UpdatePercentMode:
            {
                processActionUpdatePercentMode(action);
                break;
            }

        case ActionType::UpdateQuarter:
            {
                mThisQuarter = action->getPayload<QVariant>().toInt() + 1;
                emit thisQuarterChanged();
                break;
            }

        default:
            break;
    }
}
