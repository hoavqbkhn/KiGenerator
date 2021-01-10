#ifndef OFFICER_H
#define OFFICER_H
#include <QString>
#include <QVector>
#include <common.h>
#include <QSharedPointer>
class Officer
{
    public:
        Officer();
        Officer(const QSharedPointer<Officer>& other);
        ~Officer();

        QString getOfficerId() const;
        void setOfficerId(const QString& getOfficerId);

        QString getOfficerName() const;
        void setOfficerName(const QString& officerName);

        QString getOfficerStt() const;
        void setOfficerStt(const QString& officerStt);

        QString getThisQuarterKi() const;
        void setThisQuarterKi(const QString& thisQuarterKi);

        QString getThisMonthKi() const;
        void setThisMonthKi(const QString& thisMonthKi);

        QString getKiXMonth(int month) const;
        void insertKiXMonth(const QString& kiXMonth, int pos);

        QString getKiXQuarter(int quarter) const;
        void insertKiXQuarter(const QString& kiXQuarter, int pos);

        QString getKiXStatus(const int& kiType) const;
        void insertKiXStatus(const QString& kiXStatus, int pos);

        QString getKiXMonthlyAmount(const int& kiType) const;
        void insertKiXMonthlyAmount(const QString& kiXMonthlyAmount, int pos);

        void resetData();
        void logData();

        int getRowInDocument() const;
        void setRowInDocument(int rowInDocument);


        int getKiNotAutoSet() const;
        void setKiNotAutoSet(int kiNotAutoSet);

        bool operator > (const Officer& officer) const;
        bool operator < (const Officer& officer) const;

        int getLastYearGotKiDQuarter() const;
        void setLastYearGotKiDQuarter(int lastYearGotKiDQuarter);

        int getLastYearGotKiAQuarter() const;
        void setLastYearGotKiAQuarter(int lastYearGotKiAQuarter);

private:
        QString mOfficerId {""};
        QString mOfficerName {""};
        QString mOfficerStt {""};
        QString mThisQuarterKi {"?"};
        QString mThisMonthKi {"?"};
        QVector<QString> mKiXMonth;
        QVector<QString> mKiXQuarter;
        QVector<QString> mKiXStatus;
        QVector<QString> mKiXMonthlyAmount;
        int mRowInDocument {0};
        int mKiNotAutoSet {0};
        int mLastYearGotKiDQuarter{2017};
        int mLastYearGotKiAQuarter{2017};
};

#endif // OFFICER_H
