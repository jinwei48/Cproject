#ifndef COMMENT_H
#define COMMENT_H

#include "structs.h"

// 评论数据文件名
#define COMMENT_FILE "comments.txt"

// 评论添加函数
Comment* addComment(char* newsId, char* username, char* content);

// 评论查询函数（根据新闻ID获取该新闻的所有评论）
Comment* getCommentsByNewsId(char* newsId);

// 评论显示函数
void displayComments(Comment* comments);

// 评论删除函数（根据评论ID和新闻ID删除评论）
int deleteComment(char* newsId, char* username, char* commentDate);

// 获取所有评论列表函数
Comment* getCommentList();

// 根据用户名获取该用户的所有评论
Comment* getCommentsByUsername(char* username);

// 释放评论链表内存
void freeCommentList(Comment* commentList);

// 统计新闻的评论数量
int countComments(char* newsId);

#endif /* COMMENT_H */
