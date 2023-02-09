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
    explicit disp_ticket(QWidget *parent = nullptr);
    disp_ticket(int ticket_no, QWidget* parent=nullptr);
    ~disp_ticket();

private:
    Ui::disp_ticket *ui;
    ticket* t;
};

#endif // DISP_TICKET_H
