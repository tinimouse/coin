#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "MyPushButton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QSound>
chooseLevelScene::chooseLevelScene(QWidget *parent)
	: QMainWindow(parent)
{
	this->setFixedSize(420, 788);
	this->setWindowIcon(QIcon(":/res/Coin0001.png"));
	this->setWindowTitle("选择关卡场景");




	//创建菜单栏
	QMenuBar* myMenuBar = menuBar();
	setMenuBar(myMenuBar);
	QMenu*startMenu=myMenuBar->addMenu("开始");
	QAction* quitAction=startMenu->addAction("退出");
	connect(quitAction, &QAction::triggered, [=]() {
		this->close();
		});


	//选择关卡的音效
	QSound* chooseSound = new QSound(":/res/TapButtonSound.wav",this);
	//返回音效
	QSound* backSound = new QSound(":/res/BackButtonSound.wav", this);

	//返回按钮
	MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
	backBtn->setParent(this);
	backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
	backBtn->show();
	//设置返回逻辑
	connect(backBtn, &MyPushButton::clicked, [=]() {
		backSound->play();
		QTimer::singleShot(300, this, [=]() {
			emit this->chooseScenenBack();
			});
		});




	for (int i = 0; i < 20; i++) {
		MyPushButton* menuBtn = new MyPushButton(":/res/LevelIcon.png");
		menuBtn->setParent(this);
		menuBtn->move(50+i%4*90,180+i/4*90);
		menuBtn->show();

		//监听每个按钮的点击事件
		connect(menuBtn, &MyPushButton::clicked, [=]() {
			//QString str = QString("您选择的是第 %1 关").arg(i+1);
			//qDebug() << str;
			menuBtn->zoom1();
			menuBtn->zoom2();
			chooseSound->play();
			this->coinGameBg = new CoinGameBg(i+1);
			QTimer::singleShot(380, this, [=]() {
				coinGameBg->move(this->x(), this->y());
				//coinGameBg->setGeometry(this->geometry());
				this->hide();
				this->coinGameBg->show();
				});
			connect(this->coinGameBg, &CoinGameBg::backPreScene, [=]() {
				this->setGeometry(coinGameBg->geometry());
				this->show();
				this->coinGameBg->hide();
				delete this->coinGameBg;
				});
			});



		QLabel* label = new QLabel;
		label->setParent(this);
		label->setFixedSize(menuBtn->width(),menuBtn->height());
		label->setText(QString::number(i+1));
		label->move(50 + i % 4 * 90, 180 + i / 4 * 90);
		label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		//设置让鼠标进行穿透
		label->setAttribute(Qt::WA_TransparentForMouseEvents);
	}
}

chooseLevelScene::~chooseLevelScene()
{}



void chooseLevelScene::paintEvent(QPaintEvent*) {
	//加载背景和图标
	QPainter painter(this);
	QPixmap pix;
	pix.load(":/res/OtherSceneBg.png");
	painter.drawPixmap(0,0,this->width(),this->height(),pix);
	pix.load(":/res/Title.png");
	painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}

