#include "adjustkimethod.h"

AdjustKiMethod::AdjustKiMethod()
{
}

AdjustKiMethod::~AdjustKiMethod()
{
}

bool AdjustKiMethod::process(QString& issue)
{
    clearAllList();
    //Khởi tạo 1 list mới để xử lý.
    cloneData(mOfficialListOfficer, mExecListOfficer);
    embroilList(mExecListOfficer);
    //Tinh so luong nhan vien trong danh sach
    mNumberOfOfficer = mExecListOfficer.size();

    if (!kiRateInputIsOk(issue))
    {
        return false;
    }

    //adjust Ki
    adjustQuarterKi();
    //reset kipeople
    resetKiPeople();
    //Xóa hết KI tháng đi
    cleanKiMonth(convertQuarterToFirstMonth(mThisQuarter));
    cleanKiMonth(convertQuarterToSecondMonth(mThisQuarter));
    cleanKiMonth(convertQuarterToThirdMonth(mThisQuarter));
    //gen ki tháng
    generateMonthlyKi(convertQuarterToFirstMonth(mThisQuarter));
    generateMonthlyKi(convertQuarterToSecondMonth(mThisQuarter));
    generateMonthlyKi(convertQuarterToThirdMonth(mThisQuarter));
    //sort result
    sortResult();

    //logger
    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        mExecListOfficer[index]->logData();
    }

    return true;
}

void AdjustKiMethod::setKiPeople(int kiType1People, int kiType2People, int kiType3People, int kiType4People)
{
    mKiType1People = kiType1People;
    mKiType2People = kiType2People;
    mKiType3People = kiType3People;
    mKiType4People = kiType4People;
}

void AdjustKiMethod::setKiPercent(float kiType1Percent, float kiType2Percent, float kiType3Percent, float kiType4Percent)
{
    mKiType1Percent = kiType1Percent;
    mKiType2Percent = kiType2Percent;
    mKiType3Percent = kiType3Percent;
    mKiType4Percent = kiType4Percent;
}

void AdjustKiMethod::setThisQuarter(int quarter)
{
    mThisQuarter = quarter;
}

int AdjustKiMethod::getThisQuarter()
{
    return mThisQuarter;
}

void AdjustKiMethod::setNumberOfOfficer(int num)
{
    mNumberOfOfficer = num;
}

QVector<QSharedPointer<Officer>> AdjustKiMethod::getResult()
{
    return mExecListOfficer;
}

void AdjustKiMethod::setIsPercentMode(bool isPercentMode)
{
    mIsPercentMode = isPercentMode;
}

void AdjustKiMethod::setUpMode()
{
    if (mOfficialListOfficer[0]->getKiXQuarter(QUARTER4) != KI_NOT_SET)
    {
        mThisQuarter =  QUARTER4;
    }
    else if (mOfficialListOfficer[0]->getKiXQuarter(QUARTER3) != KI_NOT_SET)
    {
        mThisQuarter = QUARTER3;
    }
    else if (mOfficialListOfficer[0]->getKiXQuarter(QUARTER2) != KI_NOT_SET)
    {
        mThisQuarter = QUARTER2;
    }
    else if (mOfficialListOfficer[0]->getKiXQuarter(QUARTER1) != KI_NOT_SET)
    {
        mThisQuarter = QUARTER1;
    }
    else
    {
        LOG_DEBUG("Why this file is empty????")
    }
}

void AdjustKiMethod::setOfficialListOfficer(const QVector<QSharedPointer<Officer> >& list)
{
    mOfficialListOfficer = list;
}

void AdjustKiMethod::updateFixingList(const QString& id, const QString& ki)
{
    //do nothing
}


void AdjustKiMethod::setKiXQuaterStatusOfThemToYes(int kiType, const QVector<int>& listOfficerStt)
{
    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        if (listOfficerStt.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            //*decrease

                if(kiType == KiConfig::getInstance()->getKiType1Index()){
                    if (mKiType1People > 0)
                    {
                        mExecListOfficer[index]->insertKiXQuarter(KiConfig::getInstance()->getKiType1Symbol(), mThisQuarter);
                        LOG_DEBUG("STT %d Get KiType1 in Quarter %d", mExecListOfficer[index]->getOfficerStt().toInt(), mThisQuarter + 1);
                        mKiType1People--;
                    }
                }else if(kiType == KiConfig::getInstance()->getKiType2Index()){
                    if (mKiType2People > 0)
                    {
                        mExecListOfficer[index]->insertKiXQuarter(KiConfig::getInstance()->getKiType2Symbol(), mThisQuarter);
                        LOG_DEBUG("STT %d Get KiType2 in Quarter %d", mExecListOfficer[index]->getOfficerStt().toInt(), mThisQuarter + 1);
                        mKiType2People--;
                    }
                }else if(kiType == KiConfig::getInstance()->getKiType3Index()){
                    if (mKiType3People > 0)
                    {
                        mExecListOfficer[index]->insertKiXQuarter(KiConfig::getInstance()->getKiType3Symbol(), mThisQuarter);
                        LOG_DEBUG("STT %d Get KiType3 in Quarter %d", mExecListOfficer[index]->getOfficerStt().toInt(), mThisQuarter + 1);
                        mKiType3People--;
                    }
                }else if(kiType == KiConfig::getInstance()->getKiType4Index()){
                    if (mKiType4People > 0)
                    {
                        mExecListOfficer[index]->insertKiXQuarter(KiConfig::getInstance()->getKiType4Symbol(), mThisQuarter);
                        LOG_DEBUG("STT %d Get KiType4 in Quarter %d", mExecListOfficer[index]->getOfficerStt().toInt(), mThisQuarter + 1);
                        mKiType4People--;
                    }

                }
        }
    }
}

