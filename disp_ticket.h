#ifndef DISP_TICKET_H
#define DISP_TICKET_H

#include <QWidget>
#include "ticket.h"

namespace Ui {
class disp_ticket;
}

class disp_ticket : public QWidget
{
    Q_OBJECT

public:
    QWidget* prev;
    explicit disp_ticket(QWidget *parent = nullptr);
    disp_ticket(int ticket_no, QWidget* prev=nullptr, QWidget* parent=nullptr);
    ~disp_ticket();

private:
    Ui::disp_ticket *ui;
    ticket* t;

};

#endif // DISP_TICKET_H
