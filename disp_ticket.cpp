#include "disp_ticket.h"
#include "ui_disp_ticket.h"
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>

disp_ticket::disp_ticket(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::disp_ticket)
{
    ui->setupUi(this);


}

void disp_ticket::set_disp_tick() {
    QSqlQuery query;
    QString cmd = "SELECT `tickets`.`idticket`,`tickets`.`passenger`,`tickets`.`train_number`,`tickets`.`Class`,`tickets`.`price`,`tickets`.`Source`,`tickets`.`Destination`, `tickets`.`Seat` FROM `train_schema`.`tickets` WHERE idticket = :tid;";
    query.prepare(cmd);
    query.bindValue(":tid", this->tid);
    query.exec();
    query.next();
    ui->tick_no->setText(query.value(0).toString());
    ui->passenger->setText(query.value(1).toString());
    ui->train_no->setText(query.value(2).toString());
    //ui->train_n->setText(query.value(3).toString());
    ui->seat_no->setText(query.value(3).toString()+"|"+query.value(7).toString());
    ui->source->setText(query.value(5).toString());
    ui->dest->setText(query.value(6).toString());
    ui->date->setText(query.value(8).toString());
}

void disp_ticket::set_tid(int t) {
    this->tid = t;
    set_disp_tick();
}

disp_ticket::~disp_ticket()
{
    delete ui;
}
