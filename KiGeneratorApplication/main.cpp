#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "kiapp.h"
#include "common.h"
#include <QApplication>
int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qRegisterMetaType<QSharedPointer<Action>>("QSharedPointer<Action>");
    KiApp::instance().initAllSystem();
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    qRegisterMetaType<QSharedPointer<InnerMessage>>("QSharedPointer<InnerMessage>");
    qRegisterMetaType<QSharedPointer<SetDefaultOfficerKiModel>>("QSharedPointer<SetDefaultOfficerKiModel>");
    qRegisterMetaType<QSharedPointer<ResultModelOrderStyle>>("QSharedPointer<ResultModelOrderStyle>");
    qRegisterMetaType<QSharedPointer<ResultModelKiGroupStyle>>("QSharedPointer<ResultModelKiGroupStyle>");

    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}
