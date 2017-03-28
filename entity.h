#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsPixmapItem>
#include <QImage>

class Entity: public QGraphicsPixmapItem {
public:
    Entity();
    virtual void draw() = 0;

protected:
    QImage *spriteSheet;
};

#endif // ENTITY_H
