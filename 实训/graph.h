#pragma once
#ifndef _GRAPH_H_    
#define _GRAPH_H_  

#include <Windows.h>
#include <graphics.h>      // 引用图形库头文件
#include "booksystem.h"

//系统总入口，实现登陆，注册，分角色跳转页面
int Systemin(int cyScreen, int cxScreen,student &stu);

//扮演学生角色,传入屏幕尺寸
void playstudent(student stu,int cxScreen,int cyScreen);

//扮演管理员角色
void playadmin(int cxScreen, int cyScreen);


#endif     