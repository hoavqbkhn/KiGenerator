#include "kiapp.h"
KiApp KiApp::self;
KiApp::KiApp()
{
}

KiApp::~KiApp()
{
}
void KiApp::initAllSystem()
{
    initNewObject();
    initSignalSlotConnection();
    initStoreAndMiddlewareRegistration();
    initQmlAccession();
    initSystemBusiness();
}

void KiApp::initNewObject()
{
    mKiAppMiddleware = new KiAppMiddleware();
    mMainBusinessProcessor = QSharedPointer<MainBusinessProcessor>(new MainBusinessProcessor(MAIN_BUSINESS_PROCESSOR_NAME));
    mMainBusinessProcessor->setMiddlewareInterface(mKiAppMiddleware);
}

void KiApp::initQmlAccession()
{
    qmlRegisterSingletonType<ActionProvider>("Flux", 1, 0, "ActionProvider",
                                             [](QQmlEngine * engine, QJSEngine * scriptEngine) -> QObject*
    {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        QQmlEngine::setObjectOwnership(&ActionProvider::instance(), QQmlEngine::CppOwnership);
        return &ActionProvider::instance();
    });
    qmlRegisterSingletonType<KiAppStore>("Flux", 1, 0, "KiAppStore",
                                         [](QQmlEngine * engine, QJSEngine * scriptEngine) -> QObject*
    {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        QQmlEngine::setObjectOwnership(KiAppStore::getInstance(), QQmlEngine::CppOwnership);
        return KiAppStore::getInstance();
    });
}

void KiApp::initStoreAndMiddlewareRegistration()
{
    vtx::flux::Dispatcher::instance().registerMiddleware(mKiAppMiddleware);
    vtx::flux::Dispatcher::instance().registerStore(QSharedPointer<vtx::flux::Store>(KiAppStore::getInstance(), [](vtx::flux::Store*) {}));
}

void KiApp::initSignalSlotConnection()
{
    QObject::connect(mKiAppMiddleware, &KiAppMiddleware::signalDispatchActionToBusiness, mMainBusinessProcessor.get(), &MainBusinessProcessor::slotReceiveActionFromMiddleware);
}



void KiApp::initSystemBusiness()
{
}


