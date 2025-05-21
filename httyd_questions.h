#ifndef HTTYD_QUESTIONS_H
#define HTTYD_QUESTIONS_H
#include <QString>
#include<QChar>
#include <vector>
#include <QVector>
#include <algorithm>
#include <random>


class question_class {
public:
    QString question;
    std::vector<QString> options;
    bool is_asked;
    QChar answer;

    question_class() {}

    question_class(QString s_question,  std::vector<QString> s_options, bool b_asked, QChar c_answer)
        : question(s_question), options(s_options), is_asked(b_asked), answer(c_answer) {}
};

#include "httyd_question_1.h"
#include "httyd_question_2.h"
#include "httyd_question_3.h"
#include "httyd_question_4.h"

class question_randomiser {
public:
    static QVector<int> order;
    static int index;

    static void shuffle(){
        order={0,1,2,3};
        static std::random_device rd;
        static std::mt19937 g(rd());
        std::shuffle(order.begin(),order.end(),g);
        index = 0;
    }

    static QWidget* next() {
        if (index < order.size()) {
            int j = order[index++];
            switch (j) {
            case 0: return new httyd_question_1();
            case 1: return new httyd_question_2();
            case 2: return new httyd_question_3();
            case 3: return new httyd_question_4();
            default: return nullptr;
            }
        }
        return nullptr;
    }

};

#endif // HTTYD_QUESTIONS_H
