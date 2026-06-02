#include "MainWidget.h"
#include <QPainter>
#include "MyPushButton.h"
#include <QDebug>
#include <QTimer>
#include <QSound>
MainWidget::MainWidget(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //配置主场景

    //设置固定大小
    this->setFixedSize(420, 788);

    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("翻金币");

    //菜单栏退出按钮
    connect(ui.actionExitGame, &QAction::triggered, [=]() {
        this->close();
        });



    //准备开始按钮音效
    QSound *startSound=new QSound(":/res/TapButtonSound.wav",this);
    //startSound->setLoops(-1);//设置循环-1即为无限循环播放
    //startSound->play();
    //设置背景音乐
    /*QSound* backgroundSound = new QSound(":/res/myDouDZ.wav", this);
    backgroundSound->setLoops(-1);
    backgroundSound->play();*/


    //设置开始按钮
    MyPushButton* startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);
    startBtn->show();


    //返回效果
    this->chooseScene = new chooseLevelScene;
    connect(this->chooseScene, &chooseLevelScene::chooseScenenBack, this, [=]() {
        this->setGeometry(chooseScene->geometry());
        this->show();
        chooseScene->hide();
        });

    //进入关卡选择界面
    connect(startBtn, &MyPushButton::clicked, [=]() {
        //做一个弹起的特效
        startSound->play();
        startBtn->zoom1();
        startBtn->zoom2();
        
        //延时进入到关卡中
        QTimer::singleShot(380, this, [=]() {
            //设置chooseScene的位置
            chooseScene->setGeometry(this->geometry());


            this->chooseScene->show();
            this->hide();
            });

        });

}

MainWidget::~MainWidget()
{}
void MainWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0,this->width(), this->height(), pix);


    //画背景上的图标
    pix.load(":/res/Title.png");

    //缩放图片
    pix.scaled(pix.width()*0.5, pix.height()*0.5);

    painter.drawPixmap(10,30,pix);
}

