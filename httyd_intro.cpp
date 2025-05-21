#include "httyd_intro.h"
#include "httyd_questions.h"   // for question_randomiser
#include <QPushButton>
#include <QPainter>
#include <QFont>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QShowEvent>
//#include "hp_end_screen.h"


int lives = 4;
int httyd_progress = 0;
bool used_hint = false;

httyd_intro::httyd_intro(QWidget *parent)
    : QWidget(parent),
    background(":/images/Intro.png")    // ← your image here
{
    setFixedSize(1280, 720);
    setWindowTitle("Hahaha! Welcome to the land of Dragons!");

    // ——— Prepare fade effect but don't start it yet ———
    auto *fadeEffect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(fadeEffect);
    fadeEffect->setOpacity(0.0);             // start fully transparent

    // ——— Create the Start button ———
    start_btn_httyd = new QPushButton("Start", this);
    start_btn_httyd->setFixedSize(250, 70);
    start_btn_httyd->setFont(QFont("Helvetica", 28, QFont::Bold));
    start_btn_httyd->move((width() - 250)/2, height() - 150);

    // ——— On click: emit signal to MainWindow ———
    connect(start_btn_httyd, &QPushButton::clicked, this, [this]() {
        emit start_httyd();
    });
}

void httyd_intro::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);

    // ——— Actually run the fade-in now that the window is visible ———
    auto *fadeEffect = static_cast<QGraphicsOpacityEffect*>(graphicsEffect());
    auto *fadeAnim = new QPropertyAnimation(fadeEffect, "opacity", this);
    fadeAnim->setDuration(1200);                            // 1.2s fade
    fadeAnim->setStartValue(0.0);                           // from transparent
    fadeAnim->setEndValue(1.0);                             // to opaque
    fadeAnim->setEasingCurve(QEasingCurve::InOutQuad);      // smooth ease-in/out
    fadeAnim->start(QAbstractAnimation::DeleteWhenStopped);
}

void httyd_intro::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.drawPixmap(rect(), background);
}
