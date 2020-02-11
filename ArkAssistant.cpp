//
// Created by bakashigure on 2019/10/15.
// Twitter @bakashigure
//


#include "ArkAssistant.h"


#include <qstring.h>
#include <QMessageBox>
#include <qtextbrowser.h>
#include <qtextedit.h>
#include <qplaintextedit.h>
#include <qlineedit.h>
#include <qpushbutton.h>


#include  <iostream>

#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <map>



using namespace std;

vector<vector<string>> tagSelected(6); //存放选中干员的vector
vector<string> tags2In1Vector[40]; //存放两个干员词缀的合成vector，供三次合成使用

int tagSelected_MAX = 6; //you can pick less than 6 tags 你最多只能选六个tag
int selectCounter = 0;   //选择了几个干员

// vector<string> tagSelected[6] = {}; //存放选中干员的vector


string operatorName[100][2]; //0存放选中干员的本地语言名称，1存放按钮ojbectname;
QString cache[200][7]; //存放输出结果
int count_a = 0; //这啥来着，忘了，不管了
int tags2In1Counter[60][3] = {}; //一个神秘的计数器



/*
/	cache[i][0]save tags
/	cache[i][1]save 6star agents
/	cache[i][2]save 5star agents
/	cache[i][3]save 4star agents
/	.........
/
*/

ArkAssistant::ArkAssistant(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//	cw = new AboutWindow(this);
	setWindowTitle(tr("Arknights Assistant | MadeBy:cat"));
	//LanguageSwitch de;
	

}

void ArkAssistant::btnUncheckedAll()
{
	QPushButton* btn;
	for (int i = 0; i < selectCounter; i++)
	{
		btn = this->findChild<QPushButton*>((operatorName[i][1]).data());
		/*
		  Debug Output
		 */
		//QMessageBox msg;
		//msg.setText(btn->objectName());
		//msg.exec();
		btn->setChecked(false);
	}


	for (int i = 0; i < 6; i++)
		tagSelected[i].clear();
	for (int i = 0; i < 40; i++)
		tags2In1Vector[i].clear();
	//tagSelected.erase(tagSelected.begin(), tagSelected.begin()+selectCounter);
	//tags2In1Vector.erase(tags2In1Vector.begin(), tags2In1Vector.end());
	//fill(tagSelected->begin(), tagSelected->begin()+selectCounter, );
	//fill(tags2In1Vector->begin(), tags2In1Vector->end(), NULL);
	fill(*cache, *1[&cache], "");
	count_a = 0;
	selectCounter = 0;

	//fill(*operatorName, *1[&operatorName], "");
	fill(operatorName[0], operatorName[0] + 100 * 2, "");
	fill(tags2In1Counter[0], tags2In1Counter[0] + 60 * 3, 0);
	tagMap.erase(tagMap.begin(), tagMap.end());
	outputData();




}


void ArkAssistant::btnOperatorMatch()
{
	if (selectCounter != 6)
	{
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				cache[i][j].clear();
			}
		}
	}

	QMessageBox msg;

	QString objectNameBtn = sender()->objectName();
	QPushButton* tempButton = this->findChild<QPushButton*>(objectNameBtn);

	string buttonname;
	buttonname = tempButton->objectName().toStdString();

	map<string, int>::iterator iit;


	if (tempButton->isChecked())
	{

		if (selectCounter == 6)
		{
			msg.setText(QString::fromLocal8Bit("最多只能选择六个词缀！"));
			msg.exec();
			tempButton->setChecked(false);
			return;
		}
		else { selectCounter++; };
	}

	else
	{

		selectCounter--;
		int deletet;
		iit = tagMap.find(buttonname);

		if (iit != tagMap.end())
		{

			deletet = iit->second;
			tagMap.erase(buttonname);
			tagSelected[deletet].clear();
			operatorName[deletet][0].clear();
			operatorName[deletet][1].clear();

		}
		else
		{
			//if bug, this will excute
			//msg.setText(tempButton->objectName());
			//msg.exec();
		}
	}

	//msg.setText(QString::number(selectCounter));
	//msg.exec();

	if (tempButton->isChecked())
	{
		for (int i = 0; i < selectCounter; i++)
		{
			if (tagSelected[i].empty())
			{
				QString textd;
				textd = tempButton->text();
				string testt;
				testt = textd.toLocal8Bit();

				operatorName[i][0] = testt;
				operatorName[i][1] = tempButton->objectName().toStdString();

				{
					pair<map<string, int>::iterator, bool> Pair_Exm;
					Pair_Exm = tagMap.insert(map<string, int>::value_type(buttonname, i));
					if (Pair_Exm.second == true)
					{
						//	msg.setText("insert success");
						//	msg.exec();
					}


				}

				tagSelected[i] = operatorJudge(objectNameBtn);
				sort(tagSelected[i].begin(), tagSelected[i].end());
				break;
			}
		}
	}


	//QString t;

	selectCounterSwitch(objectNameBtn);

	ui.textEdit->clear();

	//QString debug;
	//debug = QString("count_a").arg(count_a);
	//msg.setText(debug);
	//msg.exec();

	outputData();



}


