#include "game.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QString>

#include <time.h>

#include <room.h>
#include <player.h>
#include <item.h>
#include <gameview.h>

#include <unistd.h>

#include "room.h"
#include "player.h"
#include "item.h"
#include "gameview.h"
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

    // Create the item to put into the scene.
    Player * player = new Player(MAX_X, MAX_Y - MAP_SIZE);

    // Add the player to the scene
    scene->addItem(player);
    scene->setBackgroundBrush(QBrush(QImage(":/images/background.png")));

    Map map(scene);

    // Add the view needed to visualise the scene.
    view = new GameView(scene, player);

    bool neighbourRooms[] = {false, false, false, false};
    map.getNeighbourRooms(neighbourRooms);
    Room *room = new Room(scene, player, neighbourRooms[0],neighbourRooms[1],neighbourRooms[2],neighbourRooms[3]);

    //draw the room onscreen.
    room->draw();

    view->show();

    int count = 1;
    double time_counter;

    clock_t this_time = clock();
    clock_t last_time = this_time;

    //main game loop
    while(!this->isPaused()) {
        this->qApplication->processEvents();

        this_time = clock();
        time_counter += (double) (this_time - last_time);
        last_time = this_time;

        if (time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC)) {
            time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);
            count++;
            room->refresh();
        }

        // If player has collided with a door, ie. Moving to a neighbour room
        if (room->getNextDirection() >= 0) {
            map.changeActiveRoom(static_cast<Direction>(room->getNextDirection()));

            bool neighbourRooms[] = {false, false, false, false};
            map.getNeighbourRooms(neighbourRooms);

            delete room;
            room = new Room(scene, player, neighbourRooms[0],neighbourRooms[1],neighbourRooms[2],neighbourRooms[3]);

            map.printMap(scene);

            room->draw();
        }
    }
    qApplication->exit();
    view->close();
}

bool Game::isPaused() const {
    return this->view->isPaused();
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Game game(&a);
    //main game loop is in here, don't need QApplication.exec()
    game.newGame();

    //return a.exec();
    return 0;
}
