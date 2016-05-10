#include "ball.h"



void ball::keyPressEvent(QKeyEvent* pe)
{

    switch(pe->key())
    {
    case Qt::Key_Left:
        if(pBallItem->x()<pBallItem->pixmap().width()/2)
            mBallSpeed=1;
        if(pBallItem->x()>=mBallSpeed-15)
        {
            pBallItem->setPos(pBallItem->x()-mBallSpeed,pBallItem->y());
                if(ball_collide_with())
                {

                     pBallItem->setPos(pBallItem->x()+mBallSpeed,pBallItem->y());
                     mBallSpeed=1;
                    return;
                }

        }
        break;
    case Qt::Key_Right:

        if(pBallItem->x()>width()-3*pBallItem->pixmap().width()/2)
            mBallSpeed=1;
    if(pBallItem->x()<=width()-pBallItem->pixmap().width()+15)
    {
        pBallItem->setPos(pBallItem->x()+mBallSpeed,pBallItem->y());
        if(ball_collide_with())
        {

            pBallItem->setPos(pBallItem->x()-mBallSpeed,pBallItem->y());
            mBallSpeed=1;
            return;
        }

    }
        break;
    }
       mBallSpeed=SPEED_OF_BALL;


}

void ball::start()
{
    set_pixmapes();
    mBlocksTimer= new QTimer(this);
    mBallTimer= new QTimer(this);
    connect(mBlocksTimer,SIGNAL(timeout()),SLOT(move_blocks()));
    connect(mBallTimer,SIGNAL(timeout()),SLOT(move_ball()));
    setSceneRect(0,0,500,700);
    setBackgroundBrush(QPixmap(".//img/fon.png"));
    plifeItem->setVisible(false);

    restart_full();
    player.setMedia(QUrl::fromLocalFile(".//img/1.mp3"));
   // player.play();


}

ball::ball(QObject *parent) : QGraphicsScene(parent)
{



}

void ball::move_blocks()
{
    int temp=0;
    for(int i=0;i<(signed)p_arr.size() ;++i)
    {
        if(!mStack.contains(i))
        {
            p_arr.at(i)->setPos(p_arr.at(i)->x(),p_arr.at(i)->y()-1);
            if(pBallItem->collidesWithItem(p_arr.at(i)))
            {
                if(pBallItem->x()+pBallItem->pixmap().width()/2>p_arr.at(i)->x()+p_arr.at(i)->pixmap().width())
                    if(pBallItem->x()+pBallItem->pixmap().width()<width())
                        pBallItem->setPos(pBallItem->x()+1,pBallItem->y());
                if(pBallItem->x()+pBallItem->pixmap().width()/2<p_arr.at(i)->x())
                    if(pBallItem->x()>0)
                         pBallItem->setPos(pBallItem->x()-1,pBallItem->y());
                pBallItem->setPos(pBallItem->x(),pBallItem->y()-1);
            }
            if(p_arr.at(i)->y()<0)
            {
                p_arr.at(i)->setPos(600,50);
                mStack.enqueue(i);
                temp=1;
            }
        }


    }
    for(int i=0;i<(signed)p_arrWithShip.size() ;++i)
    {
        if(!mStackWithShip.contains(i))
        {
            p_arrWithShip.at(i)->setPos(p_arrWithShip.at(i)->x(),p_arrWithShip.at(i)->y()-1);
            if(pBallItem->collidesWithItem(p_arrWithShip.at(i)))
                restart();
            if(p_arrWithShip.at(i)->y()<0)
            {
                p_arrWithShip.at(i)->setPos(600,50);
                mStackWithShip.enqueue(i);
                temp=1;
            }
        }


    }
    if(plifeItem->isVisible())
    {
    plifeItem->setPos(plifeItem->x(),plifeItem->y()-1);
    }

    if(plifeItem->y()<0)
    {
        plifeItem->setVisible(false);
        plifeItem->setPos(50,800);
    }
    if(temp)
    {
        mScore++;
        emit ScoreIsChanged(mScore);
        if(!mScore%10)
        {
            if(mPrepSpeed>=4)
               mPrepSpeed-=2;
            mBlocksTimer->setInterval(mPrepSpeed);
        }
        mPrepLastCoordY=the_lowest_prep()+150;
        generate_prep();
        temp=0;
    }


   if(pBallItem->y()<0)
   restart();
}


int ball::the_lowest_prep()
{
    int temp=0;

    for(int i=0;i<(signed)p_arr.size();++i)
        if(!mStack.contains(i))
            if(p_arr.at(i)->y()>temp)
                temp=p_arr.at(i)->y();
    for(int i=0;i<(signed)p_arrWithShip.size();++i)
        if(!mStackWithShip.contains(i))
            if(p_arrWithShip.at(i)->y()>temp)
                temp=p_arrWithShip.at(i)->y();
    return temp;

}


void ball::game_over()
{
    player.stop();
    mBlocksTimer->stop();
    mBallTimer->stop();
    int n = QMessageBox::warning(0,
                                 "Warning",
                                 "Game over!,"
                                 "\n Do you want to restart?",
                                 "Yes",
                                 "No",
                                 QString(),
                                 0,
                                 1
                                );
    if(!n) {
        restart_full();
    }
    else
        emit pQuitapp();
}

void ball::restart()
{
    deshow_lifes();
    int temp=0;
    pBallItem->setPos(250,100);
    while(ball_collide_with())
    {
        temp++;
        pBallItem->setPos(250,100-temp);
    }

    mBallSpeed=SPEED_OF_BALL;
    mBallSpeedFall=1;


}

