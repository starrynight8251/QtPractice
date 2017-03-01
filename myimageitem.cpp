#include "myimageitem.h"

// コンストラクタ　転送先四角形と転送元四角形を指定する
MyImageItem::MyImageItem(const QRectF& dst_rect, const QPixmap& pixmap,
                         const QRectF& src_rect, QGraphicsItem *parent)
    // 親クラスのコンストラクタを呼び出す
    :QGraphicsPixmapItem(pixmap, parent){
    m_dst_rect = dst_rect;
    m_src_rect = src_rect;
}

// 図形描画領域を定義
QRectF MyImageItem::boundingRect() const{
    return this->m_dst_rect;
}

// マウスクリックの際の形状を定義
QPainterPath MyImageItem::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

// アイテムを描画する
void MyImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
           QWidget *){
    painter->drawPixmap(m_dst_rect, QGraphicsPixmapItem::pixmap(), m_src_rect);
}
