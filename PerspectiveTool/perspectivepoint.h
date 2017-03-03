#ifndef PERSPECTIVEPOINT_H
#define PERSPECTIVEPOINT_H

#include <QPointF>
#include <QVector>
#include <QLineF>
#include <QColor>

class PerspectivePoint
{
public:
    PerspectivePoint();
    QPointF position;
    QVector<QLineF> lines;
    QColor line_color;

    int number_of_lines = 20;

    void resetLines();
    void createLinesFromTwoPoints(QPointF first_point, QPointF second_point);

};

#endif // PERSPECTIVEPOINT_H
