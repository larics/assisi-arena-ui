#ifndef QCASUSCENEITEM_H
#define QCASUSCENEITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

#include "qabstractsceneitem.h"

/*!
 * \brief Graphics scene item for CASU
 *
 * All graphical elements for individual CASU are drawn with this item
 */

class QCasuSceneItem : public QAbstractSceneItem
{
private:
    QPointF m_coordinates;
    int m_yaw;
    QElapsedTimer *FPScheck;

    double m_airflowAngle;
    double m_vibrAngle;

    QCasuZMQ *m_zmqObject;

public:
    explicit QCasuSceneItem(QPointF coordinates, double yaw, QCasuZMQ *zmqObject);

    bool isGroup() const Q_DECL_OVERRIDE;
    QList<QSharedPointer<zmqData::zmqBuffer> > getBuffers(zmqData::dataType key) const Q_DECL_OVERRIDE;
    QVector<QPointF> getCoordinateVector() const Q_DECL_OVERRIDE;
    void sendSetpoint(const QList<QByteArray> &message) const Q_DECL_OVERRIDE;
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    QCasuZMQ *getZmqObject();    
};

/*!
 * \brief Calculates bounding rectangle for triangle dependant on IR sensor angle and value
 */
class QIRTriangle : public QRectF
{
public:
    QIRTriangle(QPointF center, double angle, double value);
};
/*!
 * \brief Calculates arc parameters for temperature sensors
 */
class QTempArc
{
public:
    QTempArc(QPointF center, double angle);
    int start;
    int span;
    QRectF rect;
};
/*!
 * \brief Calculates individual petal path for fan animation dependant on petal angle
 */
class QPetal : public QPainterPath
{
public:
    QPetal(QPointF center, double angle);
};
/*!
 * \brief Calculates vibrating circle path for vibration animation dependant on number of wawes and angle
 */
class QVibratingCircle : public QPainterPath
{
public:
    QPointF points[20];
    QVibratingCircle(QPointF center, int waves, double angle);
};

#endif // QCASUSCENEITEM_H
