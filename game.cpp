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

    // Create the scene
    QGraphicsScene * scene = new QGraphicsScene();
    scene->setSceneRect(0,0,MAX_X,MAX_Y);

    // Create the item to put into the scene.
    Player * player = new Player(MAX_X, MAX_Y);
    player->setPos(MAX_X / 2, MAX_Y / 2);

    //Item *item = new Item();


    // Add the item to the scene

    scene->addItem(player);
    scene->setBackgroundBrush(QBrush(QImage(":/images/background.png")));


    // Add the view needed to visualise the scene.
    view = new GameView(scene, player);

    //make player focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //Create room object.
    Room *room = new Room(scene, player);
    //draw the room onscreen.
    room->draw();

    view->show();

    int count = 1;
    double time_counter;

    clock_t this_time = clock();
    clock_t last_time = this_time;

    //qDebug() << QString("gran = ") << NUM_SECONDS * CLOCKS_PER_SEC << endl;

    //player->setPos(400, 500);
    //item->draw();
    //player->draw();

    //main game loop
    while(!this->isPaused()) {

        this->qApplication->processEvents();

        this_time = clock();

        time_counter += (double) (this_time - last_time);

        last_time = this_time;

        if(time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC)) {
            time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);
            //
            //qDebug() << "Frame count: " << count << endl;
            count++;
            room->refresh();
            //player->move();
            //player->refreshSprite();


        }

    }
    qApplication->exit();
    view->close();

}

bool Game::isPaused() {
    return this->view->isPaused();
}

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    Game game(&a);
    game.newGame();

    //return a.exec();
    return 0;
}
