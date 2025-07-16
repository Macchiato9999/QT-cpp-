#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

// 构造函数
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_currentDirection(Right)  // 初始方向向右
    , m_nextDirection(Right)     // 初始下一个方向也向右
    , m_gameOver(false)          // 游戏初始未结束
    , m_score(0)                 // 初始分数为0
{
    ui->setupUi(this);

    setWindowTitle("贪吃蛇");
    setFixedSize(820, 680);      // 设置固定窗口大小

    // 初始化蛇的位置
    initGame();

    // 加载蛇头图片
    m_snakeHeadUp.load(":/qq_pic_merged_1752644468351.jpg");
    m_snakeHeadLeft.load(":/qq_pic_merged_1752644488661.jpg");
    m_snakeHeadDown.load(":/qq_pic_merged_1752644494215.jpg");
    m_snakeHeadRight.load(":/qq_pic_merged_1752644501000.jpg");

    // 检查图片加载情况
    if (m_snakeHeadUp.isNull() || m_snakeHeadDown.isNull() ||
        m_snakeHeadLeft.isNull() || m_snakeHeadRight.isNull()) {
        qDebug() << "警告: 部分蛇头图片加载失败!";
    }

    // 调整图片大小为20x20像素并平滑处理
    m_snakeHeadUp = m_snakeHeadUp.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_snakeHeadDown = m_snakeHeadDown.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_snakeHeadLeft = m_snakeHeadLeft.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_snakeHeadRight = m_snakeHeadRight.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 创建定时器并连接到moveSnake()槽函数，每150毫秒触发一次
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Widget::moveSnake);
    m_timer->start(150); // 每150毫秒移动一次
}

Widget::~Widget()
{
    delete ui;
}

// 初始化游戏状态
void Widget::initGame()
{
    m_snake.clear();  // 清空蛇的身体
    // 初始化蛇的三个部分（头部和两个身体部分）
    m_snake.append(QPoint(100, 100));
    m_snake.append(QPoint(80, 100));
    m_snake.append(QPoint(60, 100));

    m_currentDirection = Right;  // 初始方向向右
    m_nextDirection = Right;     // 下一个方向也向右
    m_gameOver = false;          // 游戏未结束
    m_score = 0;                 // 分数重置为0

    generateFood();  // 生成第一个食物
}

// 生成食物
void Widget::generateFood()
{
    int x, y;
    const int gridSize = 20;  // 网格大小，蛇和食物的移动单位
    const int maxX = (width() / gridSize) - 1;  // X方向最大网格数
    const int maxY = (height() / gridSize) - 1;  // Y方向最大网格数

    // 循环生成随机位置，直到不在蛇身上
    do {
        x = QRandomGenerator::global()->bounded(1, maxX) * gridSize;  // 随机X坐标
        y = QRandomGenerator::global()->bounded(1, maxY) * gridSize;  // 随机Y坐标
    } while (isFoodOnSnake(QPoint(x, y)));  // 检查是否在蛇身上

    m_food = QPoint(x, y);  // 设置食物位置
}

// 检查食物是否在蛇身上
bool Widget::isFoodOnSnake(const QPoint &point)
{
    // 遍历蛇的每个部分，检查是否与给定坐标重合
    for (const auto &segment : m_snake) {
        if (segment == point) {
            return true;
        }
    }
    return false;
}

// 检查碰撞（边界或自身）
bool Widget::checkCollision()
{
    if (m_snake.isEmpty()) return false;  // 如果蛇为空，无碰撞

    QPoint head = m_snake.first();  // 获取蛇头坐标

    // 检查是否碰到边界
    if (head.x() < 0 || head.x() >= width() ||
        head.y() < 0 || head.y() >= height()) {
        return true;  // 碰到边界，发生碰撞
    }

    // 检查是否碰到自己（从第1个索引开始，因为索引0是蛇头）
    for (int i = 1; i < m_snake.size(); ++i) {
        if (head == m_snake[i]) {
            return true;  // 碰到自身，发生碰撞
        }
    }

    return false;  // 无碰撞
}

