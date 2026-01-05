#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/news.h"
#include "../include/list.h"
#include "../include/file.h"
#include "../include/utils.h"

// 新闻添加函数
News* addNews(char* title, char* content, char* author, char* category, char* imagePath) {
    // 生成唯一ID
    char* id = generateId();
    if (id == NULL) {
        printf("生成新闻ID失败!\n");
        return NULL;
    }
    
    // 获取当前日期
    char publishDate[20];
    getCurrentDate(publishDate);
    
    // 创建新闻节点
    News* newNews = createNewsNode(id, title, content, author, category, publishDate, imagePath, 0); // 默认状态为未审核
    if (newNews == NULL) {
        free(id);
        return NULL;
    }
    
    // 加载现有新闻列表
    News* newsList = loadNewsFromFile(NEWS_FILE);
    
    // 添加到新闻列表
    insertNewsNode(&newsList, newNews);
    
    // 保存到文件
    if (!saveNewsToFile(newsList, NEWS_FILE)) {
        printf("保存新闻数据失败！\n");
        freeNewsList(newsList);
        free(id);
        return NULL;
    }
    
    // 释放新闻列表（保留新新闻指针）
    News* temp = newsList;
    while (temp != NULL && temp != newNews) {
        News* next = temp->next;
        if (temp != newNews) {
            free(temp);
        }
        temp = next;
    }
    
    free(id);
    return newNews;
}

// 新闻修改函数
int updateNews(char* id, char* title, char* content, char* category, char* imagePath) {
    if (id == NULL || strlen(id) == 0) {
        return 0;
    }
    
    // 加载现有新闻列表
    News* newsList = loadNewsFromFile(NEWS_FILE);
    
    // 查找要修改的新闻
    News* targetNews = findNewsNode(newsList, id);
    if (targetNews == NULL) {
        printf("新闻不存在！\n");
        freeNewsList(newsList);
        return 0;
    }
    
    // 更新新闻信息
    if (title != NULL && strlen(title) > 0) {
        strcpy(targetNews->title, title);
    }
    
    if (content != NULL && strlen(content) > 0) {
        strcpy(targetNews->content, content);
    }
    
    if (category != NULL && strlen(category) > 0) {
        strcpy(targetNews->category, category);
    }
    
    if (imagePath != NULL && strlen(imagePath) > 0) {
        strcpy(targetNews->imagePath, imagePath);
    }
    
    // 保存到文件
    if (!saveNewsToFile(newsList, NEWS_FILE)) {
        printf("保存新闻数据失败！\n");
        freeNewsList(newsList);
        return 0;
    }
    
    freeNewsList(newsList);
    return 1;
}

// 新闻删除函数
int deleteNews(char* id) {
    if (id == NULL || strlen(id) == 0) {
        return 0;
    }
    
    // 加载现有新闻列表
    News* newsList = loadNewsFromFile(NEWS_FILE);
    
    // 查找要删除的新闻
    News* targetNews = findNewsNode(newsList, id);
    if (targetNews == NULL) {
        printf("新闻不存在！\n");
        freeNewsList(newsList);
        return 0;
    }
    
    // 创建新闻副本
    News* deletedNews = createNewsNode(
        targetNews->id,
        targetNews->title,
        targetNews->content,
        targetNews->author,
        targetNews->category,
        targetNews->publishDate,
        targetNews->imagePath,
        2 // 设置状态为已删除
    );
    
    if (deletedNews == NULL) {
        freeNewsList(newsList);
        return 0;
    }
    
    // 从新闻列表中删除
    if (!deleteNewsNode(&newsList, id)) {
        printf("删除新闻失败！\n");
        freeNewsList(newsList);
        free(deletedNews);
        return 0;
    }
    
    // 保存更新后的新闻列表
    if (!saveNewsToFile(newsList, NEWS_FILE)) {
        printf("保存新闻数据失败！\n");
        freeNewsList(newsList);
        free(deletedNews);
        return 0;
    }
    
    // 加载已删除新闻列表
    News* deletedNewsList = loadDeletedNewsFromFile(DELETED_NEWS_FILE);
    
    // 添加到已删除列表
    insertNewsNode(&deletedNewsList, deletedNews);
    
    // 保存已删除新闻列表
    if (!saveDeletedNewsToFile(deletedNewsList, DELETED_NEWS_FILE)) {
        printf("保存已删除新闻数据失败！\n");
        freeNewsList(newsList);
        freeNewsList(deletedNewsList);
        return 0;
    }
    
    freeNewsList(newsList);
    freeNewsList(deletedNewsList);
    return 1;
}