QVector<int> AdjustKiMethod::setKiXQuaterStatusOfThemToNo(int kiType, const QVector<int>& listOfficerStt)
{
    QVector<int> randomList;

    //reset trạng thái Ki X của toàn bộ những người ko được fix cứng KI
    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        if (!listOfficerStt.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            if(kiType == KiConfig::getInstance()->getKiType1Index()){
                if (mKiType1People > 0)
                {
                    mExecListOfficer[index]->insertKiXStatus(NO, KiConfig::getInstance()->getKiType1Index());
                    randomList.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
                }
            }else if(kiType == KiConfig::getInstance()->getKiType2Index()){
                if (mKiType2People > 0)
                {
                    mExecListOfficer[index]->insertKiXStatus(NO, KiConfig::getInstance()->getKiType2Index());

                    if (!mOfficerGetKiType1InThisSessionList.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
                    {
                        randomList.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
                    }
                }
            }else if(kiType == KiConfig::getInstance()->getKiType3Index()){
                if (mKiType3People > 0)
                {
                    mExecListOfficer[index]->insertKiXStatus(NO, KiConfig::getInstance()->getKiType3Index());
                    randomList.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
                }
            }else if(kiType == KiConfig::getInstance()->getKiType4Index()){
                if (mKiType4People > 0)
                {
                    mExecListOfficer[index]->insertKiXStatus(NO, KiConfig::getInstance()->getKiType4Index());

                    if (!mOfficerGetKiType1InThisSessionList.contains(mExecListOfficer[index]->getOfficerStt().toInt()) &&
                        !mOfficerGetKiType2InThisSessionList.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
                    {
                        randomList.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
                    }
                }
            }
        }
    }
    return randomList;
}
void AdjustKiMethod::generateMonthlyKi(int month)
{
    //0.  Xáo trộn list này nhân viên trước khi chạy thuật toán
    embroilList(mExecListOfficer);
    //1   Set KiType1
    //1.1 Chọn danh sách những người có tổng số Ki Type1 của tháng ít hơn những người còn lại 1 đơn vị.
    QVector<int> peopleHavingLessThanOtherOneUnitOfKiType1;
    QVector<int> peopleHavingMoreThanOtherOneUnitOfKiType1;
    getPeopleHavingLessThanAndMoreThanOtherOneUintOfKiX(KiConfig::getInstance()->getKiType1Index(), month, peopleHavingLessThanOtherOneUnitOfKiType1, peopleHavingMoreThanOtherOneUnitOfKiType1);
    //1.2 Thực thi
    setKiType1AtMonthXOfQuarter(month, peopleHavingMoreThanOtherOneUnitOfKiType1, peopleHavingLessThanOtherOneUnitOfKiType1);
    //2   Set KiType2
    //2.1 Chọn danh sách những người có tổng số Ki Type2 của tháng ít hơn những người còn lại 1 đơn vị.
    QVector<int> peopleHavingLessThanOtherOneUnitOfKiType2;
    QVector<int> peopleHavingMoreThanOtherOneUnitOfKiType2;
    getPeopleHavingLessThanAndMoreThanOtherOneUintOfKiX(KiConfig::getInstance()->getKiType2Index(), month, peopleHavingLessThanOtherOneUnitOfKiType2, peopleHavingMoreThanOtherOneUnitOfKiType2);
    //2.2 Thực thi
    setKiType2AtMonthXOfQuarter(month, peopleHavingMoreThanOtherOneUnitOfKiType2, peopleHavingLessThanOtherOneUnitOfKiType2);
    //3   Set KiType4
    //3.1 Chọn danh sách những người có tổng số Ki Type4 của tháng ít hơn những người còn lại 1 đơn vị.
    QVector<int> peopleHavingLessThanOtherOneUnitOfKiType4;
    QVector<int> peopleHavingMoreThanOtherOneUnitOfKiType4;
    getPeopleHavingLessThanAndMoreThanOtherOneUintOfKiX(KiConfig::getInstance()->getKiType4Index(), month, peopleHavingLessThanOtherOneUnitOfKiType4, peopleHavingMoreThanOtherOneUnitOfKiType4);
    //3.2 Thực thi
    setKiType4AtMonthXOfQuarter(month, peopleHavingMoreThanOtherOneUnitOfKiType4, peopleHavingLessThanOtherOneUnitOfKiType4);
    //4.  Set KiType3
    setKiType3AtMonthXForLeftPeople(month);
}

QVector<int> AdjustKiMethod::getCandidateForKiType1(const QVector<int>& listGotKiType1InOldSession)
{
    QVector<int> list;
    // Uu tien nhung nguoi nay truoc
    list.append(listGotKiType1InOldSession);

    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        //Tất cả những người chưa đạt Ki Type1.
        if (mExecListOfficer.at(index)->getKiXStatus(KiConfig::getInstance()->getKiType1Index()) != YES
            && !list.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            list.push_back(mExecListOfficer.at(index)->getOfficerStt().toInt());
        }
    }

    return list;
}

