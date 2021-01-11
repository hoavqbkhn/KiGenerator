#ifndef ACTIONPROVIDER1_H
#define ACTIONPROVIDER1_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QUrl>
#include <QStringList>
#include <QVariantMap>

class ActionProvider final : public QObject
{

        Q_OBJECT
    public:
        static ActionProvider& instance()
        {
            static ActionProvider self;
            return self;
        }

        Q_INVOKABLE void openFileKiData();
        Q_INVOKABLE void updatePercentMode(QVariantMap data);
        Q_INVOKABLE void generate(QVariantMap preData);
        Q_INVOKABLE void exportData();
        Q_INVOKABLE void review();
        Q_INVOKABLE void updateFixingKiList(QVariantMap fixingData);
        Q_INVOKABLE void adjustKi(QVariantMap adjustData);
        Q_INVOKABLE void accessCreateMode();
        Q_INVOKABLE void accessAdjustMode();
        Q_INVOKABLE void config(QVariantMap config);





    private:
        ActionProvider() = default;
        ActionProvider(const ActionProvider&) = delete;
        ActionProvider(ActionProvider&&) = delete;
        ActionProvider& operator=(const ActionProvider&) = delete;
        ActionProvider& operator=(ActionProvider &&) = delete;
        ~ActionProvider() = default;
};

#endif // ACTIONPROVIDER_H
