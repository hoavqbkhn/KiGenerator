#ifndef CREATEKIMETHOD_H
#define CREATEKIMETHOD_H

#include "kigeneratorhelper.h"

class CreateKiMethod : public KiGeneratorHelper
{
    public:
        CreateKiMethod();
        ~CreateKiMethod();
        bool process(QString& issue) override;
        void setKiPeople(int kiAPeople, int kiBPeople, int kiCPeople, int kiDPeople) override;
        void setKiPercent(float kiAPercent, float kiBPercent, float kiCPercent, float kiDPercent) override;
        void setThisQuarter(int quarter) override;
        int getThisQuarter() override;
        void setIsPercentMode(bool isPercentMode) override;
        void setNumberOfOfficer(int num) override;
        void setUpMode() override;
        QVector<QSharedPointer<Officer>> getResult() override;
        void setOfficialListOfficer(const QVector<QSharedPointer<Officer>>& list) override;
        void updateFixingList(const QString& id, const QString& ki) override;

    private:
        //variables
        float mKiAPercent {0};
        float mKiBPercent {0};
        float mKiCPercent {0};
        float mKiDPercent {0};
        int mKiAPeople {0};
        int mKiBPeople {0};
        int mKiCPeople {0};
        int mKiDPeople {0};
        int mThisQuarter {0};
        int mNumberOfOfficer {0};
        bool mIsPercentMode {false};
        QVector<QSharedPointer<Officer>> mOfficialListOfficer;
        QVector<QSharedPointer<Officer>> mListFixedKiOfficer;
        QVector<int> mOfficerGetKiAInThisSessionList;
        QVector<int> mOfficerGetKiBInThisSessionList;
        QVector<int> mOfficerGetKiCInThisSessionList;
        QVector<int> mOfficerGetKiDInThisSessionList;

        //function
        QVector<QSharedPointer<Officer>> mExecListOfficer;
        void setKiXQuaterStatusOfThemToYes(int kiType, const QVector<int>& listOfficerStt);
        QVector<int> setKiXQuaterStatusOfThemToNo(int kiType, const QVector<int>& listOfficerStt);
        void generateQuarterKi();
        void generateMonthlyKi(int month);
        QVector<int> getCandidateForKiA();
        QVector<int> getCandidateForKiB(const QVector<int>& listSetKiAThisSession);
        QVector<int> getCandidateForKiD(const QVector<int>& listSetKiABThisSesson);
        QVector<int> getCandidateForKiC(const QVector<int>& listSetKiABDThisSesson);
        void getPeopleHavingLessThanAndMoreThanOtherOneUintOfKiX(int kiType, int month, QVector<int>& listLess, QVector<int>& listMore);
        void setKiAAtMonthXOfQuarter(int month, QVector<int> listMore, QVector<int> listLess);
        void setKiBAtMonthXOfQuarter(int month, QVector<int> listMore, QVector<int> listLess);
        void setKiDAtMonthXOfQuarter(int month, QVector<int> listMore, QVector<int> listLess);
        void setKiCAtMonthXForLeftPeople(int month);
        void embroilList(QVector<QSharedPointer<Officer>>& list);
        void removeFixingKiOfficer();
        void addFixingKiOfficer();
        void clearAllList();
        void resetKiPeople();
        void sortResult();
        bool kiRateInputIsOk(QString& issue);
        void resetForARewYear(QVector<QSharedPointer<Officer> >& list);
};

#endif // CREATEKIMETHOD_H
