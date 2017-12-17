#include "graphwidget.h"
#include "node.h"
#include "edge.h"

#include<QMessageBox>
#include<QTimer>
#include<QCursor>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include<math.h>
#include<QPair>
#include<QMap>
#include<QVector>
#include<QStack>
#include<QList>
#include<QQueue>
#include<QPushButton>
#include<QGraphicsItem>
#include<algorithm>
#include<QPixmap>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>
#include <QGraphicsPixmapItem>

static int ctrl =0;
static bool pressed = false;


graphwidget::graphwidget(QWidget *parent):QGraphicsView(parent)//,timerId(0)
{
    scene->setSceneRect(-200,-200,400,400);
    setScene(scene);
    setMinimumSize(400,400);

    timerId = startTimer(0);

    connexe_verify=new QLineEdit();
    scene->addWidget(connexe_verify);
    connexe_verify->setText("CONNEXITY ?");
    connexe_verify->setStyleSheet("background:white;color: black; font-size: 8px;");
    connexe_verify->setAlignment(Qt::AlignCenter);
    connexe_verify->setFixedHeight(20);
    connexe_verify->setFixedWidth(120);
    connexe_verify->setGeometry(-375,-175,connexe_verify->width(),connexe_verify->height());

poubelle->setPos(300,220);
}

void graphwidget::rang()
{int cpt = 0;
    foreach (QGraphicsItem *item, scene->items())
        {
            node *nd = qgraphicsitem_cast<node*>(item);
            if(!nd)
                continue;
            cpt++;
        }
    qDebug() << cpt;
}


node* graphwidget::getsource()
{
    return src;
}
node* graphwidget::getdestination()
{
    return dst;
}






void graphwidget::mousePressEvent(QMouseEvent *event)
{
    QPoint viewPoint = this->mapFromGlobal(QCursor::pos());
    QPointF scenePoint = this->mapToScene(viewPoint);

    qDebug() << scenePoint;


    if(event->button() == Qt::LeftButton)
        pressed = true;

    timer->setSingleShot(true);
        connect(timer, SIGNAL(timeout()), this, SLOT(create()));
        timer->start(100);

        foreach (QGraphicsItem *item, scene->items())
        {
            QPoint viewPoint = this->mapFromGlobal(QCursor::pos());
            QPointF scenePoint = this->mapToScene(viewPoint);
            if(item->contains(scenePoint))
            {timer->stop();qDebug()<<"noeud";}
        }
    update();
    QGraphicsView::mousePressEvent(event);
}
void graphwidget::mouseReleaseEvent(QMouseEvent *event)
{
    update();
    QGraphicsView::mouseReleaseEvent(event);
}

void graphwidget::create()
{
    if(pressed==true)
    {
        QPoint viewPoint = this->mapFromGlobal(QCursor::pos());
        QPointF scenePoint = this->mapToScene(viewPoint);
        node *nd = new node(this);



       nd->setPos(scenePoint);
       node_list<<nd;

        scene->addItem(nd);
        pressed = false;
    }
}

typedef QMap<node*, QPair<float,node*> > mypairtype;
typedef QPair<node*,node*> pairess;


bool graphwidget::contient(node *nd,mypairtype &mymap)
{
    mypairtype::iterator itr = mymap.begin();

    while(itr != mymap.end())
    {
        if(itr.key() == nd)
            return true;
        ++itr;
    }
    return false;


}



mypairtype::iterator graphwidget::miner(mypairtype &mymap)
{
    float n = 999;
    mypairtype::iterator itr = mymap.begin();
    if(mymap.size()==1)
        return itr;
    mypairtype::iterator mtr;
    while(itr != mymap.end())
    {qDebug() << itr.value().first ;
        if(itr.value().first < n)
        {
            n = itr.value().first;
                mtr = itr;
        }
    ++itr;
    }//qDebug() << "miner::::::::::::::::" << mtr.value().first;
    return mtr;
}


void graphwidget::Dijkstra()
{
    foreach (QGraphicsItem *item, scene->items())
    {
        edge *edg = qgraphicsitem_cast<edge*>(item);
        if(!edg)
            continue;

        foreach (QGraphicsItem *item, scene->items())
            {
                QGraphicsTextItem *txt = qgraphicsitem_cast<QGraphicsTextItem*>(item);
                if(!txt)
                    continue;
                if(txt->parentItem()==edg)
                    edg->setvalue(txt->toPlainText().toFloat());
            }
    }

    QPair<float,node*> mypair;
    mypairtype mymap;

    foreach (QGraphicsItem *item, scene->items())
    {
        node *nd = qgraphicsitem_cast<node*>(item);
        if(!nd)
            continue;
        mypair.first = 1000;
        mypair.second = NULL;
        mymap[nd]=mypair;
    }
qDebug() << "size of mymap" << mymap.size();
mymap.find(src).value().first = 0;
mypairtype othermap;

static int kbr = 0;
while(!(mymap.isEmpty()))
{ //qDebug() << "Node n:" << kbr ;
    kbr++;
    int salut = 0;
    //qDebug() << "nombres des arcs sortants: " << mymap.find(src).key()->edges().size() ;
    //int salut = 0;
    foreach (edge* edg, mymap.find(src).key()->edges())
    {//salut++;
        //if(mymap.find(edg->destnode()) == mymap.end()) {continue;};
        if(contient(edg->destnode(),mymap) == false) {qDebug() << "n'existe pas"; ;continue;}
        if( mymap.find(edg->destnode()).value().first > mymap.find(src).value().first + edg->getvalue() )
        {//qDebug() << mymap.find(edg->destnode()).value().first << "=" << mymap.find(src).value().first << "+" << edg->getvalue() ;
            mymap.find(edg->destnode()).value().first = mymap.find(src).value().first + edg->getvalue();
            mymap.find(edg->destnode()).value().second = src;
        }
    }
    othermap[src] = mymap.find(src).value();
    mymap.erase(mymap.find(src));
    if(mymap.isEmpty())
        qDebug() << "emptyMap";
    else
        src = miner(mymap).key();
}


    mypairtype::iterator ptr = othermap.begin();

    ptr = othermap.find(dst);

    while(ptr.value().first != 0)
    {
        QPair <node*,node*> paires;
        paires.first = ptr.key();
        paires.second = ptr.value().second;
        pcc << paires;
        ptr = othermap.find(ptr.value().second);
    }

    QPen pen(Qt::red, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);

    foreach (pairess parite, pcc)
        {
            QLineF line(parite.first->pos(),parite.second->pos());
            scene->addLine(line,pen);
        }





}







