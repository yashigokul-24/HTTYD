#include "httyd_question_4.h"
#include "ui_httyd_question_4.h"
#include "httyd_question_1.h"
#include "httyd_questions.h"
#include "flappy_dragon.h"
#include "httyd_intro.h"
#include <QWidget>
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include <random>
#include <algorithm>
//#include "hp_end_screen.h"


#include <iostream>
using namespace std;

//--------------------------------------------------------------------------------
// define_question4()
// ------------------
// Constructs and returns a question_class instance for Question 4.
// - Sets the trivia prompt asking about Toothless' hidden power.
// - Defines four answer options in the specified order.
// - Marks the question as not yet asked.
// - Assigns the correct answer ('C' corresponds to "Invisibility").
//--------------------------------------------------------------------------------
question_class define_question4() {
    question_class question_4 = question_class();
    question_4.question =
        "Toothless, the Night Fury, discovered a hidden power when meeting his "
        "shimmering counterpart. What did this newfound ability allow him to do?";
    question_4.options = {"Echolocation", "Fire Burst", "Invisibility", "Flight Solo"};
    question_4.is_asked = false;
    question_4.answer   = 'C';  // 'C' → "Invisibility"
    return question_4;
}

//--------------------------------------------------------------------------------
// httyd_question_4 Constructor
// -----------------------------
// Sets up the Question 4 dialog UI:
// - Calls setupUi() to lay out widgets from the .ui file.
// - Enforces a fixed 1280×720 window size and applies the background image.
// - Retrieves the question data via define_question4().
// - Hides the Continue button until the user selects an option.
// - Populates the question label and four answer buttons.
// - Updates the shared progress bar to reflect current httyd_progress.
// - Marks the question as asked to prevent repetition.
// - Connects each option button to the shared answer handler slot.
//--------------------------------------------------------------------------------
httyd_question_4::httyd_question_4(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::httyd_question_4)
{
    ui->setupUi(this);

    // Fix window size and stretch background to fill the dialog
    this->setFixedSize(1280, 720);
    ui->lbl_background_httyd->resize(this->size());
    QPixmap background_pic(":/images/httyd_background_4.png");
    ui->lbl_background_httyd->setPixmap(
        background_pic.scaled(1280, 720,
                              Qt::IgnoreAspectRatio,
                              Qt::SmoothTransformation)
        );

    // Load the question data for Q4
    question_class question_4 = define_question4();

    // Hide Continue button until an answer is chosen
    ui->btn_continue->setVisible(false);

    // Display the question text and options
    ui->lbl_question_4->setText(question_4.question);
    ui->option_a->setText(question_4.options[0]);
    ui->option_b->setText(question_4.options[1]);
    ui->option_c->setText(question_4.options[2]);
    ui->option_d->setText(question_4.options[3]);

    // Update the progress bar to reflect current progress
    ui->httyd_progress_bar->setValue(httyd_progress);

    if (used_hint == false /*&& hp_end_screen::hp_hint = true*/){
        ui->btn_hint->setVisible(true);
    }

    // Initialize and display current lives on the lives counter
    ui->lives_display->display(lives);

    // Mark this question as asked so it won't repeat
    question_4.is_asked = true;

    // Connect each option button to the unified click handler
    connect(ui->option_a, &QPushButton::clicked,
            this, &httyd_question_4::handleButtonClicked);
    connect(ui->option_b, &QPushButton::clicked,
            this, &httyd_question_4::handleButtonClicked);
    connect(ui->option_c, &QPushButton::clicked,
            this, &httyd_question_4::handleButtonClicked);
    connect(ui->option_d, &QPushButton::clicked,
            this, &httyd_question_4::handleButtonClicked);
}


httyd_question_4::~httyd_question_4()
{
    delete ui;
}

void httyd_question_4::on_option_a_clicked()
{
    lives--;
    ui->lives_display->display(lives);
    QWidget *parent_widget = qobject_cast<QWidget *>(parent());
    QMessageBox::information(parent_widget,"By Loki's mischief! Ye've lost yerself a life! (-1 life)","Pick yerself up, Viking—there’s dragons to ride and glory yet to claim!");
}

void httyd_question_4::on_option_d_clicked()
{
    lives--;
    ui->lives_display->display(lives);
    QWidget *parent_widget = qobject_cast<QWidget *>(parent());
    QMessageBox::information(parent_widget,"By Loki's mischief! Ye've lost yerself a life! (-1 life)","Pick yerself up, Viking—there’s dragons to ride and glory yet to claim!");
}

void httyd_question_4::on_option_b_clicked()
{

    lives--;
    ui->lives_display->display(lives);
    QWidget *parent_widget = qobject_cast<QWidget *>(parent());
    QMessageBox::information(parent_widget,"By Loki's mischief! Ye've lost yerself a life! (-1 life)","Pick yerself up, Viking—there’s dragons to ride and glory yet to claim!");
}

void httyd_question_4::handleButtonClicked(){
    ui->btn_continue->setVisible(true);
    ui->btn_continue->setStyleSheet("background-color: rgb(46, 119, 116)");
    ui->option_a->setDisabled(true);
    ui->option_b->setDisabled(true);
    ui->option_c->setDisabled(true);
    ui->option_d->setDisabled(true);
    httyd_progress = httyd_progress + 25;
}

void httyd_question_4::on_btn_hint_clicked(){
    ui->option_b->setEnabled(false);
    ui->option_d->setEnabled(false);
    used_hint = true;
}


void httyd_question_4::on_btn_continue_clicked()
{
    emit next_httyd();
}

