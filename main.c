#include <stdio.h>
#include <stdlib.h>
//#include <mem.h>
#include <memory.h>
#include "SignInProgress.h"


//初始化信息
#define newsNumber 10

#define compsNumber 20
#define teamsNumber 30


char username[10];
char teamMechanism[20];

struct news {
    char time[100];
    char content[100];
};

//struct account{
//    char username[10];
//    char password[10];
//};

struct athletes{
    char name[20];
    char id[20];        //学号
    char gender[10];
    char grade[10];     //年级
    char college[20];   //学院
   // char department[20]; //系
    char major[20];     //专业
    char preteam[10];  //代表单位
   //  char number[10];   //运动员号
   //  char score[10];    //个人成绩
};

struct competition{
    char category[10];  //田赛和径赛
    char name[20];      //
    char number[10];         //项目编号
    char result[20];    //项目结果（分数、成绩）
    char field[20];     //场地
    char gameLength[10];//时长
    char attribute[10]; //个人/团体
};

struct teams{
    char category[20];
    char name[20];
    char score[10];
    char rank[10];
    char number[10];
};

struct compDetail{
    char athletesNumber[10];
    char compNumber[10];
    char score[10];
    char integral[10];
    char rank[10];
};

void showNews();
void chooseUser();
//int adminSignIn();
void adminControl();
void addNews();
void changeNews();
void deleteNews();
void findNews();
void addComp();
void showComps();
void deleteComp();
void changeComp();
void showTeams();
void addTeams();
void getTeamMechanism();
void changeTeams();
void deleteTeams();
void setTeamMechanism();
char *s_gets(char *st,int n);

int main() {
    getTeamMechanism();
    printf("%s\n",teamMechanism);
    showNews();
    chooseUser();
    return 0;
}

//这里第二个功能由志恒做
void chooseUser(){

    int choose,checkAdmin;


    printf("------------登录------------\n");
    printf("1.管理员登录\n2.普通用户查询成绩\n");


    scanf("%d",&choose);
    //printf("%d",choose);
    switch(choose){
        case 1:
            checkAdmin=adminSignIn();

            printf("%d\n哈哈哈哈哈",checkAdmin);
            //test
            printf("成功执行adminSignIn操作success");
            if(checkAdmin==1) {
                adminControl();
            }

            else {
                printf("密码输入错误!返回主界面中...\n\n");
                showNews();
                chooseUser();
            }
            printf("？？？？？？success");
            adminControl();
            break;
        default: printf("非管理员")   ;
    }
}

//adminSignIn 在 SignInProgress里面



void adminControl(){
    int choose;
    printf("Welcome %s\n1.发布通知    2.修改通知\n3.删除通知    4.关键字查询通知\n5.查看发布的通知    6.发布新的比赛项目\n"
                   "7.查看已有的比赛项目  8.删除已有的比赛项目\n9.修改已有的比赛项目    10.设置代表队机制（学院/年级/专业）\n"
                   "11.增加代表队（默认学院制） 12.查看已有的代表队\n13.修改已有的代表队信息   14.删除已有的代表队\n"
                   "15.运动员报名项目 16.运动员取消报名项目 17.录入比赛成绩  18.成绩统计汇总\n");
    scanf("%d",&choose);
    getchar();
    switch(choose){
        case 1:
            addNews();
            break;
        case 2:
            changeNews();
            break;
        case 3:
            deleteNews();
            break;
        case 4:
            findNews();
            break;
        case 5:
            showNews();
            adminControl();
            break;
        case 6:
            addComp();
            break;
        case 7:
            showComps();
            break;
        case 8:
            deleteComp();
            break;
        case 9:
            changeComp();
            break;
        case 10:
            setTeamMechanism();  //设置代表队
            break;
        case 11:
            addTeams();
            break;
        case 12:
            showTeams();
            break;
        case 13:
            changeTeams();
            break;
        case 14:
            deleteTeams();
            break;
        //黄玉修改部分 change begin
//        case 15:
//            athleteSignUp();
//            break;
//        case 16:
//            athleteSignOff();
//            break;
//        case 17:
//            gradeRegister();
//            break;
//        case 18:
//            gradeSummary();
//            break;
        //change end
        default:
            printf("输入有误！按任意键返回");
            getchar();
            adminControl();
    }
}

/*------------对news的增删改查和显示-begin--------------*/
void addNews(){
    FILE *fp=NULL;
    struct news new;
    if((fp=fopen("C:\\Users\\nancy\\Desktop\\news.dat","ab+"))!=NULL){
        printf("time(year/mm/dd):\n·····返回管理员界面请按0");
        s_gets(new.time,100);
        if(strcmp(new.time,"0")!=0){
            printf("content:\n");
            s_gets(new.content,100);
            fwrite(&new, sizeof(struct news),1,fp);
            fclose(fp);
            printf("发布成功。");
        }else{
            adminControl();
        }
    }else{
        printf("Cannot find the file!");
    }
}

