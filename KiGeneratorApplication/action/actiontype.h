#ifndef ACTIONTYPE1_H
#define ACTIONTYPE1_H
/*
 * Group all actions in this header
 * You should group actions in enum
 *
 *
*/
enum class ActionType
{
    //none action
    None_Action,

    //exit app action
    ExitApplication,
    OpenDataKiFile,
    ProcessDataKiFile,
    UpdateOfficerData,
    UpdatePercentMode,
    Generate,
    OpenFileForExport,
    Export,
    Review,
    UpdateFixingList,
    UpdateResult,
    NotifyIssue,
    UpdateFixingListOk,
    AdjustKi,
    AccessAdjustMode,
    UpdateQuarter,
    AccessCreateMode,
    Config,
};
#endif // ACTIONTYPE_H
