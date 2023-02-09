#ifndef TRAIN_H
#define TRAIN_H
#include <QObject>


class train : public QObject
{
    Q_OBJECT
public:
    QString trainname;
    int c1;
    int c2;
    int c3;
    int cs1;
    int cs2;
    int cs3;
    train(int trainnumber=0);
    void set_train_no(int trainno);
    void set_class_type(QString);
    QString train_class();

private:
    int train_no;
    QString class_type;
    int c;
    void set_details();
};

#endif // TRAIN_H
