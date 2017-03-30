#include "game.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QString>
#include <QtWidgets>

#include <time.h>
#include <unistd.h>

#include "gameview.h"
#include "item.h"
#include "map.h"
#include "player.h"
#include "room.h"

Game::Game(QApplication  * const qApplication) {
    this->qApplication = qApplication;
}

Game::~Game() {}

void Game::newGame() {

    run();
}

void Game::run() {
    const double NUM_SECONDS = 0.033;
    const int MAX_X = 800;
    const int MAX_Y = 600;
    const int MAP_SIZE = 150;

    // Create the scene
    QGraphicsScene *scenePtr = new QGraphicsScene();
    scenePtr->setSceneRect(0,0,MAX_X,MAX_Y);
    scenePtr->setBackgroundBrush(QBrush(QImage(":/images/background.png")));

    // Create the item to put into the scene.
    Player *playerPtr = new Player(MAX_X, MAX_Y - MAP_SIZE);

    // Add the player to the scene
    scenePtr->addItem(playerPtr);

    Map map(scenePtr, playerPtr);

    Room *roomPtr = map.getActiveRoom();

    // Add the view needed to visualise the scene.
    view = new GameView(scenePtr, playerPtr, roomPtr);

    //draw the room onscreen.
    roomPtr->draw();

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

        if (roomPtr->isPlayerDead()) {
            this->setFinished(true);
            this->setGameOver(true);
        }

        if (time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC)) {
            time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);
            count++;
            roomPtr->refresh();
        }

        if (playerPtr->getScore() >= map.getNumItems()) {
            this->setFinished(true);
            this->setGameOver(true);
        }

        // If player has collided with a door, ie. Moving to a neighbour room
        if (roomPtr->getNextDirection() >= 0) {
            roomPtr = map.changeActiveRoom(static_cast<Direction>(roomPtr->getNextDirection()), scenePtr);
            roomPtr->draw();
        }
    }

    //Delete objects in last room, won't be deleted by above logic as we are not leaving the room.
    map.getActiveRoom()->tearDown();

    if (isGameOver()) {
        sleep(2);
    }

    qApplication->exit();
    view->close();
    delete scenePtr;
}

bool Game::isPaused() const {
    return this->view->isPaused();
}

void Game::setFinished( const bool finished) {
    this->finished = finished;
}

bool Game::isFinished() const {
    return this->finished;
}

void Game::setGameOver(const bool gameOver) {
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
