#include "officer.h"
#include "logger/logger.h"
Officer::Officer()
{
}

Officer::Officer(const QSharedPointer<Officer>& other)
{
    this->mOfficerId = other->getOfficerId();
    this->mOfficerName = other->getOfficerName();
    this->mOfficerStt = other->getOfficerStt();

    for (int index = 0; index < NUMBER_OF_MONTH; index++)
    {
        this->mKiXMonth.push_back(other->getKiXMonth(index));
    }

    for (int index = 0; index < NUMBER_OF_QUATER; index++)
    {
        this->mKiXQuarter.push_back(other->getKiXQuarter(index));
    }

    for (int index = 0; index < NUMBER_OF_TYPE_KI; index++)
    {
        this->mKiXStatus.push_back(other->getKiXStatus(index));
    }

    for (int index = 0; index < NUMBER_OF_TYPE_KI; index++)
    {
        this->mKiXMonthlyAmount.push_back(other->getKiXMonthlyAmount(index));
    }

    this->mRowInDocument = other->getRowInDocument();
}

Officer::~Officer()
{
}

QString Officer::getOfficerId() const
{
    return mOfficerId;
}

void Officer::setOfficerId(const QString& officerId)
{
    mOfficerId = officerId;
}

QString Officer::getOfficerName() const
{
    return mOfficerName;
}

void Officer::setOfficerName(const QString& officerName)
{
    mOfficerName = officerName;
}

QString Officer::getOfficerStt() const
{
    return mOfficerStt;
}

void Officer::setOfficerStt(const QString& officerStt)
{
    mOfficerStt = officerStt;
}

QString Officer::getThisQuarterKi() const
{
    return mThisQuarterKi;
}

void Officer::setThisQuarterKi(const QString& thisQuarterKi)
{
    mThisQuarterKi = thisQuarterKi;
}

QString Officer::getThisMonthKi() const
{
    return mThisMonthKi;
}

void Officer::setThisMonthKi(const QString& thisMonthKi)
{
    mThisMonthKi = thisMonthKi;
}

QString Officer::getKiXMonth(int month) const
{
    return mKiXMonth[month];
}

void Officer::insertKiXMonth(const QString& kiXMonth, int pos)
{
    if (pos < mKiXMonth.size())
    {
        QString ki = mKiXMonth[pos];
        mKiXMonth.remove(pos);
        mKiXMonth.insert(mKiXMonth.begin() + pos, kiXMonth);

        if (kiXMonth == KI_TYPE1_SYMBOL)
        {
            // tăng số tháng của loại ki này
            int amount = mKiXMonthlyAmount[KI_TYPE1].toInt();
            amount++;
            mKiXMonthlyAmount[KI_TYPE1] = QString::number(amount);
        }
        else if (kiXMonth == KI_TYPE2_SYMBOL)
        {
            int amount = mKiXMonthlyAmount[KI_TYPE2].toInt();
            amount++;
            mKiXMonthlyAmount[KI_TYPE2] = QString::number(amount);
        }
        else if (kiXMonth == KI_TYPE3_SYMBOL)
        {
            int amount = mKiXMonthlyAmount[KI_TYPE3].toInt();
            amount++;
            mKiXMonthlyAmount[KI_TYPE3] = QString::number(amount);
        }
        else if (kiXMonth == KI_TYPE4_SYMBOL)
        {
            int amount = mKiXMonthlyAmount[KI_TYPE4].toInt();
            amount++;
            mKiXMonthlyAmount[KI_TYPE4] = QString::number(amount);
        }
        else if (kiXMonth == KI_NOT_SET)
        {
            // giảm số tháng của loại ki này
            if (ki == KI_TYPE1_SYMBOL)
            {
                int amount = mKiXMonthlyAmount[KI_TYPE1].toInt();
                amount--;
                mKiXMonthlyAmount[KI_TYPE1] = QString::number(amount);
            }
            else if (ki == KI_TYPE2_SYMBOL)
            {
                int amount = mKiXMonthlyAmount[KI_TYPE2].toInt();
                amount--;
                mKiXMonthlyAmount[KI_TYPE2] = QString::number(amount);
            }
            else if (ki == KI_TYPE3_SYMBOL)
            {
                int amount = mKiXMonthlyAmount[KI_TYPE3].toInt();
                amount--;
                mKiXMonthlyAmount[KI_TYPE3] = QString::number(amount);
            }
            else if (ki == KI_TYPE4_SYMBOL)
            {
                int amount = mKiXMonthlyAmount[KI_TYPE4].toInt();
                amount--;
                mKiXMonthlyAmount[KI_TYPE4] = QString::number(amount);
            }
        }
    }
    else
    {
        mKiXMonth.push_back(kiXMonth);
    }
}

QString Officer::getKiXQuarter(int quarter) const
{
    return mKiXQuarter[quarter];
}

