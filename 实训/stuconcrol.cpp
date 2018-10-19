//���е��߼�����д������
#include "Graph.h"
#include "booksystem.h"

//��½����  �����ѧ������������ṹ���1��������ǹ���Ա��ֻ����2
int  loginCode(student &stu) {
	/*����һ������Ա
	����Ϊ����ʦ ������2018 id ��2018
	Ȼ��ʵ�ֵ�¼�Ĺ���
	*/


	//��ȡ����
	int key = -1;
	TCHAR Tidentity[15], Tpassward[16];
	char Cidentity[10], Cpassward[16];
	InputBox(Tidentity, 10, "�������˺�");
	_bstr_t b(Tidentity);
	strcpy(Cidentity, b);


	InputBox(Tpassward, 10, "����������");
	_bstr_t c(Tpassward);
	strcpy(Cpassward, c);

	HWND hWnd = GetHWnd();
	//��֤�Ƿ�Ϊ����Ա
	if (strcmp(Cidentity, "2018") == 0 && strcmp(Cpassward, "2018") == 0)
	{
		key = 2;
		MessageBox(hWnd, "��½�ɹ�����ӭ��������Ա��", "ͼ�����ϵͳ", MB_OK);
		return 2;
	}

	//�������ݿ⣬����û�
	MYSQL mydata;
	mysql_init(&mydata);
	mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk");
	//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص�������� 
	if (NULL == mysql_real_connect(&mydata, "localhost", "root", "123456", "test", 3306, NULL, 0))
	{
		MessageBox(hWnd, "���ݿ�����ʧ��", "ͼ�����ϵͳ", MB_OK);
		key= -1;
		return key;
	}

	MYSQL_RES *res_set=NULL;
	MYSQL_ROW row;
	
	char sql[100];
	sprintf(sql, "select * from tbl_book_student where student_id=%s", Cidentity);
	if (mysql_real_query(&mydata, sql, strlen(sql))!=0)
	{
		MessageBox(hWnd, "�û���½��ѯʧ��","ͼ�����ϵͳ", MB_OK);
		key = -1;
		return key;
	}
	//��ȡ���
	res_set = mysql_store_result(&mydata);
	
	if (res_set->row_count == 1)
	{
		row = mysql_fetch_row(res_set);
		if (strcmp(row[0], Cidentity) == 0 && strcmp(row[2], Cpassward) == 0)
		{
			key = 1;
			//sprintf(name, "��½�ɹ�����ӭ�㣺%ͬѧ��", row[1]);
			strcpy(stu.name, row[1]);
			stu.password = atoi(row[2]);
			strcpy(stu.sex, row[3]);
			stu.StuId= atoi(row[0]);
			stu.next = NULL;
			MessageBox(hWnd, "��½�ɹ�����ӭ��!", "ͼ�����ϵͳ", MB_OK);
		}
		else
		{
			MessageBox(hWnd, "����������룡", "ͼ�����ϵͳ", MB_OK);
			key = -1;
			return key;
		}
	}
	else
	{
		MessageBox(hWnd, "û������û���", "ͼ�����ϵͳ", MB_OK);
		key= -1;
		return key;
	}
	return key;
}

//ע�ᵯ�� ֻ��ע��ѧ��������ע������Ϣ���ɹ������ɹ���ʧ�ܵ���ʧ��ԭ�򣬷���ֵ���ɹ�1 ʧ��Ϊ-1��
int registerCode(student &stu)
{
	int key = -1;
	HWND hWnd = GetHWnd();		//��������Ҫһ�����ھ��
								//�Ȼ�ȡע����Ϣ:�˺ţ����������룬�Ա�
								//�˺�����
	TCHAR Tidentity[15], Tpassward[16];
	char Cidentity[10], Cpassward[16];
	InputBox(Tidentity, 10, "�������˺�");			//�����˺�
	_bstr_t a(Tidentity);
	strcpy(Cidentity, a);



	TCHAR Tname[15], Tsex[16];
	char Cname[10], Csex[16];


	//�����ݿ⣬���
	//�������ݿ⣬����û�
	MYSQL mydata;
	mysql_init(&mydata);
	mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk");
	//����ĵ�ַ���û��������룬�˿ڿ��Ը����Լ����ص�������� 
	if (NULL == mysql_real_connect(&mydata, "localhost", "root", "123456", "test", 3306, NULL, 0))
	{
		MessageBox(hWnd, "���ݿ�����ʧ��", "ͼ�����ϵͳ", MB_OK);
		key = -1;
		return key;
	}
	MYSQL_RES *res_set = NULL;
	MYSQL_ROW row;
	char sql[100];
	sprintf(sql, "SELECT *FROM TBL_BOOK_STUDENT WHERE STUDENT_ID=%s", Cidentity);
	if (!mysql_real_query(&mydata, sql, strlen(sql))) {//�ɹ�ִ��
		res_set = mysql_store_result(&mydata);
		if (res_set->row_count != 0 && res_set->field_count != 0) {
			//˵��ID��ռ��
			key = -1;
			MessageBox(hWnd, "�˺ű�ռ�ã�", "��ʾ��", MB_OK);
			return key;
		}
		else {
			//û�б��� д�����ݣ����
			InputBox(Tname, 10, "����������");
			_bstr_t c(Tname);
			strcpy(Cname, c);

			InputBox(Tpassward, 10, "����������");
			_bstr_t b(Tpassward);
			strcpy(Cpassward, b);

			InputBox(Tsex, 10, "�������Ա�");
			_bstr_t d(Tsex);
			strcpy(Csex, d);

			sprintf(sql, " INSERT INTO TBL_BOOK_STUDENT  VALUES(%s,\"%s\",%s,\"%s\") ", Cidentity,Cname, Cpassward,Csex);
			if (!mysql_real_query(&mydata, sql, strlen(sql))) {//ִ�гɹ�

				MessageBox(hWnd, "д�����ݳɹ�", "��ʾ��", MB_OK);
				key = 1;
				return key;//
			}
			else {
				MessageBox(hWnd, "д������ʧ��", "��ʾ��", MB_OK);
				//printf("%s", mysql_error(&mydata));
				key = -1;
				return key;
			}
		}

	}
	
	return key;
}

