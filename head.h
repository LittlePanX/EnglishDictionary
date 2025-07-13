#pragma once

#define MAX_USER 100    // ����û���
#define MAX_NAME 50     // ����û�������
#define MAX_PASS 50     // ������볤��

//����ȫ�ֱ���
char currentUser[MAX_NAME] = ""; // ��ǰ��¼�û�
int page = 0;

// ���ʽṹ�嶨��
typedef struct {
    char english[50];      // Ӣ�ĵ���
    char chinese[200];     // ��������
} Word;

// ѡ��ṹ�嶨��
typedef struct {
    char option[200];      // ѡ������
    int isCorrect;         // �Ƿ�Ϊ��ȷѡ��
} Option;

// ����Ĵ��󵥴ʽṹ��
typedef struct {
    char english[50];
    char chinese[200];
    int errorcount;
} errorwords;

// ����Ĵ��󵥴ʽṹ��
typedef struct {
    char english[50];
    char chinese[200];
    int errornumber;
    int mistake2;//�ñ���ֻ�����������
}test;

// �û���¼/ע�����   Powerby ���ڿ� 
int userLoginMenu();
int userLogin();
int userRegister();
int checkUser(const char* username, const char* password);
int userExists(const char* username);

// ������ʱ�   Powerby ���ڿ�
void browseWords(void);
void saveProgress(void); // ���浱ǰ���ȵ��ļ�
void loadProgress(void); // �����ϴα���Ľ���

// ��ѯ����   Powerby ������
void searchWord();
void searchWordByEnglish(const char* english);	// case 1 ����Ӣ�Ĳ鵥��
void searchWordByChinese(const char* chinese);	// case 2 �������Ĳ鵥��

// Ĭд����   Powerby ���
void selfStudy();
void testWordsEtoC();  // Ӣ��ת���Ĳ���
void testWordsCtoE();  // ����תӢ�Ĳ���
void exitTest();

// �����ղر�   Powerby ���ڿ�
void vocabularyBook(void);
void addtobook(const char* word);		// ��ӵ����ʱ� case 3		���뵥�ʺͺ���
void removefrombook(const char* word);	// �ӵ��ʱ���ɾ�� case 4		�����Ӧ���ɾ��
void InitFile(void);	// ��ʼ�����ʱ��ļ� case 5

// ��������   Powerby ������
void enhanceMemory();
void generateOptions1(Option options[], test word, int mode);

// ���ʲ���   Powerby ���
void selfTest();
void learnWordsEtoC();   // Ӣ�ġ����ı�����
void learnWordsCtoE();   // ���ġ�Ӣ�ı�����
void exitStudyProgram();
void generateOptions(Option options[], Word word, int mode); // ����ѡ��

// �˳�����   Powerby ���ڿ�
void exitProgram(void);
