#include "gameselect.h"
#include "gamehall.h"
#include"gameroom.h"

gameselect::gameselect(QWidget *parent) : QWidget(parent)
{
       this->setWindowIcon(QIcon(":res/ico.png"));
       this->setWindowTitle("游戏选择");
       this->setFixedSize(1000,800);
       //设置返回按钮
       QPushButton* back_button = new QPushButton(this);
       back_button->move(800,700);
       back_button->setText("回到主界面");
       back_button->resize(200,100);
       back_button->setIcon(QIcon(":/res/back.png"));
       back_button->setIconSize(QSize(50,50));
       connect(back_button,&QPushButton::clicked,this,[=](){
           this->close();
           GameHall* gamehall = new GameHall;
           gamehall->show();
       });

       // 3种游戏按钮


           QFont font("华文行楷",24);
           QPushButton* single_button = new QPushButton(this);
           single_button->setText("简单模式");
           single_button->move(350,200);
           single_button->setFont(font);

           QPushButton* normal_button = new QPushButton(this);
           normal_button->setText("正常模式");
           normal_button->move(350,300);
           normal_button->setFont(font);

           QPushButton* hard_button = new QPushButton(this);
           hard_button->setText("困难模式");
           hard_button->move(350,400);
           hard_button->setFont(font);

           QPushButton* history_button = new QPushButton(this);
           history_button->setText("历史战绩");
           history_button->move(350,500);
           history_button->setFont(font);
           GameRoom* newRoom = new GameRoom;
               connect(single_button,&QPushButton::clicked,this,[=](){
                   this->close();
                   newRoom->show();
                   newRoom->setGeometry(this->geometry());
                   newRoom->setSpeedInterval(300);
               });
               connect(normal_button,&QPushButton::clicked,this,[=](){
                   this->close();
                   newRoom->show();
                   newRoom->setGeometry(this->geometry());
                   newRoom->setSpeedInterval(200);
               });
               connect(hard_button,&QPushButton::clicked,this,[=](){
                   this->close();
                   newRoom->show();
                   newRoom->setGeometry(this->geometry());
                   newRoom->setSpeedInterval(50);
               });

               connect(history_button,&QPushButton::clicked,this,[=](){
                  QWidget* widget = new QWidget;
                  widget->setWindowTitle("历史战绩");
                  widget->setFixedSize(500,300);


               });

}



void gameselect::paintEvent(QPaintEvent *event)
{
    //实例化画家
    QPainter painter(this);

    //实例化画图设备
    QPixmap pix(":/res/game_select.png");

    //绘画
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
