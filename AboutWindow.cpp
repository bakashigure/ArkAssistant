//
// Created by bakashigure on 2019/10/15.
// Twitter @bakashigure
//

#include "AboutWindow.h"
#include <QGraphicsOpacityEffect>

AboutWindow::AboutWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle(QString::fromLocal8Bit("ºß ºß ºß °¡°¡°¡°¡°¡°¡°¡°¡°¡°¡"));
	QWidget* ddd = this->findChild<QWidget*>("backgroundifrit2");
	QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect;
	ddd->setGraphicsEffect(opacityEffect);
	opacityEffect->setOpacity(0.5);

	ui.label_2->setOpenExternalLinks(true);
	ui.label_5->setOpenExternalLinks(true);
	ui.label_6->setOpenExternalLinks(true);
	ui.label_7->setOpenExternalLinks(true);
	ui.label_9->setOpenExternalLinks(true);
}