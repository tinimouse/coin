#pragma once
#include <QPushButton>
#include <QPropertyAnimation>
class MyPushButton : public QPushButton {
	Q_OBJECT
public:
	//MyPushButton(QPushButton* parent = nullptr);
	MyPushButton(QString normalImg, QString presImg = "");
	~MyPushButton();
	//参数1正常显示的图片路径
	QString normalImgPath;
	//参数2正常显示的图片路径
	QString pressImgPath;


	//弹跳的特效
	void zoom1();
	void zoom2();

    //重写按钮 按下和释放实践
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

};
/*
    void bounceAnimation()
    {
        // 第一步：向下弹
        QPropertyAnimation* anim1 = new QPropertyAnimation(this, "geometry", this);
        anim1->setDuration(300);
        anim1->setEasingCurve(QEasingCurve::OutBounce);
        anim1->setStartValue(this->geometry());
        anim1->setEndValue(this->geometry().translated(0, 15));

        // 第二步：回弹到原位置
        QPropertyAnimation* anim2 = new QPropertyAnimation(this, "geometry", this);
        anim2->setDuration(300);
        anim2->setEasingCurve(QEasingCurve::OutBounce);
        anim2->setStartValue(this->geometry().translated(0, 15));
        anim2->setEndValue(this->geometry());

        // 串联两个动画：anim1结束后启动anim2
        connect(anim1, &QPropertyAnimation::finished, this, [=]() {
            anim2->start(QPropertyAnimation::DeleteWhenStopped);
            });

        // 启动第一个动画（结束后自动释放）
        anim1->start(QPropertyAnimation::DeleteWhenStopped);
    }
*/
