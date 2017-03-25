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

    this->neighbourNorth = roomNorth;
    this->neighbourEast = roomEast;
    this->neighbourSouth = roomSouth;
    this->neighbourWest = roomWest;

    this->createEntities();
}

Room::~Room() {
    QList<QGraphicsItem*> items = this->scene->items();

    // This is extremelly hacky, to prevent removing player. Need to fix!
    for (int i = 0; i < items.size(); i++) {
        if (!items[i]->hasFocus()) {
            qDebug() << items[i];
            this->scene->removeItem(items[i]);
        }
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
    if (this->neighbourNorth) {
        Door *doorPtr = new Door(NORTH);
        this->doors.push_back(doorPtr);
        this->items.push_back(doorPtr);
    }
    if (this->neighbourEast) {
        Door *doorPtr = new Door(EAST);
        this->doors.push_back(doorPtr);
        this->items.push_back(doorPtr);
    }
    if (this->neighbourSouth) {
        Door *doorPtr = new Door(SOUTH);
        this->doors.push_back(doorPtr);
        this->items.push_back(doorPtr);
    }
    if (this->neighbourWest) {
        Door *doorPtr = new Door(WEST);
        this->doors.push_back(doorPtr);
        this->items.push_back(doorPtr);
    }
}

void Room::handleCollisions() const {
    this->player->handleCollisions();
}

void Room::refresh() const {
    this->player->move();
    this->player->refreshSprite();
    handleCollisions();
}

void Room::draw() const {
    player->setPos(350, 600 - 400);
    player->draw();

    for(auto & item: this->items) {
        this->scene->addItem(item);
        item->draw();
    }
}

bool Room::getNeighbourNorth() const {
    return this->neighbourNorth;
}

bool Room::getNeighbourEast() const {
    return this->neighbourEast;
}

bool Room::getNeighbourSouth() const {
    return this->neighbourSouth;
}

bool Room::getNeighbourWest() const {
    return this->neighbourWest;
}

int Room::getNextDirection() const {
    for(auto & door: this->doors) {
        if (door->isExited()) return door->getDirection();
    }

    return -1;
}
