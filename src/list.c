#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"

// ===================== User链表操作函数实现 =====================

// 创建新的User节点
User* createUserNode(char* username, char* password, int role) {
    User* newNode = (User*)malloc(sizeof(User));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        return NULL;
    }
    strcpy(newNode->username, username);
    strcpy(newNode->password, password);
    newNode->role = role;
    newNode->next = NULL;
    return newNode;
}

// 插入User节点到链表尾部
void insertUserNode(User** head, User* newNode) {
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    User* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// 根据用户名删除User节点
int deleteUserNode(User** head, char* username) {
    if (*head == NULL) {
        return 0; // 链表为空
    }
    
    User* temp = *head;
    User* prev = NULL;
    
    // 检查头节点是否是要删除的节点
    if (strcmp(temp->username, username) == 0) {
        *head = temp->next;
        free(temp);
        return 1; // 删除成功
    }
    
    // 查找要删除的节点
    while (temp != NULL && strcmp(temp->username, username) != 0) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        return 0; // 未找到节点
    }
    
    // 删除节点
    prev->next = temp->next;
    free(temp);
    return 1; // 删除成功
}

// 根据用户名查找User节点
User* findUserNode(User* head, char* username) {
    User* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0) {
            return temp; // 找到节点
        }
        temp = temp->next;
    }
    return NULL; // 未找到节点
}

// 遍历并显示所有User节点
void displayUserList(User* head) {
    User* temp = head;
    if (temp == NULL) {
        printf("用户列表为空\n");
        return;
    }
    printf("用户名\t\t密码\t\t角色\n");
    printf("----------------------------------------\n");
    while (temp != NULL) {
        printf("%s\t\t%s\t\t%d\n", temp->username, temp->password, temp->role);
        temp = temp->next;
    }
}

// 释放User链表的所有内存
void freeUserList(User* head) {
    User* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// 获取User链表的长度
int getUserListLength(User* head) {
    int length = 0;
    User* temp = head;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}

// ===================== News链表操作函数实现 =====================

// 创建新的News节点
News* createNewsNode(char* id, char* title, char* content, char* author, char* category, char* publishDate, char* imagePath, int status) {
    News* newNode = (News*)malloc(sizeof(News));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        return NULL;
    }
    strcpy(newNode->id, id);
    strcpy(newNode->title, title);
    strcpy(newNode->content, content);
    strcpy(newNode->author, author);
    strcpy(newNode->category, category);
    strcpy(newNode->publishDate, publishDate);
    strcpy(newNode->imagePath, imagePath);
    newNode->status = status;
    newNode->comments = NULL;
    newNode->next = NULL;
    return newNode;
}

// 插入News节点到链表尾部
void insertNewsNode(News** head, News* newNode) {
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    News* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// 根据ID删除News节点
int deleteNewsNode(News** head, char* id) {
    if (*head == NULL) {
        return 0; // 链表为空
    }
    
    News* temp = *head;
    News* prev = NULL;
    
    // 检查头节点是否是要删除的节点
    if (strcmp(temp->id, id) == 0) {
        *head = temp->next;
        // 释放该新闻的评论链表
        freeCommentList(temp->comments);
        free(temp);
        return 1; // 删除成功
    }
    
    // 查找要删除的节点
    while (temp != NULL && strcmp(temp->id, id) != 0) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        return 0; // 未找到节点
    }
    
    // 删除节点
    prev->next = temp->next;
    // 释放该新闻的评论链表
    freeCommentList(temp->comments);
    free(temp);
    return 1; // 删除成功
}

// 根据ID查找News节点
News* findNewsNode(News* head, char* id) {
    News* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->id, id) == 0) {
            return temp; // 找到节点
        }
        temp = temp->next;
    }
    return NULL; // 未找到节点
}

// 遍历并显示所有News节点
void displayNewsList(News* head) {
    News* temp = head;
    if (temp == NULL) {
        printf("新闻列表为空\n");
        return;
    }
    printf("ID\t\t标题\t\t\t作者\t\t分类\t\t日期\t\t状态\n");
    printf("------------------------------------------------------------------------------------------------\n");
    while (temp != NULL) {
        printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%d\n", 
               temp->id, temp->title, temp->author, temp->category, temp->publishDate, temp->status);
        temp = temp->next;
    }
}

// 释放News链表的所有内存
void freeNewsList(News* head) {
    News* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        // 释放该新闻的评论链表
        freeCommentList(temp->comments);
        free(temp);
    }
}

// 获取News链表的长度
int getNewsListLength(News* head) {
    int length = 0;
    News* temp = head;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}

// ===================== Comment链表操作函数实现 =====================

// 创建新的Comment节点
Comment* createCommentNode(char* newsId, char* username, char* content, char* commentDate) {
    Comment* newNode = (Comment*)malloc(sizeof(Comment));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        return NULL;
    }
    strcpy(newNode->newsId, newsId);
    strcpy(newNode->username, username);
    strcpy(newNode->content, content);
    strcpy(newNode->commentDate, commentDate);
    newNode->next = NULL;
    return newNode;
}

// 插入Comment节点到链表尾部
void insertCommentNode(Comment** head, Comment* newNode) {
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Comment* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// 根据新闻ID删除所有相关Comment节点
int deleteCommentsByNewsId(Comment** head, char* newsId) {
    if (*head == NULL) {
        return 0; // 链表为空
    }
    
    Comment* temp = *head;
    Comment* prev = NULL;
    int count = 0;
    
    while (temp != NULL) {
        if (strcmp(temp->newsId, newsId) == 0) {
            // 需要删除当前节点
            Comment* toDelete = temp;
            
            if (prev == NULL) {
                // 删除头节点
                *head = temp->next;
                temp = *head;
            } else {
                prev->next = temp->next;
                temp = prev->next;
            }
            
            free(toDelete);
            count++;
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
    
    return count; // 返回删除的节点数量
}

// 根据新闻ID查找所有相关Comment节点
Comment* findCommentsByNewsId(Comment* head, char* newsId) {
    Comment* resultHead = NULL;
    Comment* temp = head;
    
    while (temp != NULL) {
        if (strcmp(temp->newsId, newsId) == 0) {
            // 创建一个新节点并添加到结果链表
            Comment* newNode = createCommentNode(temp->newsId, temp->username, temp->content, temp->commentDate);
            if (newNode != NULL) {
                insertCommentNode(&resultHead, newNode);
            }
        }
        temp = temp->next;
    }
    
    return resultHead;
}

// 遍历并显示所有Comment节点
void displayCommentList(Comment* head) {
    Comment* temp = head;
    if (temp == NULL) {
        printf("评论列表为空\n");
        return;
    }
    printf("新闻ID\t\t用户名\t\t评论内容\t\t\t评论日期\n");
    printf("------------------------------------------------------------------------------------------------\n");
    while (temp != NULL) {
        printf("%s\t\t%s\t\t%s\t\t%s\n", 
               temp->newsId, temp->username, temp->content, temp->commentDate);
        temp = temp->next;
    }
}

// 释放Comment链表的所有内存
void freeCommentList(Comment* head) {
    Comment* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// 获取Comment链表的长度
int getCommentListLength(Comment* head) {
    int length = 0;
    Comment* temp = head;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}