void ArkAssistant::outputData()
{

	ui.textEdit->clear();
	QTextCursor cursor = ui.textEdit->textCursor();

	QTextCharFormat tagfmt;
	tagfmt.setBackground(QColor("#5D62BA")); //
	tagfmt.setForeground(QColor("#FFFFFF")); // gold color maybe

	QTextCharFormat star6fmt;
	star6fmt.setBackground(QColor("#C26E54")); //
	star6fmt.setForeground(QColor("#FFFFFF")); // white

	QTextCharFormat star5fmt;
	star5fmt.setBackground(QColor("#F2CF95")); //
	star5fmt.setForeground(QColor("#000000")); // gold color maybe

	QTextCharFormat star4fmt;
	star4fmt.setBackground(QColor("#6899AB"));
	star4fmt.setForeground(QColor("#FFFFFF"));
	
	QTextCharFormat star3fmt;
	star3fmt.setBackground(QColor("#8BBA65"));
	star3fmt.setForeground(QColor("#FFFFFF"));

	QTextCharFormat star2fmt;
	star2fmt.setBackground(QColor("#C9E2E4"));
	star2fmt.setForeground(QColor("#000000"));

	QTextCharFormat star1fmt;
	star1fmt.setBackground(QColor("#000000"));
	star1fmt.setForeground(QColor("#FFFFFF"));

	QTextCharFormat blank;
	blank.setBackground(QColor(255, 255, 255, 0));


	

	map<string, int>::iterator outputDataIter;


	for (int k = 40; k >= 0; k--)
	{

		if (!cache[k][0].isEmpty())
		{

			ui.textEdit->setCurrentCharFormat(tagfmt);
			ui.textEdit->append(cache[k][0]);
			ui.textEdit->insertPlainText("\n");
			//ui.textEdit->moveCursor(QTextCursor::PreviousRow);

			outputDataIter = tagMap.find("star6");
			if (outputDataIter == tagMap.end())
			{
				if ((!cache[k][1].isEmpty())&&(ui.gaojizishenganyuan->isChecked()))
				{
					
					ui.textEdit->moveCursor(QTextCursor::End);
					ui.textEdit->setCurrentCharFormat(star6fmt);
					ui.textEdit->insertPlainText(cache[k][1]);
				}
			}

			outputDataIter = tagMap.find("star5");
			if (outputDataIter == tagMap.end())
			{
				if (!cache[k][2].isEmpty()) {
					//ui.textEdit->setTextBackgroundColor("#FF00TTFF");
					//ui.textEdit->setTextColor(Qt::yellow);
					//ui.textEdit->moveCursor(QTextCursor::End);
					ui.textEdit->moveCursor(QTextCursor::End);
					ui.textEdit->setCurrentCharFormat(star5fmt);
					ui.textEdit->insertPlainText(cache[k][2]);
					//ui.textEdit->insertPlainText(cache[k][2]);
				}
			}

			outputDataIter = tagMap.find("star4");
			if (outputDataIter == tagMap.end()) {
				if (!cache[k][3].isEmpty())
				{
					//ui.textEdit->setTextBackgroundColor("#FF00TTFF");
					//ui.textEdit->setTextColor(Qt::gray);
					ui.textEdit->moveCursor(QTextCursor::End);
					//ui.textEdit->append(cache[k][3]);
					ui.textEdit->setCurrentCharFormat(star4fmt);
					ui.textEdit->insertPlainText(cache[k][3]);
				}
			}
			outputDataIter = tagMap.find("star3");
			if (outputDataIter == tagMap.end())
			{
				if (!cache[k][4].isEmpty()) {
					ui.textEdit->moveCursor(QTextCursor::End);
					//ui.textEdit->setTextBackgroundColor("#FF00TTFF");
					//ui.textEdit->setTextColor(Qt::white);
					ui.textEdit->setCurrentCharFormat(star3fmt);
					ui.textEdit->insertPlainText(cache[k][4]);
				}
			}

			outputDataIter = tagMap.find("star2");
			if (outputDataIter == tagMap.end())
			{
				if (!cache[k][5].isEmpty()) {
					ui.textEdit->moveCursor(QTextCursor::End);
					//ui.textEdit->setTextBackgroundColor("#FF00TTFF");
					//ui.textEdit->setTextColor(Qt::white);
					ui.textEdit->setCurrentCharFormat(star2fmt);
					ui.textEdit->insertPlainText(cache[k][5]);
				}
			}
			outputDataIter = tagMap.find("star1");
			if (outputDataIter == tagMap.end())
			{
				if (!cache[k][6].isEmpty()) {
					ui.textEdit->moveCursor(QTextCursor::End);
					//ui.textEdit->setTextBackgroundColor("#FF00TTFF");
					//ui.textEdit->setTextColor(Qt::white);
					ui.textEdit->setCurrentCharFormat(star1fmt);
					ui.textEdit->insertPlainText(cache[k][6]);
				}
			}
			ui.textEdit->append("\n");
			ui.textEdit->setTextInteractionFlags(Qt::NoTextInteraction);



		}
	}



	QTextCursor chazhao;
	QTextDocument* doc = ui.textEdit->document();
	QString searchtext = " ";
	QTextCursor searchCursor(doc);
	QTextCursor cursor1(doc);
	cursor1.beginEditBlock();

		searchCursor = doc->find(searchtext, searchCursor);
		while(!searchCursor.isNull() && !searchCursor.atEnd()) {
			//searchCursor.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor, 0);

			
			//ui.textEdit->setCurrentCharFormat(blank);
			searchCursor.mergeCharFormat(blank);
			searchCursor = doc->find(searchtext, searchCursor);
			
		}

	cursor1.endEditBlock();
	cursor1.movePosition(QTextCursor::Start);
	ui.textEdit->setTextCursor(cursor1);
	
}


