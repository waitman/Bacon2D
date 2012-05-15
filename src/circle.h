/**
 * Copyright (C) 2012 by INdT
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "shape.h"

class Circle : public Shape
{
    Q_OBJECT

    Q_PROPERTY(QPointF center READ center WRITE setCenter NOTIFY centerChanged)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)

public:
    Circle(QuasiDeclarativeItem *parent = 0)
        : Shape(parent)
        , m_radius(0)
        {}

    QPointF center() const { return m_center; }
    void setCenter(const QPointF &center) {
        if (m_center == center)
            return;

        m_center = center;

        emit centerChanged();
    }

    qreal radius() const { return m_radius; }
    void setRadius(const qreal &radius) {
        if (radius <= 0.0 || m_radius == radius)
            return;

        m_radius = radius;
        emit radiusChanged();
    }

    void drawShape(QPainter *painter) {
        if (m_radius) {
            qreal halpPen = 0;
            if (m_fill && m_fill->initialized())
                halpPen = m_fill->pen()->widthF() / 2.0;
            painter->drawEllipse(m_center, m_radius - halpPen, m_radius - halpPen);
        }
    }

    void initialize() {
        if (!m_fill)
            return;
        m_fill->initialize();
    }

signals:
    void centerChanged();
    void radiusChanged();

private:
    QPointF m_center;
    qreal m_radius;
};

#endif /* _CIRCLE_H_ */