void graphwidget::Delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void graphwidget::ParcoursLargeur()
{
        QQueue<node*> queue;
        queue.push_back(src);

        //qDebug() << "BFS: ";
        while(!queue.empty())
        {
            src = queue.front();
            src->state = VISITE;

            src->active = 1;
            Delay(1000);
            src->update();

            queue.pop_front();
            for(int cpt=0;cpt<src->edges().size();cpt++)
            {
                if(src->edges()[cpt]->destnode()->state != VISITE)
                    queue.push_back(src->edges()[cpt]->destnode());
            }
        }
        //qDebug() << "endl";
}


void graphwidget::reset()
{
 //   this = new graphwidget;
    foreach (QGraphicsItem *item, scene->items())
    {
        node* nd =qgraphicsitem_cast<node*>(item);
        edge* edg=qgraphicsitem_cast<edge*>(item);

        if((!nd) && (!edg))
            continue;
        scene->removeItem(item);
    }

    src = NULL;
    dst = NULL;


}

void graphwidget::about()
    {
        QMessageBox*msgBox=new QMessageBox(this);
        msgBox->setText("Graph Manipulator Created By :\n\n Rayen Messaoudi \n Arsalen Hagui");
        msgBox->setWindowTitle("About Program");
        msgBox->setGeometry(250,250,400,325);
        msgBox->setStyleSheet("background:rgb(223, 242, 255)");
        msgBox->exec();

    }




void graphwidget::help()
    {
        QMessageBox*msgBoxx=new QMessageBox(this);
        msgBoxx->setText("Once you click on the interface, you will create a single node.\n To link 2 nodes, you have to double click the source node first, then the destination node, this will create an edge which links between the source and the destination, by default, the its value is equal to zero, you may change by clicking on it.\n To remove an edge you need to do the same as you did when you have created it.\n Drag and drop a node to the trash flag will remove it.\n To choose the source node of your graph, rightClick one node and its color will turn to Red, then do the same when you choose the destination node (its color then turns to blue).\n Each of the PushButtons on the topleft of the interface is a reference to an algorithm.\n Note that you must first choose a  source and a destination node when you push the \"Shortest path\" button, only a source node for the \"Depth first search\" and \"Breadth first search\".\n Note: the algorithm of the Shortest path is based on Dijkstra Algorithm.");
        msgBoxx->setWindowTitle("Aide");
        msgBoxx->setGeometry(250,250,400,325);
        msgBoxx->setStyleSheet("background:rgb(223, 242, 255)");
        msgBoxx->exec();

    }



void graphwidget::ParcoursProfondeur()
{
    QStack<node*> stack;
    stack.push(src);

    vector<int>::iterator i;
    qDebug() << "DFS: ";

    while(!stack.empty())
    {
       src = stack.top();//node* top
       qDebug() << src->pos() << " ";
       stack.pop();
       src->state = VISITE;
       src->active = 1;
       Delay(1000);
       src->update();

       int cpt = 0;
       for(cpt=0;cpt<src->edges().size();cpt++)
       {
           if(src->edges()[cpt]->destnode()->state != VISITE)
               stack.push(src->edges()[cpt]->destnode());
       }
    }
    qDebug() << "endl";

}

void graphwidget::connexe()
{
    node*depart_node=node_list[0];
    depart_node->couleur=QColor(255,255,255);
    foreach (node*var1, node_list)
    {
        if(var1->couleur==QColor(255,255,255))
        {
            foreach (node*var2, var1->children_list)
            {
               var2->couleur=QColor(255,255,255);
            }
            foreach (node*var2, var1->parent_list)
            {
                var2->couleur=QColor(255,255,255);
            }
        }
        update();
    }
    bool connexe1=true;
    foreach (node*var1, node_list)
    {
        if(var1->couleur!=QColor(255,255,255))
        {
            connexe1=false;
        }
    }
    if(connexe1)
    {
        connexe_verify->setText("Connexe");
        connexe_verify->setStyleSheet("background:white;color: green; font-size: 14px;");}

    else
        {
        connexe_verify->setText("Non-Connexe");
        connexe_verify->setStyleSheet("background:white;color: red; font-size: 14px;");}

}






void graphwidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    int find=0;
    foreach (node *node1, node_list)
    {
        node1->setX(qMin(388.0,node1->x()));
        if(node1->y()<-60)
            node1->setX(qMax(-245.0,node1->x()));
        else
            node1->setX(qMax(-370.0,node1->x()));

        node1->setY(qMin(312.0,node1->y()));
        node1->setY(qMax(-312.0,node1->y()));


    }


}



