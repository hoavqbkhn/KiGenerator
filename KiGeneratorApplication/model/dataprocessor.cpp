#include "dataprocessor.h"
#include <QDebug>
#include <ctime>
#include <cstdlib>
#include <QDateTime>
#include <QRandomGenerator>
#include "config/kiconfig.h"
DataProcessor::DataProcessor()
{
}

DataProcessor::~DataProcessor()
{
}

void DataProcessor::setDataFileUrl(const QString& dataFileUrl)
{
    mDataFileUrl = dataFileUrl;
}

bool DataProcessor::parseData()
{
    mOfficialListOfficer.clear();
    //1. Khoi tao
    mXlsx = QSharedPointer<QXlsx::Document>(new QXlsx::Document(mDataFileUrl));
    //2. Tim kiem chi so Column cua cac truong stt, id, name ....
    searchAllFieldColumnIndex();

    //3. ParseData
    for (int row = 0; row < 100; ++row)
    {
        QSharedPointer<Officer> officer =  QSharedPointer<Officer>(new Officer());

        //parse name
        if (QXlsx::Cell* cell = mXlsx->cellAt(row, mOfficerNameColumnIndex))
        {
            officer->setOfficerName(cell->value().toString());
        }

        //parse stt
        if (QXlsx::Cell* cell = mXlsx->cellAt(row, mSttColumnIndex))
        {
            officer->setOfficerStt(cell->value().toString());
        }

        //parse msnv
        if (QXlsx::Cell* cell = mXlsx->cellAt(row, mIdColumnIndex))
        {
            officer->setOfficerId(cell->value().toString());
        }

        //parse ki quy
        for (int index = 0; index < NUMBER_OF_QUATER; index++)
        {
            int col = mKiQuaterXColumnIndex[index];

            if (QXlsx::Cell* cell = mXlsx->cellAt(row, col))
            {
                officer->insertKiXQuarter(cell->value().toString(), index);
            }
        }

        //parse ki thang
        for (int index = 0; index < NUMBER_OF_MONTH; index++)
        {
            int col = mKiMonthXColumnIndex[index];

            if (QXlsx::Cell* cell = mXlsx->cellAt(row, col))
            {
                officer->insertKiXMonth(cell->value().toString(), index);
            }
        }

        //parse ki x status
        for (int index = 0; index < NUMBER_OF_TYPE_KI; index++)
        {
            int col = mKiXStatusColumnIndex[index];

            if (QXlsx::Cell* cell = mXlsx->cellAt(row, col))
            {
                officer->insertKiXStatus(cell->value().toString(), index);
            }
        }

        //parse ki x month amount
        for (int index = 0; index < NUMBER_OF_TYPE_KI; index++)
        {
            int col = mKiXMonthlyAmonutColumnIndex[index];

            if (QXlsx::Cell* cell = mXlsx->cellAt(row, col))
            {
                officer->insertKiXMonthlyAmount(cell->value().toString(), index);
            }
        }

        //check ki not autoset
        if (QXlsx::Cell* cell = mXlsx->cellAt(row, mKiNotAutoSetColumnIndex))
        {
            officer->setKiNotAutoSet(cell->value().toInt());
        }

        //parse last year get kiA quarter
        if (QXlsx::Cell* cell = mXlsx->cellAt(row, mKiAQuaterSetLastYear))
        {
            officer->setLastYearGotKiAQuarter(cell->value().toInt());
        }

        //parse last year get kiD quarter
        if (QXlsx::Cell* cell = mXlsx->cellAt(row, mKiDQuaterSetLastYear))
        {
            officer->setLastYearGotKiDQuarter(cell->value().toInt());
        }


        //Lưu lại để dùng khi export
        officer->setRowInDocument(row);

        if (officer->getOfficerName() != "" && officer->getOfficerName() != "Họ tên"
            && officer->getOfficerStt() != "" && officer->getKiNotAutoSet() != 1)
        {
            mOfficialListOfficer.push_back(officer);
        }
    }

    if (mOfficialListOfficer.size() > 0)
    {
        return true;
    }

    return false;
}

int DataProcessor::findAFieldColumnIndex(const QString& fieldName)
{
    bool canBreakLoop = false;
    int index = 0;

    for (int col = 0; col < 60; col++)
    {
        for (int row = 0; row < 60; row++)
        {
            if (QXlsx::Cell* cell = mXlsx->cellAt(row, col))
            {
                if (cell->value().toString().contains(fieldName))
                {
                    canBreakLoop = true;
                    index = col;
                    break;
                }
            }
        }

        if (canBreakLoop)
        {
            break;
        }
    }

    return index;
}

