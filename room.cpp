#include "room.h"

#include <QGraphicsScene>
#include <QDebug>

#include <random>
#include <functional>
#include <time.h>
#include <vector>
#include <algorithm>

#include "player.h"
#include "item.h"
#include "door.h"

using namespace std;

Room::Room(QGraphicsScene *scene, Player *player, bool roomNorth, bool roomEast, bool roomSouth, bool roomWest) {
    qDebug() << "Creating room";
    this->player = player;
    this->scene = scene;

    this->roomNorth = roomNorth;
    this->roomEast = roomEast;
    this->roomSouth = roomSouth;
    this->roomWest = roomWest;

    this->createEntities();
}

Room::~Room() {
    qDebug() << "Deleting room";

    for (auto &item: this->items) {
        // This doesn't work if item is already deleted
//        this->scene->removeItem(item);
    }
}

void Room::createEntities() {
    //make use of Mersenne Twister https://en.wikipedia.org/wiki/Mersenne_Twister
    mt19937::result_type seed = time(0);

    //Getting functional (partials) - bind the Mersenne Twister engine (w/ seed) to the uniform distribution -
    //can call rand_coord_func_partial without needing to pass the engine then.
    auto rand_coord_func_partial = std::bind(std::uniform_int_distribution<int>(0,751), mt19937(seed));

    //x coord will be under 750, enforce y coord under 550 to make sure the whole diamond is in view.
    for(int i = 0; i < 5; i++) {
        Item *itemPtr = new Item(rand_coord_func_partial(), rand_coord_func_partial() % 400);
        this->items.push_back(itemPtr);
    }
    //NOTE:
    //Non functional version would be:
    //uniform_int_distribution<int> dist(0, 751);
    //mt19937 engine(seed);
    //this->items.push_back(new Item(dist(engine), dist(engine) % 550 ));

    createDoors();
}

void Room::createDoors() {
    if (this->roomNorth) {
        qDebug() << "Neighbour north";
        Door * doorPtr = new Door(NORTH);
        this->doors.push_back(doorPtr);
        this->items.push_back(doorPtr);
    }
    if (this->roomEast) {
        qDebug() << "Neighbour east";
        Door * doorPtr = new Door(EAST);
        this->doors.push_back(doorPtr);
        this->items.push_back(doorPtr);
    }
    if (this->roomSouth) {
        qDebug() << "Neighbour south";
        Door * doorPtr = new Door(SOUTH);
        this->doors.push_back(doorPtr);
        this->items.push_back(doorPtr);
    }
    if (this->roomWest) {
        qDebug() << "Neighbour west";
        Door * doorPtr = new Door(WEST);
        this->doors.push_back(doorPtr);
        this->items.push_back(doorPtr);
    }
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
    player->setPos(350, 600 - 400);
    player->draw();

    for(auto & item: this->items) {
        this->scene->addItem(item);
        item->draw();
    }
}

bool Room::getRoomNorth() {
    return this->roomNorth;
}

bool Room::getRoomEast() {
    return this->roomEast;
}

bool Room::getRoomSouth() {
    return this->roomSouth;
}

bool Room::getRoomWest() {
    return this->roomWest;
}

int Room::getNextDirection() {
    for(auto & door: this->doors) {
        if (door->isExited()) return door->getDirection();
    }

    return -1;
}
