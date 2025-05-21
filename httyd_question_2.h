#ifndef HTTYD_QUESTION_2_H
#define HTTYD_QUESTION_2_H

#include <QDialog>

namespace Ui {
class httyd_question_2;
}

class httyd_question_2 : public QDialog
{
    Q_OBJECT

public:
    explicit httyd_question_2(QWidget *parent = nullptr);
    ~httyd_question_2();

signals:
    void next_httyd();

private:
    Ui::httyd_question_2 *ui;

private slots:
    void on_option_a_clicked();
    void on_option_c_clicked();
    void on_option_b_clicked();
    void handleButtonClicked();
    void on_btn_hint_clicked();
    void on_btn_continue_clicked();
};

#endif // HTTYD_QUESTION_2_H