QVector<int> AdjustKiMethod::getCandidateForKiType2(const QVector<int>& listSetKiType1ThisSession, const QVector<int>& listGotKiType2InOldSession)
{
    QVector<int> list;

    // Uu tien nhung nguoi nay truoc
    for (int index = 0; index < listGotKiType2InOldSession.size(); index++)
    {
        if (!listSetKiType1ThisSession.contains(listGotKiType2InOldSession[index]))
        {
            list.append(listGotKiType2InOldSession[index]);
        }
    }

    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        //Tất cả những người chưa đạt Ki Type2, trừ những người đã đạt Ki Type1 trong lượt chọn Ki Type1
        if (!listSetKiType1ThisSession.contains(mExecListOfficer[index]->getOfficerStt().toInt())
            && mExecListOfficer[index]->getKiXStatus(KiConfig::getInstance()->getKiType2Index()) != YES
            && !list.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            list.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
        }
    }

    return list;
}

QVector<int> AdjustKiMethod::getCandidateForKiType4(const QVector<int>& listSetKi12ThisSession, const QVector<int>& listGotKiType4InOldSession)
{
    QVector<int> list;

    //Uu tien nhung nguoi nay truoc
    for (int index = 0; index < listGotKiType4InOldSession.size(); index++)
    {
        if (!listSetKi12ThisSession.contains(listGotKiType4InOldSession[index]))
        {
            list.append(listGotKiType4InOldSession[index]);
        }
    }

    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        //Tất cả những người chưa đạt Ki Type2, trừ những người đã đạt Ki Type1 trong lượt chọn Ki Type1
        if (!listSetKi12ThisSession.contains(mExecListOfficer[index]->getOfficerStt().toInt())
            && mExecListOfficer[index]->getKiXStatus(KiConfig::getInstance()->getKiType4Index()) != YES
            && !list.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            list.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
        }
    }

    return list;
}

void AdjustKiMethod::getPeopleHavingLessThanAndMoreThanOtherOneUintOfKiX(int kiType, int month, QVector<int>& listLess, QVector<int>& listMore)
{
    // mặc định coi như tất cả chỉ chênh nhau 1 đơn vị
    int maxKiXAmount = mExecListOfficer[0]->getKiXMonthlyAmount(kiType).toInt();
    bool thereIsDifference = false;

    for (int index = 0 ; index < mExecListOfficer.size(); index++)
    {
        if (maxKiXAmount < mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt())
        {
            maxKiXAmount = mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt();
            thereIsDifference = true;
        }
        else if (maxKiXAmount > mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt())
        {
            thereIsDifference = true;
        }
    }

    if (kiType == KiConfig::getInstance()->getKiType1Index())
    {
        for (int index = 0; index < mExecListOfficer.size(); index++)
        {
            if (!thereIsDifference || (mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() == (maxKiXAmount - 1)
                                       || mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() == (maxKiXAmount - 2)))
            {
                listLess.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            }
            else if (mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() == maxKiXAmount)
            {
                listMore.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            }
            else
            {
                LOG_DEBUG("WRONG NUMBER OF KI MONTH KiType1")
            }
        }
    }
    else if (kiType == KiConfig::getInstance()->getKiType2Index())
    {
        for (int index = 0; index < mExecListOfficer.size(); index++)
        {
            //list được chọn của Ki Type2 phải loại những người vừa được set Ki Type1 tháng này
            if ((!thereIsDifference || (mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() == (maxKiXAmount - 1)
                                        || mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() == (maxKiXAmount - 2)))
                && mExecListOfficer[index]->getKiXMonth(month) != KiConfig::getInstance()->getKiType1Symbol())
            {
                listLess.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            }
            else if ((mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() == maxKiXAmount)
                     && mExecListOfficer[index]->getKiXMonth(month) != KiConfig::getInstance()->getKiType1Symbol())
            {
                listMore.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            }
            else if (mExecListOfficer[index]->getKiXMonth(month) != KiConfig::getInstance()->getKiType1Symbol())
            {
                LOG_DEBUG("WRONG NUMBER OF KI MONTH KiType2")
            }
        }
    }
    else if (kiType == KiConfig::getInstance()->getKiType4Index())
    {
        for (int index = 0; index < mExecListOfficer.size(); index++)
        {
            //list được chọn của Ki Type4 phải loại những người vừa được set Ki Type1 & Ki Type2 tháng này
            if ((!thereIsDifference || (mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() == (maxKiXAmount - 1)
                                        || mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() == (maxKiXAmount - 2)))
                && mExecListOfficer[index]->getKiXMonth(month) != KiConfig::getInstance()->getKiType1Symbol()
                && mExecListOfficer[index]->getKiXMonth(month) != KiConfig::getInstance()->getKiType2Symbol())
            {
                listLess.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            }
            else if ((mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() == maxKiXAmount)
                     && mExecListOfficer[index]->getKiXMonth(month) != KiConfig::getInstance()->getKiType1Symbol()
                     && mExecListOfficer[index]->getKiXMonth(month) != KiConfig::getInstance()->getKiType2Symbol())
            {
                listMore.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            }
            else if (mExecListOfficer[index]->getKiXMonth(month) != KiConfig::getInstance()->getKiType1Symbol()
                     && mExecListOfficer[index]->getKiXMonth(month) != KiConfig::getInstance()->getKiType2Symbol())
            {
                LOG_DEBUG("WRONG NUMBER OF KI MONTH KiType4 ")
            }
        }
    }
}

