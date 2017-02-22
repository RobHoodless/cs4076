#include "room.h"

#include <QGraphicsScene>
#include <QDebug>

#include <random>
#include <functional>

#include <player.h>
#include <item.h>
#include <time.h>

Room::Room(QGraphicsScene *scene, Player *player) {
    this->player = player;
    this->scene = scene;

    this->createEntities();
}

void Room::createEntities() {
    //make use of Mersenne Twister https://en.wikipedia.org/wiki/Mersenne_Twister
    mt19937::result_type seed = time(0);

    //Getting functional (partials) - bind the Mersenne Twister engine (w/ seed) to the uniform distribution -
    //can call rand_coord_func_partial without needing to pass the engine then.
    auto rand_coord_func_partial = std::bind(std::uniform_int_distribution<int>(0,751), mt19937(seed));

    //x coord will be under 750, enforce y coord under 550 to make sure the whole diamond is in view.
    for(int i = 0; i < 5; i++) {
        this->items.push_back(new Item(rand_coord_func_partial(), rand_coord_func_partial() % 550 ));
    }
    //NOTE:
    //Non functional version would be:
    //uniform_int_distribution<int> dist(0, 751);
    //mt19937 engine(seed);
    //this->items.push_back(new Item(dist(engine), dist(engine) % 550 ));

}

void Room::handleCollisions() {
    this->player->handleCollisions();
}

void Room::refresh() {
    this->player->move();
    this->player->refreshSprite();
    handleCollisions();
}

void Room::draw() {
    player->setPos(400, 500);
    player->draw();
    for(auto & item: this->items) {
        qDebug() << "Iteration" <<endl;

        this->scene->addItem(item);
        item->draw();
    }
}
