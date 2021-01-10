#ifndef DTC1_COMMON_H
#define DTC1_COMMON_H

#include <string>
#include <QString>
#include <math.h>
#include <QString>
#include <QSharedPointer>
#include <QVector>
const QString KI_THANG_1 = "Ki tháng 1";
const QString KI_THANG_2 = "Ki tháng 2";
const QString KI_THANG_3 = "Ki tháng 3";
const QString KI_THANG_4 = "Ki tháng 4";
const QString KI_THANG_5 = "Ki tháng 5";
const QString KI_THANG_6 = "Ki tháng 6";
const QString KI_THANG_7 = "Ki tháng 7";
const QString KI_THANG_8 = "Ki tháng 8";
const QString KI_THANG_9 = "Ki tháng 9";
const QString KI_THANG_10 = "Ki tháng 10";
const QString KI_THANG_11 = "Ki tháng 11";
const QString KI_THANG_12 = "Ki tháng 12";
const QString KI_QUY_1 = "Ki quý 1";
const QString KI_QUY_2 = "Ki quý 2";
const QString KI_QUY_3 = "Ki quý 3";
const QString KI_QUY_4 = "Ki quý 4";
const QString KI_A_STATUS = "KI A Status";
const QString KI_B_STATUS = "KI B Status";
const QString KI_C_STATUS = "KI C Status";
const QString KI_D_STATUS = "KI D Status";
const QString SO_KI_A_THANG = "Sô KI A Tháng";
const QString SO_KI_B_THANG = "Sô KI B Tháng";
const QString SO_KI_C_THANG = "Sô KI C Tháng";
const QString SO_KI_D_THANG = "Sô KI D Tháng";
const QString KI_NOT_AUTOSET = "NOT AUTOSET";
const QString LAST_YEAR_SET_KI_A = "Năm A Quý";
const QString LAST_YEAR_SET_KI_D = "Năm D Quý";

const QString ID_COLUMN_NAME = "Mã nhân viên";
const QString OFFICERNAME_COLUMN_NAME = "Họ tên";
const QString STT_COLUMN_NAME = "STT";
const QString KI_NOT_SET = "";
const QString AMOUNT_ZERO = "0";
const QString GDTT_ID = "060969";
const QString MAIN_BUSINESS_PROCESSOR_NAME = "MainBussinessProcessName";

const int MONTH1 = 0;
const int MONTH2 = 1;
const int MONTH3 = 2;
const int MONTH4 = 3;
const int MONTH5 = 4;
const int MONTH6 = 5;
const int MONTH7 = 6;
const int MONTH8 = 7;
const int MONTH9 = 8;
const int MONTH10 = 9;
const int MONTH11 = 10;
const int MONTH12 = 11;
const int QUARTER1 = 0;
const int QUARTER2 = 1;
const int QUARTER3 = 2;
const int QUARTER4 = 3;

const int KI_A_INDEX = 0;
const int KI_B_INDEX = 1;
const int KI_C_INDEX = 2;
const int KI_D_INDEX = 3;

const int NUMBER_OF_MONTH = 12;
const int NUMBER_OF_QUATER = 4;
const int NUMBER_OF_TYPE_KI = 4;

const QString YES = "1";
const QString NO = "0";
const double FLOATING_POINT_NUMBER_DEVIATION = 0.000001;

static inline bool compareFloatEqual(float num1, float num2, float deviation = FLOATING_POINT_NUMBER_DEVIATION)
{
    if (fabsf(num1 - num2) < deviation)
    {
        return true;
    }
    else
    {
        return false;
    }
}
template <typename T1, typename T2>
void cloneData(QVector<QSharedPointer<T1>> source, QVector<QSharedPointer<T2>>& des)
{
    for (int index = 0; index < source.size(); index++)
    {
        // Create a temp
        auto temp = qSharedPointerCast<T2> (source[index]);
        // Clone data for store
        auto cloneData = QSharedPointer<T2> (new T2(temp));
        des.push_back(cloneData);
    }
}
class Common
{
    public:
        Common();
};

#endif // DTC1_COMMON_H
