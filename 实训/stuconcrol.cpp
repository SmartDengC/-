//所有的逻辑函数写在这里
#include "Graph.h"
#include "booksystem.h"

//登陆弹框  如果是学生，返回这个结构体和1，，如果是管理员就只返回2
int  loginCode(student &stu) {
	/*定义一个管理员
	名字为李老师 密码是2018 id 是2018
	然后实现登录的过程
	*/


	//获取数据
	int key = -1;
	TCHAR Tidentity[15], Tpassward[16];
	char Cidentity[10], Cpassward[16];
	InputBox(Tidentity, 10, "请输入账号");
	_bstr_t b(Tidentity);
	strcpy(Cidentity, b);


	InputBox(Tpassward, 10, "请输入密码");
	_bstr_t c(Tpassward);
	strcpy(Cpassward, c);

	HWND hWnd = GetHWnd();
	//验证是否为管理员
	if (strcmp(Cidentity, "2018") == 0 && strcmp(Cpassward, "2018") == 0)
	{
		key = 2;
		MessageBox(hWnd, "登陆成功，欢迎您：管理员！", "图书管理系统", MB_OK);
		return 2;
	}

	//连接数据库，检查用户
	MYSQL mydata;
	mysql_init(&mydata);
	mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk");
	//这里的地址，用户名，密码，端口可以根据自己本地的情况更改 
	if (NULL == mysql_real_connect(&mydata, "localhost", "root", "123456", "test", 3306, NULL, 0))
	{
		MessageBox(hWnd, "数据库连接失败", "图书管理系统", MB_OK);
		key= -1;
		return key;
	}

	MYSQL_RES *res_set=NULL;
	MYSQL_ROW row;
	
	char sql[100];
	sprintf(sql, "select * from tbl_book_student where student_id=%s", Cidentity);
	if (mysql_real_query(&mydata, sql, strlen(sql))!=0)
	{
		MessageBox(hWnd, "用户登陆查询失败","图书管理系统", MB_OK);
		key = -1;
		return key;
	}
	//获取结果
	res_set = mysql_store_result(&mydata);
	
	if (res_set->row_count == 1)
	{
		row = mysql_fetch_row(res_set);
		if (strcmp(row[0], Cidentity) == 0 && strcmp(row[2], Cpassward) == 0)
		{
			key = 1;
			//sprintf(name, "登陆成功，欢迎你：%同学！", row[1]);
			strcpy(stu.name, row[1]);
			stu.password = atoi(row[2]);
			strcpy(stu.sex, row[3]);
			stu.StuId= atoi(row[0]);
			stu.next = NULL;
			MessageBox(hWnd, "登陆成功，欢迎你!", "图书管理系统", MB_OK);
		}
		else
		{
			MessageBox(hWnd, "请检查你的输入！", "图书管理系统", MB_OK);
			key = -1;
			return key;
		}
	}
	else
	{
		MessageBox(hWnd, "没有这个用户！", "图书管理系统", MB_OK);
		key= -1;
		return key;
	}
	return key;
}

//注册弹窗 只能注册学生，弹出注册结果信息：成功弹出成功，失败弹出失败原因，返回值：成功1 失败为-1；
int registerCode(student &stu)
{
	int key = -1;
	HWND hWnd = GetHWnd();		//弹出框需要一个窗口句柄
								//先获取注册信息:账号，姓名，密码，性别
								//账号密码
	TCHAR Tidentity[15], Tpassward[16];
	char Cidentity[10], Cpassward[16];
	InputBox(Tidentity, 10, "请输入账号");			//输入账号
	_bstr_t a(Tidentity);
	strcpy(Cidentity, a);



	TCHAR Tname[15], Tsex[16];
	char Cname[10], Csex[16];


	//打开数据库，查错
	//连接数据库，检查用户
	MYSQL mydata;
	mysql_init(&mydata);
	mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk");
	//这里的地址，用户名，密码，端口可以根据自己本地的情况更改 
	if (NULL == mysql_real_connect(&mydata, "localhost", "root", "123456", "test", 3306, NULL, 0))
	{
		MessageBox(hWnd, "数据库连接失败", "图书管理系统", MB_OK);
		key = -1;
		return key;
	}
	MYSQL_RES *res_set = NULL;
	MYSQL_ROW row;
	char sql[100];
	sprintf(sql, "SELECT *FROM TBL_BOOK_STUDENT WHERE STUDENT_ID=%s", Cidentity);
	if (!mysql_real_query(&mydata, sql, strlen(sql))) {//成功执行
		res_set = mysql_store_result(&mydata);
		if (res_set->row_count != 0 && res_set->field_count != 0) {
			//说明ID被占用
			key = -1;
			MessageBox(hWnd, "账号被占用！", "提示框", MB_OK);
			return key;
		}
		else {
			//没有被用 写入数据，查错
			InputBox(Tname, 10, "请输入姓名");
			_bstr_t c(Tname);
			strcpy(Cname, c);

			InputBox(Tpassward, 10, "请输入密码");
			_bstr_t b(Tpassward);
			strcpy(Cpassward, b);

			InputBox(Tsex, 10, "请输入性别");
			_bstr_t d(Tsex);
			strcpy(Csex, d);

			sprintf(sql, " INSERT INTO TBL_BOOK_STUDENT  VALUES(%s,\"%s\",%s,\"%s\") ", Cidentity,Cname, Cpassward,Csex);
			if (!mysql_real_query(&mydata, sql, strlen(sql))) {//执行成功

				MessageBox(hWnd, "写入数据成功", "提示框", MB_OK);
				key = 1;
				return key;//
			}
			else {
				MessageBox(hWnd, "写入数据失败", "提示框", MB_OK);
				//printf("%s", mysql_error(&mydata));
				key = -1;
				return key;
			}
		}

	}
	
	return key;
}

