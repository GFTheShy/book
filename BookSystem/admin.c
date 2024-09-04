#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "admin.h"
#include "user.h"
#include "file.h"

int admin_login()
{
    printf("\n$$$$$$$登录界面$$$$$$$$\n");
    char t_name[128],t_pass[128];  //输入的用户名和密码
    printf("请输入管理员用户名：");
    scanf("%s",t_name);
    printf("请输入密码：");
    scanf("%s",t_pass);

    if(strcmp(t_name,AdminName)==0 && strcmp(t_pass,AdminpassWord)==0)
        return 1;
    return 0;
}

void admin_disp_book(Bnode *Bhead)  //列出图书
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

void admin_find_book(Bnode *Bhead)  //查询图书
{
    printf("\n$$$$$$$$$$$$$$\n");
    printf("1 书名查找\n");
    printf("2 作者查找\n");
    printf("3 退出\n");
    printf("$$$$$$$$$$$$$$\n");
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

void admin_add_book(Bnode *Bhead)  //录入图书
{
    printf("\n$$$$$$$$$$$$$$\n");
    printf("1 录入新书\n");
    printf("2 录入旧书\n");
    printf("3 不录了\n");
    printf("$$$$$$$$$$$$$$\n");
    int flag;
    scanf("%d",&flag);
    if(flag==1)
    {
        int i,n;  //n为要录入不同书的数量
        book new;
        printf("输入录入几本不同的新书：\n");
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            printf("输入新书的书号，书名，作者，出版社，库存：");
            scanf("%d %127s %127s %127s %d",&new.id,new.book_name,new.book_writer,new.book_publish,&new.book_count);
            
            // 创建新节点并插入到链表头部
            Bnode *temp=(Bnode *)malloc(sizeof(Bnode));
            temp->data=new;
            temp->next=Bhead->next;
            Bhead->next=temp;
            printf("录入成功！\n");
        }
    }
    else if(flag==2)
    {
        int i,n;  //n为要录入不同书的数量
        book new;
        printf("输入录入几本不同的旧书：\n");
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            printf("输入旧书书的书名，作者,新增的库存：");
            scanf("%127s %127s %d",new.book_name,new.book_writer,&new.book_count);

            // 遍历链表查找是否有匹配的旧书
            Bnode *temp=Bhead->next;
            while(temp!=NULL)
            {
                if(strcmp(temp->data.book_writer,new.book_writer)==0 && strcmp(temp->data.book_name,new.book_name)==0)
                {
                    temp->data.book_count += new.book_count;
                    printf("录入成功！\n");
                    break;
                }
                temp=temp->next;
            }
            if(temp==NULL) printf("录入失败！图书馆没找到这本书！\n");
        }
    }
    else
        return;
}

void admin_del_book(Bnode *Bhead)  //删除图书
{
    printf("\n===========删除功能==============\n");
    int i,n;  //n为要删除不同书的数量
    printf("输入删除几本不同的新书(输入非正数退出)：\n");
    scanf("%d",&n);
    if(n>0)
    {
        for(i=0;i<n;i++)
        {
            char name[128]={0},writer[128]={0};
            printf("输入要删除的书名，作者：");
            scanf("%127s %127s",name,writer);
            
            // 遍历链表查找是否有匹配的旧书
            Bnode *temp=Bhead->next;
            Bnode *prev=Bhead;
            while(temp!=NULL)
            {
                if(strcmp(temp->data.book_writer,writer)==0 && strcmp(temp->data.book_name,name)==0)
                {
                    prev->next=temp->next;
                    free(temp);
                    printf("删除成功！\n");
                    break;
                }
                prev=temp;
                temp=temp->next;
            }
            if(temp==NULL) printf("删除失败！图书馆没找到这本书！\n");
        }
    }
}