// ===================== 分类管理函数实现 =====================

// 分类数据文件名
#define CATEGORIES_FILE "categories.txt"

// 添加分类
int addCategory(char* category) {
    if (category == NULL || strlen(category) == 0) {
        return 0;
    }
    
    // 加载现有分类列表
    int count;
    char** categories = loadCategoriesFromFile(CATEGORIES_FILE, &count);
    
    // 检查分类是否已存在
    for (int i = 0; i < count; i++) {
        if (strcmp(categories[i], category) == 0) {
            printf("分类已存在！\n");
            freeCategories(categories, count);
            return 0;
        }
    }
    
    // 添加新分类，创建新数组（原数量+1）
    char** newCategories = (char**)malloc((count + 1) * sizeof(char*));
    
    if (newCategories == NULL) {
        freeCategories(categories, count);
        return 0;
    }
    //复制原有的旧分类到新数组
    for (int i = 0; i < count; i++) {
        newCategories[i] = categories[i];
    }
    //添加新的分类
    newCategories[count] = (char*)malloc(strlen(category) + 1);
    if (newCategories[count] == NULL) {
        free(newCategories);
        freeCategories(categories, count);
        return 0;
    }
    strcpy(newCategories[count], category);
    
    // 保存到文件
    int result = saveCategoriesToFile(newCategories, count + 1, CATEGORIES_FILE);
    
    free(newCategories[count]);
    free(newCategories);
    freeCategories(categories, count);
    
    return result;
}

// 删除分类
int deleteCategory(char* category) {
    if (category == NULL || strlen(category) == 0) {
        return 0;
    }
    
    // 加载现有分类列表
    int count;
    char** categories = loadCategoriesFromFile(CATEGORIES_FILE, &count);
    
    if (categories == NULL || count == 0) {
        printf("分类列表为空！\n");
        return 0;
    }
    
    // 查找并删除分类
    int found = 0;
    char** newCategories = (char**)malloc(count * sizeof(char*));
    if (newCategories == NULL) {
        freeCategories(categories, count);
        return 0;
    }
    
    int newCount = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(categories[i], category) == 0) {
            found = 1;
        } else {
            newCategories[newCount++] = categories[i];
        }
    }
    
    if (!found) {
        printf("分类不存在！\n");
        free(newCategories);
        freeCategories(categories, count);
        return 0;
    }
    
    // 保存到文件
    int result = saveCategoriesToFile(newCategories, newCount, CATEGORIES_FILE);
    
    free(newCategories);
    freeCategories(categories, count);
    
    return result;
}

// 获取所有分类
char** getCategories(int* count) {
    return loadCategoriesFromFile(CATEGORIES_FILE, count);
}

// 按分类查询新闻（包括已删除新闻）
News* searchNewsByCategory(char* category, int includeDeleted) {
    News* resultList = NULL;
    
    // 加载正常新闻列表
    News* newsList = loadNewsFromFile(NEWS_FILE);
    News* temp = newsList;
    
    while (temp != NULL) {
        if (strcmp(temp->category, category) == 0) {
            News* newsCopy = createNewsNode(
                temp->id,
                temp->title,
                temp->content,
                temp->author,
                temp->category,
                temp->publishDate,
                temp->imagePath,
                temp->status
            );
            
            if (newsCopy != NULL) {
                insertNewsNode(&resultList, newsCopy);
            }
        }
        temp = temp->next;
    }
    
    freeNewsList(newsList);
    
    // 如果需要包含已删除新闻
    if (includeDeleted) {
        News* deletedNewsList = loadDeletedNewsFromFile(DELETED_NEWS_FILE);
        temp = deletedNewsList;
        
        while (temp != NULL) {
            if (strcmp(temp->category, category) == 0) {
                News* newsCopy = createNewsNode(
                    temp->id,
                    temp->title,
                    temp->content,
                    temp->author,
                    temp->category,
                    temp->publishDate,
                    temp->imagePath,
                    temp->status
                );
                
                if (newsCopy != NULL) {
                    insertNewsNode(&resultList, newsCopy);
                }
            }
            temp = temp->next;
        }
        
        freeNewsList(deletedNewsList);
    }
    
    return resultList;
}

