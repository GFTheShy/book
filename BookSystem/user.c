#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "user.h"
#include "file.h"
#include "admin.h"


Unode *user_login(Unode *Uhead)
{
    printf("\n=======登录界面========\n");
    char t_name[128],t_pass[128];  //输入的用户名和密码
    printf("请输入用户名：");
    scanf("%s",t_name);
    printf("请输入密码：");
    scanf("%s",t_pass);

    Unode *temp=Uhead->next;
    while(temp!=NULL)
    {
        if(strcmp(temp->data.name,t_name)==0 && strcmp(temp->data.password,t_pass)==0)
            return temp;
        temp=temp->next;
    }
    return NULL;
}

void user_money(Unode *user_temp)  //氪金功能
{
    printf("\n￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥\n");
    printf("￥￥￥￥￥￥￥￥欢迎来到充值系统￥￥￥￥￥￥￥￥\n");
    printf("￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥\n");
    printf("￥￥￥￥￥￥￥￥你想要氪多少价位￥￥￥￥￥￥￥￥\n");
    printf("￥￥  10   50  100  200  500  700  1000  2000 ￥\n");
    
    printf("\n选择你的价位(输入0退出)：");
    int money;
    scanf("%d",&money);
    switch(money)  //根据不同价位充值，充值成功打印界面提示用户
    {
        case 0:return;
        case 10:user_temp->data.money+=10;print_ui("./ui/money");break;
        case 50:user_temp->data.money+=50;print_ui("./ui/money");break;
        case 100:user_temp->data.money+=100;print_ui("./ui/money");break;
        case 200:user_temp->data.money+=200;print_ui("./ui/money");break;
        case 500:user_temp->data.money+=500;print_ui("./ui/money");break;
        case 700:user_temp->data.money+=700;print_ui("./ui/money");break;
        case 1000:user_temp->data.money+=1000;print_ui("./ui/money");break;
        case 2000:user_temp->data.money+=2000;print_ui("./ui/money");break;
        default:printf("暂时不支持该价位！\n");return;
    }

    
    if(user_temp->data.money>=1000)
    {
        user_temp->data.power=3;  //如果用户充值1000 自动升级为王者会员
        user_temp->data.book_max=MAX_3;  //最大借书量也为王者会员
    }
    else if(user_temp->data.money>=200) 
    {
        user_temp->data.power=2;  //如果用户充值200 自动升级为铂金会员
        user_temp->data.book_max=MAX_2;  //最大借书量也为铂金会员
    }
}

void user_disp_book(Bnode *Bhead)  //列出图书
{
    Bnode *temp=Bhead->next;
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    while(temp!=NULL)
    {
        printf("书号：%d 书名：《%s》 作者：%s 出版社：%s 库存%d\n",temp->data.id,temp->data.book_name,
                temp->data.book_writer,temp->data.book_publish,temp->data.book_count);
        temp=temp->next;
    }
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}


void user_book_look(Bnode *Bhead)
{
    printf("\n--------------\n");
    printf("1 书名查找\n");
    printf("2 作者查找\n");
    printf("3 退出\n");
    printf("--------------\n");
    int i,flag=0;  //flag用来判断是否有这本书
    scanf("%d",&i);
    char name[128];
    if(i==1)
    {
        printf("输入你想要查找的书名：");
        scanf("%s",name);;
        Bnode *temp=Bhead->next;
        while(temp!=NULL)
        {
            if(strcmp(temp->data.book_name,name)==0)
            {
                printf("书号：%d 书名：《%s》 作者：%s 出版社：%s 库存%d\n",temp->data.id,temp->data.book_name,
                temp->data.book_writer,temp->data.book_publish,temp->data.book_count);
                flag++;
            }
            temp=temp->next;
        }
        if(flag==0) printf("图书馆暂时没有该书！\n");
    }
    else if(i==2)
    {
        printf("输入你想要查找的作者：");
        scanf("%s",name);
        Bnode *temp=Bhead->next;
        while(temp!=NULL)
        {
            if(strcmp(temp->data.book_writer,name)==0)
            {
                printf("书号：%d 书名：《%s》 作者：%s 出版社：%s 库存%d\n",temp->data.id,temp->data.book_name,
                temp->data.book_writer,temp->data.book_publish,temp->data.book_count);
                flag++;
            }
            temp=temp->next;
        }
        if(flag==0) printf("图书馆暂时没有该作者的书！\n");
    }
    else
        return;
}

