#ifndef HTTYD_MAINWINDOW_H
#define HTTYD_MAINWINDOW_H

#include <QMainWindow>
#include <vector>

class QStackedWidget;
class QProgressBar;
class QLCDNumber;
class httyd_intro;
class httyd_question_1;
class httyd_question_2;
class httyd_question_3;
class httyd_question_4;
class Flappy_Dragon;

class httyd_mainwindow : public QMainWindow {
    Q_OBJECT

public:
    explicit httyd_mainwindow(QWidget *parent = nullptr);

private slots:
    void handleNext();          // already had
    void onPageChanged(int);    // ← NEW: update UI when pages switch

private:
    QStackedWidget          *stack_;
    httyd_intro             *introScreen_;
    httyd_question_1        *q1_;
    httyd_question_2        *q2_;
    httyd_question_3        *q3_;
    httyd_question_4        *q4_;
    Flappy_Dragon           *flappy_;
    std::vector<int>         order_;
    int                      currentQ_;
};

#endif // HTTYD_MAINWINDOW_H