// 按日期查询新闻（年、月、日）
News* searchNewsByDate(int year, int month, int day, int includeDeleted) {
    News* resultList = NULL;
    
    // 构建日期字符串
    char dateStr[20];
    if (day > 0) {
        sprintf(dateStr, "%04d-%02d-%02d", year, month, day);
    } else if (month > 0) {
        sprintf(dateStr, "%04d-%02d", year, month);
    } else {
        sprintf(dateStr, "%04d", year);
    }
    
    // 加载正常新闻列表
    News* newsList = loadNewsFromFile(NEWS_FILE);
    News* temp = newsList;
    
    while (temp != NULL) {
        int match = 0;
        
        if (day > 0) {
            // 按年月日查询
            if (strcmp(temp->publishDate, dateStr) == 0) {
                match = 1;
            }
        } else if (month > 0) {
            // 按年月查询
            if (strncmp(temp->publishDate, dateStr, 7) == 0) {
                match = 1;
            }
        } else {
            // 按年查询
            if (strncmp(temp->publishDate, dateStr, 4) == 0) {
                match = 1;
            }
        }
        
        if (match) {
            News* newsCopy = createNewsNode(
                temp->id,
                temp->title,
                temp->content,
                temp->author,
                temp->category,
                temp->publishDate,
                temp->imagePath,
                temp->status
            );
            
            if (newsCopy != NULL) {
                insertNewsNode(&resultList, newsCopy);
            }
        }
        
        temp = temp->next;
    }
    
    freeNewsList(newsList);
    
    // 如果需要包含已删除新闻
    if (includeDeleted) {
        News* deletedNewsList = loadDeletedNewsFromFile(DELETED_NEWS_FILE);
        temp = deletedNewsList;
        
        while (temp != NULL) {
            int match = 0;
            
            if (day > 0) {
                if (strcmp(temp->publishDate, dateStr) == 0) {
                    match = 1;
                }
            } else if (month > 0) {
                if (strncmp(temp->publishDate, dateStr, 7) == 0) {
                    match = 1;
                }
            } else {
                if (strncmp(temp->publishDate, dateStr, 4) == 0) {
                    match = 1;
                }
            }
            
            if (match) {
                News* newsCopy = createNewsNode(
                    temp->id,
                    temp->title,
                    temp->content,
                    temp->author,
                    temp->category,
                    temp->publishDate,
                    temp->imagePath,
                    temp->status
                );
                
                if (newsCopy != NULL) {
                    insertNewsNode(&resultList, newsCopy);
                }
            }
            
            temp = temp->next;
        }
        
        freeNewsList(deletedNewsList);
    }
    
    return resultList;
}

// 查询所有新闻记录（包括已删除）
News* getAllNews(int includeDeleted) {
    News* resultList = NULL;
    
    // 加载正常新闻列表
    News* newsList = loadNewsFromFile(NEWS_FILE);
    News* temp = newsList;
    
    while (temp != NULL) {
        News* newsCopy = createNewsNode(
            temp->id,
            temp->title,
            temp->content,
            temp->author,
            temp->category,
            temp->publishDate,
            temp->imagePath,
            temp->status
        );
        
        if (newsCopy != NULL) {
            insertNewsNode(&resultList, newsCopy);
        }
        
        temp = temp->next;
    }
    
    freeNewsList(newsList);
    
    // 如果需要包含已删除新闻
    if (includeDeleted) {
        News* deletedNewsList = loadDeletedNewsFromFile(DELETED_NEWS_FILE);
        temp = deletedNewsList;
        
        while (temp != NULL) {
            News* newsCopy = createNewsNode(
                temp->id,
                temp->title,
                temp->content,
                temp->author,
                temp->category,
                temp->publishDate,
                temp->imagePath,
                temp->status
            );
            
            if (newsCopy != NULL) {
                insertNewsNode(&resultList, newsCopy);
            }
            
            temp = temp->next;
        }
        
        freeNewsList(deletedNewsList);
    }
    
    return resultList;
}

