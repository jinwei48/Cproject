/**
 * @file main.c
 * @brief 校园新闻发布管理系统主程序
 * 
 * 本程序实现了一个校园新闻发布管理系统，支持用户、管理员和访客三种角色。
 * 系统功能包括新闻浏览、搜索、评论、发布、编辑、删除以及用户管理等。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/user.h"
#include "include/news.h"
#include "include/comment.h"
#include "include/ui.h"
#include "include/list.h"

/** 当前登录的用户指针 */
User* currentUser = NULL;

/**
 * @brief 运行普通用户菜单
 * 
 * 显示用户菜单并处理用户的选择，包括浏览新闻、搜索新闻、
 * 查看新闻详情、添加评论、查看我的评论、查看个人信息、修改密码和退出登录等功能。
 */
void runUserMenu() {
    int choice;
    
    do {
        showUserMenu(currentUser);
        choice = getIntInput("请选择操作: ", 0, 8);
        
        switch (choice) {
            case 1: {
                // 浏览新闻列表
                News* newsList = getNewsList();
                showNewsListPaged(newsList);
                freeNewsList(newsList);
                break;
            }
            case 2:
                // 搜索新闻
                showNewsSearch();
                break;
            case 3: {
                // 查看新闻详情
                char newsId[20];
                getStringInput("请输入新闻ID: ", newsId, sizeof(newsId));
                News* news = findNewsById(newsId);
                if (news != NULL) {
                    showNewsDetail(news);
                } else {
                    printf("\n新闻不存在！\n");
                    pauseScreen();
                }
                break;
            }
            case 4:
                // 添加评论
                showAddComment(currentUser);
                break;
            case 5: {
                // 查看我的评论
                Comment* comments = getCommentsByUsername(currentUser->username);
                if (comments != NULL) {
                    displayComments(comments);
                    freeCommentList(comments);
                } else {
                    printf("\n暂无评论！\n");
                }
                pauseScreen();
                break;
            }
            case 6:
                // 查看个人信息
                showUserInfo(currentUser);
                break;
            case 7:
                // 修改密码
                showChangePassword(currentUser);
                break;
            case 8:
                // 退出登录
                free(currentUser);
                currentUser = NULL;
                printf("\n已退出登录！\n");
                pauseScreen();
                break;
            case 0:
                break;
        }
    } while (choice != 0 && choice != 8);
}

/**
 * @brief 运行管理员菜单
 * 
 * 显示管理员菜单并处理管理员的选择，包括浏览新闻、搜索新闻、
 * 查看新闻详情、发布新闻、编辑新闻、删除新闻、用户管理、
 * 查看个人信息、修改密码和退出登录等功能。
 */
void runAdminMenu() {
    int choice;
    
    do {
        showAdminMenu();
        choice = getIntInput("请选择操作: ", 0, 18);
        
        switch (choice) {
            case 1: {
                // 浏览新闻列表
                News* newsList = getNewsList();
                showNewsListPaged(newsList);
                freeNewsList(newsList);
                break;
            }
            case 2:
                // 搜索新闻
                showNewsSearch();
                break;
            case 3: {
                // 查看新闻详情
                char newsId[20];
                getStringInput("请输入新闻ID: ", newsId, sizeof(newsId));
                News* news = findNewsById(newsId);
                if (news != NULL) {
                    showNewsDetail(news);
                } else {
                    printf("\n新闻不存在！\n");
                    pauseScreen();
                }
                break;
            }
            case 4:
                // 发布新闻
                showAddNews(currentUser);
                break;
            case 5:
                // 编辑新闻
                showEditNews(currentUser);
                break;
            case 6:
                // 删除新闻
                showDeleteNews(currentUser);
                break;
            case 7:
                // 新闻审核
                showNewsAudit();
                break;
            case 8:
                // 排序新闻
                showNewsSort();
                break;
            case 9:
                // 统计信息
                showStatistics();
                break;
            case 10:
                // 查看已删除新闻
                showDeletedNews();
                break;
            case 11:
                // 分类管理
                showCategoryManagement();
                break;
            case 12:
                // 按日期查询
                showDateSearch();
                break;
            case 13:
                // 公告发布管理
                showAnnouncementManagement();
                break;
            case 14:
                // 系统设置
                showSystemSettings();
                break;
            case 15:
                // 用户管理
                showUserManagement(currentUser);
                break;
            case 16:
                // 查看个人信息
                showUserInfo(currentUser);
                break;
            case 17:
                // 修改密码
                showChangePassword(currentUser);
                break;
            case 18:
                // 退出登录
                free(currentUser);
                currentUser = NULL;
                printf("\n已退出登录！\n");
                pauseScreen();
                break;
            case 0:
                break;
        }
    } while (choice != 0 && choice != 18);
}

/**
 * @brief 运行访客菜单
 * 
 * 显示访客菜单并处理访客的选择，包括浏览新闻列表、搜索新闻和查看新闻详情。
 * 访客只能浏览新闻，无法进行评论、发布等操作。
 */
void runGuestMenu() {
    int choice;
    
    do {
        showGuestMenu();
        choice = getIntInput("请选择操作: ", 0, 3);
        
        switch (choice) {
            case 1: {
                // 浏览新闻列表
                News* newsList = getNewsList();
                showNewsListPaged(newsList);
                freeNewsList(newsList);
                break;
            }
            case 2:
                // 搜索新闻
                showNewsSearch();
                break;
            case 3: {
                // 查看新闻详情
                char newsId[20];
                getStringInput("请输入新闻ID: ", newsId, sizeof(newsId));
                News* news = findNewsById(newsId);
                if (news != NULL) {
                    showNewsDetail(news);
                } else {
                    printf("\n新闻不存在！\n");
                    pauseScreen();
                }
                break;
            }
            case 0:
                break;
        }
    } while (choice != 0);
}

/**
 * @brief 初始化默认管理员账号
 * 
 * 检查系统中是否存在用户，如果不存在则创建默认管理员账号。
 * 默认管理员账号：用户名为admin，密码为admin123。
 */
void initializeDefaultAdmin() {
    User* userList = getUserList();
    
    if (userList == NULL) {
        printf("正在初始化系统...\n");
        User* admin = registerUser("admin", "admin123", 2);
        if (admin != NULL) {
            printf("默认管理员账号创建成功！\n");
            printf("用户名: admin\n");
            printf("密码: admin123\n");
            free(admin);
        }
    } else {
        freeUserList(userList);
    }
}

/**
 * @brief 主函数
 * 
 * 程序入口，初始化系统并显示主菜单。
 * 根据用户选择进入登录、注册或访客模式。
 * 
 * @return 程序退出状态码
 */
int main() {
    int choice;
    
    // 设置控制台编码为UTF-8以支持中文显示
    system("chcp 65001 >nul");
    
    // 初始化默认管理员账号
    initializeDefaultAdmin();
    
    do {
        showMainMenu();
        choice = getIntInput("请选择操作: ", 0, 3);
        
        switch (choice) {
            case 1:
                // 用户登录
                showUserLogin();
                if (currentUser != NULL) {
                    if (currentUser->role == 2) {
                        // 管理员登录
                        runAdminMenu();
                    } else {
                        // 普通用户登录
                        runUserMenu();
                    }
                }
                break;
            case 2:
                // 用户注册
                showUserRegister();
                break;
            case 3:
                // 访客模式
                runGuestMenu();
                break;
            case 0:
                printf("\n感谢使用校园新闻发布管理系统，再见！\n");
                break;
        }
    } while (choice != 0);
    
    return 0;
}
