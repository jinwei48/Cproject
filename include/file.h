#ifndef FILE_H
#define FILE_H

#include "structs.h"

// ===================== 用户数据文件操作函数 =====================

// 保存用户数据到文件
int saveUsersToFile(User* userList, char* filename);

// 从文件加载用户数据
User* loadUsersFromFile(char* filename);

// ===================== 新闻数据文件操作函数 =====================

// 保存新闻数据到文件
int saveNewsToFile(News* newsList, char* filename);

// 从文件加载新闻数据
News* loadNewsFromFile(char* filename);

// 保存已删除新闻数据到文件
int saveDeletedNewsToFile(News* newsList, char* filename);

// 从文件加载已删除新闻数据
News* loadDeletedNewsFromFile(char* filename);

// ===================== 评论数据文件操作函数 =====================

// 保存评论数据到文件
int saveCommentsToFile(Comment* commentList, char* filename);

// 从文件加载评论数据
Comment* loadCommentsFromFile(char* filename);

// ===================== 分类数据文件操作函数 =====================

// 保存分类数据到文件
int saveCategoriesToFile(char** categories, int count, char* filename);

// 从文件加载分类数据
char** loadCategoriesFromFile(char* filename, int* count);

// 释放分类数据的内存
void freeCategories(char** categories, int count);

#endif /* FILE_H */
