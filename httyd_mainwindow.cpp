#include "httyd_mainwindow.h"
#include <QStackedWidget>
#include <QMessageBox>
#include <QGuiApplication>
#include <QScreen>
#include <QProgressBar>
#include <QLCDNumber>
#include <random>
#include "httyd_intro.h"
#include "httyd_question_1.h"
#include "httyd_question_2.h"
#include "httyd_question_3.h"
#include "httyd_question_4.h"
#include "flappy_dragon.h"


httyd_mainwindow::httyd_mainwindow(QWidget *parent)
    : QMainWindow(parent)
    , currentQ_(0)
{
    // 1) Create the stack
    stack_ = new QStackedWidget(this);
    setCentralWidget(stack_);
    stack_->setWindowTitle("Berk Dragon Rider Test!");

    // 2) Instantiate your screens
    introScreen_ = new httyd_intro(this);
    q1_          = new httyd_question_1(this);
    q2_          = new httyd_question_2(this);
    q3_          = new httyd_question_3(this);
    q4_          = new httyd_question_4(this);
    flappy_      = new Flappy_Dragon(this);

    // 3) Add them in fixed order:
    //    [0]=Intro, [1]=Q1, [2]=Q2, [3]=Q3, [4]=Q4, [5]=Flappy
    stack_->addWidget(introScreen_);
    stack_->addWidget(q1_);
    stack_->addWidget(q2_);
    stack_->addWidget(q3_);
    stack_->addWidget(q4_);
    stack_->addWidget(flappy_);

    // 4) Shuffle the question‐page indices {1,2,3,4}
    order_ = {1,2,3,4};
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(order_.begin(), order_.end(), g);
    }

    // 5) Lock the main window to the Intro size so it’s always centered
    setFixedSize(introScreen_->width(), introScreen_->height());

    // 6) Center the window on the primary screen
    const auto geom = QGuiApplication::primaryScreen()->availableGeometry();
    move((geom.width() - width())/2, (geom.height() - height())/2);

    // 7) Whenever pages change, update progress bar & lives
    connect(stack_, &QStackedWidget::currentChanged, this, &httyd_mainwindow::onPageChanged);

    // 8) Wire Intro → first question
    connect(introScreen_, &httyd_intro::start_httyd, this, [this]() {
        currentQ_ = 0;
        stack_->setCurrentIndex(order_[currentQ_++]);
    });

    // 9) Wire all four question widgets → same handler
    auto connectNext = [&](QWidget* w){
        connect(w, SIGNAL(next_httyd()), this, SLOT(handleNext()));
    };
    connectNext(q1_);
    connectNext(q2_);
    connectNext(q3_);
    connectNext(q4_);

    // 10) Show Intro initially
    stack_->setCurrentIndex(0);
}


// called whenever any question emits next_httyd()
void httyd_mainwindow::handleNext()
{
    // Which page am I on right now?
    int idx = stack_->currentIndex();

    // If I'm on one of the 4 questions (indices 1–4) *and* lives<2, only then show the dialog
    if (idx = 4 && lives < 2) {
        QMessageBox::information(this,
                                 "Not Good Enough!",
                                 "Ye’ve run out of lives, dragon rider. Return to Berk and train once more!");

        // reset game state
        httyd_progress = 0;
        lives = 4;

        // reshuffle question order & reset pointer
        std::shuffle(order_.begin(), order_.end(), std::mt19937{std::random_device{}()});
        currentQ_ = 0;

        // jump back to intro
        stack_->setCurrentIndex(0);
        return;     // important: don’t fall through to “advance page” logic
    }

    // otherwise, if we still have questions left, go to the next shuffled question
    if (currentQ_ < (int)order_.size()) {
        stack_->setCurrentIndex(order_[currentQ_++]);
    }
    else {
        // all four answered successfully → go to Flappy
        stack_->setCurrentIndex(5);
    }
}


// whenever you land on Q1–Q4, refresh its progress & lives display
void httyd_mainwindow::onPageChanged(int idx)
{
    if (idx >= 1 && idx <= 4) {
        QWidget *page = stack_->widget(idx);

        if (auto *pb = page->findChild<QProgressBar*>("httyd_progress_bar")) {
            pb->setValue(httyd_progress);
        }
        if (auto *lcd = page->findChild<QLCDNumber*>("lives_display")) {
            lcd->display(lives);
        }
    }
}