void AdjustKiMethod::setKiType1AtMonthXOfQuarter(int month, QVector<int> listMore, QVector<int> listLess)
{
    //Tạo một list sắp xếp theo thứ tự
    //Người được KiType1 Quý này(from listLess) -> người không bị KiType4 Quý này và cũng không được KiType1 Quý này(from listLess) -> người bị KiType4 quý(from listLess) -> Những người nhiều hơn người khác 1 đơn vị Ki Type1 tháng.
    //Check từ đầu xuống cuối theo thuật toán pick Ki Type1 tháng 1 của a MungVH.
    QVector<QSharedPointer<Officer>> tempList;

    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        //Xét những người có Ki Type1 tháng ít hơn người khác 1 đơn vị trước
        if (listLess.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            //Cho những người có Ki Type1 quý này lên đầu
            if (mExecListOfficer[index]->getKiXQuarter(mThisQuarter) == KiConfig::getInstance()->getKiType1Symbol())
            {
                tempList.push_front(mExecListOfficer[index]);
            }
            //Cho những người có Ki Type4 quý này xuống cuối
            else if (mExecListOfficer[index]->getKiXQuarter(mThisQuarter) == KiConfig::getInstance()->getKiType4Symbol())
            {
                tempList.push_back(mExecListOfficer[index]);
            }
            //Những người còn lại là những người ko được Ki Type1 và D quý này thì cho vào giữa
            else
            {
                if (tempList.empty())
                {
                    tempList.push_back(mExecListOfficer[index]);
                }
                else
                {
                    for (int index1 = 0 ; index1 < tempList.size(); index1++)
                    {
                        //Tìm thấy người có Ki Type4 quý này thì nhét vào trước người này
                        if (tempList[index1]->getKiXQuarter(mThisQuarter) == KiConfig::getInstance()->getKiType4Symbol())
                        {
                            tempList.insert(tempList.begin() + index1, mExecListOfficer[index]);
                            break;
                        }

                        //Nếu người cuối cùng cũng không phải là Ki Type4 quý này thì nhét vào cuối
                        if (tempList[index1]->getKiXQuarter(mThisQuarter) != KiConfig::getInstance()->getKiType4Symbol() && index1 == tempList.size() - 1)
                        {
                            tempList.push_back(mExecListOfficer[index]);
                            break;
                        }
                    }
                }
            }
        }
    }

    //Thêm những người có Ki Type1 tháng hơn người khác một đơn vị vào cuối list
    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        if (listMore.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            tempList.push_back(mExecListOfficer[index]);
        }
    }

    //Thực thi phân phối Ki Type1 từ đầu đến cuối.
    int maxTargets = mKiType1People;

    for (int index1 = 0; index1 < tempList.size(); index1++)
    {
        for (int index2 = 0; index2 < mExecListOfficer.size(); index2++)
        {
            if (maxTargets > 0)
            {
                if (mExecListOfficer[index2]->getOfficerStt().toInt() == tempList[index1]->getOfficerStt().toInt())
                {
                    mExecListOfficer[index2]->insertKiXMonth(KiConfig::getInstance()->getKiType1Symbol(), month);
                    LOG_DEBUG("STT % d Get KiType1 in Month % d Quarter % d", mExecListOfficer[index2]->getOfficerStt().toInt(), month + 1, mThisQuarter + 1);
                    maxTargets--;
                }
            }
        }
    }
}
void AdjustKiMethod::setKiType2AtMonthXOfQuarter(int month, QVector<int> listMore, QVector<int> listLess)
{
    //Tạo một list sắp xếp theo thứ tự
    //Những người ít hơn người khác 1 đơn vị Ki Type2 tháng -> Những người nhiều hơn người khác 1 đơn vị Ki Type2 tháng (những người này đều chưa được xét Ki Type1 tháng này).
    //Check từ đầu xuống cuối theo thuật toán pick Ki Type2 tháng 1 của a MungVH.
    QVector<QSharedPointer<Officer>> tempList;

    //hững người ít hơn người khác 1 đơn vị Ki Type2 tháng lên đầu list
    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        if (listLess.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            tempList.push_front(mExecListOfficer[index]);
        }
    }

    //Thêm những người có Ki Type2 tháng hơn người khác một đơn vị vào cuối list
    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        if (listMore.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            tempList.push_back(mExecListOfficer[index]);
        }
    }

    //Thực thi phân phối Ki Type2 từ đầu đến cuối.
    int maxTargets = mKiType2People;

    for (int index1 = 0; index1 < tempList.size(); index1++)
    {
        for (int index2 = 0; index2 < mExecListOfficer.size(); index2++)
        {
            if (maxTargets > 0)
            {
                if (mExecListOfficer[index2]->getOfficerStt().toInt() == tempList[index1]->getOfficerStt().toInt())
                {
                    mExecListOfficer[index2]->insertKiXMonth(KiConfig::getInstance()->getKiType2Symbol(), month);
                    LOG_DEBUG("STT % d Get KiType2 in Month % d Quarter % d", mExecListOfficer[index2]->getOfficerStt().toInt(), month + 1, mThisQuarter + 1);
                    maxTargets--;
                }
            }
        }
    }
}

