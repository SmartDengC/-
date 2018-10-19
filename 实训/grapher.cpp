//所有的图形框架函数写在这里买呢

#include "booksystem.h"
#include "Graph.h"

//系统总入口，实现登陆，注册，分角色跳转页面
int  Systemin(int cyScreen, int cxScreen,student &stu)
{
	cleardevice();
	//标题设置
	LOGFONT changestyle, origin;
	gettextstyle(&changestyle);
	origin = changestyle;
	changestyle.lfHeight = 120;
	changestyle.lfWidth = 80;
	changestyle.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&changestyle);
	//文字输出
	RECT titletext = { 0, 0, cxScreen, 200 };
	drawtext(_T("图书管理系统"), &titletext, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(&origin);
	//层叠图案
	fillrectangle(1400, 200, 1800, 600);
	int i = 0;
	for (; i < 50; i++)
	{
		setfillcolor(RGB(i * 10, i * 10, i * 10));
		setlinecolor(RGB(i * 10, i * 10, i * 10));
		fillrectangle(1400 - i * 10, 200 + i * 10, 1800 - i * 10, 600 + i * 10);
	}
	//处理鼠标消息
	MOUSEMSG msg;
	while(1)
	{
		// 创建一个矩形区域
		HRGN rgn = CreateRectRgn(200, 300, 700, 800);		// 将该矩形区域设置为裁剪区
		
		setcliprgn(rgn);
		BeginBatchDraw();
		//登陆面板，连接数据库验证登陆
		setfillcolor(RGB(128, 128, 128));
		setlinecolor(RGB(128, 128, 128));
		fillrectangle(200, 300, 700, 800);
		setfillcolor(RGB(0, 0, 0));
		setlinecolor(RGB(0, 0, 0));
		fillrectangle(250, 350, 650, 400);
		//系统登陆文字显示
		gettextstyle(&changestyle);
		changestyle.lfHeight = 50;
		changestyle.lfWidth = 40;
		changestyle.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&changestyle);
		RECT logintext = { 250, 350, 650, 400 };
		drawtext(_T("系统登录"), &logintext, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		settextstyle(&origin);
		//登陆 注册 退出 文字显示
		gettextstyle(&changestyle);
		changestyle.lfHeight = 40;
		changestyle.lfWidth = 20;
		changestyle.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&changestyle);
		//登陆按钮
		RECT loginbuton = { 700, 750, 200, 200 };
		drawtext(_T("登录"), &loginbuton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		////注册按钮
		RECT  registerbuton = { 700 ,950, 200, 200 };
		drawtext(_T("注册"), &registerbuton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//退出程序
		RECT  quitbuton = { 700 ,1150, 200, 200 };
		drawtext(_T("退出"), &quitbuton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		FlushBatchDraw();
		EndBatchDraw();
		//处理鼠标消息
		while (MouseHit())
		{
			msg=GetMouseMsg();
			//选中登陆按钮 写好了
			if (msg.x >= 400 && msg.x <= 500 && msg.y >= 450 && msg.y <= 500)
			{
				
				setlinecolor(RGB(255, 0, 0));
				for (int i = 0; i<5; i++)
					rectangle(400 + i, 450 + i, 500 - i, 500 - i);
				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					int key = -1;
					key=loginCode(stu);
					if (key == 1)
						return key;
					if (key == 2)
						return key;
				}
			}
			//选中注册按钮 
			if (msg.x >= 400 && msg.x <= 500 && msg.y >= 550 && msg.y <= 600)
			{
				
				setlinecolor(RGB(255, 0, 0));
				for (int i = 0; i<5; i++)
					rectangle(400+i, 550+i, 500-i, 600-i);
				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					//注册成功
					if (registerCode(stu) == 1)
					{
						return 1;
					}
					else
					{
						;
					}
				}
			}

			//选中退出程序 写好了
			if (msg.x >= 400 && msg.x <= 500 && msg.y >= 650&& msg.y <= 700)
			{
				
				setlinecolor(RGB(255, 0, 0));
				for (int i = 0; i<5; i++)
					rectangle(400+i, 650+i, 500-i, 700-i);
				if (msg.uMsg == WM_LBUTTONDOWN)
					exit(0);
			}
		}
		Sleep(100);
	}

	//setfillcolor(RGB(0, 0, 0));
	//setlinecolor(RGB(0, 0, 0));
	//fillrectangle(750, 350, 650, 900);


	getch();
	return -1;
}

