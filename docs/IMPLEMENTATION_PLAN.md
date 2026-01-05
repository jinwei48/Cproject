# 校园新闻发布管理系统 - 实现计划

## 1. 系统概述

校园新闻发布管理系统是一个基于C语言开发的桌面应用程序，用于管理校园内的新闻发布、浏览和评论。系统支持三种类型的用户（管理员、普通用户、访客），并提供新闻分类管理、新闻管理、评论管理、用户管理等功能。数据采用文件存储方式，使用结构体和动态链表实现数据的内存管理。

## 2. 总体架构设计

### 2.1 架构概述

系统采用模块化设计，将功能划分为多个独立的模块，每个模块负责特定的功能领域。模块之间通过接口进行通信，提高代码的可维护性和可扩展性。

### 2.2 核心模块

| 模块名称 | 主要功能 | 相关文件 |
|---------|---------|---------|
| 用户管理模块 | 用户注册、登录、权限验证、用户信息管理、密码修改、用户统计 | `user.h`, `user.c` |
| 新闻管理模块 | 新闻的添加、修改、删除、查询、排序、审核、恢复、统计 | `news.h`, `news.c` |
| 评论管理模块 | 评论的添加、查询、显示、删除、统计 | `comment.h`, `comment.c` |
| 分类管理模块 | 新闻分类的管理（通知、公告、简讯等） | `news.h`, `news.c` |
| 文件操作模块 | 数据的文件存储与读取（包括已删除数据） | `file.h`, `file.c` |
| 界面模块 | 系统的交互界面（控制台界面 + GTK图形界面） | `ui.h`, `ui.c`, `gui.h`, `gui.c` |
| 链表操作模块 | 动态链表的基本操作（创建、插入、删除、遍历） | `list.h`, `list.c` |
| 工具模块 | 通用功能支持（如日期处理、字符串处理、ID生成） | `utils.h`, `utils.c` |

### 2.3 数据结构设计

#### 2.3.1 用户结构体
```c
typedef struct User {
    char username[50];       // 用户名
    char password[50];       // 密码
    int role;                // 角色：0-访客，1-普通用户，2-管理员
    struct User *next;       // 链表指针
} User;
```

#### 2.3.2 新闻结构体
```c
typedef struct News {
    char id[20];             // 新闻ID（唯一标识）
    char title[100];         // 新闻标题
    char content[1000];      // 新闻内容
    char author[50];         // 发布者
    char category[20];       // 新闻分类
    char publishDate[20];    // 发布日期
    char imagePath[200];     //新闻图片路径
    int status;              // 状态：0-未审核，1-已审核，2-已删除
    struct Comment *comments; // 评论链表
    struct News *next;       // 链表指针
} News;
```

#### 2.3.3 评论结构体
```c
typedef struct Comment {
    char newsId[20];         // 所属新闻ID
    char username[50];       // 评论用户
    char content[500];       // 评论内容
    char commentDate[20];    // 评论日期
    struct Comment *next;    // 链表指针
} Comment;
```

### 2.4 系统流程图

```
┌─────────────────┐     ┌─────────────────┐     ┌─────────────────┐
│  用户界面层     │────▶│  业务逻辑层     │────▶│  数据访问层     │
│ (ui.h, ui.c)    │◀────│(user.h, news.h, │◀────│ (file.h, file.c)│
│ (gui.h, gui.c)  │     │ comment.h, etc) │     │                 │
└─────────────────┘     └─────────────────┘     └─────────────────┘
                              │
                              ▼
                       ┌─────────────────┐
                       │  链表操作层     │
                       │  (list.h, list.c)│
                       └─────────────────┘
```

## 3. 详细模块设计

### 3.1 用户管理模块

#### 3.1.1 功能描述
- 用户注册：普通用户注册账号
- 用户登录：验证用户名和密码，确定用户角色
- 权限验证：根据用户角色限制功能访问
- 用户管理：管理员可以添加、修改、删除用户账号
- 密码修改：用户可以修改自己的密码
- 用户统计：统计用户总数和各角色用户数量

