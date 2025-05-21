#ifndef HTTYD_INTRO_H
#define HTTYD_INTRO_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>

extern int lives;
extern int httyd_progress;
extern bool used_hint;

class httyd_intro : public QWidget
{
    Q_OBJECT
public:
    explicit httyd_intro(QWidget *parent = nullptr);

signals:
    void start_httyd();

private :
    QPushButton *start_btn_httyd;
    QPixmap background;


protected :
    void showEvent(QShowEvent *event) override;
    void paintEvent(QPaintEvent*) override;
};

#endif // HTTYD_INTRO_H

