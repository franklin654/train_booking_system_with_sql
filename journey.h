#ifndef JOURNEY_H
#define JOURNEY_H

#include <QPushButton>
#include "ticket_gen.h"
#include <QWidget>
#include <QBoxLayout>
#include "ticket_gen.h"

namespace Ui {
class journey;
}

class journey : public QWidget
{
    Q_OBJECT

public:
    QWidget* prev;
    explicit journey(QWidget* prev=nullptr, QWidget *parent = nullptr);
    ~journey();


private:
    Ui::journey *ui;
    QBoxLayout* jlayout;
    QString source;
    QString dest;
    ticket_gen* tick;
    void book_ticket(QPushButton*);
    void display_trains();
    QVBoxLayout* trdbox;
};

#endif // JOURNEY_H
