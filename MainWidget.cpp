#pragma once

#include <QMainWindow>
#include "Coin.h"
class CoinGameBg  : public QMainWindow
{
	Q_OBJECT

public:
	CoinGameBg(int index,QWidget *parent=nullptr);
	~CoinGameBg();
	int curIndex;
	void paintEvent(QPaintEvent*);
	Coin* allCoin[4][4] = { nullptr };
	int curAllCoinOrient[4][4];
	void judgeIsWin();
	bool isGameOver;
signals:
	void backPreScene();
	void gameOverSignals();
};

