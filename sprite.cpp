#include "sprite.h"
#include "QDebug"

Sprite::Sprite() {
    //Empty implementation.
}

Sprite::Sprite(QPixmap qPixmap) {
    this->qPixmap = qPixmap;
}

bool Sprite::operator==(Sprite & rhs) const {
    //Just want to check if they are the same object, so comparing addresses works perfectly.
    return (this->getPixmap().toImage() == rhs.getPixmap().toImage());
    //return (&(*(this)) == &rhs);
}

QPixmap Sprite::getPixmap() const {
    return this->qPixmap;
}

void Sprite::setPixmap(QPixmap qPixmap) {
    this->qPixmap = qPixmap;
}
