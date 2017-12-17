#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H
#include "node.h"
#include "edge.h"
using namespace std;
#include<QGraphicsView>
#include<stdio.h>
#include<QPair>
#include<QMap>
#include<QPushButton>
#include<QTimer>
#include <QTextEdit>

#include <QTime>
#include<QLabel>
#include <QLineEdit>
#include <QCoreApplication>
#include <QEventLoop>
class node;

typedef QMap<node*, QPair<float,node*> > mypairtype;
typedef QList<QPair<node*,node*> > mylisttype;
class graphwidget: public QGraphicsView
{
    Q_OBJECT
public:
    graphwidget(QWidget *parent = 0 );
    graphwidget(QWidget *parent,int a);
    QGraphicsScene *scene= new QGraphicsScene(this);
    mypairtype::iterator miner(mypairtype &mymap);
        QTimer *timer = new QTimer(this);
    void Delay(int millisecondsToWait);
    node* getsource();
    node* getdestination();
    node *src= NULL;
    node *dst= NULL;
    bool contient(node *nd,mypairtype &mymap);

    QGraphicsPixmapItem *poubelle = scene->addPixmap( QPixmap( "C:/Users/Hagui/Desktop/poubelle (1).jpg" ) );

    //int rang();


protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event);


public slots:
    void ParcoursProfondeur();
    void ParcoursLargeur();
    void connexe();
    void Dijkstra();
    void about();
    void create();
    void help();
    void rang();
    void reset();


private:
    node *centerNode;
    QList<node*> node_list;

    QLineEdit*connexe_verify;

    int timerId;
    mypairtype mymap;
    mylisttype pcc;
};

#endif // TESTGRAPHWIDGET_H
