#ifndef UI_H
#define UI_H

#include "structs.h"

//每页显示的新闻数量
#define PAGE_SIZE 5

 
//清除控制台屏幕内容，用于界面切换时的清屏操作。
void clearScreen();

//显示系统主菜单，包括用户登录、用户注册和访客浏览新闻等选项。
void showMainMenu();

// 显示普通用户的操作菜单，包括浏览新闻、搜索新闻、查看详情、
// 发表评论、查看我的评论、个人信息、修改密码和退出登录等功能。
void showUserMenu(User* user);


//显示管理员的操作菜单，包括浏览新闻、搜索新闻、查看详情、
// 发布新闻、编辑新闻、删除新闻、用户管理、个人信息、修改密码和退出登录等功能。
void showAdminMenu();


//显示访客的操作菜单，访客只能浏览新闻、搜索新闻和查看新闻详情。
void showGuestMenu();

// 显示所有新闻的基本信息列表，包括ID、标题、分类、作者、发布日期和评论数。
void showNewsList(News* newsList);

//以分页方式显示新闻列表，支持翻页、跳转页面和查看新闻详情等操作。
void showNewsListPaged(News* newsList);

//显示指定新闻的完整信息，包括ID、标题、分类、作者、发布日期、图片路径、内容以及该新闻的所有评论。
void showNewsDetail(News* news);

//显示新闻图片
//使用系统默认程序打开并显示新闻的图片。
void showNewsImage(char* imagePath);

//显示新闻搜索界面
//提供新闻搜索功能，支持按关键词、分类、日期范围等多条件搜索。
void showNewsSearch();

//显示新闻排序界面
//提供新闻排序功能，支持按日期、作者、标题等字段进行升序或降序排序。
void showNewsSort();

//显示添加新闻界面
//提供新闻发布功能，管理员可以输入新闻标题、内容、分类和图片路径来发布新新闻。
void showAddNews(User* user);

//显示编辑新闻界面
//提供新闻编辑功能，管理员可以修改新闻的标题、内容、分类和图片路径。
void showEditNews(User* user);

//显示删除新闻界面
//提供新闻删除功能，管理员可以删除指定的新闻。
void showDeleteNews(User* user);

//显示添加评论界面
//提供评论发表功能，用户可以为指定的新闻添加评论。
void showAddComment(User* user);

//显示用户管理界面
//提供用户管理功能，管理员可以查看所有用户、添加用户、编辑用户和删除用户。
void showUserManagement(User* user);

//显示用户注册界面
//提供用户注册功能，新用户可以输入用户名和密码进行注册。
void showUserRegister();

//显示用户登录界面
//提供用户登录功能，用户可以输入用户名和密码进行登录。
void showUserLogin();

//显示用户个人信息界面
//显示当前登录用户的基本信息，包括用户名和角色。
void showUserInfo(User* user);

//显示编辑用户信息界面
//提供用户信息编辑功能（当前仅支持角色修改）。
void showEditUserInfo(User* user);

//显示修改密码界面
//提供密码修改功能，用户可以输入原密码和新密码来修改自己的密码。
void showChangePassword(User* user);

//显示所有用户列表
//显示系统中所有用户的基本信息，包括用户名和角色。
void showAllUsers(User* admin);

//示添加用户界面
//提供用户添加功能，管理员可以创建新用户并设置其角色。
void showAddUser(User* admin);

//显示编辑用户界面
//提供用户编辑功能，管理员可以修改用户的角色。
void showEditUser(User* admin);

//显示删除用户界面
//提供用户删除功能，管理员可以删除指定的用户。
void showDeleteUser(User* admin);

//显示新闻审核界面
//提供新闻审核功能，管理员可以查看待审核新闻并进行审核操作。
void showNewsAudit();

//显示统计信息界面
//提供统计信息功能，显示新闻和用户的统计数据。
void showStatistics();

//显示已删除新闻查询界面
//提供查询已删除新闻功能，管理员可以查看已删除的新闻记录。
void showDeletedNews();

//显示分类管理界面
//提供分类管理功能，管理员可以查看所有分类、添加分类、删除分类。
void showCategoryManagement();

//显示按日期查询界面
//提供按年、月、日查询新闻功能，管理员可以查询指定日期的新闻。
void showDateSearch();

//显示公告发布管理界面
//提供公告发布管理功能，管理员可以发布公告、查看公告、编辑公告、删除公告。
void showAnnouncementManagement();

//显示系统设置界面
//提供系统基本设置功能，管理员可以配置系统参数。
void showSystemSettings();

//暂停屏幕并等待用户按键
//暂停程序执行，等待用户按下任意键后继续。
void pauseScreen();

//打印标题头
//打印格式化的标题头，用于美化界面显示。
void printHeader(char* title);

//打印页脚
//打印格式化的页脚，用于美化界面显示。
void printFooter();

//打印分隔线
//打印分隔线，用于区分不同的内容区域。
void printSeparator();

//获取整数输入
//提示用户输入一个整数，并验证输入是否在指定范围内。
//如果输入无效，会持续提示用户重新输入。
int getIntInput(char* prompt, int min, int max);

//获取字符串输入
//提示用户输入一个字符串，并自动去除末尾的换行符。
void getStringInput(char* prompt, char* buffer, int maxLength);

#endif /* UI_H */
