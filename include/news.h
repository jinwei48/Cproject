#ifndef NEWS_H
#define NEWS_H

#include "structs.h"

// 新闻数据文件名
#define NEWS_FILE "news.txt"
#define DELETED_NEWS_FILE "news_del.txt"

// 新闻添加函数
News* addNews(char* title, char* content, char* author, char* category, char* imagePath);

// 新闻修改函数
int updateNews(char* id, char* title, char* content, char* category, char* imagePath);

// 新闻删除函数
int deleteNews(char* id);

// 新闻审核函数
int approveNews(char* id);
int rejectNews(char* id);
News* getPendingNews();

// 新闻查询函数（支持多种条件查询）
News* searchNews(char* keyword, char* category, char* startDate, char* endDate);

// 新闻排序函数
News* sortNews(News* newsList, char* sortBy, int order);

// 获取新闻列表函数
News* getNewsList();

// 根据ID查找新闻函数
News* findNewsById(char* id);

// 获取已删除新闻列表函数
News* getDeletedNews();

// 恢复已删除新闻函数
int restoreNews(char* id);

// 统计函数
// 统计新闻总数
int countNews();

// 统计指定状态的新闻数量
int countNewsByStatus(int status);

// 统计指定分类的新闻数量
int countNewsByCategory(char* category);

// ===================== 分类管理函数 =====================

// 添加分类
int addCategory(char* category);

// 删除分类
int deleteCategory(char* category);

// 获取所有分类
char** getCategories(int* count);

// 按分类查询新闻（包括已删除新闻）
News* searchNewsByCategory(char* category, int includeDeleted);

// 按日期查询新闻（年、月、日）
News* searchNewsByDate(int year, int month, int day, int includeDeleted);

// 查询所有新闻记录（包括已删除）
News* getAllNews(int includeDeleted);

#endif /* NEWS_H */