void ArkAssistant::selectCount1(int count)
{
	QString s;
	string str;
	//for (int i = 0; i < count; i++) 
	for (int i = 0; i < 6; i++) //如果先选3个tag，再取消第二个选中的，就会出bug，不想麻烦改了，暴力解决。
	{
		if (!tagSelected[i].empty())
		{
			for (int j = 0; j < 200; j++)
			{
				if (cache[j][0].isEmpty())
				{
					cache[j][0] = QString::fromLocal8Bit(operatorName[i][0].data());
					operatorClassify(tagSelected[i], j);
					break;
				}
			}
			str.clear();
		}
	}


	/*
	QMessageBox box;
	if (count == 2)
	{
		box.setText(QString::fromLocal8Bit(operatorName[0][0].data()));
		box.exec();
		box.setText(QString::fromLocal8Bit(operatorName[1][0].data()));
		box.exec();
		box.setText(QString::fromLocal8Bit(operatorName[2][0].data()));
		box.exec();
	}
	*/
}

void ArkAssistant::selectCount2(int count)
{
	QString s;
	string str;
	vector<string> c;

	//for (int i = 0; i < count; i++) //同上
	for(int i=0;i<6;i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (!tagSelected[i].empty() && !tagSelected[j].empty())
			{
				set_intersection(tagSelected[j].begin(), tagSelected[j].end(), tagSelected[i].begin(), tagSelected[i].end(), back_inserter(c));
				if (c.empty())
				{
					continue;
				}
				else {
					set_intersection(tagSelected[j].begin(), tagSelected[j].end(), tagSelected[i].begin(), tagSelected[i].end(), back_inserter(tags2In1Vector[count_a]));
					tags2In1Counter[count_a][0] = i;
					tags2In1Counter[count_a][1] = j;
					sort(tags2In1Vector[count_a].begin(), tags2In1Vector[count_a].end());
					count_a++;
					for (int l = 0; l < 100; l++)
					{
						if (cache[l][0] == NULL)
						{
							operatorClassify(c, l);
							str = operatorName[i][0] + "+" + operatorName[j][0];
							cache[l][0] = QString::fromLocal8Bit(str.data());
							str.clear();
							break;
						}
					}
					c.clear();
				}
				str.clear();
				c.clear();
			}
		}

	}

	tags2In1Counter[0][2] = count_a;


}



