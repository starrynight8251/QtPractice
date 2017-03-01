#include <QTimer>
#include "cyclethread.h"

CycleThread::CycleThread(QObject*parent):QThread(parent)
{
}

void CycleThread::run(){
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(cycleEvent()));
    timer.setInterval(17);
    timer.start();
    exec();
    timer.stop();
}

void CycleThread::cycleEvent(){
    static int fr = 0;
    emit snd_frame_update(fr++);
}
