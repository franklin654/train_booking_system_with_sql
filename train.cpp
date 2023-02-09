#include "train.h"
#include <QSql>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlError>

train::train(int trainnumber):train_no(trainnumber)
{
    if(train_no != 0) {
        this->set_details();
    }
}

void train::set_train_no(int trainno) {
    this->train_no = trainno;
    this->set_details();
}

void train::set_details() {
    QSqlQuery query;
    QString cmd = "SELECT `TrainName`, `1stClassPrice`, `2ndClassPrice`, `SleeperPrice`, `capacity`, `1stclasscapacity`, `2ndclasscapacity`, `3rdclasscapacity` FROM `train_schema`.`train` WHERE `train`.`TrainNumber` = :trno;";
    query.prepare(cmd);
    query.bindValue(":trno", this->train_no);
    if(query.exec()) {
        if(query.next()) {
            this->trainname = query.value(0).toString();
            this->cs1 = query.value(1).toInt();
            this->cs2 = query.value(2).toInt();
            this->cs3 = query.value(3).toInt();
            this->c = query.value(4).toInt();
            this->c1 = query.value(5).toInt();
            this->c2 = query.value(6).toInt();
            this->c3 = query.value(7).toInt();
        }
    }
}

void train::set_class_type(QString Class) {
    this->class_type = Class;
}

QString train::train_class() {
    return this->class_type;
}
