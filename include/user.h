#ifndef USER_H
#define USER_H

#include "structs.h"

// 用户管理模块核心函数

// 用户注册函数
// 参数：username - 用户名，password - 密码，role - 用户角色
// 返回：注册成功返回用户指针，失败返回NULL
User* registerUser(char* username, char* password, int role);

// 用户登录函数
// 参数：username - 用户名，password - 密码
// 返回：登录成功返回用户指针，失败返回NULL
User* loginUser(char* username, char* password);

// 权限验证函数
// 参数：user - 用户指针，requiredRole - 所需角色级别
// 返回：权限足够返回1，否则返回0
int checkPermission(User* user, int requiredRole);

// 获取用户列表函数
// 返回：用户链表头指针
User* getUserList();

// 添加用户函数
// 参数：user - 要添加的用户指针
// 返回：添加成功返回1，失败返回0
int addUser(User* user);

// 更新用户信息函数
// 参数：user - 要更新的用户指针
// 返回：更新成功返回1，失败返回0
int updateUser(User* user);

// 删除用户函数
// 参数：username - 要删除的用户名
// 返回：删除成功返回1，失败返回0
int deleteUser(char* username);

// 修改密码函数
// 参数：username - 用户名，newPassword - 新密码
// 返回：修改成功返回1，失败返回0
int changePassword(char* username, char* newPassword);

// 统计函数
// 统计用户总数
int countUsers();

// 统计指定角色的用户数量
int countUsersByRole(int role);

#endif /* USER_H */