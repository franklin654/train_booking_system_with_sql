#include "disp_ticket.h"
#include "ui_disp_ticket.h"
#include <QDebug>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>

disp_ticket::disp_ticket(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::disp_ticket)
{
    ui->setupUi(this);
}
disp_ticket::disp_ticket(int ticket_no, QWidget *prev, QWidget* parent) :
    QWidget(parent),
    prev(prev),
    ui(new Ui::disp_ticket)
{
    ui->setupUi(this);
    qInfo() << ticket_no;
    t = new ticket(ticket_no);
    ui->tick_no->setText("Ticket number: "+QVariant(t->ticket_id).toString());
    ui->tick_no->adjustSize();
    ui->tick_no->setAlignment(Qt::AlignHCenter);
    ui->train_no->setText("Train no: "+QVariant(t->train_number).toString());
    ui->train_n->setText("Train name: "+t->train_name);
    ui->source->setText(t->Source);
    ui->dest->setText(t->Destination);
    ui->passenger->setText(t->passenger);
    ui->seat_no->setText(t->Class +"\\"+QVariant(t->Seat).toString());
    ui->date->setText(t->date);
    QPalette p = palette(); //copy current, not create new
    p.setBrush(QPalette::Window, Qt::gray);
    this->setPalette(p);

}
disp_ticket::~disp_ticket()
{
    delete ui;
    delete t;
}