void admin_change_book(Bnode *Bhead)  //更新图书信息
{
    printf("\n$$$$$$$$$$$$$$\n");
    printf("1 根据书号修改图书信息\n");
    printf("2 根据书名和作者修改图书信息\n");
    printf("$$$$$$$$$$$$$$\n");
    int flag;
    scanf("%d",&flag);
    if(flag==1)
    {
        int id;
        printf("输入书号:");
        scanf("%d",&id);

        Bnode *temp=Bhead->next;
        while(temp!=NULL)
        {
            if(id==temp->data.id)
            {
                printf("当前操作的图书： ");
                printf("书号：%d 书名：《%s》 作者：%s 出版社：%s 库存%d\n",temp->data.id,temp->data.book_name,
                temp->data.book_writer,temp->data.book_publish,temp->data.book_count);

                printf("\n||||||||||||||\n");
                printf("1 修改书号\n");
                printf("2 修改书名\n");
                printf("3 修改作者\n");
                printf("4 修改出版社\n");
                printf("5 修改库存\n");
                printf("6 全都修改\n");
                printf("7 不改了\n");
                printf("||||||||||||||\n");

                int choice;
                scanf("%d",&choice);
                switch(choice)
                {
                    case 1:
                        printf("输入新的书号：");
                        scanf("%d",&temp->data.id);
                        printf("修改成功！\n");
                        break;
                    case 2:
                        printf("输入新的书名：");
                        scanf("%127s",temp->data.book_name);
                        printf("修改成功！\n");
                        break;
                    case 3:
                        printf("输入新的作者：");
                        scanf("%127s",temp->data.book_writer);
                        printf("修改成功！\n");
                        break;
                    case 4:
                        printf("输入新的出版社：");
                        scanf("%127s",temp->data.book_publish);
                        printf("修改成功！\n");
                        break;
                    case 5:
                        printf("输入新的库存：");
                        scanf("%d",&temp->data.book_count);
                        printf("修改成功！\n");
                        break;
                    case 6:
                        printf("输入新书的书号，书名，作者，出版社，库存：");
                        scanf("%d %127s %127s %127s %d",&temp->data.id,temp->data.book_name,temp->data.book_writer,
                                                                temp->data.book_publish,&temp->data.book_count);
                        printf("修改成功！\n");
                        break;
                    default:
                        return;
                }
                break;
            }
            temp=temp->next;
        }
        if(temp==NULL) printf("修改失败！图书馆没找到这本书！\n");
    }
    else if(flag==2)
    {
        char name[128]={0},writer[128]={0};
        printf("输入要修改的书名，作者：");
        scanf("%127s %127s",name,writer);

        Bnode *temp=Bhead->next;
        while(temp!=NULL)
        {
            if(strcmp(temp->data.book_writer,writer)==0 && strcmp(temp->data.book_name,name)==0)
            {
                printf("||||||||||||||\n");
                printf("1 修改书号\n");
                printf("2 修改书名\n");
                printf("3 修改作者\n");
                printf("4 修改出版社\n");
                printf("5 修改库存\n");
                printf("6 全都修改\n");
                printf("7 不改了\n");
                printf("||||||||||||||\n");

                int choice;
                scanf("%d",&choice);
                switch(choice)
                {
                    case 1:
                        printf("输入新的书号：");
                        scanf("%d",&temp->data.id);
                        printf("修改成功！\n");
                        break;
                    case 2:
                        printf("输入新的书名：");
                        scanf("%127s",temp->data.book_name);
                        printf("修改成功！\n");
                        break;
                    case 3:
                        printf("输入新的作者：");
                        scanf("%127s",temp->data.book_writer);
                        printf("修改成功！\n");
                        break;
                    case 4:
                        printf("输入新的出版社：");
                        scanf("%127s",temp->data.book_publish);
                        printf("修改成功！\n");
                        break;
                    case 5:
                        printf("输入新的库存：");
                        scanf("%d",&temp->data.book_count);
                        printf("修改成功！\n");
                        break;
                    case 6:
                        printf("输入新书的书号，书名，作者，出版社，库存：");
                        scanf("%d %127s %127s %127s %d",&temp->data.id,temp->data.book_name,temp->data.book_writer,
                                                                temp->data.book_publish,&temp->data.book_count);
                        printf("修改成功！\n");
                        break;
                    default:
                        return;
                }
                break;
            }
            temp=temp->next;
        }
        if(temp==NULL) printf("修改失败！图书馆没找到这本书！\n");
    }
    else
        return;
}

