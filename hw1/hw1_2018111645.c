#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main()
{
    struct {
        char fullname[50]; // 전체이름
        char* lastname; // 성을 가리키는 포인터
        char* firstname; // 이름을 가리키는 포인터
        int age;
        char sex;
    } student;
    //programming going on 
    // 아래에 코드를 채워 넣으세요. 
    
    while (1)
    {
        printf("Provide your personal information:\n");
        printf("➢ Name : ");
        scanf("%[^\n]s",student.fullname);
        if(strcmp(student.fullname,"stop")==0)
            break;
            
        student.firstname = strtok(student.fullname," ");
        student.lastname = strtok(NULL," ");
        
        printf("➢ Age : ");
        scanf("%d",&student.age);
        scanf("%*c");
        
        printf("➢ Sex (M/F) : ");
        scanf("%c",&student.sex);
        getchar();

        printf("\n\nYour name is %s %s,",student.lastname,student.firstname);
        printf("You are in %d0s,",student.age/10);
        printf("Your sex is %c.\n\n",student.sex);
    }
    return 0;
}