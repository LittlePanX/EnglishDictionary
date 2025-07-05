#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "head.h"

// 主函数   Powerby 潘钰楷
int main() {
    if (!userLoginMenu()) {
        printf("\n登录失败，程序退出。\n");
        return 0;
    }
    // 登录成功后，currentUser已设置
    // 后续所有收藏本操作都用vocab_<currentUser>.txt

    char xz[7];
    while (1) {
        system("cls");
        printf("\n\n\t\t\t    English Dictionary");
        printf("\n\n\t===========================================================");
        printf("\n\n\t\t\t\t0----Exit");
        printf("\n\n\t\t-------------------------------------------");
        printf("\n\n\t\t  1----浏览单词");
        printf("\t\t2----查询单词");
        printf("\n\n\t\t  3----默写单词");
        printf("\t\t4----个人收藏");
        printf("\n\n\t\t  5----错题再练");
        printf("\t\t6----单词测验");
        printf("\n\n\t\t-------------------------------------------");
        printf("\n\n\t===========================================================");
        printf("\n\n\t\t\tPlease choise: (0-6):");
        while (1) {
            gets(xz);
            if (xz[0] >= 48 && xz[0] <= 57) break;
        }
        system("cls");
        switch (xz[0]) {
		case '0': exitProgram(); return 0; break;  // 退出程序   Powerby 潘钰楷
		case '1': browseWords(); break;            // 浏览单词   Powerby 潘钰楷 
		case '2': searchWord(); break;             // 查询单词   Powerby 龙海峰
		case '3': selfStudy(); break;              // 默写单词   Powerby 李俊超
		case '4': vocabularyBook(); break;         // 个人收藏   Powerby 潘钰楷
        case '5': enhanceMemory(); break;          // 错题再练   Powerby 龙海峰
		case '6': selfTest(); break;               // 单词测验   Powerby 李俊超
        }
    }
}

// 用户登录和注册菜单   Powerby 潘钰楷
int userLoginMenu() {
    int choice;
    while (1) {
        system("cls");
        printf("\n\t欢迎使用英语词典系统！\n\n");
        printf("\t1. 登录\n");
        printf("\t2. 注册\n");
        printf("\t0. 退出\n");
        printf("\n\t请选择: ");
        scanf("%d", &choice);
        getchar(); // 吸收回车
        switch (choice) {
        case 0: return 0;
        case 1: if (userLogin()) return 1; break;
        case 2: userRegister(); break;
        default: printf("无效选择！\n"); break;
        }
    }
}

