#include "booksystem.h"
#include "Graph.h"
student *stu;          //ѧ��ָ��
book *bk;              //ͼ��ָ��
sendbook *sdbk;        //����ָ��  

int main()
{
	initgraph(640, 480);//�򿪴���
	HWND hwnd = GetHWnd();//��ȡ���ھ��
	int   cyScreen = GetSystemMetrics(SM_CYSCREEN);  // ��ʾ���߶�
	int   cxScreen = GetSystemMetrics(SM_CXSCREEN);  // ��ʾ�����
	initgraph(cxScreen, cyScreen);//��ȫ������
													 
//	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
//	SetWindowPos(hwnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CXSCREEN), SWP_SHOWWINDOW);
	int play;//��ɫ
	student stu;		//��¼��λѧ������ϵͳ
	while (1)
	{
		play = Systemin(cyScreen, cxScreen, stu);		//��½��ע��
		switch (play)
		{
		case 1:
			//����ѧ��ϵͳ
			playstudent(stu, cxScreen, cyScreen);
			break;
		case 2:
			//�����̨ϵͳ
			playadmin(cxScreen,cyScreen);
			break;
		defaut:
			break;
		}
	}
	closegraph();
	return 0;
}