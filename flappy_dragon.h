#ifndef FLAPPY_DRAGON_H
#define FLAPPY_DRAGON_H
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QWidget>

class QGraphicsView;
class Scene;

/**
 * @brief Main application window that hosts the QGraphicsView and Scene.
 */
class Flappy_Dragon : public QWidget {
    Q_OBJECT

public:
    explicit Flappy_Dragon(QWidget *parent = nullptr);
    ~Flappy_Dragon();

signals:
    void end_httyd();          // ← EMITTED when the race timer runs out

private slots:
    void onGameComplete();     // ← shows final dialog + emits end_httyd


private:
    QGraphicsView *graphics_view_;  ///< View for rendering the game scene
    Scene         *game_scene_;     ///< The game scene (QGraphicsScene subclass)
    QMediaPlayer*   music_player_;
    QAudioOutput*   audio_output;
};

#endif // FLAPPY_DRAGON_H
