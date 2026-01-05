#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/file.h"
#include "../include/list.h"

// ===================== 用户数据文件操作函数实现 =====================

// 保存用户数据到文件
int saveUsersToFile(User* userList, char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        return 0;
    }
    
    User* temp = userList;
    while (temp != NULL) {
        fprintf(file, "%s,%s,%d\n", temp->username, temp->password, temp->role);//将用户数据写入文件
        temp = temp->next;
    }
    
    fclose(file);
    return 1;
}

// 从文件加载用户数据
User* loadUsersFromFile(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        // 文件不存在，返回空链表
        return NULL;
    }
    //初始化变量
    User* userList = NULL;
    char line[200];
    //逐行读取文件内容，fgets从文件中读取一行数据存入line，直到文件结束
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // 移除换行符
        
        char username[50];
        char password[50];
        int role;
        
        // 解析行数据。%[^,]是扫描集语法，表示^排除逗号，匹配除逗号以外的所有字符
        if (sscanf(line, "%[^,],%[^,],%d", username, password, &role) == 3) {  //返回3个匹配值
            User* newUser = createUserNode(username, password, role);
            if (newUser != NULL) {
                insertUserNode(&userList, newUser);
            }
        }
    }
    
    fclose(file);
    return userList;
}

// ===================== 新闻数据文件操作函数实现 =====================

// 保存新闻数据到文件
int saveNewsToFile(News* newsList, char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        return 0;
    }
    
    News* temp = newsList;
    int is_first = 1;      // 用于判断是否是第一条新闻，1表示是第一条，0表示不是第一条
    
    while (temp != NULL) {
        if (is_first==0) {
            fprintf(file, "---\n");
        }
        is_first = 0;
        
        fprintf(file, "ID: %s\n", temp->id);
        fprintf(file, "Title: %s\n", temp->title);
        fprintf(file, "Content: %s\n", temp->content);
        fprintf(file, "Author: %s\n", temp->author);
        fprintf(file, "Category: %s\n", temp->category);
        fprintf(file, "PublishDate: %s\n", temp->publishDate);
        fprintf(file, "ImagePath: %s\n", temp->imagePath);
        fprintf(file, "Status: %d\n", temp->status);
        
        temp = temp->next;
    }
    
    fclose(file);
    return 1;
}

// 从文件加载新闻数据
News* loadNewsFromFile(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        // 文件不存在，返回空链表
        return NULL;
    }
    
    News* newsList = NULL;
    char line[200];
    
    // 解析新闻数据
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // 移除换行符
        
        if (strncmp(line, "ID: ", 4) == 0) { //判断当前读取的行是否是以”ID：“开头
            // 开始解析一条新新闻
            char id[20];
            char title[100];
            char content[1000];
            char author[50];
            char category[20];
            char publishDate[20];
            char imagePath[200];
            int status;
            
            // 初始化 imagePath 为空字符串
            imagePath[0] = '\0';
            
            // 解析ID
            strcpy(id, line + 4);
            
            // 解析Title
            if (fgets(line, sizeof(line), file) != NULL) {
                line[strcspn(line, "\n")] = '\0';
                if (strncmp(line, "Title: ", 7) == 0) {
                    strcpy(title, line + 7);
                }
            }
            
            // 解析Content
            if (fgets(line, sizeof(line), file) != NULL) {
                line[strcspn(line, "\n")] = '\0';
                if (strncmp(line, "Content: ", 9) == 0) {
                    strcpy(content, line + 9);
                }
            }
            
            // 解析Author
            if (fgets(line, sizeof(line), file) != NULL) {
                line[strcspn(line, "\n")] = '\0';
                if (strncmp(line, "Author: ", 8) == 0) {
                    strcpy(author, line + 8);
                }
            }
            
            // 解析Category
            if (fgets(line, sizeof(line), file) != NULL) {
                line[strcspn(line, "\n")] = '\0';
                if (strncmp(line, "Category: ", 10) == 0) {
                    strcpy(category, line + 10);
                }
            }
            
            // 解析PublishDate
            if (fgets(line, sizeof(line), file) != NULL) {
                line[strcspn(line, "\n")] = '\0';
                if (strncmp(line, "PublishDate: ", 13) == 0) {
                    strcpy(publishDate, line + 13);
                }
            }
            
            // 解析ImagePath
            if (fgets(line, sizeof(line), file) != NULL) {
                line[strcspn(line, "\n")] = '\0';
                if (strncmp(line, "ImagePath: ", 11) == 0) {
                    strcpy(imagePath, line + 11);
                }
            }
            
            // 解析Status
            if (fgets(line, sizeof(line), file) != NULL) {
                line[strcspn(line, "\n")] = '\0';
                if (strncmp(line, "Status: ", 8) == 0) {
                    sscanf(line + 8, "%d", &status);
                }
            }
            
            // 创建新闻节点
            News* newNews = createNewsNode(id, title, content, author, category, publishDate, imagePath, status);
            if (newNews != NULL) {
                insertNewsNode(&newsList, newNews);
            }
            
            // 跳过分隔符
            if (fgets(line, sizeof(line), file) != NULL) {
                line[strcspn(line, "\n")] = '\0';
            }
        }
    }
    
    fclose(file);
    return newsList;
}

