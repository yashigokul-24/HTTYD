QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dragon_item.cpp \
    httyd_intro.cpp \
    httyd_mainwindow.cpp \
    httyd_question_1.cpp \
    httyd_question_2.cpp \
    httyd_question_3.cpp \
    httyd_question_4.cpp \
    httyd_questions.cpp \
    main.cpp \
    flappy_dragon.cpp \
    rock_item.cpp \
    scene.cpp

HEADERS += \
    dragon_item.h \
    flappy_dragon.h \
    httyd_intro.h \
    httyd_mainwindow.h \
    httyd_question_1.h \
    httyd_question_2.h \
    httyd_question_3.h \
    httyd_question_4.h \
    httyd_questions.h \
    rock_item.h \
    scene.h

FORMS += \
    flappy_dragon.ui \
    httyd_question_1.ui \
    httyd_question_2.ui \
    httyd_question_3.ui \
    httyd_question_4.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
