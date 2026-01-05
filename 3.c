#include<stdio.h>
struct student
{
    int num;
    char name[12];
    float score;
};
int main(){
    struct student stu[3]={{1001,"zhang",80},{1002,"wang",82},{1003,"chen",95}};
    struct student temp;
    for(int i=0;i<2;i++){
        for(int j=i+1;j<3;j++){
            if(stu[j].score>stu[i].score){
               temp=stu[j];stu[j]=stu[i];stu[i]=temp;
            }
        }
    }
    for(int i=0;i<3;i++)
        printf("%6d %8s %6.2f\n",stu[i].num,stu[i].name,stu[i].score);
    return 0;
}   