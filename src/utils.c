#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/utils.h"

// 获取当前日期，格式：YYYY-MM-DD
void getCurrentDate(char* date) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    sprintf(date, "%04d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
}

// 比较两个日期的大小
// 返回值：1表示date1 > date2，0表示date1 == date2，-1表示date1 < date2
int compareDates(char* date1, char* date2) {
    int year1, month1, day1;
    int year2, month2, day2;
    
    // 解析日期格式：YYYY-MM-DD
    sscanf(date1, "%d-%d-%d", &year1, &month1, &day1);
    sscanf(date2, "%d-%d-%d", &year2, &month2, &day2);
    
    // 比较年份
    if (year1 > year2) return 1;
    if (year1 < year2) return -1;
    
    // 比较月份
    if (month1 > month2) return 1;
    if (month1 < month2) return -1;
    
    // 比较日期
    if (day1 > day2) return 1;
    if (day1 < day2) return -1;
    
    // 日期相等
    return 0;
}

// 生成唯一ID
char* generateId() {
    static int idCounter = 0;
    static int initialized = 0;
    char* id = (char*)malloc(20 * sizeof(char));
    
    if (!initialized) {
        // 初始化随机数生成器
        srand(time(NULL));
        // 随机生成初始计数器值，避免每次重启程序都从0开始
        idCounter = rand() % 1000;
        initialized = 1;
    }
    
    // 生成格式为newsXXXX的ID，其中XXXX是自增数字
    sprintf(id, "news%04d", idCounter++);
    
    return id;
}

// 检查字符串是否包含子字符串
int stringContains(char* str, char* substr) {
    if (str == NULL || substr == NULL) {
        return 0;
    }
    
    return strstr(str, substr) != NULL;
}

// 字符串替换函数
void replaceString(char* str, char* oldStr, char* newStr) {
    char buffer[1024] = {0};
    char* pos = str;
    int oldLen = strlen(oldStr);
    int newLen = strlen(newStr);
    
    // 查找并替换所有匹配的子字符串
    while ((pos = strstr(pos, oldStr)) != NULL) {
        // 复制旧字符串开始到匹配位置的内容
        strncat(buffer, str, pos - str);
        // 复制新字符串
        strcat(buffer, newStr);
        // 更新str指针到匹配位置之后
        str = pos + oldLen;
        // 更新pos指针到新的位置
        pos = str;
    }
    
    // 复制剩余内容
    strcat(buffer, str);
    
    // 将结果复制回原字符串
    strcpy(str - (pos - str), buffer);
}

// 字符串修剪函数（去除首尾空格）
void trimString(char* str) {
    int start = 0;
    int end = strlen(str) - 1;
    
    // 找到第一个非空格字符
    while (str[start] == ' ' || str[start] == '\t' || str[start] == '\n' || str[start] == '\r') {
        start++;
    }
    
    // 找到最后一个非空格字符
    while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n' || str[end] == '\r')) {
        end--;
    }
    
    // 如果字符串全是空格，返回空字符串
    if (end < start) {
        str[0] = '\0';
        return;
    }
    
    // 复制修剪后的字符串到原位置
    int i, j;
    for (i = start, j = 0; i <= end; i++, j++) {
        str[j] = str[i];
    }
    str[j] = '\0';
}
