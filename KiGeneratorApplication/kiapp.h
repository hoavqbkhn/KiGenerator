#ifndef KIAPP_H
#define KIAPP_H

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSharedPointer>
#include "common.h"
#include "action/actionprovider.h"
#include "flux/dispatcher.h"
#include "middleware/kiappmiddleware.h"
#include "processor/mainbusinessprocessor.h"
#include "store/kiappstore.h"
class KiApp: public QObject
{

        Q_OBJECT
    public:
        static KiApp& instance()
        {
            return KiApp::self;
        }

        virtual ~KiApp();
        /**
         * @brief initAllSystem
         * init all component of system
         * this function call all init function below
         */
        void initAllSystem();
        /**
         * @brief initNewObject
         * create all middleware, processor, business thread ...
         */
        void initNewObject();
        /**
         * @brief initQmlAccession
         */
        void initQmlAccession();
        /**
         * @brief initStoreAndMiddlewareRegistration
         * register store and middleware in to dispatcher
         */
        void initStoreAndMiddlewareRegistration();
        /**
         * @brief initSignalSlotConnection
         * connect signal from middleware to others
         */
        void initSignalSlotConnection();

        /**
         * @brief initSystemBusiness
         * start business
         */
        void initSystemBusiness();
    private:
        KiApp();
        static KiApp self;
        KiAppMiddleware* mKiAppMiddleware;
        QSharedPointer<MainBusinessProcessor> mMainBusinessProcessor {nullptr};
};

#endif // KIAPP_H
