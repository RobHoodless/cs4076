#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsPixmapItem>
#include <QImage>

//#include "player.h"

class Entity: public QGraphicsPixmapItem
{
public:
    Entity();
    virtual void draw() = 0;
    //virtual void handleCollision(Player *player) = 0;

protected:
    QImage *spriteSheet;
};

#endif // ENTITY_H