//实现扮演学生角色
void playstudent(student stu ,int cxScreen,int  cyScreen)
{

	book *bk;              //图书指针

	sendbook *sdbk;        //借阅指针  

	bk = (book*)malloc(sizeof(book));
	bk->next = NULL;
	sdbk = (sendbook*)malloc(sizeof(sendbook));
	sdbk->next = NULL;

	setcliprgn(NULL);	//取消剪裁区
	cleardevice();

	//显示静态内容
	//标题设置
	LOGFONT changestyle, origin;	
	gettextstyle(&changestyle);
	origin = changestyle;
	changestyle.lfHeight = 120;
	changestyle.lfWidth = 80;
	changestyle.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&changestyle);
	//文字输出
	RECT titletext = { 0, 0, cxScreen, 200 };
	drawtext(_T("欢迎使用图书管理系统"), &titletext, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(&origin);
	COLORREF oldfillcolor=getfillcolor();
	COLORREF oldlinecolor= getlinecolor();

	//显示层叠样式//51+13
	int color_a =1;
	int b = 5;
	int coordinate1[4] = {160,180,cxScreen-160 ,950 };//起始坐标
	for (int i = 1; i < 20; i++)
	{
		color_a += i;
		coordinate1[0] +=b;
		coordinate1[1] +=b;
		coordinate1[2] -=b;
		coordinate1[3] -=b;
		setfillcolor(RGB(color_a, color_a, color_a));
		setlinecolor(RGB(color_a, color_a, color_a));
		fillrectangle(coordinate1[0], coordinate1[1], coordinate1[2], coordinate1[3]);
	}

	//规划数据显示区域
	int coordinate2[4]={ coordinate1[0]+20,coordinate1[1]+20,coordinate1[2]-600 ,coordinate1[3]-20 };
	
	setlinecolor(RGB(100, 100, 100));
	rectangle(coordinate2[0], coordinate2[1], coordinate2[2], coordinate2[3]);


	//规划绘制动态总区域
	coordinate1[0] += 1000;
	coordinate1[1] += 20;
	coordinate1[2] -= 20;
	coordinate1[3] -=20;
	
	//第一方块
	int coordinate3[4] = { coordinate1[0] ,coordinate1[1] ,coordinate1[2] ,coordinate1[3] - 450 };
	//第二个方块
	int coordinate4[4] = { coordinate1[0] ,coordinate3[3] ,coordinate1[2] ,coordinate3[3]+150 };
	//第三个方块
	int coordinate5[4] = { coordinate1[0] ,coordinate4[3] ,coordinate1[2] ,coordinate4[3]+200 };
	//第四个方块
	int coordinate6[4] = { coordinate1[0] ,coordinate5[3] ,coordinate1[2] ,coordinate1[3]  };
	
	while (1)
	{
		//鼠标检测区
		BeginBatchDraw();
		setlinecolor(RGB(color_a, color_a, color_a));
		fillrectangle(coordinate1[0], coordinate1[1], coordinate1[2], coordinate1[3]);
		setlinecolor(RGB(100, 100, 100));
		rectangle(coordinate1[0], coordinate1[1], coordinate1[2], coordinate1[3]);	//总区域

		//字体修改1																																				  
		LOGFONT changestyle, origin,temp;
		gettextstyle(&changestyle);
		origin = changestyle;
		changestyle.lfHeight = 50;
		changestyle.lfWidth = 20;
		changestyle.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&changestyle);

		//第一方块
		rectangle(coordinate3[0], coordinate3[1], coordinate3[2], coordinate3[3]);
		RECT boxtext1 = { coordinate3[0], coordinate3[1], coordinate3[2], coordinate3[3] };
		char welcome[50];
		sprintf(welcome, "欢迎您，%s同学!", stu.name);
		drawtext(welcome, &boxtext1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


		//字体修改2
		changestyle.lfHeight = 30;
		changestyle.lfWidth = 15;
		changestyle.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&changestyle);

		//第二个方块
		rectangle(coordinate4[0], coordinate4[1], coordinate4[2], coordinate4[3]);
		RECT boxtext2_1 = { coordinate4[0], coordinate4[1]+10, coordinate4[2], coordinate4[3]-80 };
		drawtext(_T("用户信息查询"), &boxtext2_1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		RECT boxtext2_2= { coordinate4[0], coordinate4[1] + 50, coordinate4[2], coordinate4[3]  };
		drawtext(_T("用户信息修改"), &boxtext2_2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		//第三个方块
		rectangle(coordinate5[0], coordinate5[1], coordinate5[2], coordinate5[3]);
		RECT boxtext3_1 = { coordinate5[0], coordinate5[1] , coordinate5[2], coordinate5[3]-120 };
		drawtext(_T("图书信息查询"), &boxtext3_1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		RECT boxtext3_2 = { coordinate5[0], coordinate5[1]+80 , coordinate5[2], coordinate5[3]-80 };
		drawtext(_T("图书借阅"), &boxtext3_2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		RECT boxtext3_3 = { coordinate5[0], coordinate5[1] + 120 , coordinate5[2], coordinate5[3] };
		drawtext(_T("图书归还"), &boxtext3_3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		//第四个方块
		//字体修改3
		changestyle.lfHeight = 50;
		changestyle.lfWidth = 20;
		changestyle.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&changestyle);

		rectangle(coordinate6[0], coordinate6[1], coordinate6[2], coordinate6[3]);
		RECT boxtext4 = { coordinate6[0], coordinate6[1] , coordinate6[2], coordinate6[3] };
		drawtext(_T("退出"), &boxtext4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//outtextxy(coordinate6[0], coordinate6[1], L"4");
		//outtextxy(coordinate6[2], coordinate6[1], L"4");
		//outtextxy(coordinate6[0], coordinate6[3], L"4");
		//outtextxy(coordinate6[2], coordinate6[3], L"4");
		FlushBatchDraw();
		EndBatchDraw();

		//处理鼠标消息
		MOUSEMSG msg;
		HWND hWnd = GetHWnd();
		while (MouseHit())
		{
			msg = GetMouseMsg();
			//选中用户信息查询	已经实现
			if (msg.x >= coordinate4[0] + 100 && msg.x <= coordinate4[2] - 100 && msg.y >= coordinate4[1] + 20 && msg.y <= coordinate4[3] - 90)
			{
				setlinecolor(RGB(255, 0, 0));
				for (int i = 0; i<5; i++)
					rectangle(coordinate4[0]+100 + i, coordinate4[1]+20 + i, coordinate4[2]-100- i, coordinate4[3]-90 - i);
				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					//MessageBox(hWnd, "选中用户信息查询", "图书管理系统", MB_OK);	
					//重置数据区屏幕
					setfillcolor(RGB(color_a, color_a, color_a));
					setlinecolor(RGB(color_a, color_a, color_a));
					fillrectangle(coordinate2[0], coordinate2[1], coordinate2[2], coordinate2[3]);
					setlinecolor(RGB(100, 100, 100));
					rectangle(coordinate2[0], coordinate2[1], coordinate2[2], coordinate2[3]);
					//设置字体
					gettextstyle(&temp);
					changestyle.lfHeight = 25;
					changestyle.lfWidth =18;
					changestyle.lfQuality = ANTIALIASED_QUALITY;
					settextstyle(&changestyle); 
					//数据输出
					int y = coordinate2[1]+40;
					RECT r = { coordinate2[0]+10, coordinate2[1] +10,coordinate2[2] ,coordinate2[3]+10 };
					drawtext(_T("学号        姓名        密码        性别"), &r, DT_INTERNAL | DT_LEFT);
					r.top = y;
					char b[100];
					sprintf(b, "%-12d%-12s%-12d%-12s", stu.StuId, stu.name, stu.password, stu.sex);
					drawtext(b, &r, DT_INTERNAL | DT_LEFT);
					r.top += 40;
					drawtext(_T("                                         借阅信息                                     "), &r, DT_INTERNAL | DT_LEFT);
					book *bk2 = (book*)malloc(sizeof(book));
					SelectBroBook(bk2, stu);
					r.top += 40;
					drawtext(_T("书号        类型        书名        数量"), &r, DT_INTERNAL | DT_LEFT);
					for (int i = 0; i < 10 && bk2->next != NULL; i++)
					{
						sprintf(b, "%-12d%-12s%-12s%-12d", bk2->bookId, bk2->bookType, bk2->bookName, bk2->booknum);
						r.top += 40;
						drawtext(b, &r, DT_INTERNAL | DT_LEFT);						
						bk2 = bk2->next;
					}
					settextstyle(&temp);//恢复字体
				}
			}
			
			//选中用户信息修改 已经实现
			if (msg.x >= coordinate4[0] + 100 && msg.x <= coordinate4[2] - 100 && msg.y >= coordinate4[1] + 80 && msg.y <= coordinate4[3] - 30)
			{

				setlinecolor(RGB(255, 0, 0));
				for (int i = 0; i<5; i++)
					rectangle(coordinate4[0]+100 + i, coordinate4[1]+80 + i, coordinate4[2]-100 - i, coordinate4[3]-30 - i);
				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					//MessageBox(hWnd, "选中用户信息修改", "图书管理系统", MB_OK);
					//重置数据区屏幕
					setfillcolor(RGB(color_a, color_a, color_a));
					setlinecolor(RGB(color_a, color_a, color_a));
					fillrectangle(coordinate2[0], coordinate2[1], coordinate2[2], coordinate2[3]);
					setlinecolor(RGB(100, 100, 100));
					rectangle(coordinate2[0], coordinate2[1], coordinate2[2], coordinate2[3]);
					//设置字体
					gettextstyle(&temp);
					changestyle.lfHeight = 23;
					changestyle.lfWidth = 18;
					changestyle.lfQuality = ANTIALIASED_QUALITY;
					settextstyle(&changestyle);
					//写入数据
					if (ModiStudentinfor(&stu))
					{
						MessageBox(hWnd, "修改成功", "图书管理系统", MB_OK);
					}
					else
					{
						MessageBox(hWnd, "修改失败", "图书管理系统", MB_OK);
					}


					settextstyle(&temp);//恢复字体
				}
			}

			//选中图书信息查询 已经实现
			if (msg.x >= coordinate5[0] + 100 && msg.x <= coordinate5[2] - 100 && msg.y >= coordinate5[1] + 20 && msg.y <= coordinate5[3] - 140)
			{
				setlinecolor(RGB(255, 0, 0));
				for (int i = 0; i<5; i++)
					rectangle(coordinate5[0]+100 + i, coordinate5[1]+20 + i, coordinate5[2]-100 - i, coordinate5[3]-140 - i);
				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					//MessageBox(hWnd, "选中图书信息查询", "图书管理系统", MB_OK);
					//重置数据区屏幕
					setfillcolor(RGB(color_a, color_a, color_a));
					setlinecolor(RGB(color_a, color_a, color_a));
					fillrectangle(coordinate2[0], coordinate2[1], coordinate2[2], coordinate2[3]);
					setlinecolor(RGB(100, 100, 100));
					rectangle(coordinate2[0], coordinate2[1], coordinate2[2], coordinate2[3]);
					//设置字体
					gettextstyle(&temp);
					changestyle.lfHeight = 25;
					changestyle.lfWidth = 18;
					changestyle.lfQuality = ANTIALIASED_QUALITY;
					settextstyle(&changestyle);
					//写入数据
					
					bk->next = NULL;
					SelectBookinfor(bk);
					//显示列名
					int y = coordinate2[1] + 40;
					RECT r = { coordinate2[0] + 10, coordinate2[1] + 10,coordinate2[2] ,coordinate2[3] + 10 };
					drawtext(_T("书号        类型        书名        库存"), &r, DT_INTERNAL | DT_LEFT);
					char b[100];
					for (int i = 0; i < 10 && bk->next!= NULL; i++)
					{
						sprintf(b, "%-12d%-12s%-12s%-12d", bk->bookId, bk->bookType, bk->bookName, bk->booknum);
						r.top = y;
						drawtext(b, &r, DT_INTERNAL | DT_LEFT);
						y += 25;
						bk = bk->next;
					}
					/*char a[] = "我的世界我的世界我的世界我的世界\n";
					char b[10][100];
					for (int i = 0; i < 10; i++)
					{
					strcpy(b[i], a);
					}
					for (int i = 0; i < 10; i++)
					{
					r.top = y;
					drawtext(b[i], &r, DT_INTERNAL | DT_LEFT);
					y += 25;
					}*/
					settextstyle(&temp);//恢复字体
				}
			}

			//选中图书借阅 已经实现
			if (msg.x >= coordinate5[0] + 130 && msg.x <= coordinate5[2] - 130 && msg.y >= coordinate5[1] + 80 && msg.y <= coordinate5[3] - 80)
			{
				setlinecolor(RGB(255, 0, 0));
				for (int i = 0; i<5; i++)
					rectangle(coordinate5[0] + 130 + i, coordinate5[1] + 80 + i, coordinate5[2] - 130 - i, coordinate5[3] - 80 - i);
				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					//MessageBox(hWnd, "选中图书借阅", "图书管理系统", MB_OK);
					////重置数据区屏幕
					//setfillcolor(RGB(color_a, color_a, color_a));
					//setlinecolor(RGB(color_a, color_a, color_a));
					//fillrectangle(coordinate2[0], coordinate2[1], coordinate2[2], coordinate2[3]);
					//setlinecolor(RGB(100, 100, 100));
					//rectangle(coordinate2[0], coordinate2[1], coordinate2[2], coordinate2[3]);
					////设置字体
					//gettextstyle(&temp);
					//changestyle.lfHeight = 23;
					//changestyle.lfWidth = 18;
					//changestyle.lfQuality = ANTIALIASED_QUALITY;
					//settextstyle(&changestyle);
					//写入数据
					
					if (BroBook(stu, sdbk))
					{
						MessageBox(hWnd, "借阅成功！", "图书管理系统", MB_OK);
					}
					else
					{
						MessageBox(hWnd, "借阅失败！", "图书管理系统", MB_OK);
					}
					//settextstyle(&temp);//恢复字体
				}
			}

			//选中图书归还 已经实现
			if (msg.x >= coordinate5[0] + 130 && msg.x <= coordinate5[2] - 130 && msg.y >= coordinate5[1] + 140 && msg.y <= coordinate5[3] - 20)
			{
				setlinecolor(RGB(255, 0, 0));
				for (int i = 0; i<5; i++)
					rectangle(coordinate5[0] + 130 + i, coordinate5[1] + 140+ i, coordinate5[2] - 130 - i, coordinate5[3] - 20 - i);
				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					//MessageBox(hWnd, "选中图书归还", "图书管理系统", MB_OK);
					////重置数据区屏幕
					//setfillcolor(RGB(color_a, color_a, color_a));
					//setlinecolor(RGB(color_a, color_a, color_a));
					//fillrectangle(coordinate2[0], coordinate2[1], coordinate2[2], coordinate2[3]);
					//setlinecolor(RGB(100, 100, 100));
					//rectangle(coordinate2[0], coordinate2[1], coordinate2[2], coordinate2[3]);
					////设置字体
					//gettextstyle(&temp);
					//changestyle.lfHeight = 23;
					//changestyle.lfWidth = 18;
					//changestyle.lfQuality = ANTIALIASED_QUALITY;
					//settextstyle(&changestyle);
					//写入数据

					if (ReturnBook(sdbk, bk, &stu))
					{
						MessageBox(hWnd, "归还成功！", "图书管理系统", MB_OK);
					}
					else
					{
						MessageBox(hWnd, "归还失败！", "图书管理系统", MB_OK);
					}

					//settextstyle(&temp);//恢复字体
				}
			}

			//选中退出 已经实现
			if (msg.x >= coordinate6[0] && msg.x <= coordinate6[2]  && msg.y >= coordinate6[1]  && msg.y <= coordinate6[3])
			{
				setlinecolor(RGB(255, 0, 0));
				for (int i = 0; i<5; i++)
					rectangle(coordinate6[0] + 150 + i, coordinate6[1] +21 + i, coordinate6[2] - 150 - i, coordinate6[3] - 21 - i);
				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					rectangle(coordinate2[0], coordinate2[1], coordinate2[2], coordinate2[3]);
					//MessageBox(hWnd, "选中退出", "图书管理系统", MB_OK);
					return;
				}
			}

		}
		Sleep(100);
	}

	getch();
	settextstyle(&origin);//字体还原
	setfillcolor(oldfillcolor);//填充色还原
	setlinecolor(oldlinecolor);//线条颜色还原
	return ;
}

