#include "createkimethod.h"

CreateKiMethod::CreateKiMethod()
{
}

CreateKiMethod::~CreateKiMethod()
{
}

bool CreateKiMethod::process(QString& issue)
{
    clearAllList();
    //Khởi tạo 1 list mới để xử lý.
    cloneData(mOfficialListOfficer, mExecListOfficer);
    //Tinh so luong nhan vien trong danh sach
    mNumberOfOfficer = mExecListOfficer.size();

    if (!kiRatioInputIsOk(issue))
    {
        return false;
    }

    // Loại bỏ những người được fix Ki từ trước
    removeFixedKiOfficer();
    // Tinh ki quy
    generateQuarterKi();
    //reset kiPeople
    resetKiPeople();
    // Thêm lại những người được fix KI vào danh sách để tính KI tháng
    addFixingKiOfficer();
    //gen ki tháng
    generateMonthlyKi(convertQuarterToFirstMonth(mThisQuarter));
    generateMonthlyKi(convertQuarterToSecondMonth(mThisQuarter));
    generateMonthlyKi(convertQuarterToThirdMonth(mThisQuarter));
    sortResult();

    //logger
    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        mExecListOfficer[index]->logData();
    }

    return true;
}

void CreateKiMethod::setKiPeople(int kiType1People, int kiType2People, int kiType3People, int kiType4People)
{
    mKiType1People = kiType1People;
    mKiType2People = kiType2People;
    mKiType3People = kiType3People;
    mKiType4People = kiType4People;
}

void CreateKiMethod::setKiPercent(float kiType1Percent, float kiType2Percent, float kiType3Percent, float kiType4Percent)
{
    mKiType1Percent = kiType1Percent;
    mKiType2Percent = kiType2Percent;
    mKiType3Percent = kiType3Percent;
    mKiType4Percent = kiType4Percent;
}

void CreateKiMethod::setThisQuarter(int quarter)
{
    mThisQuarter = quarter;
}

int CreateKiMethod::getThisQuarter()
{
    return mThisQuarter;
}

void CreateKiMethod::setIsPercentMode(bool isPercentMode)
{
    mIsPercentMode = isPercentMode;
}

void CreateKiMethod::setNumberOfOfficer(int num)
{
    mNumberOfOfficer = num;
}

void CreateKiMethod::setUpMode()
{
    if (mOfficialListOfficer[0]->getKiXQuarter(QUARTER1) == KI_NOT_SET)
    {
        mThisQuarter =  QUARTER1;
    }
    else if (mOfficialListOfficer[0]->getKiXQuarter(QUARTER2) == KI_NOT_SET)
    {
        mThisQuarter = QUARTER2;
    }
    else if (mOfficialListOfficer[0]->getKiXQuarter(QUARTER3) == KI_NOT_SET)
    {
        mThisQuarter = QUARTER3;
    }
    else if (mOfficialListOfficer[0]->getKiXQuarter(QUARTER4) == KI_NOT_SET)
    {
        mThisQuarter = QUARTER4;
    }
    else
    {
        mThisQuarter = QUARTER1;
    }

    if (mThisQuarter == QUARTER1)
    {
        resetForARewYear(mOfficialListOfficer);
    }
}

QVector<QSharedPointer<Officer> > CreateKiMethod::getResult()
{
    return mExecListOfficer;
}

void CreateKiMethod::setOfficialListOfficer(const QVector<QSharedPointer<Officer> >& list)
{
    mOfficialListOfficer = list;
}

void CreateKiMethod::updateFixingList(const QString& id, const QString& ki)
{
    for (int index = 0; index < mOfficialListOfficer.size(); index++)
    {
        if (mOfficialListOfficer[index]->getOfficerId() == id)
        {
            mOfficialListOfficer[index]->insertKiXQuarter(ki, mThisQuarter);
            break;
        }
    }
}


