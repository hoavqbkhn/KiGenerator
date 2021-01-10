#include "setdefaultkimodel.h"
#include "common.h"

SetDefaultOfficerKiModel::SetDefaultOfficerKiModel()
{
}

SetDefaultOfficerKiModel::~SetDefaultOfficerKiModel()
{
}

int SetDefaultOfficerKiModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return mListOfficer.size();
}

QVariant SetDefaultOfficerKiModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= mListOfficer.count())
    {
        return QVariant();
    }

    auto infoList = mListOfficer[index.row()];

    if (role == KI_NameRole)
    {
        return infoList->getOfficerName();
    }
    else if (role == KI_ValueQuarterRole)
    {
        return infoList->getKiXQuarter(mThisQuater);
    }
    else if (role == KI_SttRole)
    {
        return infoList->getOfficerStt();
    }
    else if (role == KI_IDRole)
    {
        return infoList->getOfficerId();
    }
    else if (role == KI_KiAStatusRole)
    {
        return infoList->getKiXStatus(KI_TYPE1);
    }
    else if (role == KI_KiBStatusRole)
    {
        return infoList->getKiXStatus(KI_TYPE2);
    }
    else if (role == KI_KiCStatusRole)
    {
        return infoList->getKiXStatus(KI_TYPE3);
    }
    else if (role == KI_KiDStatusRole)
    {
        return infoList->getKiXStatus(KI_TYPE4);
    }

    return QVariant();
}

void SetDefaultOfficerKiModel::clearListOfficer()
{
    mListOfficer.clear();
    emit layoutChanged();
}

void SetDefaultOfficerKiModel::setOfficerModel(QSharedPointer<DataProcessor> data)
{
    cloneDatax(data->getListOfficer(), mListOfficer);

    for (int index = 0; index < mListOfficer.size(); index++)
    {
        mListOfficer[index]->resetData();
    }

    emit layoutChanged();
}

void SetDefaultOfficerKiModel::updateFixingData(const QString& id, const QString& ki)
{
    for (int index = 0; index < mListOfficer.size(); index++)
    {
        if (mListOfficer[index]->getOfficerId() == id)
        {
            mListOfficer[index]->insertKiXQuarter(ki, mThisQuater);
            break;
        }
    }

    emit layoutChanged();
}

QHash<int, QByteArray> SetDefaultOfficerKiModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[KI_NameRole] = "OfficerName";
    roles[KI_ValueQuarterRole] = "OfficerQuarterKI";
    roles[KI_SttRole] = "OfficerStt";
    roles[KI_IDRole] = "OfficerMsnv";
    roles[KI_KiAStatusRole] = "OfficerKiAStatus";
    roles[KI_KiBStatusRole] = "OfficerKiBStatus";
    roles[KI_KiCStatusRole] = "OfficerKiCStatus";
    roles[KI_KiDStatusRole] = "OfficerKiDStatus";
    return roles;
}

QVector<QSharedPointer<Officer> > SetDefaultOfficerKiModel::listOfficer() const
{
    return mListOfficer;
}
