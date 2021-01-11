#ifndef RESULTMODELKIGROUPSTYLE_H
#define RESULTMODELKIGROUPSTYLE_H
#include <QAbstractListModel>
#include <memory>
#include "model/officer.h"
#include "model/kigeneratorhelper.h"

class ResultModelKiGroupStyle: public QAbstractListModel
{
    public:
        ResultModelKiGroupStyle();
        ~ResultModelKiGroupStyle();
        enum KiRole
        {
            RESKI_NameRole = Qt::UserRole + 15,
            RESKI_ValueQuarterRole,
            RESKI_ValueMonth1Role,
            RESKI_ValueMonth2Role,
            RESKI_ValueMonth3Role,
            RESKI_IDRole,
            RESKI_SttRole
        };
        int rowCount(const QModelIndex& parent = QModelIndex()) const;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

        void clearListOfficer();
        void setOfficerModel(QSharedPointer<KiGeneratorHelper> data);

        QVector<QSharedPointer<Officer> > listOfficer() const;


        int numberOfPeopleGetKiA() const;
        int numberOfPeopleGetKiB() const;
        int numberOfPeopleGetKiC() const;
        int numberOfPeopleGetKiD() const;
        int numberOfOfficer() const;

    protected:
        QHash<int, QByteArray> roleNames() const;
    private:
        int mThisQuater {0};
        QVector<QSharedPointer<Officer>> mListOfficer;
        int mNumberOfPeopleGetKiType1 {0};
        int mNumberOfPeopleGetKiType2 {0};
        int mNumberOfPeopleGetKiType3 {0};
        int mNumberOfPeopleGetKiType4 {0};
        int mNumberOfOfficer {0};
        QMap<QString, int> mMap;
};

#endif // RESULTMODELKIGROUPSTYLE_H