#### 3.1.2 核心函数
- `User* registerUser(char* username, char* password, int role)`
- `User* loginUser(char* username, char* password)`
- `int checkPermission(User* user, int requiredRole)`
- `User* getUserList()`
- `int addUser(User* user)`
- `int updateUser(User* user)`
- `int deleteUser(char* username)`
- `int changePassword(char* username, char* newPassword)`
- `int countUsers()`
- `int countUsersByRole(int role)`

### 3.2 新闻管理模块

#### 3.2.1 功能描述
- 新闻添加：授权用户添加新闻（支持图片路径）
- 新闻修改：管理员可以修改新闻内容
- 新闻删除：管理员可以删除新闻（实际移至删除文件）
- 新闻恢复：管理员可以恢复已删除的新闻
- 新闻审核：管理员可以审核待发布的新闻（通过/拒绝）
- 新闻查询：按条件查询新闻（关键词、分类、日期范围）
- 新闻排序：按发布日期、作者、标题等字段排序
- 新闻统计：统计新闻总数、各状态新闻数量、各分类新闻数量
- 分类管理：添加、删除、查询新闻分类
- 按日期查询：按年、月、日查询新闻
- 查询已删除新闻：查看已删除的新闻记录

#### 3.2.2 核心函数
- `News* addNews(char* title, char* content, char* author, char* category, char* imagePath)`
- `int updateNews(char* id, char* title, char* content, char* category, char* imagePath)`
- `int deleteNews(char* id)`
- `int restoreNews(char* id)`
- `int approveNews(char* id)`
- `int rejectNews(char* id)`
- `News* getPendingNews()`
- `News* searchNews(char* keyword, char* category, char* startDate, char* endDate)`
- `News* sortNews(News* newsList, char* sortBy, int order)`
- `News* getNewsList()`
- `News* findNewsById(char* id)`
- `News* getDeletedNews()`
- `int countNews()`
- `int countNewsByStatus(int status)`
- `int countNewsByCategory(char* category)`
- `int addCategory(char* category)`
- `int deleteCategory(char* category)`
- `char** getCategories(int* count)`
- `News* searchNewsByCategory(char* category, int includeDeleted)`
- `News* searchNewsByDate(int year, int month, int day, int includeDeleted)`
- `News* getAllNews(int includeDeleted)`

### 3.3 评论管理模块

#### 3.3.1 功能描述
- 评论添加：普通用户可以对新闻发表评论
- 评论查询：获取特定新闻的所有评论
- 评论显示：在新闻阅读时显示评论
- 评论删除：用户可以删除自己的评论
- 评论统计：统计新闻的评论数量
- 按用户查询：获取指定用户的所有评论

#### 3.3.2 核心函数
- `Comment* addComment(char* newsId, char* username, char* content)`
- `Comment* getCommentsByNewsId(char* newsId)`
- `void displayComments(Comment* comments)`
- `int deleteComment(char* newsId, char* username, char* commentDate)`
- `Comment* getCommentList()`
- `Comment* getCommentsByUsername(char* username)`
- `void freeCommentList(Comment* commentList)`
- `int countComments(char* newsId)`

### 3.4 分类管理模块

#### 3.4.1 功能描述
- 新闻分类的定义与管理
- 支持动态添加和删除分类
- 按分类查询新闻（包括已删除新闻）

#### 3.4.2 核心函数
- `char** getCategories(int* count)`
- `int addCategory(char* category)`
- `int deleteCategory(char* category)`
- `News* searchNewsByCategory(char* category, int includeDeleted)`

### 3.5 文件操作模块

#### 3.5.1 功能描述
- 数据的持久化存储与读取
- 支持用户数据、新闻数据、已删除新闻数据、评论数据的文件操作
- 支持分类数据的文件操作

