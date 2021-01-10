#ifndef ADJUSTKIMETHOD_H
#define ADJUSTKIMETHOD_H

#include "kigeneratorhelper.h"
class AdjustKiMethod: public KiGeneratorHelper
{
    public:
        AdjustKiMethod();
        ~AdjustKiMethod();
        bool process(QString& issue) override;
        void setKiPeople(int kiAPeople, int kiBPeople, int kiCPeople, int kiDPeople) override;
        void setKiPercent(float kiAPercent, float kiBPercent, float kiCPercent, float kiDPercent) override;
        void setThisQuarter(int quarter) override;
        int getThisQuarter() override;
        void setNumberOfOfficer(int num) override;
        QVector<QSharedPointer<Officer>> getResult() override;
        void setIsPercentMode(bool isPercentMode) override;
        void setUpMode() override;
        void setOfficialListOfficer(const QVector<QSharedPointer<Officer>>& list) override;
        void updateFixingList(const QString& id, const QString& ki) override;

    private:
        //variables
        float mKiType1Percent {0};
        float mKiType2Percent {0};
        float mKiType3Percent {0};
        float mKiType4Percent {0};
        int mKiType1People {0};
        int mKiType2People {0};
        int mKiType3People {0};
        int mKiType4People {0};
        int mThisQuarter {0};
        int mNumberOfOfficer {0};
        bool mIsPercentMode {false};
        QVector<QSharedPointer<Officer>> mListFixedKiOfficer;
        QVector<QSharedPointer<Officer>> mOfficialListOfficer;
        QVector<int> mOfficerGetKiType1InThisSessionList;
        QVector<int> mOfficerGetKiType2InThisSessionList;
        QVector<int> mOfficerGetKiType3InThisSessionList;
        QVector<int> mOfficerGetKiType4InThisSessionList;

        //function
        QVector<QSharedPointer<Officer>> mExecListOfficer;
        QVector<int> setKiXQuaterStatusOfThemToNo(int kiType, const QVector<int>& listOfficerStt);
        void generateQuarterKi();
        void generateMonthlyKi(int month);
        QVector<int> getCandidateForKiType1(const QVector<int>& listGotKiAInOldSession);
        QVector<int> getCandidateForKiType2(const QVector<int>& listSetKiAThisSession, const QVector<int>& listGotKiBInOldSession);
        QVector<int> getCandidateForKiType4(const QVector<int>& listSetKiABThisSession, const QVector<int>& listGotKiDInOldSession);
        QVector<int> getCandidateForKiType3(const QVector<int>& listSetKiABDThisSesson);
        void setKiXQuaterStatusOfThemToYes(int kiType, const QVector<int>& listOfficerStt);
        void getPeopleHavingLessThanAndMoreThanOtherOneUintOfKiX(int kiType, int month, QVector<int>& listLess, QVector<int>& listMore);
        void setKiType1AtMonthXOfQuarter(int month, QVector<int> listMore, QVector<int> listLess);
        void setKiType2AtMonthXOfQuarter(int month, QVector<int> listMore, QVector<int> listLess);
        void setKiType4AtMonthXOfQuarter(int month, QVector<int> listMore, QVector<int> listLess);
        void setKiType3AtMonthXForLeftPeople(int month);
        void embroilList(QVector<QSharedPointer<Officer>>& list);
        void removeFixingKiOfficer();
        void addFixingKiOfficer();
        void clearAllList();
        void resetKiPeople();
        void cleanKiMonth(int month);
        void sortResult();
        void adjustQuarterKi();
        bool kiRateInputIsOk(QString& issue);
};

#endif // ADJUSTKIMETHOD_H
