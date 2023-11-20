#ifndef HOME_H
#define HOME_H


#include <QWidget>
#include "QMessageBox"
#include "QTime"
#include"QPaintEvent"
#include"QPainter"
#include"QPixmap"

namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);

    ~Home();


    void DrawPrize();
    void drawBallsAndText(QLabel *label,int *redBalls, int blueBall);

private slots:
    void user_check();
    void on_btn_prize_clicked();
    void on_btn_close_clicked();

private:
    Ui::Home *ui;
    int user_red[6]={0};
    int user_blue=0;
    int prize_red[6]={0};
    int prize_blue=0;
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // HOME_H
