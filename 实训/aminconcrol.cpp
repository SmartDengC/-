//���е��߼�����д������
#include "Graph.h"
#include "booksystem.h"



//��ѯ�û���Ϣ���Թ���Ա��ݲ�ѯ��
void SelectStudentinfoForMan(student *stu)
{
	//MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL������
	char szTargetDSN[] = "test";                       //���ݿ���
	const char username[] = "root";                    //�������ݿ�ĺϷ��û���
	const char password[] = "123456.";            //����
	unsigned int port = 3306;                          //���Ӷ˿ڣ�Ĭ��Ϊ3306

	student *ap, *cp;
	ap = NULL;
	cp = stu;



	//if ((conn = mysql_init((MYSQL*)0)) && (mysql_options(conn, MYSQL_SET_CHARSET_NAME, "gbk") == 0) && mysql_real_connect(conn, host, username, password, szTargetDSN, port, NULL, 0))
	MYSQL mysql; //mysql����
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص�������� 
	if (NULL != mysql_real_connect(
		&mysql, "localhost", "root", "123456", "test", 3306, NULL, 0)
		)
	{
		if (mysql_query(&mysql, "select *from tbl_book_student"))                     //������߷���
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
		printf("�������ݿ�ʧ��\n");
		mysql_close(&mysql);
		system("pause");
		exit(1);
	}
	mysql_close(&mysql);


}
//ɾ���û���Ϣ

int DeleteStudent(student *stu)
{
	//MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL������
	char szTargetDSN[] = "test";                       //���ݿ���
	const char username[] = "root";                    //�������ݿ�ĺϷ��û���
	const char password[] = "zerodeng.";            //����
	unsigned int port = 3306;                          //���Ӷ˿ڣ�Ĭ��Ϊ3306
	char SzSqlTest1[100];
	char SzSqlTest2[100];
	char ID[20], Csex[100];

	student *ap, *cp;
	ap = NULL;
	cp = stu;


	InputBox(ID, 10, "��������Ҫɾ�����û����: ");

	sprintf(SzSqlTest1, "DELETE FROM tbl_book_student WHERE student_id='%s'", ID);
	sprintf(SzSqlTest2, "select *from tbl_book_student where student_id='%s'", ID);


	//if ((conn = mysql_init((MYSQL*)0)) && (mysql_options(conn, MYSQL_SET_CHARSET_NAME, "gbk") == 0) && mysql_real_connect(conn, host, username, password, szTargetDSN, port, NULL, 0))
	MYSQL mysql; //mysql����
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص�������� 
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
			printf("���û������ڣ���\n");
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
			printf("ɾ���ɹ�����\n");
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
		printf("�������ݿ�ʧ��\n");
		mysql_close(&mysql);
		system("pause");
		exit(1);
	}
	mysql_close(&mysql);
}



//����Աͼ����� ��ѯ��
void SelectBroBook(sendbook *sdbk)
{
	//MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL������
	char szTargetDSN[] = "test";                       //���ݿ���
	const char username[] = "root";                    //�������ݿ�ĺϷ��û���
	const char password[] = "Deng6225217.";            //����
	unsigned int port = 3306;                          //���Ӷ˿ڣ�Ĭ��Ϊ3306

	sendbook *ap, *cp;
	ap = NULL;
	cp = sdbk;



	//if ((conn = mysql_init((MYSQL*)0)) && (mysql_options(conn, MYSQL_SET_CHARSET_NAME, "gbk") == 0) && mysql_real_connect(conn, host, username, password, szTargetDSN, port, NULL, 0))

	MYSQL mysql; //mysql����
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص�������� 
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
		printf("�������ݿ�ʧ��\n");
		mysql_close(&mysql);
		system("pause");
		exit(1);
	}
	mysql_close(&mysql);

}




