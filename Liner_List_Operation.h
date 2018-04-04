//
// Created by Nancy on 18/3/19.
//


#define MAX_SIZE 100
#define comp_per_athle 3;
//using namespace std;


//#define compsNumber 20


//#define compsNumber 20


//typedef struct {
//    char name[20];
//    char id[20];
//    char gender[10];
//    char grade[10];
//    char college[20]; //学院
//    // char department[20];
//    char major[20];   //专业
//    char preteam[10]; //代表队
//    // char number[10];
//    // char score[10];
//    //struct compitition *comp[comp_per_athle];
//} athletes;


int Append_List(athletes athle[],int number, athletes *addAth);
void Delete_List(athletes athle[],int number,athletes deleteAth);
void Chanege_List(athletes athle[],int number,athletes changeAth);
athletes Find_List(athletes athle[], int number, int method, char* keyword );
int isFind_List(athletes athle[], int number, int method, char* keyword );
void Display_List(athletes athle[], int number);


//#define comp_per_athle 3;
#define athe_per_comp _Max 30;

//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <memory.h>
//
//
//


//都是从




//typedef struct SqList{
//    struct athletes *elem;  //根据程序来改变
//    int length;
//};



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

/*=====追加=====*/  //number就是下标
int Append_List(athletes athle[],int number, athletes *addAth){

   // L->elem[L->length-1] = addAth;

   if((number+1<1)||(number+1>athleteNumber))
       return 0;
   else{
       athle[number+1]=*addAth;
       return 1;
   }

}


/*=====删除=====*/           //whereDelete就是下标,删除就是后面的移到前面去

//传入删除前的数组的地址，该数组的大小，要删除的元素
void Delete_List(athletes athle[],int number,athletes deleteAth){
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
//    struct athletes *p;
//    *p=athle[number];
//    p=NULL;
//    printf("删除成功");



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
void Chanege_List(athletes athle[],int number,athletes changeAth){
    //L->elem[num] = ele;
    int whereChange=0;  //删除操作的下标
    for(int i=0;i<=number;i++)
    {
        if(athle[i].id==changeAth.id)  //找到对应的i
        {
            whereChange=i;
            break;
        }
    }

    athle[whereChange]=changeAth;
}

/*=====查询=====*/    //number是从0开始的
athletes Find_List(athletes athle[], int number, int method, char* keyword )
{
    //int temp=0;
    //cout<<"L"<<"["<<num<<"]"<<"="<<L->elem[num-1]<<endl;
    if(method==1)  //用学号找运动员
    {
        for(int i=0;i<=number;i++)
        {
            if(strcmp(athle[i].id,keyword)==0)  //如果一致
            {

                return athle[i];
            }
        }

        printf("没有找到！");


//        struct athletes empty;
//        struct athletes *p;
//        *p=empty;
//        p=NULL;
//        return empty ;
    }

}

int isFind_List(athletes athle[], int number, int method, char* keyword )
{
    //int temp=0;
    //cout<<"L"<<"["<<num<<"]"<<"="<<L->elem[num-1]<<endl;
    if(method==1)  //用学号找运动员
    {
        for(int i=0;i<=number;i++)
        {
            if(strcmp(athle[i].id,keyword)==0)  //如果一致
            {
               // findtemp=1;
                return 1;
            }
        }

      //  printf("没有找到！");
      //  findtemp=0;
        return 0;

//        struct athletes empty;
//        struct athletes *p;
//        *p=empty;
//        p=NULL;
//        return empty ;
    }

}

//根据运动员学号找代表队的名称
char* Find_List_teamName(athletes athle[], int number, int method, char* keyword , char *dest)
{
    //int temp=0;
    //cout<<"L"<<"["<<num<<"]"<<"="<<L->elem[num-1]<<endl;
    if(method==1)  //用学号找运动员对应的队伍
    {
        for(int i=0;i<=number;i++)
        {
            if(strcmp(athle[i].id,keyword)==0)  //如果一致
            {
                strcpy(dest,athle[i].preteam);
                return dest;
            }
        }

       // printf("没有找到！");
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
void Display_List(athletes athle[], int number){
    printf("===display===\n");
    for(int i=0;i<=number;i++){
        printf("%s   %s   %s   %s  %s   %s   %s",athle[i].id,athle[i].name,athle[i].gender,athle[i].major,athle[i].college,athle[i].grade,athle[i].preteam);
        printf("\n");
    }
    printf("\n");
}

