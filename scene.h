#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>

class dragon_item;

/**
 * @brief Custom QGraphicsScene that manages the game elements.
 */
class Scene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit Scene(QObject *parent = nullptr);
    void start_game();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void spawn_rock();
    void game_over();

private:
    dragon_item *dragon_item_;  ///< The player-controlled dragon
    QTimer      *rock_timer_;   ///< Timer to schedule rock spawning
    QTimer      *game_timer_;   ///< Timer for overall game duration
};

#endif // SCENE_H