// 登录
int userLogin() {
    char username[MAX_NAME], password[MAX_PASS];
    printf("请输入用户名: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;
    printf("请输入密码: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;
    if (checkUser(username, password)) { // 调用checkUser函数检查用户名和密码
		strcpy(currentUser, username); // 将当前用户设置为登录的用户名
        printf("登录成功！\n");
        system("pause");
        return 1;
    } else {
        printf("用户名或密码错误！\n");
        system("pause");
        return 0;
    }
}

// 注册
int userRegister() {
    char username[MAX_NAME], password[MAX_PASS];
    printf("请输入新用户名: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;
    if (userExists(username)) {
        printf("用户名已存在！\n");
        system("pause");
        return 0;
    }
    printf("请输入新密码: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;
	FILE* fp = fopen("users.txt", "a"); // 追加模式打开用户文件
    if (fp) {
		fprintf(fp, "%s %s\n", username, password); // 将用户名和密码写入文件
        fclose(fp);
        printf("注册成功！\n");
        system("pause");
        return 1;
    }
    printf("注册失败！\n");
    system("pause");
    return 0;
}

// 检查用户名和密码
int checkUser(const char* username, const char* password) {
    FILE* fp = fopen("users.txt", "r");
    char u[MAX_NAME], p[MAX_PASS];
    if (!fp) return 0;
    while (fscanf(fp, "%s %s", u, p) == 2) {
		if (strcmp(u, username) == 0 && strcmp(p, password) == 0) { // 检查用户名和密码是否匹配
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// 检查用户名是否存在
int userExists(const char* username) {
    FILE* fp = fopen("users.txt", "r");
    char u[MAX_NAME], p[MAX_PASS];
    if (!fp) return 0;
    while (fscanf(fp, "%s %s", u, p) == 2) {
        if (strcmp(u, username) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
//----------------------------------------------------------------

// 浏览单词本   Powerby 潘钰楷
void browseWords() {
    FILE* fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printf("无法打开单词文件!\n");
        return;
    }

    char words[300][50];      // 单词本容量为300
    char meanings[300][50];
    int count = 0;

    // 读取单词
    while (count < 300 && fscanf(fp, "%s\t%s", words[count], meanings[count]) == 2) {
        count++;
    }
    fclose(fp);

    int wordsPerPage = 10;    // 每页显示10个单词
    int totalPages = (count + wordsPerPage - 1) / wordsPerPage;

    while (1) {
     F1:system("cls");
        printf("\n\t\t\t单词本 (第%d页/共%d页, 共%d个单词)\n\n", page + 1, totalPages, count);

        // 显示当前页单词
        for (int i = page * wordsPerPage;
            i < (page + 1) * wordsPerPage && i < count;
            i++) {
            printf("%d. %s - %s\n", i + 1, words[i], meanings[i]);
        }

        printf("\n\n0:关闭单词本   1:上一页   2:下一页   3:新增单词   4:删除单词   5:收藏单词\n");
		printf("6:添加书签     7:回到书签位置\n");
        printf("\n请选择操作: ");

        int choice;
        char input[10];
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%d", &choice) == 1) {
                switch (choice) {
                case 0: return;
                case 1: if (page > 0) page--; break;
                case 2: if (page < totalPages - 1) page++; break;
                case 3:
                {
                    char newWord[50], newMeaning[50];
                    printf("请输入新单词: ");
                    fgets(newWord, sizeof(newWord), stdin);
                    newWord[strcspn(newWord, "\n")] = 0;
                    printf("请输入单词含义: ");
                    fgets(newMeaning, sizeof(newMeaning), stdin);
                    newMeaning[strcspn(newMeaning, "\n")] = 0;

                    // 检查单词是否已存在
                    int exists = 0;
                    for (int i = 0; i < count; i++) {
                        if (strcmp(words[i], newWord) == 0) {
							exists = 1; // 单词已存在
                            break;
                        }
                    }
                    if (exists) {
                        printf("该单词已存在，无法重复添加！\n");
                        system("pause");
						break; // 跳过添加单词
                    }

					fp = fopen("words.txt", "a"); // 追加模式打开单词文件
                    if (fp != NULL) {
						fprintf(fp, "%s\t%s\n", newWord, newMeaning); // 写入新单词和含义
                        fclose(fp);
                        printf("新单词已添加!\n");
                        // 重新加载单词列表
                        count = 0;
						fp = fopen("words.txt", "r"); // 重新打开文件读取
                        while (count < 300 && fscanf(fp, "%s\t%s", words[count], meanings[count]) == 2) {
							count++; // 重新读取单词数
                        }
                        fclose(fp);
                    }
                    else {
                        printf("无法打开单词文件!\n");
                    }
                    system("pause");
                } break;
                case 4: // 删除单词
                {
                    if (count == 0) {
                        printf("单词本为空，无可删除单词。\n");
                        system("pause");
                        break;
                    }
                    int delIdx;
                    printf("请输入要删除的单词序号: ");
                    fgets(input, sizeof(input), stdin);
                    if (sscanf(input, "%d", &delIdx) == 1 && delIdx >= 1 && delIdx <= count) {
                        delIdx--; // 转为下标
                        // 删除单词并重新排列
                        for (int i = delIdx; i < count - 1; i++) {
							strcpy(words[i], words[i + 1]); // 将后面的单词前移
							strcpy(meanings[i], meanings[i + 1]); // 将后面的含义前移
                        }
                        count--;
                        // 重新写入文件
                        fp = fopen("words.txt", "w");
                        if (fp != NULL) {
                            for (int i = 0; i < count; i++) {
                                fprintf(fp, "%s\t%s\n", words[i], meanings[i]);
                            }
                            fclose(fp);
                            printf("单词已删除!\n");
                        }
                        else {
                            printf("无法打开单词文件!\n");
                        }
                        system("pause");
                    }
                    else {
                        printf("输入无效。\n");
                        system("pause");
                    }
                }
                break;
                case 5: // 收藏单词
                {
                    int idx;
                    printf("请输入要收藏的单词序号: ");
                    fgets(input, sizeof(input), stdin);
                    if (sscanf(input, "%d", &idx) == 1 && idx >= 1 && idx <= count) {
                        char filename[100];
						snprintf(filename, sizeof(filename), "vocab_%s.txt", currentUser); // 用户名创建个人收藏本
                        FILE* fav = fopen(filename, "a");
                        if (fav != NULL) {
                            fprintf(fav, "%s\t%s\n", words[idx - 1], meanings[idx - 1]);
                            fclose(fav);
                            printf("单词已收藏到收藏本！\n");
                        }
                        else {
                            printf("无法打开收藏本文件！\n");
                        }
                    }
                    else {
                        printf("输入无效。\n");
                    }
                    system("pause");
                } break;
				// case 6 和 case 7 相当于进度功能，通过书签来保存和加载当前浏览的页数进度
                case 6:
                {
                    saveProgress();// 保存当前进度到文件
                    goto F1;
                }
                case 7:
                {
                    loadProgress();// 加载上次保存的进度
                    goto F1;
                }
                }
            }
        }
    }
}

//定义全局变量page，通过储存和读取page的值来实现书签功能
// 保存当前进度到文件
void saveProgress() {
    FILE* fp;
    if ((fp = fopen("bookmark.txt", "w")) == NULL) {
        printf("\n\nCannot open bookmark.txt file!\n");
        system("pause");
    }
    if ((fprintf(fp, "%d", page)) == NULL){
        printf("保存失败！(按任意键继续)");
        getch();
    }
    else {
        printf("保存成功！(按任意键继续)");
        getch();
    }
    fclose(fp);
}

// 加载上次保存的进度
void loadProgress() {
    FILE* fp;
    if ((fp = fopen("bookmark.txt", "r")) == NULL) {
        printf("\n\nCannot open bookmark.txt file!\n");
        system("pause");
    }
    if ((fscanf(fp, "%d", &page)) == NULL) {
        printf("\n书签不存在(按任意键继续)");
        getch();
    }
    fclose(fp);
}
//-----------------------------------------------------------------------------------------------

// 查询单词   Powerby 龙海峰
void searchWord() {
    char xz[8];
    system("cls");
    printf("\n\n                    0--退出");
    printf("\n\n                    1--英文查词");
    printf("\n\n                    2--中文查词");
    printf("\n\n\n                    请选择: (0, 1, 2): ");
    do {
        fgets(xz, 8, stdin);
    } while (xz[0] != '0' && xz[0] != '1' && xz[0] != '2' && xz[0] != '3');
    switch (xz[0]) {
    case '0': return;
    case '1': {
        char ch[50];   int find;    FILE* fp;
        Word x;      // 定义单词的结构体变量x
        if ((fp = fopen("words.txt", "r")) == NULL) {
            printf("\n\nCannot open words.txt file!\n");
            system("pause"); break;
        }
    F1: system("cls");
        printf("\n     Input English Word Which You Want To Know ");
        printf("\n==================================================");
        printf("\n English Word : ");    gets(ch);    // 输入一个单词到字符数组ch
        find = 0;
        rewind(fp);    // 复位到文件头
        fscanf(fp, "%s\t%s", x.english, x.chinese);   // 从词典中读取一个单词
        while (!feof(fp)) {
            if (strcmp(x.english, ch) == 0) {    // 如果在词典中找到了英文为ch的单词结构体
                printf("\n English:%s\n chinese:%s\n", x.english, x.chinese);    // 打印单词结构体成员
                find = 1;
                break;
            }
            fscanf(fp, "%s\t%s", x.english, x.chinese);  //循环读取
        }
        if (!find) {
            printf("\n对不起,未查询到您输入的单词 (ó﹏ò?)\n");
        }
        printf("==================================================");
        printf("\n\n\n   您还想继续查询单词吗？ (y/n)  ");
        do {
            fgets(ch, 50, stdin);
        } while (!(ch[0] == 'y' || ch[0] == 'n' || ch[0] == 'Y' || ch[0] == 'N'));
        if (ch[0] == 'y' || ch[0] == 'Y') goto F1;    // 实际上是构成循环
        else fclose(fp);
        break;
    }
    case '2': {
        char ch[50];   int find;    FILE* fp;
        Word x;      // 定义单词的结构体变量x
        if ((fp = fopen("words.txt", "r")) == NULL) {
            printf("\n\nCannot open words.txt file!\n");
            system("pause"); break;
        }
    F2: system("cls");
        printf("\n     Input Chinese Word Which You Want To Know ");
        printf("\n==================================================");
        printf("\n Chinese Word : ");    gets(ch);    // 输入一个学号到字符数组ch
        find = 0;
        rewind(fp);    // 复位到文件头
        fscanf(fp, "%s\t%s", x.english, x.chinese);   // 从词典中读取一个单词
        while (!feof(fp)) {
            if (strcmp(x.chinese, ch) == 0) {    // 如果在词典中找到了中文为ch的单词结构体
                printf("\n English:%-s\n chinese:%-s\n", x.english, x.chinese);    // 打印单词结构体成员
                find = 1;
                break;
            }
            fscanf(fp, "%s\t%s", x.english, x.chinese);    // 从学生文件中读取一个学生记录
        }
        if (!find) {
            printf("\n对不起,未查询到您输入的单词 (ó﹏ò?)\n");
        }
        printf("==================================================");
        printf("\n\n\n   您还想继续查询单词吗？ (y/n)  ");
        do {
            fgets(ch, 50, stdin);
        } while (!(ch[0] == 'y' || ch[0] == 'n' || ch[0] == 'Y' || ch[0] == 'N'));
        if (ch[0] == 'y' || ch[0] == 'Y') goto F2;    // 实际上是构成循环
        else fclose(fp);
        break;
    }
    }
}
//-----------------------------------------------------------------------------------------------

// 默写单词   Powerby 李俊超
void selfStudy() {
    char choice[10];  // 存储用户输入的选择

    while (1) {
        system("cls");  // 清屏
        // 显示菜单界面
        printf("\n\n\t\t\t===== 英语单词测试系统 =====\n");
        printf("\t=======================================================\n");
        printf("\n\t\t\t请选择测试模式：\n\n");
        printf("\t\t1. 英文单词 -> 中文释义 (English to Chinese)\n");
        printf("\t\t2. 中文释义 -> 英文单词 (Chinese to English)\n");
        printf("\n\t\t0. 退出系统 (Exit)\n");
        printf("\n\t\t--------------------------------------------\n");
        printf("\t\t提示：输入对应数字并按Enter键确认选择\n");
        printf("\t=======================================================\n");

        // 获取用户选择
        printf("\n\t\t请选择 (0-2): ");
        if (fgets(choice, sizeof(choice), stdin) != NULL) {
            choice[strcspn(choice, "\n")] = 0;  // 移除换行符

            // 验证输入是否为有效数字
            int ch;
            if (sscanf(choice, "%d", &ch) == 1) {
                switch (ch) {
                case 0:
                    exitTest();
                    return 0;
                case 1:
                    testWordsEtoC();
                    break;
                case 2:
                    testWordsCtoE();
                    break;
                default:
                    printf("\n\t输入无效，请选择0-2之间的数字！\n");
                    getch();  // 暂停查看提示
                    break;
                }
            }
            else {
                printf("\n\t请输入有效的数字！\n");
                getch();  // 暂停查看提示
            }
        }
    }
}

void testWordsCtoE() {
    Word words[300], learnedwords[300];
    int count = 0;         // 单词库总数
    int score = 0;         // 正确题数
    int total = 0;         // 总测试题数
    int learned = 0;       // 已学习单词数
    int current = 0;       // 当前单词索引
    char userAnswer[200];  // 用户输入的答案
    clock_t startTime, endTime;
    double totalTime = 0.0;

    FILE* fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printf("无法打开单词文件!\n");
        getch();
        return;
    }
    while (fscanf(fp, "%s\t%s", words[count].english, words[count].chinese) != EOF && count < 300) {
        count++;
    }
    fclose(fp);

    // 加载已学习单词
    FILE* fp1 = fopen("learnedwords.txt", "r+");
    if (fp1 == NULL) {
        fp1 = fopen("learnedwords.txt", "w");
        if (fp1 == NULL) {
            printf("无法创建已学习单词文件!\n");
            getch();
            return;
        }
        fclose(fp1);
        fp1 = fopen("learnedwords.txt", "r+");
    }

    while (fscanf(fp1, "%s\t%s", learnedwords[learned].english, learnedwords[learned].chinese) != EOF && learned < 300) {
        learned++;
    }
    fclose(fp1);

    if (count == 0) {
        printf("单词库为空，无法进行测试!\n");
        getch();
        return;
    }

    srand(time(NULL));
    startTime = clock();
    system("cls");
    printf("\n\n\t=============== 单词学习开始 ===============\n");
    printf("\t\t根据中文输入对应的英文单词\n");
    printf("\t\t按ESC键随时退出学习\n");
    printf("\t\t按L键设置已掌握单词\n\n");

    while (1) {
        // 查找未学习的单词
        while (current < count) {
            int isLearned = 0;
            for (int j = 0; j < learned; j++) {
                if (strcmp(words[current].chinese, learnedwords[j].chinese) == 0) {
                    isLearned = 1;
                    current++;
                    break;
                }
            }
            if (!isLearned) {
                break;
            }

        }

        // 检查是否所有单词都已学习
        if (current >= count) {
            printf("\n\n\t所有单词已学习完毕!\n");
            break;
        }

        total++;
        printf("\n第 %d 题: 请输入 \"%s\" 对应的英文单词: ", total, words[current].chinese);

        int ch;
        int i = 0;
        while ((ch = getch()) != '\r') {
            if (ch == 27) { // ESC键
                printf("\n\n\t用户选择退出学习...\n");
                goto exitTest;
            }

            if (ch == '\b' && i > 0) {
                i--;
                printf("\b \b");
                continue;
            }

            if (ch == 'L' || ch == 'l') {
                if (learned < 300) {
                    strcpy(learnedwords[learned].english, words[current].english);
                    strcpy(learnedwords[learned].chinese, words[current].chinese);
                    learned++;


                }
                printf("\n已将该单词标记为已掌握\n");
                printf("已记住 %d 个单词\n", learned);
                break;
            }

            if (i < sizeof(userAnswer) - 1) {
                userAnswer[i++] = ch;
                putchar(ch);
            }
        }
        userAnswer[i] = '\0'; // 字符串结束符

        if (strcmp(userAnswer, words[current].english) == 0) {
            printf("\n回答正确! 恭喜获得1分\n");
            score++;
        }
        else if (ch == 'L' || ch == 'l') {
            current++;
            score++;
        }
        else {
            printf("\n回答错误! 正确答案是: %s\n", words[current].english);
        }

        current++;

        // 按Enter继续，ESC退出
        printf("\n按Enter键继续测试，按ESC键退出: ");
        while (1) {
            ch = getch();
            if (ch == 27) { // ESC键
                printf("\n用户选择退出测试...\n");
                goto exitTest;
            }
            if (ch == '\r') { // Enter键
                printf("\n");
                break;
            }
        }
    }

exitTest:
    // 保存已学习单词
    fp1 = fopen("learnedwords.txt", "w");
    if (fp1 == NULL) {
        printf("无法打开已学习单词文件!\n");
        getch();
        return;
    }
    for (int i = 0; i < learned; i++) {
        fprintf(fp1, "%s\t%s\n", learnedwords[i].english, learnedwords[i].chinese);
    }
    fclose(fp1);

    // 计算并显示统计信息
    endTime = clock();
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	system("cls");
    printf("\n\n\t=============== 单词学习结束 ===============\n");
    printf("\t总题数: %d\n", total);
    printf("\t正确数: %d\n", score);
    printf("\t正确率: %.1f%%\n", total > 0 ? (float)score / total * 100 : 0);
    printf("\t总用时: %.2f秒\n", totalTime);
    if (total > 0) {
        printf("\t平均每题用时: %.2f 秒\n", totalTime / total);
    }
    printf("\t按任意键返回主菜单...\n");
    getch();
}

void testWordsEtoC() {
    Word words[300], learnedwords[300];
    int count = 0;         // 单词库总数
    int score = 0;         // 正确题数
    int total = 0;         // 总测试题数
    int learned = 0;       // 已学习单词数
    int current = 0;       // 当前单词索引
    char userAnswer[200];  // 用户输入的答案
    clock_t startTime, endTime;
    double totalTime = 0.0;

    FILE* fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printf("无法打开单词文件!\n");
        getch();
        return;
    }
    while (fscanf(fp, "%s\t%s", words[count].english, words[count].chinese) != EOF && count < 300) {
        count++;
    }
    fclose(fp);

    // 加载已学习单词
    FILE* fp1 = fopen("learnedwords.txt", "r+");
    if (fp1 == NULL) {
        fp1 = fopen("learnedwords.txt", "w");
        if (fp1 == NULL) {
            printf("无法创建已学习单词文件!\n");
            getch();
            return;
        }
        fclose(fp1);
        fp1 = fopen("learnedwords.txt", "r+");
    }

    while (fscanf(fp1, "%s\t%s", learnedwords[learned].english, learnedwords[learned].chinese) != EOF && learned < 300) {
        learned++;
    }
    fclose(fp1);

    if (count == 0) {
        printf("单词库为空，无法进行测试!\n");
        getch();
        return;
    }

    srand(time(NULL));
    startTime = clock();
    system("cls");
    printf("\n\n\t=============== 单词学习开始 ===============\n");
    printf("\t\t根据英文输入对应的中文\n");
    printf("\t\t按ESC键随时退出测试\n");
    printf("\t\t按L键设置已掌握单词\n\n");

    while (1) {
        // 查找未学习的单词
        while (current < count) {
            int isLearned = 0;
            for (int j = 0; j < learned; j++) {
                if (strcmp(words[current].english, learnedwords[j].english) == 0) {
                    isLearned = 1;
                    current++;
                    break;
                }
            }
            if (!isLearned) {
                break;
            }

        }

        // 检查是否所有单词都已学习
        if (current >= count) {
            printf("\n\n\t所有单词已学习完毕!\n");
            break;
        }

        total++;
        printf("\n第 %d 题: 请输入 \"%s\" 对应的中文释义: ", total, words[current].english);

        int ch;
        int i = 0;
        while ((ch = getch()) != '\r') {
            if (ch == 27) { // ESC键
                printf("\n\n\t用户选择退出测试...\n");
                goto exitTest;
            }

            if (ch == '\b' && i > 0) { // 退格键
                i--;
                printf("\b \b");
                continue;
            }

            if (ch == 'L' || ch == 'l') { // 标记为已学习
                if (learned < 300) {
                    strcpy(learnedwords[learned].english, words[current].english);
                    strcpy(learnedwords[learned].chinese, words[current].chinese);
                    learned++;
                }
                printf("\n已将该单词标记为已掌握\n");
                printf("已记住 %d 个单词\n", learned);
                break;
            }

            if (i < sizeof(userAnswer) - 1) {
                userAnswer[i++] = ch;
                putchar(ch);
            }
        }
        userAnswer[i] = '\0'; // 字符串结束符

        if (strcmp(userAnswer, words[current].chinese) == 0) {
            printf("\n回答正确! 恭喜获得1分\n");
            score++;
        }
        else if (ch == 'L' || ch == 'l') {
            current++;
            score++;
        }
        else {
            printf("\n回答错误! 正确答案是: %s\n", words[current].chinese);
        }

        current++;

        // 按Enter继续，ESC退出
        printf("\n按Enter键继续测试，按ESC键退出: ");
        while (1) {
            ch = getch();
            if (ch == 27) { // ESC键
                printf("\n用户选择退出测试...\n");
                goto exitTest;
            }
            if (ch == '\r') { // Enter键
                printf("\n");
                break;
            }
        }
    }

exitTest:
    // 保存已学习单词
    fp1 = fopen("learnedwords.txt", "w");
    if (fp1 == NULL) {
        printf("无法打开已学习单词文件!\n");
        getch();
        return;
    }
    for (int i = 0; i < learned; i++) {
        fprintf(fp1, "%s\t%s\n", learnedwords[i].english, learnedwords[i].chinese);
    }
    fclose(fp1);

    // 计算并显示统计信息
    endTime = clock();
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	system("cls");
    printf("\n\n\t=============== 单词学习结束 ===============\n");
    printf("\t总题数: %d\n", total);
    printf("\t正确数: %d\n", score);
    printf("\t正确率: %.1f%%\n", total > 0 ? (float)score / total * 100 : 0);
    printf("\t总用时: %.2f秒\n", totalTime);
    if (total > 0) {
        printf("\t平均每题用时: %.2f 秒\n", totalTime / total);
    }
    printf("\t按任意键返回主菜单...\n");
    getch();
}

void exitTest() {
    system("cls");
    printf("\n\n\t\t今天默写做得不错,下次再接再厉哦！~^o^~\n");
    printf("\n\t\t按任意键退出...");
    getch();
}
//-----------------------------------------------------------------------------------------------

// 单词收藏本   Powerby 潘钰楷
void vocabularyBook() {
    FILE* fp;
    char filename[100];
	snprintf(filename, sizeof(filename), "vocab_%s.txt", currentUser); // 使用当前用户名创建个人收藏本
    char words[100][50];
    char meanings[100][50];
    int count = 0;

    // 如果文件不存在则新建
    fp = fopen(filename, "a+");
    if (fp == NULL) {
        printf("无法创建或打开收藏本文件!\n");
        return;
    }
    fclose(fp);

reload:
    // 读取单词
    count = 0;
    fp = fopen(filename, "r");
    while (fp && fscanf(fp, "%s\t%s", words[count], meanings[count]) != EOF && count < 100) {
        count++;
    }
    if (fp) fclose(fp);

    int page = 0;
    int wordsPerPage = 5;
    int totalPages = (count + wordsPerPage - 1) / wordsPerPage;

    while (1) {
        system("cls");
        printf("\n\t\t\t单词收藏本 (第%d页/共%d页, 共%d个单词)\n\n", page + 1, totalPages > 0 ? totalPages : 1, count);

        // 显示当前页单词
        for (int i = page * wordsPerPage; i < (page + 1) * wordsPerPage && i < count; i++) {
            printf(" %d. %s - %s\n", i + 1, words[i], meanings[i]);
        }

        printf("\n\n 0:关闭收藏本   1:上一页   2:下一页   3:新增单词   4:移除单词   5:初始化\n");
        printf("\n 请选择操作: ");

        int choice;
        char input[10];
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%d", &choice) == 1) {
                switch (choice) {
                case 0:
                    return;
                case 1:
                    if (page > 0) page--;
                    break;
                case 2:
                    if (page < totalPages - 1) page++;
                    break;
                case 3: {
                    char newWord[50], newMeaning[50];
                    printf("请输入新单词: ");
                    fgets(newWord, sizeof(newWord), stdin);
                    newWord[strcspn(newWord, "\n")] = 0;
                    printf("请输入单词含义: ");
                    fgets(newMeaning, sizeof(newMeaning), stdin);
                    newMeaning[strcspn(newMeaning, "\n")] = 0;

                    // 检查单词是否已存在
                    int exists = 0;
                    for (int i = 0; i < count; i++) {
                        if (strcmp(words[i], newWord) == 0) {
                            exists = 1;
                            break;
                        }
                    }
                    if (exists) {
                        printf("该单词已存在，无法重复添加！\n");
                        system("pause");
                        break;
                    }

                    fp = fopen(filename, "a");
                    if (fp != NULL) {
                        fprintf(fp, "%s\t%s\n", newWord, newMeaning);
                        fclose(fp);
                        printf("新单词已添加!\n");
                        system("pause");
                        goto reload;
                    } else {
                        printf("无法打开收藏本文件!\n");
                        system("pause");
                    }
                    break;
                }
                case 4: {
                    if (count == 0) {
                        printf("收藏本为空，无可移除单词。\n");
                        system("pause");
                        break;
                    }
                    int delIdx;
                    printf("请输入要移除的单词序号: ");
                    fgets(input, sizeof(input), stdin);
                    if (sscanf(input, "%d", &delIdx) == 1 && delIdx >= 1 && delIdx <= count) {
                        delIdx--; // 转为下标
                        // 移除单词
                        for (int i = delIdx; i < count - 1; i++) {
                            strcpy(words[i], words[i + 1]);
                            strcpy(meanings[i], meanings[i + 1]);
                        }
                        count--;
                        // 重新写入文件
                        fp = fopen(filename, "w");
                        for (int i = 0; i < count; i++) {
                            fprintf(fp, "%s\t%s\n", words[i], meanings[i]);
                        }
                        fclose(fp);
                        printf("单词已移除!\n");
                        system("pause");
                        goto reload;
                    } else {
                        printf("输入无效。\n");
                        system("pause");
                    }
                    break;
                }
                case 5: {
                    printf("\n确定要初始化收藏本吗？此操作会清空所有收藏单词！(y/n): ");
                    fgets(input, sizeof(input), stdin);
                    if (input[0] == 'y' || input[0] == 'Y') {
						fp = fopen(filename, "w"); // 清空文件内容
                        if (fp) fclose(fp);
                        printf("收藏本已初始化！\n");
                        system("pause");
                        goto reload;
                    }
                    break;
                }
                }
            }
        }
    }
}
//-----------------------------------------------------------------------------------------------

// 错题再练   Powerby 龙海峰
void enhanceMemory() { //对于错误次数越多的单词，在背单词的时候出现次数越多
    test t[300];
    test transmit;
    int i;     //sum是抽查的题目总数，i是有记录的背错单词数量
    int j, k;
    int mistake1[300];//该变量只服务于随机数，没有实际意义
F1:srand((unsigned)time(NULL));
    i = 0;
    FILE* fp;
    if ((fp = fopen("errorwords.txt", "r")) == NULL) {
        printf("不能打开错误统计文集！");
        system("pause");
    }
    while (!feof(fp)) {
        fscanf(fp, "%s\t%s\t%d", t[i].english, t[i].chinese, &t[i].errornumber);//从文件中读取错词内容以及背错次数
        i++;
    }
    //利用冒泡排序法将错误次数较多的单词移至结构体数组靠前位置
    for (j = 1; j < i; j++) {        //对j个数进行j-1次排序
        for (k = 0; k <= i - 1 - j; k++) {    //第j次排序后，t[i-1-j].errornumber排序到位
            if (t[k].errornumber < t[k + 1].errornumber) {  //降序排位：将较大错误次数的单词调到前面
                transmit = t[k];
                t[k] = t[k + 1];
                t[k + 1] = transmit;
            }
        }
    }
    for (j = 0; j <= i - 1; j++) {
        mistake1[j] = rand() % (j + 1);    //数组中越靠前的单词的位子越容易被随机数抽到
    }
    for (j = 0; j <= i - 1; j++) {   //将结构体中mistake2成员赋值为0；
        t[j].mistake2 = 0;
    }
    for (j = 0; j <= i - 1; j++) {       //统计各个随机数出现的次数
        for (k = 0; k <= i - 1; k++) {
            if (mistake1[k] == j) {
                t[j].mistake2++;
            }
        }
    }
    //利用冒泡排序法将被随机数选中较多次数的单词移至结构体数组靠前位置
    for (j = 1; j < i; j++) {        //对j个数进行j-1次排序
        for (k = 0; k <= i - 1 - j; k++) {    //第j次排序后，t[i-1-j].errornumber排序到位
            if (t[k].mistake2 < t[k + 1].mistake2) {  //降序排位：将随机数选中较多次数的单词调到前面
                transmit = t[k];
                t[k] = t[k + 1];
                t[k + 1] = transmit;
            }
        }
    }
    fclose(fp);

    //测试页面设计
    char xz[8]; int total = 0;
    printf("                 错题再练               \n");
    printf("=============================================\n");
    printf("              请选择学习模式：\n");
    printf("       1. 英文单词 → 中文释义 (选释义)\n");
    printf("       2. 中文释义 → 英文单词 (选单词)\n");
    printf("           0. 退出 (Exit)\n");
    printf("---------------------------------------------\n");
    printf("      提示：输入对应数字并按Enter键确认选择\n");
    printf("=============================================\n");
    while (1) {
        fgets(xz, 8, stdin);
        if (xz[0] >= 48 && xz[0] <= 57) {
            break;
        }
    }
    system("cls");
    switch (xz[0]) {
    case '0':return 0;
    case '1': {
        Option options[4];
        for (j = 1; j <= 10; j++) {
            generateOptions1(options, t[j - 1], 1);
            printf("根据英文单词选出对应的中文（共10题）\n");
            printf("第 %d 题：%s\n", j, t[j - 1].english);
            printf("--------------------------------------------\n");
            printf("     A,%s\n", options[0].option);
            printf("     B,%s\n", options[1].option);
            printf("     C,%s\n", options[2].option);
            printf("     D,%s\n", options[3].option);
            printf("--------------------------------------------\n");
            printf("请选择（A-D）：");
            while (1) {
                fgets(xz, 8, stdin);
                if (xz[0] >= 'A' && xz[0] <= 'D') {
                    break;
                }
            }

            if (options[xz[0] - 'A'].isCorrect) {
                total++;
                printf("回答正确，正确答案是:%s(按任意键继续)", t[j - 1].chinese);
                getch();
            }
            else {
                printf("回答错误，正确答案是:%s(按任意键继续)", t[j - 1].chinese);
                getch();
            }
            system("cls");
        }
        printf("\n\n\n\t测试结束！\n\n");
        printf("\t你成功答对了%d道题\n\n", total);
        printf("\n\t是否需要再次测验（y/n）？");
        while (1) {
            fgets(xz, 8, stdin);
            if (xz[0] == 'y' || xz[0] == 'Y' || xz[0] == 'n' || xz[0] == 'N') {
                break;
            }
        }
        if (xz[0] == 'y' || xz[0] == 'Y') {
            system("cls");
            goto F1;
            break;
        }
        else {
            system("cls");
            break;
        }
    }
    case '2': {
        Option options[4];
        for (j = 1; j <= 10; j++) {
            generateOptions1(options, t[j - 1], 2);
            printf("根据中文选出对应的英文单词（共10题）\n");
            printf("第 %d 题：%s\n", j, t[j - 1].chinese);
            printf("--------------------------------------------\n");
            printf("     A,%s\n", options[0].option);
            printf("     B,%s\n", options[1].option);
            printf("     C,%s\n", options[2].option);
            printf("     D,%s\n", options[3].option);
            printf("--------------------------------------------\n");
            printf("请选择（A-D）：");
            while (1) {
                fgets(xz, 8, stdin);
                if (xz[0] >= 'A' && xz[0] <= 'D') {
                    break;
                }
            }
            
            if (options[xz[0] - 'A'].isCorrect) {
                total++;
                printf("回答正确，正确答案是:%s(按任意键继续)", t[j - 1].english);
                getch();
            }
            else {
                printf("回答错误，正确答案是:%s(按任意键继续)", t[j - 1].english);
                getch();
            }
            system("cls");
        }
        printf("\n\n\n\t测试结束！\n\n");
        printf("\t你成功答对了%d道题\n\n", total);
        printf("\n\t是否需要再次测验（y/n）？");
        while (1) {
            fgets(xz, 8, stdin);
            if (xz[0] == 'y' || xz[0] == 'Y' || xz[0] == 'n' || xz[0] == 'N') {
                break;
            }
        }
        if (xz[0] == 'y' || xz[0] == 'Y') {
            system("cls");
            goto F1;
            break;
        }
        else {
            system("cls");
            break;
        }
    }
    }
}

void generateOptions1(Option options[], test word, int mode) {
    Word words[300];
    int count = 0;
    FILE* fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printf("无法打开单词文件!\n");
        getch();
        return 0;
    }

    while (fscanf(fp, "%s\t%s", words[count].english, words[count].chinese) != EOF && count < 100) {
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("单词库为空，无法进行学习!\n");
        getch();
    }
    if (count <= 1) return; // 至少需要2个单词才能生成错误选项

    if (mode == 1) {
        // 设置正确选项
        strcpy(options[0].option, word.chinese);
        options[0].isCorrect = 1;

        for (int i = 1; i < 4; i++) {
            int randIndex;
            do {
                randIndex = rand() % count;
            } while (strcmp(words[randIndex].english, word.english) == 0); // 避免选到同一单词
            strcpy(options[i].option, words[randIndex].chinese);
            options[i].isCorrect = 0;
        }
    }

    else {
        // 设置正确选项
        strcpy(options[0].option, word.english);
        options[0].isCorrect = 1;

        // 生成3个错误选项
        for (int i = 1; i < 4; i++) {
            int randIndex;
            do {
                randIndex = rand() % count;
            } while (strcmp(words[randIndex].chinese, word.chinese) == 0); // 避免选到同一单词
            strcpy(options[i].option, words[randIndex].english);
            options[i].isCorrect = 0;
        }
    }

    // 随机打乱选项顺序
    for (int i = 0; i < 4; i++) {
        int j = rand() % 4;
        Option temp = options[i];
        options[i] = options[j];
        options[j] = temp;
    }
}
//-----------------------------------------------------------------------------------------------

// 单词测验   Powerby 李俊超
void selfTest() {
    char choice[10];  // 存储用户输入的选择

    while (1) {
        system("cls");

        // 显示菜单界面
        printf("\n\n\t\t\t===== 英语单词背诵 =====\n");
        printf("\t=======================================================\n");
        printf("\n\t\t\t请选择学习模式：\n\n");
        printf("\t\t1. 英文单词 → 中文释义 (选释义)\n");
        printf("\t\t2. 中文释义 → 英文单词 (选单词)\n");
        printf("\n\t\t0. 退出系统 (Exit)\n");
        printf("\n\t\t--------------------------------------------\n");
        printf("\t\t提示：输入对应数字并按Enter键确认选择\n");
        printf("\t=======================================================\n");

        // 获取用户选择
        printf("\n\t\t请选择 (0-2): ");
        if (fgets(choice, sizeof(choice), stdin) != NULL) {
            choice[strcspn(choice, "\n")] = 0;

            // 验证输入是否为有效数字
            int ch;
            if (sscanf(choice, "%d", &ch) == 1) {
                switch (ch) {
                case 0:
                    exitStudyProgram();
                    return;
                case 1:
                    learnWordsEtoC();
                    break;
                case 2:
                    learnWordsCtoE();
                    break;
                default:
                    printf("\n\t输入无效，请选择0-2之间的数字！\n");
                    getch();
                    break;
                }
            }
            else {
                printf("\n\t请输入有效的数字！\n");
                getch();
            }
        }
    }
}

void generateOptions(Option options[], Word word, int mode) {
    Word words[300];
    int count = 0;
    FILE* fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printf("无法打开单词文件!\n");
        getch();
        return 0;
    }

    while (fscanf(fp, "%s\t%s", words[count].english, words[count].chinese) != EOF && count < 100) {
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("单词库为空，无法进行学习!\n");
        getch();
    }

    if (count <= 1) return; // 至少需要2个单词才能生成错误选项

    if (mode == 1) {
        // 设置正确选项
        strcpy(options[0].option, word.chinese);
        options[0].isCorrect = 1;

        for (int i = 1; i < 4; i++) {
            int randIndex;
            do {
                randIndex = rand() % count;
            } while (strcmp(words[randIndex].english, word.english) == 0); // 避免选到同一单词
            strcpy(options[i].option, words[randIndex].chinese);
            options[i].isCorrect = 0;
        }
    }

    else {
        // 设置正确选项
        strcpy(options[0].option, word.english);
        options[0].isCorrect = 1;

        // 生成3个错误选项
        for (int i = 1; i < 4; i++) {
            int randIndex;
            do {
                randIndex = rand() % count;
            } while (strcmp(words[randIndex].chinese, word.chinese) == 0); // 避免选到同一单词
            strcpy(options[i].option, words[randIndex].english);
            options[i].isCorrect = 0;
        }
    }

    // 随机打乱选项顺序
    for (int i = 0; i < 4; i++) {
        int j = rand() % 4;
        Option temp = options[i];
        options[i] = options[j];
        options[j] = temp;
    }
}

void learnWordsEtoC() {
    Word words[300];             // 单词结构体数组
    errorwords errorwords[300], error[300];  // 临时错误单词数组
    FILE* fp1;

    int count = 0;              // 单词库数量
    int errorcount = 0;         // 本次学习中错误单词数量
    int errorFileCount = 0;     // 错误单词文件中的数量

    FILE* fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printf("无法打开单词文件!\n");
        getch();
        return;
    }

    while (fscanf(fp, "%49s\t%199s", words[count].english, words[count].chinese) != EOF && count < 300) {
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("单词库为空，无法进行学习!\n");
        getch();
        return;
    }

    int score = 0;
    int total = 0;
    char userChoice;              // 用户选择的选项
    clock_t startTime, endTime;   // 计时变量
    double totalTime = 0.0;       // 总时间

    srand(time(NULL));            // 初始化随机数种子
    startTime = clock();          // 开始计时
    system("cls");
    printf("\n\n\t=============== 背单词模式开始 ===============\n");
    printf("\t\t根据英文单词选择正确的中文释义\n");
    printf("\t\t选项：A/B/C/D，按ESC键随时退出\n");
    printf("\n");

    while (1) {
        if (total >= count) {
            printf("\n\n所有单词已学习完毕!\n");
            break;
        }

        int randIndex = rand() % count;
        total++;

        Option options[4];          // 4个选项
        generateOptions(options, words[randIndex], 1);  // 生成选项
        system("cls");
        printf("\n第 %d 题: 单词 \"%s\" 的中文释义是？\n", total, words[randIndex].english);
        printf("------------------------------------\n");

        // 显示4个选项
        for (int i = 0; i < 4; i++) {
            printf("    %c. %s\n", 'A' + i, options[i].option);
        }
        printf("------------------------------------\n");
        printf("请选择 (A-D): ");

        // 读取用户选择
        while (1) {
            int ch = getch();
            if (ch == 27) {         // ESC键
                endTime = clock();
                totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
                printf("\n\n用户选择退出学习...\n");
                goto exitLearn;
            }

            if (ch >= 'A' && ch <= 'D' || ch >= 'a' && ch <= 'd') {
                userChoice = toupper(ch);
                printf("%c\n", userChoice);
                break;
            }
            else {
                printf("\n请输入A-D之间的选项: ");
            }
        }

        // 判断选择是否正确
        int choiceIndex = userChoice - 'A';
        if (options[choiceIndex].isCorrect) {
            printf("\n选择正确! 恭喜获得1分\n");
            score++;
        }
        else {
            printf("\n选择错误! 正确选项是: ");
            for (int i = 0; i < 4; i++) {
                if (options[i].isCorrect) {
                    // 记录错误单词
                    strcpy(errorwords[errorcount].chinese, options[i].option);
                    strcpy(errorwords[errorcount].english, words[randIndex].english);
                    errorwords[errorcount].errorcount = 1;
                    errorcount++;
                    printf("%c. %s\n", 'A' + i, options[i].option);
                    break;
                }
            }
        }

        // 按Enter继续
        printf("\n按Enter键继续学习，按ESC键退出: ");
        while (1) {
            int ch = getch();
            if (ch == 27) {     // ESC键
                endTime = clock();
                totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
                printf("\n用户选择退出学习...\n");
                goto exitLearn;
            }
            if (ch == '\r') {    // Enter键
                printf("\n");
                break;
            }
        }
    }

    endTime = clock();              // 结束计时
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC; // 计算总时间

exitLearn:
    // 处理错误单词文件
    fp1 = fopen("errorwords.txt", "r+");
    if (fp1 == NULL) {
        fp1 = fopen("errorwords.txt", "w");
        if (fp1 == NULL) {
            printf("无法创建错误单词文件!\n");
            getch();
            return;
        }
        fclose(fp1);
        fp1 = fopen("errorwords.txt", "r+");
    }

    // 读取现有错误单词
    while (fscanf(fp1, "%49s\t%199s\t%d\n", error[errorFileCount].english, error[errorFileCount].chinese, &error[errorFileCount].errorcount) != EOF && errorFileCount < 300) {
        errorFileCount++;
    }

    // 检查并更新错误单词
    for (int i = 0; i < errorcount; i++) {
        int found = 0;
        for (int j = 0; j < errorFileCount; j++) {
            if (strcmp(error[j].english, errorwords[i].english) == 0) {
                error[j].errorcount++;
                found = 1;
                break;
            }
        }
        // 添加新的错误单词
        if (!found && errorFileCount < 300) {
            error[errorFileCount] = errorwords[i];
            errorFileCount++;
        }
    }

    // 重新写入错误单词文件
    fseek(fp1, 0, SEEK_SET);

    for (int i = 0; i < errorFileCount; i++) {
        fprintf(fp1, "%s\t%s\t%d\n", error[i].english, error[i].chinese, error[i].errorcount);
    }
    fclose(fp1);

    system("cls");
    printf("\n\n\t=============== 背单词模式结束 ===============\n");
    printf("\t总题数: %d\n", total);
    printf("\t正确数: %d\n", total > 0 ? score : 0);
    printf("\t正确率: %.1f%%\n", total > 0 ? (float)score / total * 100 : 0);
    printf("\t总用时: %.2f 秒\n", totalTime);
    if (total > 0) {
        printf("\t平均每题用时: %.2f 秒\n", totalTime / total);
    }
    printf("\n\n\t按任意键返回主菜单...\n");
    getch();
}

