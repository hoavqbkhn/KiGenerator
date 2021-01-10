#ifndef KICONFIG_H
#define KICONFIG_H
#include <QString>
#include <QMap>
class KiConfig
{
public:
    static KiConfig* getInstance();
    ~KiConfig();

    QString getKiType1Symbol() const;
    QString getKiType2Symbol() const;
    QString getKiType3Symbol() const;
    QString getKiType4Symbol() const;

    int getKiType1Index() const;
    int getKiType2Index() const;
    int getKiType3Index() const;
    int getKiType4Index() const;

private:
    static KiConfig* instance;
    KiConfig();
    QString mKiType1Symbol{"D"};
    QString mKiType2Symbol{"A"};
    QString mKiType3Symbol{"C"};
    QString mKiType4Symbol{"B"};

    int mKiType1Index{3};
    int mKiType2Index{0};
    int mKiType3Index{2};
    int mKiType4Index{1};

};

#endif // KICONFIG_H
