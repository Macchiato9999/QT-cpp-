#ifndef GAMESELECT_H
#define GAMESELECT_H

#include <QWidget>

class gameselect : public QWidget
{
    Q_OBJECT
public:
    explicit gameselect(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;
signals:

};

#endif // GAMESELECT_H
