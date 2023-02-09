#include "ticket_gen.h"
#include "ui_ticket_gen.h"
#include <QDate>
#include <QDebug>
#include <QPushButton>
#include <QSql>
#include <QSqlQuery>

ticket_gen::ticket_gen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ticket_gen)
{
    ui->setupUi(this);
}

ticket_gen::ticket_gen(int train_no, QDate date, QString src, QString d, QWidget* parent):QWidget(parent), ui(new Ui::ticket_gen)
{
    ui->setupUi(this);
    t.set_train_no(train_no);
    ui->cost->setText("");
    ui->train_no->setText(ui->train_no->text() + QVariant(train_no).toString());
    ui->train_n->setText(ui->train_n->text() + t.trainname);
    ui->train_n->adjustSize();
    QString dat = date.toString("'DATE OF TRAVEL: 'd.MM.yyyy");
    ui->date_of_travel->setText(dat);
    ui->source->setText("SOURCE: "+src);
    ui->dest->setText("DESTINATION: "+d);
    connect(ui->radioButton, &QRadioButton::toggled, this, [=](){
        if(ui->radioButton->isChecked()) {
            ui->cost->setText(QVariant(t.cs1).toString());
            t.set_class_type(ui->radioButton->text());
            this->seat = t.c1;
        }
    });
    connect(ui->radioButton_2, &QRadioButton::toggled, this, [=](){
        if(ui->radioButton_2->isChecked()) {
            ui->cost->setText(QVariant(t.cs2).toString());
            t.set_class_type(ui->radioButton_2->text());
            this->seat = t.c2;
        }
    });
    connect(ui->radioButton_3, &QRadioButton::toggled, this, [=](){
        if(ui->radioButton_3->isChecked()) {
            ui->cost->setText(QVariant(t.cs3).toString());
            t.set_class_type(ui->radioButton_3->text());
            this->seat = t.c3;
        }
    });
    connect(ui->confirm, &QPushButton::clicked, this, [=](){
        qInfo() << t.train_class();
        QSqlQuery query;
        QString cmd = "INSERT INTO `train_schema`.`tickets` (`passenger`, `train_number`, `Class`, `price`, `Source`, `Destination`, `Seat`, `date`) VALUES (:passenger, :train_number, :Class, :price, :src, :dst, :seat, :date);";
        query.prepare(cmd);
        query.bindValue(":passenger",ui->name->text());
        query.bindValue(":train_number", train_no);
        query.bindValue(":Class", t.train_class());
        query.bindValue(":price", ui->cost->text().toInt());
        query.bindValue(":src", ui->source->text());
        query.bindValue(":dst", ui->dest->text());
        query.bindValue(":seat", seat);
        query.bindValue(":date", date.toString("dd.MM.yyyy"));
        if(query.exec()) {
            ticket_id = query.lastInsertId().toInt();
        }
        if(t.train_class() == "Class 1") {
            cmd = "UPDATE `train_schema`.`train` SET `1stclasscapacity` = `1stclasscapacity` - 1, `capacity` = `capacity`-1 WHERE `train`.`TrainNumber` = :trno;";
        }
        else if(t.train_class() == "Class 2"){
            cmd = "UPDATE `train_schema`.`train` SET `2ndclasscapacity` = `2ndclasscapacity` - 1, `capacity` = `capacity`-1 WHERE `train`.`TrainNumber` = :trno;";
        }
        else {
            cmd = "UPDATE `train_schema`.`train` SET `3rdclasscapacity` = `3rdclasscapacity` - 1, `capacity` = `capacity`-1 WHERE `train`.`TrainNumber` = :trno;";
        }
        query.prepare(cmd);
        query.bindValue(":trno", train_no);
        query.exec();
        this->dtick = new disp_ticket();
        dtick->set_tid(ticket_id);
        this->hide();
        dtick->show();
    });
}

void ticket_gen::classes_available() {
    if(!(t.c1>0)) {
        ui->radioButton->setDisabled(true);
    }
    if(!(t.c2>0)) {
        ui->radioButton_2->setDisabled(true);
    }
    if(!(t.c3>0)) {
        ui->radioButton_3->setDisabled(true);
    }
}

ticket_gen::~ticket_gen()
{
    delete ui;
    delete dtick;
}
