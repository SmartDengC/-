#include "booksystem.h"
#include "Graph.h"
student *stu;          //学生指针
book *bk;              //图书指针
sendbook *sdbk;        //借阅指针  

int main()
{
	initgraph(640, 480);//打开窗口
	HWND hwnd = GetHWnd();//获取窗口句柄
	int   cyScreen = GetSystemMetrics(SM_CYSCREEN);  // 显示器高度
	int   cxScreen = GetSystemMetrics(SM_CXSCREEN);  // 显示器宽度
	initgraph(cxScreen, cyScreen);//打开全屏窗口
													 
//	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
//	SetWindowPos(hwnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CXSCREEN), SWP_SHOWWINDOW);
	int play;//角色
	student stu;		//记录那位学生进入系统
	while (1)
	{
		play = Systemin(cyScreen, cxScreen, stu);		//登陆与注册
		switch (play)
		{
		case 1:
			//进入学生系统
			playstudent(stu, cxScreen, cyScreen);
			break;
		case 2:
			//进入后台系统
			playadmin(cxScreen,cyScreen);
			break;
		defaut:
			break;
		}
	}
	closegraph();
	return 0;
}