void CreateKiMethod::setKiXQuaterStatusOfThemToYes(int kiType, const QVector<int>& listOfficerStt)
{
    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        if (listOfficerStt.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            //*decrease
            switch (kiType)
            {
                case KI_TYPE1:
                    if (mKiType1People > 0)
                    {
                        mExecListOfficer[index]->insertKiXQuarter(KI_TYPE1_SYMBOL, mThisQuarter);
                        LOG_DEBUG("STT %d Get KiType1 in Quarter %d", mExecListOfficer[index]->getOfficerStt().toInt(), mThisQuarter + 1);
                        mKiType1People--;
                    }

                    break;

                case KI_TYPE2:
                    if (mKiType2People > 0)
                    {
                        mExecListOfficer[index]->insertKiXQuarter(KiConfig::getInstance()->getKiType2Symbol(), mThisQuarter);
                        LOG_DEBUG("STT %d Get KiType2 in Quarter %d", mExecListOfficer[index]->getOfficerStt().toInt(), mThisQuarter + 1);
                        mKiType2People--;
                    }

                    break;

                case KI_TYPE3:
                    if (mKiType3People > 0)
                    {
                        mExecListOfficer[index]->insertKiXQuarter(KiConfig::getInstance()->getKiType3Symbol(), mThisQuarter);
                        LOG_DEBUG("STT %d Get KiType3 in Quarter %d", mExecListOfficer[index]->getOfficerStt().toInt(), mThisQuarter + 1);
                        mKiType3People--;
                    }

                    break;

                case KI_TYPE4:
                    if (mKiType4People > 0)
                    {
                        mExecListOfficer[index]->insertKiXQuarter(KiConfig::getInstance()->getKiType4Symbol(), mThisQuarter);
                        LOG_DEBUG("STT %d Get KiType4 in Quarter %d", mExecListOfficer[index]->getOfficerStt().toInt(), mThisQuarter + 1);
                        mKiType4People--;
                    }

                    break;

                default:
                    break;
            }
        }
    }
}

