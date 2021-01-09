#include "resultmodelorderstyle.h"

ResultModelOrderStyle::ResultModelOrderStyle()
{
}

ResultModelOrderStyle::~ResultModelOrderStyle()
{
}

int ResultModelOrderStyle::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return mListOfficer.size();
}

QVariant ResultModelOrderStyle::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= mListOfficer.count())
    {
        return QVariant();
    }

    auto infoList = mListOfficer[index.row()];

    if (role == RESKI_NameRole)
    {
        return infoList->getOfficerName();
    }
    else if (role == RESKI_ValueQuarterRole)
    {
        return infoList->getKiXQuarter(mThisQuater);
    }
    else if (role == RESKI_SttRole)
    {
        return infoList->getOfficerStt();
    }
    else if (role == RESKI_IDRole)
    {
        return infoList->getOfficerId();
    }
    else if (role == RESKI_ValueMonth1Role)
    {
        return infoList->getKiXMonth(mThisQuater * 3);
    }
    else if (role == RESKI_ValueMonth2Role)
    {
        return infoList->getKiXMonth(mThisQuater * 3 + 1);
    }
    else if (role == RESKI_ValueMonth3Role)
    {
        return infoList->getKiXMonth(mThisQuater * 3 + 2);
    }

    return QVariant();
}

void ResultModelOrderStyle::clearListOfficer()
{
    mListOfficer.clear();
    emit layoutChanged();
}

void ResultModelOrderStyle::setOfficerModel(QSharedPointer<KiGeneratorHelper> data)
{
    mThisQuater = data->getThisQuarter();

    for (int index = 0; index < data->getResult().size(); index++)
    {
        mListOfficer.push_back(data->getResult().at(index));
    }

    emit layoutChanged();
}

QVector<QSharedPointer<Officer> > ResultModelOrderStyle::listOfficer() const
{
    return mListOfficer;
}

QHash<int, QByteArray> ResultModelOrderStyle::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[RESKI_NameRole] = "OfficerName";
    roles[RESKI_ValueQuarterRole] = "OfficerQuarterKI";
    roles[RESKI_ValueMonth1Role] = "OfficerMonth1KI";
    roles[RESKI_ValueMonth2Role] = "OfficerMonth2KI";
    roles[RESKI_ValueMonth3Role] = "OfficerMonth3KI";
    roles[RESKI_SttRole] = "OfficerStt";
    roles[RESKI_IDRole] = "OfficerMsnv";
    return roles;
}

