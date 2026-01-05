#include<stdio.h>
#include<stdlib.h>
#define SIZE 15
size_t binarysearch(const int b[],int searchkey,size_t low,size_t high);
void printheader(void);
void printrow(const b[],size_t low,size_t mid,size_t high);
int main(){
    int a[SIZE];
    for(int i=0;i<SIZE;i++){
       a[i]=2*i;
    }
    printf("Enter a number between 1 and 15:");
    int key;
    scanf("%d",&key);
    printheader();
    size_t result=binarysearch(a,key,0,SIZE-1);
    if(result!=-1){
        printf("\n%d found at index %d\n",key,result);
    }else {
        printf("\n%d not found\n",key);
    }
    return 0;
}
size_t binarysearch(const int b[],int searchkey,size_t low,size_t high){
    if(low>high){return -1;}
    size_t middle=(low+high)/2;
    printrow(b,low,middle,high);
    if(searchkey==b[middle]) return middle;
    else if(searchkey<b[middle]) return binarysearch(b,searchkey,low,middle-1);
    else return binarysearch(b,searchkey,middle+1,high);
}
void printheader(void){
    puts("\nIndices:");
    for(int i=0;i<SIZE;++i){
        printf("%3u",i);
    }
    puts("");
    for(int i=1;i<=4*SIZE;++i){
        printf("%s","-");
    }puts("");
}
void printrow(const b[],size_t low,size_t mid,size_t high){
    for(size_t i=0;i<SIZE;++i){
        if(i<low||i>high){
            printf("%s","  ");
        }else if(i==mid) {printf("%3d*",b[i]);}
        else {printf("%3d",b[i]);}
    }
    puts("");
}