void admin_disp_user(Unode *Uhead)  //列出所有用户
{
    Unode *temp=Uhead->next;
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    while(temp!=NULL)
    {
        printf("用户名:%s  ",temp->data.name);
        if(temp->data.power==1) printf("青铜会员\t");
        else if(temp->data.power==2) printf("铂金会员\t");
        else if(temp->data.power==3) printf("王者会员\t");
        else printf("黑名单\t");
        printf("氪金：%d元 ",temp->data.money);
        printf("借书量:%d\n",temp->data.book_count);
        if(temp->data.book_count>0)
            {
                printf("所借书籍：");
                for(int i=0;i<temp->data.book_count;i++)
                    {
                        printf("《%s》 ",temp->data.borrow[i].book_name);
                    }
                printf("\n");
            }
        printf("\n");
        temp=temp->next;
    }
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}

void admin_del_user(Unode *Uhead)  //删除用户
{
    char name[128];
    printf("\n$$$$$$$删除界面$$$$$$$$\n");
    printf("输入你要删除的用户名：");
    scanf("%s",name);

    Unode *temp=Uhead->next;
    Unode *prev=Uhead;
    while(temp!=NULL)
    {
        if(strcmp(temp->data.name,name)==0)
        {
            prev->next=temp->next;
            free(temp);
            printf("删除成功！\n");
            return;
        }
        prev=temp;
        temp=temp->next;
    }
    if(temp==NULL) printf("删除失败！\n");
}

void admin_change_user(Unode *Uhead)  //管理用户会员
{
    printf("\n$$$$$$$管理界面$$$$$$$$\n");
    printf("输入你要修改的用户名：");
    char name[128];
    scanf("%s",name);

    Unode *temp=Uhead->next;
    while(temp!=NULL)
    {
        if(strcmp(temp->data.name,name)==0)  //找到要修改的用户
        {
            printf("[* 当前操作用户名：%s 权限：%d 累计充值：%d *]\n",temp->data.name,temp->data.power,temp->data.money);

            printf("\n￥￥修改￥￥\n");
            printf("1 修改会员种类\n");
            printf("2 修改累计充值\n");
            printf("3 取消操作\n");
            printf("请选择功能：");
            int i;
            scanf("%d",&i);

            if(i==1)
            {
                printf("×××××××××××××××××\n");
                printf("1 青铜会员 2 铂金会员 3 王者会员\n");
                printf("输入修改后的权限：");
                int n;
                scanf("%d",&n);
                //n必须是1 2 3 而且不可以和之前一样
                if(n>=1 && n<=3 && n!=temp->data.power)
                 {
                    temp->data.power=n;
                    printf("修改成功！\n");
                    if(temp->data.power==1) temp->data.book_max=MAX_1;  //修改会员后 最大借书也修改为对应的
                    else if(temp->data.power==2) temp->data.book_max=MAX_2;
                    else if(temp->data.power==3) temp->data.book_max=MAX_3;
                    return;
                }
                else printf("修改失败！\n");
                return;
            }
            else if(i==2)
            {
                printf("×××××××××××××××××\n");
                printf("输入修改后的充值金额：");
                int n;
                scanf("%d",&n);
                if(n>=0)
                {
                    temp->data.money=n;
                    printf("修改成功！\n");
                    return;
                }
                else
                {
                    printf("输入的金额不能是负数！\n");
                    return;
                }
            }
            else
                return;
        }
        temp=temp->next;
    }
    if(temp==NULL) printf("没有该用户！\n");
}

void admin_block_user(Unode *Uhead)  //拉黑用户
{
    printf("\n$$$$$$$拉黑界面$$$$$$$$\n");
    printf("输入你要拉黑的用户名：");
    char name[128];
    scanf("%s",name);

    Unode *temp=Uhead->next;
    while(temp!=NULL)
    {
        if(strcmp(temp->data.name,name)==0)  //找到要修改的用户
            {   
                printf("[* 当前操作用户名：%s 权限：%d 累计充值：%d *]\n",temp->data.name,temp->data.power,temp->data.money);
                temp->data.power=0;
                printf("拉黑成功！\n");
                return;
            }
        temp=temp->next;
    }
    if(temp==NULL) printf("没有该用户！\n");
}