void learnWordsCtoE() {
    Word words[300];
    errorwords errorwords[300], error[300];  // 临时错误单词数组// 单词结构体数组
    int count = 0;
    int errorcount = 0;         // 本次学习中错误单词数量
    int errorFileCount = 0;
    FILE* fp1;
    FILE* fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printf("无法打开单词文件!\n");
        getch();
        return 0;
    }

    while (fscanf(fp, "%s\t%s", words[count].english, words[count].chinese) != EOF && count < 100) {
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("单词库为空，无法进行学习!\n");
        getch();
    }
    if (count == 0) return;

    int score = 0;
    int total = 0;
    char userChoice;      // 用户选择的选项
    clock_t startTime, endTime; // 计时变量
    double totalTime = 0.0;    // 总时间

    srand(time(NULL)); // 初始化随机数种子
    startTime = clock(); // 开始计时
    system("cls");
    printf("\n\n\t=============== 背单词模式开始 ===============\n");
    printf("\t\t根据中文释义选择正确的英文单词\n");
    printf("\t\t选项：A/B/C/D，按ESC键随时退出\n");
    printf("\t\t当前时间: %s", ctime(&startTime)); // 显示开始时间
    printf("\n");

    while (1) {
        if (total >= count) {
            printf("\n\n所有单词已学习完毕!\n");
            break;
        }

        // 生成随机单词索引
        int randIndex = rand() % count;
        total++;

        Option options[4]; // 4个选项
        generateOptions(options, words[randIndex], 2);
        system("cls");
        printf("\n第 %d 题: 释义 \"%s\" 对应的英文单词是？\n", total, words[randIndex].chinese);
        printf("------------------------------------\n");

        // 显示4个选项
        for (int i = 0; i < 4; i++) {
            printf("    %c. %s\n", 'A' + i, options[i].option);
        }
        printf("------------------------------------\n");
        printf("请选择 (A-D): ");

        while (1) {
            int ch = getch();
            if (ch == 27) { // ESC键
                endTime = clock(); // 结束计时
                totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
                printf("\n\n用户选择退出学习...\n");
                goto exitLearn;
            }

            if (ch >= 'A' && ch <= 'D' || ch >= 'a' && ch <= 'd') {
                userChoice = toupper(ch);
                printf("%c\n", userChoice);
                break;
            }
            else {
                printf("\n请输入A-D之间的选项: ");
            }
        }

        // 判断选择是否正确
        int choiceIndex = userChoice - 'A';
        if (options[choiceIndex].isCorrect) {
            printf("\n选择正确! 恭喜获得1分\n");
            score++;
        }
        else {
            printf("\n选择错误! 正确选项是: ");
            for (int i = 0; i < 4; i++) {
                if (options[i].isCorrect) {
                    strcpy(errorwords[errorcount].english, options[i].option);
                    strcpy(errorwords[errorcount].chinese, words[randIndex].chinese);
                    errorwords[errorcount].errorcount = 1;
                    errorcount++;
                    printf("%c. %s\n", 'A' + i, options[i].option);
                    break;
                }
            }
        }

        // 按Enter继续，ESC退出
        printf("\n按Enter键继续学习，按ESC键退出: ");
        while (1) {
            int ch = getch();
            if (ch == 27) {
                endTime = clock();
                totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
                printf("\n用户选择退出学习...\n");
                goto exitLearn;
            }
            if (ch == '\r') {
                printf("\n");
                break;
            }
        }
    }

    endTime = clock();
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC; // 计算总时间

