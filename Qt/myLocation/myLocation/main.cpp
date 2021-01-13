#include <QApplication>
#include <QQuickView>
#include "getlocation.h"
#include <QQmlContext>
#include "losql.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQuickView *view = new QQuickView;
    getLocation location;
    view->rootContext()->setContextProperty("loca",&location);

    loSql mysql;
    mysql.initDateBase();
    view->rootContext()->setContextProperty("mySql",&mysql);
    QObject::connect((QObject*)view->engine(), SIGNAL(quit()), &app, SLOT(quit()));
    view->setSource(QUrl("qrc:/main.qml"));
    view->setWidth(480);
    view->setHeight(600);
    view->show();
    return app.exec();
}
