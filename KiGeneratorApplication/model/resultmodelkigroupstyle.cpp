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
    mNumberOfPeopleGetKiA = 0;
    mNumberOfPeopleGetKiB = 0;
    mNumberOfPeopleGetKiC = 0;
    mNumberOfPeopleGetKiD = 0;
    mNumberOfOfficer = 0;
    mListOfficer.clear();
    emit layoutChanged();
}

void ResultModelKiGroupStyle::setOfficerModel(QSharedPointer<KiGeneratorHelper> data)
{
    mThisQuater = data->getThisQuarter();
    mNumberOfPeopleGetKiA = 0;
    mNumberOfPeopleGetKiB = 0;
    mNumberOfPeopleGetKiC = 0;
    mNumberOfPeopleGetKiD = 0;
    mNumberOfOfficer = 0;

    for (int index = 0; index < data->getResult().size(); index++)
    {
        QSharedPointer<Officer> officer = data->getResult().at(index);

        if (officer->getKiXQuarter(mThisQuater) == KI_A_SYMBOL)
        {
            mListOfficer.push_back(officer);
            mNumberOfPeopleGetKiA ++;
        }
    }

    for (int index = 0; index < data->getResult().size(); index++)
    {
        QSharedPointer<Officer> officer = data->getResult().at(index);

        if (officer->getKiXQuarter(mThisQuater) == KI_B_SYMBOL)
        {
            mListOfficer.push_back(officer);
            mNumberOfPeopleGetKiB++;
        }
    }

    for (int index = 0; index < data->getResult().size(); index++)
    {
        QSharedPointer<Officer> officer = data->getResult().at(index);

        if (officer->getKiXQuarter(mThisQuater) == KI_C_SYMBOL)
        {
            mListOfficer.push_back(officer);
            mNumberOfPeopleGetKiC++;
        }
    }

    for (int index = 0; index < data->getResult().size(); index++)
    {
        QSharedPointer<Officer> officer = data->getResult().at(index);

        if (officer->getKiXQuarter(mThisQuater) == KI_D_SYMBOL)
        {
            mListOfficer.push_back(officer);
            mNumberOfPeopleGetKiD++;
        }
    }

    mNumberOfOfficer = mNumberOfPeopleGetKiA + mNumberOfPeopleGetKiB + mNumberOfPeopleGetKiC + mNumberOfPeopleGetKiD;
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
    return mNumberOfPeopleGetKiD;
}

int ResultModelKiGroupStyle::numberOfPeopleGetKiC() const
{
    return mNumberOfPeopleGetKiC;
}

int ResultModelKiGroupStyle::numberOfPeopleGetKiB() const
{
    return mNumberOfPeopleGetKiB;
}

int ResultModelKiGroupStyle::numberOfPeopleGetKiA() const
{
    return mNumberOfPeopleGetKiA;
}

