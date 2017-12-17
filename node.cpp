#include "node.h"
#include "graphwidget.h"
#include "edge.h"

#include<QDebug>
#include<QGraphicsTextItem>
#include<QGraphicsScene>
#include<QGraphicsSceneMouseEvent>
#include<QStyleOption>
#include<QPainter>


static node* node1 = NULL;
static node* node2 = NULL;

node::node(graphwidget *graphwidget):graphe(graphwidget)
{
    prepareGeometryChange();
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    qDebug() << "new node";
}

void node::inaddedge(edge *edge)
{
    inedgelist << edge;
    edge->adjust();
}

void node::outaddedge(edge *edge)
{
    outedgelist << edge;
    edge->adjust();
}

QList<edge*> node::edges() const
{
    return outedgelist;
}

bool node::advance()
{
    if(newpos==pos())
        return false;
    setPos(newpos);
    return true;
}

QRectF node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-10-adjust,-10-adjust,23+adjust,23+adjust);
}

QPainterPath node::shape() const
{
    QPainterPath path;
    path.addEllipse(-10,-10,20,20);
    return path;
}

void node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{qDebug()<<"node";
    if(event->button() == Qt::RightButton)
    {
        if(this->graphe->src == NULL)
        {this->graphe->src = this;}
        else if((this->graphe->src != NULL)&&(this->graphe->dst == NULL))
            this->graphe->dst = this;
        else
            return;
        qDebug() << "right";
    }
    graphe->timer->stop();

    update();
    QGraphicsItem::mousePressEvent(event);
}

void node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    graphe->timer->stop();
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    graphe->timer->stop();
    if(node1==NULL)
    {node1 = this;return;}
    else
    {
        if(node1==this)
            return;
        node2 =this;
        link(node1,node2);

        parent_list<<node1;

        children_list<<node2;

        node1=NULL;
        node2=NULL;
    }

    update();
    QGraphicsItem::mouseDoubleClickEvent(event);
}

typedef QList<edge*> sometype;


void node::link(node* nd1,node* nd2)
{
    foreach (edge *edg, nd1->outedgelist)
    {
       if(edg->destnode() == nd2)
       {
           qDebug() << "existe deja un arc!";
           qDebug() << nd1->outedgelist.size();

           QList<edge*>::iterator itr = nd1->outedgelist.begin();

           while(itr!=nd1->outedgelist.end())
           {
               if((*itr)==edg)
                   nd1->outedgelist.erase(itr);
           ++itr;
           }

           qDebug() << nd1->outedgelist.size();
           scene()->removeItem(edg);
           return;
       }
    }

    edge* edg = new edge(nd1,nd2);
    scene()->addItem(edg);

}

QVariant node::itemChange(GraphicsItemChange change,const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
    {
        foreach (edge *edg, inedgelist)
        {
            edg->adjust();
        }

        foreach (edge *edg, outedgelist)
        {
            edg->adjust();
        }

        if(graphe->poubelle->sceneBoundingRect().contains(pos()))
        {
            foreach (edge *edg, inedgelist)
            {
                scene()->removeItem(edg);
            }
            foreach (edge *edg, outedgelist)
            {
                scene()->removeItem(edg);
            }
            if(this == graphe->src)
                graphe->src =NULL;
            if(this == graphe->dst)
                graphe->dst =NULL;
            scene()->removeItem(this);
        }

    }
        break;
    default:
        break;
    }
    return QGraphicsItem::itemChange(change,value);
}

void node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);
    QRadialGradient gradient(-3, -3, 10);
    gradient.setCenter(3, 3);
    gradient.setFocalPoint(3, 3);
    if(active == 0)
    {
        if((this != graphe->src)&&(this != graphe->dst))
        {
            if (option->state & QStyle::State_Sunken)
            {
                gradient.setColorAt(1, QColor(Qt::magenta).light(120));
                gradient.setColorAt(0, QColor(Qt::darkMagenta).light(120));
            }
            else
            {
                gradient.setColorAt(0, Qt::magenta);
                gradient.setColorAt(1, Qt::darkMagenta);
            }
            painter->setBrush(gradient);
            painter->setPen(QPen(Qt::black, 0));
            painter->drawEllipse(-10, -10, 20, 20);
        }
        else if(this == graphe->src)
        {
            if (option->state & QStyle::State_Sunken)
            {
                gradient.setColorAt(1, QColor(Qt::red).light(120));
                gradient.setColorAt(0, QColor(Qt::darkRed).light(120));
            }
            else
            {
                gradient.setColorAt(0, Qt::red);
                gradient.setColorAt(1, Qt::darkRed);
            }
        }
        else if(this == graphe->dst)
        {
            if (option->state & QStyle::State_Sunken)
            {
                gradient.setColorAt(1, QColor(Qt::blue).light(120));
                gradient.setColorAt(0, QColor(Qt::darkBlue).light(120));
            }
            else
            {
                gradient.setColorAt(0, Qt::blue);
                gradient.setColorAt(1, Qt::darkBlue);
            }
        }
    }
    else if(active ==1)
    {
        gradient.setColorAt(0, Qt::green);
        gradient.setColorAt(1, Qt::darkGreen);
    }
    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
}

