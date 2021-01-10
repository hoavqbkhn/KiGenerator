#include "kiconfig.h"
KiConfig* KiConfig::instance = NULL;
KiConfig::KiConfig()
{

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


