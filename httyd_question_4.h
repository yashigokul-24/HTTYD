#ifndef HTTYD_QUESTION_4_H
#define HTTYD_QUESTION_4_H

#include <QDialog>

namespace Ui {
class httyd_question_4;
}

class httyd_question_4 : public QDialog
{
    Q_OBJECT

public:
    explicit httyd_question_4(QWidget *parent = nullptr);
    ~httyd_question_4();

signals:
    void next_httyd();

private:
    Ui::httyd_question_4 *ui;

private slots:
    void on_option_a_clicked();
    void on_option_d_clicked();
    void on_option_b_clicked();
    void handleButtonClicked();
    void on_btn_hint_clicked();
    void on_btn_continue_clicked();
};

#endif // HTTYD_QUESTION_4_H
