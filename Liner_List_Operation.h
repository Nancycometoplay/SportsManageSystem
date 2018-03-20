//
// Created by Nancy on 18/3/19.
//

#ifndef SPORTSYSTEM_2_LINER_LIST_OPERATION_H
#define SPORTSYSTEM_2_LINER_LIST_OPERATION_H

#endif //SPORTSYSTEM_2_LINER_LIST_OPERATION_H


//#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_SIZE 100
//using namespace std;

int findtemp=0;


typedef struct SqList{
    struct athletes *elem;  //根据程序来改变
    int length;
};

struct athletes{
    char name[20];
    char id[20];
    char gender[10];
    char grade[10];
    char college[20]; //学院
    // char department[20];
    char major[20];   //专业
    char preteam[10]; //代表队
    // char number[10];
    // char score[10];
};


//int Init_List(struct SqList *L);
//int Insert_List(struct SqList *L,int ele,int num);
//int Delete_List(struct SqList *L,int num);
//void Display_List(struct SqList L);
//int Append_List(struct SqList *L,int ele);
//int Chanege_List(struct SqList *L,int ele,int num);
//int Find_List(struct SqList *L,int num);


//int main()
//{
//    struct SqList L1;
//    int a;
//    Init_List(&L1);
//    cout<<"---append---"<<endl;
//    cout<<"---delete---"<<endl;
//    cout<<"---change---"<<endl;
//    cout<<"--- find ---"<<endl;
//    cout<<"---insert---"<<endl;
//    cout<<"---display---"<<endl;
//    while(1){
//        scanf("%d",&a);
//        switch(a){
//            case 1:
//                Append_List(&L1,20);
//                break;
//            case 2:
//                Delete_List(&L1,2);
//                break;
//            case 3:
//                Chanege_List(&L1,2,2);
//                break;
//            case 4:
//                Find_List(&L1,2);
//                break;
//            case 5:
//                Insert_List(&L1,9,3);
//                break;
//            case 6:
//                Display_List(L1);
//                break;
//        }
//    }
//    return 0;
//}

/*=====初始化=====*/
//int Init_List(struct athletes athle[],int number){
//    struct SqList *L;
//    L->elem=NULL;
//    L->length=0;
//
//    L->elem = athle;   //不知道对不对
//    if(!L->elem) {return -1;}
//    L->length = number;
//    for(int i=0;i<L->length;i++){
//        L->elem[i]=athle[i] ;
//    }
//    return 1;
//}

/*=====追加=====*/
int Append_List(struct athletes athle[],int number, struct athletes addAth){
    int i,j;
    struct SqList *L;
    L->elem=NULL;
    L->length=0;

    L->elem = athle;   //不知道对不对
    if(!L->elem) {return -1;}
    L->length = number;
    for(int i=0;i<L->length;i++){
        L->elem[i]=athle[i] ;
    }
    L->length++;
    L->elem[L->length-1] = addAth;

    //将athle清空
    for(int j=0;j<number;j++)
    {
        memset(&athle[j],0,sizeof(struct athletes));
    }

    //传回athle[]
    for(int i=0;i<L->length;i++){
        athle[i]=L->elem[i];
    }
}


/*=====删除=====*/           //whereDelete就是下标,删除就是后面的移到前面去
void Delete_List(struct athletes athle[],int number,struct athletes deleteAth){
    int whereDelete=0;  //删除操作的下标
    for(int i=0;i<=number;i++)
    {
        if(athle[i].id==deleteAth.id)  //找到对应的i
        {
            whereDelete=i;
            break;
        }
    }

    for(int i=whereDelete;i<number;i++)
    {
        athle[i]=athle[i+1];
    }
    //删除最后一个元素
    struct athletes *p;
    *p=athle[number];
    p=NULL;
    printf("删除成功");



//    printf("delete...\n");
//    int i,j;
//    struct SqList *L;
//    L->elem=NULL;
//    L->length=0;
//
//    L->elem = athle;   //不知道对不对
//    if(!L->elem) {return -1;}
//    L->length = number;  //总共有多少个元素
//    for(int i=0;i<L->length;i++){
//        L->elem[i]=athle[i] ;
//    }
//
//    for(i=whereDelete;i<L->length-1;i++){   // 有问题
//        L->elem[i]=L->elem[i+1];
//    }
//    L->length = L->length - 1;
//    //printf("delete is OK...");
//
//    //将athle清空
//    for(int j=0;j<number;j++)
//    {
//        memset(&athle[j],0,sizeof(struct athletes));
//    }
//
//    //传回athle[]
//    for(int i=0;i<L->length;i++){
//        athle[i]=L->elem[i];
//    }

}

/*=====修改=====*/
int Chanege_List(struct athletes athle[], int number,int changeNum, struct athletes changeAth){
    //L->elem[num] = ele;
    int i,j;
    struct SqList *L;
    L->elem=NULL;
    L->length=0;

    L->elem = athle;   //不知道对不对
    if(!L->elem) {return -1;}
    L->length = number;  //总共有多少个元素
    for(int i=0;i<L->length;i++){
        L->elem[i]=athle[i] ;
    }

    L->elem[changeNum] = changeAth;

    //将athle清空
    for(int j=0;j<number;j++)
    {
        memset(&athle[j],0,sizeof(struct athletes));
    }

    //传回athle[]
    for(int i=0;i<L->length;i++){
        athle[i]=L->elem[i];
    }



}
/*=====查询=====*/    //number是从0开始的
struct athletes Find_List(struct athletes athle[], int number, int method, char* keyword )
{
    //int temp=0;
    //cout<<"L"<<"["<<num<<"]"<<"="<<L->elem[num-1]<<endl;
    if(method==1)  //学号
    {
        for(int i=0;i<=number;i++)
        {
            if(strcmp(athle[i].id,keyword)==0)  //如果一致
            {
                findtemp=1;
                return athle[i];
            }
        }

        printf("没有找到！");
        findtemp=0;

        struct athletes empty;
        struct athletes *p;
        *p=empty;
        p=NULL;
        return empty ;
    }

}


/*=====插入=====*/
//int Insert_List(struct SqList *L,int ele,int num){
//    printf("\ninsert...\n");
//    int i,j;
//    L->length = L->length + 1;
//    for(i=L->length;i>=num;i--){
//        L->elem[i-1]=L->elem[i-2];
//    }
//    L->elem[num-1] = ele;
//    printf("insert %d is OK...\n\n\n",ele);
//}

/*=====显示=====*/
void Display_List(struct athletes athle[], int number){
    printf("===display===\n");
    for(int i=0;i<number;i++){
        printf("%s   %s   %s   %s  %s   %s   %s ",athle[i].id,athle[i].name,athle[i].gender,athle[i].major,athle[i].college,athle[i].grade,athle[i].preteam);
    }
    printf("\n");
}

int getFindTemp()
{
    return findtemp;
}