// 统计新闻总数
int countNews() {
    News* newsList = loadNewsFromFile(NEWS_FILE);
    if (newsList == NULL) {
        return 0;
    }
    
    int count = 0;
    News* temp = newsList;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    
    freeNewsList(newsList);
    return count;
}

// 统计指定状态的新闻数量
int countNewsByStatus(int status) {
    News* newsList = loadNewsFromFile(NEWS_FILE);
    if (newsList == NULL) {
        return 0;
    }
    
    int count = 0;
    News* temp = newsList;
    while (temp != NULL) {
        if (temp->status == status) {
            count++;
        }
        temp = temp->next;
    }
    
    freeNewsList(newsList);
    return count;
}

// 统计指定分类的新闻数量
int countNewsByCategory(char* category) {
    News* newsList = loadNewsFromFile(NEWS_FILE);
    if (newsList == NULL) {
        return 0;
    }
    
    int count = 0;
    News* temp = newsList;
    while (temp != NULL) {
        if (strcmp(temp->category, category) == 0) {
            count++;
        }
        temp = temp->next;
    }
    
    freeNewsList(newsList);
    return count;
}

// 新闻查询函数（支持多种条件查询）
News* searchNews(char* keyword, char* category, char* startDate, char* endDate) {
    // 加载现有新闻列表
    News* newsList = loadNewsFromFile(NEWS_FILE);
    News* resultList = NULL;
    
    News* temp = newsList;
    while (temp != NULL) {
        int match = 1;
        
        // 关键词匹配（标题或内容）
        if (keyword != NULL && strlen(keyword) > 0) {
            if (!stringContains(temp->title, keyword) && !stringContains(temp->content, keyword)) {
                match = 0;
            }
        }
        
        // 分类匹配
        if (match && category != NULL && strlen(category) > 0) {
            if (strcmp(temp->category, category) != 0) {
                match = 0;
            }
        }
        
        // 开始日期匹配
        if (match && startDate != NULL && strlen(startDate) > 0) {
            if (compareDates(temp->publishDate, startDate) < 0) {
                match = 0;
            }
        }
        
        // 结束日期匹配
        if (match && endDate != NULL && strlen(endDate) > 0) {
            if (compareDates(temp->publishDate, endDate) > 0) {
                match = 0;
            }
        }
        
        // 如果匹配所有条件，添加到结果列表
        if (match) {
            News* newsCopy = createNewsNode(
                temp->id,
                temp->title,
                temp->content,
                temp->author,
                temp->category,
                temp->publishDate,
                temp->imagePath,
                temp->status
            );
            
            if (newsCopy != NULL) {
                insertNewsNode(&resultList, newsCopy);
            }
        }
        
        temp = temp->next;
    }
    
    freeNewsList(newsList);
    return resultList;
}

