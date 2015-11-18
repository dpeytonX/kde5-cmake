#include <%{APPNAMELC}.h>

//#include <KDeclarative/QmlObject>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <qglobal.h>
#include <QString>

Q_DECL_EXPORT int main(int argc, char* argv[]) {
    QScopedPointer<QGuiApplication> app(new QGuiApplication ( argc, argv ));
/*
    app->setApplicationDisplayName(app->tr("Project"));
    app->setApplicationVersion(PROJECT_VERSION_MAJOR + "." + PROJECT_VERSION_MINOR);

    QQmlApplicationEngine* viewer = new QQmlApplicationEngine(app.data());

    QUrl qurl( QStringLiteral ( "qrc:///qml/qt5/main.qml" ) );
    KDeclarative::QmlObject* context = new KDeclarative::QmlObject(viewer, app.data());
    context->setSource (qurl);
*/
    return app->exec();
}