QVector<int> CreateKiMethod::setKiXQuaterStatusOfThemToNo(int kiType, const QVector<int>& listOfficerStt)
{
    QVector<int> randomList;

    //reset trạng thái Ki X của toàn bộ những người ko được fix cứng KI
    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        if (!listOfficerStt.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            switch (kiType)
            {
                case KI_TYPE1:
                    if (mKiType1People > 0)
                    {
                        mExecListOfficer[index]->insertKiXStatus(NO, KI_TYPE1);
                        randomList.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
                    }

                    break;

                case KI_TYPE2:
                    if (mKiType2People > 0)
                    {
                        mExecListOfficer[index]->insertKiXStatus(NO, KI_TYPE2);

                        if (!mOfficerGetKiType1InThisSessionList.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
                        {
                            randomList.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
                        }
                    }

                    break;

                case KI_TYPE3:
                    if (mKiType3People > 0)
                    {
                        mExecListOfficer[index]->insertKiXStatus(NO, KI_TYPE3);
                        randomList.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
                    }

                    break;

                case KI_TYPE4:
                    if (mKiType4People > 0)
                    {
                        mExecListOfficer[index]->insertKiXStatus(NO, KI_TYPE4);

                        if (!mOfficerGetKiType1InThisSessionList.contains(mExecListOfficer[index]->getOfficerStt().toInt()) &&
                            !mOfficerGetKiType2InThisSessionList.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
                        {
                            randomList.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
                        }
                    }

                    break;

                default:
                    break;
            }
        }
    }

    return randomList;
}

void CreateKiMethod::generateQuarterKi()
{
    //1. Set Ki loai 1
    //1.1 Chon ra tat ca nhung nguoi co the duoc ki loai 1
    QVector<int> candidateForKiType1ListStt = getCandidateForKiType1();

    //1.2 Set Ki
    //Nếu số người trong danh sách chưa đạt Ki loai 1 ít hơn số Ki loai 1 cần tạo
    if (candidateForKiType1ListStt.size() < mKiType1People)
    {
        //thì toàn bộ số người trong sanh sách ở bước trên sẽ đạt Ki loai 1
        setKiXQuaterStatusOfThemToYes(KI_TYPE1, candidateForKiType1ListStt);
        //và reset trạng thái Ki loai 1 của toàn bộ số người đã đạt Ki loai 1 khác về "Không"
        //roi đưa vào danh sách để random số Ki loai 1 còn thiếu.
        QVector<int> randomList = setKiXQuaterStatusOfThemToNo(KI_TYPE1, candidateForKiType1ListStt);
        //random
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedList(mKiType1People, randomList);
        setKiXQuaterStatusOfThemToYes(KI_TYPE1, selectedOfficerAfterRandom);
        //Lưu lại những người được set KiType1 trong turn này để xử lý KiType2
        mOfficerGetKiType1InThisSessionList.append(candidateForKiType1ListStt);
        mOfficerGetKiType1InThisSessionList.append(selectedOfficerAfterRandom);
    }
    else //Nếu số người trong danh sách chưa đạt KiType1 nhiều hơn hoặc bằng số KiType1 cần tạo
    {
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedList(mKiType1People, candidateForKiType1ListStt);
        setKiXQuaterStatusOfThemToYes(KI_TYPE1, selectedOfficerAfterRandom);
        //Lưu lại những người được set KiType1 trong turn này để xử lý KiType2
        mOfficerGetKiType1InThisSessionList.append(selectedOfficerAfterRandom);
    }

    //2. Set Ki Type2
    //2.1 Chon ra tat ca nhung nguoi co the duoc Ki Type2
    QVector<int> candidatesForKiType2ListStt = getCandidateForKiType2(mOfficerGetKiType1InThisSessionList);
    QVector<int> officerGetKi12InThisSessionList;

    //2.2 Set Ki
    //Nếu số người trong danh sách co the duoc đạt Ki Type2 ít hơn số Ki Type2 cần tạo
    if (candidatesForKiType2ListStt.size() < mKiType2People)
    {
        //thì toàn bộ số người trong sanh sách ở bước trên sẽ đạt Ki Type2
        setKiXQuaterStatusOfThemToYes(KI_TYPE2, candidatesForKiType2ListStt);
        //và reset trạng thái Ki Type2 của toàn bộ số người đã đạt Ki Type2 khác về "Không"
        //roi đưa vào danh sách để random số Ki Type2 còn thiếu.
        QVector<int> randomList = setKiXQuaterStatusOfThemToNo(KI_TYPE2, candidatesForKiType2ListStt);
        //random
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedList(mKiType2People, randomList);
        setKiXQuaterStatusOfThemToYes(KI_TYPE2, selectedOfficerAfterRandom);
        //Lưu lại những người được set Ki12 trong turn này để xử lý Ki Type4
        officerGetKi12InThisSessionList.append(candidatesForKiType2ListStt);
        officerGetKi12InThisSessionList.append(selectedOfficerAfterRandom);
        mOfficerGetKiType2InThisSessionList = officerGetKi12InThisSessionList;
        officerGetKi12InThisSessionList.append(mOfficerGetKiType1InThisSessionList);
    }
    //Nếu số người trong danh sách co the duoc đạt Ki Type2 nhiều hơn hoặc bằng số Ki Type2 cần tạo
    else
    {
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedList(mKiType2People, candidatesForKiType2ListStt);
        setKiXQuaterStatusOfThemToYes(KI_TYPE2, selectedOfficerAfterRandom);
        //Lưu lại những người được set Ki12 trong turn này để xử lý KiType4
        officerGetKi12InThisSessionList.append(selectedOfficerAfterRandom);
        mOfficerGetKiType2InThisSessionList = officerGetKi12InThisSessionList;
        officerGetKi12InThisSessionList.append(mOfficerGetKiType1InThisSessionList);
    }

    //3. Set KiType4
    //3.1 Chon ra tat ca nhung nguoi co the duoc Ki Type4
    QVector<int> candidatesForKiType4ListStt = getCandidateForKiType4(officerGetKi12InThisSessionList);
    QVector<int> officerGetKi124InThisSessionList;

    //3.2 Set Ki
    //Nếu số người trong danh sách co the duoc đạt Ki Type4 ít hơn số Ki Type4 cần tạo
    if (candidatesForKiType4ListStt.size() < mKiType4People)
    {
        //thì toàn bộ số người trong sanh sách ở bước trên sẽ đạt Ki Type4
        setKiXQuaterStatusOfThemToYes(KI_TYPE4, candidatesForKiType4ListStt);
        //và reset trạng thái Ki Type4 của toàn bộ số người đã đạt Ki Type4 khác về "Không"
        //roi đưa vào danh sách để random số Ki Type4 còn thiếu.
        QVector<int> randomList = setKiXQuaterStatusOfThemToNo(KI_TYPE4, candidatesForKiType4ListStt);
        //random
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedList(mKiType4People, randomList);
        setKiXQuaterStatusOfThemToYes(KI_TYPE4, selectedOfficerAfterRandom);
        //Lưu lại những người được set Ki124 trong turn này để xử lý Ki Type3
        officerGetKi124InThisSessionList.append(candidatesForKiType4ListStt);
        officerGetKi124InThisSessionList.append(selectedOfficerAfterRandom);
        mOfficerGetKiType4InThisSessionList = officerGetKi124InThisSessionList;
        officerGetKi124InThisSessionList.append(officerGetKi12InThisSessionList);
    }
    //Nếu số người trong danh sách co the duoc đạt Ki Type4 nhiều hơn hoặc bằng số Ki Type4 cần tạo
    else
    {
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedList(mKiType4People, candidatesForKiType4ListStt);
        setKiXQuaterStatusOfThemToYes(KI_TYPE4, selectedOfficerAfterRandom);
        //Lưu lại những người được set Ki12 trong turn này để xử lý KiType4
        officerGetKi124InThisSessionList.append(selectedOfficerAfterRandom);
        mOfficerGetKiType4InThisSessionList = officerGetKi124InThisSessionList;
        officerGetKi124InThisSessionList.append(officerGetKi12InThisSessionList);
    }

    //4. Set KiType3
    //Mặc định những người còn lại trong danh sách là Ki Type3.
    QVector<int> candidatesForKiType3ListStt = getCandidateForKiType3(officerGetKi124InThisSessionList);
    setKiXQuaterStatusOfThemToYes(KI_TYPE3, candidatesForKiType3ListStt);
    mOfficerGetKiType3InThisSessionList.append(candidatesForKiType3ListStt);
    LOG_DEBUG("Ki Type1 = %d ng, Ki Type2 = %d ng, Ki Type3 =%d ng, Ki Type4 = %d ng",
              mOfficerGetKiType1InThisSessionList.size(), mOfficerGetKiType2InThisSessionList.size(),
              mOfficerGetKiType3InThisSessionList.size(), mOfficerGetKiType4InThisSessionList.size())
}

void CreateKiMethod::generateMonthlyKi(int month)
{
    //0.  Xáo trộn list này nhân viên trước khi chạy thuật toán
    embroilList(mExecListOfficer);
    //1   Set KiType1
    //1.1 Chọn danh sách những người có tổng số Ki Type1 của tháng ít hơn những người còn lại 1 đơn vị.
    QVector<int> peopleHavingLessThanOtherOneUnitOfKiType1;
    QVector<int> peopleHavingMoreThanOtherOneUnitOfKiType1;
    getPeopleHavingLessThanAndMoreThanOtherOneUintOfKiX(KI_TYPE1, month, peopleHavingLessThanOtherOneUnitOfKiType1, peopleHavingMoreThanOtherOneUnitOfKiType1);
    //1.2 Thực thi
    setKiType1AtMonthXOfQuarter(month, peopleHavingMoreThanOtherOneUnitOfKiType1, peopleHavingLessThanOtherOneUnitOfKiType1);
    //2   Set KiType2
    //2.1 Chọn danh sách những người có tổng số Ki Type2 của tháng ít hơn những người còn lại 1 đơn vị.
    QVector<int> peopleHavingLessThanOtherOneUnitOfKiType2;
    QVector<int> peopleHavingMoreThanOtherOneUnitOfKiType2;
    getPeopleHavingLessThanAndMoreThanOtherOneUintOfKiX(KI_TYPE2, month, peopleHavingLessThanOtherOneUnitOfKiType2, peopleHavingMoreThanOtherOneUnitOfKiType2);
    //2.2 Thực thi
    setKiType2AtMonthXOfQuarter(month, peopleHavingMoreThanOtherOneUnitOfKiType2, peopleHavingLessThanOtherOneUnitOfKiType2);
    //3   Set KiType4
    //3.1 Chọn danh sách những người có tổng số Ki Type4 của tháng ít hơn những người còn lại 1 đơn vị.
    QVector<int> peopleHavingLessThanOtherOneUnitOfKiType4;
    QVector<int> peopleHavingMoreThanOtherOneUnitOfKiType4;
    getPeopleHavingLessThanAndMoreThanOtherOneUintOfKiX(KI_TYPE4, month, peopleHavingLessThanOtherOneUnitOfKiType4, peopleHavingMoreThanOtherOneUnitOfKiType4);
    //3.2 Thực thi
    setKiType4AtMonthXOfQuarter(month, peopleHavingMoreThanOtherOneUnitOfKiType4, peopleHavingLessThanOtherOneUnitOfKiType4);
    //4.  Set KiType3
    setKiType3AtMonthXForLeftPeople(month);
}

void CreateKiMethod::getPeopleHavingLessThanAndMoreThanOtherOneUintOfKiX(int kiType, int month, QVector<int>& listLess, QVector<int>& listMore)
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

    if (kiType == KI_TYPE1)
    {
        for (int index = 0; index < mExecListOfficer.size(); index++)
        {
            if (!thereIsDifference || (mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() < maxKiXAmount))
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
    else if (kiType == KI_TYPE2)
    {
        for (int index = 0; index < mExecListOfficer.size(); index++)
        {
            //list được chọn của Ki Type2 phải loại những người vừa được set Ki Type1 tháng này
            if ((!thereIsDifference || (mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() < maxKiXAmount))
                && mExecListOfficer[index]->getKiXMonth(month) != KI_TYPE1_SYMBOL)
            {
                listLess.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            }
            else if ((mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() == maxKiXAmount)
                     && mExecListOfficer[index]->getKiXMonth(month) != KI_TYPE1_SYMBOL)
            {
                listMore.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            }
            else if (mExecListOfficer[index]->getKiXMonth(month) != KI_TYPE1_SYMBOL)
            {
                LOG_DEBUG("WRONG NUMBER OF KI MONTH KiType2")
            }
        }
    }
    else if (kiType == KI_TYPE4)
    {
        for (int index = 0; index < mExecListOfficer.size(); index++)
        {
            //list được chọn của Ki Type4 phải loại những người vừa được set Ki Type1 & Ki Type2 tháng này
            if ((!thereIsDifference || (mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() < maxKiXAmount))
                && mExecListOfficer[index]->getKiXMonth(month) != KI_TYPE1_SYMBOL
                && mExecListOfficer[index]->getKiXMonth(month) != KiConfig::getInstance()->getKiType2Symbol())
            {
                listLess.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            }
            else if ((mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() == maxKiXAmount)
                     && mExecListOfficer[index]->getKiXMonth(month) != KI_TYPE1_SYMBOL
                     && mExecListOfficer[index]->getKiXMonth(month) != KiConfig::getInstance()->getKiType2Symbol())
            {
                listMore.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            }
            else if (mExecListOfficer[index]->getKiXMonth(month) != KI_TYPE1_SYMBOL
                     && mExecListOfficer[index]->getKiXMonth(month) != KiConfig::getInstance()->getKiType2Symbol())
            {
                LOG_DEBUG("WRONG NUMBER OF KI MONTH KiType4 ")
            }
        }
    }
}

void CreateKiMethod::setKiType1AtMonthXOfQuarter(int month, QVector<int> listMore, QVector<int> listLess)
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
            if (mExecListOfficer[index]->getKiXQuarter(mThisQuarter) == KI_TYPE1_SYMBOL)
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
                    mExecListOfficer[index2]->insertKiXMonth(KI_TYPE1_SYMBOL, month);
                    LOG_DEBUG("STT % d Get KiType1 in Month % d Quarter % d", mExecListOfficer[index2]->getOfficerStt().toInt(), month + 1, mThisQuarter + 1);
                    maxTargets--;
                }
            }
        }
    }
}

