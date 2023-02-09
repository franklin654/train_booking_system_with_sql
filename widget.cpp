#include "widget.h"
#include "user.h"
#include "journey.h"
#include "./ui_widget.h"
#include <QSql>
#include <QSqlQuery>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->signup, &QPushButton::clicked, this, &Widget::signup_handler);

}

Widget::~Widget()
{
    delete ui;
    delete j;
}


void Widget::on_login_clicked()
{
    user u(ui->username->text(), ui->password->text());
    if(u.check_login()) {
        this->hide();
        j = new journey;
        j->show();
    }
    else {
        qInfo() << "User or system error check the dialogue box";
    }
}

void Widget::signup_handler() {
    QSqlQuery query_ins;
    QString cmd = "INSERT INTO `train_schema`.`user` (`username`, `password`) VALUES (:user, :password);";
    query_ins.prepare(cmd);
    query_ins.bindValue(":user", ui->username->text());
    query_ins.bindValue(":password", ui->password->text());
    if(query_ins.exec()) {
        qInfo() << "User signed up";
    }
}

