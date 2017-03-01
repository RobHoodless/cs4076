#include "room.h"

#include <QGraphicsScene>
#include <QDebug>

#include <random>
#include <functional>
#include <time.h>
#include <vector>

#include "player.h"
#include "item.h"
#include "door.h"

using namespace std;

Room::Room(QGraphicsScene *scene, Player *player, bool roomNorth, bool roomEast, bool roomSouth, bool roomWest) {
    this->player = player;
    this->scene = scene;

    this->roomNorth = roomNorth;
    this->roomEast = roomEast;
    this->roomSouth = roomSouth;
    this->roomWest = roomWest;

    this->createEntities();
    this->createDoors();
}

void Room::createEntities() {
    //make use of Mersenne Twister https://en.wikipedia.org/wiki/Mersenne_Twister
    mt19937::result_type seed = time(0);

    //Getting functional (partials) - bind the Mersenne Twister engine (w/ seed) to the uniform distribution -
    //can call rand_coord_func_partial without needing to pass the engine then.
    auto rand_coord_func_partial = std::bind(std::uniform_int_distribution<int>(0,751), mt19937(seed));

    //x coord will be under 750, enforce y coord under 550 to make sure the whole diamond is in view.
    for(int i = 0; i < 5; i++) {
        this->items.push_back(new Item(rand_coord_func_partial(), rand_coord_func_partial() % 400 ));
    }
    //NOTE:
    //Non functional version would be:
    //uniform_int_distribution<int> dist(0, 751);
    //mt19937 engine(seed);
    //this->items.push_back(new Item(dist(engine), dist(engine) % 550 ));

    createDoors();
}

void Room::createDoors() {
    if (this->roomNorth) this->items.push_back(new Door(0));
    if (this->roomEast) this->items.push_back(new Door(1));
    if (this->roomSouth) this->items.push_back(new Door(2));
    if (this->roomWest) this->items.push_back(new Door(3));
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
    player->setPos(350, 600 - 250);
    player->draw();
    for(auto & item: this->items) {
        this->scene->addItem(item);
        item->draw();
    }
}

bool Room::getRoomNorth() {
    return roomNorth;
}

bool Room::getRoomEast() {
    return roomEast;
}

bool Room::getRoomSouth() {
    return roomSouth;
}

bool Room::getRoomWest() {
    return roomWest;
}
