#ifndef JOURNEY_H
#define JOURNEY_H

#include <QPushButton>
#include "ticket_gen.h"
#include <QWidget>
#include <QBoxLayout>

namespace Ui {
class journey;
}

class journey : public QWidget
{
    Q_OBJECT

public:
    explicit journey(QWidget *parent = nullptr);
    ~journey();


private:
    Ui::journey *ui;
    QBoxLayout* jlayout;
    QString source;
    QString dest;
    ticket_gen* tick;
    void book_ticket(QPushButton*);
    void display_trains();
};

#endif // JOURNEY_H
