#include "httyd_question_1.h"
#include "ui_httyd_question_1.h"
#include "httyd_question_2.h"
#include "httyd_questions.h"
#include "httyd_question_4.h"
#include "httyd_question_3.h"
#include "flappy_dragon.h"
#include "httyd_intro.h"
#include <QWidget>
#include <QMessageBox>
#include <QPixmap>
#include <random>
#include <algorithm>
//#include "hp_end_screen.h"


#include <QDebug>

//--------------------------------------------------------------------------------
// define_question1()
// ------------------
// Constructs and returns a fully initialized `question_class` object representing
// the first HTTYD trivia question. Sets the question text, multiple-choice options,
// marks it as not yet asked, and specifies the correct answer.
//--------------------------------------------------------------------------------
question_class define_question1() {
    question_class question_1 = question_class();
    question_1.question =
        "By Thor's hammer! Young Hiccup, the blacksmith's lad, dared to befriend a "
        "Night Fury—most elusive of dragons. But tell me, what did he craft to aid the "
        "beast in flight?";
    question_1.options = {"Saddle", "Tail Fin", "Wing Brace", "Helmet"};
    question_1.is_asked = false;
    question_1.answer   = 'B';
    return question_1;
}

//--------------------------------------------------------------------------------
// httyd_question_1 Constructor
// -----------------------------
// Initializes the question dialog UI for question 1.
//   • Sets fixed window size and background image
//   • Loads the question data from `define_question1()`
//   • Hides the Continue button until an answer is chosen
//   • Updates the progress bar to reflect current progress
//   • Populates question label and option buttons with text
//   • Marks the question as asked and connects each option button to the
//     common answer handler slot.
//--------------------------------------------------------------------------------
httyd_question_1::httyd_question_1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::httyd_question_1)
{
    ui->setupUi(this);
    this->setFixedSize(1280, 720);

    // Stretch the background label to fill the entire dialog
    ui->lbl_background_httyd->resize(this->size());
    QPixmap background_pic(":/images/httyd_background_1.png");
    ui->lbl_background_httyd->setPixmap(
        background_pic.scaled(1280, 720,
                              Qt::IgnoreAspectRatio,
                              Qt::SmoothTransformation));

    // Retrieve and display the first question
    question_class question_1 = define_question1();

    //hint button
    ui->btn_hint->setVisible(false);

    // Hide the Continue button until the user selects an answer
    ui->btn_continue->setVisible(false);

    // Initialize and display current progress on the progress bar
    ui->httyd_progress_bar->setValue(httyd_progress);

    // Initialize and display current lives on the lives counter
    ui->lives_display->display(lives);

    // Populate UI elements with question text and options
    ui->lbl_question_1->setText(question_1.question);
    ui->option_a->setText(question_1.options[0]);
    ui->option_b->setText(question_1.options[1]);
    ui->option_c->setText(question_1.options[2]);
    ui->option_d->setText(question_1.options[3]);

    if (used_hint == false){
        ui->btn_hint->setVisible(true);
    }

    // Mark this question as asked to avoid repetition
    question_1.is_asked = true;

    // Connect each option button to the shared click handler
    connect(ui->option_a, &QPushButton::clicked,
            this, &httyd_question_1::handleButtonClicked);
    connect(ui->option_b, &QPushButton::clicked,
            this, &httyd_question_1::handleButtonClicked);
    connect(ui->option_c, &QPushButton::clicked,
            this, &httyd_question_1::handleButtonClicked);
    connect(ui->option_d, &QPushButton::clicked,
            this, &httyd_question_1::handleButtonClicked);
}



httyd_question_1::~httyd_question_1()
{
    delete ui;
}

// on_option_x_clicked() handles how wrong answers will be dealt with.
void httyd_question_1::on_option_a_clicked()
{
    lives--;
    ui->lives_display->display(lives);
    QWidget *parent_widget = qobject_cast<QWidget *>(parent());
    QMessageBox::information(parent_widget,"By Loki's mischief! Ye've lost yerself a life! (-1 life)","Pick yerself up, Viking—there’s dragons to ride and glory yet to claim!");    
}


void httyd_question_1::on_option_c_clicked()
{
    lives--;
    ui->lives_display->display(lives);
    QWidget *parent_widget = qobject_cast<QWidget *>(parent());
    QMessageBox::information(parent_widget,"By Loki's mischief! Ye've lost yerself a life! (-1 life)","Pick yerself up, Viking—there’s dragons to ride and glory yet to claim!");
}

void httyd_question_1::on_option_d_clicked()
{

    lives--;
    ui->lives_display->display(lives);
    QWidget *parent_widget = qobject_cast<QWidget *>(parent());
    QMessageBox::information(parent_widget,"By Loki's mischief! Ye've lost yerself a life! (-1 life)","Pick yerself up, Viking—there’s dragons to ride and glory yet to claim!");
}

void httyd_question_1::handleButtonClicked(){
    ui->btn_continue->setVisible(true);
    ui->btn_continue->setStyleSheet("background-color: rgb(46, 119, 116)");
    ui->option_a->setDisabled(true);
    ui->option_b->setDisabled(true);
    ui->option_c->setDisabled(true);
    ui->option_d->setDisabled(true);
    httyd_progress = httyd_progress + 25;
}

void httyd_question_1::on_btn_hint_clicked(){
    ui->option_a->setEnabled(false);
    ui->option_d->setEnabled(false);
    used_hint = true;
}

void httyd_question_1::on_btn_continue_clicked(){
    emit next_httyd();
}
