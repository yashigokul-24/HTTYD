// flappy_dragon.cpp
#include "flappy_dragon.h"
#include "scene.h"
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include <QMessageBox>
#include <QUrl>

Flappy_Dragon::Flappy_Dragon(QWidget *parent)
    : QWidget(parent)
    , music_player_(new QMediaPlayer(this))
    , audio_output(new QAudioOutput(this))
    , graphics_view_(new QGraphicsView(this))
    , game_scene_(new Scene(this))
{
    // 1) Set fixed window size and title
    setFixedSize(1280, 1080);
    setWindowTitle("Race to the edge of the World!");

    // 2) Attach audio output and play music
    music_player_->setAudioOutput(audio_output);
    audio_output->setVolume(1.0f);  // 100%
    music_player_->setSource(QUrl("qrc:/images/final_flight.mp3"));
    music_player_->play();

    // 3) Configure graphics view
    graphics_view_->setScene(game_scene_);
    graphics_view_->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    graphics_view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphics_view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphics_view_->setGeometry(0, 0, width(), height());

    // 4) Ensure keyboard focus
    graphics_view_->setFocusPolicy(Qt::StrongFocus);
    graphics_view_->setFocus();

    // 5) Start the game logic
    game_scene_->start_game();

    // 6) After 10 s (10000 ms), finish the mini‐game
    QTimer::singleShot(10000, this, &Flappy_Dragon::onGameComplete);
}

Flappy_Dragon::~Flappy_Dragon() = default;

void Flappy_Dragon::onGameComplete()
{
    // Show your end‐of‐race message
    QMessageBox::information(this,
                             "A Farewell from the Skies",
                             "Treasure this fleeting moment—be vigilant on your next journey!");

    // Stop the music
    music_player_->stop();

    // Emit the signal that the level is over
    emit end_httyd();
}
