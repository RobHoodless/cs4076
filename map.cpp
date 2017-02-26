#include <QCoreApplication>
#include <QDebug>
#include <QtDebug>
#include <time.h>
#include <vector>

#include "map.h"

using namespace std;

static const int GRID_HEIGHT = 5;
static const int GRID_WIDTH = 5;

Map::Map() {
    srand(time(NULL));

    for (int i = 0; i < GRID_HEIGHT; i++) {
        vector<bool> xRooms;
        rooms.push_back(xRooms);
        for (int j = 0; j < GRID_WIDTH; j++) {
            xRooms.push_back(false);
        }
    }

    vector<int> roomPositions(GRID_HEIGHT, -1);

    /* Populate base room for each floor */
    for (int i = 0; i < GRID_HEIGHT; i++) {
        int baseRoomPosition = rand() % GRID_WIDTH;

        rooms[i][baseRoomPosition] = true;
        roomPositions[i] = baseRoomPosition;
        activeY = GRID_HEIGHT - 1;
        activeX = roomPositions[GRID_HEIGHT - 1];
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

void Map::printMap() {
    qDebug() << "Width: " << GRID_WIDTH << " | Height: " << GRID_HEIGHT << "\n";
    qDebug() << "O = Room | # = Not a room" << "\n";
    for (int i = 0; i < GRID_HEIGHT; i++) {
        QString row = "";
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (rooms[i][j] == true) {
                row.append("O");
            } else {
                row.append("#");
            }
        }
        qDebug() << row;
    }
    qDebug() << endl;
}

int Map::getActiveX() {
    return activeX;
}

int Map::getActiveY() {
    return activeY;
}

// TODO The logic in this is broken
void Map::getNeighbourRooms(bool* nesw) {
    if ((activeY - 1) >= 0 && rooms[activeY-1][activeX]) { // North
        nesw[0] = true;
    }
    if ((activeY + 1) < GRID_WIDTH && rooms[activeX][activeY+1]) { // East
        nesw[1] = true;
    }
    if ((activeX + 1) < GRID_HEIGHT && rooms[activeX+1][activeY]) { // South
        nesw[2] = true;
    }
    if ((activeY - 1) >= 0 && rooms[activeX][activeY-1]) { // West
        nesw[3] = true;
    }
}