void AdjustKiMethod::setKiType4AtMonthXOfQuarter(int month, QVector<int> listMore, QVector<int> listLess)
{
    //Tạo một list sắp xếp theo thứ tự
    //Người được KiType4 Quý này(from listLess) -> người không bị KiType4 Quý này(from listLess) -> Những người nhiều hơn người khác 1 đơn vị Ki Type4 tháng.
    //Check từ đầu xuống cuối theo thuật toán pick Ki Type4 tháng 1 của a MungVH.
    QVector<QSharedPointer<Officer>> tempList;

    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        //Xét những người có Ki Type4 tháng ít hơn người khác 1 đơn vị trước
        if (listLess.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            //Cho những người có Ki Type4 quý này lên đầu
            if (mExecListOfficer[index]->getKiXQuarter(mThisQuarter) == KiConfig::getInstance()->getKiType4Symbol())
            {
                tempList.push_front(mExecListOfficer[index]);
            }

            //Cho những người ko có Ki Type4 quý này xuống cuối
            if (mExecListOfficer[index]->getKiXQuarter(mThisQuarter) != KiConfig::getInstance()->getKiType4Symbol())
            {
                tempList.push_back(mExecListOfficer[index]);
            }
        }
    }

    //Thêm những người có Ki Type4 tháng hơn người khác một đơn vị vào cuối list
    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        if (listMore.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            tempList.push_back(mExecListOfficer[index]);
        }
    }

    //Thực thi phân phối Ki Type4 từ đầu đến cuối.
    int maxTargets = mKiType4People;

    for (int index1 = 0; index1 < tempList.size(); index1++)
    {
        for (int index2 = 0; index2 < mExecListOfficer.size(); index2++)
        {
            if (maxTargets > 0)
            {
                if (mExecListOfficer[index2]->getOfficerStt().toInt() == tempList[index1]->getOfficerStt().toInt())
                {
                    mExecListOfficer[index2]->insertKiXMonth(KiConfig::getInstance()->getKiType4Symbol(), month);
                    LOG_DEBUG("STT % d Get KiType4 in Month % d Quarter % d", mExecListOfficer[index2]->getOfficerStt().toInt(), month + 1 , mThisQuarter + 1);
                    maxTargets--;
                }
            }
        }
    }
}
void AdjustKiMethod::setKiType3AtMonthXForLeftPeople(int month)
{
    for (int index = 0 ; index < mExecListOfficer.size(); index++)
    {
        if (mExecListOfficer[index]->getKiXMonth(month) == KI_NOT_SET)
        {
            mExecListOfficer[index]->insertKiXMonth(KiConfig::getInstance()->getKiType3Symbol(), month);
        }
    }
}

