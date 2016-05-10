#pragma once
#include <QtWidgets>
#include <vector>
#include <QGraphicsScene>
#include <QMediaPlayer>

#define SIZE_OF_LIFES 3
#define SIZE_OF_PREP 14
#define SIZE_OF_PREP_WITH_SHIPI 4
#define SPEED_OF_BALL 30


class ball : public QGraphicsScene
{
    Q_OBJECT
private:
    void set_pixmapes(); // set all items pixmap
    void generate_prep(); //generate new preps
    void initiate_prep(); // initiate preps in the begin
    void restart(); // restart when ball is fall but lifes>0
    void restart_full(); //restart when no lifes
    int contains(int); // if prep is in mStack
    int ball_collide_with(); // if ball collide with prep return true
    int the_lowest_prep(); // return number of prep with max y
    void keyPressEvent(QKeyEvent* pe); // key press event
    void deshow_lifes();//deshow 1 life
    void show_life(); // show 1 more life
    void game_over();

   QQueue<int> mStack;   //stack not usable platforms
   QMediaPlayer player;
   QQueue<int> mStackWithShip;
   QGraphicsPixmapItem* pBallItem; // ptr to ball img
   QGraphicsPixmapItem* plifeItem; // ptr to life img
   QVector <QGraphicsPixmapItem*> p_arr; // arr of prep img
   QVector <QGraphicsPixmapItem*> p_arrWithShip; // arr of prep img
   QVector <QGraphicsPixmapItem*> p_arr_of_lifes; // arr of lifes img
   int mBallSpeed; // horizontal speed of ball
   int mBallSpeedFall; // down speed of ball
   int mPrepSpeed;
   int mScore; // score
   int mPrepLastCoordY;
   QTimer* mBlocksTimer; // timer of blocks up
   QTimer* mBallTimer; // timer ball to fall
   int mLifesCounter; // counter of lifes

signals:
   void pQuitapp(); // signal to quit app
   void ScoreIsChanged(int); // signal to change the score

public:

    explicit ball(QObject *parent = 0);
    void start();



protected slots:
    void restart_signal();
    void move_blocks();
    void move_ball();

};



