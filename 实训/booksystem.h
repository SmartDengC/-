#pragma once
#ifndef _BOOKSYSTEM_H_    
#define _BOOKSYSTEM_H_  
#include<mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <comdef.h>  // wchar_tתchar 
#define STUDENTNUM 100
#define BOOKNUM 100
#define SENDBOOKNUM 100
#pragma comment(lib, "libmysql.lib")


//�û��������Ͻṹ��
typedef struct Student
{
	char name[20];             //�û�����
	int password;          //��½����
	char sex[4];              //�û��Ա�
	int StuId;             //�û�ID
	struct Student *next;
}student;

//ͼ�������Ϣ�ṹ��
typedef struct Book
{
	int bookId;           //ͼ����
	char bookType[20];        //ͼ������
	char bookName[20];        //ͼ������
	int booknum;          //�������
	struct Book *next;

}book;


//����ͼ�������Ϣ�ṹ��
typedef struct SendBook
{
	int SendBookID;       //�����鼮���
	int SendStuID;        //����ѧ��ID
	int SendNum;          //�����鼮����
	struct SendBook *next;
}sendbook;
 


//����û���Ϣ
void AddStudentinfor(student *stu);



//��ѯ�û���Ϣ���Թ���Ա��ݲ�ѯ��
void SelectStudentinfoForMan(student *stu);

//�޸��û���Ϣ
int ModiStudentinfor(student *stu);

//ɾ���û���Ϣ
int DeleteStudent(student *stu);

//��ѯͼ����Ϣ
void SelectBookinfor(book *bk);

//����ͼ��
int BroBook(student stu, sendbook *sdbk);
//ͼ��黹
int ReturnBook(sendbook *sdbk, book *bk, student *stu);

//�޸�ͼ����Ϣ
void ModiBookinfor(book *bt);

//ɾ��ͼ����Ϣ
int DeleteBook(book *bk);

//��½����
int loginCode(student &stu);//�����ѧ������������ṹ���1��������ǹ���Ա��ֻ����2,ʧ�ܷ���-1

//ע�����
int registerCode(student &stu);//����ע��ɹ����  1Ϊ�ɹ� -1Ϊʧ��

//��ѯ�ѽ���ͼ��
void SelectBroBook(book *sdbk, student stu);



//���������ӵĺ��� 

//ͼ������
void AddBookinfor(book *bk);
void SelectBroBook(sendbook *sdbk);


#endif


