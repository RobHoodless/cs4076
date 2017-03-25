#ifndef MOBILEENTITY_H
#define MOBILEENTITY_H

#include <QPixmap>
#include <entity.h>

class MobileEntity : public Entity {
public:
    MobileEntity();
    virtual void move() = 0;
    virtual void refreshSprite() = 0;

protected:
    QPixmap nextSprite;
    QPixmap standing;
    QPixmap walkingTransition;
    QPixmap walkingFull;

};

#endif // MOBILEENTITY_H
