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

#include "room.h"

using namespace std;

Room::Room(QGraphicsScene *scene, Player *player) {
    this->player = player;
    this->scene = scene;
}

void Room::setup(bool n, bool e, bool s, bool w) {
    this->neighbourNorth = n;
    this->neighbourEast = e;
    this->neighbourSouth = s;
    this->neighbourWest = w;
}

void Room::tearDown() {
    QList<QGraphicsItem*> sceneItems = this->scene->items();

    for (auto &enemy: this->enemies) {
        if (sceneItems.contains(enemy)) {
            scene->removeItem(enemy);
        }
    }

    for (auto &item: this->items) {
        if (sceneItems.contains(item)) {
            scene->removeItem(item);
        }

        if (item->isDeleted()) {
            this->numItems--;
        }
    }

    for (auto &door: this->doors) {
        if (sceneItems.contains(door)) {
            this->scene->removeItem(door);
        }
    }

    this->items.clear();
    this->doors.clear();
    this->enemies.clear();
}

void Room::createEntities() {
    //make use of Mersenne Twister https://en.wikipedia.org/wiki/Mersenne_Twister for
    //random coordinate generation.
    mt19937::result_type seed = time(0);

    //Bind the Mersenne Twister engine (w/ seed) to the uniform distribution -
    //can call rand_partial without needing to pass the engine then.
    auto rand_partial = std::bind(std::uniform_int_distribution<int>(0,751), mt19937(seed));

    //x coord will be under 750, enforce y coord under 375 to make sure the whole diamond is in view.
    for(int i = 0; i < this->numItems; i++) {
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
                                          y,
                                          800,
                                          450, //total size - map size.
                                          rand_partial() % 2 ));
    }

    createDoors();
}

void Room::createDoors() {
    if (this->neighbourNorth) this->doors.push_back(new Door(NORTH));
    if (this->neighbourEast) this->doors.push_back(new Door(EAST));
    if (this->neighbourSouth) this->doors.push_back(new Door(SOUTH));
    if (this->neighbourWest) this->doors.push_back(new Door(WEST));
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
    for(MobileEntity * enemy: this->enemies) {
        this->scene->addItem(enemy);
        enemy->draw();
    }

    for(StationaryEntity * item: this->items) {
        this->scene->addItem(item);
        item->draw();
    }

    for (auto & door: this->doors) {
        this->scene->addItem(door);
        door->draw();
    }
}

bool Room::isExited() {
    return exited;
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
