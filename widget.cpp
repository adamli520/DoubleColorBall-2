#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);



    ui->password_1->setEchoMode(QLineEdit::Password);
    ui->label_test->setOpenExternalLinks(true);
    ui->label_test->setText("<a href='https://www.lijun520.cn/'>www.lijun520.cn</a>");

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btn_login_clicked()
{
    if(ui->login_1->text()=="admin" && ui->password_1->text()=="123456"){
    QMessageBox::information(this,"登录系统","登录成功");
    home.show();
    this->close();


    }else {
        QMessageBox::information(this,"登录系统","登录失败,请重试！");

    }
}
