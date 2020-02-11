//
// Created by bakashigure on 2019/10/15.
// Twitter @bakashigure
//

#include "ArkAssistant.h"
#include <QGraphicsOpacityEffect>


void ArkAssistant::stylesheetInit()
{
	QWidget* ddd = this->findChild<QWidget*>("backgroundifrit");
	QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect;
	ddd->setGraphicsEffect(opacityEffect);
	opacityEffect->setOpacity(0.3);


	QWidget* dddd = this->findChild<QWidget*>("list_stars_2");
	dddd->setStyleSheet(
		"QPushButton{"
		"background-color:rgb(100,100,100,1);"
		"border-style:solid;"                  
		"border-width:2.1px;"                  
		"border-radius:4px;"                   
		"border-color:rgba(140, 140, 140,1);" 
		"font:Microsoft YaHei;"
		"font:DemiBold,12px;"                       
		"color:rgba(255,255,255,1);"               
		"padding:6px;"
		"}"
		"QPushButton:checked{"
		"background-color:rgba(255,255,255,1);"
		"border-color:rgba(255,255,255,0);"
		"font:blod,12px;"                       
		"color:rgba(100,100,100,1);"
		"}"
	);

	setStyleSheet(
		"QPushButton{"
		"background-color:rgb(255,255,255,1);"
		"border-style:solid;"                  
		"border-width:2.1px;"                    
		"border-radius:4px;"                   
		"border-color:rgba(140, 140, 140,1);"    
		"font:Microsoft YaHei;"
		"font:DemiBold,12px;"         
		"color:rgba(0,0,0,1);"                
		"padding:6px;"                        
		"}"

		"QPushButton:checked{"
		"background-color:rgba(100,100,100,1);"
		"border-color:rgba(255,255,255,0);"
		"font:blod,12px;"                       
		"color:rgba(255,255,255,1);"
		"}"
	);


	ui.ALL->setStyleSheet(
		"QPushButton{"
		"background-color:rgb(255,255,255,1);"
		"border-style:solid;"                 
		"border-width:2.1px;"                     
		"border-radius:4px;"                   
		"border-color:rgba(140, 140, 140,1);"   
		"font:Microsoft YaHei;"
		"font:DemiBold,12px;"                    
		"color:rgba(0,0,0,1);"               
		"padding:6px;"                         
		"}"


		"QPushButton:pressed{"
		"background-color:rgba(100,100,100,1);"
		"border-color:rgba(255,255,255,0);"
		"font:blod,12px;"                      
		"color:rgba(255,255,255,1);"
		"}"

		"QPushButton:checked{"
		"background-color:rgb(255,255,255,1);"
		"border-style:solid;"                  
		"border-width:2.1px;"                    
		"border-radius:4px;"                  
		"border-color:rgba(140, 140, 140,1);"    
		"font:Microsoft YaHei;"
		"font:DemiBold,12px;"                     
		"color:rgba(0,0,0,1);"               
		"padding:6px;"
		"}"
	);


	ui.uncheckedbtn->setStyleSheet(
		"QPushButton{"
		"background-color:rgb(255,255,255,1);"
		"border-style:solid;"                  
		"border-width:2.1px;"                    
		"border-radius:4px;"                  
		"border-color:rgba(140, 140, 140,1);"   
		"font:Microsoft YaHei;"
		"font:DemiBold,12px;"                       
		"color:rgba(0,0,0,1);"              
		"padding:6px;"                         
		"}"
		"QPushButton:pressed{"
		"background-color:rgba(100,100,100,1);"
		"border-color:rgba(255,255,255,0);"
		"font:blod,12px;"                       
		"color:rgba(255,255,255,1);"
		"}"
		"QPushButton:checked{"
		"background-color:rgb(255,255,255,1);"
		"border-style:solid;"                 
		"border-width:2.1px;"                    
		"border-radius:4px;"                   
		"border-color:rgba(140, 140, 140,1);"  
		"font:Microsoft YaHei;"
		"font:DemiBold,12px;"                     
		"color:rgba(0,0,0,1);"              
		"padding:6px;"
		"}"
	);
}