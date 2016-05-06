#include <QtWidgets>
#include "ball.h"
#include <QGraphicsView>





int main(int argc, char *argv[])
{


    //creation main windows
    QApplication a(argc, argv);
    QWidget wgt;
    QPushButton* button= new QPushButton("Restart");
    ball pBall;
    QGraphicsView* view= new QGraphicsView(&pBall);
    QLabel* lbl= new QLabel("You score = ");
    QLabel* score= new QLabel("0");
    QVBoxLayout* layout = new QVBoxLayout;
    QHBoxLayout* layout1 = new QHBoxLayout;

    //setting up
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    a.setApplicationName("Ball ver.0.2");
    layout1->addWidget(lbl);
    layout1->addWidget(score);
    layout1->addWidget(button);
    layout1->setAlignment(Qt::AlignLeft);
    layout->addLayout(layout1);
    layout->addWidget(view);
    wgt.setLayout(layout);
    wgt.setFixedSize(550,770);
    QObject::connect(&pBall,SIGNAL(pQuitapp()),&a,SLOT(quit()));
    QObject::connect(button,SIGNAL(clicked()),&pBall,SLOT(restart_signal()));
    QObject::connect(&pBall,SIGNAL(ScoreIsChanged(int)),score,SLOT(setNum(int)));
    // start
    pBall.start();
    //show
    wgt.show();
    return a.exec();
}
