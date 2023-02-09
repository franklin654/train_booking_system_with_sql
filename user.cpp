#include "user.h"
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

user::user(QObject* parent):QObject(parent)
{
    this->username = "test";
    this->password = "test";
}

user::user(QString usr, QString passwd, QObject* parent):QObject(parent), username(usr), password(passwd) {}

    bool user::check_login() {
        QSqlQuery query;
        QString cmd = "SELECT user.* FROM user WHERE user.username = :user AND user.password = :passwd;";
        query.prepare(cmd);
        query.bindValue(":user", this->username);
        query.bindValue(":passwd", this->password);
        if(query.exec()) {
            if(query.next()) {
                qInfo() << query.value(1);
                return true;
            }
            else {
                QMessageBox box;
                box.setText("Incorrect username or password!!!");
                box.exec();
                return false;
            }
        }
        else {
            QMessageBox box;
            box.setText("query failed unable to access database!!!");
            box.exec();
            return false;
        }
    }
