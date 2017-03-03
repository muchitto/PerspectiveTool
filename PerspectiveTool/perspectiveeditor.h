#ifndef PERSPECTIVEEDITOR_H
#define PERSPECTIVEEDITOR_H

#include <QDebug>
#include <QVector>
#include <QPoint>
#include <QWidget>
#include <QLineF>
#include <QRectF>
#include <QPainter>
#include <QWheelEvent>
#include <QtMath>
#include <QApplication>
#include <QImage>

#include "perspectivepoint.h"

class PerspectiveEditor : public QWidget
{
    Q_OBJECT
public:
    explicit PerspectiveEditor(QWidget *parent = 0);

    bool camera_drag_mode = false;

    int perspective_point_count = 1;
    int perspective_point_move = -1;

    float zoom_level = 1;
    float zoom_level_change = 0.5;

    QVector<PerspectivePoint> perspective_points;

    QPointF camera_position = QPointF(100, 100);

    QRectF canvas = QRectF(0, 0, 640, 400);

    QLineF camera_drag_line;

    QImage canvas_image;


public slots:
    void perspectivePointsSelected (int perspective);

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent * event) override;
};

#endif // PERSPECTIVEEDITOR_H
