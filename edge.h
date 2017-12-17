#ifndef EDGE_H
#define EDGE_H

#include<QGraphicsItem>
class node;
enum etatEdge {NONSELECTION=0,SELECTION=1,RETOUR=2};

class edge:public QGraphicsItem
{
public:
    edge(node *sourcenode,node *destnode);
    node *sourcenode() const;
    node *destnode() const;
    void adjust();

    void setvalue(qreal value);
    float getvalue();

    enum{Type = UserType + 2 };
    int type() const Q_DECL_OVERRIDE{return Type;}

    etatEdge state = NONSELECTION;

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);

private:
    node *source,*dest;
    QPointF sourcePoint,destPoint;
    qreal arrowSize;
    qreal value = 0;
};

#endif // EDGE_H
