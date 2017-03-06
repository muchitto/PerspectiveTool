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
    bool camera_dragging = false;

    int perspective_point_count = 1;
    int perspective_point_move = -1;
    int perspective_point_activated = -1;

    float zoom_level = 1;
    float zoom_level_change = 0.25;

    QVector<PerspectivePoint> perspective_points;

    QPointF camera_position = QPointF(100, 100);

    QRectF canvas = QRectF(0, 0, 1280, 800);

    QLineF camera_drag_line;

    QImage canvas_image;

    QPointF mouse, mouse_view;

    bool antialiasing = false;

    void selectPerspectivePoint(int p);

    QPointF convertToViewerCoords(QPointF point);
    QPointF convertToRealCoords(QPointF point);
    QPointF convertToRealCoords(QPointF point, QPointF offset);
    QPointF convertToViewerCoords(QPointF point, QPointF offset);
    QImage renderImage(int width, int height);

    QImage scaled_image;

    void startCameraDrag();
    void endCameraDrag();
    void updateCameraDrag();
    QPointF zoomify(QPointF point);
    QPointF dezoomify(QPointF point);
    int dezoomify(int value);
    int zoomify(int value);
    void startCameraDragMode();
    void endCameraDragMode();
    QPointF getCurrentOffset();
    void raiseZoomLevel();
    void decreaseZoomLevel();
    void reRenderCanvasImage();
public slots:
    void perspectivePointsSelected (int perspective);
    void setAntialiasing(bool antialiasing);
    void setCurrentOpacity(int opacity);
    void setCurrentLines(int lines);
    void setCurrentCenterRemoval(int center_removal);

signals:
    void setOpacity(int opacity);
    void setLines (int lines);
    void setCenterRemoval (int center_removal);

    void perspectivePointActivationState(bool state);

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
