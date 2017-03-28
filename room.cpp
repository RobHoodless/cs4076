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

    this->createEntities();
}

void Room::tearDown() {
    QList<QGraphicsItem*> sceneItems = this->scene->items();

    //This is extremelly hacky, to prevent removing player. Need to fix!
    qDebug() << "Removing items";
    for (int i = 0; i < sceneItems.size(); i++) {
        if (!sceneItems[i]->hasFocus()) {
            qDebug() << sceneItems[i];
            this->scene->removeItem(sceneItems[i]);
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

    qDebug() << "Adding items:";
    for(auto & item: this->items) {
        qDebug() << item;
        this->scene->addItem(item);
        item->draw();
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
