#include "game.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QString>

#include <time.h>

#include <room.h>
#include <player.h>
#include <item.h>
#include <gameview.h>

#include <unistd.h>
#include "map.h"

Game::Game(QApplication *qApplication) {
    this->qApplication = qApplication;
}

void Game::newGame() {
    run();
}

void Game::run() {
    const double NUM_SECONDS = 0.033;
    const int MAX_X = 800;
    const int MAX_Y = 600;
    const int MAP_SIZE = 150;

    // Create the scene
    QGraphicsScene * scene = new QGraphicsScene();
    scene->setSceneRect(0,0,MAX_X,MAX_Y);
    scene->setBackgroundBrush(QBrush(QImage(":/images/background.png")));

    // Create the item to put into the scene.
    Player * player = new Player(MAX_X, MAX_Y - MAP_SIZE);

    // Add the player to the scene
    scene->addItem(player);

    Map map(scene, player);

    // Add the view needed to visualise the scene.
    view = new GameView(scene, player);

    Room *room = map.getActiveRoom();

    //draw the room onscreen.
    room->draw();

    view->show();

    int count = 1;
    double time_counter;

    clock_t this_time = clock();
    clock_t last_time = this_time;

    //main game loop
    while(!this->isPaused() && !this->isFinished()) {
        this->qApplication->processEvents();

        this_time = clock();
        time_counter += (double) (this_time - last_time);
        last_time = this_time;

        if(room->isPlayerDead()) {
            this->setFinished(true);
            this->setGameOver(true);
        }

        if (time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC)) {
            time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);
            count++;
            room->refresh();
        }

        // If player has collided with a door, ie. Moving to a neighbour room
        if (room->getNextDirection() >= 0) {
            map.changeActiveRoom(static_cast<Direction>(room->getNextDirection()));

            room = map.getActiveRoom();

            map.printMap(scene);

            room->draw();
        }
    }

    if(isGameOver()) {
        sleep(2);
    }

    qApplication->exit();
    view->close();
}

bool Game::isPaused() const {
    return this->view->isPaused();
}

void Game::setFinished(bool finished) {
    this->finished = finished;
}

bool Game::isFinished() const {
    return this->finished;
}

void Game::setGameOver(bool gameOver) {
    this->gameOver = gameOver;
}

bool Game::isGameOver() const {
    return this->gameOver;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Game game(&a);
    //main game loop is in here, don't need QApplication.exec()
    game.newGame();

    //return a.exec();
    return 0;
}
