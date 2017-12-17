#include "edge.h"
#include "node.h"
#include<math.h>
#include<QPainter>
#include<QGraphicsTextItem>
#include<QDebug>

static const double Pi = 3.14159265358979323846264338327950288419717;
static const double TwoPi = 2.0*Pi;

edge::edge(node *sourcenode,node *destnode):arrowSize(10)
{
    setAcceptedMouseButtons(0);
    source = sourcenode;
    dest = destnode;
    source->outaddedge(this);
    dest->inaddedge(this);
    adjust();

    QGraphicsTextItem *text = new QGraphicsTextItem("00",this) ;
    text->setTextInteractionFlags(Qt::TextEditorInteraction);
    text->setPos((sourcenode->pos().x()+destnode->pos().x())/2,(sourcenode->pos().y()+destnode->pos().y())/2);
}

node *edge::sourcenode() const
{
    return source;
}
node *edge::destnode() const
{
    return dest;
}

void edge::adjust()
{
    if(!source||!dest)
        return;
    QLineF line(mapFromItem(source,0,0),mapFromItem(dest,0,0));
    prepareGeometryChange();
    sourcePoint = line.p1();
    destPoint = line.p2();
    if(childItems().size() > 0)
    childItems()[0]->setPos(((sourcePoint.x()+destPoint.x())/2),(sourcePoint.y()+destPoint.y())/2); ;
    update();
}
void edge::setvalue(qreal valeur)
{
    value = valeur;
}
float edge::getvalue()
{
    return value;
}

QRectF edge::boundingRect() const
{
    if(!source||!dest)
        return QRectF();
    qreal penwidth = 1;
    qreal extra = (penwidth + arrowSize) / 2.0;
    return QRectF(sourcePoint, QSizeF(destPoint.x()-sourcePoint.x(),destPoint.y()-sourcePoint.y())).normalized().adjusted(-extra, -extra,extra,extra);
}

void edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;
    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TwoPi - angle;
    //QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + Pi / 3) * arrowSize,
    //                                              cos(angle + Pi / 3) * arrowSize);
    //QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
    //                                              cos(angle + Pi - Pi / 3) * arrowSize);
    QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,
                                              cos(angle - Pi / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
                                              cos(angle - Pi + Pi / 3) * arrowSize);
    painter->setBrush(Qt::black);
    //painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}
