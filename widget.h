#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "journey.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void signup_handler();

private slots:
    void on_login_clicked();

private:
    Ui::Widget *ui;
    journey *j;
};
#endif // WIDGET_H