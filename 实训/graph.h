#pragma once
#ifndef _GRAPH_H_    
#define _GRAPH_H_  

#include <Windows.h>
#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include "booksystem.h"

//ϵͳ����ڣ�ʵ�ֵ�½��ע�ᣬ�ֽ�ɫ��תҳ��
int Systemin(int cyScreen, int cxScreen,student &stu);

//����ѧ����ɫ,������Ļ�ߴ�
void playstudent(student stu,int cxScreen,int cyScreen);

//���ݹ���Ա��ɫ
void playadmin(int cxScreen, int cyScreen);


#endif     