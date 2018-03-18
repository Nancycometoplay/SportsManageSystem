//
// Created by Chan on 2018/3/11.
//

#include <stdio.h>

#include <memory.h>

char *s_gets(char *st,int n);

//struct account{
//    char username[10];
//    char password[10];
//};

int main(void){
    struct account acc[2];
    for(int i=0;i<2;i++){
        s_gets(acc[i].username,10);
        printf("password\n");
        s_gets(acc[i].password,10);
        printf("username\n");
    }
    FILE *fp=NULL;
    fp=fopen("account.dat","wb");
    for(int i=0;i<2;i++)
       fwrite(&acc[i], sizeof(struct account),1,fp);
        //fprintf(fp,"%s %s ",acc[i].username,acc[i].password);
    fclose(fp);
    return 0;
}

char *s_gets(char *st,int n){
    char * ret_val;
    char *find;

    ret_val=fgets(st,n,stdin);
    if(ret_val){
        find=strchr(st,'\n');
        if(find)
            *find='\0';
        else
            while(getchar()!='\n')
                continue;
    }
    return ret_val;
}