#include "room.h"

#include <QGraphicsScene>
#include <QDebug>

#include <random>
#include <functional>
#include <time.h>
#include <enemy.h>
#include <vector>

#include "player.h"
#include "item.h"
#include "door.h"

using namespace std;

Room::Room(QGraphicsScene *scene, Player *player, bool roomNorth, bool roomEast, bool roomSouth, bool roomWest)
    : scene(scene),
      player(player),
      neighbourNorth(roomNorth),
      neighbourEast(roomEast),
      neighbourWest(roomWest),
      neighbourSouth(roomSouth){

    this->createEntities();
}

Room::~Room() {
    QList<QGraphicsItem*> items = this->scene->items();

    // This is extremelly hacky, to prevent removing player. Need to fix!
    for (int i = 0; i < items.size(); i++) {
        if (!items[i]->hasFocus()) {
            this->scene->removeItem(items[i]);
        }
    }
}

void Room::createEntities() {
    //make use of Mersenne Twister https://en.wikipedia.org/wiki/Mersenne_Twister for
    //random coordinate generation.
    mt19937::result_type seed = time(0);

    //Bind the Mersenne Twister engine (w/ seed) to the uniform distribution -
    //can call rand_partial without needing to pass the engine then.
    auto rand_partial = std::bind(std::uniform_int_distribution<int>(0,751), mt19937(seed));

    //x coord will be under 750, enforce y coord under 375 to make sure the whole diamond is in view.
    for(int i = 0; i < 3; i++) {
        Item *itemPtr = new Item(rand_partial(), rand_partial() % 375);
        this->items.push_back(itemPtr);
    }

    for(int i = 0; i < 1; i++) {
        //Enforce enemy isn't in player spawn zone.
        int x = rand_partial();
        while(x > 300 && x < 400) {
            x = rand_partial();
        }

        int y = rand_partial() % 375;
        while(y > 200 && y < 300 ) {
            y = rand_partial() % 375;
        }

        this->enemies.push_back(new Enemy(x,
                                          rand_partial() % 375,
                                          rand_partial() % 2 ));
    }

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
    for(auto & enemy: enemies) {
        enemy->move();
        enemy->refreshSprite();
    }
    handleCollisions();
}

void Room::draw() const {
    player->setPos(350, 600 - 400);
    player->draw();
    for(auto & enemy: this->enemies) {
        this->scene->addItem(enemy);
        enemy->draw();
    }

    for(auto & item: this->items) {
        this->scene->addItem(item);
        item->draw();
    }
}

bool Room::isExited() {
    return exited;
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

bool Room::isPlayerDead() const {
    return player->isDead();
}

int Room::getNextDirection() const {
    for(auto & door: this->doors) {
        if (door->isExited()) return door->getDirection();
    }

    return -1;
}
