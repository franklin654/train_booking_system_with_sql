#include "widget.h"
#include "qmessagebox.h"
#include "user.h"
#include "disp_ticket.h"
#include "journey.h"
#include "./ui_widget.h"
#include <QSql>
#include <QSqlQuery>
#include <QDebug>
#include <QPalette>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->signup, &QPushButton::clicked, this, &Widget::signup_handler);
    connect(ui->tic_button, &QPushButton::clicked, this, [=](){
        dt = new disp_ticket(ui->tick_no->text().toInt());
        this->hide();
        dt->show();
    });


    QPalette p = palette(); //copy current, not create new
    p.setBrush(QPalette::Window, Qt::gray);
    this->setPalette(p);


}

Widget::~Widget()
{
    delete ui;
    delete j;
    delete dt;
}


void Widget::on_login_clicked()
{
    user u(ui->username->text(), ui->password->text());
    if(u.check_login()) {
        this->hide();
        j = new journey(this);
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
    else {
        QMessageBox *singnuperr = new  QMessageBox(this);
        singnuperr->setText("USERNAME ALREADY EXISTS PLEASE USE ANOTHER!!!");
        singnuperr->setWindowTitle("SIGNUP ERROR");
        singnuperr->open();
    }
}