//扮演管理员角色
void playadmin(int cxScreen, int cyScreen)
{
	setcliprgn(NULL);//取消剪裁区
	cleardevice();
	

	//显示静态内容
	//标题设置
	LOGFONT changestyle, origin;
	gettextstyle(&changestyle);
	origin = changestyle;
	changestyle.lfHeight = 120;
	changestyle.lfWidth = 80;
	changestyle.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&changestyle);
	//文字输出
	RECT titletext = { 0, 0, cxScreen, 200 };
	drawtext(_T("欢迎使用图书管理系统"), &titletext, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(&origin);
	COLORREF oldfillcolor = getfillcolor();
	COLORREF oldlinecolor = getlinecolor();
	int a = 10;
	int b = 5;
	//显示层叠样式//51+13
	for (int i = 0; i < 20; i++)
	{
		setfillcolor(RGB(0 + a * i, 0 + a * i, 0 + a * i));
		setlinecolor(RGB(0 + a * i, 0 + a * i, 0 + a * i));
		fillrectangle(160 + i * b, 180 + i * b, cxScreen - 160 - i * b, 950 - i * b);
	}

	while (1) {
		BeginBatchDraw();

		//汉字
		//提示汉字
		TCHAR COME[] = _T("			欢迎进入    ");
		//图书管理文字
		char BOOK[15][20] = { _T("			图书管理"),_T("图书增加"),_T("图书信息修改"),_T("图书删除"),_T("用户借阅查询") };
		//用户管理文字
		char USER[15][20] = { _T("			用户管理"),_T("用户查询"),_T("用户删除") };
		TCHAR EXIT[] = _T("	欢迎退出    ");
		//设置字体的样式
		LOGFONT f;
		gettextstyle(&f);                     // 获取当前字体设置
		f.lfHeight = 48;                      // 设置字体高度为 
		settextstyle(&f);                     // 设置字体样式
		outtextxy(1000, 280, COME);
		outtextxy(1000, 355, BOOK[0]);
		f.lfHeight = 35;                      // 设置字体高度为 
		settextstyle(&f);                     // 设置字体样式
		outtextxy(1000, 430, BOOK[1]);
		outtextxy(1000, 480, BOOK[2]);
		outtextxy(1000, 530, BOOK[3]);
		outtextxy(1000, 580, BOOK[4]);
		f.lfHeight = 48;                      // 设置字体高度为 
		settextstyle(&f);                     // 设置字体样式
		outtextxy(1000, 630, USER[0]);
		f.lfHeight = 35;                      // 设置字体高度为 
		settextstyle(&f);
		outtextxy(1000, 705, USER[1]);
		outtextxy(1000, 765, USER[2]);
		f.lfHeight = 48;                      // 设置字体高度为 
		settextstyle(&f);                     // 设置字体样式
		outtextxy(1000, 805, EXIT);
		setlinecolor(RGB(90, 90, 90));
		for (int i = 0; i < 5; i++) {
			//竖线
			line(1000 + i, 280 + i, 1000 - i, 855 - i);//左
			line(1280 + i, 280 + i, 1280 - i, 855 - i);//右
													   //横线
			line(1000 + i, 280 + i, 1280 - i, 280 - i);//1
			line(1000 + i, 355 + i, 1280 - i, 355 - i);//2
			line(1000 + i, 430 + i, 1280 - i, 430 - i);//3
			line(1000 + i, 480 + i, 1280 - i, 480 - i);//4
			line(1000 + i, 530 + i, 1280 - i, 530 - i);//5
			line(1000 + i, 580 + i, 1280 - i, 580 - i);//6
			line(1000 + i, 630 + i, 1280 - i, 630 - i);//7
			line(1000 + i, 705 + i, 1280 - i, 705 - i);//8
			line(1000 + i, 755 + i, 1280 - i, 755 - i);//9
			line(1000 + i, 805 + i, 1280 - i, 805 - i);//10
			line(1000 + i, 855 + i, 1280 - i, 855 - i);//11
		}
		FlushBatchDraw();
		EndBatchDraw();
		//处理鼠标消息
		MOUSEMSG msg;
		HWND hWnd = GetHWnd();
		while (MouseHit()) {
			book *bk = (book *)malloc(sizeof(book));
			struct Student *stu = (student *)malloc(sizeof(student));
			sendbook *sdbk = (sendbook*)malloc(sizeof(sendbook));
			msg = GetMouseMsg();
			//选中图书增加按钮 写好了
			if (msg.x >= 1000 && msg.x <= 1280 && msg.y >= 430 && msg.y <= 480) {
				setlinecolor(RGB(0, 255, 255));
				for (int i = 0; i<5; i++)
					rectangle(1000 + i, 430 + i, 1280 - i, 480 - i);
				if (msg.uMsg == WM_LBUTTONDOWN) {
					//MessageBox(hWnd, "图书增加按钮", "提示框", MB_OK);
					book *bk = (book *)malloc(sizeof(book));
					AddBookinfor(bk);
				}
			}
			//图书信息修改按钮 
			if (msg.x >= 1000 && msg.x <= 1280 && msg.y >= 480 && msg.y <= 530) {
				setlinecolor(RGB(0, 255, 255));
				for (int i = 0; i<5; i++)
					rectangle(1000 + i, 480 + i, 1280 - i, 530 - i);
				if (msg.uMsg == WM_LBUTTONDOWN) {
					//MessageBox(hWnd, "按钮", "提示框", MB_OK);
					//book *bk = (book *)malloc(sizeof(book));
					ModiBookinfor(bk);

				}
			}
			//图书删除 写好了
			if (msg.x >= 1000 && msg.x <= 1280 && msg.y >= 530 && msg.y <= 580) {
				setlinecolor(RGB(0, 255, 255));

				for (int i = 0; i < 5; i++)
					rectangle(1000 + i, 530 + i, 1280 - i, 580 - i);

				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					book *bt = (book *)malloc(sizeof(book));
					DeleteBook(bk);
				}
				//MessageBox(hWnd, "按钮1", "提示框", MB_OK);

			}
			//用户借阅查询 写好了
			if (msg.x >= 1000 && msg.x <= 1280 && msg.y >= 580 && msg.y <= 630) {
				setlinecolor(RGB(0, 255, 255));

				for (int i = 0; i < 5; i++)
					rectangle(1000 + i, 580 + i, 1280 - i, 630 - i);

				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					oldfillcolor = getfillcolor();
					oldlinecolor = getlinecolor();
					clearrectangle(255, 280, 950, 850);
					setfillcolor(RGB(190, 190, 190));
					setlinecolor(RGB(190, 190, 190));
					fillrectangle(255, 280, 950, 850);

					//颜色还原
					setfillcolor(oldfillcolor);
					setlinecolor(oldlinecolor);
					SelectStudentinfoForMan(stu);
					SelectBroBook(sdbk);
					char c[100];
					int y = 280;
					RECT r = { 255,y ,900 ,85 * 10 };
					//drawtext(_T("学生成绩管理系统"), &r, DT_INTERNAL | DT_LEFT);
					for (int i = 0; i < 3 && sdbk->next != NULL; i++) {
						sprintf(c, "%d ,%d ,%d ", sdbk->SendBookID, sdbk->SendStuID, sdbk->SendNum);
						r.top = y;
						drawtext(c, &r, DT_INTERNAL | DT_LEFT);
						y += 65;
						sdbk = sdbk->next;
					}
					EndBatchDraw();

				}



			}
			//用户查询 写好了
			if (msg.x >= 1000 && msg.x <= 1280 && msg.y >= 705 && msg.y <= 755) {
				setlinecolor(RGB(0, 255, 255));

				for (int i = 0; i < 5; i++)
				{
					rectangle(1000 + i, 705 + i, 1280 - i, 755 - i);
				}


				if (msg.uMsg == WM_LBUTTONDOWN) {
					

					oldfillcolor=getfillcolor();
					oldlinecolor = getlinecolor();
					clearrectangle(255,280,950,850);
					setfillcolor(RGB(190, 190, 190));
					setlinecolor(RGB(190, 190, 190));
					fillrectangle(255, 280, 950, 850);

					//颜色还原
					setfillcolor(oldfillcolor);
					setlinecolor(oldlinecolor);
					SelectStudentinfoForMan(stu);
					char c[100];
					int y = 280;
					RECT r = { 255,y ,900 ,85 * 10 };
					//drawtext(_T("学生成绩管理系统"), &r, DT_INTERNAL | DT_LEFT);
					for (int i = 0; i <4 && stu->next != NULL; i++) {
						sprintf(c, "%d ,%s ,%d,%s ", stu->StuId, stu->name, stu->password, stu->sex);
						r.top = y;
						drawtext(c, &r, DT_INTERNAL | DT_LEFT);
						y += 65;
						stu = stu->next;
					}

				}


			}
			//用户删除 写好了
			if (msg.x >= 1000 && msg.x <= 1280 && msg.y >= 765 && msg.y <= 805) {
				setlinecolor(RGB(0, 255, 255));

				for (int i = 0; i < 5; i++)
					rectangle(1000 + i, 755 + i, 1280 - i, 805 - i);

				if (msg.uMsg == WM_LBUTTONDOWN)
					//MessageBox(hWnd, "按钮1", "提示框", MB_OK);
					DeleteStudent(stu);
			}
			//欢迎退出 写好了
			if (msg.x >= 1000 && msg.x <= 1280 && msg.y >= 805 && msg.y <= 855) {
				setlinecolor(RGB(0, 255, 255));

				for (int i = 0; i < 5; i++)
					rectangle(1000 + i, 805 + i, 1280 - i, 855 - i);

				if (msg.uMsg == WM_LBUTTONDOWN)
					//exit(0);
					return;
			}
		}



		
		
	}

	Sleep(100);
	getch();
	//setfillstyle(oldfillcolor);
	//setlinecolor(oldlinecolor);
	//return;
}
