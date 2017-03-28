#ifndef MYPIXMAP_H
#define MYPIXMAP_H

#include <QPixmap>

class Sprite {
public:
    Sprite();
    Sprite(QPixmap qPixmap);
    bool operator==(Sprite & rhs) const;
    QPixmap getPixmap() const;
    void setPixmap(QPixmap qPixmap);

private:
    QPixmap qPixmap;
};

#endif // MYPIXMAP_H
