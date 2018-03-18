#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define newsNumber 10
#define accsNumber 10
#define compsNumber 20
#define teamsNumber 30

char username[10];
char teamMechanism[20];
int judgeMechanism=0;

struct news{
    char time[100];
    char content[100];
};

struct account{
    char username[10];
    char password[10];
};

//运动员7个参数
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
int adminSignIn();
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

void chooseUser(){
    int choose,checkAdmin;
    printf("\n1.管理员登录\n2.普通用户\n");
    scanf("%d",&choose);
    switch(choose){
        case 1:
            checkAdmin=adminSignIn();
            //system("cls");
            printf("%d\n",checkAdmin);
            if(checkAdmin==1) {
                adminControl();
            }
            else {
                printf("密码输入错误!返回主界面中...\n\n");
                showNews();
                chooseUser();
            }
            break;
    }
}

//管理员登录
int adminSignIn(){
    int count=0;
    char password[10];
    printf("username?\n");
    scanf("%s",username);
    printf("password?\n");
    scanf("%s",password);
    FILE *fp=NULL;
    struct account acc[accsNumber];
    if((fp=fopen("account.txt","rb"))!=NULL){
        while(!feof(fp)){
            fread(&acc[count], sizeof(struct account),1,fp);
            if((strcmp(acc[count].username,username)==0)&&(strcmp(acc[count].password,password)==0)){
                return 1;
            }
            count++;
        }
        fclose(fp);
    }else{
        printf("Cannot find account file!");
    }
    return 0;
}