//���ͼ����Ϣ
void AddBookinfor(book *bk)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL������
	char szTargetDSN[] = "test";                       //���ݿ���
	const char username[] = "root";                    //�������ݿ�ĺϷ��û���
	const char password[] = "123456";            //����
	unsigned int port = 3306;                          //���Ӷ˿ڣ�Ĭ��Ϊ3306
	char SzSqlTest[1000];

	int ID, Num;
	char Name[20], Type[20];

	book *ap, *cp;
	ap = NULL;
	cp = bk;
	/*
	printf("������ͼ����: ");scanf("%d", &ID);
	printf("������ͼ�����ƣ� ");scanf("%s", Name);
	printf("������ͼ����� ");scanf("%s", Type);
	printf("������ͼ���棺 ");scanf("%d", &Num);
	*/

	char keepArray[10][20];

	InputBox(keepArray[0], 20, "������ͼ����:");
	InputBox(Name, 20, "������ͼ������:");
	InputBox(Type, 20, "������ͼ�����:");
	InputBox(keepArray[3], 20, "������ͼ����:");


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
				row = mysql_fetch_row(res);                 //ȡ��һ�е�row��
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
		printf("�������ݿ�ʧ��\n");
		mysql_close(conn);
		system("pause");
		exit(1);
	}
	mysql_close(conn);

}


//�Ҳ�����ɾ�� �鼮����

int DeleteBook(book *bk)
{

	//MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL������
	char szTargetDSN[] = "test";                       //���ݿ���
	const char username[] = "root";                    //�������ݿ�ĺϷ��û���
	const char password[] = "123456.";            //����
	unsigned int port = 3306;                          //���Ӷ˿ڣ�Ĭ��Ϊ3306
	char SzSqlTest1[100];
	char SzSqlTest2[100];
	char ID[20], Csex[100];


	book *ap, *cp;
	ap = NULL;
	cp = bk;


	InputBox(ID, 10, "��������Ҫɾ����ͼ����: ");
	if (ID == NULL) {
		return -1;
	}


	sprintf(SzSqlTest1, "DELETE FROM tbl_book_infor WHERE book_id='%s'", ID);
	sprintf(SzSqlTest2, "select *from tbl_book_infor where book_id='%s'", ID);


	//if ((conn = mysql_init((MYSQL*)0)) && (mysql_options(conn, MYSQL_SET_CHARSET_NAME, "gbk") == 0) && mysql_real_connect(conn, host, username, password, szTargetDSN, port, NULL, 0))
	MYSQL mysql; //mysql����
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص�������� 
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
			printf("���鼮�����ڣ���\n");
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
			printf("ɾ���ɹ�����\n");
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
		printf("�������ݿ�ʧ��\n");
		mysql_close(&mysql);
		//system("pause");
		return -1;;
	}
	mysql_close(&mysql);

}


//�޸��鼮 
void  ModiBookinfor(book *bk) {
	MYSQL mysql; //mysql����
	MYSQL *conn;
	MYSQL_FIELD *fd;  //�ֶ�������
	char field[32][32];  //���ֶ�����ά����
	MYSQL_RES *res; //����ṹ�������е�һ����ѯ�����
	MYSQL_ROW row;
	char query[150]; //��ѯ���

					 //char SzSqlTest[1000];//��ѯ���

	char Name[20], type[20];//����
	int ID1, ID2, num;
	book *ap, *cp;
	ap = NULL;
	cp = bk;

	char IDchar[20];
	InputBox(IDchar, 20, "��������Ҫ�޸ĵ��鼮���: ");
	ID1 = atoi(IDchar);
	sprintf(query, "select *from tbl_book_infor where book_id='%d'", ID1);


	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص�������� 
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
			printf("��ͼ�鲻���ڣ���\n");
			return;
		}
		row = mysql_fetch_row(res);                 //ȡ��һ�е�row��


		char keepArray[5][20];

		InputBox(keepArray[0], 20, "������ͼ����:");
		InputBox(Name, 20, "������ͼ������:");
		InputBox(type, 20, "������ͼ�����:");//type
		InputBox(keepArray[3], 20, "������ͼ����:");


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
			printf("�޸ĳɹ��ɹ�����\n");
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
		printf("���ݿ�����ʧ�ܣ�%s\n", mysql_error(&mysql));

		system("pause");
	}
	mysql_close(&mysql);
}

