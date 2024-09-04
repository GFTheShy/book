#ifndef FILE_H
#define FILE_H

typedef struct UserNode Unode;  //申明结构体定义  
typedef struct BookNode Bnode;

typedef struct BOOK{   //存储图书信息
    int id;   //书号
    char book_name[128];  //书名
    char book_writer[128];   //作者
    char book_publish[128];  //出版社
    int book_count; //库存量
}book;

typedef struct BookNode  //构建链表结点信息
{
    book data;
    struct BookNode *next;
}Bnode;

void print_ui(char *fpname);  //输出界面

Unode *readUser();  //加载用户信息

void writeUser(Unode *Uhead);  //保存用户信息

void user_register(Unode *Uhead); //用户注册

Bnode *readBook();  //加载图书信息

void writeBook(Bnode *Bhead);  //保存图书信息

#endif