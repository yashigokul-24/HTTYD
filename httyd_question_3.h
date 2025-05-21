#ifndef HTTYD_QUESTION_3_H
#define HTTYD_QUESTION_3_H

#include <QDialog>

namespace Ui {
class httyd_question_3;
}

class httyd_question_3 : public QDialog
{
    Q_OBJECT

public:
    explicit httyd_question_3(QWidget *parent = nullptr);
    ~httyd_question_3();

signals:
    void next_httyd();

private:
    Ui::httyd_question_3 *ui;

private slots:
    void on_option_a_clicked();
    void handleButtonClicked();
    void on_btn_continue_clicked();
};

#endif // HTTYD_QUESTION_3_H
