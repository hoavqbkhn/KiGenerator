#include "resultmodelkigroupstyle.h"

ResultModelKiGroupStyle::ResultModelKiGroupStyle()
{
}

ResultModelKiGroupStyle::~ResultModelKiGroupStyle()
{
}

int ResultModelKiGroupStyle::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return mListOfficer.size();
}

QVariant ResultModelKiGroupStyle::data(const QModelIndex& index, int role) const
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

void ResultModelKiGroupStyle::clearListOfficer()
{
    mNumberOfPeopleGetKiType1 = 0;
    mNumberOfPeopleGetKiType2 = 0;
    mNumberOfPeopleGetKiType3 = 0;
    mNumberOfPeopleGetKiType4 = 0;
    mNumberOfOfficer = 0;
    mListOfficer.clear();
    emit layoutChanged();
}

void ResultModelKiGroupStyle::setOfficerModel(QSharedPointer<KiGeneratorHelper> data)
{
    mThisQuater = data->getThisQuarter();
    mNumberOfPeopleGetKiType1 = 0;
    mNumberOfPeopleGetKiType2 = 0;
    mNumberOfPeopleGetKiType3 = 0;
    mNumberOfPeopleGetKiType4 = 0;
    mNumberOfOfficer = 0;

    for (int index = 0; index < data->getResult().size(); index++)
    {
        QSharedPointer<Officer> officer = data->getResult().at(index);

        if (officer->getKiXQuarter(mThisQuater) == KiConfig::getInstance()->getKiType1Symbol())
        {
            mListOfficer.push_back(officer);
            mNumberOfPeopleGetKiType1 ++;
        }
    }

    for (int index = 0; index < data->getResult().size(); index++)
    {
        QSharedPointer<Officer> officer = data->getResult().at(index);

        if (officer->getKiXQuarter(mThisQuater) == KiConfig::getInstance()->getKiType2Symbol())
        {
            mListOfficer.push_back(officer);
            mNumberOfPeopleGetKiType2++;
        }
    }

    for (int index = 0; index < data->getResult().size(); index++)
    {
        QSharedPointer<Officer> officer = data->getResult().at(index);

        if (officer->getKiXQuarter(mThisQuater) == KiConfig::getInstance()->getKiType3Symbol())
        {
            mListOfficer.push_back(officer);
            mNumberOfPeopleGetKiType3++;
        }
    }

    for (int index = 0; index < data->getResult().size(); index++)
    {
        QSharedPointer<Officer> officer = data->getResult().at(index);

        if (officer->getKiXQuarter(mThisQuater) == KiConfig::getInstance()->getKiType4Symbol())
        {
            mListOfficer.push_back(officer);
            mNumberOfPeopleGetKiType4++;
        }
    }

    mNumberOfOfficer = mNumberOfPeopleGetKiType1 + mNumberOfPeopleGetKiType2 + mNumberOfPeopleGetKiType3 + mNumberOfPeopleGetKiType4;
    mMap.clear();
    mMap.insert(KiConfig::getInstance()->getKiType1Symbol(), mNumberOfPeopleGetKiType1);
    mMap.insert(KiConfig::getInstance()->getKiType2Symbol(), mNumberOfPeopleGetKiType2);
    mMap.insert(KiConfig::getInstance()->getKiType3Symbol(), mNumberOfPeopleGetKiType3);
    mMap.insert(KiConfig::getInstance()->getKiType4Symbol(), mNumberOfPeopleGetKiType4);
    emit layoutChanged();
}

QVector<QSharedPointer<Officer> > ResultModelKiGroupStyle::listOfficer() const
{
    return mListOfficer;
}

QHash<int, QByteArray> ResultModelKiGroupStyle::roleNames() const
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

int ResultModelKiGroupStyle::numberOfOfficer() const
{
    return mNumberOfOfficer;
}

int ResultModelKiGroupStyle::numberOfPeopleGetKiD() const
{
    return mMap["D"];
}

int ResultModelKiGroupStyle::numberOfPeopleGetKiC() const
{
    return mMap["C"];
}

int ResultModelKiGroupStyle::numberOfPeopleGetKiB() const
{
    return mMap["B"];
}

int ResultModelKiGroupStyle::numberOfPeopleGetKiA() const
{
    return mMap["A"];
}