#### 3.5.2 核心函数
- `int saveUsersToFile(User* userList, char* filename)`
- `User* loadUsersFromFile(char* filename)`
- `int saveNewsToFile(News* newsList, char* filename)`
- `News* loadNewsFromFile(char* filename)`
- `int saveDeletedNewsToFile(News* newsList, char* filename)`
- `News* loadDeletedNewsFromFile(char* filename)`
- `int saveCommentsToFile(Comment* commentList, char* filename)`
- `Comment* loadCommentsFromFile(char* filename)`
- `int saveCategoriesToFile(char** categories, int count, char* filename)`
- `char** loadCategoriesFromFile(char* filename, int* count)`
- `void freeCategories(char** categories, int count)`

### 3.6 界面模块

#### 3.6.1 功能描述
- 提供用户交互界面（控制台界面 + GTK图形界面）
- 实现菜单导航和功能选择
- 支持分页显示新闻列表
- 提供新闻图片显示功能
- 提供各种输入验证和错误提示

#### 3.6.2 核心函数
- `void showMainMenu()`
- `void showUserMenu(User* user)`
- `void showAdminMenu()`
- `void showGuestMenu()`
- `void showNewsList(News* newsList)`
- `void showNewsListPaged(News* newsList)`
- `void showNewsDetail(News* news)`
- `void showNewsImage(char* imagePath)`
- `void showNewsSearch()`
- `void showNewsSort()`
- `void showAddNews(User* user)`
- `void showEditNews(User* user)`
- `void showDeleteNews(User* user)`
- `void showAddComment(User* user)`
- `void showUserManagement(User* user)`
- `void showUserRegister()`
- `void showUserLogin()`
- `void showUserInfo(User* user)`
- `void showEditUserInfo(User* user)`
- `void showChangePassword(User* user)`
- `void showAllUsers(User* admin)`
- `void showAddUser(User* admin)`
- `void showEditUser(User* admin)`
- `void showDeleteUser(User* admin)`
- `void showNewsAudit()`
- `void showStatistics()`
- `void showDeletedNews()`
- `void showCategoryManagement()`
- `void showDateSearch()`
- `void showAnnouncementManagement()`
- `void showSystemSettings()`
- `void pauseScreen()`
- `void printHeader(char* title)`
- `void printFooter()`
- `void printSeparator()`
- `int getIntInput(char* prompt, int min, int max)`
- `void getStringInput(char* prompt, char* buffer, int maxLength)`

### 3.7 链表操作模块

#### 3.7.1 功能描述
- 提供动态链表的基本操作
- 支持用户、新闻、评论链表的创建、插入、删除、遍历
- 提供链表节点的查找和释放功能

#### 3.7.2 核心函数
- `User* createUserNode(char* username, char* password, int role)`
- `void insertUserNode(User** head, User* newNode)`
- `User* findUserNode(User* head, char* username)`
- `void deleteUserNode(User** head, char* username)`
- `void freeUserList(User* head)`
- `News* createNewsNode(char* id, char* title, char* content, char* author, char* category, char* publishDate, char* imagePath, int status)`
- `void insertNewsNode(News** head, News* newNode)`
- `News* findNewsNode(News* head, char* id)`
- `void deleteNewsNode(News** head, char* id)`
- `void freeNewsList(News* head)`
- `Comment* createCommentNode(char* newsId, char* username, char* content, char* commentDate)`
- `void insertCommentNode(Comment** head, Comment* newNode)`
- `Comment* findCommentNode(Comment* head, char* newsId, char* username, char* commentDate)`
- `void deleteCommentNode(Comment** head, char* newsId, char* username, char* commentDate)`
- `void freeCommentList(Comment* head)`

### 3.8 工具模块

#### 3.8.1 功能描述
- 提供通用功能支持
- 如日期处理、字符串处理、ID生成等

#### 3.8.2 核心函数
- `void getCurrentDate(char* date)`
- `int compareDates(char* date1, char* date2)`
- `char* generateId()`
- `int stringContains(char* str, char* substr)`
- `void replaceString(char* str, char* oldStr, char* newStr)`
- `void trimString(char* str)`

## 4. 数据存储设计

