#ifndef MYSHAPEITEM_H
#define MYSHAPEITEM_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class MyShapeItem : public QGraphicsItem
 {
 public:
    MyShapeItem(QColor col,QGraphicsItem *parent = Q_NULLPTR);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

 private:
     QColor color;
     bool   Pressed;
};

#endif // MYSHAPEITEM_H
