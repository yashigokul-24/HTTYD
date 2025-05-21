#ifndef ROCK_ITEM_H
#define ROCK_ITEM_H

#include <QObject>
#include <QGraphicsItemGroup>
#include <QPropertyAnimation>

class Rock_Item : public QObject, public QGraphicsItemGroup {
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)

public:
    explicit Rock_Item(QGraphicsScene *scene);
    qreal x() const { return current_x_; }

public slots:
    void setX(qreal x);
    void freeze_in_place();

private:
    QPropertyAnimation *x_animation_;
    qreal               current_x_;
};

#endif // ROCK_ITEM_H