void ArkAssistant::selectCount3(int count)
{
	QString s;
	string str;
	vector<string> c;

	for (int count_b = 0; count_b < tags2In1Counter[0][2]; count_b++)
	{
		for (int j = 0; (j < count) && (j != tags2In1Counter[count_b][0]) && (j != tags2In1Counter[count_b][1]); j++)
		{

			set_intersection(tags2In1Vector[count_b].begin(), tags2In1Vector[count_b].end(), tagSelected[j].begin(), tagSelected[j].end(), back_inserter(c));
			if (!c.empty())
			{
				/*
				  Debug Output
				/*
				/*
				string debug;
				debug = " count_b=" + to_string(count_b) + " j=" + to_string(j)
					+ " tags2In1Counter[count_b]=" + to_string(tags2In1Counter[count_b][0]) + " tags2In1Counter[count_b1]" + to_string(tags2In1Counter[count_b][1]);
				QMessageBox msg;
				msg.setText(QString::fromStdString(debug));
				msg.exec();
				*/


				for (int l = 0; l < 100; l++)
				{
					if (cache[l][0].isEmpty())
					{
						sort(c.begin(), c.end());
						operatorClassify(c, l);
						str = operatorName[tags2In1Counter[count_b][0]][0] + "+" + operatorName[tags2In1Counter[count_b][1]][0] + "+" + operatorName[j][0];
						cache[l][0] = QString::fromLocal8Bit(str.data());
						str.clear();
						c.clear();

						break;
					}
				}
			}
		}
	}
	//tags2In1Vector.erase(tags2In1Vector.begin(), tags2In1Vector.end());
	for (int i = 0; i < 40; i++)
		tags2In1Vector[i].clear();
}


void ArkAssistant::btnClassify()
{
	QString objectNameBtn = sender()->objectName();
	QPushButton* tempButton = this->findChild<QPushButton*>(objectNameBtn);

	if (!tempButton->isChecked())
	{
		tagMap.erase(objectNameBtn.toStdString());
	}
	else
	{
		tagMap.insert(map<string, int>::value_type(objectNameBtn.toStdString(), 114514));
	}
	outputData();
}

void ArkAssistant::starBtnAllChecked()
{

	ui.star1->setChecked(false);
	ui.star2->setChecked(false);
	ui.star3->setChecked(false);
	ui.star4->setChecked(false);
	ui.star5->setChecked(false);
	ui.star6->setChecked(false);

	tagMap.erase("star1");
	tagMap.erase("star2");
	tagMap.erase("star3");
	tagMap.erase("star4");
	tagMap.erase("star5");
	tagMap.erase("star6");
	outputData();
}




