#ifndef TICKET_H
#define TICKET_H

#include <QObject>

class ticket : public QObject
{
    Q_OBJECT
public:
    int ticket_id;
    QString passenger;
    int train_number;
    QString train_name;
    QString Class;
    QString Source;
    QString Destination;
    int Seat;
    QString date;
    ticket(QObject* parent=nullptr);
    ticket(int t, QObject* parent = nullptr);
private:
    void set_details();
};

#endif // TICKET_H
