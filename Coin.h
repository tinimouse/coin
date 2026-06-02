#include "Coin.h"
#include <QTimer>
Coin::Coin(int orient) {
	this->curOrient = orient;
	this->isAnimation = false;
	//1是正面，0是反面
	QPixmap pix;
	if (this->curOrient == 1) {
		pix.load(":/res/Coin0001.png");
	}
	else {
		pix.load(":/res/Coin0008.png");
	}
	//pix.scaled(pix.width() * 100, pix.height() * 100);
	this->setStyleSheet("QPushButton{border:Opx;}");
	this->setFixedSize(pix.width(), pix.height());
	this->setIcon(pix);
}

Coin::~Coin()
{}
void Coin::reverseCoin() {
	this->isAnimation = true;
	QTimer* timer = new QTimer(this);
	timer->setInterval(30);
	QPixmap pix[8];
	pix[0].load(":/res/Coin0001.png");
	pix[1].load(":/res/Coin0002.png");
	pix[2].load(":/res/Coin0003.png");
	pix[3].load(":/res/Coin0004.png");
	pix[4].load(":/res/Coin0005.png");
	pix[5].load(":/res/Coin0006.png");
	pix[6].load(":/res/Coin0007.png");
	pix[7].load(":/res/Coin0008.png");
	int *index;
	if (this->curOrient == 1) {
		index = new int(0);
		this->curOrient = 0;
		connect(timer, &QTimer::timeout, [=]()mutable {
			if ((*index) > 7) {
				timer->stop();
				timer->deleteLater();
				delete index;
				this->isAnimation = false;
				return;
			}
			this->setIcon(pix[(*index)]);
			(*index)++;
			});
	}
	else {
		index = new int(7);
		this->curOrient = 1;
		connect(timer, &QTimer::timeout, [=]() mutable{
			if ((*index) < 0) {
				timer->stop();
				timer->deleteLater();
				delete index;
				this->isAnimation = false;
				return;
			}
			this->setIcon(pix[(*index)]);
			(*index)--;
			});
	}
	timer->start();
}
void Coin::mousePressEvent(QMouseEvent* e) {
	if (this->isAnimation == true)return;
	else return QPushButton::mousePressEvent(e);
}

