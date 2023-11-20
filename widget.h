#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "QMessageBox"
#include "home.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    Home home;

private slots:
//    void on_login_clicked();

    void on_btn_login_clicked();

private:
    Ui::Widget *ui;

};
#endif // WIDGET_H
