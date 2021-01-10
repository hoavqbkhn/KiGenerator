#ifndef KIGENERATORHELPER_H
#define KIGENERATORHELPER_H
#include <QString>
#include "officer.h"
#include "innermessage.h"
#include "common.h"
#include "logger/logger.h"
#include <QVector>
#include <QRandomGenerator>
#include <array>
#include <algorithm>
#include <iterator>
#include <functional>
#include "config/kiconfig.h"

class KiGeneratorHelper : public InnerMessage
{
    public:
        KiGeneratorHelper();
        ~KiGeneratorHelper();
        virtual bool process(QString& issue) = 0;
        virtual void setKiPeople(int kiAPeople, int kiBPeople, int kiCPeople, int kiDPeople) = 0;
        virtual void setKiPercent(float kiAPercent, float kiBPercent, float kiCPercent, float kiDPercent) = 0;
        virtual void setThisQuarter(int quarter) = 0;
        virtual int getThisQuarter() = 0;
        virtual void setNumberOfOfficer(int num) = 0;
        virtual void setIsPercentMode(bool isPercentMode) = 0;
        virtual QVector<QSharedPointer<Officer>> getResult() = 0;
        virtual void setUpMode() = 0;
        virtual void setOfficialListOfficer(const QVector<QSharedPointer<Officer>>& list) = 0;
        virtual void updateFixingList(const QString& id, const QString& ki) = 0;

    public:
        int convertQuarterToFirstMonth(int quarter);
        int convertQuarterToSecondMonth(int quarter);
        int convertQuarterToThirdMonth(int quarter);
        int randomIntergerInRange(int minVal, int maxVal);
        QVector<int> getRandomSelectedList(int maxAmount,const QVector<int>& list);
        QVector<int> getRandomSelectedListVer2(int maxAmount, const QVector<int>& list, const QVector<int> priorityList);


};

#endif // KIGENERATORHELPER_H
