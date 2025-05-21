#include "httyd_question_3.h"
#include "ui_httyd_question_3.h"
#include "httyd_questions.h"
#include "httyd_question_1.h"
#include "httyd_question_2.h"
#include "httyd_question_4.h"
#include "httyd_intro.h"
#include "flappy_dragon.h"
#include <QWidget>
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include <random>
#include <algorithm>
//#include "hp_end_screen.h"

//--------------------------------------------------------------------------------
// define_question3()
// ------------------
// Constructs and returns a question_class instance for Question 3.
// - Initializes the statement about Vikings and dragons as the prompt.
// - Provides two options: "True" and "False" for the user to choose.
// - Marks the question as not yet asked.
// - Sets the correct answer ('F' corresponds to "False").
//--------------------------------------------------------------------------------
question_class define_question3() {
    question_class question_3 = question_class();
    question_3.question =
        "In the early days, the Vikings of Berk lived in harmony with dragons, "
        "sharing mead and tales by the hearth.";
    question_3.options = {"True", "False"};
    question_3.is_asked = false;
    question_3.answer   = 'F';  // 'F' → "False"
    return question_3;
}

//--------------------------------------------------------------------------------
// httyd_question_3 Constructor
// -----------------------------
// Sets up the Question 3 dialog UI:
// - Calls setupUi() to construct widgets from the .ui file.
// - Enforces a fixed 1280×720 window size and applies the background image.
// - Retrieves the question data via define_question3().
// - Hides the Continue button until the user selects an answer.
// - Populates the question label and two option buttons.
// - Updates the shared progress bar with the current httyd_progress value.
// - Marks the question as asked to prevent it from repeating.
// - Connects each option button to the unified answer handler slot.
//--------------------------------------------------------------------------------
httyd_question_3::httyd_question_3(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::httyd_question_3)
{
    ui->setupUi(this);

    // Fix dialog size and stretch the background to fit
    this->setFixedSize(1280, 720);
    ui->lbl_background_httyd->resize(this->size());
    QPixmap background_pic(":/images/httyd_background_3.png");
    ui->lbl_background_httyd->setPixmap(
        background_pic.scaled(1280, 720,
                              Qt::IgnoreAspectRatio,
                              Qt::SmoothTransformation)
        );

    // Load the question data for Q3
    question_class question_3 = define_question3();


    // Hide the Continue button until an answer is chosen
    ui->btn_continue->setVisible(false);

    // Display the question text and option buttons
    ui->lbl_question_3->setText(question_3.question);
    ui->option_a->setText(question_3.options[0]);
    ui->option_b->setText(question_3.options[1]);

    // Update the progress bar to reflect current progress
    ui->httyd_progress_bar->setValue(httyd_progress);

    // Initialize and display current lives on the lives counter
    ui->lives_display->display(lives);

    // Mark this question as asked
    question_3.is_asked = true;

    // Connect each option to the shared click handler
    connect(ui->option_a, &QPushButton::clicked,
            this, &httyd_question_3::handleButtonClicked);
    connect(ui->option_b, &QPushButton::clicked,
            this, &httyd_question_3::handleButtonClicked);
}


httyd_question_3::~httyd_question_3()
{
    delete ui;
}

void httyd_question_3::on_option_a_clicked()
{
    lives--;
    ui->lives_display->display(lives);
    QWidget *parent_widget = qobject_cast<QWidget *>(parent());
    QMessageBox::information(parent_widget,"By Loki's mischief! Ye've lost yerself a life! (-1 life)","Pick yerself up, Viking—there’s dragons to ride and glory yet to claim!");
}

void httyd_question_3::handleButtonClicked(){
    ui->btn_continue->setVisible(true);
    ui->btn_continue->setStyleSheet("background-color: rgb(46, 119, 116)");
    ui->option_a->setDisabled(true);
    ui->option_b->setDisabled(true);
    httyd_progress = httyd_progress + 25;
}


void httyd_question_3::on_btn_continue_clicked()
{
    emit next_httyd();
}
