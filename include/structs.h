#ifndef STRUCTS_H
#define STRUCTS_H

// 评论结构体（前向声明，用于News结构体中的comments指针）
typedef struct Comment Comment;

// 用户结构体
typedef struct User {
    char username[50];       // 用户名
    char password[50];       // 密码
    int role;                // 角色：0-访客，1-普通用户，2-管理员
    struct User *next;       // 链表指针
} User;

// 新闻结构体
typedef struct News {
    char id[20];             // 新闻ID（唯一标识）
    char title[100];         // 新闻标题
    char content[1000];      // 新闻内容
    char author[50];         // 发布者
    char category[20];       // 新闻分类
    char publishDate[20];    // 发布日期
    char imagePath[200];     // 新闻图片路径
    int status;              // 状态：0-未审核，1-已审核，2-已删除
    Comment *comments;       // 评论链表
    struct News *next;       // 链表指针
} News;

// 评论结构体
typedef struct Comment {
    char newsId[20];         // 所属新闻ID
    char username[50];       // 评论用户
    char content[500];       // 评论内容
    char commentDate[20];    // 评论日期
    struct Comment *next;    // 链表指针
} Comment;

#endif /* STRUCTS_H */
