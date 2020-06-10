#include "bullet.h"

bullet::bullet(QGraphicsScene *mainwin, const int i, const double X, const double Y) : blt(new QGraphicsPixmapItem),
                                                                                       X_axis(X),
                                                                                       Y_axis(Y),
                                                                                       type(i),
                                                                                       bullet_pix_type_1(new QPixmap(":/rec/photo/bullet/brown.png")),
                                                                                       bullet_pix_type_2(new QPixmap(":/rec/photo/bullet/blue.png")),
                                                                                       blt_time(new QTimer),
                                                                                       here(mainwin)
{
    blt->setPos(X_axis + Doodle_SIZE / 2 - 20, Y_axis);
    if (type == 1)
        blt->setPixmap(bullet_pix_type_1->scaled(Doodle_SIZE / 3, Doodle_SIZE / 3));
    if (type == 2)
        blt->setPixmap(bullet_pix_type_1->scaled(Doodle_SIZE / 5, Doodle_SIZE / 5));

    mainwin->addItem(blt);
}

void bullet::fly()
{
    Y_axis -= 10;
    blt->setPos(X_axis + 5, Y_axis - 20);
    if (Y_axis < 20)
    {
        this->here->removeItem(blt);
        delete this;
    }
}

void bullet::con()
{
    if (!blt_time)
        delete blt_time;
    blt_time = new QTimer;
    connect(blt_time, SIGNAL(timeout()), this, SLOT(fly()));
    blt_time->start(10);
}