### 4.1 文件结构

| 文件名 | 用途 | 数据格式 |
|-------|------|---------|
| users.txt | 存储用户信息 | 每行一条用户记录，字段用逗号分隔：username,password,role |
| news.txt | 存储新闻信息 | 每条新闻记录包含多行，用分隔符分隔不同新闻 |
| comments.txt | 存储评论信息 | 每行一条评论记录，字段用逗号分隔：newsId,username,content,commentDate |
| news_del.txt | 存储已删除新闻 | 格式与news.txt相同 |
| categories.txt | 存储新闻分类 | 每行一个分类名称 |

### 4.2 文件格式示例

#### 4.2.1 users.txt
```
admin,admin123,2
user1,user123,1
user2,user456,1
```

#### 4.2.2 news.txt
```
ID: news001
Title: 校园春季运动会即将举行
Content: 我校将于下月举行春季运动会，欢迎全体师生踊跃参与...
Author: admin
Category: 通知
PublishDate: 2023-10-15
ImagePath: images/news/news001.jpg
Status: 1
---
ID: news002
Title: 图书馆新馆开放通知
Content: 学校图书馆新馆将于本周六正式开放，新增藏书10万册...
Author: user1
Category: 公告
PublishDate: 2023-10-16
ImagePath: images/news/news002.jpg
Status: 1
---
```

#### 4.2.3 comments.txt
```
news001,user1,这个活动太棒了！,2023-10-15
news001,user2,期待参加运动会,2023-10-15
news002,user1,图书馆新馆环境很好,2023-10-16
```

#### 4.2.4 categories.txt
```
通知
公告
简讯
活动
学术
```

#### 4.2.5 news_del.txt
```
ID: news003
Title: 旧新闻标题
Content: 这是一条已删除的新闻内容...
Author: admin
Category: 简讯
PublishDate: 2023-09-01
ImagePath: images/news/news003.jpg
Status: 2
---
```

## 5. 实现路线图

### 5.1 阶段一：项目初始化与基础结构搭建（预计时间：2天）

**目标**：搭建项目框架，实现基础数据结构和文件操作功能

**技术任务**：
1. 创建项目目录结构（include、src、docs、images、build等）
2. 实现用户、新闻、评论等基础结构体
3. 实现动态链表的基本操作（创建、插入、删除、遍历）
4. 实现文件操作的基本函数
5. 实现工具函数（日期处理、字符串处理、ID生成）

**依赖关系**：无

**输出文件**：
- `structs.h` - 定义所有结构体
- `list.h`, `list.c` - 链表操作函数
- `file.h`, `file.c` - 文件操作函数
- `utils.h`, `utils.c` - 工具函数

### 5.2 阶段二：用户管理模块实现（预计时间：2天）

**目标**：实现用户注册、登录和权限管理功能

**技术任务**：
1. 实现用户注册函数
2. 实现用户登录函数
3. 实现权限验证函数
4. 实现用户信息管理函数（添加、修改、删除）
5. 实现密码修改函数
6. 实现用户统计函数

**依赖关系**：阶段一完成的结构体和文件操作功能

**输出文件**：
- `user.h`, `user.c` - 用户管理函数

### 5.3 阶段三：新闻管理模块实现（预计时间：3天）

**目标**：实现新闻的添加、修改、删除、查询、排序、审核和统计功能

**技术任务**：
1. 实现新闻添加函数（支持图片路径）
2. 实现新闻修改函数
3. 实现新闻删除函数（包括移至删除文件）
4. 实现新闻恢复函数
5. 实现新闻审核函数（通过/拒绝）
6. 实现新闻查询函数（支持多种条件查询）
7. 实现新闻排序函数
8. 实现新闻统计函数
9. 实现分类管理函数
10. 实现按日期查询函数

**依赖关系**：阶段一和阶段二完成的功能

**输出文件**：
- `news.h`, `news.c` - 新闻管理函数

### 5.4 阶段四：评论管理模块实现（预计时间：1天）

