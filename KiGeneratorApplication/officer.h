#ifndef OFFICER_H
#define OFFICER_H
#include <QString>
#include <QVector>
class Officer
{
    public:
        Officer();
        ~Officer();

        void setOfficerName(const QString& officerName);
        QString getOfficerName() const;

        void setKi(const QString& ki);
        QVector<QString> getKi() const;

    private:
        QString mOfficerName {""};
        QVector<QString> mKi;
};

#endif // OFFICER_H
