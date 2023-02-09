#ifndef TICKET_GEN_H
#define TICKET_GEN_H

#include <QWidget>
#include "train.h"
#include "disp_ticket.h"

namespace Ui {
class ticket_gen;
}

class ticket_gen : public QWidget
{
    Q_OBJECT

public:
    explicit ticket_gen(QWidget *parent = nullptr);
    ticket_gen(int train_no, QDate date, QString src, QString d, QWidget *parent = nullptr);
    void classes_available();
    ~ticket_gen();

private:
    Ui::ticket_gen *ui;
    train t;
    disp_ticket * dtick;
    int seat;
    int ticket_id = -1;
};

#endif // TICKET_GEN_H
