#ifndef CYCLETHREAD_H
#define CYCLETHREAD_H

#include <QThread>

class CycleThread : public QThread
{
    Q_OBJECT

public:
    CycleThread(QObject*parent=0);

private slots:
    void cycleEvent();

protected:
    void run();

signals:
    void snd_frame_update(int i);
};

#endif // CYCLETHREAD_H
