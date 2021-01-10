#include "kiconfig.h"
KiConfig* KiConfig::instance = NULL;
KiConfig::KiConfig()
{
}

int KiConfig::getThisYear() const
{
    return mThisYear;
}

void KiConfig::setThisYear(int thisYear)
{
    mThisYear = thisYear;
}

int KiConfig::getKiType4Index() const
{
    return mKiType4Index;
}

int KiConfig::getKiType3Index() const
{
    return mKiType3Index;
}

int KiConfig::getKiType2Index() const
{
    return mKiType2Index;
}

int KiConfig::getKiType1Index() const
{
    return mKiType1Index;
}

KiConfig* KiConfig::getInstance()
{
    if (instance == NULL)
    {
        instance = new KiConfig();
    }

    return instance;
}
KiConfig::~KiConfig()
{

}

QString KiConfig::getKiType1Symbol() const
{
    return mKiType1Symbol;
}

QString KiConfig::getKiType2Symbol() const
{
    return mKiType2Symbol;
}

QString KiConfig::getKiType3Symbol() const
{
    return mKiType3Symbol;
}

QString KiConfig::getKiType4Symbol() const
{
    return mKiType4Symbol;
}


