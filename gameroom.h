/*(原代码)

#ifndef GAMEROOM_H
#define GAMEROOM_H

#include <QWidget>

class GameRoom : public QWidget
{
    Q_OBJECT
public:
    explicit GameRoom(QWidget *parent = nullptr);

signals:

};

#endif // GAMEROOM_H

*/
#ifndef GAMEROOM_H
#define GAMEROOM_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QVector>
#include <QPoint>
#include <QRandomGenerator>
#include <QPixmap>
#include<QPushButton>
#include <QMessageBox>


class GameRoom : public QWidget
{
    Q_OBJECT

public:
     explicit GameRoom(QWidget *parent = nullptr);
     ~GameRoom() { delete m_timer; } // 仅需释放定时器资源

    void setSpeedInterval(int);


signals:
    void backToSelect(); // 回到游戏选择界面的信号


protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void moveSnake();

private:
     bool m_useDefaultHead;  // 新增标志，用于判断是否使用默认样式
    void drawSnake(QPainter &painter);

    // 蛇相关属性
    QVector<QPoint> m_snake;
    QPixmap m_snakeHeadUp;
    QPixmap m_snakeHeadDown;
    QPixmap m_snakeHeadLeft;
    QPixmap m_snakeHeadRight;

    // 游戏属性
    enum Direction { Up, Down, Left, Right };
    Direction m_currentDirection;
    Direction m_nextDirection;
    QPoint m_food;
    bool m_gameOver;
    bool m_gameStarted;
    int m_score;
    int m_speedInterval;
    QTimer *m_timer;

    // 辅助函数
    void initUI();
    void initGame();
    void generateFood();
    bool isFoodOnSnake(const QPoint &point);
    bool checkCollision();
};

#endif // GAMEROOM_H
