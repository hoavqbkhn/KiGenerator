#ifndef KIAPPSTORE_H
#define KIAPPSTORE_H
#include <QSharedPointer>
#include <QTimer>
#include <QDateTime>
#include "logger/logger.h"
#include <QObject>
#include "flux/action.h"
#include "flux/store.h"
#include "action/actiontype.h"
#include "flux/dispatcher.h"
#include "common.h"
#include <QFileDialog>
#include "model/setdefaultkimodel.h"
#include "model/resultmodelorderstyle.h"
#include "model/resultmodelkigroupstyle.h"
class KiAppStore : public QObject, public vtx::flux::Store
{
        Q_OBJECT
        Q_PROPERTY(bool isLoadedFile READ getFileIsLoaded NOTIFY loadingFileChanged)
        Q_PROPERTY(QString issue READ getIssue NOTIFY issueChanged)
        Q_PROPERTY(bool isPercentMode READ getIsPercentMode NOTIFY kiScaleChanged)
        Q_PROPERTY(int kiAPeople READ getKiAPeople NOTIFY kiScaleChanged)
        Q_PROPERTY(int kiBPeople READ getKiBPeople NOTIFY kiScaleChanged)
        Q_PROPERTY(int kiCPeople READ getKiCPeople NOTIFY kiScaleChanged)
        Q_PROPERTY(int kiDPeople READ getKiDPeople NOTIFY kiScaleChanged)
        Q_PROPERTY(int thisQuarter READ getThisQuarter NOTIFY thisQuarterChanged)
        Q_PROPERTY(QSharedPointer<SetDefaultOfficerKiModel> mListOfficerModel
                   READ getListOfficerModel NOTIFY officerModelChanged)
        Q_PROPERTY(QSharedPointer<ResultModelOrderStyle> mResultModelOrderStyle
                   READ getResultModel NOTIFY officerModelChanged)
        Q_PROPERTY(QSharedPointer<ResultModelKiGroupStyle> mResultModelKiGroupStyle
                   READ getResultModelKiGroupStyle NOTIFY officerModelChanged)

    public:
        ~KiAppStore();
        static KiAppStore* getInstance();


        void process(const QSharedPointer<vtx::flux::Action>& action) Q_DECL_OVERRIDE;
        bool getFileIsLoaded() const;
        void setFileIsLoaded(bool fileIsLoaded);
        QSharedPointer<SetDefaultOfficerKiModel> getListOfficerModel() const;

        int getKiAPeople() const;
        int getKiBPeople() const;
        int getKiCPeople() const;
        int getKiDPeople() const;
        bool getIsPercentMode() const;

        QSharedPointer<ResultModelOrderStyle> getResultModel() const;
        void setResultModel(const QSharedPointer<ResultModelOrderStyle>& resultModel);

        QString getIssue() const;

        QSharedPointer<ResultModelKiGroupStyle> getResultModelKiGroupStyle() const;

        int getThisQuarter() const;

    signals:
        void loadingFileChanged();
        void officerModelChanged();
        void kiScaleChanged();
        void issueChanged();
        void thisQuarterChanged();

    private:
        KiAppStore();
        static KiAppStore* instance;
        bool mFileIsLoaded {false};
        bool mIsPercentMode {true};
        int mKiAPeople {0};
        int mKiBPeople {0};
        int mKiCPeople {0};
        int mKiDPeople {0};
        int mNumberOfOfficer {0};
        int mThisQuarter {0};
        QString mIssue {""};

        QSharedPointer<SetDefaultOfficerKiModel> mListOfficerModel {nullptr};
        QSharedPointer<ResultModelOrderStyle> mResultModelOrderStyle {nullptr};
        QSharedPointer<ResultModelKiGroupStyle> mResultModelKiGroupStyle {nullptr};

        /**
         * @brief processActionOpenDataKiFile
         * @param action
         */
        void processActionOpenDataKiFile(const QSharedPointer<vtx::flux::Action>& action);

        /**
         * @brief processActionUpdateOfficerData
         * @param action
         */
        void processActionUpdateOfficerData(const QSharedPointer<vtx::flux::Action>& action);

        void processActionUpdateResult(const QSharedPointer<vtx::flux::Action>& action);
        void processActionUpdateIssue(const QSharedPointer<vtx::flux::Action>& action);
        void processActionUpdateFixingKiListOk(const QSharedPointer<vtx::flux::Action>& action);
        void processActionOpenFileForExport(const QSharedPointer<vtx::flux::Action>& action);
        void processActionUpdatePercentMode(const QSharedPointer<vtx::flux::Action>& action);
};

#endif // KIAPPSTORE_H