void user_book_lend(Bnode *Bhead,Unode *Utemp) 
{
    printf("\n--------------\n");
    printf("借书功能：\n");
    printf("--------------\n");
    printf("输入借书的书名和作者：\n");
    char name[128],writer[128];
    scanf("%s %s",name,writer);

    Bnode *temp=Bhead->next;
    while(temp!=NULL)
    {
        if(strcmp(temp->data.book_writer,writer)==0 && strcmp(temp->data.book_name,name)==0)
        {
            if(temp->data.book_count>0 && Utemp->data.book_count<Utemp->data.book_max) 
                {
                    temp->data.book_count--;  //书库存--
                    Utemp->data.borrow[Utemp->data.book_count]=temp->data;  //把借的书存到用户信息
                    Utemp->data.book_count++;  //用户借书++
                    printf("借书成功\n");
                    return;
                }  //找到这本书了，让书库存减少1
            else 
                {
                    printf("借书失败！\n");
                    return;
                }
        }
        temp=temp->next;
    }
    printf("图书馆暂时没有该书！\n");
    return;
}

void user_book_return(Bnode *Bhead,Unode *Utemp)
{
    printf("\n--------------\n");
    printf("还书功能：\n");
    printf("--------------\n");
    printf("输入还书的书名,作者\n");
    char name[128],writer[128];
    scanf("%s %s",name,writer);

    int i;
    for(i=0;i<Utemp->data.book_count;i++) //找到用户借的书
        {
            if(strcmp(Utemp->data.borrow[i].book_name,name)==0 && strcmp(Utemp->data.borrow[i].book_writer,writer)==0)  
            {
                break;
            }
        }
    if(i<Utemp->data.book_count)
        {
            Bnode *temp=Bhead->next;
            while(temp!=NULL)
            {
                if(strcmp(temp->data.book_name,name)==0)
                {
                    temp->data.book_count++;  //书库存++

                    //删除用户借书信息
                    for(int j=i;j<Utemp->data.book_count-1;j++)
                    {
                        Utemp->data.borrow[j]=Utemp->data.borrow[j+1];
                    }
                    Utemp->data.book_count--;  //用户借书量--

                    printf("还书成功\n");
                    return; //找到这本书了，让书库存增加1
                }
                temp=temp->next;
            }
            printf("图书馆没有该书！还不支持做慈善\n");
        }
    else
        printf("你没有借这本书！\n");
}

void user_per(Unode *user_temp)
{
    printf("\n===============个人信息界面===============\n");
    printf("用户名:%s  ",user_temp->data.name);
    if(user_temp->data.power==1) printf("(青铜会员-_-  最大借书量为:%d)\n",user_temp->data.book_max);
    else if(user_temp->data.power==2) printf("(亲爱的铂金会员=_= 最大借书量为:%d)\n",user_temp->data.book_max);
    else if(user_temp->data.power==3) printf("(尊贵的王者会员^-^  最大借书量为:%d)\n",user_temp->data.book_max);
    printf("氪金：%d元,少年你想变强吗，那就氪吧！\n",user_temp->data.money);
    printf("借书量:%d\n",user_temp->data.book_count);
    if(user_temp->data.book_count>0)
        {
            printf("所借书籍：\n");
            printf("书名\t作者\n");
            for(int i=0;i<user_temp->data.book_count;i++)
                {
                    printf("《%s》 %s\n",user_temp->data.borrow[i].book_name,user_temp->data.borrow[i].book_writer);
                }
        }
    printf("==========================================\n");
}

void user_password(Unode *user_temp)  //修改密码
{
    printf("\n--------------\n");
    printf("---修改密码---\n");
    printf("--------------\n");

    while(1)
    {
        char pass1[128],pass2[128];

        printf("输入你的原密码：");
        scanf("%s",pass1);

        printf("请再次输入你的密码：");
        scanf("%s",pass2);

        if(strcmp(pass1,pass2)==0)   //判断两次密码是否输入正确
        {
            if(strcmp(pass1,user_temp->data.password)==0)  //判断密码是否正确
            {
                printf("修改后的密码：");
                scanf("%s",user_temp->data.password);
                printf("修改成功！\n");
                return;
            }
            else
                printf("密码错误！\n");
        }
        else
            printf("两次输入不一样！\n");
    }
}