void CreateKiMethod::setKiType2AtMonthXOfQuarter(int month, QVector<int> listMore, QVector<int> listLess)
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

void CreateKiMethod::setKiType4AtMonthXOfQuarter(int month, QVector<int> listMore, QVector<int> listLess)
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

void CreateKiMethod::setKiType3AtMonthXForLeftPeople(int month)
{
    for (int index = 0 ; index < mExecListOfficer.size(); index++)
    {
        if (mExecListOfficer[index]->getKiXMonth(month) == KI_NOT_SET)
        {
            mExecListOfficer[index]->insertKiXMonth(KiConfig::getInstance()->getKiType3Symbol(), month);
        }
    }
}

void CreateKiMethod::embroilList(QVector<QSharedPointer<Officer> >& list)
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

void CreateKiMethod::removeFixedKiOfficer()
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

void CreateKiMethod::addFixingKiOfficer()
{
    mExecListOfficer.append(mListFixedKiOfficer);
}

void CreateKiMethod::clearAllList()
{
    mExecListOfficer.clear();
    mListFixedKiOfficer.clear();
    mOfficerGetKiType4InThisSessionList.clear();
    mOfficerGetKiType1InThisSessionList.clear();
    mOfficerGetKiType2InThisSessionList.clear();
    mOfficerGetKiType3InThisSessionList.clear();
}

