#ifndef LIST_H
#define LIST_H

#include "structs.h"

// ===================== User链表操作函数 =====================

// 创建新的User节点
User* createUserNode(char* username, char* password, int role);

// 插入User节点到链表尾部
void insertUserNode(User** head, User* newNode);

// 根据用户名删除User节点
int deleteUserNode(User** head, char* username);

// 根据用户名查找User节点
User* findUserNode(User* head, char* username);

// 遍历并显示所有User节点
void displayUserList(User* head);

// 释放User链表的所有内存
void freeUserList(User* head);

// 获取User链表的长度
int getUserListLength(User* head);

// ===================== News链表操作函数 =====================

// 创建新的News节点
News* createNewsNode(char* id, char* title, char* content, char* author, char* category, char* publishDate, char* imagePath, int status);

// 插入News节点到链表尾部
void insertNewsNode(News** head, News* newNode);

// 根据ID删除News节点
int deleteNewsNode(News** head, char* id);

// 根据ID查找News节点
News* findNewsNode(News* head, char* id);

// 遍历并显示所有News节点
void displayNewsList(News* head);

// 释放News链表的所有内存
void freeNewsList(News* head);

// 获取News链表的长度
int getNewsListLength(News* head);

// ===================== Comment链表操作函数 =====================

// 创建新的Comment节点
Comment* createCommentNode(char* newsId, char* username, char* content, char* commentDate);

// 插入Comment节点到链表尾部
void insertCommentNode(Comment** head, Comment* newNode);

// 根据新闻ID删除所有相关Comment节点
int deleteCommentsByNewsId(Comment** head, char* newsId);

// 根据新闻ID查找所有相关Comment节点
Comment* findCommentsByNewsId(Comment* head, char* newsId);

// 遍历并显示所有Comment节点
void displayCommentList(Comment* head);

// 释放Comment链表的所有内存
void freeCommentList(Comment* head);

// 获取Comment链表的长度
int getCommentListLength(Comment* head);

#endif /* LIST_H */