void ball::restart_full()
{
    mLifesCounter=3;
    mScore=0;
    mBallSpeed=SPEED_OF_BALL;
    mBallSpeedFall=1;
    mPrepSpeed=20;
    pBallItem->setPos(250,100);
    emit ScoreIsChanged(mScore);
    for( int i=0;i<(signed)p_arr_of_lifes.size();++i)
        p_arr_of_lifes.at(i)->setVisible(true);
    mPrepLastCoordY=height();
    mStack.clear();
    mStackWithShip.clear();
    for(int i=0;i<(signed)p_arr.size();i++)
    {
        mStack.enqueue(i);
    }
    for(int i=0;i<(signed)p_arrWithShip.size();i++)
    {
        mStackWithShip.enqueue(i);
    }
    for(int i=0;i<(signed)p_arrWithShip.size();++i)
        p_arrWithShip.at(i)->setPos(100,800);
    for(int i=0;i<(signed)p_arr.size();++i)
        p_arr.at(i)->setPos(100,800);
    initiate_prep();
    mBlocksTimer->start(mPrepSpeed);
    mBallTimer->start(50);




}

void ball::restart_signal()
{
    restart();
}

void ball::move_ball()
{
    static int temp=0;
    temp++;
    if(ball_collide_with())
        return;

    pBallItem->setPos(pBallItem->x(),pBallItem->y()+mBallSpeedFall);

    if(ball_collide_with())
        {
            pBallItem->setPos(pBallItem->x(),pBallItem->y()-mBallSpeedFall);
            mBallSpeedFall=1;
            return;
        }
    if(!temp%2 && mBallSpeedFall<15)
       mBallSpeedFall++;

   if(pBallItem->y()+pBallItem->pixmap().height()>height())
   {
       restart();
   }
}


void ball::deshow_lifes()
{
    if(mLifesCounter>0)
    {
        mLifesCounter--;
        p_arr_of_lifes.at(mLifesCounter)->setVisible(false);
    }
    else
        game_over();
}


void ball::generate_prep()
{
    int temp=0;
    if(mStack.isEmpty())
        return;
    if((qrand()%15<6) || mStack.count()==1)
    {
        if((qrand()%15<7)&&!mStackWithShip.isEmpty())
         {
            temp=mStackWithShip.head();
            p_arrWithShip.at(temp)->setPos(qrand()%((int)width()-p_arrWithShip.at(temp)->pixmap().width()),mPrepLastCoordY);
            mStackWithShip.dequeue();

        }
        else
        {
         temp = mStack.head();
         p_arr.at(temp)->setPos(qrand()%((int)width()-p_arr.at(temp)->pixmap().width()),mPrepLastCoordY);
         mStack.dequeue();

         if(!plifeItem->isVisible())
         {
             plifeItem->setPos(p_arr.at(temp)->x(),p_arr.at(temp)->y()-plifeItem->pixmap().height());
             plifeItem->setVisible(true);
         }

        }

    }
    else
    {
        temp=mStack.head();
        p_arr.at(temp)->setPos(qrand()%((int)width()-2*p_arr.at(temp)->pixmap().width()-2*pBallItem->pixmap().width()),mPrepLastCoordY);

        mStack.dequeue();
        p_arr.at(mStack.head())->setPos(qrand()%((int)width()-(int)p_arr.at(temp)->x()-p_arr.at(temp)->pixmap().width()-2*pBallItem->pixmap().width())+(int)p_arr.at(temp)->x()+p_arr.at(temp)->pixmap().width()+2*pBallItem->pixmap().width(),mPrepLastCoordY);
        mStack.dequeue();
    }


}


void ball::initiate_prep()
{

    while(mStack.size()>7)
    {
        generate_prep();
        mPrepLastCoordY+=150;
    }
}

void ball::show_life()
{
    plifeItem->setVisible(false);
    plifeItem->setPos(50,800);
    if(mLifesCounter<3)
    {
        p_arr_of_lifes.at(mLifesCounter)->setVisible(true);
        mLifesCounter++;
    }
}


int ball::ball_collide_with()
{
    for(int i=0;i<(signed)p_arr.size();i++)
        if(!mStack.contains(i))
            if(pBallItem->collidesWithItem(p_arr.at(i)))
                return 1;
    for(int i=0;i<(signed)p_arrWithShip.size();i++)
        if(!mStackWithShip.contains(i))
            if(pBallItem->collidesWithItem(p_arrWithShip.at(i)))
              restart();
    if(pBallItem->collidesWithItem(plifeItem))
        show_life();
    return 0;

}

void ball::set_pixmapes()
{
    for(int i=0;i< SIZE_OF_LIFES;++i)
        p_arr_of_lifes.push_back(addPixmap(QPixmap(".//img/life.png")));

    for(int i=0;i<(signed)p_arr_of_lifes.size();++i)
       p_arr_of_lifes.at(i)->setPos(p_arr_of_lifes.at(i)->pixmap().width()*i-10,0);

    pBallItem = addPixmap(QPixmap(".//img/ball.png"));

    plifeItem = addPixmap(QPixmap(".//img/life.png"));

    for(int i=0;i< SIZE_OF_PREP;++i)
        p_arr.push_back(addPixmap(QPixmap(".//img/prep.png")));
    for(int i=0;i< SIZE_OF_PREP;++i)
        p_arr.push_back(addPixmap(QPixmap(".//img/prep.png")));
    for(int i=0;i< SIZE_OF_PREP_WITH_SHIPI;++i)
        p_arrWithShip.push_back(addPixmap(QPixmap(".//img/prep_2.png")));
}




