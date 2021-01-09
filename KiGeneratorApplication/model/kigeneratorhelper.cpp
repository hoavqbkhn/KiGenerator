#include "kigeneratorhelper.h"

KiGeneratorHelper::KiGeneratorHelper()
{
}

KiGeneratorHelper::~KiGeneratorHelper()
{
}

int KiGeneratorHelper::convertQuarterToFirstMonth(int quarter)
{
    return quarter * 3;
}

int KiGeneratorHelper::convertQuarterToSecondMonth(int quarter)
{
    return quarter * 3 + 1;
}

int KiGeneratorHelper::convertQuarterToThirdMonth(int quarter)
{
    return quarter * 3 + 2;
}

int KiGeneratorHelper::randomIntergerInRange(int minVal, int maxVal)
{
    return QRandomGenerator::global()->bounded(minVal, maxVal);
}

QVector<int> KiGeneratorHelper::getRandomSelectedList(int maxAmount, const QVector<int>& list)
{
    //PP:Chọn random phần tử thứ x trong vector chứa số thứ tự của các officer
    int selectedOfficerAmount = maxAmount;
    QVector<int> selectedIndexList;
    QVector<int> selectedSttList;
    selectedSttList.clear();
    selectedIndexList.clear();
    int luckyIndex = 0;

    //Cho random hết số lượng ki
    while (selectedOfficerAmount > 0 && selectedSttList.size() != list.size())
    {
        do
        {
            //Lấy random phần tử thứ x trong vector
            luckyIndex = randomIntergerInRange(0, list.size());
        }
        while (selectedIndexList.size() != 0 && selectedIndexList.contains(luckyIndex));

        selectedIndexList.push_back(luckyIndex);
        selectedSttList.push_back(list[luckyIndex]);
        luckyIndex = 0;
        selectedOfficerAmount--;
    }

    return selectedSttList;
}

QVector<int> KiGeneratorHelper::getRandomSelectedListVer2(int maxAmount, const QVector<int>& list, const QVector<int> priorityList)
{
    //PP:Chọn random phần tử thứ x trong vector chứa số thứ tự của các officer
    QVector<int> selectedIndexList;
    QVector<int> selectedSttList;
    selectedSttList.clear();
    selectedIndexList.clear();

    for (int index = 0; index < priorityList.size(); index++)
    {
        if (maxAmount - selectedSttList.size() > 0)
        {
            if (list.contains(priorityList[index]))
            {
                selectedSttList.append(priorityList[index]);
            }
        }
    }

    int selectedOfficerAmount = maxAmount - selectedSttList.size()  ;
    int luckyIndex = 0;

    //Cho random hết số lượng ki
    while (selectedOfficerAmount > 0)
    {
        do
        {
            //Lấy random phần tử thứ x trong vector
            luckyIndex = randomIntergerInRange(0, list.size());
        }
        while (/*selectedIndexList.size() != 0 || */selectedSttList.contains(list[luckyIndex]));

        selectedIndexList.push_back(luckyIndex);
        selectedSttList.push_back(list[luckyIndex]);
        luckyIndex = 0;
        selectedOfficerAmount--;
    }

    return selectedSttList;
}
