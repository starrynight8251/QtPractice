#include <QMouseEvent>
#include <random>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "myshapeitem.h"
#include "myimageitem.h"

// スクリーンサイズ定数
static const int SCENE_W = 640;
static const int SCENE_H = 480;

// 図形アイテム基準位置、移動情報定数
static const int CNTX = 5;
static const int CNTY = 5;
static const int SPAN = 100;
static const int RADIUS = 100;

// 画像アイテム基準位置、移動情報定数
static int x_mid,y_mid;
static int bx[CNTX],by[CNTY];
static const int MV_STEP = 4;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // 乱数初期化
    std::random_device rnd;
    mt.seed(rnd());

    // UI初期化
    ui->setupUi(this);
    // イベントフィルタを追加（キーイベント）
    installEventFilter(this);

    // シーン初期化
    m_scene = new QGraphicsScene(0, 0, SCENE_W, SCENE_H);
    // UI上のグラフィクスビューにシーンをセット
    ui->graphicsView->setScene(m_scene);

    // 図形、画像アイテムリスト初期化
    m_shapes = new QVector<QGraphicsItem *>();
    m_pixs  = new QVector<QGraphicsItem *>();

    // 図形、画像アイテム初期化
    // シーンへの追加
    for(int i=0; i<CNTY; i++){
        for(int j=0; j<CNTX; j++){
            QGraphicsItem *item = new MyShapeItem(QColor(mt()%256,mt()%256,mt()%256));
            item->hide();//非表示
            m_shapes->push_back(item);
            m_scene->addItem(item);
        }
    }

    QPixmap pix = QPixmap(":/img/airman.png");
    QRectF src_rect = pix.rect();
    QRectF dst_rect(-src_rect.width()/2,-src_rect.height()/2,
                    src_rect.width(),src_rect.height());
    QGraphicsItem *item = new MyImageItem(dst_rect, pix, src_rect);
    item->hide();//非表示
    m_pixs->push_back(item);
    m_scene->addItem(item);

    // 図形アイテム基準位置初期化
    x_mid = m_scene->width() / 2;
    y_mid = m_scene->height() / 2;
    for(int j=0; j<CNTX; j++){
        bx[j] = SPAN*j - SPAN*(CNTX-1)/2;
    }
    for(int i=0; i<CNTY; i++){
        by[i] = SPAN*i - SPAN*(CNTY-1)/2;
    }

    // 画像アイテム位置、移動速度初期化
    m_pos_x = x_mid;
    m_pos_y = y_mid;
    m_vel_x1 = 0; m_vel_x2 = 0;
    m_vel_y1 = 0; m_vel_y2 = 0;

    // 周期スレッドからフレーム更新シグナルが来たらフレーム更新スロットを起動
    QObject::connect(&m_cycleThread, SIGNAL(snd_frame_update(int)),
                     this, SLOT(rcv_frame_update(int)));
    m_cycleThread.start();
}

MainWindow::~MainWindow()
{
    // 周期スレッド停止要求、終了を待つ
    m_cycleThread.quit();
    m_cycleThread.wait();

    // 図形、画像アイテム解放
    for(int i=0; i<m_shapes->count(); i++){
        QGraphicsItem *item = (*m_shapes)[i];
        m_scene->removeItem(item);
        delete item;
    }
    m_shapes->clear();
    for(int i=0; i<m_pixs->count(); i++){
        QGraphicsItem *pix = (*m_pixs)[i];
        m_scene->removeItem(pix);
        delete pix;
    }
    m_pixs->clear();

    // 図形、画像アイテムリスト解放
    delete m_shapes;
    delete m_pixs;

    // シーン、UI解放
    delete m_scene;
    delete ui;
}

void MainWindow::rcv_frame_update(int fr){
    // 図形アイテム位置情報更新
    // 基準位置からの差分だけ計算する
    float rad = qDegreesToRadians((float)fr);
    float dx = RADIUS * cos(rad);
    float dy = RADIUS * sin(rad);

    for(int i=0; i<CNTY; i++){
        for(int j=0; j<CNTX; j++){
            QGraphicsItem *item = (*m_shapes)[CNTX*i+j];
            float x = x_mid + bx[j] + dx;
            float y = y_mid + by[i] + dy;
            item->setPos(x,y);
            item->show();//表示
        }
    }

    // 画像アイテム位置情報更新
    // K右 H左 M下 U上　キーにより移動
    QGraphicsItem *pix2 = (*m_pixs)[0];
    m_pos_x += (m_vel_x1 + m_vel_x2);
    m_pos_y += (m_vel_y1 + m_vel_y2);
    pix2->setPos(m_pos_x ,m_pos_y);
    pix2->show();//表示

    // シーン再描画要求
    m_scene->update();
}

bool MainWindow::eventFilter(QObject *, QEvent * event)
{
    QKeyEvent * keyEvent;
    int key;

    //　キーが押された時のイベントの処理
    if(event->type() == QEvent::KeyPress){
        keyEvent = static_cast<QKeyEvent * >(event);
        key = keyEvent->key();

        if(key == Qt::Key_K){
            m_vel_x1 = MV_STEP;
        }
        if(key == Qt::Key_H){
            m_vel_x2 = -MV_STEP;
        }
        if(key == Qt::Key_M){
            m_vel_y1 = MV_STEP;
        }
        if(key == Qt::Key_U){
            m_vel_y2 = -MV_STEP;
        }

        return true;
    }

    //　キーが離された時のイベントの処理
    if(event->type() == QEvent::KeyRelease){
        keyEvent = static_cast<QKeyEvent* >(event);
        key = keyEvent->key();

        if(key == Qt::Key_K){
            m_vel_x1 = 0;
        }
        if(key == Qt::Key_H){
            m_vel_x2 = 0;
        }
        if(key == Qt::Key_M){
            m_vel_y1 = 0;
        }
        if(key == Qt::Key_U){
            m_vel_y2 = 0;
        }

        return true;
    }

    return false;
}