void AdjustKiMethod::embroilList(QVector<QSharedPointer<Officer> >& list)
{
    for (int index = 0; index < 30; index++)
    {
        int ranVal1 = randomIntergerInRange(0, list.size());
        int ranVal2 = randomIntergerInRange(0, list.size());
        QSharedPointer<Officer> temp = list[ranVal1];
        list[ranVal1] = list[ranVal2];
        list[ranVal2] = temp;
    }
}

void AdjustKiMethod::removeFixingKiOfficer()
{
    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        QString ki = mExecListOfficer[index]->getKiXQuarter(mThisQuarter);

        if (ki != KI_NOT_SET)
        {
            mListFixedKiOfficer.push_back(mExecListOfficer[index]);
            mExecListOfficer.remove(index);
            index--;

            if (ki == KiConfig::getInstance()->getKiType1Symbol())
            {
                mKiType1People --;
            }
            else if (ki == KiConfig::getInstance()->getKiType2Symbol())
            {
                mKiType2People--;
            }
            else if (ki == KiConfig::getInstance()->getKiType3Symbol())
            {
                mKiType3People--;
            }
            else if (ki == KiConfig::getInstance()->getKiType4Symbol())
            {
                mKiType4People--;
            }
            else
            {
                LOG_DEBUG("WRONG SYMBOL KI")
            }
        }
    }
}

void AdjustKiMethod::addFixingKiOfficer()
{
    mExecListOfficer.append(mListFixedKiOfficer);
}

void AdjustKiMethod::clearAllList()
{
    mExecListOfficer.clear();
    mListFixedKiOfficer.clear();
    mOfficerGetKiType4InThisSessionList.clear();
    mOfficerGetKiType1InThisSessionList.clear();
    mOfficerGetKiType2InThisSessionList.clear();
    mOfficerGetKiType3InThisSessionList.clear();
}

void AdjustKiMethod::resetKiPeople()
{
    // Tính cụ thể số lượng người cho từng loại KI
    mKiType1People = static_cast<int>(std::roundf(mKiType1Percent * mNumberOfOfficer / 100));
    mKiType2People = static_cast<int>(std::roundf(mKiType2Percent * mNumberOfOfficer / 100));
    mKiType4People = static_cast<int>(std::roundf(mKiType4Percent * mNumberOfOfficer / 100));
    mKiType3People = mNumberOfOfficer - mKiType1People - mKiType2People - mKiType4People;
}

void AdjustKiMethod::cleanKiMonth(int month)
{
    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        mExecListOfficer[index]->insertKiXMonth(KI_NOT_SET, month);
    }
}

void AdjustKiMethod::sortResult()
{
    std::sort(std::begin(mExecListOfficer), std::end(mExecListOfficer), std::less<Officer> {});
}

