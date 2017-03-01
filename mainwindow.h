#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <random>
#include "cyclethread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    std::mt19937 mt;
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    QVector<QGraphicsItem *> *m_shapes;
    QVector<QGraphicsItem *> *m_pixs;
    CycleThread m_cycleThread;

    int m_pos_x;
    int m_pos_y;
    int m_vel_x1;
    int m_vel_x2;
    int m_vel_y1;
    int m_vel_y2;

private slots:
    void rcv_frame_update(int i);

protected:
    bool eventFilter(QObject * obj, QEvent * event);
};

#endif // MAINWINDOW_H
