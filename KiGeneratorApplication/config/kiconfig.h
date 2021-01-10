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

    int getThisYear() const;
    void setThisYear(int thisYear);

private:
    static KiConfig* instance;
    KiConfig();
    QString mKiType1Symbol{"D"};
    QString mKiType2Symbol{"A"};
    QString mKiType3Symbol{"C"};
    QString mKiType4Symbol{"B"};

    int mKiType1Index{3}; //lưu giá trị index của ki type1 trong file excel (Ở đây type1 đang là KiD có index  = 3 trong file excel)
    int mKiType2Index{0}; //lưu giá trị index của ki type2 trong file excel (Ở đây type2 đang là KiA có index  = 0 trong file excel)
    int mKiType3Index{2};
    int mKiType4Index{1};

    int mThisYear{2020};

};

#endif // KICONFIG_H
