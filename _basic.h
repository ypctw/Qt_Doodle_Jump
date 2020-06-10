#ifndef _BASIC_H
#define _BASIC_H

//headerfile

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsItemGroup>
#include <QKeyEvent>
#include <QTimer>
#include <iostream>


//define

#define bigger_sqrt 1.414
#define Scene_X 400
#define Scene_Y 800
#define Default_X 200
#define Default_Y 550
#define Doodle_SIZE 60

//doodle jump time
    //double
#define Doodle_Jump_time 200.0
    //int
#define Doodle_Jump_time_int 150

// 2/sqrt(Doodle_Jump_time_int/100)/10
#define Doodle_vertical_acc 0.16329*1.3*1.4

#define Doodle_horizonal_acc 0.02
#define Doodle_horizonal_run 100
#define Doodle_horizonal_vel (Doodle_horizonal_acc*Doodle_horizonal_run)
#define Doodle_per_push 0.01
#define Move_By 10

#endif // _BASIC_H
