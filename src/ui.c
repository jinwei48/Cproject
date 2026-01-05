#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/ui.h"
#include "../include/news.h"
#include "../include/comment.h"
#include "../include/user.h"
#include "../include/list.h"

// 当前登录用户的全局变量
extern User* currentUser;

/**
 * 清屏函数
 * 使用系统命令清空屏幕显示
 */
void clearScreen() {
    system("cls");
}

/**
 * 暂停屏幕函数
 * 等待用户按任意键后继续程序执行
 */
void pauseScreen() {
    printf("\n按任意键继续...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

/**
 * 打印标题头部
 * @param title 标题文本
 */
void printHeader(char* title) {
    printf("\n");
    printf("========================================\n");
    printf("            %s\n", title);
    printf("========================================\n");
}

/**
 * 打印底部边框
 */
void printFooter() {
    printf("========================================\n");
}

/**
 * 打印分隔线
 */
void printSeparator() {
    printf("----------------------------------------\n");
}

/**
 * 获取整数输入
 * @param prompt 提示信息
 * @param min 最小值
 * @param max 最大值
 * @return 用户输入的有效整数
 */
int getIntInput(char* prompt, int min, int max) {
    int value;
    char buffer[100];
    
    while (1) {
        printf("%s", prompt);
        fgets(buffer, sizeof(buffer), stdin);
        
        if (sscanf(buffer, "%d", &value) == 1) {
            if (value >= min && value <= max) {
                return value;
            }
        }
        
        printf("输入无效，请输入 %d 到 %d 之间的整数。\n", min, max);
    }
}

/**
 * 获取字符串输入
 * @param prompt 提示信息
 * @param buffer 存储输入的缓冲区
 * @param maxLength 缓冲区最大长度
 */
void getStringInput(char* prompt, char* buffer, int maxLength) {
    printf("%s", prompt);
    fgets(buffer, maxLength, stdin);
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

/**
 * 显示主菜单
 * 显示系统主菜单，包括用户登录、用户注册和访客浏览新闻等选项
 */
void showMainMenu() {
    clearScreen();
    printHeader("校园新闻发布管理系统");
    printf("\n");
    printf("  1. 用户登录\n");
    printf("  2. 用户注册\n");
    printf("  3. 访客浏览新闻\n");
    printf("  0. 退出系统\n");
    printFooter();
}

/**
 * 显示用户菜单
 * @param user 当前登录的用户指针
 */
void showUserMenu(User* user) {
    clearScreen();
    printHeader("用户菜单");
    printf("\n");
    printf("  欢迎您，%s！\n", user->username);
    printf("\n");
    printf("  1. 浏览新闻列表\n");
    printf("  2. 搜索新闻\n");
    printf("  3. 查看新闻详情\n");
    printf("  4. 发表评论\n");
    printf("  5. 查看我的评论\n");
    printf("  6. 个人信息\n");
    printf("  7. 修改密码\n");
    printf("  8. 退出登录\n");
    printf("  0. 返回主菜单\n");
    printFooter();
}

/**
 * 显示管理员菜单
 */
void showAdminMenu() {
    clearScreen();
    printHeader("管理员菜单");
    printf("\n");
    printf("  欢迎您，管理员！\n");
    printf("\n");
    printf("  1. 浏览新闻列表\n");
    printf("  2. 搜索新闻\n");
    printf("  3. 查看新闻详情\n");
    printf("  4. 添加新闻\n");
    printf("  5. 编辑新闻\n");
    printf("  6. 删除新闻\n");
    printf("  7. 新闻审核\n");
    printf("  8. 排序新闻\n");
    printf("  9. 统计信息\n");
    printf("  10. 查看已删除新闻\n");
    printf("  11. 分类管理\n");
    printf("  12. 按日期查询\n");
    printf("  13. 公告发布管理\n");
    printf("  14. 系统设置\n");
    printf("  15. 用户管理\n");
    printf("  16. 个人信息\n");
    printf("  17. 修改密码\n");
    printf("  18. 退出登录\n");
    printf("  0. 返回主菜单\n");
    printFooter();
}

/**
 * 显示访客菜单
 */
void showGuestMenu() {
    clearScreen();
    printHeader("访客菜单");
    printf("\n");
    printf("  欢迎您，访客！\n");
    printf("\n");
    printf("  1. 浏览新闻列表\n");
    printf("  2. 搜索新闻\n");
    printf("  3. 查看新闻详情\n");
    printf("  0. 返回主菜单\n");
    printFooter();
}

/**
 * 显示新闻列表
 * @param newsList 新闻链表头指针
 */
void showNewsList(News* newsList) {
    if (newsList == NULL) {
        printf("\n暂无新闻数据！\n");
        return;
    }
    
    clearScreen();
    printHeader("新闻列表");
    printf("\n");
    
    News* temp = newsList;
    int count = 1;
    
    while (temp != NULL) {
        printf("【新闻 %d】\n", count);
        printf("  ID: %s\n", temp->id);
        printf("  标题: %s\n", temp->title);
        printf("  分类: %s\n", temp->category);
        printf("  作者: %s\n", temp->author);
        printf("  发布日期: %s\n", temp->publishDate);
        
        int commentCount = countComments(temp->id);
        printf("  评论数: %d\n", commentCount);
        
        printSeparator();
        
        temp = temp->next;
        count++;
    }
    
    printf("\n共 %d 条新闻\n", count - 1);
}

/**
 * 分页显示新闻列表
 * @param newsList 新闻链表头指针
 */
void showNewsListPaged(News* newsList) {
    if (newsList == NULL) {
        printf("\n暂无新闻数据！\n");
        pauseScreen();
        return;
    }
    
    int totalNews = getNewsListLength(newsList);
    int currentPage = 1;
    int totalPages = (totalNews + PAGE_SIZE - 1) / PAGE_SIZE;
    int choice;
    
    do {
        clearScreen();
        printHeader("新闻列表");
        printf("\n");
        
        int startIndex = (currentPage - 1) * PAGE_SIZE;
        int endIndex = startIndex + PAGE_SIZE;
        int currentCount = 0;
        
        News* temp = newsList;
        
        while (temp != NULL && currentCount < endIndex) {
            if (currentCount >= startIndex) {
                printf("【新闻 %d】\n", currentCount + 1);
                printf("  ID: %s\n", temp->id);
                printf("  标题: %s\n", temp->title);
                printf("  分类: %s\n", temp->category);
                printf("  作者: %s\n", temp->author);
                printf("  发布日期: %s\n", temp->publishDate);
                
                int commentCount = countComments(temp->id);
                printf("  评论数: %d\n", commentCount);
                
                printSeparator();
            }
            
            temp = temp->next;
            currentCount++;
        }
        
        printf("\n第 %d 页 / 共 %d 页\n", currentPage, totalPages);
        printf("共 %d 条新闻\n", totalNews);
        printf("\n");
        printf("操作选项:\n");
        printf("  1. 上一页\n");
        printf("  2. 下一页\n");
        printf("  3. 跳转到指定页\n");
        printf("  4. 查看新闻详情\n");
        printf("  0. 返回\n");
        
        choice = getIntInput("\n请选择操作: ", 0, 4);
        
        switch (choice) {
            case 1:
                if (currentPage > 1) {
                    currentPage--;
                } else {
                    printf("已经是第一页了！\n");
                    pauseScreen();
                }
                break;
            case 2:
                if (currentPage < totalPages) {
                    currentPage++;
                } else {
                    printf("已经是最后一页了！\n");
                    pauseScreen();
                }
                break;
            case 3:
                {
                    int page = getIntInput("请输入页码: ", 1, totalPages);
                    currentPage = page;
                }
                break;
            case 4:
                {
                    int minNewsNum = startIndex + 1;
                    int maxNewsNum = (endIndex > totalNews) ? totalNews : endIndex;
                    int newsNum = getIntInput("请输入新闻编号: ", minNewsNum, maxNewsNum);
                    News* selectedNews = newsList;
                    int count = 1;
                    while (selectedNews != NULL && count < newsNum) {
                        selectedNews = selectedNews->next;
                        count++;
                    }
                    if (selectedNews != NULL) {
                        showNewsDetail(selectedNews);
                    } else {
                        printf("\n新闻不存在！\n");
                        pauseScreen();
                    }
                }
                break;
            case 0:
                break;
        }
        
    } while (choice != 0);
}

void showNewsDetail(News* news) {
    if (news == NULL) {
        printf("\n新闻不存在！\n");
        pauseScreen();
        return;
    }
    
    clearScreen();
    printHeader("新闻详情");
    printf("\n");
    
    printf("  ID: %s\n", news->id);
    printf("  标题: %s\n", news->title);
    printf("  分类: %s\n", news->category);
    printf("  作者: %s\n", news->author);
    printf("  发布日期: %s\n", news->publishDate);
    
    printf("  [DEBUG] imagePath: '%s', length: %zu\n", news->imagePath, strlen(news->imagePath));
    
    if (strlen(news->imagePath) > 0) {
        printf("  图片: %s\n", news->imagePath);
    }
    
    printf("\n  内容:\n");
    printf("  %s\n", news->content);
    
    printSeparator();
    
    Comment* comments = getCommentsByNewsId(news->id);
    if (comments != NULL) {
        printf("\n  评论列表:\n");
        displayComments(comments);
        freeCommentList(comments);
    } else {
        printf("\n  暂无评论\n");
    }
    
    printFooter();
    
    if (strlen(news->imagePath) > 0) {
        printf("\n是否查看新闻图片？\n");
        printf("  1. 是\n");
        printf("  2. 否\n");
        
        int choice = getIntInput("\n请选择: ", 1, 2);
        if (choice == 1) {
            showNewsImage(news->imagePath);
        }
    }
    
    pauseScreen();
}

void showNewsImage(char* imagePath) {
    if (imagePath == NULL || strlen(imagePath) == 0) {
        printf("\n图片路径为空！\n");
        pauseScreen();
        return;
    }
    
    printf("\n正在打开图片: %s\n", imagePath);
    
    char command[512];
    snprintf(command, sizeof(command), "start \"\" \"%s\"", imagePath);
    
    int result = system(command);
    
    if (result == 0) {
        printf("图片已使用系统默认程序打开。\n");
    } else {
        printf("打开图片失败！请检查图片路径是否正确。\n");
    }
    
    pauseScreen();
}

/**
 * 显示分类管理界面
 * 
 * 提供分类管理功能，管理员可以查看所有分类、添加分类、删除分类。
 */
void showCategoryManagement() {
    int choice;
    
    do {
        clearScreen();
        printHeader("分类管理");
        printf("\n");
        printf("  1. 查看所有分类\n");
        printf("  2. 添加分类\n");
        printf("  3. 删除分类\n");
        printf("  4. 按分类查询新闻（包括已删除）\n");
        printf("  0. 返回\n");
        
        choice = getIntInput("\n请选择操作: ", 0, 4);
        
        switch (choice) {
            case 1: {
                // 查看所有分类
                clearScreen();
                printHeader("所有分类");
                printf("\n");
                
                int count;
                char** categories = getCategories(&count);
                
                if (categories == NULL || count == 0) {
                    printf("暂无分类！\n");
                } else {
                    for (int i = 0; i < count; i++) {
                        printf("  %d. %s\n", i + 1, categories[i]);
                    }
                    printf("\n共 %d 个分类\n", count);
                    freeCategories(categories, count);
                }
                
                pauseScreen();
                break;
            }
            case 2: {
                // 添加分类
                clearScreen();
                printHeader("添加分类");
                printf("\n");
                
                char category[50];
                getStringInput("请输入分类名称: ", category, sizeof(category));
                
                int result = addCategory(category);
                if (result) {
                    printf("\n分类添加成功！\n");
                } else {
                    printf("\n分类添加失败！\n");
                }
                
                pauseScreen();
                break;
            }
            case 3: {
                // 删除分类
                clearScreen();
                printHeader("删除分类");
                printf("\n");
                
                int count;
                char** categories = getCategories(&count);
                
                if (categories == NULL || count == 0) {
                    printf("暂无分类！\n");
                    pauseScreen();
                    break;
                }
                
                printf("现有分类：\n");
                for (int i = 0; i < count; i++) {
                    printf("  %d. %s\n", i + 1, categories[i]);
                }
                
                char category[50];
                getStringInput("\n请输入要删除的分类名称: ", category, sizeof(category));
                
                printf("\n确认删除分类 %s 吗？\n", category);
                printf("  1. 确认\n");
                printf("  2. 取消\n");
                
                int confirm = getIntInput("\n请选择: ", 1, 2);
                
                if (confirm == 1) {
                    int result = deleteCategory(category);
                    if (result) {
                        printf("\n分类删除成功！\n");
                    } else {
                        printf("\n分类删除失败！\n");
                    }
                } else {
                    printf("\n已取消删除。\n");
                }
                
                freeCategories(categories, count);
                pauseScreen();
                break;
            }
            case 4: {
                // 按分类查询新闻（包括已删除）
                clearScreen();
                printHeader("按分类查询新闻");
                printf("\n");
                
                int count;
                char** categories = getCategories(&count);
                
                if (categories == NULL || count == 0) {
                    printf("暂无分类！\n");
                    pauseScreen();
                    break;
                }
                
                printf("现有分类：\n");
                for (int i = 0; i < count; i++) {
                    printf("  %d. %s\n", i + 1, categories[i]);
                }
                
                char category[50];
                getStringInput("\n请输入分类名称: ", category, sizeof(category));
                
                printf("\n是否包含已删除新闻？\n");
                printf("  1. 是\n");
                printf("  2. 否\n");
                
                int includeDeleted = (getIntInput("\n请选择: ", 1, 2) == 1) ? 1 : 0;
                
                News* newsList = searchNewsByCategory(category, includeDeleted);
                
                if (newsList == NULL) {
                    printf("\n未找到该分类的新闻！\n");
                } else {
                    printf("\n查询结果：\n\n");
                    showNewsListPaged(newsList);
                    freeNewsList(newsList);
                }
                
                freeCategories(categories, count);
                pauseScreen();
                break;
            }
            case 0:
                break;
        }
    } while (choice != 0);
}

/**
 * 显示按日期查询界面
 * 
 * 提供按年、月、日查询新闻功能，管理员可以查询指定日期的新闻。
 */
void showDateSearch() {
    clearScreen();
    printHeader("按日期查询新闻");
    printf("\n");
    
    printf("请选择查询方式：\n");
    printf("  1. 按年查询\n");
    printf("  2. 按年月查询\n");
    printf("  3. 按年月日查询\n");
    
    int searchType = getIntInput("\n请选择: ", 1, 3);
    
    int year = 0, month = 0, day = 0;
    
    switch (searchType) {
        case 1:
            year = getIntInput("请输入年份: ", 2000, 2100);
            break;
        case 2:
            year = getIntInput("请输入年份: ", 2000, 2100);
            month = getIntInput("请输入月份: ", 1, 12);
            break;
        case 3:
            year = getIntInput("请输入年份: ", 2000, 2100);
            month = getIntInput("请输入月份: ", 1, 12);
            day = getIntInput("请输入日期: ", 1, 31);
            break;
    }
    
    printf("\n是否包含已删除新闻？\n");
    printf("  1. 是\n");
    printf("  2. 否\n");
    
    int includeDeleted = (getIntInput("\n请选择: ", 1, 2) == 1) ? 1 : 0;
    
    News* newsList = searchNewsByDate(year, month, day, includeDeleted);
    
    if (newsList == NULL) {
        printf("\n未找到符合条件的新闻！\n");
    } else {
        printf("\n查询结果：\n\n");
        showNewsListPaged(newsList);
        freeNewsList(newsList);
    }
    
    pauseScreen();
}

/**
 * 显示公告发布管理界面
 * 
 * 提供公告发布管理功能，管理员可以发布公告、查看公告、编辑公告、删除公告。
 */
void showAnnouncementManagement() {
    int choice;
    
    do {
        clearScreen();
        printHeader("公告发布管理");
        printf("\n");
        printf("  1. 发布公告\n");
        printf("  2. 查看公告列表\n");
        printf("  3. 编辑公告\n");
        printf("  4. 删除公告\n");
        printf("  0. 返回\n");
        
        choice = getIntInput("\n请选择操作: ", 0, 4);
        
        switch (choice) {
            case 1: {
                // 发布公告
                clearScreen();
                printHeader("发布公告");
                printf("\n");
                
                char title[100];
                char content[1000];
                char imagePath[200];
                
                printf("请输入公告信息:\n");
                getStringInput("标题: ", title, sizeof(title));
                getStringInput("内容: ", content, sizeof(content));
                getStringInput("图片路径（可选）: ", imagePath, sizeof(imagePath));
                
                News* newNews = addNews(title, content, "系统管理员", "公告", imagePath);
                
                if (newNews != NULL) {
                    printf("\n公告发布成功！\n");
                    printf("公告ID: %s\n", newNews->id);
                } else {
                    printf("\n公告发布失败！\n");
                }
                
                pauseScreen();
                break;
            }
            case 2: {
                // 查看公告列表
                clearScreen();
                printHeader("公告列表");
                printf("\n");
                
                News* announcements = searchNewsByCategory("公告", 0);
                
                if (announcements == NULL) {
                    printf("暂无公告！\n");
                } else {
                    showNewsListPaged(announcements);
                    freeNewsList(announcements);
                }
                
                pauseScreen();
                break;
            }
            case 3: {
                // 编辑公告
                clearScreen();
                printHeader("编辑公告");
                printf("\n");
                
                char id[20];
                getStringInput("请输入要编辑的公告ID: ", id, sizeof(id));
                
                News* news = findNewsById(id);
                if (news == NULL || strcmp(news->category, "公告") != 0) {
                    printf("\n公告不存在！\n");
                    pauseScreen();
                    break;
                }
                
                printf("\n当前公告信息:\n");
                printf("  标题: %s\n", news->title);
                printf("  内容: %s\n", news->content);
                printf("  图片路径: %s\n", news->imagePath);
                
                printf("\n请输入新的信息（留空表示不修改）:\n");
                
                char title[100];
                char content[1000];
                char imagePath[200];
                
                getStringInput("新标题: ", title, sizeof(title));
                getStringInput("新内容: ", content, sizeof(content));
                getStringInput("新图片路径: ", imagePath, sizeof(imagePath));
                
                int result = updateNews(id, title, content, "公告", imagePath);
                
                if (result) {
                    printf("\n公告更新成功！\n");
                } else {
                    printf("\n公告更新失败！\n");
                }
                
                pauseScreen();
                break;
            }
            case 4: {
                // 删除公告
                clearScreen();
                printHeader("删除公告");
                printf("\n");
                
                char id[20];
                getStringInput("请输入要删除的公告ID: ", id, sizeof(id));
                
                News* news = findNewsById(id);
                if (news == NULL || strcmp(news->category, "公告") != 0) {
                    printf("\n公告不存在！\n");
                    pauseScreen();
                    break;
                }
                
                printf("\n确认删除公告 %s 吗？\n", id);
                printf("  1. 确认\n");
                printf("  2. 取消\n");
                
                int confirm = getIntInput("\n请选择: ", 1, 2);
                
                if (confirm == 1) {
                    int result = deleteNews(id);
                    if (result) {
                        printf("\n公告删除成功！\n");
                    } else {
                        printf("\n公告删除失败！\n");
                    }
                } else {
                    printf("\n已取消删除。\n");
                }
                
                pauseScreen();
                break;
            }
            case 0:
                break;
        }
    } while (choice != 0);
}

/**
 * 显示系统设置界面
 * 
 * 提供系统基本设置功能，管理员可以配置系统参数。
 */
void showSystemSettings() {
    int choice;
    
    do {
        clearScreen();
        printHeader("系统设置");
        printf("\n");
        printf("  1. 查看系统信息\n");
        printf("  2. 系统数据备份\n");
        printf("  3. 系统数据恢复\n");
        printf("  4. 清空已删除新闻\n");
        printf("  5. 重置系统\n");
        printf("  0. 返回\n");
        
        choice = getIntInput("\n请选择操作: ", 0, 5);
        
        switch (choice) {
            case 1: {
                // 查看系统信息
                clearScreen();
                printHeader("系统信息");
                printf("\n");
                
                printf("=== 系统统计 ===\n");
                printf("  新闻总数: %d\n", countNews());
                printf("  待审核: %d\n", countNewsByStatus(0));
                printf("  已审核: %d\n", countNewsByStatus(1));
                printf("  用户总数: %d\n", countUsers());
                printf("  普通用户: %d\n", countUsersByRole(1));
                printf("  管理员: %d\n", countUsersByRole(2));
                
                int categoryCount;
                char** categories = getCategories(&categoryCount);
                printf("  分类数量: %d\n", categoryCount);
                freeCategories(categories, categoryCount);
                
                printFooter();
                pauseScreen();
                break;
            }
            case 2: {
                // 系统数据备份
                clearScreen();
                printHeader("系统数据备份");
                printf("\n");
                
                printf("正在备份数据...\n");
                
                News* newsList = getNewsList();
                if (newsList != NULL) {
                    saveNewsToFile(newsList, "news_backup.txt");
                    freeNewsList(newsList);
                    printf("新闻数据备份成功！\n");
                }
                
                User* userList = getUserList();
                if (userList != NULL) {
                    saveUsersToFile(userList, "users_backup.txt");
                    freeUserList(userList);
                    printf("用户数据备份成功！\n");
                }
                
                printf("\n数据备份完成！\n");
                pauseScreen();
                break;
            }
            case 3: {
                // 系统数据恢复
                clearScreen();
                printHeader("系统数据恢复");
                printf("\n");
                
                printf("警告：数据恢复将覆盖当前数据！\n");
                printf("  1. 确认恢复\n");
                printf("  2. 取消\n");
                
                int confirm = getIntInput("\n请选择: ", 1, 2);
                
                if (confirm == 1) {
                    printf("\n正在恢复数据...\n");
                    
                    News* backupNews = loadNewsFromFile("news_backup.txt");
                    if (backupNews != NULL) {
                        saveNewsToFile(backupNews, NEWS_FILE);
                        freeNewsList(backupNews);
                        printf("新闻数据恢复成功！\n");
                    }
                    
                    User* backupUsers = loadUsersFromFile("users_backup.txt");
                    if (backupUsers != NULL) {
                        saveUsersToFile(backupUsers, "users.txt");
                        freeUserList(backupUsers);
                        printf("用户数据恢复成功！\n");
                    }
                    
                    printf("\n数据恢复完成！\n");
                } else {
                    printf("\n已取消恢复。\n");
                }
                
                pauseScreen();
                break;
            }
            case 4: {
                // 清空已删除新闻
                clearScreen();
                printHeader("清空已删除新闻");
                printf("\n");
                
                printf("警告：此操作将永久删除所有已删除的新闻记录！\n");
                printf("  1. 确认清空\n");
                printf("  2. 取消\n");
                
                int confirm = getIntInput("\n请选择: ", 1, 2);
                
                if (confirm == 1) {
                    FILE* file = fopen(DELETED_NEWS_FILE, "w");
                    if (file != NULL) {
                        fclose(file);
                        printf("\n已删除新闻已清空！\n");
                    } else {
                        printf("\n清空失败！\n");
                    }
                } else {
                    printf("\n已取消清空。\n");
                }
                
                pauseScreen();
                break;
            }
            case 5: {
                // 重置系统
                clearScreen();
                printHeader("重置系统");
                printf("\n");
                
                printf("警告：此操作将删除所有数据并恢复到初始状态！\n");
                printf("  1. 确认重置\n");
                printf("  2. 取消\n");
                
                int confirm = getIntInput("\n请选择: ", 1, 2);
                
                if (confirm == 1) {
                    printf("\n正在重置系统...\n");
                    
                    // 删除所有数据文件
                    remove(NEWS_FILE);
                    remove(DELETED_NEWS_FILE);
                    remove("users.txt");
                    remove("comments.txt");
                    remove("categories.txt");
                    
                    // 重新初始化默认管理员
                    initializeDefaultAdmin();
                    
                    printf("\n系统重置完成！\n");
                } else {
                    printf("\n已取消重置。\n");
                }
                
                pauseScreen();
                break;
            }
            case 0:
                break;
        }
    } while (choice != 0);
}

/**
 * 显示新闻审核界面
 * 
 * 提供新闻审核功能，管理员可以查看待审核新闻并进行审核操作。
 */
void showNewsAudit() {
    clearScreen();
    printHeader("新闻审核");
    printf("\n");
    
    News* pendingNews = getPendingNews();
    
    if (pendingNews == NULL) {
        printf("暂无待审核新闻！\n");
        pauseScreen();
        return;
    }
    
    printf("待审核新闻列表：\n\n");
    
    News* temp = pendingNews;
    int count = 1;
    
    while (temp != NULL) {
        printf("【新闻 %d】\n", count);
        printf("  ID: %s\n", temp->id);
        printf("  标题: %s\n", temp->title);
        printf("  分类: %s\n", temp->category);
        printf("  作者: %s\n", temp->author);
        printf("  发布日期: %s\n", temp->publishDate);
        printf("  状态: 待审核\n");
        printSeparator();
        
        temp = temp->next;
        count++;
    }
    
    printf("\n共 %d 条待审核新闻\n", count - 1);
    
    char newsId[20];
    getStringInput("\n请输入要审核的新闻ID（留空返回）: ", newsId, sizeof(newsId));
    
    if (strlen(newsId) == 0) {
        freeNewsList(pendingNews);
        return;
    }
    
    News* news = findNewsNode(pendingNews, newsId);
    if (news == NULL) {
        printf("\n新闻不存在！\n");
        freeNewsList(pendingNews);
        pauseScreen();
        return;
    }
    
    printf("\n请选择审核结果:\n");
    printf("  1. 通过\n");
    printf("  2. 拒绝\n");
    
    int choice = getIntInput("\n请选择: ", 1, 2);
    
    int result;
    if (choice == 1) {
        result = approveNews(newsId);
        if (result) {
            printf("\n新闻审核通过！\n");
        } else {
            printf("\n新闻审核失败！\n");
        }
    } else {
        result = rejectNews(newsId);
        if (result) {
            printf("\n新闻已拒绝！\n");
        } else {
            printf("\n新闻审核失败！\n");
        }
    }
    
    freeNewsList(pendingNews);
    pauseScreen();
}

/**
 * 显示统计信息界面
 * 
 * 提供统计信息功能，显示新闻和用户的统计数据。
 */
void showStatistics() {
    clearScreen();
    printHeader("统计信息");
    printf("\n");
    
    printf("=== 新闻统计 ===\n");
    int totalNews = countNews();
    int pendingNews = countNewsByStatus(0);
    int approvedNews = countNewsByStatus(1);
    int rejectedNews = countNewsByStatus(2);
    
    printf("  新闻总数: %d\n", totalNews);
    printf("  待审核: %d\n", pendingNews);
    printf("  已审核: %d\n", approvedNews);
    printf("  已拒绝: %d\n", rejectedNews);
    
    printf("\n=== 用户统计 ===\n");
    int totalUsers = countUsers();
    int normalUsers = countUsersByRole(1);
    int adminUsers = countUsersByRole(2);
    
    printf("  用户总数: %d\n", totalUsers);
    printf("  普通用户: %d\n", normalUsers);
    printf("  管理员: %d\n", adminUsers);
    
    printFooter();
    pauseScreen();
}

/**
 * 显示已删除新闻查询界面
 * 
 * 提供查询已删除新闻功能，管理员可以查看已删除的新闻记录。
 */
void showDeletedNews() {
    clearScreen();
    printHeader("已删除新闻");
    printf("\n");
    
    News* deletedNews = getDeletedNews();
    
    if (deletedNews == NULL) {
        printf("暂无已删除新闻！\n");
        pauseScreen();
        return;
    }
    
    printf("已删除新闻列表：\n\n");
    
    News* temp = deletedNews;
    int count = 1;
    
    while (temp != NULL) {
        printf("【新闻 %d】\n", count);
        printf("  ID: %s\n", temp->id);
        printf("  标题: %s\n", temp->title);
        printf("  分类: %s\n", temp->category);
        printf("  作者: %s\n", temp->author);
        printf("  发布日期: %s\n", temp->publishDate);
        printSeparator();
        
        temp = temp->next;
        count++;
    }
    
    printf("\n共 %d 条已删除新闻\n", count - 1);
    
    char newsId[20];
    getStringInput("\n请输入要恢复的新闻ID（留空返回）: ", newsId, sizeof(newsId));
    
    if (strlen(newsId) == 0) {
        freeNewsList(deletedNews);
        return;
    }
    
    printf("\n确认恢复新闻 %s 吗？\n", newsId);
    printf("  1. 确认\n");
    printf("  2. 取消\n");
    
    int choice = getIntInput("\n请选择: ", 1, 2);
    
    if (choice == 1) {
        int result = restoreNews(newsId);
        
        if (result) {
            printf("\n新闻恢复成功！\n");
        } else {
            printf("\n新闻恢复失败！\n");
        }
    } else {
        printf("\n已取消恢复。\n");
    }
    
    freeNewsList(deletedNews);
    pauseScreen();
}

void showNewsSearch() {
    clearScreen();
    printHeader("搜索新闻");
    printf("\n");
    
    char keyword[100] = "";
    char category[20] = "";
    char startDate[20] = "";
    char endDate[20] = "";
    
    printf("请输入搜索条件（留空表示不限制该条件）:\n");
    
    getStringInput("关键词: ", keyword, sizeof(keyword));
    getStringInput("分类: ", category, sizeof(category));
    getStringInput("开始日期 (YYYY-MM-DD): ", startDate, sizeof(startDate));
    getStringInput("结束日期 (YYYY-MM-DD): ", endDate, sizeof(endDate));
    
    News* result = searchNews(keyword, category, startDate, endDate);
    
    if (result == NULL) {
        printf("\n未找到符合条件的新闻！\n");
    } else {
        showNewsListPaged(result);
        freeNewsList(result);
    }
    
    pauseScreen();
}

void showNewsSort() {
    clearScreen();
    printHeader("排序新闻");
    printf("\n");
    
    printf("请选择排序方式:\n");
    printf("  1. 按日期排序\n");
    printf("  2. 按作者排序\n");
    printf("  3. 按标题排序\n");
    
    int sortChoice = getIntInput("\n请选择: ", 1, 3);
    
    printf("\n请选择排序顺序:\n");
    printf("  1. 降序（从新到旧）\n");
    printf("  2. 升序（从旧到新）\n");
    
    int orderChoice = getIntInput("\n请选择: ", 1, 2);
    
    char sortBy[20];
    int order;
    
    switch (sortChoice) {
        case 1:
            strcpy(sortBy, "date");
            break;
        case 2:
            strcpy(sortBy, "author");
            break;
        case 3:
            strcpy(sortBy, "title");
            break;
    }
    
    order = (orderChoice == 1) ? 0 : 1;
    
    News* newsList = getNewsList();
    if (newsList == NULL) {
        printf("\n暂无新闻数据！\n");
        pauseScreen();
        return;
    }
    
    News* sortedList = sortNews(newsList, sortBy, order);
    if (sortedList != NULL) {
        showNewsListPaged(sortedList);
        freeNewsList(sortedList);
    }
    
    freeNewsList(newsList);
}

void showAddNews(User* user) {
    clearScreen();
    printHeader("添加新闻");
    printf("\n");
    
    char title[100];
    char content[1000];
    char category[20];
    char imagePath[200];
    
    printf("请输入新闻信息:\n");
    getStringInput("标题: ", title, sizeof(title));
    getStringInput("内容: ", content, sizeof(content));
    getStringInput("分类: ", category, sizeof(category));
    getStringInput("图片路径: ", imagePath, sizeof(imagePath));
    
    News* newNews = addNews(title, content, user->username, category, imagePath);
    
    if (newNews != NULL) {
        printf("\n新闻添加成功！\n");
        printf("新闻ID: %s\n", newNews->id);
    } else {
        printf("\n新闻添加失败！\n");
    }
    
    pauseScreen();
}

void showEditNews(User* user) {
    clearScreen();
    printHeader("编辑新闻");
    printf("\n");
    
    char id[20];
    getStringInput("请输入要编辑的新闻ID: ", id, sizeof(id));
    
    News* news = findNewsById(id);
    if (news == NULL) {
        printf("\n新闻不存在！\n");
        pauseScreen();
        return;
    }
    
    printf("\n当前新闻信息:\n");
    printf("  标题: %s\n", news->title);
    printf("  内容: %s\n", news->content);
    printf("  分类: %s\n", news->category);
    printf("  图片路径: %s\n", news->imagePath);
    
    printf("\n请输入新的信息（留空表示不修改）:\n");
    
    char title[100];
    char content[1000];
    char category[20];
    char imagePath[200];
    
    getStringInput("新标题: ", title, sizeof(title));
    getStringInput("新内容: ", content, sizeof(content));
    getStringInput("新分类: ", category, sizeof(category));
    getStringInput("新图片路径: ", imagePath, sizeof(imagePath));
    
    int result = updateNews(id, title, content, category, imagePath);
    
    if (result) {
        printf("\n新闻更新成功！\n");
    } else {
        printf("\n新闻更新失败！\n");
    }
    
    pauseScreen();
}

/**
 * 显示删除新闻界面
 * 
 * 提供删除新闻的用户界面，管理员可以输入新闻ID来删除指定的新闻。
 * 删除前会进行二次确认，防止误操作。
 * 
 * @param user 当前登录的用户指针（必须是管理员）
 */
void showDeleteNews(User* user) {
    clearScreen();
    printHeader("删除新闻");
    printf("\n");
    
    char id[20];
    getStringInput("请输入要删除的新闻ID: ", id, sizeof(id));
    
    printf("\n确认删除新闻 %s 吗？\n", id);
    printf("  1. 确认\n");
    printf("  2. 取消\n");
    
    int choice = getIntInput("\n请选择: ", 1, 2);
    
    if (choice == 1) {
        int result = deleteNews(id);
        
        if (result) {
            printf("\n新闻删除成功！\n");
        } else {
            printf("\n新闻删除失败！\n");
        }
    } else {
        printf("\n已取消删除。\n");
    }
    
    pauseScreen();
}

/**
 * 显示发表评论界面
 * 
 * 提供发表评论的用户界面，用户可以输入新闻ID和评论内容来发表评论。
 * 会先验证新闻是否存在，然后创建新的评论记录。
 * 
 * @param user 当前登录的用户指针
 */
void showAddComment(User* user) {
    clearScreen();
    printHeader("发表评论");
    printf("\n");
    
    char newsId[20];
    getStringInput("请输入新闻ID: ", newsId, sizeof(newsId));
    
    News* news = findNewsById(newsId);
    if (news == NULL) {
        printf("\n新闻不存在！\n");
        pauseScreen();
        return;
    }
    
    printf("\n新闻标题: %s\n", news->title);
    
    char content[500];
    getStringInput("请输入评论内容: ", content, sizeof(content));
    
    Comment* newComment = addComment(newsId, user->username, content);
    
    if (newComment != NULL) {
        printf("\n评论发表成功！\n");
    } else {
        printf("\n评论发表失败！\n");
    }
    
    pauseScreen();
}

/**
 * 显示用户管理界面
 * 
 * 提供用户管理的用户界面，管理员可以查看所有用户、添加新用户、
 * 编辑用户信息和删除用户。该界面会循环显示，直到用户选择返回。
 * 
 * @param user 当前登录的用户指针（必须是管理员）
 */
void showUserManagement(User* user) {
    int choice;
    
    do {
        clearScreen();
        printHeader("用户管理");
        printf("\n");
        printf("  1. 查看所有用户\n");
        printf("  2. 添加用户\n");
        printf("  3. 编辑用户\n");
        printf("  4. 删除用户\n");
        printf("  0. 返回\n");
        
        choice = getIntInput("\n请选择操作: ", 0, 4);
        
        switch (choice) {
            case 1:
                showAllUsers(user);
                break;
            case 2:
                showAddUser(user);
                break;
            case 3:
                showEditUser(user);
                break;
            case 4:
                showDeleteUser(user);
                break;
            case 0:
                break;
        }
        
    } while (choice != 0);
}

/**
 * 显示用户注册界面
 * 
 * 提供用户注册的用户界面，新用户可以输入用户名和密码进行注册。
 * 注册成功后默认为普通用户角色。
 */
void showUserRegister() {
    clearScreen();
    printHeader("用户注册");
    printf("\n");
    
    char username[50];
    char password[50];
    
    printf("请输入注册信息:\n");
    getStringInput("用户名: ", username, sizeof(username));
    getStringInput("密码: ", password, sizeof(password));
    
    User* newUser = registerUser(username, password, 1);
    
    if (newUser != NULL) {
        printf("\n注册成功！\n");
    } else {
        printf("\n注册失败！\n");
    }
    
    pauseScreen();
}

/**
 * 显示用户登录界面
 * 
 * 提供用户登录的用户界面，用户可以输入用户名和密码进行登录。
 * 登录成功后根据用户角色显示相应的欢迎信息，并设置全局当前用户。
 */
void showUserLogin() {
    clearScreen();
    printHeader("用户登录");
    printf("\n");
    
    char username[50];
    char password[50];
    
    printf("请输入登录信息:\n");
    getStringInput("用户名: ", username, sizeof(username));
    getStringInput("密码: ", password, sizeof(password));
    
    User* user = loginUser(username, password);
    
    if (user != NULL) {
        printf("\n登录成功！\n");
        
        if (user->role == 2) {
            printf("欢迎管理员 %s！\n", user->username);
        } else {
            printf("欢迎用户 %s！\n", user->username);
        }
        
        currentUser = user;
        pauseScreen();
    } else {
        printf("\n登录失败！用户名或密码错误。\n");
        pauseScreen();
    }
}

/**
 * 显示用户个人信息界面
 * 
 * 显示当前登录用户的个人信息，包括用户名和角色。
 * 
 * @param user 当前登录的用户指针
 */
void showUserInfo(User* user) {
    clearScreen();
    printHeader("个人信息");
    printf("\n");
    
    printf("  用户名: %s\n", user->username);
    printf("  角色: %s\n", user->role == 2 ? "管理员" : "普通用户");
    
    printFooter();
    pauseScreen();
}

/**
 * 显示编辑个人信息界面
 * 
 * 提供编辑个人信息的用户界面。目前仅显示当前用户名，
 * 暂不支持修改用户名功能。
 * 
 * @param user 当前登录的用户指针
 */
void showEditUserInfo(User* user) {
    clearScreen();
    printHeader("编辑个人信息");
    printf("\n");
    
    printf("当前用户名: %s\n", user->username);
    printf("\n注意：用户名暂不支持修改。\n");
    
    pauseScreen();
}

/**
 * 显示修改密码界面
 * 
 * 提供修改密码的用户界面，用户需要输入原密码进行验证，
 * 然后输入新密码并确认。只有原密码正确且两次新密码一致时才能修改成功。
 * 
 * @param user 当前登录的用户指针
 */
void showChangePassword(User* user) {
    clearScreen();
    printHeader("修改密码");
    printf("\n");
    
    char oldPassword[50];
    char newPassword[50];
    char confirmPassword[50];
    
    getStringInput("请输入原密码: ", oldPassword, sizeof(oldPassword));
    
    if (strcmp(user->password, oldPassword) != 0) {
        printf("\n原密码错误！\n");
        pauseScreen();
        return;
    }
    
    getStringInput("请输入新密码: ", newPassword, sizeof(newPassword));
    getStringInput("请确认新密码: ", confirmPassword, sizeof(confirmPassword));
    
    if (strcmp(newPassword, confirmPassword) != 0) {
        printf("\n两次输入的密码不一致！\n");
        pauseScreen();
        return;
    }
    
    strcpy(user->password, newPassword);
    
    if (updateUser(user)) {
        printf("\n密码修改成功！\n");
    } else {
        printf("\n密码修改失败！\n");
    }
    
    pauseScreen();
}

/**
 * 显示所有用户列表界面
 * 
 * 显示系统中所有用户的列表，包括用户名和角色信息。
 * 只有管理员可以访问此功能。
 * 
 * @param admin 当前登录的管理员指针
 */
void showAllUsers(User* admin) {
    clearScreen();
    printHeader("用户列表");
    printf("\n");
    
    User* userList = getUserList();
    
    if (userList == NULL) {
        printf("暂无用户数据！\n");
        pauseScreen();
        return;
    }
    
    User* temp = userList;
    int count = 1;
    
    while (temp != NULL) {
        printf("【用户 %d】\n", count);
        printf("  用户名: %s\n", temp->username);
        printf("  角色: %s\n", temp->role == 2 ? "管理员" : "普通用户");
        printSeparator();
        
        temp = temp->next;
        count++;
    }
    
    printf("\n共 %d 个用户\n", count - 1);
    
    freeUserList(userList);
    pauseScreen();
}

/**
 * 显示添加用户界面
 * 
 * 提供添加新用户的用户界面，管理员可以输入用户名、密码并选择角色
 * 来创建新用户。角色可以是普通用户或管理员。
 * 
 * @param admin 当前登录的管理员指针
 */
void showAddUser(User* admin) {
    clearScreen();
    printHeader("添加用户");
    printf("\n");
    
    char username[50];
    char password[50];
    
    printf("请输入用户信息:\n");
    getStringInput("用户名: ", username, sizeof(username));
    getStringInput("密码: ", password, sizeof(password));
    
    printf("\n请选择用户角色:\n");
    printf("  1. 普通用户\n");
    printf("  2. 管理员\n");
    
    int roleChoice = getIntInput("\n请选择: ", 1, 2);
    int role = (roleChoice == 1) ? 1 : 2;
    
    User* newUser = registerUser(username, password, role);
    
    if (newUser != NULL) {
        printf("\n用户添加成功！\n");
    } else {
        printf("\n用户添加失败！\n");
    }
    
    pauseScreen();
}

/**
 * 显示编辑用户界面
 * 
 * 提供编辑用户信息的用户界面，管理员可以修改指定用户的角色。
 * 目前仅支持修改用户角色，不支持修改用户名和密码。
 * 
 * @param admin 当前登录的管理员指针
 */
void showEditUser(User* admin) {
    clearScreen();
    printHeader("编辑用户");
    printf("\n");
    
    char username[50];
    getStringInput("请输入要编辑的用户名: ", username, sizeof(username));
    
    User* userList = getUserList();
    User* targetUser = findUserNode(userList, username);
    
    if (targetUser == NULL) {
        printf("\n用户不存在！\n");
        freeUserList(userList);
        pauseScreen();
        return;
    }
    
    printf("\n当前用户信息:\n");
    printf("  用户名: %s\n", targetUser->username);
    printf("  角色: %s\n", targetUser->role == 2 ? "管理员" : "普通用户");
    
    printf("\n请选择新的角色:\n");
    printf("  1. 普通用户\n");
    printf("  2. 管理员\n");
    
    int roleChoice = getIntInput("\n请选择: ", 1, 2);
    targetUser->role = (roleChoice == 1) ? 1 : 2;
    
    if (updateUser(targetUser)) {
        printf("\n用户信息更新成功！\n");
    } else {
        printf("\n用户信息更新失败！\n");
    }
    
    freeUserList(userList);
    pauseScreen();
}

/**
 * 显示删除用户界面
 * 
 * 提供删除用户的用户界面，管理员可以输入用户名来删除指定用户。
 * 删除前会进行二次确认，防止误操作。不允许删除当前登录的管理员账号。
 * 
 * @param admin 当前登录的管理员指针
 */
void showDeleteUser(User* admin) {
    clearScreen();
    printHeader("删除用户");
    printf("\n");
    
    char username[50];
    getStringInput("请输入要删除的用户名: ", username, sizeof(username));
    
    if (strcmp(username, admin->username) == 0) {
        printf("\n不能删除当前登录的管理员账号！\n");
        pauseScreen();
        return;
    }
    
    printf("\n确认删除用户 %s 吗？\n", username);
    printf("  1. 确认\n");
    printf("  2. 取消\n");
    
    int choice = getIntInput("\n请选择: ", 1, 2);
    
    if (choice == 1) {
        int result = deleteUser(username);
        
        if (result) {
            printf("\n用户删除成功！\n");
        } else {
            printf("\n用户删除失败！\n");
        }
    } else {
        printf("\n已取消删除。\n");
    }
    
    pauseScreen();
}
