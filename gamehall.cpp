#include "gamehall.h"
#include "ui_gamehall.h"
#include "gameselect.h"
#include <QPushButton>
#include <QFont>
#include <memory>

GameHall::GameHall(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameHall)
{
    ui->setupUi(this);
    this->setFixedSize(1000,800);//设置窗口大小
    //暂定
    this->setWindowTitle("贪吃蛇游戏");

    //添加开始按钮
       QFont font("华文行楷",24);
       QPushButton*strBtn = new QPushButton(this);
       strBtn->move(370,530);
       strBtn->setFont(font);
       strBtn->setText("开始游戏");

       //跳转界面
       gameselect * gameSelect = new gameselect;
       connect(strBtn,&QPushButton::clicked,this,[=](){
           this->close();           gameSelect->setGeometry(this->geometry());
           gameSelect->show();//展示界面
       });
}

void GameHall::paintEvent(QPaintEvent *event)
{
    //实例化画家
    QPainter painter(this);

    //实例化画图设备
    QPixmap pix(":/res/game_hall.png");

    //绘画
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}




GameHall::~GameHall()
{
    delete ui;
}

