//
// Created by Nancy on 18/3/20.
//

#ifndef SPORTSYSTEM_2_FILE_OPERATION_H
#define SPORTSYSTEM_2_FILE_OPERATION_H

#endif //SPORTSYSTEM_2_FILE_OPERATION_H

//#include "Liner_List_Operation.h"


int ReadFromFile(char* filename,struct athletes athle[],FILE *fp  )
{
    int count=0;
    if ((fp = fopen(filename, "rb")) != NULL) {  //更新模式
        while (!feof(fp)) {
            fread(&athle[count], sizeof(struct athletes), 1, fp);
            count++;
        }
        count -= 2; //why?  feof多读了一次，最后多读了一次
        fclose(fp);
        return count;  //从0开始的
    }
}

void WriteInFile(char* filename,struct athletes athle[],int number,FILE *fp)//需要传入结构数组的数目（就是下标）
{

//    if ((fp = fopen(filename, "wb")) != NULL) {  //重写模式
//        while () {
//            f(&athle[count], sizeof(struct athletes), 1, fp);
//            count++;
//        }
//        count -= 2; //why?  feof多读了一次，最后多读了一次
//        fclose(fp);
//        return count;  //从0开始的
//    }
        if((fp=fopen(filename,"wb+"))!=NULL){   //重写模式
            for(int i=0;i<=number;i++)
                fwrite(&athle[i], sizeof(struct athletes),1,fp);
            fclose(fp);

        }else{
            printf("Cannot find the file!");
        }
}