void ArkAssistant::operatorClassify(vector<string> c, int count)
{
	string str;
	vector<string> d;



	set_intersection(c.begin(), c.end(), gaojizishenganyuan.begin(), gaojizishenganyuan.end(), back_inserter(d));
	if (!d.empty())
	{
		for (string n : d)
			str = str + n + " ";
		cache[count][1] = QString::fromLocal8Bit(str.data());
	}
	d.clear();
	str.clear();

	set_intersection(c.begin(), c.end(), zishenganyuan.begin(), zishenganyuan.end(), back_inserter(d));
	if (!d.empty())
	{
		for (string n : d)
			str = str + n + " ";
		cache[count][2] = QString::fromLocal8Bit(str.data());

	}
	d.clear();
	str.clear();

	set_intersection(c.begin(), c.end(), star4.begin(), star4.end(), back_inserter(d));
	if (!d.empty())
	{
		for (string n : d)
			str = str + n + " ";
		cache[count][3] = QString::fromLocal8Bit(str.data());
	}
	d.clear();
	str.clear();

	set_intersection(c.begin(), c.end(), star3.begin(), star3.end(), back_inserter(d));
	if (!d.empty())
	{
		for (string n : d)
			str = str + n + " ";
		cache[count][4] = QString::fromLocal8Bit(str.data());
	}
	d.clear();
	str.clear();

	set_intersection(c.begin(), c.end(), star2.begin(), star2.end(), back_inserter(d));
	if (!d.empty())
	{
		for (string n : d)
			str = str + n + " ";
		cache[count][5] = QString::fromLocal8Bit(str.data());
	}
	d.clear();
	str.clear();

	set_intersection(c.begin(), c.end(), star1.begin(), star1.end(), back_inserter(d));
	if (!d.empty())
	{
		for (string n : d)
			str = str + n + " ";
		cache[count][6] = QString::fromLocal8Bit(str.data());
	}
	d.clear();
	str.clear();

}

void ArkAssistant::selectCounterSwitch(QString& stri)
{
	switch (selectCounter)
	{
	case(1):
		selectCount1(1);
		break;

	case(2):
		selectCount1(2);
		selectCount2(2);
		break;

	case(3):
		selectCount1(3);
		selectCount2(3);
		selectCount3(3);
		break;

	case(4):
		selectCount1(4);
		selectCount2(4);
		selectCount3(4);
		break;

	case(5):
		selectCount1(5);
		selectCount2(5);
		selectCount3(5);
		break;

	case(6):
		selectCount1(6);
		selectCount2(6);
		selectCount3(6);
		break;

	}
	//tags2In1Vector.erase(tags2In1Vector.begin(), tags2In1Vector.end());
	for (int i = 0; i < 40; i++)
		tags2In1Vector[i].clear();
	count_a = 0;

}