// 新闻排序函数
News* sortNews(News* newsList, char* sortBy, int order) {
    if (newsList == NULL || sortBy == NULL) {
        return NULL;
    }
    
    // 创建新闻列表副本
    News* sortedList = NULL;
    News* temp = newsList;
    
    // 复制所有新闻到新列表
    while (temp != NULL) {
        News* newsCopy = createNewsNode(
            temp->id,
            temp->title,
            temp->content,
            temp->author,
            temp->category,
            temp->publishDate,
            temp->imagePath,
            temp->status
        );
        
        if (newsCopy != NULL) {
            insertNewsNode(&sortedList, newsCopy);
        }
        
        temp = temp->next;
    }
    
    // 冒泡排序
    if (sortedList != NULL) {
        int swapped;
        News* ptr1;
        News* lptr = NULL;
        
        do {
            swapped = 0;
            ptr1 = sortedList;
            
            while (ptr1->next != lptr) {
                int compareResult = 0;
                
                // 根据排序字段比较
                if (strcmp(sortBy, "date") == 0) {
                    // 按日期排序
                    compareResult = compareDates(ptr1->publishDate, ptr1->next->publishDate);
                } else if (strcmp(sortBy, "author") == 0) {
                    // 按作者排序
                    compareResult = strcmp(ptr1->author, ptr1->next->author);
                } else if (strcmp(sortBy, "title") == 0) {
                    // 按标题排序
                    compareResult = strcmp(ptr1->title, ptr1->next->title);
                }
                
                // 根据排序顺序调整比较结果
                if (order == 1) { // 升序
                    compareResult *= -1;
                }
                
                // 如果需要交换，交换节点内容
                if (compareResult > 0) {
                    // 交换节点内容
                    char tempId[20], tempTitle[100], tempContent[1000];
                    char tempAuthor[50], tempCategory[20], tempDate[20];
                    int tempStatus;
                    
                    // 保存第一个节点的内容
                    strcpy(tempId, ptr1->id);
                    strcpy(tempTitle, ptr1->title);
                    strcpy(tempContent, ptr1->content);
                    strcpy(tempAuthor, ptr1->author);
                    strcpy(tempCategory, ptr1->category);
                    strcpy(tempDate, ptr1->publishDate);
                    tempStatus = ptr1->status;
                    
                    // 复制第二个节点的内容到第一个节点
                    strcpy(ptr1->id, ptr1->next->id);
                    strcpy(ptr1->title, ptr1->next->title);
                    strcpy(ptr1->content, ptr1->next->content);
                    strcpy(ptr1->author, ptr1->next->author);
                    strcpy(ptr1->category, ptr1->next->category);
                    strcpy(ptr1->publishDate, ptr1->next->publishDate);
                    ptr1->status = ptr1->next->status;
                    
                    // 复制保存的内容到第二个节点
                    strcpy(ptr1->next->id, tempId);
                    strcpy(ptr1->next->title, tempTitle);
                    strcpy(ptr1->next->content, tempContent);
                    strcpy(ptr1->next->author, tempAuthor);
                    strcpy(ptr1->next->category, tempCategory);
                    strcpy(ptr1->next->publishDate, tempDate);
                    ptr1->next->status = tempStatus;
                    
                    swapped = 1;
                }
                
                ptr1 = ptr1->next;
            }
            
            lptr = ptr1;
        } while (swapped);
    }
    
    return sortedList;
}

// 获取新闻列表函数
News* getNewsList() {
    return loadNewsFromFile(NEWS_FILE);
}

// 根据ID查找新闻函数
News* findNewsById(char* id) {
    if (id == NULL || strlen(id) == 0) {
        return NULL;
    }
    
    // 加载新闻列表
    News* newsList = loadNewsFromFile(NEWS_FILE);
    
    // 查找新闻
    News* targetNews = findNewsNode(newsList, id);
    
    // 创建副本
    News* result = NULL;
    if (targetNews != NULL) {
        result = createNewsNode(
            targetNews->id,
            targetNews->title,
            targetNews->content,
            targetNews->author,
            targetNews->category,
            targetNews->publishDate,
            targetNews->imagePath,
            targetNews->status
        );
    }
    
    // 释放原列表
    freeNewsList(newsList);
    
    return result;
}

// 新闻审核通过函数
int approveNews(char* id) {
    if (id == NULL || strlen(id) == 0) {
        return 0;
    }
    
    // 加载新闻列表
    News* newsList = loadNewsFromFile(NEWS_FILE);
    
    // 查找要审核的新闻
    News* targetNews = findNewsNode(newsList, id);
    if (targetNews == NULL) {
        printf("新闻不存在！\n");
        freeNewsList(newsList);
        return 0;
    }
    
    // 更新新闻状态为已审核
    targetNews->status = 1;
    
    // 保存到文件
    if (!saveNewsToFile(newsList, NEWS_FILE)) {
        printf("保存新闻数据失败！\n");
        freeNewsList(newsList);
        return 0;
    }
    
    freeNewsList(newsList);
    return 1;
}

