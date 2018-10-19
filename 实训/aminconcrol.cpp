//所有的逻辑函数写在这里
#include "Graph.h"
#include "booksystem.h"



//查询用户信息（以管理员身份查询）
void SelectStudentinfoForMan(student *stu)
{
	//MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL主机名
	char szTargetDSN[] = "test";                       //数据库名
	const char username[] = "root";                    //连接数据库的合法用户名
	const char password[] = "123456.";            //密码
	unsigned int port = 3306;                          //连接端口，默认为3306

	student *ap, *cp;
	ap = NULL;
	cp = stu;



	//if ((conn = mysql_init((MYSQL*)0)) && (mysql_options(conn, MYSQL_SET_CHARSET_NAME, "gbk") == 0) && mysql_real_connect(conn, host, username, password, szTargetDSN, port, NULL, 0))
	MYSQL mysql; //mysql连接
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//这里的地址，用户名，密码，端口可以根据自己本地的情况更改 
	if (NULL != mysql_real_connect(
		&mysql, "localhost", "root", "123456", "test", 3306, NULL, 0)
		)
	{
		if (mysql_query(&mysql, "select *from tbl_book_student"))                     //查找最高分数
		{
			mysql_close(&mysql);
			exit(1);
		}
		else
		{
			res = mysql_store_result(&mysql);
			while (row = mysql_fetch_row(res))
			{

				//printf("%s\t\t%s\t\t%s\t\t%s\n", row[0], row[1], row[2], row[3]);
				cp->StuId = atoi(row[0]);
				sprintf(cp->name, "%s", row[1]);
				//strcpy(cp->name, row[1]);
				cp->password = atoi(row[2]);
				//strcpy(cp->sex, row[3]);
				sprintf(cp->sex, "%s", row[3]);
				ap = cp;
				cp->next = (student*)malloc(sizeof(student));
				cp = cp->next;

			}
		}
	}
	else
	{
		printf("连接数据库失败\n");
		mysql_close(&mysql);
		system("pause");
		exit(1);
	}
	mysql_close(&mysql);


}
//删除用户信息

int DeleteStudent(student *stu)
{
	//MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL主机名
	char szTargetDSN[] = "test";                       //数据库名
	const char username[] = "root";                    //连接数据库的合法用户名
	const char password[] = "zerodeng.";            //密码
	unsigned int port = 3306;                          //连接端口，默认为3306
	char SzSqlTest1[100];
	char SzSqlTest2[100];
	char ID[20], Csex[100];

	student *ap, *cp;
	ap = NULL;
	cp = stu;


	InputBox(ID, 10, "请输入需要删除的用户编号: ");

	sprintf(SzSqlTest1, "DELETE FROM tbl_book_student WHERE student_id='%s'", ID);
	sprintf(SzSqlTest2, "select *from tbl_book_student where student_id='%s'", ID);


	//if ((conn = mysql_init((MYSQL*)0)) && (mysql_options(conn, MYSQL_SET_CHARSET_NAME, "gbk") == 0) && mysql_real_connect(conn, host, username, password, szTargetDSN, port, NULL, 0))
	MYSQL mysql; //mysql连接
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//这里的地址，用户名，密码，端口可以根据自己本地的情况更改 
	if (NULL != mysql_real_connect(
		&mysql, "localhost", "root", "123456", "test", 3306, NULL, 0)
		)
	{
		if (mysql_query(&mysql, SzSqlTest2))
		{
			mysql_close(&mysql);
			exit(1);
		}
		res = mysql_store_result(&mysql);

		if (res->row_count == 0)
		{
			printf("该用户不存在！！\n");
			return -1;
		}
		row = mysql_fetch_row(res);
		if (mysql_query(&mysql, SzSqlTest1))
		{
			mysql_close(&mysql);
			exit(1);
		}
		else
		{
			printf("删除成功！！\n");
			/*
			while (cp->next != NULL)
			{
			if (cp->StuId == (int)ID)
			{
			break;
			}
			ap = cp;
			cp = cp->next;
			}
			if (ap == NULL)
			{
			stu = stu->next;
			free(cp);
			cp = cp->next;
			}
			else
			{
			ap->next = cp->next;
			free(cp);
			cp = cp->next;
			}
			*/
		}
		return 1;
	}
	else
	{
		printf("连接数据库失败\n");
		mysql_close(&mysql);
		system("pause");
		exit(1);
	}
	mysql_close(&mysql);
}



