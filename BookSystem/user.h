#ifndef USER_H
#define USER_H


//不同用户的借书最大数量
#define MAX_0 0   //黑户
#define MAX_1 10  //青铜用户
#define MAX_2 20  //铂金用户
#define MAX_3 50  //王者用户

#include "file.h"
typedef struct BookNode Bnode;
typedef struct BOOK book;

typedef struct USER{   //存储用户信息
    char name[128];   //用户名
    char password[128];  //密码
    int book_count;   //所借书的数量
    int book_max;  //能借的最大的书的数量
    int power;  //权限
    int money;  //氪金升级会员
    book borrow[MAX_3];  //借的书
}user;

typedef struct UserNode  //构建链表结点信息
{
    user data;
    struct UserNode *next;
}Unode;

Unode *user_login(Unode *Uhead);  //用户登陆

void user_money(Unode *user_temp);  //氪金功能

void user_disp_book(Bnode *Bhead);  //列出图书

void user_book_look(Bnode *Bhead); //用户查询书籍信息

void user_book_lend(Bnode *Bhead,Unode *Utemp);  //用户借书

void user_book_return(Bnode *Bhead,Unode *Utemp);  //用户还书

void user_per(Unode *user_temp);  //用户个人信息

void user_password(Unode *user_temp);  //修改密码


#endif