void changeNews(){
    int changeNumber;
    int count=0;
    showNews();
    struct news new[newsNumber];
    char choose;
    printf("选择要修改的通知序号:·····返回管理员界面请按0");
    scanf("%d",&changeNumber);
    if(changeNumber!=0){
        getchar();
        printf("确定修改?(y/n)：·····返回管理员界面请按0");
        scanf("%c",&choose);
        getchar();
        if(choose=='y'){
            FILE *fp=NULL;

            if((fp=fopen("/Users/nancy/Desktop/SportSystem/news.dat","rb"))!=NULL){
                while(!feof(fp)){
                    fread(&new[count],sizeof(struct news),1,fp);
                    count++;
                }
                fclose(fp);
                count--;
                int use=count+1-changeNumber;   //count+1-changeNumber就是实际上选择要修改的条目
                printf("要修改的条目内容为：\n         时间                     通知内容 \n");
                printf("       %s               %s\n",new[use-1].time,new[use-1].content);
                printf("请输入修改后的内容：");
                s_gets(new[use-1].content,100);
                printf("%s",new[use-1].content);
                printf("\n修改成功!");
            }else{
                printf("Cannot find the file!");
            }
            if((fp=fopen("/Users/nancy/Desktop/SportSystem/news.dat","wb+"))!=NULL){
                for(int i=0;i<count;i++)
                    fwrite(&new[i], sizeof(struct news),1,fp);
                fclose(fp);
                adminControl();
            }else{
                printf("Cannot find the file!");
            }
        }else if(choose=='n'){
            changeNews();
        }else{
            printf("输入无效！");
            changeNews();
        }
    }else{
        adminControl();
    }
}


void deleteNews(){
    int deleteNumber;
    int count=0;
    showNews();
    struct news new[newsNumber];
    char choose;
    printf("选择要删除的通知序号:·····返回管理员界面请按0");
    scanf("%d",&deleteNumber);
    if(deleteNumber!=0){
        getchar();
        printf("确定删除?(y/n)：·····返回管理员界面请按0");
        scanf("%c",&choose);
        getchar();
        if(choose=='y'){
            FILE *fp=NULL;
            if((fp=fopen("C:\\Users\\nancy\\Desktop\\news.dat","rb"))!=NULL){
                while(!feof(fp)){
                    fread(&new[count],sizeof(struct news),1,fp);
                    count++;
                }
                fclose(fp);
                count--;
                int use=count+1-deleteNumber;
                for(use;use<count;use++){      //count+1-deleteNumber就是实际上选择要删除的条目
                    strcpy(new[use-1].time,new[use].time);
                    strcpy(new[use-1].content,new[use].content);
                }
            }else{
                printf("Cannot find the file!");
            }
            if((fp=fopen("C:\\Users\\nancy\\Desktop\\news.dat","wb+"))!=NULL){
                for(int i=0;i<count-1;i++)
                    fwrite(&new[i], sizeof(struct news),1,fp);
                fclose(fp);
                adminControl();
            }else{
                printf("Cannot find the file!");
            }
        }else if(choose=='n'){
            deleteNews();
        }else{
            printf("输入无效！");
            deleteNews();
        }
    }else{
        adminControl();
    }
}

void findNews(){
    int choose,count=0,i=1,isFind=0;
    char time[100];
    char content[100];
    FILE *fp=NULL;
    struct news new[newsNumber];
    printf("1.按时间查找\n2.按关键词搜索");
    scanf("%d",&choose);
    switch (choose){
        case 1:
            printf("请输入时间：");
            getchar();
            s_gets(time,100);
            if((fp=fopen("C:\\Users\\nancy\\Desktop\\news.dat","rb"))!=NULL){
                while(!feof(fp)){
                    fread(&new[count],sizeof(struct news),1,fp);
                    count++;
                }
                count-=2;
                while(count>=0){
                    if(strcmp(new[count].time,time)==0){
                        printf("%d       %s               %s\n",i,new[count].time,new[count].content);
                        isFind=1;
                    }
                    i++;
                    count--;
                }
                if(isFind==0){
                    printf("无找到所查信息\n");
                }
                fclose(fp);
            }else{
                printf("Cannot find the file!");
            }
            printf("按任意键返回");
            getchar();
            adminControl();
            break;
        case 2:
            printf("请输关键字：");
            getchar();
            s_gets(content,100);
            if((fp=fopen("C:\\Users\\Chan\\Desktop\\news.dat","rb"))!=NULL){
                while(!feof(fp)){
                    fread(&new[count],sizeof(struct news),1,fp);
                    count++;
                }
                count-=2;
                while(count>=0){
                    if(strstr(new[count].content, content) != NULL){
                        printf("%d       %s               %s\n",i,new[count].time,new[count].content);
                        isFind=1;
                    }
                    i++;
                    count--;
                }
                if(isFind==0){
                    printf("无找到所查信息\n");
                }
                fclose(fp);
            }else{
                printf("Cannot find the file!");
            }
            printf("按任意键返回");
            getchar();
            adminControl();
            break;
    }
}


void showNews(){
    int i=1;
    int count=0;
    printf("         时间                     通知内容 \n");
    struct news new[newsNumber];
    FILE *fp=NULL;
    if((fp=fopen("/Users/nancy/Desktop/SportSystem/news.dat","rb"))!=NULL){
        while(!feof(fp)){
            fread(&new[count],sizeof(struct news),1,fp);
            count++;
        }
        count-=2;
        while(count>=0){
            printf("%d       %s               %s\n",i,new[count].time,new[count].content);
            i++;
            count--;
        }
        fclose(fp);
    }else{
        printf("Cannot find the !!!!file!");
    }
}


