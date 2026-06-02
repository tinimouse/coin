#include "CoinGameBg.h"
#include <QPainter>
#include "MyPushButton.h"
#include <QMenuBar>
#include <QTimer>
#include <QLabel>
#include <QColor>
#include "Coin.h"
#include "levelInitialCondition.h"
#include <QPropertyAnimation>
#include <QSound>
CoinGameBg::CoinGameBg(int index,QWidget *parent)
	: QMainWindow(parent)
{
	this->isGameOver = false;
	this->curIndex = index;
	this->setFixedSize(420,788);
	QString str = QString("第 %1 关").arg(this->curIndex);
	this->setWindowTitle(str);
	this->setWindowIcon(QIcon(":/res/Coin0001.png"));



	//创建菜单栏
	QMenuBar* myMenuBar = menuBar();
	setMenuBar(myMenuBar);
	QMenu* startMenu = myMenuBar->addMenu("开始");
	QAction* quitAction = startMenu->addAction("退出");
	connect(quitAction, &QAction::triggered, [=]() {
		this->close();
		});

	//返回按钮音效
	QSound* backSound = new QSound(":/res/BackButtonSound.wav", this);
	//翻金币的音效
	QSound* reverseCoinSound = new QSound(":/res/ConFlipSound.wav", this);
	//胜利音效
	QSound* winSound = new QSound(":/res/LevelWinSound.wav", this);



	//设置返回按钮
	MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
	backBtn->setParent(this);
	backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());
	backBtn->show();
	connect(backBtn, &QPushButton::clicked, [=]() {
		backSound->play();
		QTimer::singleShot(300, this, [=]() {
			emit this->backPreScene();
			});
		});




	//显示当前是第几关
	QLabel* label = new QLabel;
	label->setParent(this);
	//设置字体
	QFont font;
	font.setFamily("微软雅黑");
	font.setPointSize(20);
	label->setFont(font);
	label->setGeometry(QRect(0,this->height()-65,180,50));//x,y,w,h四个参数的对应关系
	label->setText(QString("LEVEL: %1").arg(this->curIndex));
	label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	label->show();




	//绘制coin的背景
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			QLabel* label = new QLabel;
			label->setGeometry(0, 0, 50, 50);
			label->setPixmap(QPixmap(":/res/BoardNode.png"));
			label->setParent(this);
			label->move(110 + i * 50, 250 + j * 50);
			label->show();
		}
	}





	//绘制coin
	//得到当前的状态
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->curAllCoinOrient[i][j] = levelInitialCondition[this->curIndex-1][i][j];
		}
	}
	//根据状态绘制硬币
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->allCoin[i][j] = new Coin(this->curAllCoinOrient[i][j]);
			this->allCoin[i][j]->setParent(this);
			this->allCoin[i][j]->move(112+j*50,253+i*50);
			this->allCoin[i][j]->show();
		}
	}

	//绑定点击
	int d[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			connect(this->allCoin[i][j], &Coin::clicked, [=]() {
				if (this->isGameOver)return;
				reverseCoinSound->play();
				this->allCoin[i][j]->reverseCoin();
				QTimer::singleShot(300, this, [=]() {
					for (int k = 0; k < 4; k++) {
						int newI = i + d[k][0];
						int newJ = j + d[k][1];
						if (newI >= 0 && newI < 4 && newJ >= 0 && newJ < 4) {
							//reverseCoinSound->play();
							this->allCoin[newI][newJ]->reverseCoin();
						}
					}
					this->judgeIsWin();
					});
				});
		}
	}

	//胜利图片结算
	QLabel* winLabel = new QLabel;
	QPixmap pix;
	pix.load(":/res/LevelCompletedDialogBg.png");
	winLabel->setParent(this);
	winLabel->setPixmap(pix);
	winLabel->setGeometry(this->width()/2-pix.width()/2, -pix.height(), pix.width(), pix.height());
	winLabel->show();
	connect(this, &CoinGameBg::gameOverSignals, [=]() {
		winSound->play();
		QPropertyAnimation* animation = new QPropertyAnimation(winLabel, "geometry");
		animation->setDuration(1000);
		animation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
		animation->setEndValue(QRect(winLabel->x(), winLabel->y() + 190, winLabel->width(), winLabel->height()));
		animation->setEasingCurve(QEasingCurve::OutBounce);
		animation->start();
		});
}

CoinGameBg::~CoinGameBg()
{}



void CoinGameBg::paintEvent(QPaintEvent*) {
	//第一步，创建对象并确定在那一个界面上画
	QPainter painter(this);
	//第二步，创建pixmap对象并加载对应的图片
	QPixmap pix;
	pix.load(":/res/PlayLevelSceneBg.png");
	//第三步，将图片渲染上去，注意参数
	painter.drawPixmap(0, 0, this->width(), this->height(),pix);
	pix.load(":/res/Title.png");
	painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);


}
void CoinGameBg::judgeIsWin() {
	bool flag = true;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->curAllCoinOrient[i][j] = this->allCoin[i][j]->curOrient;
			if (this->curAllCoinOrient[i][j] == 0) {
				flag = false;
				break;
			}
		}
	}
	if (flag) {
		this->isGameOver = true;
		emit this->gameOverSignals();
	}
}

