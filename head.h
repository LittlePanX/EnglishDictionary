#pragma once

#define MAX_USER 100    // 最大用户数
#define MAX_NAME 50     // 最大用户名长度
#define MAX_PASS 50     // 最大密码长度

//声明全局变量
char currentUser[MAX_NAME] = ""; // 当前登录用户
int page = 0;

// 单词结构体定义
typedef struct {
    char english[50];      // 英文单词
    char chinese[200];     // 中文释义
} Word;

// 选项结构体定义
typedef struct {
    char option[200];      // 选项内容
    int isCorrect;         // 是否为正确选项
} Option;

// 定义的错误单词结构体
typedef struct {
    char english[50];
    char chinese[200];
    int errorcount;
} errorwords;

// 定义的错误单词结构体
typedef struct {
    char english[50];
    char chinese[200];
    int errornumber;
    int mistake2;//该变量只服务于随机数
}test;

// 用户登录/注册界面   Powerby 潘钰楷 
int userLoginMenu();
int userLogin();
int userRegister();
int checkUser(const char* username, const char* password);
int userExists(const char* username);

// 浏览单词本   Powerby 潘钰楷
void browseWords(void);
void saveProgress(void); // 保存当前进度到文件
void loadProgress(void); // 加载上次保存的进度

// 查询单词   Powerby 龙海峰
void searchWord();
void searchWordByEnglish(const char* english);	// case 1 根据英文查单词
void searchWordByChinese(const char* chinese);	// case 2 根据中文查单词

// 默写单词   Powerby 李俊超
void selfStudy();
void testWordsEtoC();  // 英文转中文测试
void testWordsCtoE();  // 中文转英文测试
void exitTest();

// 单词收藏本   Powerby 潘钰楷
void vocabularyBook(void);
void addtobook(const char* word);		// 添加到单词本 case 3		输入单词和含义
void removefrombook(const char* word);	// 从单词本中删除 case 4		输入对应序号删除
void InitFile(void);	// 初始化单词本文件 case 5

// 错题再练   Powerby 龙海峰
void enhanceMemory();
void generateOptions1(Option options[], test word, int mode);

// 单词测验   Powerby 李俊超
void selfTest();
void learnWordsEtoC();   // 英文→中文背单词
void learnWordsCtoE();   // 中文→英文背单词
void exitStudyProgram();
void generateOptions(Option options[], Word word, int mode); // 生成选项

// 退出程序   Powerby 潘钰楷
void exitProgram(void);
