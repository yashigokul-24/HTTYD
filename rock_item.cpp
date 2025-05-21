#include "rock_item.h"
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QTransform>

Rock_Item::Rock_Item(QGraphicsScene *scene)
    : x_animation_(new QPropertyAnimation(this, "x", this)),
    current_x_(scene->sceneRect().width())
{
    // Load original rock pixmaps
    QPixmap top_pix(":/images/rock_top.PNG");
    QPixmap bottom_pix_orig(":/images/rock_bottom.PNG");

    // Increase rock size for flush appearance (80% of original)
    constexpr qreal scale_factor = 1;
    top_pix    = top_pix.scaled(
        top_pix.width() * scale_factor,
        top_pix.height() * scale_factor,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        );
    QPixmap bottom_pix = bottom_pix_orig.scaled(
        bottom_pix_orig.width() * scale_factor,
        bottom_pix_orig.height() * scale_factor,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        );

    // Create pixmap items and group them
    auto *top_item    = new QGraphicsPixmapItem(top_pix);
    auto *bottom_item = new QGraphicsPixmapItem(bottom_pix);
    addToGroup(top_item);
    addToGroup(bottom_item);

    // Continue with randomized vertical gap code
    // Randomize vertical gap so dragon can fly through, allowing near-top or near-bottom
    const int gap_size = 200; // vertical space between rocks
    const int min_gap_y = gap_size/2; // allow gap center from very top
    const int max_gap_y = static_cast<int>(scene->sceneRect().height()) - gap_size/2; // down to very bottom
    int gap_center = QRandomGenerator::global()->bounded(min_gap_y, max_gap_y + 1);

     // Position top rock above the gap
    //int top_y = gap_center - gap_size - top_item->boundingRect().height()/2;
    top_item->setPos(-20, -100 );

    // Position bottom rock below the gap
    int bottom_y = gap_center + gap_size/2;
    bottom_item->setPos(0, bottom_y);


    // Add this group to the scene
    scene->addItem(this);

    // Animate the rock moving left across the scene
    x_animation_->setDuration(4000);
    x_animation_->setStartValue(current_x_);
    x_animation_->setEndValue(-top_item->boundingRect().width());
    connect(x_animation_, &QPropertyAnimation::finished,
            this, &Rock_Item::freeze_in_place);
    x_animation_->start();
}

void Rock_Item::setX(qreal x)
{
    current_x_ = x;
    setPos(current_x_, 0);
}

void Rock_Item::freeze_in_place()
{
    x_animation_->stop();
    if (scene()) {
        scene()->removeItem(this);
    }
    deleteLater();
}
