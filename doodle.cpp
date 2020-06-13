#include "doodle.h"

doodle::doodle(QGraphicsScene *mainwin, int i) : ps_R(0),
                                                 ps_L(0),
                                                 doodle_pos_X(Default_X),
                                                 doodle_pos_Y(Default_Y),
                                                 type(i),
                                                 L_R(0),
                                                 place_Y(Default_Y),
                                                 player(new QGraphicsPixmapItem),
                                                 hor_int(new QTimer),
                                                 sync_time(new QTimer),
                                                 doodle_pix_type_1{QPixmap(":/rec/photo/player/scene1/L.png"),
                                                                   QPixmap(":/rec/photo/player/scene1/R.png"),
                                                                   QPixmap(":/rec/photo/player/scene1/S.png")},
                                                 doodle_pix_type_2{QPixmap(":/rec/photo/player/scene1/L.png"),
                                                                   QPixmap(":/rec/photo/player/scene1/R.png"),
                                                                   QPixmap(":/rec/photo/player/scene1/S.png")}
{
    player->setPos(doodle_pos_X, doodle_pos_Y);
    for (int m = 0; m < 2; ++m)
    {
        doodle_pix_type_1[m] = doodle_pix_type_1[m].scaled(Doodle_SIZE, Doodle_SIZE);
        doodle_pix_type_2[m] = doodle_pix_type_2[m].scaled(Doodle_SIZE, Doodle_SIZE);
    }
    doodle_pix_type_1[2] = doodle_pix_type_1[2].scaled(Doodle_SIZE - 20, Doodle_SIZE + 20);
    doodle_pix_type_2[2] = doodle_pix_type_2[2].scaled(Doodle_SIZE - 20, Doodle_SIZE + 20);
    player->setPixmap(doodle_pix_type_1[0]);
    mainwin->addItem(player);
    sync_time->start(1);
    connect(sync_time, SIGNAL(timeout()), this, SLOT(sync_status()));
}
//Y
bool doodle::judge() //collide
{

    bool test = false;
    if (up_or_down)  //upup
        return test; //no collide
    //down
    for (int tt = 0; tt < Platform_NUM; ++tt)
    {
        test = player->collidesWithItem(_main.pltfm_QItem.at(tt), Qt::IntersectsItemShape);
        if (test)
        {
            Y_to_stay = Default_Y - _main.pltfm_QItem.at(tt)->y();
            break;
        }
    }
    return test;
}
void doodle::to_jump() //Y
{
    if (judge())
        change();
    r_doodle_jump();
}
void doodle::change() //Y
{
    jump = 101 - jump;
    emit platform_move(Y_to_stay, jump);
}
/*
void doodle::doodle_jump() //Y
{

    if (jump == 100)
    {
        jump = 0;
        return;
    }
    t = jump % Doodle_Jump_time_int;
    if (t == 0)
        doodle_pos_Y = Default_Y;
    if (t > (Doodle_Jump_time_int / 2))
    {
        int k = t;
        k -= (Doodle_Jump_time_int / 2);
        double t_t = 2 * k + 1;
        double temp = (Doodle_vertical_acc * t_t) / 2.0;
        doodle_pos_Y += temp * (100.0 / Doodle_Jump_time);
        up_or_down = true;
    }
    else
    {
        double t_t = -1 * 2 * (t - (Doodle_Jump_time_int / 2) + 1) + 1;
        double temp = (Doodle_vertical_acc * t_t) / 2.0;
        doodle_pos_Y -= temp * (100.0 / Doodle_Jump_time);
        up_or_down = false;
    }
    ++jump;
}*/
bool doodle::check_place() //Y check
{
    sync_status();
    if (player->y() > DOODLE_HIGH)
        up_down = true;

    if (player->y() < DOODLE_LOW + 10)
        up_down = false;
    //up
    if (up_down)      //
        return false; //upup
    else
        return true; //down
}
void doodle::r_doodle_jump() //revise Y jump
{
    jump++;
    jump %= Doodle_Jump_time_int;
    if (check_place())
        lowlow(); //down
    else
        upup(); //up
}
void doodle::upup() //Y up
{
    int t = (jump % (Doodle_Jump_time_int / 2));
    doodle_pos_Y -= (DOODLE_ACC / 2) * (2 * t + 1);
    up_down = true;
}
void doodle::lowlow() //Y down
{
    int t = jump % (Doodle_Jump_time_int / 2);
    t = 49 - t;
    doodle_pos_Y += (DOODLE_ACC / 2) * (2 * t + 1);
    up_down = false;
}
//X
void doodle::move_R() //X
{
    ++push_time_R;
    player->setPixmap(doodle_pix_type_1[1]);
    doodle_test();
    doodle_pos_X += Move_By;
    horizon_intercial(false);
    doodle_test();
    player->setX(doodle_pos_X);
}
void doodle::move_L() //X
{
    ++push_time_L;
    player->setPixmap(doodle_pix_type_1[0]);
    doodle_test();
    doodle_pos_X -= Move_By;
    horizon_intercial(true);
    doodle_test();
    player->setX(doodle_pos_X);
}

void doodle::horizon_intercial(bool direction) //X
{
    if (direction)
        L_R = -1;
    else
        L_R = 1; //R
    time = 0;
    if (!hor_int)
    {
        delete hor_int;
        hor_int = new QTimer;
    }
    hor_int->start(10);
    connect(hor_int, SIGNAL(timeout()), this, SLOT(ho_in()));
}
void doodle::ho_in() //X inertia
{
    time++;
    if (time >= Doodle_horizonal_run)
    {
        delete hor_int;
        hor_int = new QTimer;
        time = 0;
        push_time_L = 0;
        push_time_R = 0;
        return;
    }
    position = 0;
    if (L_R == 1)
        --push_time_R;
    else
        --push_time_L;
    double vel = L_R * Doodle_horizonal_vel - (push_time_R - push_time_L) * Doodle_per_push * Doodle_vertical_acc;
    double acc = vel / Doodle_horizonal_run;

    position = vel - (acc / 2) * (2 * this->time + 1);
    doodle_pos_X += position;
    doodle_test();
}
void doodle::doodle_test() //X check
{
    if (doodle_pos_X >= Scene_X - Doodle_SIZE * 0.5)
    {
        doodle_pos_X -= (Scene_X);
        doodle_pos_X -= Doodle_SIZE / 2;
    }
    if (doodle_pos_X < Doodle_SIZE * -1 * 0.5)
    {
        doodle_pos_X += Scene_X;
        doodle_pos_X += Doodle_SIZE / 2;
    }
}

//shot
void doodle::shot()
{
    this->player->setPixmap(doodle_pix_type_1[2]);
    QTimer::singleShot(150, this, SLOT(aftershot()));
}
void doodle::aftershot() { player->setPixmap(doodle_pix_type_1[1]); }

//X_Y
void doodle::sync_status() { player->setPos(doodle_pos_X, doodle_pos_Y); }
