#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);
//    ui->label_red->setStyleSheet("QLabel { color : red; }");
//    ui->label_blue->setStyleSheet("QLabel { color : blue; }");
//    ui->PrizeResult->setStyleSheet("QTextBrowser {backgroundcolor : #CDEE64;}");

    // 连接用户输入框的文本变化信号到槽函数
        connect(ui->red_1, &QLineEdit::textChanged, this, &Home::user_check);
        connect(ui->red_2, &QLineEdit::textChanged, this, &Home::user_check);
        connect(ui->red_3, &QLineEdit::textChanged, this, &Home::user_check);
        connect(ui->red_4, &QLineEdit::textChanged, this, &Home::user_check);
        connect(ui->red_5, &QLineEdit::textChanged, this, &Home::user_check);
        connect(ui->red_6, &QLineEdit::textChanged, this, &Home::user_check);
        connect(ui->blue_1, &QLineEdit::textChanged, this, &Home::user_check);

}

Home::~Home()
{
    delete ui;
}

void Home::DrawPrize()
{
   //判先随机生成符合规范的号码，将其存在//int prize_red[6]={0}; int prize_blue=0;中，之后将显示开奖的号码在对象red_prize和blue_prize中，再与用户的结果进行对比将中奖信息更新在PrizeResult中

      // 检查用户输入的红球和蓝球号码是否为空
      bool isInputValid = true;
      for (int i = 0; i < 6; i++) {
          if (user_red[i] == 0) {
              isInputValid = false;
              break;
          }
      }
      if (user_blue == 0) {
          isInputValid = false;
      }

      // 如果号码不完整，弹出提示框
      if (!isInputValid) {
          QMessageBox::warning(this, "提示", "请填写全部红球和蓝球号码！");
          return;
      }

      // 生成符合规范的开奖号码
      qsrand(QTime::currentTime().msec()); // 设置随机数种子
      for (int i = 0; i < 6; i++) {
          int redBall;
          do {
              redBall = qrand() % 33 + 1; // 生成1到33之间的随机数
          } while (std::count(prize_red, prize_red + i, redBall) > 0); // 检查是否已经存在相同的红球号码
          prize_red[i] = redBall;
      }
      prize_blue = qrand() % 16 + 1; // 生成1到16之间的随机数

      // 显示开奖号码
      ui->red_prize->setText(QString::number(prize_red[0]) + " " +
                             QString::number(prize_red[1]) + " " +
                             QString::number(prize_red[2]) + " " +
                             QString::number(prize_red[3]) + " " +
                             QString::number(prize_red[4]) + " " +
                             QString::number(prize_red[5]));
      ui->blue_prize->setText(QString::number(prize_blue));

      // 对比用户输入的号码和开奖号码
      int matchingRedCount = 0;
      for (int i = 0; i < 6; i++) {
          if (std::count(user_red, user_red + 6, prize_red[i]) > 0) {
              matchingRedCount++;
          }
      }

      // 更新中奖信息
      QString prizeResult;
      if (matchingRedCount == 6 && user_blue == prize_blue) {
          prizeResult = "恭喜你中得一等奖！";
      } else if (matchingRedCount == 6 && user_blue != prize_blue) {
          prizeResult = "恭喜你中得二等奖！";
      } else if (matchingRedCount == 5 && user_blue == prize_blue) {
          prizeResult = "恭喜你中得三等奖！";
      } else if (matchingRedCount == 5 && user_blue != prize_blue) {
          prizeResult = "恭喜你中得四等奖！";
      } else if ((matchingRedCount == 4 && user_blue == prize_blue) || (matchingRedCount == 5 && user_blue != prize_blue)) {
          prizeResult = "恭喜你中得五等奖！";
      } else if ((matchingRedCount == 3 && user_blue == prize_blue) || (matchingRedCount == 4 && user_blue != prize_blue) || (matchingRedCount == 2 && user_blue == prize_blue)) {
          prizeResult = "恭喜你中得六等奖！";
      } else if ((matchingRedCount == 3 && user_blue != prize_blue) || (matchingRedCount == 1 && user_blue == prize_blue) || (matchingRedCount == 0 && user_blue == prize_blue)) {
          prizeResult = "恭喜你中得七等奖！";
      } else {
          prizeResult = "很遗憾，你未中奖。";
      }

      ui->PrizeResult->setText(prizeResult);
}

void Home::on_btn_prize_clicked()
{
    DrawPrize();
}

