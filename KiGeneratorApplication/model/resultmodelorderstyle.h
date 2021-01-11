#ifndef RESULTMODEL_H
#define RESULTMODEL_H
#include <QAbstractListModel>
#include <memory>
#include "model/officer.h"
#include "model/kigeneratorhelper.h"

class ResultModelOrderStyle: public QAbstractListModel
{

    public:
        ResultModelOrderStyle();
        ~ResultModelOrderStyle();
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


    protected:
        QHash<int, QByteArray> roleNames() const;
    private:
        int mThisQuater {0};
        QVector<QSharedPointer<Officer>> mListOfficer;
};

#endif // RESULTMODEL_H
