#include <QApplication>
#include "widget.h"
#include <QCoreApplication>
#include <QDebug>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QPluginLoader>
#include <QSqlDatabase>

void connectDB() {
    qInfo() << "Opening a database";
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("train_schema");
    db.setUserName("dev_account");
    db.setPassword("Password1");
    if(!db.open()) {
        qInfo() << "Failed to connect!";
        qInfo() << db.lastError().text();

    }
    else {
        qInfo() << "connected";
    }
}

bool testPlugin() {
    qInfo() << "testing plugin";
    QPluginLoader loader("C:\\Qt\\6.4.2\\mingw_64\\plugins\\sqldrivers\\qsqlmysql.dll");
    qInfo() << loader.metaData();
    if(loader.load()) {
        qInfo() << "loaded the plugin";
        return true;
    }
    qInfo() << loader.errorString();
    return false;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    if(testPlugin()) {
        connectDB();
        w.show();
    }
    return a.exec();
}