void Home::user_check()
{
    //实现实时的判断用户是否在QlineEdit里的red_1 2 3到6，以及blue_1是否以及输入，并且具有检测是否符合双色球的规范，要是没有输入或不符合规范就在对象PrizeResult里输出提示具体的信息

    QString red1 = ui->red_1->text();
          QString red2 = ui->red_2->text();
          QString red3 = ui->red_3->text();
          QString red4 = ui->red_4->text();
          QString red5 = ui->red_5->text();
          QString red6 = ui->red_6->text();
          QString blue1 = ui->blue_1->text();

          QString errorMessage;

          // 检查红球输入是否合法
          if (red1.isEmpty() || red2.isEmpty() || red3.isEmpty() || red4.isEmpty() || red5.isEmpty() || red6.isEmpty()) {
              errorMessage = "请填写全部红球的值！";
          } else {
              QStringList redBalls;
              redBalls << red1 << red2 << red3 << red4 << red5 << red6;

              // 检查红球是否符合规范
              for (int i = 0; i < redBalls.size(); i++) {
                  int redBall = redBalls[i].toInt();
                  if (redBall < 1 || redBall > 33) {
                      errorMessage = "红球的取值范围应为1到33之间！";
                      errorMessage += " 第" + QString::number(i + 1) + "个红球的值为" + redBalls[i] + "，不符合规范。";
                      break;
                  }
                  if (redBalls.count(redBalls[i]) > 1) {
                      errorMessage = "红球存在重复的数字！";
                      errorMessage += " 第" + QString::number(i + 1) + "个红球的值为" + redBalls[i] + "，与其他红球重复。";
                      break;
                  }

                  // 将符合规范的红球存入数组
                  user_red[i] = redBall;
              }
          }

          // 检查蓝球输入是否合法
          if (blue1.isEmpty()) {
              errorMessage = "请填写蓝球的值！";
          } else {
              int blueBall = blue1.toInt();
              if (blueBall < 1 || blueBall > 16) {
                  errorMessage = "蓝球的取值范围应为1到16之间！";
                  errorMessage += " 蓝球的值为" + blue1 + "，不符合规范。";
              } else {
                  // 将符合规范的蓝球存入数组
                  user_blue = blueBall;
              }
          }

          // 在PrizeResult对象中显示提示信息
          ui->PrizeResult->setText(errorMessage);
//          update();
}



void Home::on_btn_close_clicked()
{
    this->destroy();

}
void Home::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    drawBallsAndText(ui->label_user, user_red, user_blue);
    drawBallsAndText(ui->label_prize, prize_red, prize_blue);
}

void Home::drawBallsAndText(QLabel *label,int *redBalls, int blueBall)
{
    if (label) {
        QPixmap pixmap(label->size());
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);

        int ballRadius = 30; // 球体半径
        QColor redBallColor(Qt::red); // 红球颜色
        QColor blueBallColor(Qt::blue); // 篮球颜色

        for (int i = 0; i < 6; i++) {
            if (redBalls[i] != 0) {
                int x = i * 80 + 50; // 球体的横坐标位置
                int y = 50; // 球体的纵坐标位置

                // 创建球体的渐变填充
                QRadialGradient gradient(QPoint(x, y), ballRadius, QPoint(x, y));
                gradient.setColorAt(0, redBallColor.lighter(120));
                gradient.setColorAt(1, redBallColor.darker(150));

                // 绘制球体
                painter.setPen(Qt::NoPen);
                painter.setBrush(gradient);
                painter.drawEllipse(QPoint(x, y), ballRadius, ballRadius);

                // 设置字体的大小与球体差不多大
                QFont font = painter.font();
                font.setPointSizeF(ballRadius * 0.8); // 根据球体半径调整字体大小
                painter.setFont(font);

                // 绘制数字
                painter.setPen(Qt::white); // 设置文本颜色为白色
                painter.drawText(QRect(x - ballRadius, y - ballRadius, ballRadius * 2, ballRadius * 2),
                                 Qt::AlignCenter, QString::number(redBalls[i]));
            }
        }

        if (blueBall != 0) {
            int x = 50; // 篮球的横坐标位置
            int y = 120; // 篮球的纵坐标位置

            // 创建篮球的渐变填充
            QRadialGradient gradient(QPoint(x, y), ballRadius, QPoint(x, y));
            gradient.setColorAt(0, blueBallColor.lighter(120));
            gradient.setColorAt(1, blueBallColor.darker(150));

            // 绘制篮球
            painter.setPen(Qt::NoPen);
            painter.setBrush(gradient);
            painter.drawEllipse(QPoint(x, y), ballRadius, ballRadius);

            // 设置字体的大小与球体差不多大
            QFont font = painter.font();
            font.setPointSizeF(ballRadius * 0.8); // 根据球体半径调整字体大小
            painter.setFont(font);

            // 绘制数字
            painter.setPen(Qt::white); // 设置文本颜色为白色
            painter.drawText(QRect(x - ballRadius, y - ballRadius, ballRadius * 2, ballRadius * 2),
                             Qt::AlignCenter, QString::number(blueBall));
        }

        label->setPixmap(pixmap);
    }
}


