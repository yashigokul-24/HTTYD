#include "httyd_question_2.h"
#include "ui_httyd_question_2.h"
#include "httyd_questions.h"
#include "httyd_question_1.h"
#include "httyd_question_4.h"
#include "httyd_question_3.h"
#include "httyd_intro.h"
#include "flappy_dragon.h"
#include <QWidget>
#include <QMessageBox>
#include <QPixmap>
#include <random>
#include <algorithm>
#include <QDebug>

//--------------------------------------------------------------------------------
// define_question2()
// ------------------
// Constructs and returns a question_class instance for Question 2.
// - Initializes the question text with a dramatic Viking-style prompt.
// - Sets up four answer options in the required order.
// - Marks the question as not yet asked.
// - Specifies the correct answer ('D' corresponds to "Drago").
//--------------------------------------------------------------------------------
question_class define_question2() {
    question_class question_2 = question_class();
    question_2.question =
        "In the days of yore, a mighty foe sought to enslave dragons and men alike. "
        "Who was this warlord with a heart as cold as the northern seas?";
    question_2.options = {"Grimmel", "Alvin", "Dagger", "Drago"};
    question_2.is_asked = false;
    question_2.answer   = 'D';  // 'D' → "Drago"
    return question_2;
}

//--------------------------------------------------------------------------------
// httyd_question_2 Constructor
// -----------------------------
// Sets up the Question 2 dialog UI:
// - Calls setupUi() to lay out widgets from the .ui file.
// - Enforces a fixed 1280×720 window and stretches the background image.
// - Retrieves the prompt and options via define_question2().
// - Hides the Continue button until the user selects an answer.
// - Displays the question text and populates option buttons.
// - Updates the shared progress bar to the current value.
// - Marks this question as asked to prevent repeats.
// - Connects each option button to the common answer handler slot.
//--------------------------------------------------------------------------------
httyd_question_2::httyd_question_2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::httyd_question_2)
{
    ui->setupUi(this);

    // Fix dialog size and apply background
    this->setFixedSize(1280, 720);
    ui->lbl_background_httyd->resize(this->size());
    QPixmap background_pic(":/images/httyd_background_2.png");
    ui->lbl_background_httyd->setPixmap(
        background_pic.scaled(1280, 720,
                              Qt::IgnoreAspectRatio,
                              Qt::SmoothTransformation)
        );

    // Load question data
    question_class question_2 = define_question2();

    if (used_hint == false /*&& hp_end_screen::hp_hint = true*/){
        ui->btn_hint->setVisible(true);
    }

    // Hide Continue until an answer is chosen
    ui->btn_continue->setVisible(false);

    // Display question text and options
    ui->lbl_question_2->setText(question_2.question);
    ui->option_a->setText(question_2.options[0]);
    ui->option_b->setText(question_2.options[1]);
    ui->option_c->setText(question_2.options[2]);
    ui->option_d->setText(question_2.options[3]);

    // Update progress bar to reflect current progress
    ui->httyd_progress_bar->setValue(httyd_progress);

    // Initialize and display current lives on the lives counter
    ui->lives_display->display(lives);

    // Mark as asked so it won’t be shown again
    question_2.is_asked = true;

    // Connect each option button to the shared click handler
    connect(ui->option_a, &QPushButton::clicked,
            this, &httyd_question_2::handleButtonClicked);
    connect(ui->option_b, &QPushButton::clicked,
            this, &httyd_question_2::handleButtonClicked);
    connect(ui->option_c, &QPushButton::clicked,
            this, &httyd_question_2::handleButtonClicked);
    connect(ui->option_d, &QPushButton::clicked,
            this, &httyd_question_2::handleButtonClicked);
}



httyd_question_2::~httyd_question_2()
{
    delete ui;
}

void httyd_question_2::on_option_a_clicked()
{
    lives--;
    ui->lives_display->display(lives);
    QWidget *parent_widget = qobject_cast<QWidget *>(parent());
    QMessageBox::information(parent_widget,"By Loki's mischief! Ye've lost yerself a life! (-1 life)","Pick yerself up, Viking—there’s dragons to ride and glory yet to claim!");
}

void httyd_question_2::on_option_c_clicked()
{
    lives--;
    ui->lives_display->display(lives);
    QWidget *parent_widget = qobject_cast<QWidget *>(parent());
    QMessageBox::information(parent_widget,"By Loki's mischief! Ye've lost yerself a life! (-1 life)","Pick yerself up, Viking—there’s dragons to ride and glory yet to claim!");
}

void httyd_question_2::on_option_b_clicked()
{

    lives--;
    ui->lives_display->display(lives);
    QWidget *parent_widget = qobject_cast<QWidget *>(parent());
    QMessageBox::information(parent_widget,"By Loki's mischief! Ye've lost yerself a life! (-1 life)","Pick yerself up, Viking—there’s dragons to ride and glory yet to claim!");
}

void httyd_question_2::handleButtonClicked(){
    ui->btn_continue->setVisible(true);
    ui->btn_continue->setStyleSheet("background-color: rgb(46, 119, 116)");
    ui->option_a->setDisabled(true);
    ui->option_b->setDisabled(true);
    ui->option_c->setDisabled(true);
    ui->option_d->setDisabled(true);
    httyd_progress = httyd_progress + 25;
}

void httyd_question_2::on_btn_hint_clicked(){
    ui->option_b->setEnabled(false);
    ui->option_c->setEnabled(false);
    used_hint = true;
}

// In httyd_question_1.cpp (and likewise in 2,3,4):
void httyd_question_2::on_btn_continue_clicked()
{
    emit next_httyd();   // NOTHING ELSE—no close(), no shuffle(), no QMessageBox
}
