#ifndef MYPIXMAP_H
#define MYPIXMAP_H

#include <QPixmap>

class MyPixmap : public QPixmap {
public:
    MyPixmap();
    bool operator==(MyPixmap & rhs) const;
};

#endif // MYPIXMAP_H
