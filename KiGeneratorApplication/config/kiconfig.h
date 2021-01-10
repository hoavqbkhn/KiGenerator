#ifndef KICONFIG_H
#define KICONFIG_H
#include <QString>

class KiConfig
{
public:
    static KiConfig* getInstance();
    ~KiConfig();

    QString getKiType1Symbol() const;

    QString getKiType2Symbol() const;

    QString getKiType3Symbol() const;

    QString getKiType4Symbol() const;

private:
    static KiConfig* instance;
    KiConfig();
    QString mKiType1Symbol{"D"};
    QString mKiType2Symbol{"A"};
    QString mKiType3Symbol{"C"};
    QString mKiType4Symbol{"B"};
};

#endif // KICONFIG_H
