#pragma once

#include <QPushButton>

class Coin  : public QPushButton
{
	Q_OBJECT

public:
	Coin(int orient);
	~Coin();
	int curOrient;
	bool isAnimation;
	void reverseCoin();
	//重写按下的事件
	void mousePressEvent(QMouseEvent* e);
};