void AdjustKiMethod::adjustQuarterKi()
{
    //Lưu lại ai được Ki gì trong phiên trước đây
    QVector<int> listOfficerGotKiType1InOldSession;
    QVector<int> listOfficerGotKiType2InOldSession;
    QVector<int> listOfficerGotKiType4InOldSession;

    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        if (mExecListOfficer[index]->getKiXQuarter(mThisQuarter) == KiConfig::getInstance()->getKiType1Symbol())
        {
            listOfficerGotKiType1InOldSession.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            //Xóa đi trạng thái cập nhật KI trước đây của họ
            mExecListOfficer[index]->insertKiXStatus(KI_NOT_SET, KiConfig::getInstance()->getKiType1Index());
        }
        else if (mExecListOfficer[index]->getKiXQuarter(mThisQuarter) == KiConfig::getInstance()->getKiType2Symbol())
        {
            listOfficerGotKiType2InOldSession.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            //Xóa đi trạng thái cập nhật KI trước đây của họ
            mExecListOfficer[index]->insertKiXStatus(KI_NOT_SET, KiConfig::getInstance()->getKiType2Index());
        }
        else if (mExecListOfficer[index]->getKiXQuarter(mThisQuarter) == KiConfig::getInstance()->getKiType4Symbol())
        {
            listOfficerGotKiType4InOldSession.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            //Xóa đi trạng thái cập nhật KI trước đây của họ
            mExecListOfficer[index]->insertKiXStatus(KI_NOT_SET, KiConfig::getInstance()->getKiType4Index());
        }

        mExecListOfficer[index]->insertKiXQuarter(KI_NOT_SET, mThisQuarter);
    }

    //set lại Ki Type1
    //1.1 Chon ra tat ca nhung nguoi co the duoc Ki Type1
    QVector<int> candidateForKiType1ListStt = getCandidateForKiType1(listOfficerGotKiType1InOldSession);

    //1.2 Set Ki
    //Nếu số người trong danh sách chưa đạt Ki Type1 ít hơn số Ki Type1 cần tạo
    if (candidateForKiType1ListStt.size() < mKiType1People)
    {
        //thì toàn bộ số người trong sanh sách ở bước trên sẽ đạt Ki Type1
        setKiXQuaterStatusOfThemToYes(KiConfig::getInstance()->getKiType1Index(), candidateForKiType1ListStt);
        //và reset trạng thái Ki Type1 của toàn bộ số người đã đạt Ki Type1 khác về "Không"
        //roi đưa vào danh sách để random số Ki Type1 còn thiếu.
        QVector<int> randomList = setKiXQuaterStatusOfThemToNo(KiConfig::getInstance()->getKiType1Index(), candidateForKiType1ListStt);
        //random
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedList(mKiType1People, randomList);
        setKiXQuaterStatusOfThemToYes(KiConfig::getInstance()->getKiType1Index(), selectedOfficerAfterRandom);
        //Lưu lại những người được set KiType1 trong turn này để xử lý KiType2
        mOfficerGetKiType1InThisSessionList.append(candidateForKiType1ListStt);
        mOfficerGetKiType1InThisSessionList.append(selectedOfficerAfterRandom);
    }
    else
    {
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedListVer2(mKiType1People, candidateForKiType1ListStt, listOfficerGotKiType1InOldSession);
        setKiXQuaterStatusOfThemToYes(KiConfig::getInstance()->getKiType1Index(), selectedOfficerAfterRandom);
        //Lưu lại những người được set KiType1 trong turn này để xử lý KiType2
        mOfficerGetKiType1InThisSessionList.append(selectedOfficerAfterRandom);
    }

    //2. Set Ki Type2
    //2.1 Chon ra tat ca nhung nguoi co the duoc Ki Type2
    QVector<int> candidatesForKiType2ListStt = getCandidateForKiType2(mOfficerGetKiType1InThisSessionList, listOfficerGotKiType2InOldSession);
    QVector<int> officerGetKi12InThisSessionList;

    //2.2 Set Ki
    //Nếu số người trong danh sách co the duoc đạt Ki Type2 ít hơn số Ki Type2 cần tạo
    if (candidatesForKiType2ListStt.size() < mKiType2People)
    {
        //thì toàn bộ số người trong sanh sách ở bước trên sẽ đạt Ki Type2
        setKiXQuaterStatusOfThemToYes(KiConfig::getInstance()->getKiType2Index(), candidatesForKiType2ListStt);
        //và reset trạng thái Ki Type2 của toàn bộ số người đã đạt Ki Type2 khác về "Không"
        //roi đưa vào danh sách để random số Ki Type2 còn thiếu.
        QVector<int> randomList = setKiXQuaterStatusOfThemToNo(KiConfig::getInstance()->getKiType2Index(), candidatesForKiType2ListStt);
        //random
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedList(mKiType2People, randomList);
        setKiXQuaterStatusOfThemToYes(KiConfig::getInstance()->getKiType2Index(), selectedOfficerAfterRandom);
        //Lưu lại những người được set KiType1B trong turn này để xử lý Ki Type4
        officerGetKi12InThisSessionList.append(candidatesForKiType2ListStt);
        officerGetKi12InThisSessionList.append(selectedOfficerAfterRandom);
        mOfficerGetKiType2InThisSessionList = officerGetKi12InThisSessionList;
        officerGetKi12InThisSessionList.append(mOfficerGetKiType1InThisSessionList);
    }
    //Nếu số người trong danh sách co the duoc đạt Ki Type2 nhiều hơn hoặc bằng số Ki Type2 cần tạo
    else
    {
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedListVer2(mKiType2People, candidatesForKiType2ListStt, listOfficerGotKiType2InOldSession);
        setKiXQuaterStatusOfThemToYes(KiConfig::getInstance()->getKiType2Index(), selectedOfficerAfterRandom);
        //Lưu lại những người được set KiType1B trong turn này để xử lý KiType4
        officerGetKi12InThisSessionList.append(selectedOfficerAfterRandom);
        mOfficerGetKiType2InThisSessionList = officerGetKi12InThisSessionList;
        officerGetKi12InThisSessionList.append(mOfficerGetKiType1InThisSessionList);
    }

    //3. Set KiType4
    //3.1 Chon ra tat ca nhung nguoi co the duoc Ki Type4
    QVector<int> candidatesForKiType4ListStt = getCandidateForKiType4(officerGetKi12InThisSessionList, listOfficerGotKiType4InOldSession);
    QVector<int> officerGetKi124InThisSessionList;

    //3.2 Set Ki
    //Nếu số người trong danh sách co the duoc đạt Ki Type4 ít hơn số Ki Type4 cần tạo
    if (candidatesForKiType4ListStt.size() < mKiType4People)
    {
        //thì toàn bộ số người trong sanh sách ở bước trên sẽ đạt Ki Type2
        setKiXQuaterStatusOfThemToYes(KiConfig::getInstance()->getKiType4Index(), candidatesForKiType4ListStt);
        //và reset trạng thái Ki Type2 của toàn bộ số người đã đạt Ki Type4 khác về "Không"
        //roi đưa vào danh sách để random số Ki Type4 còn thiếu.
        QVector<int> randomList = setKiXQuaterStatusOfThemToNo(KiConfig::getInstance()->getKiType4Index(), candidatesForKiType4ListStt);
        //random
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedList(mKiType4People, randomList);
        setKiXQuaterStatusOfThemToYes(KiConfig::getInstance()->getKiType4Index(), selectedOfficerAfterRandom);
        //Lưu lại những người được set Ki124 trong turn này để xử lý Ki Type3
        officerGetKi124InThisSessionList.append(candidatesForKiType4ListStt);
        officerGetKi124InThisSessionList.append(selectedOfficerAfterRandom);
        mOfficerGetKiType4InThisSessionList = officerGetKi124InThisSessionList;
        officerGetKi124InThisSessionList.append(officerGetKi12InThisSessionList);
    }
    //Nếu số người trong danh sách co the duoc đạt Ki Type4 nhiều hơn hoặc bằng số Ki Type4 cần tạo
    else
    {
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedListVer2(mKiType4People, candidatesForKiType4ListStt, listOfficerGotKiType4InOldSession);
        setKiXQuaterStatusOfThemToYes(KiConfig::getInstance()->getKiType4Index(), selectedOfficerAfterRandom);
        //Lưu lại những người được set KiType1B trong turn này để xử lý KiType4
        officerGetKi124InThisSessionList.append(selectedOfficerAfterRandom);
        mOfficerGetKiType4InThisSessionList = officerGetKi124InThisSessionList;
        officerGetKi124InThisSessionList.append(officerGetKi12InThisSessionList);
    }

    //4. Set KiType3
    //Mặc định những người còn lại trong danh sách là Ki Type3.
    QVector<int> candidatesForKiType3ListStt = getCandidateForKiType3(officerGetKi124InThisSessionList);
    setKiXQuaterStatusOfThemToYes(KiConfig::getInstance()->getKiType3Index(), candidatesForKiType3ListStt);
    mOfficerGetKiType3InThisSessionList.append(candidatesForKiType3ListStt);
    LOG_DEBUG("Ki Type1 = %d ng, Ki Type2 = %d ng, Ki Type3 =%d ng, Ki Type4 = %d ng",
              mOfficerGetKiType1InThisSessionList.size(), mOfficerGetKiType2InThisSessionList.size(),
              mOfficerGetKiType3InThisSessionList.size(), mOfficerGetKiType4InThisSessionList.size())
}