//修改用户信息
int ModiStudentinfor(student *stu)
{
	MYSQL conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char host[] = "localhost";                         //MYSQL主机名
	char szTargetDSN[] = "test";                       //数据库名
	const char username[] = "root";                    //连接数据库的合法用户名
	//const char password[] = "123456.";					//密码
	unsigned int port = 3306;                          //连接端口，默认为3306
	char SzSqlTest[1000];
	char Name[20], sex[4];
	int ID1, ID2, Password;

	student *ap, *cp;
	ap = NULL;
	cp = stu;
	ID1 = stu->StuId;
	sprintf(SzSqlTest, "select *from tbl_book_student where student_id='%d'", ID1);

	mysql_init(&conn);
	mysql_options(&conn, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&conn, "localhost", "root", "123456", "test", 3306, NULL, 0)!=0)
	{
		if (mysql_query(&conn, SzSqlTest))
		{
			mysql_close(&conn);
			return -1;
		}
		res = mysql_store_result(&conn);

		if (res->row_count == 0)
		{
			printf("该用户不存在！！\n");
			return -1;
		}
		row = mysql_fetch_row(res);                 //取第一行到row中

		//printf("请输入用户编号: ");
		//scanf("%d", &ID2);
		//printf("请输入用户姓名: ");
		//scanf("%s", Name);
		//printf("请输入用户密码: ");
		//scanf("%d", &Password);
		//printf("请输入用户性别: ");
		//scanf("%s", sex);
		char Cidentity[20], Cpassward[20];
		InputBox(Cidentity, 10, "请输入账号");			//输入账号
		InputBox(Name, 10, "请输入姓名");
		InputBox(Cpassward, 10, "请输入密码");
		InputBox(sex, 10, "请输入性别");
		ID2 = atoi(Cidentity);
		Password = atoi(Cpassward);
		
		sprintf(SzSqlTest, "UPDATE tbl_book_student SET student_id='%d',student_name='%s',password='%d',student_sex='%s' WHERE student_id='%d'", ID2, Name, Password, sex, ID1);

		if (mysql_real_query(&conn, SzSqlTest,strlen(SzSqlTest)))
		{
			mysql_close(&conn);
			return -1;
		}
		else
		{
			printf("修改成功成功！！\n");
			while (cp != NULL)
			{
				if (cp->StuId == ID1)
				{
					break;
				}
				ap = cp;
				cp = cp->next;
			}
			cp->StuId = ID2;
			strcpy(cp->name, Name);
			cp->password = Password;
			strcpy(cp->sex, sex);
		}
	}
	else
	{
		printf("连接数据库失败\n");
		mysql_close(&conn);
		return -1;
	}
	mysql_close(&conn);
	return 1;
}

