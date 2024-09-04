#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "file.h"
#include "user.h"
#include "admin.h"

void print_ui(char *fname)
{
    FILE *fp=fopen(fname,"r");
    if(fp==NULL)
    {
        printf("文件打开失败\n");
        return;
    }

    char s[1024];
    while(fgets(s,1024,fp)!=NULL)
    {
        fputs(s,stdout);
    }

    fclose(fp);
}

Unode *readUser()
{
    Unode *head=(Unode *)malloc(sizeof(Unode)); //创建头结点
    head->next=NULL;

    FILE *fp=fopen("user_per","r");
    if(fp==NULL)
    {
        printf("文件打开失败\n");
        return NULL;
    }

    user new;
    while(fscanf(fp,"%127[^,],%127[^,],%d,%d,%d,%d\n",new.name,new.password,
                            &new.book_count,&new.book_max,&new.power,&new.money)!=EOF)  //读取文件，并且插入链表
    {
        for(int i=0;i<new.book_count;i++)
        {
            fscanf(fp,"%d,%127[^,],%127[^,],%127[^,],%d\n",&new.borrow[i].id,new.borrow[i].book_name,
                        new.borrow[i].book_writer,new.borrow[i].book_publish,&new.borrow[i].book_count);
        }
        Unode *temp=(Unode *)malloc(sizeof(Unode));
        temp->data=new;
        temp->next=head->next;
        head->next=temp;
    }

    fclose(fp);
    return head;
}

void writeUser(Unode *Uhead)
{
    FILE *fp=fopen("user_per","w");
    if(fp==NULL)
    {
        printf("文件打开失败\n");
        return;
    }

    Unode *temp=Uhead->next;
    Unode *freetemp=NULL;  //保存结点用来释放
    while(temp!=NULL)  //把链表写入文件
    {
        fprintf(fp,"%s,%s,%d,%d,%d,%d\n",temp->data.name,temp->data.password,temp->data.book_count,
                                                            temp->data.book_max,temp->data.power,temp->data.money);
        for(int i=0;i<temp->data.book_count;i++)
        {
            fprintf(fp,"%d,%s,%s,%s,%d\n",temp->data.borrow[i].id,temp->data.borrow[i].book_name,
                        temp->data.borrow[i].book_writer,temp->data.borrow[i].book_publish,temp->data.borrow[i].book_count);
        }
        freetemp=temp;
        temp=temp->next;
        free(freetemp);  //释放结点
    }
    free(Uhead);  //释放头结点
    fclose(fp);
}

void user_register(Unode *Uhead)
{
    FILE *fp=fopen("user_per","a");
    if(fp==NULL)
    {
        printf("文件打开失败\n");
        return;
    }

    printf("\n=======注册界面========\n");
    user new;
    while(1)
    {
        char s[128];
        int flag=1;
        printf("你想要什么用户名：");
        scanf("%127s",s);

        Unode *temp=Uhead->next;
        while(temp!=NULL)    //如果已经注册过的用户名，则重新输入用户名进行注册
        {
            if(strcmp(s,temp->data.name)==0)
            {
                printf("用户名已被注册，重新输入用户名\n");
                flag=0;
                break;
            }
            temp=temp->next;
        }
        if(flag==1)
        {
            printf("输入密码：");
            scanf("%127s",new.password);
            //0是代表用户借书的数量，默认为0，max_1是青铜用户，1代表权限 0代表还没冲钱
            fprintf(fp,"%s,%s,%d,%d,%d,%d\n",s,new.password,0,MAX_1,1,0);  
            
            printf("注册成功！\n");
            break;
        }
    }

    fclose(fp);
}

Bnode *readBook()
{
    Bnode *head=(Bnode *)malloc(sizeof(Bnode)); //创建头结点
    head->next=NULL;

    FILE *fp=fopen("book","r");
    if(fp==NULL)
    {
        printf("文件打开失败\n");
        free(head);
        return NULL;
    }

    book new;
    while(fscanf(fp,"%d,%127[^,],%127[^,],%127[^,],%d\n",&new.id,new.book_name,new.book_writer,
                                new.book_publish,&new.book_count)!=EOF)  //读取文件，并且插入链表
    {
        Bnode *temp=(Bnode *)malloc(sizeof(Bnode));
        temp->data=new;
        temp->next=head->next;
        head->next=temp;
    }

    fclose(fp);
    return head;
}

void writeBook(Bnode *Bhead)
{
    FILE *fp=fopen("book","w");
    if(fp==NULL)
    {
        printf("文件打开失败\n");
        return;
    }

    Bnode *temp=Bhead->next;
    Bnode *freetemp=NULL;  //保存结点用来释放
    while(temp!=NULL)  //把链表写入文件
    {
        fprintf(fp,"%d,%s,%s,%s,%d\n",temp->data.id,temp->data.book_name,temp->data.book_writer,
                                temp->data.book_publish,temp->data.book_count);
        freetemp=temp;
        temp=temp->next;
        free(freetemp);  //释放结点
    }
    free(Bhead);  //释放头结点
    fclose(fp);
}