bool AdjustKiMethod::kiRateInputIsOk(QString& issue)
{
    if (mIsPercentMode)
    {
        // Tính cụ thể số lượng người cho từng loại KI
        mKiType1People = static_cast<int>(std::roundf(mKiType1Percent * mNumberOfOfficer / 100));
        mKiType2People = static_cast<int>(std::roundf(mKiType2Percent * mNumberOfOfficer / 100));
        mKiType4People = static_cast<int>(std::roundf(mKiType4Percent * mNumberOfOfficer / 100));

        if (mKiType1Percent + mKiType2Percent + mKiType4Percent > 100.0)
        {
            issue = "Tỷ lệ % Ki chưa đúng";
            return false;
        }

        mKiType3People = mNumberOfOfficer - mKiType1People - mKiType2People - mKiType4People;
        mKiType3Percent = 100 - mKiType1Percent - mKiType2Percent - mKiType4Percent;
        LOG_DEBUG("Convert percent to number of people, result: mKiType1People = %d, mKiType2People = %d, mKiType3People = %d, mKiType4People = %d",
                  mKiType1People, mKiType2People, mKiType3People, mKiType4People)
    }
    else
    {
        mKiType1Percent = mKiType1People * 100 / mNumberOfOfficer;
        mKiType2Percent = mKiType2People * 100 / mNumberOfOfficer ;
        mKiType4Percent = mKiType4People * 100 / mNumberOfOfficer ;

        if (mNumberOfOfficer < mKiType1People + mKiType2People + mKiType4People)
        {
            issue = "Phân phối KI theo số người chưa đúng";
            issue += "\nTổng số nhân viên cần phân phối KI là: ";
            issue += QString::number(mNumberOfOfficer);
            return false;
        }

        mKiType3People = mNumberOfOfficer - mKiType1People - mKiType4People - mKiType2People;
        mKiType3Percent = 100 - mKiType1Percent - mKiType2Percent - mKiType4Percent;
    }

    return true;
}


QVector<int> AdjustKiMethod::getCandidateForKiType3(const QVector<int>& listSetKi124ThisSesson)
{
    QVector<int> listCandidateKiType3;

    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        //Tất cả những người đạt Ki 1,4,2 this round
        if (!listSetKi124ThisSesson.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            listCandidateKiType3.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
        }
    }

    return listCandidateKiType3;
}
