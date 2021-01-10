#ifndef OFFICERMODEL_H
#define OFFICERMODEL_H

#include <QAbstractListModel>
#include <memory>
#include "model/officer.h"
#include "model/dataprocessor.h"
class SetDefaultOfficerKiModel : public QAbstractListModel
{
    public:
        SetDefaultOfficerKiModel();
        ~SetDefaultOfficerKiModel();
        enum KiRole
        {
            KI_NameRole = Qt::UserRole + 15,
            KI_ValueQuarterRole,
            KI_IDRole,
            KI_SttRole,
            KI_KiAStatusRole,
            KI_KiBStatusRole,
            KI_KiCStatusRole,
            KI_KiDStatusRole,
        };
        int rowCount(const QModelIndex& parent = QModelIndex()) const;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

        void clearListOfficer();
        void setOfficerModel(QSharedPointer<DataProcessor> data);
        void updateFixingData(const QString& id, const QString& ki);

        QVector<QSharedPointer<Officer> > listOfficer() const;

    protected:
        QHash<int, QByteArray> roleNames() const;
    private:
        int mThisQuater {0};
        QVector<QSharedPointer<Officer>> mListOfficer;
        void cloneDatax(QVector<QSharedPointer<Officer>> source, QVector<QSharedPointer<Officer>>& des)
        {
            for (int index = 0; index < source.size(); index++)
            {
                // Create a temp
                auto temp = qSharedPointerCast<Officer> (source[index]);
                // Clone data for store
                auto cloneData = QSharedPointer<Officer> (new Officer(temp));
                des.push_back(cloneData);
            }
        }

};

#endif // OFFICERMODEL_H
