#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/comment.h"
#include "../include/file.h"
#include "../include/list.h"
#include "../include/utils.h"

// 全局评论列表指针
static Comment* globalCommentList = NULL;

// 评论添加函数
Comment* addComment(char* newsId, char* username, char* content) {
    if (newsId == NULL || username == NULL || content == NULL) {
        printf("参数不能为空\n");
        return NULL;
    }
    
    if (strlen(newsId) == 0 || strlen(username) == 0 || strlen(content) == 0) {
        printf("新闻ID、用户名和评论内容不能为空\n");
        return NULL;
    }
    
    char currentDate[20];
    getCurrentDate(currentDate);
    //创建新节点
    Comment* newComment = createCommentNode(newsId, username, content, currentDate);
    if (newComment == NULL) {
        printf("创建评论失败\n");
        return NULL;
    }
    //插入评论链表
    insertCommentNode(&globalCommentList, newComment);
    //保存到文件
    saveCommentsToFile(globalCommentList, COMMENT_FILE);
    
    printf("评论添加成功\n");
    return newComment;
}

// 评论查询函数（根据新闻ID获取该新闻的所有评论）
Comment* getCommentsByNewsId(char* newsId) {
    if (newsId == NULL || strlen(newsId) == 0) {
        printf("新闻ID不能为空\n");
        return NULL;
    }
    
    if (globalCommentList == NULL) {
        globalCommentList = loadCommentsFromFile(COMMENT_FILE);
    }
    
    Comment* result = NULL;
    Comment* temp = globalCommentList;
    
    while (temp != NULL) {
        if (strcmp(temp->newsId, newsId) == 0) {
            Comment* newComment = createCommentNode(
                temp->newsId,
                temp->username,
                temp->content,
                temp->commentDate
            );
            if (newComment != NULL) {
                insertCommentNode(&result, newComment);
            }
        }
        temp = temp->next;
    }
    
    return result;
}

// 评论显示函数
void displayComments(Comment* comments) {
    if (comments == NULL) {
        printf("暂无评论\n");
        return;
    }
    
    printf("\n========== 评论列表 ==========\n");
    
    Comment* temp = comments;
    int count = 1;
    
    while (temp != NULL) {
        printf("\n【评论 %d】\n", count);
        printf("  评论用户: %s\n", temp->username);
        printf("  评论日期: %s\n", temp->commentDate);
        printf("  评论内容: %s\n", temp->content);
        printf("  ------------------------\n");
        
        temp = temp->next;
        count++;
    }
    
    printf("\n=============================\n");
}

// 评论删除函数（根据新闻ID和评论日期删除评论）
int deleteComment(char* newsId, char* username, char* commentDate) {
    if (newsId == NULL || username == NULL || commentDate == NULL) {
        printf("参数不能为空\n");
        return 0;
    }
    
    if (globalCommentList == NULL) {
        globalCommentList = loadCommentsFromFile(COMMENT_FILE);
    }
    
    Comment* prev = NULL;
    Comment* current = globalCommentList;
    int found = 0;
    
    while (current != NULL) {
        if (strcmp(current->newsId, newsId) == 0 &&
            strcmp(current->username, username) == 0 &&
            strcmp(current->commentDate, commentDate) == 0) {
            
            if (prev == NULL) {
                globalCommentList = current->next;
            } else {
                prev->next = current->next;
            }
            
            free(current);
            found = 1;
            break;
        }
        
        prev = current;
        current = current->next;
    }
    
    if (found) {
        saveCommentsToFile(globalCommentList, COMMENT_FILE);
        printf("评论删除成功\n");
        return 1;
    } else {
        printf("未找到指定的评论\n");
        return 0;
    }
}

// 获取所有评论列表函数
Comment* getCommentList() {
    if (globalCommentList == NULL) {
        globalCommentList = loadCommentsFromFile(COMMENT_FILE);
    }
    return globalCommentList;
}

// 根据用户名获取该用户的所有评论
Comment* getCommentsByUsername(char* username) {
    if (username == NULL || strlen(username) == 0) {
        printf("用户名不能为空\n");
        return NULL;
    }
    
    if (globalCommentList == NULL) {
        globalCommentList = loadCommentsFromFile(COMMENT_FILE);
    }
    
    Comment* result = NULL;
    Comment* temp = globalCommentList;
    
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0) {
            Comment* newComment = createCommentNode(
                temp->newsId,
                temp->username,
                temp->content,
                temp->commentDate
            );
            if (newComment != NULL) {
                insertCommentNode(&result, newComment);
            }
        }
        temp = temp->next;
    }
    
    return result;
}

// 统计新闻的评论数量
int countComments(char* newsId) {
    if (newsId == NULL || strlen(newsId) == 0) {
        return 0;
    }
    
    if (globalCommentList == NULL) {
        globalCommentList = loadCommentsFromFile(COMMENT_FILE);
    }
    
    int count = 0;
    Comment* temp = globalCommentList;
    
    while (temp != NULL) {
        if (strcmp(temp->newsId, newsId) == 0) {
            count++;
        }
        temp = temp->next;
    }
    
    return count;
}