**目标**：实现评论的添加、查询、显示、删除和统计功能

**技术任务**：
1. 实现评论添加函数
2. 实现评论查询函数
3. 实现评论显示函数
4. 实现评论删除函数
5. 实现评论统计函数
6. 实现按用户查询评论函数

**依赖关系**：阶段一完成的结构体和文件操作功能

**输出文件**：
- `comment.h`, `comment.c` - 评论管理函数

### 5.5 阶段五：界面模块实现（预计时间：3天）

**目标**：实现系统的交互界面（控制台界面 + GTK图形界面）

**技术任务**：
1. 实现主菜单界面
2. 实现用户菜单界面（根据权限显示不同功能）
3. 实现管理员菜单界面
4. 实现访客菜单界面
5. 实现新闻列表和详情显示界面（支持分页）
6. 实现新闻图片显示功能
7. 实现各种功能的操作界面
8. 实现输入验证和错误提示
9. 实现GTK图形界面（可选）

**依赖关系**：阶段二、三、四完成的功能

**输出文件**：
- `ui.h`, `ui.c` - 控制台界面函数
- `gui.h`, `gui.c` - GTK图形界面函数（可选）

### 5.6 阶段六：系统整合与测试（预计时间：3天）

**目标**：整合所有模块，进行系统测试

**技术任务**：
1. 整合所有模块，实现main函数
2. 进行功能测试
3. 进行边界测试
4. 修复发现的bug
5. 生成测试数据
6. 准备图片资源

**依赖关系**：所有阶段完成的功能

**输出文件**：
- `main.c` - 主程序入口
- `main_gui.c` - GUI主程序入口（可选）
- `test_data/` - 测试数据文件
- `images/` - 图片资源目录

### 5.7 阶段八：文档编写与项目交付（预计时间：1天）

**目标**：完成项目文档，准备项目交付

**技术任务**：
1. 编写项目说明文档
2. 编写用户使用手册
3. 编写GUI版本说明文档
4. 整理代码和相关文件
5. 进行最终检查

**依赖关系**：所有阶段完成的功能和文档

**输出文件**：
- `README.md` - 项目说明文档
- `USER_MANUAL.md` - 用户使用手册
- `README_GUI.md` - GUI版本说明文档
- `IMPLEMENTATION_PLAN.md` - 实现计划文档（本文档）

## 6. 技术栈与环境

### 6.1 开发语言
- C语言

### 6.2 开发环境
- Windows平台
- GCC编译器（MinGW-W64）
- GTK+ 3.0开发库（用于图形界面）
- pkg-config工具（用于GTK+库配置）

### 6.3 技术要点
- 结构体和动态链表的使用
- 文件I/O操作
- 模块化程序设计
- 错误处理机制
- GTK+图形界面开发（可选）
- 控制台界面开发
- 图片资源管理

### 6.4 项目结构
```
News system/
├── include/           # 头文件目录
│   ├── structs.h     # 数据结构定义
│   ├── user.h        # 用户管理头文件
│   ├── news.h        # 新闻管理头文件
│   ├── comment.h     # 评论管理头文件
│   ├── file.h        # 文件操作头文件
│   ├── list.h        # 链表操作头文件
│   ├── utils.h       # 工具函数头文件
│   ├── ui.h          # 控制台界面头文件
│   └── gui.h         # GTK图形界面头文件
├── src/              # 源文件目录
│   ├── user.c        # 用户管理实现
│   ├── news.c        # 新闻管理实现
│   ├── comment.c     # 评论管理实现
│   ├── file.c        # 文件操作实现
│   ├── list.c        # 链表操作实现
│   ├── utils.c       # 工具函数实现
│   ├── ui.c          # 控制台界面实现
│   └── gui.c         # GTK图形界面实现
├── docs/             # 文档目录
│   ├── IMPLEMENTATION_PLAN.md
│   ├── README_GUI.md
│   └── 课设
├── images/           # 图片资源目录
│   ├── avatars/      # 用户头像
│   ├── backgrounds/  # 背景图片
│   ├── icons/        # 图标
│   └── news/         # 新闻图片
├── build/            # 编译输出目录
├── main.c            # 控制台主程序入口
├── main_gui.c        # GUI主程序入口
├── Makefile          # Makefile配置
├── build_gui.bat     # GUI编译脚本
└── run_gui.bat       # GUI运行脚本
```

