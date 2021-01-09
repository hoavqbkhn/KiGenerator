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

    //===============================================================
    //Kiểm tra tỷ lệ Ki trước và hiện tại
    //checKiRateBeforeAndCurrent();
    // Loại bỏ những người được fix Ki từ trước (Ở case này thì đây là những người không bị điều chỉnh Ki)
    //removeFixingKiOfficer();
    // Tinh ki quy
    //generateQuarterKi();
    //===============================================================
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

void AdjustKiMethod::setKiPeople(int kiAPeople, int kiBPeople, int kiCPeople, int kiDPeople)
{
    mKiAPeople = kiAPeople;
    mKiBPeople = kiBPeople;
    mKiCPeople = kiCPeople;
    mKiDPeople = kiDPeople;
}

void AdjustKiMethod::setKiPercent(float kiAPercent, float kiBPercent, float kiCPercent, float kiDPercent)
{
    mKiAPercent = kiAPercent;
    mKiBPercent = kiBPercent;
    mKiCPercent = kiCPercent;
    mKiDPercent = kiDPercent;
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
            switch (kiType)
            {
                case KI_A:
                    if (mKiAPeople > 0)
                    {
                        mExecListOfficer[index]->insertKiXQuarter(KI_A_SYMBOL, mThisQuarter);
                        LOG_DEBUG("STT %d Get KiA in Quarter %d", mExecListOfficer[index]->getOfficerStt().toInt(), mThisQuarter + 1);
                        mKiAPeople--;
                    }

                    break;

                case KI_B:
                    if (mKiBPeople > 0)
                    {
                        mExecListOfficer[index]->insertKiXQuarter(KI_B_SYMBOL, mThisQuarter);
                        LOG_DEBUG("STT %d Get KiB in Quarter %d", mExecListOfficer[index]->getOfficerStt().toInt(), mThisQuarter + 1);
                        mKiBPeople--;
                    }

                    break;

                case KI_C:
                    if (mKiCPeople > 0)
                    {
                        mExecListOfficer[index]->insertKiXQuarter(KI_C_SYMBOL, mThisQuarter);
                        LOG_DEBUG("STT %d Get KiC in Quarter %d", mExecListOfficer[index]->getOfficerStt().toInt(), mThisQuarter + 1);
                        mKiCPeople--;
                    }

                    break;

                case KI_D:
                    if (mKiDPeople > 0)
                    {
                        mExecListOfficer[index]->insertKiXQuarter(KI_D_SYMBOL, mThisQuarter);
                        LOG_DEBUG("STT %d Get KiD in Quarter %d", mExecListOfficer[index]->getOfficerStt().toInt(), mThisQuarter + 1);
                        mKiDPeople--;
                    }

                    break;

                default:
                    break;
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
            switch (kiType)
            {
                case KI_A:
                    if (mKiAPeople > 0)
                    {
                        mExecListOfficer[index]->insertKiXStatus(NO, KI_A);
                        randomList.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
                    }

                    break;

                case KI_B:
                    if (mKiBPeople > 0)
                    {
                        mExecListOfficer[index]->insertKiXStatus(NO, KI_B);

                        if (!mOfficerGetKiAInThisSessionList.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
                        {
                            randomList.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
                        }
                    }

                    break;

                case KI_C:
                    if (mKiCPeople > 0)
                    {
                        mExecListOfficer[index]->insertKiXStatus(NO, KI_C);
                        randomList.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
                    }

                    break;

                case KI_D:
                    if (mKiDPeople > 0)
                    {
                        mExecListOfficer[index]->insertKiXStatus(NO, KI_D);

                        if (!mOfficerGetKiAInThisSessionList.contains(mExecListOfficer[index]->getOfficerStt().toInt()) &&
                            !mOfficerGetKiBInThisSessionList.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
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
void AdjustKiMethod::generateMonthlyKi(int month)
{
    //0.  Xáo trộn list này nhân viên trước khi chạy thuật toán
    embroilList(mExecListOfficer);
    //1   Set KiA
    //1.1 Chọn danh sách những người có tổng số Ki A của tháng ít hơn những người còn lại 1 đơn vị.
    QVector<int> peopleHavingLessThanOtherOneUnitOfKiA;
    QVector<int> peopleHavingMoreThanOtherOneUnitOfKiA;
    getPeopleHavingLessThanAndMoreThanOtherOneUintOfKiX(KI_A, month, peopleHavingLessThanOtherOneUnitOfKiA, peopleHavingMoreThanOtherOneUnitOfKiA);
    //1.2 Thực thi
    setKiAAtMonthXOfQuarter(month, peopleHavingMoreThanOtherOneUnitOfKiA, peopleHavingLessThanOtherOneUnitOfKiA);
    //2   Set KiB
    //2.1 Chọn danh sách những người có tổng số Ki B của tháng ít hơn những người còn lại 1 đơn vị.
    QVector<int> peopleHavingLessThanOtherOneUnitOfKiB;
    QVector<int> peopleHavingMoreThanOtherOneUnitOfKiB;
    getPeopleHavingLessThanAndMoreThanOtherOneUintOfKiX(KI_B, month, peopleHavingLessThanOtherOneUnitOfKiB, peopleHavingMoreThanOtherOneUnitOfKiB);
    //2.2 Thực thi
    setKiBAtMonthXOfQuarter(month, peopleHavingMoreThanOtherOneUnitOfKiB, peopleHavingLessThanOtherOneUnitOfKiB);
    //3   Set KiD
    //3.1 Chọn danh sách những người có tổng số Ki D của tháng ít hơn những người còn lại 1 đơn vị.
    QVector<int> peopleHavingLessThanOtherOneUnitOfKiD;
    QVector<int> peopleHavingMoreThanOtherOneUnitOfKiD;
    getPeopleHavingLessThanAndMoreThanOtherOneUintOfKiX(KI_D, month, peopleHavingLessThanOtherOneUnitOfKiD, peopleHavingMoreThanOtherOneUnitOfKiD);
    //3.2 Thực thi
    setKiDAtMonthXOfQuarter(month, peopleHavingMoreThanOtherOneUnitOfKiD, peopleHavingLessThanOtherOneUnitOfKiD);
    //4.  Set KiC
    setKiCAtMonthXForLeftPeople(month);
}

QVector<int> AdjustKiMethod::getCandidateForKiA(const QVector<int>& listGotKiAInOldSession)
{
    QVector<int> list;
    // Uu tien nhung nguoi nay truoc
    list.append(listGotKiAInOldSession);

    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        //Tất cả những người chưa đạt Ki A.
        if (mExecListOfficer.at(index)->getKiXStatus(KI_A) != YES
            && !list.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            list.push_back(mExecListOfficer.at(index)->getOfficerStt().toInt());
        }
    }

    return list;
}

QVector<int> AdjustKiMethod::getCandidateForKiB(const QVector<int>& listSetKiAThisSession, const QVector<int>& listGotKiBInOldSession)
{
    QVector<int> list;

    // Uu tien nhung nguoi nay truoc
    for (int index = 0; index < listGotKiBInOldSession.size(); index++)
    {
        if (!listSetKiAThisSession.contains(listGotKiBInOldSession[index]))
        {
            list.append(listGotKiBInOldSession[index]);
        }
    }

    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        //Tất cả những người chưa đạt Ki B, trừ những người đã đạt Ki A trong lượt chọn Ki A
        if (!listSetKiAThisSession.contains(mExecListOfficer[index]->getOfficerStt().toInt())
            && mExecListOfficer[index]->getKiXStatus(KI_B) != YES
            && !list.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            list.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
        }
    }

    return list;
}

QVector<int> AdjustKiMethod::getCandidateForKiD(const QVector<int>& listSetKiABThisSession, const QVector<int>& listGotKiDInOldSession)
{
    QVector<int> list;

    //Uu tien nhung nguoi nay truoc
    for (int index = 0; index < listGotKiDInOldSession.size(); index++)
    {
        if (!listSetKiABThisSession.contains(listGotKiDInOldSession[index]))
        {
            list.append(listGotKiDInOldSession[index]);
        }
    }

    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        //Tất cả những người chưa đạt Ki B, trừ những người đã đạt Ki A trong lượt chọn Ki A
        if (!listSetKiABThisSession.contains(mExecListOfficer[index]->getOfficerStt().toInt())
            && mExecListOfficer[index]->getKiXStatus(KI_D) != YES
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

    if (kiType == KI_A)
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
                LOG_DEBUG("WRONG NUMBER OF KI MONTH KIA")
            }
        }
    }
    else if (kiType == KI_B)
    {
        for (int index = 0; index < mExecListOfficer.size(); index++)
        {
            //list được chọn của KI B phải loại những người vừa được set KI A tháng này
            if ((!thereIsDifference || (mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() == (maxKiXAmount - 1)
                                        || mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() == (maxKiXAmount - 2)))
                && mExecListOfficer[index]->getKiXMonth(month) != KI_A_SYMBOL)
            {
                listLess.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            }
            else if ((mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() == maxKiXAmount)
                     && mExecListOfficer[index]->getKiXMonth(month) != KI_A_SYMBOL)
            {
                listMore.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            }
            else if (mExecListOfficer[index]->getKiXMonth(month) != KI_A_SYMBOL)
            {
                LOG_DEBUG("WRONG NUMBER OF KI MONTH KIB")
            }
        }
    }
    else if (kiType == KI_D)
    {
        for (int index = 0; index < mExecListOfficer.size(); index++)
        {
            //list được chọn của KI D phải loại những người vừa được set KI A & KI B tháng này
            if ((!thereIsDifference || (mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() == (maxKiXAmount - 1)
                                        || mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() == (maxKiXAmount - 2)))
                && mExecListOfficer[index]->getKiXMonth(month) != KI_A_SYMBOL
                && mExecListOfficer[index]->getKiXMonth(month) != KI_B_SYMBOL)
            {
                listLess.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            }
            else if ((mExecListOfficer[index]->getKiXMonthlyAmount(kiType).toInt() == maxKiXAmount)
                     && mExecListOfficer[index]->getKiXMonth(month) != KI_A_SYMBOL
                     && mExecListOfficer[index]->getKiXMonth(month) != KI_B_SYMBOL)
            {
                listMore.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            }
            else if (mExecListOfficer[index]->getKiXMonth(month) != KI_A_SYMBOL
                     && mExecListOfficer[index]->getKiXMonth(month) != KI_B_SYMBOL)
            {
                LOG_DEBUG("WRONG NUMBER OF KI MONTH KID ")
            }
        }
    }
}

void AdjustKiMethod::setKiAAtMonthXOfQuarter(int month, QVector<int> listMore, QVector<int> listLess)
{
    //Tạo một list sắp xếp theo thứ tự
    //Người được KIA Quý này(from listLess) -> người không bị KID Quý này và cũng không được KIA Quý này(from listLess) -> người bị KID quý(from listLess) -> Những người nhiều hơn người khác 1 đơn vị Ki A tháng.
    //Check từ đầu xuống cuối theo thuật toán pick Ki A tháng 1 của a MungVH.
    QVector<QSharedPointer<Officer>> tempList;

    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        //Xét những người có Ki A tháng ít hơn người khác 1 đơn vị trước
        if (listLess.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            //Cho những người có KI A quý này lên đầu
            if (mExecListOfficer[index]->getKiXQuarter(mThisQuarter) == KI_A_SYMBOL)
            {
                tempList.push_front(mExecListOfficer[index]);
            }
            //Cho những người có KI D quý này xuống cuối
            else if (mExecListOfficer[index]->getKiXQuarter(mThisQuarter) == KI_D_SYMBOL)
            {
                tempList.push_back(mExecListOfficer[index]);
            }
            //Những người còn lại là những người ko được KI A và D quý này thì cho vào giữa
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
                        //Tìm thấy người có ki D quý này thì nhét vào trước người này
                        if (tempList[index1]->getKiXQuarter(mThisQuarter) == KI_D_SYMBOL)
                        {
                            tempList.insert(tempList.begin() + index1, mExecListOfficer[index]);
                            break;
                        }

                        //Nếu người cuối cùng cũng không phải là Ki D quý này thì nhét vào cuối
                        if (tempList[index1]->getKiXQuarter(mThisQuarter) != KI_D_SYMBOL && index1 == tempList.size() - 1)
                        {
                            tempList.push_back(mExecListOfficer[index]);
                            break;
                        }
                    }
                }
            }
        }
    }

    //Thêm những người có KI A tháng hơn người khác một đơn vị vào cuối list
    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        if (listMore.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            tempList.push_back(mExecListOfficer[index]);
        }
    }

    //Thực thi phân phối KI A từ đầu đến cuối.
    int maxTargets = mKiAPeople;

    for (int index1 = 0; index1 < tempList.size(); index1++)
    {
        for (int index2 = 0; index2 < mExecListOfficer.size(); index2++)
        {
            if (maxTargets > 0)
            {
                if (mExecListOfficer[index2]->getOfficerStt().toInt() == tempList[index1]->getOfficerStt().toInt())
                {
                    mExecListOfficer[index2]->insertKiXMonth(KI_A_SYMBOL, month);
                    LOG_DEBUG("STT % d Get KiA in Month % d Quarter % d", mExecListOfficer[index2]->getOfficerStt().toInt(), month + 1, mThisQuarter + 1);
                    maxTargets--;
                }
            }
        }
    }
}
void AdjustKiMethod::setKiBAtMonthXOfQuarter(int month, QVector<int> listMore, QVector<int> listLess)
{
    //Tạo một list sắp xếp theo thứ tự
    //Những người ít hơn người khác 1 đơn vị Ki B tháng -> Những người nhiều hơn người khác 1 đơn vị Ki B tháng (những người này đều chưa được xét Ki A tháng này).
    //Check từ đầu xuống cuối theo thuật toán pick Ki B tháng 1 của a MungVH.
    QVector<QSharedPointer<Officer>> tempList;

    //hững người ít hơn người khác 1 đơn vị Ki B tháng lên đầu list
    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        if (listLess.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            tempList.push_front(mExecListOfficer[index]);
        }
    }

    //Thêm những người có KI B tháng hơn người khác một đơn vị vào cuối list
    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        if (listMore.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            tempList.push_back(mExecListOfficer[index]);
        }
    }

    //Thực thi phân phối KI B từ đầu đến cuối.
    int maxTargets = mKiBPeople;

    for (int index1 = 0; index1 < tempList.size(); index1++)
    {
        for (int index2 = 0; index2 < mExecListOfficer.size(); index2++)
        {
            if (maxTargets > 0)
            {
                if (mExecListOfficer[index2]->getOfficerStt().toInt() == tempList[index1]->getOfficerStt().toInt())
                {
                    mExecListOfficer[index2]->insertKiXMonth(KI_B_SYMBOL, month);
                    LOG_DEBUG("STT % d Get KiB in Month % d Quarter % d", mExecListOfficer[index2]->getOfficerStt().toInt(), month + 1, mThisQuarter + 1);
                    maxTargets--;
                }
            }
        }
    }
}

