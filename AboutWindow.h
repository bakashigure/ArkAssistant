//
// Created by bakashigure on 2019/10/15.
// Twitter @bakashigure
//

#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include "ui_AboutWindow.h"

class AboutWindow : public QMainWindow
{
	Q_OBJECT

public:
	AboutWindow(QWidget* parent = Q_NULLPTR);

private:
	Ui::AboutWindow ui;
};


#endif //ABOUTWINDOW_H

