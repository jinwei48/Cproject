#ifndef UTILS_H
#define UTILS_H

// 获取当前日期，格式：YYYY-MM-DD
void getCurrentDate(char* date);

// 比较两个日期的大小
// 返回值：1表示date1 > date2，0表示date1 == date2，-1表示date1 < date2
int compareDates(char* date1, char* date2);

// 生成唯一ID
char* generateId();

// 检查字符串是否包含子字符串
int stringContains(char* str, char* substr);

// 字符串替换函数
void replaceString(char* str, char* oldStr, char* newStr);

// 字符串修剪函数（去除首尾空格）
void trimString(char* str);

#endif /* UTILS_H */
