#include "mypixmap.h"

MyPixmap::MyPixmap() {

}

bool MyPixmap::operator==(MyPixmap & rhs) const {
    return (&(*(this)) == &rhs);
}
