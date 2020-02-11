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

	map<string, vector<string>> operatorMap; // ��Ÿ�Աstring��vector
	map<string, vector<string>>::iterator operatorMapIter;
	map<string, int> tagMap; //��Ÿ�Աstring�����
	map<string, int>::iterator outputDataIter;
	void stylesheetInit(); //��ť��ʽ���ʼ��
public slots:
	void init(); //��ʼ��
	void selectCounterSwitch(QString &stri); //ѡ���˼���tag
	vector<string>operatorJudge(QString& stri);//���ȡ�ø�Աvector
	void operatorClassify(vector<string> c,int count); //��Ա���Ǽ�����
	void selectCount1(int count); //ÿһ����Ա�Ĵ�׺�ϳɽ��
	void selectCount2(int count); //ÿ������Ա�Ĵ�׺�ϳɽ��
	void selectCount3(int count); //ÿ������Ա�Ĵ�׺�ϳɽ��
	void about(); //����
	void btnOperatorMatch();//��׺��ťƥ��
	void btnClassify(); //��ѡָ���Ǽ��ĸ�Ա
	void btnUnfinished();//��ʱ�������õİ�ť
	void outputData(); //���
	void starBtnAllChecked(); //�Ǽ�ȫѡ�İ�ť��
	void btnUncheckedAll();
private:
	QAction* openAction;
	Ui::ArkAssistantClass ui;
	AboutWindow* cw;
	
};


#endif //ARKASSISTANT_H