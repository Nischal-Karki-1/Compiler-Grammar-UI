#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Controllers/system.h"
#include "QuestionOne/token.h"
#include "QuestionTwo/leftrecursion.h"
#include "QuestionThree/leftfactoring.h"
#include "QuestionFour/firstfollow.h"
#include "QuestionFive/llgrammar.h"
#include "QuestionSix/lrparser.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType < System > ( "System", 1, 0, "System");
    qmlRegisterType < Tokenizer >("Token", 1, 0, "Tokenizer");
    qmlRegisterType < LeftRecursion >("Grammar", 1, 0, "LRecursion");
    qmlRegisterType < LeftFactoring >("Factor", 1, 0, "LFactoring");
    qmlRegisterType < GrammarParser >("Parser", 1, 0, "FirstFollow");
    qmlRegisterType < LL1Parser >("LParser", 1, 0, "LL1");
    qmlRegisterType < LRParser >("LRParser", 1, 0, "LR");







    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    // QQmlContext *context (engine.rootContext());
    // context -> setContextProperty("systemHandler", &m_systemHandler);
    return app.exec();
}







