#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "user.h"
#include "admin.h"
#include "file.h"

void fun_user();  //进入普通用户界面

void fun_admin();  //进入管理员用户

void fun_admin_book();  //管理员管理图书

void fun_admin_user();  //管理员管理用户


int main()
{
    int choice;
    while(1)
    {
        print_ui("./ui/main");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                fun_user();
                break;
            case 2:
                fun_admin();
                break;
            default:
                exit(0);
        }
    }
    return 0;
}

void fun_user()
{
    Bnode *Bhead=readBook();  //加载图书信息
    Unode *Uhead = readUser();  //加载用户信息
    Unode *user_temp=NULL;  //记录当前登陆的用户
    int choice;
    while(1)
    {
        print_ui("./ui/user_main");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                user_temp=user_login(Uhead);  //保存登陆的用户
                if(user_temp!=NULL && user_temp->data.power!=0)  //登陆成功 必须不是黑名单
                {
                    int choice;
                    while(1)
                    {
                        print_ui("./ui/user_login");
                        scanf("%d",&choice);
                        switch(choice)
                            {
                                case 0:
                                    user_money(user_temp);
                                    break;
                                case 1:
                                    user_disp_book(Bhead);
                                    break;
                                case 2:
                                    user_book_look(Bhead);
                                    break;
                                case 3:
                                    user_book_lend(Bhead,user_temp);
                                    break;
                                case 4:
                                    if(user_temp->data.book_count>0)  user_book_return(Bhead,user_temp);
                                    //必须用户借了书才可以还书
                                    else
                                        printf("你还没借书勒\n");
                                    break;
                                case 5:
                                    user_per(user_temp);
                                    break;
                                case 6:
                                    user_password(user_temp);
                                default:
                                    writeUser(Uhead);  //保存用户信息
                                    writeBook(Bhead);  //保存图书信息
                                    return;
                            }
                    }
                }
                else
                    printf("登陆失败！\n");
                break;
            case 2:
                user_register(Uhead);
                return;
            default:
                return;
        }
    }
}

void fun_admin()
{
    int choice;
    while(1)
    {
        print_ui("./ui/admin_main");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                if(admin_login()==1)  //登陆成功 返回值为1
                {
                    int choice;
                    while(1)
                    {
                        print_ui("./ui/admin_login");
                        scanf("%d",&choice);
                        switch(choice)
                            {
                                case 1:
                                    fun_admin_book();
                                    break;
                                case 2:
                                    fun_admin_user();
                                    break;
                                default:
                                    return;
                            }
                    }
                }
                else
                    printf("登陆失败！\n");
                break;
            default:
                return;
        }
    }
}

void fun_admin_book()
{
    Bnode *Bhead=readBook();  //加载图书信息
    int choice;
    while(1)
    {
        print_ui("./ui/fun_admin_book");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                admin_disp_book(Bhead);
                break;
            case 2:
                admin_find_book(Bhead);
                break;
            case 3:
                admin_add_book(Bhead);
                break;
            case 4:
                admin_del_book(Bhead);
                break;
            case 5:
                admin_change_book(Bhead);
                break;
            default:
                writeBook(Bhead);  //保存图书信息
                return;
        }
    }
}

void fun_admin_user()
{
    Unode *Uhead = readUser();  //加载用户信息
    int choice;
    while(1)
    {
        print_ui("./ui/fun_admin_user");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                admin_disp_user(Uhead);
                break;
            case 2:
                admin_del_user(Uhead);
                break;
            case 3:
                admin_change_user(Uhead);
                break;
            case 4:
                admin_block_user(Uhead);
                break;
            default:
                writeUser(Uhead);  //保存用户信息
                return;
        }
    }
}