//管理员图书借阅 查询？
void SelectBroBook(sendbook *sdbk)
{
	//MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL主机名
	char szTargetDSN[] = "test";                       //数据库名
	const char username[] = "root";                    //连接数据库的合法用户名
	const char password[] = "Deng6225217.";            //密码
	unsigned int port = 3306;                          //连接端口，默认为3306

	sendbook *ap, *cp;
	ap = NULL;
	cp = sdbk;



	//if ((conn = mysql_init((MYSQL*)0)) && (mysql_options(conn, MYSQL_SET_CHARSET_NAME, "gbk") == 0) && mysql_real_connect(conn, host, username, password, szTargetDSN, port, NULL, 0))

	MYSQL mysql; //mysql连接
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//这里的地址，用户名，密码，端口可以根据自己本地的情况更改 
	if (NULL != mysql_real_connect(
		&mysql, "localhost", "root", "123456", "test", 3306, NULL, 0)
		) {
		if (mysql_query(&mysql, "select *from tbl_book_send"))
		{
			mysql_close(&mysql);
			exit(1);
		}
		else
		{
			res = mysql_store_result(&mysql);
			while (row = mysql_fetch_row(res))
			{


				cp->SendBookID = atoi(row[0]);
				cp->SendStuID = atoi(row[1]);
				cp->SendNum = atoi(row[2]);
				ap = cp;
				cp->next = (sendbook*)malloc(sizeof(sendbook));
				cp = cp->next;
				cp->next = NULL;
			}
		}
	}
	else
	{
		printf("连接数据库失败\n");
		mysql_close(&mysql);
		system("pause");
		exit(1);
	}
	mysql_close(&mysql);

}