// 保存已删除新闻数据到文件
int saveDeletedNewsToFile(News* newsList, char* filename) {
    // 与保存普通新闻相同的格式
    return saveNewsToFile(newsList, filename);
}

// 从文件加载已删除新闻数据
News* loadDeletedNewsFromFile(char* filename) {
    // 与加载普通新闻相同的格式
    return loadNewsFromFile(filename);
}

// ===================== 评论数据文件操作函数实现 =====================

// 保存评论数据到文件
int saveCommentsToFile(Comment* commentList, char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        return 0;
    }
    
    Comment* temp = commentList;
    while (temp != NULL) {
        fprintf(file, "%s,%s,%s,%s\n", temp->newsId, temp->username, temp->content, temp->commentDate);
        temp = temp->next;
    }
    
    fclose(file);
    return 1;
}

// 从文件加载评论数据
Comment* loadCommentsFromFile(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        // 文件不存在，返回空链表
        return NULL;
    }
    
    Comment* commentList = NULL;
    char line[1000];
    
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // 移除换行符，计算line从开头到第一个\n的字符长度，并将其替换为'\0
        
        char newsId[20];
        char username[50];
        char content[500];
        char commentDate[20];
        
        // 解析行数据
        // 使用strtok处理包含逗号的内容
        char* token;
        
        // 解析新闻ID
        token = strtok(line, ",");
        if (token != NULL) {
            strcpy(newsId, token);
        } else {
            continue;
        }
        
        // 解析用户名
        token = strtok(NULL, ",");
        if (token != NULL) {
            strcpy(username, token);
        } else {
            continue;
        }
        
        // 解析评论内容（可能包含逗号）
        token = strtok(NULL, ",");
        if (token != NULL) {
            strcpy(content, token);
            // 处理内容中可能包含的逗号
            char* rest;
            while ((rest = strtok(NULL, ",")) != NULL) {
                strcat(content, ",");
                strcat(content, rest);
            }
        } else {
            continue;
        }
        
        // 解析评论日期
        // 日期应该在最后，没有逗号
        int contentLen = strlen(content);
        int lastCommaIndex = -1;
        for (int i = contentLen - 1; i >= 0; i--) {
            if (content[i] == ',') {
                lastCommaIndex = i;
                break;
            }
        }
        
        if (lastCommaIndex != -1) {
            strcpy(commentDate, content + lastCommaIndex + 1);
            content[lastCommaIndex] = '\0'; // 截断内容
        } else {
            continue;
        }
        
        // 创建评论节点
        Comment* newComment = createCommentNode(newsId, username, content, commentDate);
        if (newComment != NULL) {
            insertCommentNode(&commentList, newComment);
        }
    }
    
    fclose(file);
    return commentList;
}

// ===================== 分类数据文件操作函数实现 =====================

// 保存分类数据到文件
int saveCategoriesToFile(char** categories, int count, char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        return 0;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n", categories[i]);
    }
    
    fclose(file);
    return 1;
}

// 从文件加载分类数据
char** loadCategoriesFromFile(char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        // 文件不存在，就返回默认的3个分类
        *count = 3;
        // 先为指针数组分配内存
        char** defaultCategories = (char**)malloc(*count * sizeof(char*));
        if (defaultCategories == NULL) {
            return NULL;
        }
        // 为每个分类字符串分配内存
        defaultCategories[0] = (char*)malloc((strlen("通知")+1) * sizeof(char));
        defaultCategories[1] = (char*)malloc((strlen("公告")+1) * sizeof(char));
        defaultCategories[2] = (char*)malloc((strlen("简讯")+1) * sizeof(char));
        
        strcpy(defaultCategories[0], "通知");
        strcpy(defaultCategories[1], "公告");
        strcpy(defaultCategories[2], "简讯");
        
        return defaultCategories;
    }
    
    // 先计算行数
    int lineCount = 0;
    char line[50];
    
    while (fgets(line, sizeof(line), file) != NULL) {
        lineCount++;
    }
    
    // 重置文件指针
    fseek(file, 0, SEEK_SET);
    
    // 分配内存
    char** categories = (char**)malloc(lineCount * sizeof(char*));
    if (categories == NULL) {
        fclose(file);
        return NULL;
    }
    
    // 读取分类
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // 移除换行符
        categories[i] = (char*)malloc((strlen(line) + 1) * sizeof(char));
        if (categories[i] == NULL) {
            // 释放已分配的内存
            for (int j = 0; j < i; j++) {
                free(categories[j]);
            }
            free(categories);
            fclose(file);
            return NULL;
        }
        strcpy(categories[i], line);
        i++;
    }
    
    fclose(file);
    *count = lineCount;
    return categories;
}

// 释放分类数组的内存
void freeCategories(char** categories, int count) {
    for (int i = 0; i < count; i++) {
        free(categories[i]);
    }
    free(categories);
}
