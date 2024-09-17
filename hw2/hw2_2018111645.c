#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int asc_chk(int set[]);
void sort_dsc(int set[]);

int main()
{
    char input[2][100];
    char* ptr = NULL;
    int num[20];
    int i = 0, j = 0;
    int flag = 0;

    printf("Input :\n");

    for (i = 0; i < 2; i++)
    {
        gets(input[i]);                     //한 줄 받기
        ptr = strtok(input[i], ", ");       //첫 번째 숫자(문자열)을 포인터에 넣기
        do
        {
            num[j] = atoi(ptr);             //ATOI로 문자열을 정수형으로 변환
            j++;
            ptr = strtok(NULL, ", ");
            flag++;
        } while (ptr != NULL);      //NULL이 들어갔다면 중지

        if (flag != 10)             //정수를 10개 입력했는가
        {
            printf("You must input 2 sets of 10 numbers\n\n");
            exit(0);
        }

        if (asc_chk(num) == 0)        //오름차순인지 확인
        {
            printf("The input numbers are not in ascending order.\n\n");
            exit(0);
        }
        flag = 0;
    }
    sort_dsc(num);                  //내림차순 정렬

    printf("output :\n\n");
    for (j = 0; j < 20; j++)
    {
        if (num[j] != num[j + 1])
            printf("%d ", num[j]);  //다음 숫자와 달라야만 출력하기
    }
    return 0;
}
int asc_chk(int set[])
{
    int k = 0;
    int asc = 1; //오름차순이 아니라면 0이 됨

    for (k = 0; k < 20; k++)
    {
        if (set[k] > set[k + 1])
        {
            asc = 0;
            break;
        }
    }
    return asc;
}
void sort_dsc(int set[])
{
    int i = 0, j = 0;
    int str = 0;
    int change = 0;

    for (i = 0; i < 19; i++)
    {
        for (j = 0, change = 0; j < 19; j++)
        {
            if (set[j] < set[j + 1])
            {
                str = set[j];
                set[j] = set[j + 1];
                set[j + 1] = str;
                change = 1;
            }
        }
        if (change == 0)
            break; //정렬 끝, 반복문 탈출
    }
}