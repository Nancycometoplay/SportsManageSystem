//
// Created by Nancy on 18/3/16.
//

//将信息写入文件

#include "main.c"


//信息参考
//struct athletes{
//    char name[20];
//    char id[20];        //学号
//    char gender[10];
//    char grade[10];     //年级
//    char college[20];   //学院
//    // char department[20]; //系
//    char major[20];     //专业
//    char preteam[10];  //代表单位
//    //  char number[10];   //运动员号
//    //  char score[10];    //个人成绩
//};

//fwrite(da,sizeof(),10,fp);


//将信息从文件中读出

//fread(&x,sizeof(),1,fp);


//athleteSignUp
//char[10] id_temp;
//各种运动员的信息
//让用户依次输入数据存储到temp变量中

//再用文件fread 比较，看是否有一样的

//有，看项目号合不合法
//没有就报错

void athleteSignUp(){
    FILE *fp=NULL;
    const char *file = "Athlete.dat";
    struct athletes athle;
    int judge=0;
    if((fp=fopen(file,"ab+"))!=NULL){    //ab+ 意味着
        printf("新增的项目类别（田赛和径赛）：\n·····返回管理员界面请按0");
        s_gets(athle.category,10);
        if(strcmp(.category,"0")!=0){              //strcmp函数：比较函数，如果str1和str2一样则返回0（按ASCII码比较大小）
            if(strstr(athle.category,"赛")!= NULL){
                printf("项目名称:\n");
                s_gets(athle.name,20);
                printf("项目编号:\n");
                s_gets(athle.number,10);
                printf("项目场地:\n");
                s_gets(athle.field,20);
                printf("项目时长:\n");
                s_gets(athle.gameLength,10);
                printf("项目属性(个人/团体):\n");
                s_gets(athle.attribute,10);
                fwrite(&athle, sizeof(struct competition),1,fp);
                fclose(fp);
                printf("发布成功。");
            } else{
                printf("输入有误！按任意键重新输入");
                getchar();
                addComp();
            }
        }else{
            adminControl();
        }
    }else{
        printf("Cannot find %s!",file);
    }
    adminControl();
}


void addComp(){
    FILE *fp=NULL;
    struct competition comp;
    if((fp=fopen("C:\\Users\\Chan\\Desktop\\competition.dat","ab+"))!=NULL){
        printf("新增的项目类别（田赛和径赛）：\n·····返回管理员界面请按0");
        s_gets(comp.category,10);
        if(strcmp(comp.category,"0")!=0){
            if(strstr(comp.category,"赛")!= NULL){
                printf("项目名称:\n");
                s_gets(comp.name,20);
                printf("项目编号:\n");
                s_gets(comp.number,10);
                printf("项目场地:\n");
                s_gets(comp.field,20);
                printf("项目时长:\n");
                s_gets(comp.gameLength,10);
                printf("项目属性(个人/团体):\n");
                s_gets(comp.attribute,10);
                fwrite(&comp, sizeof(struct competition),1,fp);
                fclose(fp);
                printf("发布成功。");
            } else{
                printf("输入有误！按任意键重新输入");
                getchar();
                addComp();
            }
        }else{
            adminControl();
        }
    }else{
        printf("Cannot find the file!");
    }
    adminControl();
}
