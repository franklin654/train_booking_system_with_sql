#ifndef USER_H
#define USER_H

#include <QObject>

class user: public QObject
{
    Q_OBJECT
public:
    explicit user(QObject* parent = nullptr);
    user(QString usr, QString passwd, QObject* parent = nullptr);
    bool check_login();
private:
QString username;
QString password;
};

#endif // USER_H