void Officer::insertKiXQuarter(const QString& kiXQuarter, int pos)
{
    if (pos < mKiXQuarter.size())
    {
        mKiXQuarter.remove(pos);
        mKiXQuarter.insert(mKiXQuarter.begin() + pos, kiXQuarter);

        if (kiXQuarter == KI_NOT_SET)
        {
            insertKiXMonth(KI_NOT_SET, pos * 3);
            insertKiXMonth(KI_NOT_SET, pos * 3 + 1);
            insertKiXMonth(KI_NOT_SET, pos * 3 + 2);
        }

        if (kiXQuarter == KI_TYPE1_SYMBOL)
        {
            insertKiXStatus(YES, KI_TYPE1);
        }
        else if (kiXQuarter == KI_TYPE2_SYMBOL)
        {
            insertKiXStatus(YES, KI_TYPE2);
        }
        else if (kiXQuarter == KI_TYPE3_SYMBOL)
        {
            insertKiXStatus(YES, KI_TYPE3);
        }
        else if (kiXQuarter == KI_TYPE4_SYMBOL)
        {
            insertKiXStatus(YES, KI_TYPE4);
        }
    }
    else
    {
        mKiXQuarter.push_back(kiXQuarter);
    }
}

QString Officer::getKiXStatus(const int& kiType) const
{
    return mKiXStatus.at(kiType);
}

void Officer::insertKiXStatus(const QString& kiXStatus, int pos)
{
    if (pos < mKiXStatus.size())
    {
        mKiXStatus.remove(pos);
        mKiXStatus.insert(mKiXStatus.begin() + pos, kiXStatus);
    }
    else
    {
        mKiXStatus.push_back(kiXStatus);
    }
}

QString Officer::getKiXMonthlyAmount(const int& kiType) const
{
    return mKiXMonthlyAmount.at(kiType);
}

void Officer::insertKiXMonthlyAmount(const QString& kiXMonthlyAmount, int pos)
{
    if (pos < mKiXMonthlyAmount.size())
    {
        mKiXMonthlyAmount.remove(pos);
        mKiXMonthlyAmount.insert(mKiXMonthlyAmount.begin() + pos, kiXMonthlyAmount);
    }
    else
    {
        mKiXMonthlyAmount.push_back(kiXMonthlyAmount);
    }
}

void Officer::resetData()
{
    for (int index = 0; index < mKiXMonth.size(); index++)
    {
        mKiXMonth[index] = KI_NOT_SET;
    }

    for (int index = 0; index < mKiXQuarter.size(); index++)
    {
        mKiXQuarter[index] = KI_NOT_SET;
    }

    for (int index = 0; index < mKiXMonthlyAmount.size(); index++)
    {
        mKiXMonthlyAmount[index] = AMOUNT_ZERO;
    }
}

void Officer::logData()
{
    LOG_DEBUG("STT %s, KiM1 = %s, KiM2 = %s, KiM3 = %s, KiM4 = %s, KiM5 = %s, KiM6 = %s, KiM7 = %s, KiM8 = %s, KiM9 = %s, KiM10 = %s, KiM11 = %s, KiM12 = %s, KiQ1 = %s, KiQ2 = %s, KiQ3 = %s, mKiQ4 = %s, KiA Status = %s, KiB Status = %s, KiC Status = %s, KiD Status = %s, KiAMonthNum = %s, KiBMonthNum = %s,KiCMonthNum = %s,KiDMonthNum = %s",
              mOfficerStt.toStdString().c_str(), mKiXMonth[0].toStdString().c_str(), mKiXMonth[1].toStdString().c_str(), mKiXMonth[2].toStdString().c_str(), mKiXMonth[3].toStdString().c_str(),
              mKiXMonth[4].toStdString().c_str(), mKiXMonth[5].toStdString().c_str(), mKiXMonth[6].toStdString().c_str(), mKiXMonth[7].toStdString().c_str(),
              mKiXMonth[8].toStdString().c_str(), mKiXMonth[9].toStdString().c_str(), mKiXMonth[10].toStdString().c_str(), mKiXMonth[11].toStdString().c_str(),
              mKiXQuarter[0].toStdString().c_str(), mKiXQuarter[1].toStdString().c_str(), mKiXQuarter[2].toStdString().c_str(), mKiXQuarter[3].toStdString().c_str(),
              mKiXStatus[0].toStdString().c_str(), mKiXStatus[1].toStdString().c_str(), mKiXStatus[2].toStdString().c_str(), mKiXStatus[3].toStdString().c_str(),
              mKiXMonthlyAmount[0].toStdString().c_str(), mKiXMonthlyAmount[1].toStdString().c_str(), mKiXMonthlyAmount[2].toStdString().c_str(), mKiXMonthlyAmount[3].toStdString().c_str());
}

int Officer::getRowInDocument() const
{
    return mRowInDocument;
}

void Officer::setRowInDocument(int rowInDocument)
{
    mRowInDocument = rowInDocument;
}

int Officer::getKiNotAutoSet() const
{
    return mKiNotAutoSet;
}

void Officer::setKiNotAutoSet(int kiNotAutoSet)
{
    mKiNotAutoSet = kiNotAutoSet;
}

bool Officer::operator > (const Officer& officer) const
{
    if (mOfficerStt.toInt() > officer.getOfficerStt().toInt())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Officer::operator <(const Officer& officer) const
{
    if (mOfficerStt.toInt() < officer.getOfficerStt().toInt())
    {
        return true;
    }
    else
    {
        return false;
    }
}
