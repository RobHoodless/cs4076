#include "sprite.h"
#include "QDebug"

Sprite::Sprite() {
    //Empty implementation.
}

Sprite::Sprite(QPixmap qPixmap)
    : qPixmap(qPixmap) { }

bool Sprite::operator==(const Sprite & rhs) const {
    return (this->getPixmap().toImage() == rhs.getPixmap().toImage());
}

QPixmap Sprite::getPixmap() const {
    return this->qPixmap;
}

void Sprite::setPixmap(QPixmap qPixmap) {
    this->qPixmap = qPixmap;
}
