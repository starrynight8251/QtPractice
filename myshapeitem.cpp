#include <QDebug>
#include "myshapeitem.h"

// 図形描画領域定数
static const int RADIUS = 30;
static const int RX = -RADIUS;
static const int RY = -RADIUS;
static const int RW = RADIUS * 2;
static const int RH = RADIUS * 2;

// コンストラクタ　色を設定する
MyShapeItem::MyShapeItem(QColor col,QGraphicsItem *parent)
    // 親クラスのコンストラクタを呼び出す
    :QGraphicsItem(parent){
    color = col;
    Pressed = false;
}

// 図形描画領域を定義
QRectF MyShapeItem::boundingRect() const{
    return QRectF(RX, RY, RW, RH);
}

// マウスクリックの際の形状を定義
QPainterPath MyShapeItem::shape() const{
    QPainterPath path;
    if(Pressed)
    {
        path.addRect(boundingRect());
    }
    else
    {
        path.addEllipse(boundingRect());
    }
    return path;
}

// アイテムを描画する
void MyShapeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    QRectF rect = boundingRect();
    painter->setBrush(color);
    painter->setRenderHint(QPainter::Antialiasing);
    if(Pressed)
    {
        painter->drawRect(rect);
    }
    else
    {
        painter->drawEllipse(rect);
    }
}

// 図形上でマウスボタンが押された時のイベント処理
void MyShapeItem::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    qDebug() << "mousePressEvent !!";
    Pressed = !Pressed;
    update();
}

// 図形上でマウスボタンが動かされた時のイベント処理
void MyShapeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *){
    qDebug() << "mouseMoveEvent !!";
}

// 図形上でマウスボタンが離された時のイベント処理
void MyShapeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    qDebug() << "mouseReleaseEvent !!";
}
