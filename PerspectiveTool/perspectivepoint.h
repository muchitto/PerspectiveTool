#ifndef PERSPECTIVEPOINT_H
#define PERSPECTIVEPOINT_H

#include <QPointF>
#include <QVector>
#include <QLineF>
#include <QColor>
#include <QRectF>
#include <QDebug>

class PerspectivePoint
{
public:
    PerspectivePoint();
    QPointF position;
    QVector<QLineF> lines;
    QColor line_color;

    int number_of_lines = 120;

    int center_removal = 20;

    int opacity = 50;

    void resetLines();
    void createLinesFromTwoPoints(QPointF first_point, QPointF second_point);

    bool inHelperArea (QPointF point);

    void addLine();
    void subtractLine();
};

#endif // PERSPECTIVEPOINT_H
