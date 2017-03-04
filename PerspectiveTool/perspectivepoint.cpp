#include "perspectivepoint.h"

PerspectivePoint::PerspectivePoint() {

}

bool PerspectivePoint::inHelperArea(QPointF point) {

    QRectF box(position.x() - 10,  position.y() - 10,  20,  20);

    return box.contains(point);
}

void PerspectivePoint::addLine() {
    number_of_lines += 4;

    if(number_of_lines > 500)
        number_of_lines = 500;
}

void PerspectivePoint::subtractLine() {

    number_of_lines -= 4;

    if(number_of_lines < 0)
        number_of_lines = 0;

}