// 移动蛇的函数，由定时器触发
void Widget::moveSnake()
{
    if (m_gameOver) return;  // 如果游戏已结束，不移动

    // 更新方向（在键盘事件中设置m_nextDirection）
    m_currentDirection = m_nextDirection;

    // 计算新的蛇头位置
    QPoint head = m_snake.first();
    switch (m_currentDirection) {
    case Up:
        head.setY(head.y() - 20);  // 向上移动
        break;
    case Down:
        head.setY(head.y() + 20);  // 向下移动
        break;
    case Left:
        head.setX(head.x() - 20);  // 向左移动
        break;
    case Right:
        head.setX(head.x() + 20);  // 向右移动
        break;
    }

    // 将新头添加到蛇身的前端
    m_snake.prepend(head);

    // 检查是否吃到食物
    if (head == m_food) {
        m_score += 10;  // 吃到食物，分数加10
        generateFood();  // 生成新食物
    } else {
        // 没有吃到食物，移除尾部，保持蛇的长度不变
        m_snake.removeLast();
    }

    // 检查碰撞
    if (checkCollision()) {
        m_gameOver = true;  // 发生碰撞，游戏结束
    }

    // 重绘界面
    update();
}

// 绘制事件，每当需要重绘界面时调用
void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);  // 创建绘图对象
    painter.setRenderHint(QPainter::Antialiasing);  // 启用抗锯齿，使图形更平滑

    // 绘制背景为黑色
    painter.fillRect(rect(), Qt::black);

    // 绘制食物（绿色圆形）
    painter.setBrush(Qt::green);
    painter.drawEllipse(m_food.x(), m_food.y(), 20, 20);

    // 绘制蛇
    drawSnake(painter);

    // 绘制分数
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 16));
    painter.drawText(20, 30, QString("分数: %1").arg(m_score));

    // 如果游戏结束，绘制游戏结束信息
    if (m_gameOver) {
        painter.setPen(Qt::red);
        painter.setFont(QFont("Arial", 30));
        painter.drawText(rect(), Qt::AlignCenter, "游戏结束！按R键重新开始");
    }
}

// 键盘按下事件，处理用户输入
void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        // 只有当前方向不是向下时，才能向上移动（防止180度转向）
        if (m_currentDirection != Down)
            m_nextDirection = Up;
        break;
    case Qt::Key_Down:
        // 只有当前方向不是向上时，才能向下移动
        if (m_currentDirection != Up)
            m_nextDirection = Down;
        break;
    case Qt::Key_Left:
        // 只有当前方向不是向右时，才能向左移动
        if (m_currentDirection != Right)
            m_nextDirection = Left;
        break;
    case Qt::Key_Right:
        // 只有当前方向不是向左时，才能向右移动
        if (m_currentDirection != Left)
            m_nextDirection = Right;
        break;
    case Qt::Key_R:
        // 按R键重新开始游戏
        initGame();
        break;
    default:
        QWidget::keyPressEvent(event);  // 其他按键使用默认处理
    }
}

// 绘制蛇的函数
void Widget::drawSnake(QPainter &painter)
{
    if (m_snake.isEmpty()) return;  // 如果蛇为空，不绘制

    // 根据当前方向选择正确的蛇头图片
    QPixmap headImg;
    switch (m_currentDirection) {
    case Up:
        headImg = m_snakeHeadUp;
        break;
    case Down:
        headImg = m_snakeHeadDown;
        break;
    case Left:
        headImg = m_snakeHeadLeft;
        break;
    case Right:
        headImg = m_snakeHeadRight;
        break;
    }

    // 绘制蛇头
    painter.drawPixmap(m_snake.first().x(), m_snake.first().y(), 20, 20, headImg);

    // 绘制蛇身（红色圆形）
    painter.setBrush(Qt::red);
    painter.setPen(Qt::NoPen);  // 无边框
    for (int i = 1; i < m_snake.size(); ++i) {
        painter.drawEllipse(m_snake[i].x(), m_snake[i].y(), 18, 18);
    }
}
