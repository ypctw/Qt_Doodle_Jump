#ifndef DOODLE_H
#define DOODLE_H

#include <QObject>
#include <QWidget>
#include "_basic.h"

class doodle : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    doodle(QGraphicsScene *mainwin, int i);
    void horizon_intercial(bool direction);
    void doodle_test();
    int ps_R;
    int ps_L;
    double doodle_pos_X;
    double doodle_pos_Y;
    void shot();
    static bool up_down;

public slots:
    void doodle_jump();
    void move_L();
    void move_R();
    void ho_in();
    void aftershot();
    void sync_status();

protected:
    int type = 0;
    int time;
    int L_R;
    static int jump;
    double t_t;
    double place_Y;

    double position;
    int push_time_R = 0;
    int push_time_L = 0;
    QGraphicsPixmapItem *player;
    QPixmap *doodle_pix_type_1;
    QPixmap *doodle_pix_type_2;
    QPixmap *bullet_type_1;
    QPixmap *bullet_type_2;
    QTimer *hor_int;
    QTimer *bullet_timer;
    QTimer *sync_time;
    int k = 0;
};

#endif // DOODLE_H
