#ifndef NODE_H
#define NODE_H

#include<QGraphicsItem>
#include<QList>
#include<QSet>

class graphwidget;
class edge;
class QGraphicsSceneMouseEvent;
enum etatNode {NONEXPL=0,VISITE=1};
typedef QList<edge*> sometype;
class node: public QGraphicsItem
{
public:
    node(graphwidget *graphe);
    void inaddedge(edge *edge);
    void outaddedge(edge *edge);
    QList<edge*>edges() const;
    bool advance();
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *);
    void link(node* nd1,node* nd2);


    int active = 0;
    int rang = 50;

    etatNode state = NONEXPL;
    enum {Type = UserType + 1};
    int type() const Q_DECL_OVERRIDE{return Type;}


protected:
    QVariant itemChange(GraphicsItemChange change,const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);




public:
    QList<edge*> inedgelist;
    QList<edge*> outedgelist;
    QPointF newpos;
    graphwidget *graphe;
    QColor couleur;
    QList<node*> parent_list;
    QList<node*> children_list;






};

#endif // TESTNODE_H
