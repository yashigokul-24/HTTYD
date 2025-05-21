#include "dragon_item.h"
#include <QTimer>


// Constructor: initialize the pixmap item, animation objects, and start the flap timer
dragon_item::dragon_item(const QPixmap &pixmap)
    : QGraphicsPixmapItem(pixmap),                           // set initial image
    state_(FlapMiddle),                                    // start in the “middle” flap state
    current_y_(0),                                         // initial vertical offset
    rotation_angle_(0),                                    // initial rotation angle
    y_animation_(new QPropertyAnimation(this, "y", this)), // animate vertical movement
    rotation_animation_(new QPropertyAnimation(this, "rotation", this)) // animate rotation
{
    // Pivot rotations around the pixmap’s center
    setTransformOriginPoint(boundingRect().center());

    // Timer that ticks every 150 ms to cycle through wing-flap frames
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &dragon_item::update_pixmap);
    timer->start(150);
}

// Called when the dragon “shoots up” (e.g. on a flap input).
// Rotates the sprite upward and moves it up.

void dragon_item::shoot_up() {
    // --- Rotation animation ---
    rotation_animation_->stop();
    rotation_animation_->setDuration(200);             // 200 ms rotation
    rotation_animation_->setStartValue(rotation_angle_);// from current angle
    rotation_animation_->setEndValue(-30);             // to –30° (tilted up)
    rotation_animation_->start();

    // --- Vertical movement animation ---
    y_animation_->stop();
    y_animation_->setDuration(200);                    // 200 ms movement
    y_animation_->setStartValue(current_y_);           // from current Y
    y_animation_->setEndValue(current_y_ - 50);        // to 50 units higher
    y_animation_->start();
}

// Called when the dragon “shoots down” (e.g. falling).
// Rotates the sprite downward and moves it down.

void dragon_item::shoot_down() {
    // --- Rotation animation ---
    rotation_animation_->stop();
    rotation_animation_->setDuration(200);
    rotation_animation_->setStartValue(rotation_angle_);
    rotation_animation_->setEndValue(30);              // to +30° (tilted down)
    rotation_animation_->start();

    // --- Vertical movement animation ---
    y_animation_->stop();
    y_animation_->setDuration(200);
    y_animation_->setStartValue(current_y_);
    y_animation_->setEndValue(current_y_ + 50);        // to 50 units lower
    y_animation_->start();
}


// update_pixmap(): cycles through the FlapUp → FlapMiddle → FlapDown states,
// swapping the QPixmap each time to simulate wing flapping.

void dragon_item::update_pixmap() {
    switch (state_) {
    case FlapUp:
        setPixmap(QPixmap(":/images/dragon_middle.PNG")); // transition up→middle
        state_ = FlapMiddle;
        break;

    case FlapMiddle:
        setPixmap(QPixmap(":/images/dragon_down.PNG"));   // transition middle→down
        state_ = FlapDown;
        break;

    case FlapDown:
    default:
        setPixmap(QPixmap(":/images/dragon_up.PNG"));     // transition down→up
        state_ = FlapUp;
        break;
    }
}