//添加图书信息
void AddBookinfor(book *bk)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL主机名
	char szTargetDSN[] = "test";                       //数据库名
	const char username[] = "root";                    //连接数据库的合法用户名
	const char password[] = "123456";            //密码
	unsigned int port = 3306;                          //连接端口，默认为3306
	char SzSqlTest[1000];

	int ID, Num;
	char Name[20], Type[20];

	book *ap, *cp;
	ap = NULL;
	cp = bk;
	/*
	printf("请输入图书编号: ");scanf("%d", &ID);
	printf("请输入图书名称： ");scanf("%s", Name);
	printf("请输入图书类别： ");scanf("%s", Type);
	printf("请输入图书库存： ");scanf("%d", &Num);
	*/

	char keepArray[10][20];

	InputBox(keepArray[0], 20, "请输入图书编号:");
	InputBox(Name, 20, "请输入图书名称:");
	InputBox(Type, 20, "请输入图书类别:");
	InputBox(keepArray[3], 20, "请输入图书库存:");


	ID = atoi(keepArray[0]);
	Num = atoi(keepArray[3]);


	sprintf(SzSqlTest, "INSERT INTO tbl_book_infor VALUES ('%d','%s','%s','%d')", ID, Type, Name, Num);


	if ((conn = mysql_init((MYSQL*)0))
		&& (mysql_options(conn, MYSQL_SET_CHARSET_NAME, "gbk") == 0)
		&& mysql_real_connect(conn, host, username, password, szTargetDSN, port, NULL, 0))
	{
		if (mysql_query(conn, SzSqlTest))
		{
			mysql_close(conn);
			exit(1);
		}
		else
		{
			if (mysql_query(conn, "select *from tbl_book_infor"))
			{
				mysql_close(conn);
				exit(1);
			}
			res = mysql_store_result(conn);
			while (1)
			{
				row = mysql_fetch_row(res);                 //取第一行到row中
				if (row == NULL)
				{
					ap->next = NULL;
					break;
				}
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
	else
	{
		printf("连接数据库失败\n");
		mysql_close(conn);
		system("pause");
		exit(1);
	}
	mysql_close(conn);

}


//我猜这是删除 书籍操作

int DeleteBook(book *bk)
{

	//MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL主机名
	char szTargetDSN[] = "test";                       //数据库名
	const char username[] = "root";                    //连接数据库的合法用户名
	const char password[] = "123456.";            //密码
	unsigned int port = 3306;                          //连接端口，默认为3306
	char SzSqlTest1[100];
	char SzSqlTest2[100];
	char ID[20], Csex[100];


	book *ap, *cp;
	ap = NULL;
	cp = bk;


	InputBox(ID, 10, "请输入需要删除的图书编号: ");
	if (ID == NULL) {
		return -1;
	}


	sprintf(SzSqlTest1, "DELETE FROM tbl_book_infor WHERE book_id='%s'", ID);
	sprintf(SzSqlTest2, "select *from tbl_book_infor where book_id='%s'", ID);


	//if ((conn = mysql_init((MYSQL*)0)) && (mysql_options(conn, MYSQL_SET_CHARSET_NAME, "gbk") == 0) && mysql_real_connect(conn, host, username, password, szTargetDSN, port, NULL, 0))
	MYSQL mysql; //mysql连接
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//这里的地址，用户名，密码，端口可以根据自己本地的情况更改 
	if (NULL != mysql_real_connect(
		&mysql, "localhost", "root", "123456", "test", 3306, NULL, 0)
		)

	{
		if (mysql_query(&mysql, SzSqlTest2))
		{
			mysql_close(&mysql);
			exit(1);
		}
		res = mysql_store_result(&mysql);

		if (res->row_count == 0)
		{
			printf("该书籍不存在！！\n");
			return -1;
		}
		row = mysql_fetch_row(res);
		if (mysql_query(&mysql, SzSqlTest1))
		{
			mysql_close(&mysql);
			exit(1);
		}
		else
		{
			printf("删除成功！！\n");
			/*
			while (cp->next != NULL)
			{
			if (cp->bookId == (int)ID)
			{
			break;
			}
			ap = cp;
			cp = cp->next;
			}
			if (ap == NULL)
			{
			bk = bk->next;
			free(cp);
			cp = cp->next;
			}
			else
			{
			ap->next = cp->next;
			free(cp);
			cp = cp->next;
			}
			*/
		}
		return 1;
	}
	else
	{
		printf("连接数据库失败\n");
		mysql_close(&mysql);
		//system("pause");
		return -1;;
	}
	mysql_close(&mysql);

}


//修改书籍 
void  ModiBookinfor(book *bk) {
	MYSQL mysql; //mysql连接
	MYSQL *conn;
	MYSQL_FIELD *fd;  //字段列数组
	char field[32][32];  //存字段名二维数组
	MYSQL_RES *res; //这个结构代表返回行的一个查询结果集
	MYSQL_ROW row;
	char query[150]; //查询语句

					 //char SzSqlTest[1000];//查询语句

	char Name[20], type[20];//定义
	int ID1, ID2, num;
	book *ap, *cp;
	ap = NULL;
	cp = bk;

	char IDchar[20];
	InputBox(IDchar, 20, "请输入需要修改的书籍编号: ");
	ID1 = atoi(IDchar);
	sprintf(query, "select *from tbl_book_infor where book_id='%d'", ID1);


	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//这里的地址，用户名，密码，端口可以根据自己本地的情况更改 
	if (NULL != mysql_real_connect(
		&mysql, "localhost", "root", "123456", "test", 3306, NULL, 0)
		)
	{
		if (mysql_query(&mysql, query))
		{
			mysql_close(&mysql);
			exit(1);
		}
		res = mysql_store_result(&mysql);

		if (res->row_count == 0)
		{
			printf("该图书不存在！！\n");
			return;
		}
		row = mysql_fetch_row(res);                 //取第一行到row中


		char keepArray[5][20];

		InputBox(keepArray[0], 20, "请输入图书编号:");
		InputBox(Name, 20, "请输入图书名称:");
		InputBox(type, 20, "请输入图书类别:");//type
		InputBox(keepArray[3], 20, "请输入图书库存:");


		ID2 = atoi(keepArray[0]);
		num = atoi(keepArray[3]);



		sprintf(query, "UPDATE tbl_book_infor SET book_id='%d',book_type='%s',book_name='%s',book_num='%d' WHERE book_id='%d'", ID2, type, Name, num, ID1);

		if (mysql_query(&mysql, query))
		{
			mysql_close(&mysql);
			exit(1);
		}
		else
		{
			printf("修改成功成功！！\n");
			/*
			while (cp != NULL)
			{
			if (cp->bookId == ID1)
			{
			break;
			}
			ap = cp;
			cp = cp->next;
			}
			cp->bookId = ID2;
			strcpy(cp->bookType, type);
			strcpy(cp->bookName, Name);
			cp->booknum = num;
			*/
		}
	}
	else
	{
		printf("数据库连接失败！%s\n", mysql_error(&mysql));

		system("pause");
	}
	mysql_close(&mysql);
}

