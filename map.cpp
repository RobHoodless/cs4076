#include <QCoreApplication>
#include <QGraphicsScene>
#include <QString>
#include <time.h>
#include <vector>

#include "room.h"
#include "direction.h"
#include "map.h"

using namespace std;

static const int MAP_SIZE = 5;
static const int CELL_MAP_X = 650;
static const int CELL_MAP_Y = 475;
static const int CELL_SIZE = 20;
static const int CELL_PADDING = 2;

Map::Map(QGraphicsScene *scene, Player *player) {
    this->createMap(scene, player);
    this->printMap(scene);
}

Map::~Map()
{
    //Call the destructor for all elements in vector.
    for(vector<Room*> roomVector: rooms) {
        for(Room* room: roomVector) {
            delete room;
        }
    }
}

void Map::createMap(QGraphicsScene *scene, Player *player) {
    srand(time(NULL));

    int roomPositions[MAP_SIZE];

    // Initialize rooms to vector of nullptrs
    for (int i = 0; i < MAP_SIZE; i++) {
        vector<Room*> innerRooms;
        for (int j = 0; j < MAP_SIZE; j++) {
            innerRooms.push_back(nullptr);
        }
        this->rooms.push_back(innerRooms);
    }

    // Add rooms to map
    for (int i = 0; i < MAP_SIZE; i++) {
        int initialRoomPosition = rand() % MAP_SIZE;

        this->rooms[i][initialRoomPosition] = new Room(scene, player);
        this->numRooms++;
        roomPositions[i] = initialRoomPosition;
    }

    this->activeY = MAP_SIZE - 1;
    this->activeX = roomPositions[MAP_SIZE - 1];

    /* Connect base rooms */
    for (int row = 0; row < MAP_SIZE - 1; row++) {
        if (!this->rooms[row + 1][roomPositions[row]]) {
            this->rooms[row + 1][roomPositions[row]] = new Room(scene, player);
            this->numRooms++;
        }

        if (roomPositions[row] < roomPositions[row + 1]) {
            for (int j = roomPositions[row]; j < roomPositions[row + 1]; j++) {
                if (!this->rooms[row + 1][j]) {
                    this->rooms[row + 1][j] = new Room(scene, player);
                    this->numRooms++;
                }
            }
        } else if (roomPositions[row] > roomPositions[row + 1]) {
            for (int j = roomPositions[row]; j > roomPositions[row + 1]; j--) {
                if (!this->rooms[row + 1][j]) {
                    this->rooms[row + 1][j] = new Room(scene, player);
                    this->numRooms++;
                }
            }
        }
    }

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (rooms[i][j]) {
                bool neighbours[4] = {false, false, false, false};
                fillNeighbours(neighbours, j, i);

                this->rooms[i][j]->setup(neighbours[0], neighbours[1], neighbours[2], neighbours[3]);
            }
        }
    }

    this->activeRoom = this->rooms[this->activeY][this->activeX];
    this->activeRoom->createEntities();
}

void Map::printMap(QGraphicsScene *scene) {
    int x = CELL_MAP_X;
    int y = CELL_MAP_Y;

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (this->rooms[i][j]) {
                QGraphicsRectItem* currentCellPtr = scene->addRect(x, y, CELL_SIZE, CELL_SIZE, QPen(QColor(255, 255, 255)));

                if (i == this->activeY && j == this->activeX) {
                    this->activeCellPtr = currentCellPtr;
                    this->activeCellPtr->setBrush(* new QBrush(Qt::red));
                }
            }
            x += CELL_SIZE + CELL_PADDING;
        }
        x = CELL_MAP_X;
        y += CELL_SIZE + CELL_PADDING;
    }
}

void Map::fillNeighbours(bool* nesw, int x, int y) const {
    if ((y - 1) >= 0 && rooms[y - 1][x]) nesw[0] = true; // North
    if ((x + 1) < MAP_SIZE && rooms[y][x + 1]) nesw[1] = true; // East
    if ((y + 1) < MAP_SIZE && rooms[y + 1][x]) nesw[2] = true; // South
    if ((x - 1) >= 0 && rooms[y][x - 1]) nesw[3] = true; // West
}

Room* Map::changeActiveRoom(Direction direction, QGraphicsScene *scene) {
    this->activeRoom->tearDown();

    this->removePreviousActiveCell();

    if (direction == NORTH) this->goNorth();
    else if (direction == EAST) this->goEast();
    else if (direction == SOUTH) this->goSouth();
    else if (direction == WEST) this->goWest();

    this->activeRoom = this->rooms[this->activeY][this->activeX];
    this->activeRoom->createEntities();

    this->updateActiveCell(scene);

    return this->getActiveRoom();
}

void Map::removePreviousActiveCell() {
    if (this->activeRoom->getNumItems() <= 0) {
        this->activeCellPtr->setBrush(* new QBrush(Qt::blue));
    } else {
        this->activeCellPtr->setBrush(* new QBrush(Qt::white));
    }
}

void Map::updateActiveCell(QGraphicsScene *scene) {
    int roomX = CELL_MAP_X;
    int roomY = CELL_MAP_Y;

    for (int i = 0; i < this->activeX; i++) roomX += CELL_SIZE + CELL_PADDING;
    for (int j = 0; j < this->activeY; j++) roomY += CELL_SIZE + CELL_PADDING;

    this->activeCellPtr = (QGraphicsRectItem*) scene->itemAt(roomX, roomY, QTransform());
    this->activeCellPtr->setBrush(* new QBrush(Qt::red));
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

Room* Map::getActiveRoom() const {
    return this->activeRoom;
}

int Map::getNumItems() const {
    return this->numRooms * 5;
}