void AdjustKiMethod::setKiDAtMonthXOfQuarter(int month, QVector<int> listMore, QVector<int> listLess)
{
    //Tạo một list sắp xếp theo thứ tự
    //Người được KID Quý này(from listLess) -> người không bị KID Quý này(from listLess) -> Những người nhiều hơn người khác 1 đơn vị Ki D tháng.
    //Check từ đầu xuống cuối theo thuật toán pick Ki D tháng 1 của a MungVH.
    QVector<QSharedPointer<Officer>> tempList;

    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        //Xét những người có Ki D tháng ít hơn người khác 1 đơn vị trước
        if (listLess.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            //Cho những người có KI D quý này lên đầu
            if (mExecListOfficer[index]->getKiXQuarter(mThisQuarter) == KI_D_SYMBOL)
            {
                tempList.push_front(mExecListOfficer[index]);
            }

            //Cho những người ko có KI D quý này xuống cuối
            if (mExecListOfficer[index]->getKiXQuarter(mThisQuarter) != KI_D_SYMBOL)
            {
                tempList.push_back(mExecListOfficer[index]);
            }
        }
    }

    //Thêm những người có KI D tháng hơn người khác một đơn vị vào cuối list
    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        if (listMore.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            tempList.push_back(mExecListOfficer[index]);
        }
    }

    //Thực thi phân phối KI D từ đầu đến cuối.
    int maxTargets = mKiDPeople;

    for (int index1 = 0; index1 < tempList.size(); index1++)
    {
        for (int index2 = 0; index2 < mExecListOfficer.size(); index2++)
        {
            if (maxTargets > 0)
            {
                if (mExecListOfficer[index2]->getOfficerStt().toInt() == tempList[index1]->getOfficerStt().toInt())
                {
                    mExecListOfficer[index2]->insertKiXMonth(KI_D_SYMBOL, month);
                    LOG_DEBUG("STT % d Get KiD in Month % d Quarter % d", mExecListOfficer[index2]->getOfficerStt().toInt(), month + 1 , mThisQuarter + 1);
                    maxTargets--;
                }
            }
        }
    }
}
void AdjustKiMethod::setKiCAtMonthXForLeftPeople(int month)
{
    for (int index = 0 ; index < mExecListOfficer.size(); index++)
    {
        if (mExecListOfficer[index]->getKiXMonth(month) == KI_NOT_SET)
        {
            mExecListOfficer[index]->insertKiXMonth(KI_C_SYMBOL, month);
        }
    }
}