void DataProcessor::searchAllFieldColumnIndex()
{
    mSttColumnIndex = findAFieldColumnIndex(STT_COLUMN_NAME);
    mIdColumnIndex = findAFieldColumnIndex(ID_COLUMN_NAME);
    mOfficerNameColumnIndex = findAFieldColumnIndex(OFFICERNAME_COLUMN_NAME);
    mKiMonthXColumnIndex[MONTH1] = findAFieldColumnIndex(KI_THANG_1);
    mKiMonthXColumnIndex[MONTH2] = findAFieldColumnIndex(KI_THANG_2);
    mKiMonthXColumnIndex[MONTH3] = findAFieldColumnIndex(KI_THANG_3);
    mKiMonthXColumnIndex[MONTH4] = findAFieldColumnIndex(KI_THANG_4);
    mKiMonthXColumnIndex[MONTH5] = findAFieldColumnIndex(KI_THANG_5);
    mKiMonthXColumnIndex[MONTH6] = findAFieldColumnIndex(KI_THANG_6);
    mKiMonthXColumnIndex[MONTH7] = findAFieldColumnIndex(KI_THANG_7);
    mKiMonthXColumnIndex[MONTH8] = findAFieldColumnIndex(KI_THANG_8);
    mKiMonthXColumnIndex[MONTH9] = findAFieldColumnIndex(KI_THANG_9);
    mKiMonthXColumnIndex[MONTH10] = findAFieldColumnIndex(KI_THANG_10);
    mKiMonthXColumnIndex[MONTH11] = findAFieldColumnIndex(KI_THANG_11);
    mKiMonthXColumnIndex[MONTH12] = findAFieldColumnIndex(KI_THANG_12);
    mKiQuaterXColumnIndex[QUARTER1] = findAFieldColumnIndex(KI_QUY_1);
    mKiQuaterXColumnIndex[QUARTER2] = findAFieldColumnIndex(KI_QUY_2);
    mKiQuaterXColumnIndex[QUARTER3] = findAFieldColumnIndex(KI_QUY_3);
    mKiQuaterXColumnIndex[QUARTER4] = findAFieldColumnIndex(KI_QUY_4);
    mKiXMonthlyAmonutColumnIndex[KI_A_INDEX] = findAFieldColumnIndex(SO_KI_A_THANG);
    mKiXMonthlyAmonutColumnIndex[KI_B_INDEX] = findAFieldColumnIndex(SO_KI_B_THANG);
    mKiXMonthlyAmonutColumnIndex[KI_C_INDEX] = findAFieldColumnIndex(SO_KI_C_THANG);
    mKiXMonthlyAmonutColumnIndex[KI_D_INDEX] = findAFieldColumnIndex(SO_KI_D_THANG);
    mKiXStatusColumnIndex[KI_A_INDEX] = findAFieldColumnIndex(KI_A_STATUS);
    mKiXStatusColumnIndex[KI_B_INDEX] = findAFieldColumnIndex(KI_B_STATUS);
    mKiXStatusColumnIndex[KI_C_INDEX] = findAFieldColumnIndex(KI_C_STATUS);
    mKiXStatusColumnIndex[KI_D_INDEX] = findAFieldColumnIndex(KI_D_STATUS);
    mKiNotAutoSetColumnIndex = findAFieldColumnIndex(KI_NOT_AUTOSET);
    mKiAQuaterSetLastYear = findAFieldColumnIndex(LAST_YEAR_SET_KI_A);
    mKiDQuaterSetLastYear = findAFieldColumnIndex(LAST_YEAR_SET_KI_D);
}



void DataProcessor::exportData(QVector<QSharedPointer<Officer>> list, const QString& url)
{
    for (int index = 0; index < list.size(); index++)
    {
        //save ki month
        for (int j = 0; j < NUMBER_OF_MONTH; j++)
        {
            int col = mKiMonthXColumnIndex[j];
            int row = list[index]->getRowInDocument();
            mXlsx->write(row, col, list[index]->getKiXMonth(j));
        }

        //save ki quarter
        for (int j = 0; j < NUMBER_OF_QUATER; j++)
        {
            int col = mKiQuaterXColumnIndex[j];
            int row = list[index]->getRowInDocument();
            mXlsx->write(row, col, list[index]->getKiXQuarter(j));
        }

        //save ki status
        for (int j = 0; j < NUMBER_OF_TYPE_KI; j++)
        {
            int col = mKiXStatusColumnIndex[j];
            int row = list[index]->getRowInDocument();
            mXlsx->write(row, col, list[index]->getKiXStatus(j).toInt());
        }

        //save ki month amount
        for (int j = 0; j < NUMBER_OF_TYPE_KI; j++)
        {
            int col = mKiXMonthlyAmonutColumnIndex[j];
            int row = list[index]->getRowInDocument();
            mXlsx->write(row, col, list[index]->getKiXMonthlyAmount(j).toInt());
        }
    }

    mXlsx->saveAs(url);
    LOG_DEBUG("SAVE OK")
}

QVector<QSharedPointer<Officer> > DataProcessor::getListOfficer()
{
    return mOfficialListOfficer;
}