void ArkAssistant::init()
{

	cw = new AboutWindow(this);
	stylesheetInit();

	juji = { "普罗旺斯","蓝毒","守林人","陨星","白金","流星","白雪"
				,"杰西卡","克洛丝","安德切尔","巡林者","空爆","能天使" };

	shuchu = { "普罗旺斯","蓝毒","雷蛇","因陀罗","狮蝎","守林人","火神","真理","白金"
				,"崖心" ,"杜宾" ,"流星" ,"夜烟" ,"慕斯" ,"霜叶" ,"清道夫" ,"缠丸" ,"红豆"
				,"杰西卡" ,"克洛丝" ,"史都华德" ,"玫兰莎" ,"翎羽","安德切尔","夜魔","月见夜"
				,"猎蜂","推进之王","能天使", "银灰", "星熊","斯卡蒂" };

	xianfeng = { "德克萨斯","凛冬","清道夫","红豆","芬","香草","翎羽","夜刀" ,"推进之王"};

	jingwei = { "幽灵鲨","因陀罗", "杜宾", "艾丝黛尔", "慕斯", "霜叶", "缠丸","猎蜂" "玫兰莎","月见夜" "Castle-3", "银灰","斯卡蒂" };

	zhongzhuang = { "临光","雷蛇","火神","可颂","蛇屠箱","古米","角峰","米格鲁","黑角", "星熊", "塞雷娅" };

	yiliao = { "白面鸮","赫默", "华法琳", "末药", "调香师", "芙蓉", "安赛尔", "Lancet-2","闪灵","夜莺" };

	fuzhu = { "初雪","真理", "梅尔", "地灵", "梓兰" };

	tezhong = { "红","狮蝎", "崖心", "食铁兽", "暗索", "砾", "阿消" };

	nan = { "角峰","史都华德", "安赛尔", "安德切尔", "巡林者", "黑角", "12F", "Castle-3" }; //无用
	nv = { "幽灵鲨","凛冬", "白面鸮","德克萨斯", "蓝毒", "普罗旺斯", "临光", "雷蛇", "红",
			"赫默", "因陀罗", "初雪", "华法琳","守林人", "狮蝎", "火神", "真理", "白金", "陨星",
			"可颂", "梅尔", "崖心", "食铁兽", "杜宾", "流星","夜烟", "白雪", "远山", "末药", "蛇屠箱",
			"艾丝黛尔", "慕斯", "暗索", "砾", "地灵", "调香师", "霜叶","清道夫", "古米", "缠丸", "阿消",
			"红豆", "杰西卡", "芬", "克洛丝", "炎熔", "米格鲁", "芙蓉","香草", "玫兰莎", "梓兰",
			"翎羽", "杜林", "Lancet-2" }; //无用 x2

	jinzhanwei = { "幽灵鲨","凛冬", "德克萨斯", "临光", "雷蛇", "红", "因陀罗", "狮蝎", "火神", "可颂",
				"崖心", "食铁兽", "杜宾", "蛇屠箱", "艾丝黛尔", "慕斯", "暗索", "砾", "霜叶", "清道夫", "古米",
				"角峰", "缠丸", "阿消", "红豆", "芬", "米格鲁", "香草", "玫兰莎", "翎羽", "夜刀", "黑角",
				"Castle-3","猎蜂" ,"月见夜","推进之王" , "银灰", "星熊", "塞雷娅","斯卡蒂" };

	yuanchenwei = { "白面鸮","蓝毒", "普罗旺斯", "赫默", "初雪", "华法琳", "守林人", "真理", "白金", "陨星",
				"梅尔", "流星", "夜烟", "白雪", "远山", "末药", "地灵", "调香师", "杰西卡", "克洛丝", "炎熔",
				"芙蓉", "史都华德", "安赛尔", "梓兰", "安德切尔", "巡林者", "杜林", "12F", "Lancet-2","夜魔",
				"空爆","闪灵","夜莺","伊芙利特","能天使" };

	fanghu = { "临光","雷蛇", "火神", "可颂", "蛇屠箱", "砾", "古米", "角峰", "米格鲁", "星熊", "塞雷娅" };

	shencun = { "幽灵鲨", "因陀罗", "狮蝎", "火神", "艾丝黛尔", "缠丸", "杰西卡", "玫兰莎","斯卡蒂" };

	zhiliao = { "白面鸮","临光", "赫默", "华法琳", "末药", "调香师", "古米", "芙蓉", "安赛尔", "Lancet-2"
				,"夜魔","闪灵","夜莺", "塞雷娅" };

	feiyonghuifu = { "凛冬","德克萨斯", "清道夫", "红豆", "芬", "香草", "翎羽","推进之王" };

	qungong = { "幽灵鲨", "陨星", "白雪", "远山", "艾丝黛尔", "炎熔" ,"空爆","伊芙利特" };

	jiansu = { "真理","食铁兽", "白雪", "地灵", "霜叶", "梓兰" ,"夜魔" };

	zhiyuan = { "凛冬","白面鸮", "华法琳", "杜宾", "Castle-3" ,"闪灵","夜莺", "银灰", "塞雷娅" };

	kuaisufuhuo = { "红","砾" };

	xueruo = { "初雪","陨星", "流星", "夜烟" ,"伊芙利特" };

	weiyi = { "可颂","崖心", "食铁兽","暗索", "阿消" };

	zhaohuan = { "梅尔" };

	kongchang = { "德克萨斯","红", "梅尔" };

	baofa = { "守林人" };

	xinshou = { "夜刀","巡林者", "杜林", "黑角", "12F", };

	zishenganyuan = { "幽灵鲨","凛冬", "白面鸮", "德克萨斯", "蓝毒", "普罗旺斯", "临光", "雷蛇", "红", "赫默",
				"因陀罗", "初雪", "华法琳", "守林人", "狮蝎", "火神", "真理", "白金", "陨星", "可颂", "梅尔", "崖心", "食铁兽" ,"夜魔" };

	gaojizishenganyuan = { "推进之王","能天使", "星熊", "闪灵","伊芙利特", "银灰", "塞雷娅", "夜莺","斯卡蒂" };

	star1 = { "Lancet-2","Castle-3" };

	star2 = { "夜刀","黑角","巡林者","杜林","12F" };

	star3 = { "安德切尔","芬", "翎羽", "玫兰莎", "米格鲁", "克洛斯", "炎熔", "芙蓉", "安赛尔", "史都华德", "梓兰", "空爆","月见夜" };

	star4 = { "艾斯黛尔","夜烟", "远山", "杰西卡", "流星", "白雪", "清道夫", "红豆", "杜宾", "缠丸", "霜叶", "慕斯", "砾", "暗锁",
			"末药", "调香师", "角峰", "蛇屠箱", "古米", "地灵", "阿消", "猎蜂" };

	zhiyuanjixie = { "Lancet-2","Castle-3" };

	shushi = { "夜魔","夜烟", "远山", "炎熔", "史都华德", "杜林","12F" ,"伊芙利特" };


	operatorMap.insert(pair<string, vector<string>>("zhiyuanjixie", zhiyuanjixie));
	operatorMap.insert(pair<string, vector<string>>("shushi", shushi));
	operatorMap.insert(pair<string, vector<string>>("juji", juji));
	operatorMap.insert(pair<string, vector<string>>("star1", star1));
	operatorMap.insert(pair<string, vector<string>>("star2", star2));
	operatorMap.insert(pair<string, vector<string>>("star3", star3));
	operatorMap.insert(pair<string, vector<string>>("star4", star4));
	operatorMap.insert(pair<string, vector<string>>("shuchu", shuchu));
	operatorMap.insert(pair<string, vector<string>>("xianfeng", xianfeng));
	operatorMap.insert(pair<string, vector<string>>("jingwei", jingwei));
	operatorMap.insert(pair<string, vector<string>>("zhongzhuang", zhongzhuang));
	operatorMap.insert(pair<string, vector<string>>("yiliao", yiliao));
	operatorMap.insert(pair<string, vector<string>>("fuzhu", fuzhu));
	operatorMap.insert(pair<string, vector<string>>("tezhong", tezhong));
	operatorMap.insert(pair<string, vector<string>>("jinzhanwei", jinzhanwei));
	operatorMap.insert(pair<string, vector<string>>("yuanchenwei", yuanchenwei));
	operatorMap.insert(pair<string, vector<string>>("fanghu", fanghu));
	operatorMap.insert(pair<string, vector<string>>("shencun", shencun));
	operatorMap.insert(pair<string, vector<string>>("zhiliao", zhiliao));
	operatorMap.insert(pair<string, vector<string>>("feiyonghuifu", feiyonghuifu));
	operatorMap.insert(pair<string, vector<string>>("qungong", qungong));
	operatorMap.insert(pair<string, vector<string>>("jiansu", jiansu));
	operatorMap.insert(pair<string, vector<string>>("zhiyuan", zhiyuan));
	operatorMap.insert(pair<string, vector<string>>("kuaisufuhuo", kuaisufuhuo));
	operatorMap.insert(pair<string, vector<string>>("xueruo", xueruo));
	operatorMap.insert(pair<string, vector<string>>("weiyi", weiyi));
	operatorMap.insert(pair<string, vector<string>>("zhaohuan", zhaohuan));
	operatorMap.insert(pair<string, vector<string>>("kongchang", kongchang));
	operatorMap.insert(pair<string, vector<string>>("baofa", baofa));
	operatorMap.insert(pair<string, vector<string>>("xinshou", xinshou));
	operatorMap.insert(pair<string, vector<string>>("zishenganyuan", zishenganyuan));
	operatorMap.insert(pair<string, vector<string>>("gaojizishenganyuan", gaojizishenganyuan));


	sort(gaojizishenganyuan.begin(), gaojizishenganyuan.end());
	sort(zishenganyuan.begin(), zishenganyuan.end());
	sort(star1.begin(), star1.end());
	sort(star2.begin(), star2.end());
	sort(star3.begin(), star3.end());
	sort(star4.begin(), star4.end());

}

vector<string> ArkAssistant::operatorJudge(QString& stri)
{

	vector<string> operatorVector;
	operatorMapIter = operatorMap.find(stri.toStdString());
	operatorVector = operatorMapIter->second;
	sort(operatorVector.begin(), operatorVector.end());
	return operatorVector;
}

void ArkAssistant::btnUnfinished()
{
	QMessageBox msg;
	msg.setText(QString::fromLocal8Bit("这个按钮暂时不起作用"));
	msg.exec();
}

void ArkAssistant::about()
{
	cw->show();
}