void CreateKiMethod::resetKiPeople()
{
    // Tính cụ thể số lượng người cho từng loại KI
    mKiType1People = static_cast<int>(std::roundf(mKiType1Percent * mNumberOfOfficer / 100));
    mKiType2People = static_cast<int>(std::roundf(mKiType2Percent * mNumberOfOfficer / 100));
    mKiType4People = static_cast<int>(std::roundf(mKiType4Percent * mNumberOfOfficer / 100));
    mKiType3People = mNumberOfOfficer - mKiType1People - mKiType2People - mKiType4People;
}

void CreateKiMethod::sortResult()
{
    std::sort(std::begin(mExecListOfficer), std::end(mExecListOfficer), std::less<Officer> {});
}

bool CreateKiMethod::kiRatioInputIsOk(QString& issue)
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

void CreateKiMethod::resetForARewYear(QVector<QSharedPointer<Officer> >& list)
{
    for (int index = 0; index < list.size(); index++)
    {
        list[index]->resetData();
    }
}




QVector<int> CreateKiMethod::getCandidateForKiType1()
{
    QVector<int> listOfficerNotGetKiType1;

    for (auto officer = mExecListOfficer.begin(); officer != mExecListOfficer.end(); officer++)
    {
        if (officer->data()->getKiXStatus(KI_TYPE1) != YES)
        {
            listOfficerNotGetKiType1.push_back(officer->data()->getOfficerStt().toInt());
        }
    }

    return listOfficerNotGetKiType1;
}

