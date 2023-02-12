#include "ticket.h"
#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>

ticket::ticket(QObject* parent):QObject(parent) {
    ticket_id = 0;
    set_details();
}
ticket::ticket(int t, QObject* parent) : QObject(parent), ticket_id(t)
{
    set_details();

}

void ticket::set_details() {
    QSqlQuery query;
    QString cmd = "SELECT passenger,train_number,Class,Source,Destination,Seat,date,train_name FROM `train_schema`.`tickets` WHERE `idticket` = :tickid;";
    query.prepare(cmd);
    query.bindValue(":tickid", this->ticket_id);
    if(query.exec()) {
        if(query.next() != NULL) {
            this->passenger = query.value(0).toString();
            qInfo()<<this->passenger;
            this->train_number = query.value(1).toInt();
            qInfo()<<this->train_number;
            this->Class = query.value(2).toString();
            qInfo()<<this->Class;
            this->Source = query.value(3).toString();
            qInfo()<<this->Source;
            this->Destination = query.value(4).toString();
            this->Seat = query.value(5).toInt();
            qInfo()<<this->Seat;
            this->date = query.value(6).toString();
            this->train_name = query.value(7).toString();
        }
        else {
            qInfo() << query.executedQuery();
            QMessageBox wrong_ticket_id;
            wrong_ticket_id.setWindowTitle("wrong id");
            wrong_ticket_id.setWindowTitle("PLEASE CHECK THE TICKET NUMBER YOU HAVE ENTERED!!!");
            wrong_ticket_id.open();
        }
    }
    else {
        qInfo() << "Query failed";
    }
}
