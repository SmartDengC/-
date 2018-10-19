#pragma once
#ifndef _BOOKSYSTEM_H_    
#define _BOOKSYSTEM_H_  
#include<mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <comdef.h>  // wchar_t转char 
#define STUDENTNUM 100
#define BOOKNUM 100
#define SENDBOOKNUM 100
#pragma comment(lib, "libmysql.lib")


//用户基本资料结构体
typedef struct Student
{
	char name[20];             //用户姓名
	int password;          //登陆密码
	char sex[4];              //用户性别
	int StuId;             //用户ID
	struct Student *next;
}student;

//图书基本信息结构体
typedef struct Book
{
	int bookId;           //图书编号
	char bookType[20];        //图书类型
	char bookName[20];        //图书名称
	int booknum;          //库存数量
	struct Book *next;

}book;


//借阅图书基本信息结构体
typedef struct SendBook
{
	int SendBookID;       //借阅书籍编号
	int SendStuID;        //借阅学生ID
	int SendNum;          //借阅书籍数量
	struct SendBook *next;
}sendbook;
 


//添加用户信息
void AddStudentinfor(student *stu);



//查询用户信息（以管理员身份查询）
void SelectStudentinfoForMan(student *stu);

//修改用户信息
int ModiStudentinfor(student *stu);

//删除用户信息
int DeleteStudent(student *stu);

//查询图书信息
void SelectBookinfor(book *bk);

//借阅图书
int BroBook(student stu, sendbook *sdbk);
//图书归还
int ReturnBook(sendbook *sdbk, book *bk, student *stu);

//修改图书信息
void ModiBookinfor(book *bt);

//删除图书信息
int DeleteBook(book *bk);

//登陆操作
int loginCode(student &stu);//如果是学生，返回这个结构体和1，，如果是管理员就只返回2,失败返回-1

//注册操作
int registerCode(student &stu);//返回注册成功与否  1为成功 -1为失败

//查询已借阅图书
void SelectBroBook(book *sdbk, student stu);



//这里是增加的函数 

//图书增加
void AddBookinfor(book *bk);
void SelectBroBook(sendbook *sdbk);


#endif