## 7. 项目管理与质量控制

### 7.1 代码规范
- 采用一致的命名规范
- 每个函数都有详细的注释说明
- 保持适当的代码缩进和格式

### 7.2 测试策略
- 单元测试：对每个模块的核心函数进行测试
- 集成测试：测试模块之间的交互
- 系统测试：对整个系统进行功能测试
- 边界测试：测试极端情况下的系统行为

### 7.3 进度管理
- 每天更新开发进度
- 定期检查功能实现情况
- 及时调整开发计划

## 8. 风险评估与应对措施

| 风险 | 影响 | 应对措施 |
|------|------|--------|
| 文件操作失败 | 数据丢失或损坏 | 实现完善的错误处理机制，定期备份数据 |
| 内存泄漏 | 程序崩溃或性能下降 | 仔细管理动态内存分配和释放，使用内存检测工具 |
| 权限控制不严 | 安全漏洞 | 实现严格的权限验证机制，在每个功能入口检查用户权限 |
| 数据结构设计不合理 | 性能问题或功能受限 | 仔细设计数据结构，考虑扩展性和效率 |

## 9. 扩展功能规划

1. ~~图形界面支持（使用GTK或其他图形库）~~ - 已实现GTK+图形界面
2. 数据库存储支持（替换文件存储）
3. 网络功能支持（远程访问）
4. 多媒体内容支持（图片、视频）- 已支持图片显示
5. 通知功能支持（邮件或系统通知）
6. 用户头像上传功能
7. 新闻富文本编辑器
8. 数据导出功能（导出为PDF、Excel等格式）
9. 搜索历史记录功能
10. 新闻标签系统

## 10. 已实现功能总结

### 10.1 核心功能
- ✅ 用户注册、登录、权限管理
- ✅ 新闻发布、编辑、删除、恢复
- ✅ 新闻审核机制（通过/拒绝）
- ✅ 新闻查询（关键词、分类、日期范围）
- ✅ 新闻排序（日期、作者、标题）
- ✅ 评论管理（添加、查询、删除）
- ✅ 分类管理（添加、删除、查询）
- ✅ 用户管理（添加、编辑、删除）
- ✅ 统计功能（新闻统计、用户统计、评论统计）
- ✅ 密码修改功能
- ✅ 已删除新闻查询和恢复
- ✅ 新闻图片显示功能

### 10.2 界面功能
- ✅ 控制台界面（完整实现）
- ✅ GTK+图形界面（完整实现）
- ✅ 分页显示新闻列表
- ✅ 输入验证和错误提示
- ✅ 美化的界面显示（标题、分隔线、页脚）

### 10.3 数据管理
- ✅ 文件存储（用户、新闻、评论、分类）
- ✅ 软删除机制（已删除新闻单独存储）
- ✅ 动态链表管理
- ✅ 图片资源管理

## 11. 总结

本实现计划详细描述了校园新闻发布管理系统的架构设计和实现路线图。通过模块化设计和分阶段实现，系统已经成功实现了所有核心功能，包括用户管理、新闻管理、评论管理、分类管理等，并提供了控制台和GTK图形界面两种交互方式。系统采用文件存储方式，使用动态链表进行内存管理，实现了完整的权限控制和数据管理功能。

项目特点：
1. 模块化设计，代码结构清晰
2. 双界面支持（控制台 + 图形界面）
3. 完整的权限控制机制
4. 丰富的查询和统计功能
5. 软删除机制，支持数据恢复
6. 图片资源支持
7. 良好的用户体验（分页显示、输入验证等）

该系统适合作为课程设计项目使用，代码质量高，功能完整，易于扩展和维护。