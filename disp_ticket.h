#ifndef DISP_TICKET_H
#define DISP_TICKET_H

#include <QWidget>

namespace Ui {
class disp_ticket;
}

class disp_ticket : public QWidget
{
    Q_OBJECT

public:
    explicit disp_ticket(QWidget *parent = nullptr);
    void set_tid(int t);
    ~disp_ticket();

private:
    Ui::disp_ticket *ui;
    int tid;
    void set_disp_tick();
};

#endif // DISP_TICKET_H
