#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>     // 绘图类
#include <QTimer>       // 定时器类，用于控制游戏更新频率
#include <QKeyEvent>    // 键盘事件类，用于处理用户输入
#include <QVector>      // 动态数组类，用于存储蛇的身体部分
#include <QPoint>       // 点类，用于表示坐标
#include <QRandomGenerator> // 随机数生成器

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event) override;    // 重绘事件，用于绘制游戏界面
    void keyPressEvent(QKeyEvent *event) override;  // 键盘按下事件，用于处理用户输入

private slots:
    void moveSnake();  // 移动蛇的槽函数，由定时器触发

private:
    Ui::Widget *ui;

    // 蛇相关属性
    QVector<QPoint> m_snake;        // 存储蛇的所有身体部分的坐标
    QPixmap m_snakeHeadUp;         // 向上的蛇头图片
    QPixmap m_snakeHeadDown;       // 向下的蛇头图片
    QPixmap m_snakeHeadLeft;       // 向左的蛇头图片
    QPixmap m_snakeHeadRight;      // 向右的蛇头图片

    // 游戏属性
    enum Direction { Up, Down, Left, Right };  // 蛇的移动方向枚举
    Direction m_currentDirection;  // 当前移动方向
    Direction m_nextDirection;     // 下一次移动的方向
    QPoint m_food;                 // 食物的坐标
    bool m_gameOver;               // 游戏是否结束
    int m_score;                   // 玩家分数
    QTimer *m_timer;               // 游戏定时器，控制蛇的移动速度

    // 辅助函数
    void initGame();               // 初始化游戏
    void generateFood();           // 生成食物
    bool isFoodOnSnake(const QPoint &point);  // 检查食物是否在蛇身上
    bool checkCollision();         // 检查碰撞（边界或自身）
};
#endif // WIDGET_H