/*------------对news的增删改查和显示-end--------------*/
/*------------对competition的增删改和显示(没有查询)-begin--------------*/
void showComps(){
    int i=1;
    int count=0;
    printf("   项目编号    比赛类型    项目属性   项目时长    项目场地    项目名称   项目结果 \n");
    struct competition comp[compsNumber];
    FILE *fp=NULL;
    if((fp=fopen("C:\\Users\\Chan\\Desktop\\competition.dat","rb"))!=NULL){
        while(!feof(fp)){
            fread(&comp[count],sizeof(struct competition),1,fp);
            count++;
        }
        count-=2;
        while(count>=0){
            printf("    %s        %s      %s      %s       %s       %s        %s\n",comp[count].number,comp[count].category,comp[count].attribute,comp[count].gameLength,comp[count].field,comp[count].name,comp[count].result);
            i++;
            count--;
        }
        fclose(fp);
    }else{
        printf("Cannot find the file!");
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

void changeComp(){
    char changeNumber[10];
    char changeDetail[20];
    char category[10];  //田赛和径赛
    char name[20];      //
    char result[20];    //项目结果（分数、成绩）
    char field[20];     //场地
    char gameLength[10];//时长
    char attribute[10]; //个人/团体
    int count=0;
    int i=0;
    struct competition comp[compsNumber];
    char choose;
    printf("   项目编号    比赛类型    项目属性   项目时长    项目场地    项目名称   项目结果 \n");
    FILE *fp=NULL;
    FILE *fpp=NULL;
    if((fp=fopen("C:\\Users\\nancy\\Desktop\\competition.dat","rb"))!=NULL){
        while(!feof(fp)){
            fread(&comp[count],sizeof(struct competition),1,fp);
            count++;
        }
        count-=2;
        while(count>=0){
            printf("    %s        %s      %s      %s       %s       %s        %s\n",comp[count].number,comp[count].category,comp[count].attribute,comp[count].gameLength,comp[count].field,comp[count].name,comp[count].result);
            i++;
            count--;
        }
        fclose(fp);
    }else{
        printf("Cannot find the file!");
        adminControl();
    }
    count=0;
    i=0;
    printf("选择要修改的项目编号:·····返回管理员界面请按0");
    s_gets(changeNumber,10);
    printf("%s\n",changeNumber);
    if(strcmp("0",changeNumber)!=0){
        printf("确定修改?(y/n)：·····返回管理员界面请按0");
        scanf("%c",&choose);
        getchar();
        if(choose=='y'){
            if((fpp=fopen("C:\\Users\\nancy\\Desktop\\competition.dat","rb"))!=NULL){
                while(!feof(fpp)){
                    fread(&comp[count],sizeof(struct competition),1,fpp);
                    count++;
                }
                fclose(fpp);
                count--;
                while((strcmp(comp[i].number,changeNumber)!=0)&&(i<count)){
                    i++;
                }
                printf("请选择要修改的详细内容：（比赛类型、项目属性、项目时长、项目场地、项目名称、项目结果）");
                s_gets(changeDetail,20);
                printf("请输入修改后的内容：");
                if(strcmp("比赛类型",changeDetail)==0){
                    s_gets(category,10);
                    strcpy(comp[i].category,category);
                }else if(strcmp("项目时长",changeDetail)==0){
                    s_gets(gameLength,10);
                    strcpy(comp[i].gameLength,gameLength);
                }else if(strcmp("项目属性",changeDetail)==0) {
                    s_gets(attribute, 10);
                    strcpy(comp[i].attribute, attribute);
                }else if(strcmp("项目场地",changeDetail)==0){
                    s_gets(field,20);
                    strcpy(comp[i].field,field);
                }else if(strcmp("项目名称",changeDetail)==0){
                    s_gets(name,20);
                    strcpy(comp[i].name,name);
                }else if(strcmp("项目结果",changeDetail)==0){
                    s_gets(result,20);
                    strcpy(comp[i].result,result);
                }else{
                    printf("输入有误！按任意键重新输入");
                    getchar();
                    changeComp();
                }
            }else{
                printf("Cannot find the file!");
            }
            if((fpp=fopen("C:\\Users\\Chan\\Desktop\\competition.dat","wb+"))!=NULL){
                for(int i=0;i<count;i++)
                    fwrite(&comp[i], sizeof(struct competition),1,fpp);
                fclose(fpp);
                adminControl();
            }else{
                printf("Cannot find the file!");
            }
        }else if(choose=='n'){
            deleteComp();
        }else{
            printf("输入无效！");
            deleteComp();
        }
    }else{
        adminControl();
    }
}

void deleteComp(){
    char deleteNumber[10];
    int count=0;
    int i=0;
    struct competition comp[compsNumber];
    char choose;
    FILE *fp=NULL;
    FILE *fpp=NULL;
    if((fp=fopen("C:\\Users\\Chan\\Desktop\\competition.dat","rb"))!=NULL){
        while(!feof(fp)){
            fread(&comp[count],sizeof(struct competition),1,fp);
            count++;
        }
        count-=2;
        printf("   项目编号    比赛类型    项目属性   项目时长    项目场地    项目名称   项目结果 \n");
        while(count>=0){
            printf("    %s        %s      %s      %s       %s       %s        %s\n",comp[count].number,comp[count].category,comp[count].attribute,comp[count].gameLength,comp[count].field,comp[count].name,comp[count].result);
            i++;
            count--;
        }
        fclose(fp);
    }else{
        printf("Cannot find the file!");
        adminControl();
    }
    count=0;
    i=0;
    printf("选择要删除的项目编号:·····返回管理员界面请按0");
    s_gets(deleteNumber,10);
    printf("%s\n",deleteNumber);
    if(strcmp("0",deleteNumber)!=0){
        printf("确定删除?(y/n)：·····返回管理员界面请按0");
        scanf("%c",&choose);
        getchar();
        if(choose=='y'){
            if((fpp=fopen("C:\\Users\\Chan\\Desktop\\competition.dat","rb"))!=NULL){
                while(!feof(fpp)){
                    fread(&comp[count],sizeof(struct competition),1,fpp);
                    count++;
                }
                fclose(fpp);
                count--;
                while((strcmp(comp[i].number,deleteNumber)!=0)&&(i<count)){
                    i++;
                }
                for(i;i<count;i++){
                    strcpy(comp[i].number,comp[i+1].number);
                    strcpy(comp[i].category,comp[i+1].category);
                    strcpy(comp[i].name,comp[i+1].name);
                    strcpy(comp[i].result,comp[i+1].result);
                    strcpy(comp[i].field,comp[i+1].field);
                    strcpy(comp[i].gameLength,comp[i+1].gameLength);
                    strcpy(comp[i].attribute,comp[i+1].attribute);
                }
            }else{
                printf("Cannot find the file!");
            }
            if((fpp=fopen("C:\\Users\\Chan\\Desktop\\competition.dat","wb+"))!=NULL){
                for(int i=0;i<count-1;i++)
                    fwrite(&comp[i], sizeof(struct competition),1,fpp);
                fclose(fpp);
                adminControl();
            }else{
                printf("Cannot find the file!");
            }
        }else if(choose=='n'){
            deleteComp();
        }else{
            printf("输入无效！");
            deleteComp();
        }
    }else{
        adminControl();
    }
}

void showTeams(){
    int i=1;
    int count=0;
    struct teams team[teamsNumber];
    FILE *fp=NULL;
    if(strcmp(teamMechanism,"学院")==0){
        printf("     编号      名称     分数    名次\n");
        if((fp=fopen("C:\\Users\\Chan\\Desktop\\teamForCollege.dat","rb"))!=NULL){
            while(!feof(fp)){
                fread(&team[count],sizeof(struct teams),1,fp);
                count++;
            }
            count-=2;
            while(count>=0){
                printf("    %s    %s    %s    %s\n",team[count].number,team[count].name,team[count].score,team[count].rank);
                i++;
                count--;
            }
            fclose(fp);
        }else{
            printf("Cannot find the file!");
        }
    }else if(strcmp(teamMechanism,"专业")==0) {
        printf("     编号     分数    名次      名称\n");
        if ((fp = fopen("C:\\Users\\Chan\\Desktop\\teamForMajor.dat", "rb")) != NULL) {
            while (!feof(fp)) {
                fread(&team[count], sizeof(struct teams), 1, fp);
                count++;
            }
            count -= 2;
            while (count >= 0) {
                printf("    %s    %s    %s          %s\n", team[count].number, team[count].score, team[count].rank,
                       team[count].name);
                i++;
                count--;
            }
            fclose(fp);
        } else {
            printf("Cannot find the file!");
        }
    } else if(strcmp(teamMechanism,"年级")==0) {
        printf("     编号      名称     分数    名次\n");
        if ((fp = fopen("C:\\Users\\Chan\\Desktop\\teamForGrade.dat", "rb")) != NULL) {
            while (!feof(fp)) {
                fread(&team[count], sizeof(struct teams), 1, fp);
                count++;
            }
            count -= 2;
            while (count >= 0) {
                printf("    %s    %s    %s    %s\n", team[count].number, team[count].score, team[count].rank,
                       team[count].name);
                i++;
                count--;
            }
            fclose(fp);
        } else {
            printf("Cannot find the file!");
        }
    }
    printf("按任意键返回");
    getchar();
    adminControl();
}

/*------------对competition的增删改和显示(没有查询)-end--------------*/

/*------------对代表队Team的增删改和显示(没有查询)-begin--------------*/
void addTeams(){
    FILE *fp=NULL;
    struct teams team;
    if(strcmp(teamMechanism,"学院")==0){
        if((fp=fopen("C:\\Users\\Chan\\Desktop\\teamForCollege.dat","ab+"))!=NULL){
            printf("新增的代表队名称：(如学院请以“院”结尾，专业请以“专业”结尾，年级请以“级”结尾)\n·····返回管理员界面请按0");
            s_gets(team.name,20);
            if(strcmp(team.name,"0")!=0){
                if((strstr(team.name,"院")!=NULL)||(strstr(team.name,"专业")!=NULL)||(strstr(team.name,"级")!=NULL)){
                    printf("代表队编号:\n");
                    s_gets(team.number,10);
                    strcpy(team.rank," ");
                    strcpy(team.score," ");
                    fwrite(&team, sizeof(struct teams),1,fp);
                    fclose(fp);
                    printf("添加成功。");
                } else{
                    printf("输入有误！按任意键重新输入");
                    getchar();
                    addTeams();
                }
            }else{
                adminControl();
            }
        }else{
            printf("Cannot find the file!");
        }
    }else if(strcmp(teamMechanism,"专业")==0){
        if((fp=fopen("C:\\Users\\Chan\\Desktop\\teamForMajor.dat","ab+"))!=NULL){
            printf("新增的代表队名称：(如学院请以“院”结尾，专业请以“专业”结尾，年级请以“级”结尾)\n·····返回管理员界面请按0");
            s_gets(team.name,20);
            if(strcmp(team.name,"0")!=0){
                if((strstr(team.name,"院")!=NULL)||(strstr(team.name,"专业")!=NULL)||(strstr(team.name,"级")!=NULL)){
                    printf("代表队编号:\n");
                    s_gets(team.number,10);
                    strcpy(team.rank," ");
                    strcpy(team.score," ");
                    fwrite(&team, sizeof(struct teams),1,fp);
                    fclose(fp);
                    printf("添加成功。");
                } else{
                    printf("输入有误！按任意键重新输入");
                    getchar();
                    addTeams();
                }
            }else{
                adminControl();
            }
        }else{
            printf("Cannot find the file!");
        }
    }else if(strcmp(teamMechanism,"年级")==0){
        if((fp=fopen("C:\\Users\\Chan\\Desktop\\teamForGrade.dat","ab+"))!=NULL){
            printf("新增的代表队名称：(如学院请以“院”结尾，专业请以“专业”结尾，年级请以“级”结尾)\n·····返回管理员界面请按0");
            s_gets(team.name,20);
            if(strcmp(team.name,"0")!=0){
                if((strstr(team.name,"院")!=NULL)||(strstr(team.name,"专业")!=NULL)||(strstr(team.name,"级")!=NULL)){
                    printf("代表队编号:\n");
                    s_gets(team.number,10);
                    strcpy(team.rank," ");
                    strcpy(team.score," ");
                    fwrite(&team, sizeof(struct teams),1,fp);
                    fclose(fp);
                    printf("添加成功。");
                } else{
                    printf("输入有误！按任意键重新输入");
                    getchar();
                    addTeams();
                }
            }else{
                adminControl();
            }
        }else{
            printf("Cannot find the file!");
        }
    }
    adminControl();
}

void changeTeams(){
    char changeNumber[10];
    char changeDetail[20];
    char name[20];
    char score[10];
    char rank[10];
    char number[10];
    int count=0;
    int i=0;
    struct teams team[teamsNumber];
    char choose;
    FILE *fp=NULL;
    FILE *fpp=NULL;
    if(strcmp(teamMechanism,"学院")==0){
        printf("     编号      名称     分数    名次\n");
        if((fp=fopen("C:\\Users\\Chan\\Desktop\\teamForCollege.dat","rb"))!=NULL){
            while(!feof(fp)){
                fread(&team[count],sizeof(struct teams),1,fp);
                count++;
            }
            count-=2;
            while(count>=0){
                printf("    %s    %s    %s    %s\n",team[count].number,team[count].name,team[count].score,team[count].rank);
                i++;
                count--;
            }
            fclose(fp);
        }else{
            printf("Cannot find the file!");
        }
        count=0;
        i=0;
        printf("选择要修改的项目编号:·····返回管理员界面请按0");
        s_gets(changeNumber,10);
        printf("%s\n",changeNumber);
        if(strcmp("0",changeNumber)!=0){
            printf("确定修改?(y/n)：·····返回管理员界面请按0");
            scanf("%c",&choose);
            getchar();
            if(choose=='y'){
                if((fpp=fopen("C:\\Users\\Chan\\Desktop\\teamForCollege.dat","rb"))!=NULL){
                    while(!feof(fpp)){
                        fread(&team[count],sizeof(struct teams),1,fpp);
                        count++;
                    }
                    fclose(fpp);
                    count--;
                    while((strcmp(team[i].number,changeNumber)!=0)&&(i<count)){
                        i++;
                    }
                    printf("请选择要修改的详细内容：（编号、名称、分数、名次）");
                    s_gets(changeDetail,20);
                    printf("请输入修改后的内容：");
                    if(strcmp("编号",changeDetail)==0){
                        s_gets(number,10);
                        strcpy(team[i].number,number);
                    }else if(strcmp("名称",changeDetail)==0){
                        s_gets(name,20);
                        strcpy(team[i].name,name);
                    }else if(strcmp("分数",changeDetail)==0) {
                        s_gets(score, 10);
                        strcpy(team[i].score, score);
                    }else if(strcmp("名次",changeDetail)==0){
                        s_gets(rank,20);
                        strcpy(team[i].rank,rank);
                    }else{
                        printf("输入有误！按任意键重新输入");
                        getchar();
                        changeComp();
                    }
                }else{
                    printf("Cannot find the file!");
                }
                if((fpp=fopen("C:\\Users\\Chan\\Desktop\\teamForCollege.dat","wb+"))!=NULL){
                    for(int i=0;i<count;i++)
                        fwrite(&team[i], sizeof(struct teams),1,fpp);
                    fclose(fpp);
                    adminControl();
                }else{
                    printf("Cannot find the file!");
                }
            }else if(choose=='n'){
                deleteComp();
            }else{
                printf("输入无效！");
                deleteComp();
            }
        }else{
            adminControl();
        }
    }else if(strcmp(teamMechanism,"专业")==0) {
        printf("     编号     分数    名次      名称\n");
        if ((fp = fopen("C:\\Users\\Chan\\Desktop\\teamForMajor.dat", "rb")) != NULL) {
            while (!feof(fp)) {
                fread(&team[count], sizeof(struct teams), 1, fp);
                count++;
            }
            count -= 2;
            while (count >= 0) {
                printf("    %s    %s    %s          %s\n", team[count].number, team[count].score, team[count].rank,
                       team[count].name);
                i++;
                count--;
            }
            fclose(fp);
        } else {
            printf("Cannot find the file!");
        }
        count=0;
        i=0;
        printf("选择要修改的项目编号:·····返回管理员界面请按0");
        s_gets(changeNumber,10);
        printf("%s\n",changeNumber);
        if(strcmp("0",changeNumber)!=0){
            printf("确定修改?(y/n)：·····返回管理员界面请按0");
            scanf("%c",&choose);
            getchar();
            if(choose=='y'){
                if((fpp=fopen("C:\\Users\\Chan\\Desktop\\teamForMajor.dat","rb"))!=NULL){
                    while(!feof(fpp)){
                        fread(&team[count],sizeof(struct teams),1,fpp);
                        count++;
                    }
                    fclose(fpp);
                    count--;
                    while((strcmp(team[i].number,changeNumber)!=0)&&(i<count)){
                        i++;
                    }
                    printf("请选择要修改的详细内容：（编号、名称、分数、名次）");
                    s_gets(changeDetail,20);
                    printf("请输入修改后的内容：");
                    if(strcmp("编号",changeDetail)==0){
                        s_gets(number,10);
                        strcpy(team[i].number,number);
                    }else if(strcmp("名称",changeDetail)==0){
                        s_gets(name,20);
                        strcpy(team[i].name,name);
                    }else if(strcmp("分数",changeDetail)==0) {
                        s_gets(score, 10);
                        strcpy(team[i].score, score);
                    }else if(strcmp("名次",changeDetail)==0){
                        s_gets(rank,20);
                        strcpy(team[i].rank,rank);
                    }else{
                        printf("输入有误！按任意键重新输入");
                        getchar();
                        changeComp();
                    }
                }else{
                    printf("Cannot find the file!");
                }
                if((fpp=fopen("C:\\Users\\Chan\\Desktop\\teamForMajor.dat","wb+"))!=NULL){
                    for(int i=0;i<count;i++)
                        fwrite(&team[i], sizeof(struct teams),1,fpp);
                    fclose(fpp);
                    adminControl();
                }else{
                    printf("Cannot find the file!");
                }
            }else if(choose=='n'){
                deleteComp();
            }else{
                printf("输入无效！");
                deleteComp();
            }
        }else{
            adminControl();
        }
    } else if(strcmp(teamMechanism,"年级")==0) {
        printf("     编号      名称     分数    名次\n");
        if ((fp = fopen("C:\\Users\\Chan\\Desktop\\teamForGrade.dat", "rb")) != NULL) {
            while (!feof(fp)) {
                fread(&team[count], sizeof(struct teams), 1, fp);
                count++;
            }
            count -= 2;
            while (count >= 0) {
                printf("    %s    %s    %s    %s\n", team[count].number, team[count].score, team[count].rank,
                       team[count].name);
                i++;
                count--;
            }
            fclose(fp);
        } else {
            printf("Cannot find the file!");
        }
        count=0;
        i=0;
        printf("选择要修改的项目编号:·····返回管理员界面请按0");
        s_gets(changeNumber,10);
        printf("%s\n",changeNumber);
        if(strcmp("0",changeNumber)!=0){
            printf("确定修改?(y/n)：·····返回管理员界面请按0");
            scanf("%c",&choose);
            getchar();
            if(choose=='y'){
                if((fpp=fopen("C:\\Users\\Chan\\Desktop\\teamForGrade.dat","rb"))!=NULL){
                    while(!feof(fpp)){
                        fread(&team[count],sizeof(struct teams),1,fpp);
                        count++;
                    }
                    fclose(fpp);
                    count--;
                    while((strcmp(team[i].number,changeNumber)!=0)&&(i<count)){
                        i++;
                    }
                    printf("请选择要修改的详细内容：（编号、名称、分数、名次）");
                    s_gets(changeDetail,20);
                    printf("请输入修改后的内容：");
                    if(strcmp("编号",changeDetail)==0){
                        s_gets(number,10);
                        strcpy(team[i].number,number);
                    }else if(strcmp("名称",changeDetail)==0){
                        s_gets(name,20);
                        strcpy(team[i].name,name);
                    }else if(strcmp("分数",changeDetail)==0) {
                        s_gets(score, 10);
                        strcpy(team[i].score, score);
                    }else if(strcmp("名次",changeDetail)==0){
                        s_gets(rank,20);
                        strcpy(team[i].rank,rank);
                    }else{
                        printf("输入有误！按任意键重新输入");
                        getchar();
                        changeComp();
                    }
                }else{
                    printf("Cannot find the file!");
                }
                if((fpp=fopen("C:\\Users\\Chan\\Desktop\\teamForGrade.dat","wb+"))!=NULL){
                    for(int i=0;i<count;i++)
                        fwrite(&team[i], sizeof(struct teams),1,fpp);
                    fclose(fpp);
                    adminControl();
                }else{
                    printf("Cannot find the file!");
                }
            }else if(choose=='n'){
                deleteComp();
            }else{
                printf("输入无效！");
                deleteComp();
            }
        }else{
            adminControl();
        }
    }
}

void deleteTeams(){
    char deleteNumber[10];
    int count=0;
    int i=0;
    struct teams team[teamsNumber];
    char choose;
    FILE *fp=NULL;
    FILE *fpp=NULL;
    if(strcmp(teamMechanism,"学院")==0){
        printf("     编号      名称     分数    名次\n");
        if((fp=fopen("C:\\Users\\Chan\\Desktop\\teamForCollege.dat","rb"))!=NULL){
            while(!feof(fp)){
                fread(&team[count],sizeof(struct teams),1,fp);
                count++;
            }
            count-=2;
            while(count>=0){
                printf("    %s    %s    %s    %s\n",team[count].number,team[count].name,team[count].score,team[count].rank);
                i++;
                count--;
            }
            fclose(fp);
        }else{
            printf("Cannot find the file!");
        }
        count=0;
        i=0;
        printf("选择要删除的项目编号:·····返回管理员界面请按0");
        s_gets(deleteNumber,10);
        printf("%s\n",deleteNumber);
        if(strcmp("0",deleteNumber)!=0){
            printf("确定删除?(y/n)：·····返回管理员界面请按0");
            scanf("%c",&choose);
            getchar();
            if(choose=='y'){
                if((fpp=fopen("C:\\Users\\Chan\\Desktop\\teamForCollege.dat","rb"))!=NULL){
                    while(!feof(fpp)){
                        fread(&team[count],sizeof(struct teams),1,fpp);
                        count++;
                    }
                    fclose(fpp);
                    count--;
                    while((strcmp(team[i].number,deleteNumber)!=0)&&(i<count)){
                        i++;
                    }
                    for(i;i<count;i++){
                        strcpy(team[i].number,team[i+1].number);
                        strcpy(team[i].name,team[i+1].name);
                        strcpy(team[i].score,team[i+1].score);
                        strcpy(team[i].rank,team[i+1].rank);
                    }
                }else{
                    printf("Cannot find the file!");
                }
                if((fpp=fopen("C:\\Users\\Chan\\Desktop\\teamForCollege.dat","wb+"))!=NULL){
                    for(int i=0;i<count-1;i++)
                        fwrite(&team[i], sizeof(struct teams),1,fpp);
                    fclose(fpp);
                    adminControl();
                }else{
                    printf("Cannot find the file!");
                }
            }else if(choose=='n'){
                deleteComp();
            }else{
                printf("输入无效！");
                deleteComp();
            }
        }else{
            adminControl();
        }
    }else if(strcmp(teamMechanism,"专业")==0) {
        printf("     编号     分数    名次      名称\n");
        if ((fp = fopen("C:\\Users\\Chan\\Desktop\\teamForMajor.dat", "rb")) != NULL) {
            while (!feof(fp)) {
                fread(&team[count], sizeof(struct teams), 1, fp);
                count++;
            }
            count -= 2;
            while (count >= 0) {
                printf("    %s    %s    %s          %s\n", team[count].number, team[count].score, team[count].rank,
                       team[count].name);
                i++;
                count--;
            }
            fclose(fp);
        } else {
            printf("Cannot find the file!");
        }
        count=0;
        i=0;
        printf("选择要删除的项目编号:·····返回管理员界面请按0");
        s_gets(deleteNumber,10);
        printf("%s\n",deleteNumber);
        if(strcmp("0",deleteNumber)!=0){
            printf("确定删除?(y/n)：·····返回管理员界面请按0");
            scanf("%c",&choose);
            getchar();
            if(choose=='y'){
                if((fpp=fopen("C:\\Users\\Chan\\Desktop\\teamForMajor.dat","rb"))!=NULL){
                    while(!feof(fpp)){
                        fread(&team[count],sizeof(struct teams),1,fpp);
                        count++;
                    }
                    fclose(fpp);
                    count--;
                    while((strcmp(team[i].number,deleteNumber)!=0)&&(i<count)){
                        i++;
                    }
                    for(i;i<count;i++){
                        strcpy(team[i].number,team[i+1].number);
                        strcpy(team[i].name,team[i+1].name);
                        strcpy(team[i].score,team[i+1].score);
                        strcpy(team[i].rank,team[i+1].rank);
                    }
                }else{
                    printf("Cannot find the file!");
                }
                if((fpp=fopen("C:\\Users\\Chan\\Desktop\\teamForMajor.dat","wb+"))!=NULL){
                    for(int i=0;i<count-1;i++)
                        fwrite(&team[i], sizeof(struct teams),1,fpp);
                    fclose(fpp);
                    adminControl();
                }else{
                    printf("Cannot find the file!");
                }
            }else if(choose=='n'){
                deleteComp();
            }else{
                printf("输入无效！");
                deleteComp();
            }
        }else{
            adminControl();
        }
    } else if(strcmp(teamMechanism,"年级")==0) {
        printf("     编号      名称     分数    名次\n");
        if((fp=fopen("C:\\Users\\Chan\\Desktop\\teamForGrade.dat","rb"))!=NULL){
            while(!feof(fp)){
                fread(&team[count],sizeof(struct teams),1,fp);
                count++;
            }
            count-=2;
            while(count>=0){
                printf("    %s    %s    %s    %s\n",team[count].number,team[count].name,team[count].score,team[count].rank);
                i++;
                count--;
            }
            fclose(fp);
        }else{
            printf("Cannot find the file!");
        }
        count=0;
        i=0;
        printf("选择要删除的项目编号:·····返回管理员界面请按0");
        s_gets(deleteNumber,10);
        printf("%s\n",deleteNumber);
        if(strcmp("0",deleteNumber)!=0){
            printf("确定删除?(y/n)：·····返回管理员界面请按0");
            scanf("%c",&choose);
            getchar();
            if(choose=='y'){
                if((fpp=fopen("C:\\Users\\Chan\\Desktop\\teamForGrade.dat","rb"))!=NULL){
                    while(!feof(fpp)){
                        fread(&team[count],sizeof(struct teams),1,fpp);
                        count++;
                    }
                    fclose(fpp);
                    count--;
                    while((strcmp(team[i].number,deleteNumber)!=0)&&(i<count)){
                        i++;
                    }
                    for(i;i<count;i++){
                        strcpy(team[i].number,team[i+1].number);
                        strcpy(team[i].name,team[i+1].name);
                        strcpy(team[i].score,team[i+1].score);
                        strcpy(team[i].rank,team[i+1].rank);
                    }
                }else{
                    printf("Cannot find the file!");
                }
                if((fpp=fopen("C:\\Users\\Chan\\Desktop\\teamForGrade.dat","wb+"))!=NULL){
                    for(int i=0;i<count-1;i++)
                        fwrite(&team[i], sizeof(struct teams),1,fpp);
                    fclose(fpp);
                    adminControl();
                }else{
                    printf("Cannot find the file!");
                }
            }else if(choose=='n'){
                deleteComp();
            }else{
                printf("输入无效！");
                deleteComp();
            }
        }else{
            adminControl();
        }
    }
}

void setTeamMechanism(){
    int choose;
    char newTeamMechanism[20];
    FILE *fp=NULL;
    if((fp=fopen("C:\\Users\\Chan\\Desktop\\teamMechanism.dat","wb+"))!=NULL){
        while(!feof(fp)){
            fread(&teamMechanism,sizeof(teamMechanism),1,fp);
        }
        printf("当前机制为：%s\n",teamMechanism);
    }else{
        printf("Cannot find the file!");
    }
    printf("需要修改请按1，无需修改请按其他任意键");
    scanf("%d",&choose);
    getchar();
    switch (choose){
        case 1:
            printf("请输入新的代表队机制（学院/年级/专业：");
            s_gets(newTeamMechanism,20);
            if((strcmp(newTeamMechanism,"学院")==0)||(strcmp(newTeamMechanism,"年级")==0)||(strcmp(newTeamMechanism,"专业")==0)){
                strcpy(teamMechanism,newTeamMechanism);
                fwrite(&teamMechanism, sizeof(teamMechanism),1,fp);
                printf("设置成功");
                fclose(fp);
            }else{
                printf("输入有误！按任意键返回输入");
                getchar();
                setTeamMechanism();
            }
            break;
        default:fclose(fp);adminControl();
    }

    adminControl();
}
/*------------对代表队Team的增删改和显示(没有查询)-end----------------*/
//获取代表队是什么单位
void getTeamMechanism(){
    FILE *fp=NULL;
    //if((fp=fopen(strcat(filePath,"teamMechanism.dat"),"rb"))!=NULL){
    if((fp=fopen("C:\\Users\\nancy\\Desktop\\teamMechanism.dat","rb"))!=NULL){
        while(!feof(fp)){
            fread(&teamMechanism,sizeof(teamMechanism),1,fp);
        }
        fclose(fp);
    }else{
        printf("Cannot find Mechanism file!");
    }
}

//读字符的
char *s_gets(char *st,int n){
    char * ret_val;
    char *find;

    ret_val=fgets(st,n,stdin);  //fget是什么意思
    if(ret_val){
        find=strchr(st,'\n');   //strchr是什么意思，加在st后面？
        if(find)
            *find='\0';
        else
            while(getchar()!='\n')
                continue;
    }
    return ret_val;
}