//管理员选择界面
void adminControl(){
    int choose;
    printf("Welcome %s\n1.发布通知    2.修改通知\n3.删除通知    4.关键字查询通知\n5.查看发布的通知    6.发布新的比赛项目\n"
                   "7.查看已有的比赛项目  8.删除已有的比赛项目\n9.修改已有的比赛项目    10.设置代表队机制（学院/年级/专业）\n"
                   "11.增加代表队（默认学院制） 12.查看已有的代表队\n13.修改已有的代表队信息   14.删除已有的代表队",username);
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
            setTeamMechanism();
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
        default:
            printf("输入有误！按任意键返回");
            getchar();
            adminControl();
    }
}
/*------------对news的增删改查和显示-begin-------------------------*/
void addNews(){
    FILE *fp=NULL;
    struct news new;
    if((fp=fopen("news.txt","ab+"))!=NULL){
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
        printf("Cannot find news file!");
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
            if((fp=fopen("news.txt","rb"))!=NULL){
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
            if((fp=fopen("news.txt","wb+"))!=NULL){
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
            if((fp=fopen("news.txt","rb"))!=NULL){
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
            if((fp=fopen("news.txt","wb+"))!=NULL){
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
            if((fp=fopen("news.txt","rb"))!=NULL){
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
            if((fp=fopen("news.txt","rb"))!=NULL){
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
    if((fp=fopen("news.txt","rb"))!=NULL){
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
        printf("Cannot find news file!");
    }
}
/*------------对news的增删改查和显示-end-----------------------------*/

/*------------对competition的增删改和显示(没有查询)-begin--------------*/

void showComps(){
    int i=1;
    int count=0;
    printf("   项目编号    比赛类型    项目属性   项目时长    项目场地    项目名称   项目结果 \n");
    struct competition comp[compsNumber];
    FILE *fp=NULL;
    if((fp=fopen("competition.txt","rb"))!=NULL){
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
    if((fp=fopen("competition.txt","ab+"))!=NULL){
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
    if((fp=fopen("competition.txt","rb"))!=NULL){
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
            if((fpp=fopen("competition.txt","rb"))!=NULL){
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
            if((fpp=fopen("competition.txt","wb+"))!=NULL){
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
    if((fp=fopen("competition.txt","rb"))!=NULL){
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
            if((fpp=fopen("competition.txt","rb"))!=NULL){
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
            if((fpp=fopen("competition.txt","wb+"))!=NULL){
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

/*------------对competition的增删改和显示(没有查询)-end--------------*/


/*------------对代表队Team的增删改和显示(没有查询)-begin--------------*/


void showTeams(){
    int i=1;
    int count=0;
    struct teams team[teamsNumber];
    FILE *fp=NULL;
    if(strcmp(teamMechanism,"学院")==0){
        printf("     编号      名称     分数    名次\n");
        if((fp=fopen("teamForCollege.txt","rb"))!=NULL){
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
        if ((fp = fopen("teamForMajor.txt", "rb")) != NULL) {
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
        if ((fp = fopen("teamForGrade.txt", "rb")) != NULL) {
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

void addTeams(){
    FILE *fp=NULL;
    struct teams team;
    if(strcmp(teamMechanism,"学院")==0){
        if((fp=fopen("teamForCollege.txt","ab+"))!=NULL){
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
        if((fp=fopen("teamForMajor.txt","ab+"))!=NULL){
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
        if((fp=fopen("teamForGrade.txt","ab+"))!=NULL){
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
        if((fp=fopen("teamForCollege.txt","rb"))!=NULL){
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
                if((fpp=fopen("teamForCollege.txt","rb"))!=NULL){
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
                if((fpp=fopen("teamForCollege.txt","wb+"))!=NULL){
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
        if ((fp = fopen("teamForMajor.txt", "rb")) != NULL) {
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
                if((fpp=fopen("teamForMajor.txt","rb"))!=NULL){
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
                if((fpp=fopen("teamForMajor.txt","wb+"))!=NULL){
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
        if ((fp = fopen("teamForGrade.txt", "rb")) != NULL) {
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
                if((fpp=fopen("teamForGrade.txt","rb"))!=NULL){
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
                if((fpp=fopen("teamForGrade.txt","wb+"))!=NULL){
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
        if((fp=fopen("teamForCollege.txt","rb"))!=NULL){
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
                if((fpp=fopen("teamForCollege.txt","rb"))!=NULL){
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
                if((fpp=fopen("teamForCollege.txt","wb+"))!=NULL){
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
        if ((fp = fopen("teamForMajor.txt", "rb")) != NULL) {
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
                if((fpp=fopen("teamForMajor.txt","rb"))!=NULL){
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
                if((fpp=fopen("teamForMajor.txt","wb+"))!=NULL){
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
        if((fp=fopen("teamForGrade.txt","rb"))!=NULL){
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
                if((fpp=fopen("teamForGrade.txt","rb"))!=NULL){
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
                if((fpp=fopen("teamForGrade.txt","wb+"))!=NULL){
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
/*------------对代表队Team的增删改和显示(没有查询)-end----------------*/

void setTeamMechanism(){
    int choose;
    char newTeamMechanism[20];
    FILE *fp=NULL;
    if((fp=fopen("teamMechanism.txt","wb+"))!=NULL){
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
            if(!judgeMechanism)     //当judge 是1 时，证明已经录入了运动员，如果judge是0就可以改
            {
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
            }

            break;
        default:fclose(fp);adminControl();
    }

    adminControl();
}

void getTeamMechanism(){
    FILE *fp=NULL;
    if((fp=fopen("teamMechanism.txt","rb"))!=NULL){
        while(!feof(fp)){
            fread(&teamMechanism,sizeof(teamMechanism),1,fp);
        }
        fclose(fp);
    }else{
        printf("Cannot find teamMechanism file!");
    }
}

/*------------对athlete的增删改查-begin--------------*/
void addAthlete(){
    FILE *fp=NULL;
    struct athletes athle;
    int sex;
    if((fp=fopen("athlete.txt","ab+"))!=NULL){
        printf("请输入运动员学号 \n·····返回管理员界面请按0");
        s_gets(athle.id,20);
        if(strcmp(athle.id,"0")!=0){
            printf("姓名：\n");
            s_gets(athle.name,20);
            printf("性别：1:男 2:女\n");
            //鲁棒性
            while(scanf("%d",&sex)&&(sex==1||sex==2)){
                if (sex==1) strcpy(athle.gender,"男") ;
                else if(sex==2) strcpy(athle.gender,"女") ;
            }
            printf("年级：\n");
            s_gets(athle.grade,10);
            printf("学院：\n");
            s_gets(athle.college,20);
            printf("专业：\n");
            s_gets(athle.major,20);
            //根据代表队机制选择代表队
            getTeamMechanism();
            judgeMechanism=1;//不能再修改代表队属性
            //代表队属性
            if(strcmp(teamMechanism,"学院")==0)
            {strcpy(athle.preteam,athle.college);}
            else if(strcmp(teamMechanism,"专业")==0)
                 {strcpy(athle.preteam,athle.major);}
                 else if(strcmp(teamMechanism,"年级")==0)
                     {strcpy(athle.preteam,athle.grade);}

            fwrite(&athle, sizeof(struct athletes),1,fp);
            fclose(fp);
            printf("增加运动员%s成功。",athle.name);
        }else{
            adminControl();
        }
    }
    else{
        printf("Cannot find athlete file!");
    }
}

void changeAthlete(){
    int changeNumber;
    int count=0;

    struct athletes athle[newsNumber];
    char choose;
    printf("输入要修改的运动员的学号:·····返回管理员界面请按0");
    scanf("%d",&changeNumber);
    if(changeNumber!=0){
        getchar();
        printf("确定修改?(y/n)：·····返回管理员界面请按0");
        scanf("%c",&choose);
        getchar();
        if(choose=='y'){
            FILE *fp=NULL;
            if((fp=fopen("news.txt","rb"))!=NULL){
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
            if((fp=fopen("news.txt","wb+"))!=NULL){
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

/*------------对athlete的增删改查-end----------------*/


char *s_gets(char *st,int n){
    char * ret_val;
    char *find;

    ret_val=fgets(st,n,stdin);    //存入st中 ，读取n个（包括换行符），从标准输入中读
    if(ret_val)
    {
        find=strchr(st,'\n');  //strchr找到换行符
        if(find)
            *find='\0';        //如果找到了就替换成空格符
        else
            while(getchar()!='\n')
                continue;
    }
    return ret_val;
}