//�޸��û���Ϣ
int ModiStudentinfor(student *stu)
{
	MYSQL conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char host[] = "localhost";                         //MYSQL������
	char szTargetDSN[] = "test";                       //���ݿ���
	const char username[] = "root";                    //�������ݿ�ĺϷ��û���
	//const char password[] = "123456.";					//����
	unsigned int port = 3306;                          //���Ӷ˿ڣ�Ĭ��Ϊ3306
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
			printf("���û������ڣ���\n");
			return -1;
		}
		row = mysql_fetch_row(res);                 //ȡ��һ�е�row��

		//printf("�������û����: ");
		//scanf("%d", &ID2);
		//printf("�������û�����: ");
		//scanf("%s", Name);
		//printf("�������û�����: ");
		//scanf("%d", &Password);
		//printf("�������û��Ա�: ");
		//scanf("%s", sex);
		char Cidentity[20], Cpassward[20];
		InputBox(Cidentity, 10, "�������˺�");			//�����˺�
		InputBox(Name, 10, "����������");
		InputBox(Cpassward, 10, "����������");
		InputBox(sex, 10, "�������Ա�");
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
			printf("�޸ĳɹ��ɹ�����\n");
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
		printf("�������ݿ�ʧ��\n");
		mysql_close(&conn);
		return -1;
	}
	mysql_close(&conn);
	return 1;
}

//��ѯͼ����Ϣ
void SelectBookinfor(book *bk)
{
	MYSQL conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL������
	char szTargetDSN[] = "test";                       //���ݿ���
	const char username[] = "root";                    //�������ݿ�ĺϷ��û���
	const char password[] = "Deng6225217.";            //����
	unsigned int port = 3306;                          //���Ӷ˿ڣ�Ĭ��Ϊ3306

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
		printf("�������ݿ�ʧ��\n");
		mysql_close(&conn);
		return;
	}
	mysql_close(&conn);
}


//����ͼ��
int BroBook(student stu, sendbook *sdbk)
{
	MYSQL conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL������
	char szTargetDSN[] = "test";                       //���ݿ���
	const char username[] = "root";                    //�������ݿ�ĺϷ��û���
	const char password[] = "Deng6225217.";            //����
	unsigned int port = 3306;                          //���Ӷ˿ڣ�Ĭ��Ϊ3306
	char SzSqlTest[1000];
	int book_id, student_id, num;
	char Csex[100], Csex2[100];



	sendbook *ap, *cp;
	ap = NULL;
	cp = sdbk;
	InputBox(Csex, 10, "��������Ҫ������鼮���: ");
	InputBox(Csex2, 10, "����������鼮�������� ");
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
		printf("�������ݿ�ʧ��\n");
		mysql_close(&conn);
		return -1;
	}
	mysql_close(&conn);
}


//ͼ��黹
int ReturnBook(sendbook *sdbk, book *bk, student *stu)
{
	MYSQL conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL������
	char szTargetDSN[] = "test";                       //���ݿ���
	const char username[] = "root";                    //�������ݿ�ĺϷ��û���
	const char password[] = "Deng6225217.";            //����
	unsigned int port = 3306;                          //���Ӷ˿ڣ�Ĭ��Ϊ3306
	char SzSqlTest[1000];
	int book_id, student_id, num;
	char Csex[100], Csex1[100], Csex2[100];

	sendbook *ap, *cp;
	ap = NULL;
	cp = sdbk;
	InputBox(Csex, 10, "��������Ҫ������鼮���:  ");
	InputBox(Csex2, 10, "������黹�鼮��������  ");
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
		printf("�������ݿ�ʧ��\n");
		mysql_close(&conn);
		
		return -1;
	}
	mysql_close(&conn);

}

//��ѯ�ѽ���ͼ��
void SelectBroBook(book *sdbk, student stu)
{
	MYSQL conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char host[] = "localhost";                         //MYSQL������
	char szTargetDSN[] = "test";                       //���ݿ���
	const char username[] = "root";                    //�������ݿ�ĺϷ��û���
	const char password[] = "Deng6225217.";            //����
	unsigned int port = 3306;                          //���Ӷ˿ڣ�Ĭ��Ϊ3306

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
					strcpy(cp->bookName, "��");
					cp->booknum = 0000;
					strcpy(cp->bookType, "��");
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
		printf("�������ݿ�ʧ��\n");
		mysql_close(&conn);
		return;
	}
	mysql_close(&conn);

}