// 新闻审核拒绝函数
int rejectNews(char* id) {
    if (id == NULL || strlen(id) == 0) {
        return 0;
    }
    
    // 加载新闻列表
    News* newsList = loadNewsFromFile(NEWS_FILE);
    
    // 查找要审核的新闻
    News* targetNews = findNewsNode(newsList, id);
    if (targetNews == NULL) {
        printf("新闻不存在！\n");
        freeNewsList(newsList);
        return 0;
    }
    
    // 更新新闻状态为已拒绝（使用状态2表示已删除/拒绝）
    targetNews->status = 2;
    
    // 保存到文件
    if (!saveNewsToFile(newsList, NEWS_FILE)) {
        printf("保存新闻数据失败！\n");
        freeNewsList(newsList);
        return 0;
    }
    
    freeNewsList(newsList);
    return 1;
}

// 获取待审核新闻列表函数
News* getPendingNews() {
    // 加载新闻列表
    News* newsList = loadNewsFromFile(NEWS_FILE);
    News* pendingList = NULL;
    
    News* temp = newsList;
    while (temp != NULL) {
        // 筛选状态为0（未审核）的新闻
        if (temp->status == 0) {
            News* newsCopy = createNewsNode(
                temp->id,
                temp->title,
                temp->content,
                temp->author,
                temp->category,
                temp->publishDate,
                temp->imagePath,
                temp->status
            );
            
            if (newsCopy != NULL) {
                insertNewsNode(&pendingList, newsCopy);
            }
        }
        
        temp = temp->next;
    }
    
    freeNewsList(newsList);
    return pendingList;
}

// 获取已删除新闻列表函数
News* getDeletedNews() {
    return loadDeletedNewsFromFile(DELETED_NEWS_FILE);
}

// 恢复已删除新闻函数
int restoreNews(char* id) {
    if (id == NULL || strlen(id) == 0) {
        return 0;
    }
    
    // 加载已删除新闻列表
    News* deletedNewsList = loadDeletedNewsFromFile(DELETED_NEWS_FILE);
    
    // 查找要恢复的新闻
    News* targetNews = findNewsNode(deletedNewsList, id);
    if (targetNews == NULL) {
        printf("新闻不存在！\n");
        freeNewsList(deletedNewsList);
        return 0;
    }
    
    // 创建新闻副本，状态设为已审核
    News* restoredNews = createNewsNode(
        targetNews->id,
        targetNews->title,
        targetNews->content,
        targetNews->author,
        targetNews->category,
        targetNews->publishDate,
        targetNews->imagePath,
        1 // 设置状态为已审核
    );
    
    if (restoredNews == NULL) {
        freeNewsList(deletedNewsList);
        return 0;
    }
    
    // 从已删除列表中删除
    if (!deleteNewsNode(&deletedNewsList, id)) {
        printf("恢复新闻失败！\n");
        freeNewsList(deletedNewsList);
        free(restoredNews);
        return 0;
    }
    
    // 保存更新后的已删除新闻列表
    if (!saveDeletedNewsToFile(deletedNewsList, DELETED_NEWS_FILE)) {
        printf("保存已删除新闻数据失败！\n");
        freeNewsList(deletedNewsList);
        free(restoredNews);
        return 0;
    }
    
    // 加载现有新闻列表
    News* newsList = loadNewsFromFile(NEWS_FILE);
    
    // 添加到新闻列表
    insertNewsNode(&newsList, restoredNews);
    
    // 保存到新闻文件
    if (!saveNewsToFile(newsList, NEWS_FILE)) {
        printf("保存新闻数据失败！\n");
        freeNewsList(newsList);
        freeNewsList(deletedNewsList);
        return 0;
    }
    
    freeNewsList(newsList);
    freeNewsList(deletedNewsList);
    return 1;
}
