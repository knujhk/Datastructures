#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef  struct {
    char name[10];
    int  age;
    int  math;
    int  english;
    int  history;
}STUDENT;

STUDENT* std[500];      //500명 정보 저장 가능
int num = 0, i = 0, j = 0;    //NUM = 자료개수

void create_student(char file[]);   //구조체 변수에 동적 메모리 할당 후 학생정보 저장
void sort_std(int type);
void print_std(int type);           //정렬 type에 맞게 출력
void line();                        //========


int main()
{
    char file_name[30];
    int menu, type;


    line();
    while (1)
    {
        printf("1) Insert\n2) Sort\n3) Quit\n");
        printf("select a menu : ");
        scanf("%d", &menu);
        getchar();

        if (menu == 1)
        {
            printf("\nFile name : ");
            gets(file_name);
            create_student(file_name);
            printf("\n");
            line();
        }
        else if (menu == 2)
        {
            if(std[0]==NULL)
            {
                printf("\nResult : There is no data to be sorted. Program terminates.");
                exit(0);
            }
            printf("\n\n1) Name\n2) Age\n3) Math\n4) english\n5) history\n");
            printf("Choose the field to sort by : ");
            scanf("%d",&type);
            getchar();
            sort_std(type);
            print_std(type);
            line();
        }
        else 
        {
            for (i = 0; i<num-1;i++)
                free(std[i]);
            line();
            exit(0);
        }
    }

    return 0;
}
void create_student(char file[])        //파일 열고 구조체에 동적할당, 저장
{

    FILE* fp = fopen(file, "r");
    while (feof(fp) == 0) //fp위치가 파일 끝이면 1 반환
    {
        std[num] = (STUDENT*)malloc(sizeof(STUDENT));
        fscanf(fp, "%s %d %d %d %d", std[num]->name, &std[num]->age
            , &std[num]->math, &std[num]->english, &std[num]->history);     
            
        if ((std[num]->age) <= 0 )                                          //age 범위 체크
        {
            printf("Result : The age cannot be a negative number. Program terminates.");
            for (i = 0; i<num-1;i++)
                free(std[i]);
            exit(0);
        }
        else if ((std[num]->math<0||std[num]->math>100)||(std[num]->english<0||std[num]->english>100)   //성적 범위 체크
                    ||(std[num]->history<0||std[num]->history>100))
        {
            printf("Result : The scores should be in [0,100]. Program terminates.");
            for (i = 0; i<num-1;i++)
                free(std[i]);
            exit(0);
        }
        
        num++;
    }
    printf("Result :\n");
    printf("No Name Age Math English History\n");
    for (i = 0; i < num; i++)
        printf("%d %s %d %d %d %d\n", i + 1, std[i]->name, std[i]->age, std[i]->math, std[i]->english, std[i]->history);
    fclose(fp);
}
void sort_std(int type)             //case별로 정렬
{
    STUDENT* temp  = NULL;
    int flag = 0;
    
    switch (type)
    {
    case 1:         //NAME
        for (i = 0, temp = NULL; i < num-2; i++)
        {
            for (j=0, flag = 0; j < num-2; j++)
            {
                if(strcmp(std[j]->name,std[j+1]->name) >0)
                {    
                    temp = std[j];
                    std[j] = std[j+1];
                    std[j+1] = temp;
                    flag=1;
                }    
            }
            if (flag == 1)
                break;
        }
        break;
    case 2:         //AGE
        for (i = 0; i < num; i++)
        {
            for (j=0, flag = 0; j < num-2; j++)
            {
                if((std[j]->age > std[j+1]->age))
                {    
                    temp = std[j];
                    std[j] = std[j+1];
                    std[j+1] = temp;
                    flag=1;
                }    
            }
            if (flag == 1)
                break;
        }
        break;
    case 3:         //MATH
        for (i = 0; i < num; i++)
        {
            for (j=0, flag = 0; j < num-2; j++)
            {
                if((std[j]->math > std[j+1]->math))
                {    
                    temp = std[j];
                    std[j] = std[j+1];
                    std[j+1] = temp;
                    flag=1;
                }    
            }
            if (flag == 1)
                break;
        }
        break;      
    case 4:         //ENGLISH
        for (i = 0; i < num; i++)
         {
            for (j=0, flag = 0; j < num-2; j++)
            {
                if((std[j]->english > std[j+1]->english))
                {    
                    temp = std[j];
                    std[j] = std[j+1];
                    std[j+1] = temp;
                    flag=1;
                }    
            }
            if (flag == 1)
                break;
        }
        break;
    case 5:         //HISTORY
        for (i = 0; i < num; i++)
         {
            for (j=0, flag = 0; j < num-2; j++)
            {
                if((std[j]->history > std[j+1]->history))
                {    
                    temp = std[j];
                    std[j] = std[j+1];
                    std[j+1] = temp;
                    flag=1;
                }    
            }
            if (flag == 1)
                break;
        }   
        break;
    }
}
void print_std(int type) 
{

    switch (type)
    {
    case 1:
        printf("\n\nNo Name Age Math English History\n");
        for (i = 0; i < num; i++)
            printf("%d %s %d %d %d %d\n", i + 1, std[i]->name, std[i]->age, std[i]->math, std[i]->english, std[i]->history);
        break;
    case 2:
        printf("\n\nNo Age Name Math English History\n");
        for (i = 0; i < num; i++)
            printf("%d %d %s %d %d %d\n", i + 1, std[i]->age, std[i]->name, std[i]->math, std[i]->english, std[i]->history);
        break;
    case 3:
        printf("\n\nNo Math Name Age English History\n");
        for (i = 0; i < num; i++)
            printf("%d %d %s %d %d %d\n", i + 1, std[i]->math, std[i]->name, std[i]->age, std[i]->english, std[i]->history);
        break;
    case 4:
        printf("\n\nNo English Name Age Math History\n");
        for (i = 0; i < num; i++)
            printf("%d %d %s %d %d %d\n", i + 1, std[i]->english, std[i]->name, std[i]->age, std[i]->math, std[i]->history);
        break;
    case 5:
        printf("\n\nNo History Name Age Math English\n");
        for (i = 0; i < num; i++)
            printf("%d %d %s %d %d %d\n", i + 1, std[i]->history, std[i]->name, std[i]->age, std[i]->math, std[i]->english);
        break;
    }

}
void line()
{

    for (i = 0; i < 25; i++)
        printf("=");
    printf("\n");
}