void AdjustKiMethod::embroilList(QVector<QSharedPointer<Officer> >& list)
{
    for (int index = 0; index < 30; index++)
    {
        int ranVal1 = randomIntergerInRange(0, list.size() - 1);
        int ranVal2 = randomIntergerInRange(0, list.size() - 1);
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

            if (ki == KI_A_SYMBOL)
            {
                mKiAPeople --;
            }
            else if (ki == KI_B_SYMBOL)
            {
                mKiBPeople--;
            }
            else if (ki == KI_C_SYMBOL)
            {
                mKiCPeople--;
            }
            else if (ki == KI_D_SYMBOL)
            {
                mKiDPeople--;
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
    mOfficerGetKiDInThisSessionList.clear();
    mOfficerGetKiAInThisSessionList.clear();
    mOfficerGetKiBInThisSessionList.clear();
    mOfficerGetKiCInThisSessionList.clear();
}

void AdjustKiMethod::resetKiPeople()
{
    // Tính cụ thể số lượng người cho từng loại KI
    mKiAPeople = static_cast<int>(std::roundf(mKiAPercent * mNumberOfOfficer / 100));
    mKiBPeople = static_cast<int>(std::roundf(mKiBPercent * mNumberOfOfficer / 100));
    mKiDPeople = static_cast<int>(std::roundf(mKiDPercent * mNumberOfOfficer / 100));
    mKiCPeople = mNumberOfOfficer - mKiAPeople - mKiBPeople - mKiDPeople;
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
    QVector<int> listOfficerGotKiAInOldSession;
    QVector<int> listOfficerGotKiBInOldSession;
    QVector<int> listOfficerGotKiDInOldSession;

    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        if (mExecListOfficer[index]->getKiXQuarter(mThisQuarter) == KI_A_SYMBOL)
        {
            listOfficerGotKiAInOldSession.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            //Xóa đi trạng thái cập nhật KI trước đây của họ
            mExecListOfficer[index]->insertKiXStatus(KI_NOT_SET, KI_A);
        }
        else if (mExecListOfficer[index]->getKiXQuarter(mThisQuarter) == KI_B_SYMBOL)
        {
            listOfficerGotKiBInOldSession.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            //Xóa đi trạng thái cập nhật KI trước đây của họ
            mExecListOfficer[index]->insertKiXStatus(KI_NOT_SET, KI_B);
        }
        else if (mExecListOfficer[index]->getKiXQuarter(mThisQuarter) == KI_D_SYMBOL)
        {
            listOfficerGotKiDInOldSession.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
            //Xóa đi trạng thái cập nhật KI trước đây của họ
            mExecListOfficer[index]->insertKiXStatus(KI_NOT_SET, KI_D);
        }

        mExecListOfficer[index]->insertKiXQuarter(KI_NOT_SET, mThisQuarter);
    }

    //set lại Ki A
    //1.1 Chon ra tat ca nhung nguoi co the duoc ki A
    QVector<int> candidateForKiAListStt = getCandidateForKiA(listOfficerGotKiAInOldSession);

    //1.2 Set Ki
    //Nếu số người trong danh sách chưa đạt Ki A ít hơn số Ki A cần tạo
    if (candidateForKiAListStt.size() < mKiAPeople)
    {
        //thì toàn bộ số người trong sanh sách ở bước trên sẽ đạt Ki A
        setKiXQuaterStatusOfThemToYes(KI_A, candidateForKiAListStt);
        //và reset trạng thái Ki A của toàn bộ số người đã đạt Ki A khác về "Không"
        //roi đưa vào danh sách để random số Ki A còn thiếu.
        QVector<int> randomList = setKiXQuaterStatusOfThemToNo(KI_A, candidateForKiAListStt);
        //random
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedList(mKiAPeople, randomList);
        setKiXQuaterStatusOfThemToYes(KI_A, selectedOfficerAfterRandom);
        //Lưu lại những người được set KiA trong turn này để xử lý KiB
        mOfficerGetKiAInThisSessionList.append(candidateForKiAListStt);
        mOfficerGetKiAInThisSessionList.append(selectedOfficerAfterRandom);
    }
    else
    {
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedListVer2(mKiAPeople, candidateForKiAListStt, listOfficerGotKiAInOldSession);
        setKiXQuaterStatusOfThemToYes(KI_A, selectedOfficerAfterRandom);
        //Lưu lại những người được set KiA trong turn này để xử lý KiB
        mOfficerGetKiAInThisSessionList.append(selectedOfficerAfterRandom);
    }

    //2. Set Ki B
    //2.1 Chon ra tat ca nhung nguoi co the duoc ki B
    QVector<int> candidatesForKiBListStt = getCandidateForKiB(mOfficerGetKiAInThisSessionList, listOfficerGotKiBInOldSession);
    QVector<int> officerGetKiABInThisSessionList;

    //2.2 Set Ki
    //Nếu số người trong danh sách co the duoc đạt Ki B ít hơn số Ki B cần tạo
    if (candidatesForKiBListStt.size() < mKiBPeople)
    {
        //thì toàn bộ số người trong sanh sách ở bước trên sẽ đạt Ki B
        setKiXQuaterStatusOfThemToYes(KI_B, candidatesForKiBListStt);
        //và reset trạng thái Ki B của toàn bộ số người đã đạt Ki B khác về "Không"
        //roi đưa vào danh sách để random số Ki B còn thiếu.
        QVector<int> randomList = setKiXQuaterStatusOfThemToNo(KI_B, candidatesForKiBListStt);
        //random
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedList(mKiBPeople, randomList);
        setKiXQuaterStatusOfThemToYes(KI_B, selectedOfficerAfterRandom);
        //Lưu lại những người được set KiAB trong turn này để xử lý Ki D
        officerGetKiABInThisSessionList.append(candidatesForKiBListStt);
        officerGetKiABInThisSessionList.append(selectedOfficerAfterRandom);
        mOfficerGetKiBInThisSessionList = officerGetKiABInThisSessionList;
        officerGetKiABInThisSessionList.append(mOfficerGetKiAInThisSessionList);
    }
    //Nếu số người trong danh sách co the duoc đạt Ki B nhiều hơn hoặc bằng số Ki B cần tạo
    else
    {
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedListVer2(mKiBPeople, candidatesForKiBListStt, listOfficerGotKiBInOldSession);
        setKiXQuaterStatusOfThemToYes(KI_B, selectedOfficerAfterRandom);
        //Lưu lại những người được set KiAB trong turn này để xử lý KiD
        officerGetKiABInThisSessionList.append(selectedOfficerAfterRandom);
        mOfficerGetKiBInThisSessionList = officerGetKiABInThisSessionList;
        officerGetKiABInThisSessionList.append(mOfficerGetKiAInThisSessionList);
    }

    //3. Set KiD
    //3.1 Chon ra tat ca nhung nguoi co the duoc ki D
    QVector<int> candidatesForKiDListStt = getCandidateForKiD(officerGetKiABInThisSessionList, listOfficerGotKiDInOldSession);
    QVector<int> officerGetKiABDInThisSessionList;

    //3.2 Set Ki
    //Nếu số người trong danh sách co the duoc đạt Ki D ít hơn số Ki D cần tạo
    if (candidatesForKiDListStt.size() < mKiDPeople)
    {
        //thì toàn bộ số người trong sanh sách ở bước trên sẽ đạt Ki B
        setKiXQuaterStatusOfThemToYes(KI_D, candidatesForKiDListStt);
        //và reset trạng thái Ki B của toàn bộ số người đã đạt Ki D khác về "Không"
        //roi đưa vào danh sách để random số Ki D còn thiếu.
        QVector<int> randomList = setKiXQuaterStatusOfThemToNo(KI_D, candidatesForKiDListStt);
        //random
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedList(mKiDPeople, randomList);
        setKiXQuaterStatusOfThemToYes(KI_D, selectedOfficerAfterRandom);
        //Lưu lại những người được set KiABD trong turn này để xử lý Ki C
        officerGetKiABDInThisSessionList.append(candidatesForKiDListStt);
        officerGetKiABDInThisSessionList.append(selectedOfficerAfterRandom);
        mOfficerGetKiDInThisSessionList = officerGetKiABDInThisSessionList;
        officerGetKiABDInThisSessionList.append(officerGetKiABInThisSessionList);
    }
    //Nếu số người trong danh sách co the duoc đạt Ki D nhiều hơn hoặc bằng số Ki D cần tạo
    else
    {
        QVector<int> selectedOfficerAfterRandom = getRandomSelectedListVer2(mKiDPeople, candidatesForKiDListStt, listOfficerGotKiDInOldSession);
        setKiXQuaterStatusOfThemToYes(KI_D, selectedOfficerAfterRandom);
        //Lưu lại những người được set KiAB trong turn này để xử lý KiD
        officerGetKiABDInThisSessionList.append(selectedOfficerAfterRandom);
        mOfficerGetKiDInThisSessionList = officerGetKiABDInThisSessionList;
        officerGetKiABDInThisSessionList.append(officerGetKiABInThisSessionList);
    }

    //4. Set KiC
    //Mặc định những người còn lại trong danh sách là Ki C.
    QVector<int> candidatesForKiCListStt = getCandidateForKiC(officerGetKiABDInThisSessionList);
    setKiXQuaterStatusOfThemToYes(KI_C, candidatesForKiCListStt);
    mOfficerGetKiCInThisSessionList.append(candidatesForKiCListStt);
    LOG_DEBUG("KI A = %d ng, KI B = %d ng, KI C =%d ng, KI D = %d ng",
              mOfficerGetKiAInThisSessionList.size(), mOfficerGetKiBInThisSessionList.size(),
              mOfficerGetKiCInThisSessionList.size(), mOfficerGetKiDInThisSessionList.size())
}

bool AdjustKiMethod::kiRateInputIsOk(QString& issue)
{
    if (mIsPercentMode)
    {
        // Tính cụ thể số lượng người cho từng loại KI
        mKiAPeople = static_cast<int>(std::roundf(mKiAPercent * mNumberOfOfficer / 100));
        mKiBPeople = static_cast<int>(std::roundf(mKiBPercent * mNumberOfOfficer / 100));
        mKiDPeople = static_cast<int>(std::roundf(mKiDPercent * mNumberOfOfficer / 100));

        if (mKiAPercent + mKiBPercent + mKiDPercent > 100.0)
        {
            issue = "Tỷ lệ % Ki chưa đúng";
            return false;
        }

        mKiCPeople = mNumberOfOfficer - mKiAPeople - mKiBPeople - mKiDPeople;
        mKiCPercent = 100 - mKiAPercent - mKiBPercent - mKiDPercent;
        LOG_DEBUG("Convert percent to number of people, result: mKiAPeople = %d, mKiBPeople = %d, mKiCPeople = %d, mKiDPeople = %d",
                  mKiAPeople, mKiBPeople, mKiCPeople, mKiDPeople)
    }
    else
    {
        mKiAPercent = mKiAPeople * 100 / mNumberOfOfficer;
        mKiBPercent = mKiBPeople * 100 / mNumberOfOfficer ;
        mKiDPercent = mKiDPeople * 100 / mNumberOfOfficer ;

        if (mNumberOfOfficer < mKiAPeople + mKiBPeople + mKiDPeople)
        {
            issue = "Phân phối KI theo số người chưa đúng";
            issue += "\nTổng số nhân viên cần phân phối KI là: ";
            issue += QString::number(mNumberOfOfficer);
            return false;
        }

        mKiCPeople = mNumberOfOfficer - mKiAPeople - mKiDPeople - mKiBPeople;
        mKiCPercent = 100 - mKiAPercent - mKiBPercent - mKiDPercent;
    }

    return true;
}


QVector<int> AdjustKiMethod::getCandidateForKiC(const QVector<int>& listSetKiABDThisSesson)
{
    QVector<int> listCandidateKiC;

    for (int index = 0; index < mExecListOfficer.size(); index++)
    {
        //Tất cả những người đạt Ki A,D, B this round
        if (!listSetKiABDThisSesson.contains(mExecListOfficer[index]->getOfficerStt().toInt()))
        {
            listCandidateKiC.push_back(mExecListOfficer[index]->getOfficerStt().toInt());
        }
    }

    return listCandidateKiC;
}