QVector<int> CreateKiMethod::getCandidateForKiType2(const QVector<int>& listSetKiType1ThisSession)
{
    QVector<int> listCandidateKiType2;

    for (auto officer = mExecListOfficer.begin(); officer != mExecListOfficer.end(); officer++)
    {
        if (!listSetKiType1ThisSession.contains(officer->data()->getOfficerStt().toInt())
            && officer->data()->getKiXStatus(KI_TYPE2) != YES)
        {
            listCandidateKiType2.push_back(officer->data()->getOfficerStt().toInt());
        }
    }

    return listCandidateKiType2;
}

QVector<int> CreateKiMethod::getCandidateForKiType4(const QVector<int>& listSetKiType12ThisSesson)
{
    QVector<int> listCandidateKiType4;

    for (auto officer = mExecListOfficer.begin(); officer != mExecListOfficer.end(); officer++)
    {
        if (!listSetKiType12ThisSesson.contains(officer->data()->getOfficerStt().toInt())
            && officer->data()->getKiXStatus(KI_TYPE4) != YES)
        {
            listCandidateKiType4.push_back(officer->data()->getOfficerStt().toInt());
        }
    }

    return listCandidateKiType4;
}

QVector<int> CreateKiMethod::getCandidateForKiType3(const QVector<int>& listSetKi124ThisSesson)
{
    QVector<int> listCandidateKiType3;

    for (auto officer = mExecListOfficer.begin(); officer != mExecListOfficer.end(); officer++)
    {
        if (!listSetKi124ThisSesson.contains(officer->data()->getOfficerStt().toInt()))
        {
            listCandidateKiType3.push_back(officer->data()->getOfficerStt().toInt());
        }
    }

    return listCandidateKiType3;
}
