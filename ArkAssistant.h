//
// Created by bakashigure on 2019/10/15.
// Twitter @bakashigure
//

#ifndef ARKASSISTANT_H
#define ARKASSISTANT_H

#include "ui_ArkAssistant.h"
#include "AboutWindow.h"


#include <iostream>

#include <set>
#include <vector>
#include <map>


using namespace std;

class ArkAssistant : public QMainWindow
{
	Q_OBJECT

public:
	ArkAssistant(QWidget *parent = Q_NULLPTR);
	vector<string> juji, shushi, xianfeng, jingwei, zhongzhuang, yiliao, fuzhu,
		tezhong, nan, nv, jinzhanwei, yuanchenwei, shuchu, fanghu, shencun, zhiliao,
		feiyonghuifu, qungong, jiansu, zhiyuan, kuaisufuhuo, xueruo, weiyi, zhaohuan,
		kongchang, baofa, xinshou, zishenganyuan, gaojizishenganyuan, star3, star4, star2,
		star1, zhiyuanjixie;

	map<string, vector<string>> operatorMap; // 存放干员string和vector
	map<string, vector<string>>::iterator operatorMapIter;
	map<string, int> tagMap; //存放干员string和序号
	map<string, int>::iterator outputDataIter;
	void stylesheetInit(); //按钮样式表初始化
public slots:
	void init(); //初始化
	void selectCounterSwitch(QString &stri); //选择了几个tag
	vector<string>operatorJudge(QString& stri);//查表取得干员vector
	void operatorClassify(vector<string> c,int count); //干员按星级分类
	void selectCount1(int count); //每一个干员的词缀合成结果
	void selectCount2(int count); //每两个干员的词缀合成结果
	void selectCount3(int count); //每三个干员的词缀合成结果
	void about(); //关于
	void btnOperatorMatch();//词缀按钮匹配
	void btnClassify(); //挑选指定星级的干员
	void btnUnfinished();//暂时不起作用的按钮
	void outputData(); //输出
	void starBtnAllChecked(); //星级全选的按钮、
	void btnUncheckedAll();
private:
	QAction* openAction;
	Ui::ArkAssistantClass ui;
	AboutWindow* cw;
	
};


#endif //ARKASSISTANT_H