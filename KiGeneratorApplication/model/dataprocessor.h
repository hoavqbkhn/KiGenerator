#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H
#include <QString>
#include "xlsxdocument.h"
#include "xlsxcell.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
#include "officer.h"
#include "common.h"
#include "logger/logger.h"
#include "innermessage.h"
class DataProcessor : public InnerMessage
{
    public:
        DataProcessor();
        ~DataProcessor();

        void setDataFileUrl(const QString& dataFileUrl);
        bool parseData();
        void exportData(QVector<QSharedPointer<Officer>> list, const QString& url);
        void setIsPercentMode(bool isPercentMode);
        void updateFixingList(const QString& id, const QString& ki);
        QVector<QSharedPointer<Officer>> getListOfficer();


    private:
        QString mDataFileUrl {""};
        QSharedPointer<QXlsx::Document> mXlsx {nullptr};
        QVector<QSharedPointer<Officer>> mOfficialListOfficer;

        //column index
        int mSttColumnIndex {0};
        int mIdColumnIndex {0};
        int mOfficerNameColumnIndex {0};
        int mKiMonthXColumnIndex[NUMBER_OF_MONTH];
        int mKiQuaterXColumnIndex[NUMBER_OF_QUATER];
        int mKiXStatusColumnIndex[NUMBER_OF_TYPE_KI];
        int mKiXMonthlyAmonutColumnIndex[NUMBER_OF_TYPE_KI];
        int mKiNotAutoSetColumnIndex {0};

        int findAFieldColumnIndex(const QString& fieldName);
        void searchAllFieldColumnIndex();
};

#endif // DATAPROCESSOR_H
