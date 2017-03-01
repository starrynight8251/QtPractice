#ifndef MYIMAGEITEM_H
#define MYIMAGEITEM_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>


class MyImageItem : public QGraphicsPixmapItem
{
public:
    MyImageItem(const QRectF& dst_rect, const QPixmap& pixmap,
                const QRectF& src_rect, QGraphicsItem *parent = Q_NULLPTR);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF m_src_rect;
    QRectF m_dst_rect;
};

#endif // MYIMAGEITEM_H
