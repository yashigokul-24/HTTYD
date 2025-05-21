#ifndef DRAGON_ITEM_H
#define DRAGON_ITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class dragon_item : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)

public:
    explicit dragon_item(const QPixmap &pixmap);
    qreal y() const { return current_y_; }
    qreal rotation() const { return rotation_angle_; }

public slots:
    void setY(qreal y) { current_y_ = y; QGraphicsPixmapItem::setY(y); }
    void setRotation(qreal r) { rotation_angle_ = r; QGraphicsPixmapItem::setRotation(r); }
    void shoot_up();
    void shoot_down();

private slots:
    void update_pixmap();

private:
    enum DragonState { FlapUp, FlapMiddle, FlapDown } state_;
    qreal current_y_;
    qreal rotation_angle_;
    QPropertyAnimation *y_animation_;
    QPropertyAnimation *rotation_animation_;
};

#endif // DRAGON_ITEM_H