//查询图书信息
void SelectBookinfor(book *bk)
{
	MYSQL conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL主机名
	char szTargetDSN[] = "test";                       //数据库名
	const char username[] = "root";                    //连接数据库的合法用户名
	const char password[] = "Deng6225217.";            //密码
	unsigned int port = 3306;                          //连接端口，默认为3306

	book *ap, *cp;
	ap = NULL;
	cp = bk;



	mysql_init(&conn);
	mysql_options(&conn, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&conn, "localhost", "root", "123456", "test", 3306, NULL, 0) != 0)
	{
		if (mysql_query(&conn, "select *from tbl_book_infor"))
		{
			mysql_close(&conn);
			return ;
		}
		else
		{
			res = mysql_store_result(&conn);
			while (1)
			{
				row = mysql_fetch_row(res);
				if (row == NULL)
				{
					cp->next = NULL;
					break;
				}
				if ((int)row[3] != 0)
				{
					printf("%s\t\t%s\t\t%s\t\t%s\n", row[0], row[1], row[2], row[3]);
					cp->bookId = atoi(row[0]);
					strcpy(cp->bookType, row[1]);
					strcpy(cp->bookName, row[2]);
					cp->booknum = atoi(row[3]);
					ap = cp;
					cp->next = (book*)malloc(sizeof(book));
					cp = cp->next;
				}
			}
		}
	}
	else
	{
		printf("连接数据库失败\n");
		mysql_close(&conn);
		return;
	}
	mysql_close(&conn);
}


//借阅图书
int BroBook(student stu, sendbook *sdbk)
{
	MYSQL conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL主机名
	char szTargetDSN[] = "test";                       //数据库名
	const char username[] = "root";                    //连接数据库的合法用户名
	const char password[] = "Deng6225217.";            //密码
	unsigned int port = 3306;                          //连接端口，默认为3306
	char SzSqlTest[1000];
	int book_id, student_id, num;
	char Csex[100], Csex2[100];



	sendbook *ap, *cp;
	ap = NULL;
	cp = sdbk;
	InputBox(Csex, 10, "请输入需要借书的书籍编号: ");
	InputBox(Csex2, 10, "请输入借阅书籍的数量： ");
	book_id = atoi(Csex);
	num = atoi(Csex2);
	student_id = stu.StuId;
	sprintf(SzSqlTest, "SELECT *FROM tbl_book_send where send_book_id='%d'", book_id);

	mysql_init(&conn);
	mysql_options(&conn, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&conn, "localhost", "root", "123456", "test", 3306, NULL, 0) != 0)
	{
		if (mysql_query(&conn, SzSqlTest))
		{
			mysql_close(&conn);
			return -1;
		}
		else
		{
			res = mysql_store_result(&conn);


			if (res->row_count == 0)
			{
				sprintf(SzSqlTest, "INSERT INTO tbl_book_send VALUES ('%d','%d','%d')", book_id, stu.StuId, num);
				if (mysql_query(&conn, SzSqlTest))
				{
					mysql_close(&conn);
					return -1;
				}
				else
				{
					if (mysql_query(&conn, "select *from tbl_book_send"))
					{
						mysql_close(&conn);
						return -1;
					}
					res = mysql_store_result(&conn);
					while (1)
					{
						row = mysql_fetch_row(res);
						if (row == NULL)
						{
							ap->next = NULL;
							break;
						}
						printf("%s\t\t%s\t\t%s\n", row[0], row[1], row[2]);
						cp->SendBookID = atoi(row[0]);
						cp->SendStuID = atoi(row[1]);
						cp->SendNum = atoi(row[2]);
						ap = cp;
						cp->next = (sendbook*)malloc(sizeof(sendbook));
						cp = cp->next;
					}
				}
			}

			else
			{
				row = mysql_fetch_row(res);
				if (atoi(row[0]) == book_id && atoi(row[1]) == student_id)
				{
					int n = atoi(row[2]);
					n = n + num;
					sprintf(SzSqlTest, "UPDATE tbl_book_send SET send_book_num='%d' where send_book_id='%d'", n, book_id);
					if (mysql_query(&conn, SzSqlTest))
					{
						mysql_close(&conn);
						return 1;
					}
					else
					{
						return 1;
					}
				}
			}


			sprintf(SzSqlTest, "select *from tbl_book_infor where book_id='%d'", book_id);
			if (mysql_query(&conn, SzSqlTest))
			{
				mysql_close(&conn);
				return -1;
			}
			else
			{
				res = mysql_store_result(&conn);
				row = mysql_fetch_row(res);
				int i = atoi(row[3]);
				i = i - num;
				sprintf(SzSqlTest, "UPDATE tbl_book_infor SET book_num='%d' where book_id='%d'", i, book_id);
			}
			if (mysql_query(&conn, SzSqlTest))
			{
				mysql_close(&conn);
				return -1;
			}
			else
			{
				return 1;
			}
		}
	}
	else
	{
		printf("连接数据库失败\n");
		mysql_close(&conn);
		return -1;
	}
	mysql_close(&conn);
}


