#include "perspectiveeditor.h"

PerspectiveEditor::PerspectiveEditor(QWidget *parent) : QWidget(parent) {

    setFocusPolicy(Qt::StrongFocus);

    perspective_points.resize(5);

    perspective_points[0].line_color = QColor(200, 50, 50);
    perspective_points[1].line_color = QColor(50, 200, 50);
    perspective_points[2].line_color = QColor(50, 50, 200);

    repaint();

    canvas_image = QImage((int) canvas.width(), (int) canvas.height(), QImage::Format_RGB32);
}


void PerspectiveEditor::perspectivePointsSelected (int perspective) {
    if(perspective == -2) {
        perspective_point_count = 1;
    } else if(perspective == -3) {
        perspective_point_count = 2;
    } else if(perspective == -4) {
        perspective_point_count = 3;
    }

    repaint();
}

void PerspectiveEditor::wheelEvent (QWheelEvent *event) {
    if(event->delta() < 0) {
        zoom_level += zoom_level_change;
    } else {
        zoom_level -= zoom_level_change;
    }

    repaint();
}

void PerspectiveEditor::mouseMoveEvent(QMouseEvent *event) {
    if(perspective_point_move != -1) {
        perspective_points[perspective_point_move].position = QPointF(event->x(), event->y()) - camera_position;
        repaint();
    } else if(camera_drag_mode) {
        camera_drag_line.setP2(QPointF(event->x(), event->y()));
    }
}

void PerspectiveEditor::mouseReleaseEvent(QMouseEvent *event) {
    perspective_point_move = -1;
}

void PerspectiveEditor::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Space) {
        camera_drag_mode = true;

        setCursor(Qt::OpenHandCursor);
    }
}

void PerspectiveEditor::keyReleaseEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Space) {
        camera_drag_mode = false;
        setCursor(Qt::ArrowCursor);
    }
}

void PerspectiveEditor::mousePressEvent(QMouseEvent *event) {
    if(camera_drag_mode) {
        camera_drag_line = QLineF(QPointF(event->x(), event->y()), QPointF(event->x(), event->y()));
        return;
    }

    for(int p = 0; p < perspective_point_count; p++) {
        QPointF point = camera_position + perspective_points[p].position;

        QRectF box(point.x() - 10,  point.y() - 10,  20,  20);

        if(box.contains(event->x(), event->y())) {
            perspective_point_move = p;
            break;
        }
    }

}

void PerspectiveEditor::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPainter canvas_painter (&canvas_image);

    canvas_painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);


    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    painter.setBrush(QBrush(QColor(120, 120, 120)));

    painter.drawRect(QRect(0, 0, this->width() - 1, this->height() - 1));

    QPointF coord_offset = camera_position;

    if(camera_drag_mode) {
        coord_offset = camera_drag_line.p2();
    }

    QRectF canvas_rect = QRectF(coord_offset.x(), coord_offset.y(), canvas.width(), canvas.height());

    canvas_painter.setPen(QPen(Qt::black));
    canvas_painter.setBrush(QBrush(Qt::white));
    canvas_painter.drawRect(canvas);

    for(int p = 0; p < perspective_point_count; p++) {
        QPointF ppoint = coord_offset + perspective_points[p].position;

        QPolygonF canvas_polygon(canvas_rect);

        canvas_polygon.pop_back();

        if(!canvas_rect.contains(ppoint)) {
            QPointF first_point;
            QPointF second_point;

            if(ppoint.x() < canvas_polygon[0].x() && ppoint.y() < canvas_polygon[0].y()) {
                first_point = canvas_polygon[1];
                second_point = canvas_polygon[3];
            } else if (ppoint.x() > canvas_polygon[1].x() && ppoint.y() < canvas_polygon[0].y()) {
                first_point = canvas_polygon[0];
                second_point = canvas_polygon[2];
            } else if(ppoint.x() > canvas_polygon[0].x() && ppoint.y() < canvas_polygon[0].y()) {
                first_point = canvas_polygon[1];
                second_point = canvas_polygon[0];
            }

            if(ppoint.x() > canvas_polygon[2].x() && ppoint.y() > canvas_polygon[2].y()) {
                first_point = canvas_polygon[1];
                second_point = canvas_polygon[3];
            } else if(ppoint.x() > canvas_polygon[1].x() && ppoint.y() > canvas_polygon[1].y()) {
                first_point = canvas_polygon[1];
                second_point = canvas_polygon[2];
            } else if(ppoint.x() > canvas_polygon[3].x() && ppoint.y() > canvas_polygon[2].y()) {
                first_point = canvas_polygon[2];
                second_point = canvas_polygon[3];
            }

            if(ppoint.x() < canvas_polygon[3].x() && ppoint.y() > canvas_polygon[3].y()) {
                first_point = canvas_polygon[0];
                second_point = canvas_polygon[2];
            } else if(ppoint.x() < canvas_polygon[0].x() && ppoint.y() > canvas_polygon[0].y()) {
                first_point = canvas_polygon[0];
                second_point = canvas_polygon[3];
            }

            QPen box_line;
            box_line.setWidth(2);
            box_line.setStyle(Qt::DashLine);
            box_line.setColor(QColor(75, 75, 125));

            painter.setPen(box_line);

            painter.drawLine(ppoint, first_point);
            painter.drawLine(ppoint, second_point);
        }

        QColor line_color = perspective_points[p].line_color;

        line_color.setAlpha(50);

        canvas_painter.setPen(QPen(line_color));

        for(int l = 0; l < perspective_points[p].number_of_lines; l++) {
            QLineF line (perspective_points[p].position, perspective_points[p].position + QPointF(100, 100));

            qDebug() << 360 / (float) perspective_points[p].number_of_lines;

            line.setLength(10000);
            line.setAngle(360 / (float) perspective_points[p].number_of_lines * l);

            canvas_painter.drawLine(line);
        }
    }

    painter.drawImage(coord_offset.x(), coord_offset.y(), canvas_image);

    for(int p = 0; p < perspective_point_count; p++) {
        QPointF ppoint = coord_offset + perspective_points[p].position;

        painter.setBrush(QBrush(QColor(200, 200, 200)));
        painter.setPen(QPen(Qt::black));
        painter.drawEllipse(ppoint, 10, 10);
        painter.drawText(ppoint - QPointF(3, -4), QString::number(p + 1));
    }

    foreach(PerspectivePoint point, perspective_points) {
    }

    painter.setBrush(QBrush(Qt::transparent));
    painter.setPen(QPen(QColor(200, 200, 200)));
    painter.drawRect(QRect(0, 0, this->width() - 1, this->height() - 1));
}
