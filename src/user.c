#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/user.h"
#include "../include/list.h"
#include "../include/file.h"

// 用户数据文件名
#define USER_FILE "users.txt"

// 用户注册函数
User* registerUser(char* username, char* password, int role) {
    // 加载现有用户列表,从文件中加载用户数据
    User* userList = loadUsersFromFile(USER_FILE);
    
    // 检查用户名是否已存在
    if (findUserNode(userList, username) != NULL) {
        printf("用户名已存在！\n");
        freeUserList(userList);
        return NULL;
    }
    
    // 创建新用户
    User* newUser = createUserNode(username, password, role);
    if (newUser == NULL) {
        freeUserList(userList);
        return NULL;
    }
    
    // 添加用户列表到链表尾部
    insertUserNode(&userList, newUser);
    
    // 保存到文件
    if (!saveUsersToFile(userList, USER_FILE)) {
        printf("保存用户数据失败！\n");
        freeUserList(userList);
        return NULL;
    }
    
    // 释放用户列表（保留新用户指针）
    User* temp = userList;
    while (temp != NULL && temp != newUser) {
        User* next = temp->next;
        if (temp != newUser) {
            free(temp);
        }
        temp = next;
    }
    
    return newUser;
}

// 用户登录函数
User* loginUser(char* username, char* password) {
    // 加载用户列表或从文件中加载用户数据
    User* userList = loadUsersFromFile(USER_FILE);
    if (userList == NULL) {
        printf("用户列表为空！\n");
        return NULL;
    }
    
    // 查找用户
    User* user = findUserNode(userList, username);
    if (user == NULL) {
        printf("用户名不存在！\n");
        freeUserList(userList);
        return NULL;
    }
    
    // 验证密码
    if (strcmp(user->password, password) != 0) {
        printf("密码错误！\n");
        freeUserList(userList);
        return NULL;
    }
    
    // 创建用户副本并释放原列表
    User* loginUser = (User*)malloc(sizeof(User));
    if (loginUser == NULL) {
        printf("内存分配失败！\n");
        freeUserList(userList);
        return NULL;
    }
    
    memcpy(loginUser, user, sizeof(User));
    loginUser->next = NULL;
    
    freeUserList(userList);
    return loginUser;
}

// 权限验证函数
int checkPermission(User* user, int requiredRole) {
    if (user == NULL) {
        return 0; // 未登录用户无权限
    }
    
    // 角色级别：0-访客，1-普通用户，2-管理员
    // 管理员(2)拥有所有权限，普通用户(1)拥有普通用户权限，访客(0)权限最低
    return user->role >= requiredRole;
}

// 获取用户列表函数
User* getUserList() {
    return loadUsersFromFile(USER_FILE);
}

// 添加用户函数（管理员功能）
int addUser(User* user) {
    if (user == NULL) {
        return 0;
    }
    
    // 加载现有用户列表
    User* userList = loadUsersFromFile(USER_FILE);
    
    // 检查用户名是否已存在
    if (findUserNode(userList, user->username) != NULL) {
        printf("用户名已存在！\n");
        freeUserList(userList);
        return 0;
    }
    
    // 创建新用户节点
    User* newUser = createUserNode(user->username, user->password, user->role);
    if (newUser == NULL) {
        freeUserList(userList);
        return 0;
    }
    
    // 添加到用户列表
    insertUserNode(&userList, newUser);
    
    // 保存到文件
    if (!saveUsersToFile(userList, USER_FILE)) {
        printf("保存用户数据失败！\n");
        freeUserList(userList);
        return 0;
    }
    
    freeUserList(userList);
    return 1;
}

int changePassword(char* username, char* newPassword) {
    if (username == NULL || newPassword == NULL || strlen(username) == 0 || strlen(newPassword) == 0) {
        return 0;
    }
    
    User* userList = loadUsersFromFile(USER_FILE);
    
    User* targetUser = findUserNode(userList, username);
    if (targetUser == NULL) {
        printf("用户不存在！\n");
        freeUserList(userList);
        return 0;
    }
    
    strcpy(targetUser->password, newPassword);
    
    if (!saveUsersToFile(userList, USER_FILE)) {
        printf("保存用户数据失败！\n");
        freeUserList(userList);
        return 0;
    }
    
    freeUserList(userList);
    return 1;
}

// 统计用户总数
int countUsers() {
    User* userList = loadUsersFromFile(USER_FILE);
    if (userList == NULL) {
        return 0;
    }
    
    int count = 0;
    User* temp = userList;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    
    freeUserList(userList);
    return count;
}

// 统计指定角色的用户数量
int countUsersByRole(int role) {
    User* userList = loadUsersFromFile(USER_FILE);
    if (userList == NULL) {
        return 0;
    }
    
    int count = 0;
    User* temp = userList;
    while (temp != NULL) {
        if (temp->role == role) {
            count++;
        }
        temp = temp->next;
    }
    
    freeUserList(userList);
    return count;
}

// 更新用户信息函数（管理员功能）
int updateUser(User* user) {
    if (user == NULL) {
        return 0;
    }
    
    // 加载用户列表
    User* userList = loadUsersFromFile(USER_FILE);
    
    // 查找用户
    User* targetUser = findUserNode(userList, user->username);
    if (targetUser == NULL) {
        printf("用户不存在！\n");
        freeUserList(userList);
        return 0;
    }
    
    // 更新用户信息
    strcpy(targetUser->password, user->password);
    targetUser->role = user->role;
    
    // 保存到文件
    if (!saveUsersToFile(userList, USER_FILE)) {
        printf("保存用户数据失败！\n");
        freeUserList(userList);
        return 0;
    }
    
    freeUserList(userList);
    return 1;
}

// 删除用户函数（管理员功能）
int deleteUser(char* username) {
    if (username == NULL || strlen(username) == 0) {
        return 0;
    }
    
    // 加载用户列表
    User* userList = loadUsersFromFile(USER_FILE);
    
    // 删除用户
    if (!deleteUserNode(&userList, username)) {
        printf("用户不存在！\n");
        freeUserList(userList);
        return 0;
    }
    
    // 保存到文件
    if (!saveUsersToFile(userList, USER_FILE)) {
        printf("保存用户数据失败！\n");
        freeUserList(userList);
        return 0;
    }
    
    freeUserList(userList);
    return 1;
}