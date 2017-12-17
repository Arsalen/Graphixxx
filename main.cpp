#include "graphwidget.h"
#include<QApplication>
#include<QTime>
#include<QMainWindow>
#include<QPushButton>
#include<QDebug>
#include <QDockWidget>


int main(int argc,char **argv)
{
    QApplication App(argc,argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    graphwidget *window = new graphwidget;

    QMainWindow mainWindow;
    QString background_color="background:rgb(223, 242, 255)";
    mainWindow.setStyleSheet(background_color);
    mainWindow.setCentralWidget(window);
    mainWindow.setFixedWidth(800);
    mainWindow.setFixedHeight(650);
    mainWindow.setWindowTitle("GRAPH MANIPULATOR");



    QPushButton*pp=new QPushButton("Parcours en profondeur",&mainWindow);
    pp->setStyleSheet(background_color);
    pp->setFixedWidth(120);
    pp->setToolTip("Parcours en profondeur");
    pp->setGeometry(25,25,50,30);
    QMainWindow::connect(pp,SIGNAL(clicked()),window,SLOT(ParcoursProfondeur()));


    QPushButton*pl=new QPushButton("Parcours en largeur",&mainWindow);
    pl->setStyleSheet(background_color);
    pl->setFixedWidth(120);
    pl->setToolTip("Parcours en largeur");
    pl->setGeometry(25,55,50,30);
    QMainWindow::connect(pl,SIGNAL(clicked()),window,SLOT(ParcoursLargeur()));

    QPushButton*djik=new QPushButton("Dijkstra",&mainWindow);
    djik->setStyleSheet(background_color);
    djik->setFixedWidth(120);
    djik->setToolTip("Dijkstra");
    djik->setGeometry(25,85,50,30);
    QMainWindow::connect(djik,SIGNAL(clicked()),window,SLOT(Dijkstra()));

    QPushButton*cnx=new QPushButton("Connexité",&mainWindow);
    cnx->setStyleSheet(background_color);
    cnx->setFixedWidth(120);
    cnx->setToolTip("Connexité");
    cnx->setGeometry(25,115,50,30);
    QObject::connect(cnx, SIGNAL(clicked()), window, SLOT(connexe()));

    QPushButton*rst=new QPushButton("Reset",&mainWindow);
    rst->setStyleSheet(background_color);
    rst->setFixedWidth(120);
    rst->setToolTip("reset");
    rst->setGeometry(25,175,50,30);
    QObject::connect(rst, SIGNAL(clicked()), window, SLOT(reset()));

    QPushButton*rg=new QPushButton("nombre",&mainWindow);
    rg->setStyleSheet(background_color);
    rg->setFixedWidth(120);
    rg->setToolTip("nombre de noeuds");
    rg->setGeometry(25,205,50,30);
    QMainWindow::connect(rg,SIGNAL(clicked()),window,SLOT(rang()));

    QPushButton*about=new QPushButton("ABOUT",&mainWindow);
    about->setStyleSheet(background_color);
    about->setToolTip("Infos sur L'application");
    about->setFixedWidth(120);
    about->setGeometry(25,235,50,30);
    QMainWindow::connect(about,SIGNAL(clicked()),window,SLOT(about()));

    QPushButton*help=new QPushButton("HELP",&mainWindow);
    help->setStyleSheet(background_color);
    help->setToolTip("Aide!");
    help->setFixedWidth(120);
    help->setGeometry(25,265,50,30);
    QMainWindow::connect(help,SIGNAL(clicked()),window,SLOT(help()));





    QPushButton*quit=new QPushButton("QUIT",&mainWindow);
    quit->setStyleSheet(background_color);
    quit->setFixedWidth(120);
    quit->setToolTip("Quitter le programme");
    quit->setGeometry(25,295,50,30);
    QObject::connect(quit, SIGNAL(clicked()), &App, SLOT(quit()));




    mainWindow.show();
    return App.exec();
}