exitLearn:
    // 处理错误单词文件
    fp1 = fopen("errorwords.txt", "r+");
    if (fp1 == NULL) {

        fp1 = fopen("errorwords.txt", "w");
        if (fp1 == NULL) {
            printf("无法创建错误单词文件!\n");
            getch();
            return;
        }
        fclose(fp1);
        fp1 = fopen("errorwords.txt", "r+");
    }

    // 读取现有错误单词
    while (fscanf(fp1, "%49s\t%199s\t%d\n", error[errorFileCount].english, error[errorFileCount].chinese, &error[errorFileCount].errorcount) != EOF && errorFileCount < 300) {
        errorFileCount++;
    }

    // 检查并更新错误单词
    for (int i = 0; i < errorcount; i++) {
        int found = 0;
        for (int j = 0; j < errorFileCount; j++) {
            if (strcmp(error[j].english, errorwords[i].english) == 0) {
                error[j].errorcount++;
                found = 1;
                break;
            }
        }
        // 添加新的错误单词
        if (!found && errorFileCount < 300) {
            error[errorFileCount] = errorwords[i];
            errorFileCount++;
        }
    }

    // 重新写入错误单词文件
    fseek(fp1, 0, SEEK_SET);

    for (int i = 0; i < errorFileCount; i++) {
        fprintf(fp1, "%s\t%s\t%d\n", error[i].english, error[i].chinese, error[i].errorcount);
    }
    fclose(fp1);
    system("cls");
    system("color 07");
    printf("\n\n\t=============== 背单词模式结束 ===============\n");
    printf("\t总题数: %d\n", total);
    printf("\t正确数: %d\n", total > 0 ? score : 0);
    printf("\t正确率: %.1f%%\n", total > 0 ? (float)score / total * 100 : 0);
    printf("\t总用时: %.2f 秒\n", totalTime);
    if (total > 0) {
        printf("\t平均每题用时: %.2f 秒\n", totalTime / total);
    }
    printf("\t按任意键返回主菜单...\n");
    getch();
}

void exitStudyProgram() {
    system("cls");
    printf("\n\n\t\t今天做得很好！再接再厉哦！  (^ρ^)/\n");
    printf("\t\t按任意键退出...\n\n");
    getch();
}
//-----------------------------------------------------------------------------------------------

// 退出程序   Powerby 潘钰楷
void exitProgram() {
    system("cls");
    printf("\n\n\n\t\t感谢您使用我们的英语电子词典!\n\n\t\t期待与您的再次相遇！  =^_^=");
    printf("\n\n\t\t按任意键退出...\n\n\n");
    getch(); // 等待用户按键
}