//图书归还
int ReturnBook(sendbook *sdbk, book *bk, student *stu)
{
	MYSQL conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL主机名
	char szTargetDSN[] = "test";                       //数据库名
	const char username[] = "root";                    //连接数据库的合法用户名
	const char password[] = "Deng6225217.";            //密码
	unsigned int port = 3306;                          //连接端口，默认为3306
	char SzSqlTest[1000];
	int book_id, student_id, num;
	char Csex[100], Csex1[100], Csex2[100];

	sendbook *ap, *cp;
	ap = NULL;
	cp = sdbk;
	InputBox(Csex, 10, "请输入需要还书的书籍编号:  ");
	InputBox(Csex2, 10, "请输入归还书籍的数量：  ");
	book_id = atoi(Csex);
	student_id = stu->StuId;
	num = atoi(Csex2);
	sprintf(SzSqlTest, "SELECT *FROM tbl_book_send WHERE send_book_id='%d' AND send_student_id='%d'", book_id, student_id);
	mysql_init(&conn);
	mysql_options(&conn, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&conn, "localhost", "root", "123456", "test", 3306, NULL, 0) != 0)
	{
		if (mysql_query(&conn, SzSqlTest))
		{
			mysql_close(&conn);
			return -1;
		}
		else
		{
			res = mysql_store_result(&conn);
			if (res->row_count == 0)
			{
				return -1;
			}
			else
			{
				row = mysql_fetch_row(res);
				if (atoi(row[0]) == book_id && atoi(row[1]) == student_id)
				{
					int n = atoi(row[2]);
					if (n < num)
					{
						return -1;
					}
					else
					{
						n = n - num;
						if (n == 0)
						{
							sprintf(SzSqlTest, "DELETE FROM tbl_book_send WHERE send_book_id", book_id);
						}
						else
						{
							sprintf(SzSqlTest, "UPDATE tbl_book_send SET send_book_num='%d' where send_book_id='%d'", n, book_id);
						}
					}
					if (mysql_query(&conn, SzSqlTest))
					{
						mysql_close(&conn);
						return -1;
					}
					else
					{
						return 1;
					}
				}
			}


			sprintf(SzSqlTest, "select *from tbl_book_infor where book_id='%d'", book_id);
			if (mysql_query(&conn, SzSqlTest))
			{
				mysql_close(&conn);
				return -1;
			}
			else
			{
				res = mysql_store_result(&conn);
				row = mysql_fetch_row(res);
				int i = atoi(row[3]);
				i = i + num;
				sprintf(SzSqlTest, "UPDATE tbl_book_infor SET book_num='%d' where book_id='%d'", i, book_id);
			}
			if (mysql_query(&conn, SzSqlTest))
			{
				mysql_close(&conn);
				return -1;
			}
			else
			{
				return 1;
			}
		}

		return 0;
	}
	else
	{
		printf("连接数据库失败\n");
		mysql_close(&conn);
		
		return -1;
	}
	mysql_close(&conn);

}

//查询已借阅图书
void SelectBroBook(book *sdbk, student stu)
{
	MYSQL conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL主机名
	char szTargetDSN[] = "test";                       //数据库名
	const char username[] = "root";                    //连接数据库的合法用户名
	const char password[] = "Deng6225217.";            //密码
	unsigned int port = 3306;                          //连接端口，默认为3306

	book *ap, *cp;
	ap = NULL;
	cp = sdbk;

	char sql[200];
	//select * from book as a,stu as b where a.sutid = b.stuid
	sprintf(sql, "select *from tbl_book_infor as a,tbl_book_send as b where a.book_id=b.send_book_id and b.send_student_id=%d", stu.StuId);


	mysql_init(&conn);
	mysql_options(&conn, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&conn, "localhost", "root", "123456", "test", 3306, NULL, 0) != 0)
	{
		if (mysql_real_query(&conn, sql,strlen(sql)))
		{
			mysql_close(&conn);
			return ;
		}
		else
		{
			res = mysql_store_result(&conn);
			while (1)
			{
				row = mysql_fetch_row(res);
				if (row == NULL)
				{
					cp->bookId = 00000;
					strcpy(cp->bookName, "无");
					cp->booknum = 0000;
					strcpy(cp->bookType, "无");
					cp->next = NULL;
					break;
				}
				
				cp->bookId = atoi(row[0]);
				strcpy(cp->bookType,row[1]);
				strcpy(cp->bookName, row[2]);
				cp->booknum = atoi(row[6]);
				ap = cp;
				cp->next = (book*)malloc(sizeof(book));
				cp = cp->next;

			}
		}
	}
	else
	{
		printf("连接数据库失败\n");
		mysql_close(&conn);
		return;
	}
	mysql_close(&conn);

}
