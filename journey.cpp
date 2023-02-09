#include "journey.h"
#include "ticket_gen.h"
#include "ui_journey.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QBoxLayout>

journey::journey(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::journey)
{
    this->jlayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    this->setLayout(jlayout);
    ui->setupUi(this);
    ui->verticalLayout->setAlignment(Qt::AlignLeft);
    ui->dateEdit->setDate(QDate::currentDate());
    jlayout->setAlignment(Qt::AlignLeft);
    connect(ui->submit, &QPushButton::clicked,this, &journey::display_trains);
}

journey::~journey()
{
    delete ui;
    delete tick;
}

void journey::display_trains() {
    this->source = ui->source->text();
    this->dest = ui->destination->text();
    QSqlQuery query;
    QString cmd = "select distinct t.TrainNumber,t.TrainName,1stClassPrice,2ndClassPrice,SleeperPrice,capacity From Train t JOIN Takes r ON t.TrainNumber = r.TrainNumber JOIN Takes r1 ON t.TrainNumber = r1.TrainNumber JOIN  Route ro ON r.RouteNum = ro.RouteNum JOIN  Route ro1 ON r1.RouteNum = ro1.RouteNum where upper(ro.Location) = upper(:src) and upper(ro1.Location) = upper(:dest) and (ro.Duration<ro1.Duration);";
    query.prepare(cmd);
    query.bindValue(":src", this->source);
    query.bindValue(":dest", this->dest);
    QVBoxLayout* trdbox = new QVBoxLayout();
    if(query.exec()) {
        if(query.size() > 0) {
        while(query.next()) {
            if(query.value(5).toInt() > 0) {
            QHBoxLayout* trdis = new QHBoxLayout();
            QPushButton* train = new QPushButton(this);
            train->setText(query.value(0).toString());
            QString tr_d =  query.value(1).toString()+" "+query.value(2).toString()+" "+query.value(3).toString()+" "+query.value(4).toString();
            QLabel* train_details = new QLabel(tr_d, this);
            train_details->setFixedHeight(10);
            train->setFixedWidth(100);
            trdis->addWidget(train);
            trdis->addWidget(train_details);
            trdbox->addLayout(trdis);
            connect(train, &QPushButton::clicked,this, [=](){this->book_ticket(train);});
            }else {
                qInfo() << "no vacancy in" << query.value(1).toString();
                continue;
            }
        }
        }
        else {
            QMessageBox *box = new QMessageBox(this);
            box->resize(200, 100);
            box->setText("CHECK SOURCE AND DESTINATION!!!");
            box->open();
        }
    }else {
        qInfo() << query.lastError().text();
    }
    trdbox->setSpacing(0);
    this->jlayout->addLayout(trdbox);

    //trbox->setAlignment(Qt::AlignLeft);
}

void journey::book_ticket( QPushButton* button) {
    qInfo() << "this train was selected"<<button->text();
    tick = new ticket_gen(button->text().toInt(), ui->dateEdit->date(), this->source, this->dest);
    this->hide();
    tick->show();
}
