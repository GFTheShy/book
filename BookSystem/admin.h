#ifndef ADMIN_H
#define ADMIN_H

#define AdminName "lcghs"  //管理员用户名
#define AdminpassWord  "lcghs"  //管理员密码


#include "user.h"
#include "file.h"
typedef struct BookNode Bnode; ////申明结构体定义 
typedef struct UserNode Unode;


int admin_login();  //管理员登陆


void admin_disp_book(Bnode *Bhead);  //列出图书

void admin_find_book(Bnode *Bhead);  //查询图书

void admin_add_book(Bnode *Bhead);  //录入图书

void admin_del_book(Bnode *Bhead);  //删除图书

void admin_change_book(Bnode *Bhead);  //更新图书信息


void admin_disp_user(Unode *Uhead);  //列出所有用户

void admin_del_user(Unode *Uhead);  //删除用户

void admin_change_user(Unode *Uhead);  //管理用户会员

void admin_block_user(Unode *Uhead);  //拉黑用户

#endif