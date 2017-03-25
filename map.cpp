#include <QCoreApplication>
#include <QGraphicsScene>
#include <QDebug>
#include <QtDebug>
#include <QString>
#include <time.h>
#include <vector>

#include "map.h"

using namespace std;

static const int GRID_HEIGHT = 5;
static const int GRID_WIDTH = 5;

Map::Map(QGraphicsScene *scene) {
    this->createMap();
    this->printMap(scene);
}

void Map::createMap() {
    srand(time(NULL));

    for (int i = 0; i < GRID_HEIGHT; i++) {
        vector<bool> xRooms;
        for (int j = 0; j < GRID_WIDTH; j++) {
            xRooms.push_back(0);
        }
        rooms.push_back(xRooms);
    }

    vector<int> roomPositions(GRID_HEIGHT, -1);

    /* Populate initial room for each floor */
    for (int i = 0; i < GRID_HEIGHT; i++) {
        int baseRoomPosition = rand() % GRID_WIDTH;

        rooms[i][baseRoomPosition] = true;
        roomPositions[i] = baseRoomPosition;
        activeY = GRID_HEIGHT - 1;
        activeX = roomPositions[GRID_WIDTH - 1];
    }

    /* Connect base rooms */
    for (int row = 0; row < GRID_HEIGHT - 1; row++) {
        rooms[row + 1][roomPositions[row]] = true;

        if (roomPositions[row] < roomPositions[row + 1]) {
            for (int j = roomPositions[row]; j < roomPositions[row + 1]; j++) {
                rooms[row + 1][j] = true;
            }
        } else if (roomPositions[row] > roomPositions[row + 1]) {
            for (int j = roomPositions[row]; j > roomPositions[row + 1]; j--) {
                rooms[row + 1][j] = true;
            }
        }
    }
}

// This doesn't update when moving to a new room, need to fix
void Map::printMap(QGraphicsScene *scene) const {
    const int ROOM_SIZE = 20;

    int x = 650;
    int y = 475;

    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (rooms[i][j]) {
                if (i == this->activeY && j == this->activeX) {
                    scene->addRect(x, y, ROOM_SIZE, ROOM_SIZE, QPen(QColor(255, 0, 0)));
                } else {
                    scene->addRect(x, y, ROOM_SIZE, ROOM_SIZE, QPen(QColor(255, 255, 255)));
                }
            }
            x += 20;
        }
        x = 650;
        y += 20;
    }
}

int Map::getActiveX() const {
    return this->activeX;
}

int Map::getActiveY() const {
    return this->activeY;
}

void Map::getNeighbourRooms(bool* nesw) const {
    if ((activeY - 1) >= 0 && rooms[activeY-1][activeX]) { // North
        nesw[0] = true;
    }
    if ((activeX + 1) < GRID_WIDTH && rooms[activeY][activeX+1]) { // East
        nesw[1] = true;
    }
    if ((activeY + 1) < GRID_HEIGHT && rooms[activeY+1][activeX]) { // South
        nesw[2] = true;
    }
    if ((activeX - 1) >= 0 && rooms[activeY][activeX-1]) { // West
        nesw[3] = true;
    }
}

void Map::changeActiveRoom(Direction direction) {
    if (direction == NORTH) this->goNorth();
    else if (direction == EAST) this->goEast();
    else if (direction == SOUTH) this->goSouth();
    else if (direction == WEST) this->goWest();
}

inline void Map::goNorth() {
    this->activeY -= 1;
}

inline void Map::goEast() {
    this->activeX += 1;
}

inline void Map::goSouth() {
    this->activeY += 1;
}

inline void Map::goWest() {
    this->activeX -= 1;
}
