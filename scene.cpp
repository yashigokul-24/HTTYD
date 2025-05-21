#include "scene.h"
#include "dragon_item.h"
#include "rock_item.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QMessageBox>
#include <QWidget>
#include <QMediaPlayer>
#include <QPropertyAnimation>
#include <QEasingCurve>

Scene::Scene(QObject *parent)
    : QGraphicsScene(parent),
    dragon_item_(nullptr),
    rock_timer_(new QTimer(this)),
    game_timer_(new QTimer(this))
{

    // Define scene rect at 16:9 resolution
    setSceneRect(0, 0, 1280, 1080);
    connect(rock_timer_, &QTimer::timeout,
            this,         &Scene::spawn_rock);
    connect(game_timer_, &QTimer::timeout,
            this,         &Scene::game_over);
}

void Scene::start_game() {


    // Draw and scale the background to fill the scene
    auto bg_pix = QPixmap(":/images/cave.PNG");
    bg_pix = bg_pix.scaled(
        sceneRect().size().toSize(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        );
    addPixmap(bg_pix)->setZValue(-1);

    // Create and position the dragon
    dragon_item_ = new dragon_item(
        QPixmap(":/images/dragon_middle.PNG")
        );
    dragon_item_->setPos(100, sceneRect().height() / 2);
    addItem(dragon_item_);

    // Start spawning rocks every 2 seconds
    rock_timer_->start(2000);

    // Start overall game timer (20 seconds)
    game_timer_->setSingleShot(true);
    game_timer_->start(20000);
}

void Scene::keyPressEvent(QKeyEvent *event) {
    if (!dragon_item_) return;
    if (event->key() == Qt::Key_Up) {
        dragon_item_->shoot_up();
    } else if (event->key() == Qt::Key_Down) {
        dragon_item_->shoot_down();
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::spawn_rock() {
    // Each Rock_Item adds itself to the scene in its constructor
    new Rock_Item(this);
}

void Scene::game_over() {
    // Stop spawning new rocks
    rock_timer_->stop();

    // Show a professional message box
    QWidget *parent_widget = qobject_cast<QWidget *>(parent());
    QMessageBox::information(
        parent_widget,
        "Farewell Dragon Rider!",
        "Yers could handle this Nightfury, but can you handle the terrible terror to come...?"
        );

    // ——— Fade-out animation on the window ———
    auto *fadeAnim = new QPropertyAnimation(parent_widget, "windowOpacity", this);
    fadeAnim->setDuration(1200);                              // match the intro’s pace :contentReference[oaicite:4]{index=4}
    fadeAnim->setStartValue(1.0);                             // start fully opaque
    fadeAnim->setEndValue(0.0);                               // end fully transparent
    fadeAnim->setEasingCurve(QEasingCurve::InOutQuad);        // smooth ease-in-out :contentReference[oaicite:5]{index=5}

    // Once done, close the window
    connect(fadeAnim, &QPropertyAnimation::finished,
            parent_widget, &QWidget::close);

    fadeAnim->start(QAbstractAnimation::DeleteWhenStopped);
}
