#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "head.h"

// ������   Powerby ���ڿ�
int main() {
    if (!userLoginMenu()) {
        printf("\n��¼ʧ�ܣ������˳���\n");
        return 0;
    }
    // ��¼�ɹ���currentUser������
    // ���������ղر���������vocab_<currentUser>.txt

    char xz[7];
    while (1) {
        system("cls");
        printf("\n\n\t\t\t    English Dictionary");
        printf("\n\n\t===========================================================");
        printf("\n\n\t\t\t\t0----Exit");
        printf("\n\n\t\t-------------------------------------------");
        printf("\n\n\t\t  1----�������");
        printf("\t\t2----��ѯ����");
        printf("\n\n\t\t  3----Ĭд����");
        printf("\t\t4----�����ղ�");
        printf("\n\n\t\t  5----��������");
        printf("\t\t6----���ʲ���");
        printf("\n\n\t\t-------------------------------------------");
        printf("\n\n\t===========================================================");
        printf("\n\n\t\t\tPlease choise: (0-6):");
        while (1) {
            gets(xz);
            if (xz[0] >= 48 && xz[0] <= 57) break;
        }
        system("cls");
        switch (xz[0]) {
		case '0': exitProgram(); return 0; break;  // �˳�����   Powerby ���ڿ�
		case '1': browseWords(); break;            // �������   Powerby ���ڿ� 
		case '2': searchWord(); break;             // ��ѯ����   Powerby ������
		case '3': selfStudy(); break;              // Ĭд����   Powerby ���
		case '4': vocabularyBook(); break;         // �����ղ�   Powerby ���ڿ�
        case '5': enhanceMemory(); break;          // ��������   Powerby ������
		case '6': selfTest(); break;               // ���ʲ���   Powerby ���
        }
    }
}

// �û���¼��ע��˵�   Powerby ���ڿ�
int userLoginMenu() {
    int choice;
    while (1) {
        system("cls");
        printf("\n\t��ӭʹ��Ӣ��ʵ�ϵͳ��\n\n");
        printf("\t1. ��¼\n");
        printf("\t2. ע��\n");
        printf("\t0. �˳�\n");
        printf("\n\t��ѡ��: ");
        scanf("%d", &choice);
        getchar(); // ���ջس�
        switch (choice) {
        case 0: return 0;
        case 1: if (userLogin()) return 1; break;
        case 2: userRegister(); break;
        default: printf("��Чѡ��\n"); break;
        }
    }
}

// ��¼
int userLogin() {
    char username[MAX_NAME], password[MAX_PASS];
    printf("�������û���: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;
    printf("����������: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;
    if (checkUser(username, password)) { // ����checkUser��������û���������
		strcpy(currentUser, username); // ����ǰ�û�����Ϊ��¼���û���
        printf("��¼�ɹ���\n");
        system("pause");
        return 1;
    } else {
        printf("�û������������\n");
        system("pause");
        return 0;
    }
}

// ע��
int userRegister() {
    char username[MAX_NAME], password[MAX_PASS];
    printf("���������û���: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;
    if (userExists(username)) {
        printf("�û����Ѵ��ڣ�\n");
        system("pause");
        return 0;
    }
    printf("������������: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;
	FILE* fp = fopen("users.txt", "a"); // ׷��ģʽ���û��ļ�
    if (fp) {
		fprintf(fp, "%s %s\n", username, password); // ���û���������д���ļ�
        fclose(fp);
        printf("ע��ɹ���\n");
        system("pause");
        return 1;
    }
    printf("ע��ʧ�ܣ�\n");
    system("pause");
    return 0;
}

// ����û���������
int checkUser(const char* username, const char* password) {
    FILE* fp = fopen("users.txt", "r");
    char u[MAX_NAME], p[MAX_PASS];
    if (!fp) return 0;
    while (fscanf(fp, "%s %s", u, p) == 2) {
		if (strcmp(u, username) == 0 && strcmp(p, password) == 0) { // ����û����������Ƿ�ƥ��
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// ����û����Ƿ����
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

// ������ʱ�   Powerby ���ڿ�
void browseWords() {
    FILE* fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printf("�޷��򿪵����ļ�!\n");
        return;
    }

    char words[300][50];      // ���ʱ�����Ϊ300
    char meanings[300][50];
    int count = 0;

    // ��ȡ����
    while (count < 300 && fscanf(fp, "%s\t%s", words[count], meanings[count]) == 2) {
        count++;
    }
    fclose(fp);

    int wordsPerPage = 10;    // ÿҳ��ʾ10������
    int totalPages = (count + wordsPerPage - 1) / wordsPerPage;

    while (1) {
     F1:system("cls");
        printf("\n\t\t\t���ʱ� (��%dҳ/��%dҳ, ��%d������)\n\n", page + 1, totalPages, count);

        // ��ʾ��ǰҳ����
        for (int i = page * wordsPerPage;
            i < (page + 1) * wordsPerPage && i < count;
            i++) {
            printf("%d. %s - %s\n", i + 1, words[i], meanings[i]);
        }

        printf("\n\n0:�رյ��ʱ�   1:��һҳ   2:��һҳ   3:��������   4:ɾ������   5:�ղص���\n");
		printf("6:�����ǩ     7:�ص���ǩλ��\n");
        printf("\n��ѡ�����: ");

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
                    printf("�������µ���: ");
                    fgets(newWord, sizeof(newWord), stdin);
                    newWord[strcspn(newWord, "\n")] = 0;
                    printf("�����뵥�ʺ���: ");
                    fgets(newMeaning, sizeof(newMeaning), stdin);
                    newMeaning[strcspn(newMeaning, "\n")] = 0;

                    // ��鵥���Ƿ��Ѵ���
                    int exists = 0;
                    for (int i = 0; i < count; i++) {
                        if (strcmp(words[i], newWord) == 0) {
							exists = 1; // �����Ѵ���
                            break;
                        }
                    }
                    if (exists) {
                        printf("�õ����Ѵ��ڣ��޷��ظ���ӣ�\n");
                        system("pause");
						break; // ������ӵ���
                    }

					fp = fopen("words.txt", "a"); // ׷��ģʽ�򿪵����ļ�
                    if (fp != NULL) {
						fprintf(fp, "%s\t%s\n", newWord, newMeaning); // д���µ��ʺͺ���
                        fclose(fp);
                        printf("�µ��������!\n");
                        // ���¼��ص����б�
                        count = 0;
						fp = fopen("words.txt", "r"); // ���´��ļ���ȡ
                        while (count < 300 && fscanf(fp, "%s\t%s", words[count], meanings[count]) == 2) {
							count++; // ���¶�ȡ������
                        }
                        fclose(fp);
                    }
                    else {
                        printf("�޷��򿪵����ļ�!\n");
                    }
                    system("pause");
                } break;
                case 4: // ɾ������
                {
                    if (count == 0) {
                        printf("���ʱ�Ϊ�գ��޿�ɾ�����ʡ�\n");
                        system("pause");
                        break;
                    }
                    int delIdx;
                    printf("������Ҫɾ���ĵ������: ");
                    fgets(input, sizeof(input), stdin);
                    if (sscanf(input, "%d", &delIdx) == 1 && delIdx >= 1 && delIdx <= count) {
                        delIdx--; // תΪ�±�
                        // ɾ�����ʲ���������
                        for (int i = delIdx; i < count - 1; i++) {
							strcpy(words[i], words[i + 1]); // ������ĵ���ǰ��
							strcpy(meanings[i], meanings[i + 1]); // ������ĺ���ǰ��
                        }
                        count--;
                        // ����д���ļ�
                        fp = fopen("words.txt", "w");
                        if (fp != NULL) {
                            for (int i = 0; i < count; i++) {
                                fprintf(fp, "%s\t%s\n", words[i], meanings[i]);
                            }
                            fclose(fp);
                            printf("������ɾ��!\n");
                        }
                        else {
                            printf("�޷��򿪵����ļ�!\n");
                        }
                        system("pause");
                    }
                    else {
                        printf("������Ч��\n");
                        system("pause");
                    }
                }
                break;
                case 5: // �ղص���
                {
                    int idx;
                    printf("������Ҫ�ղصĵ������: ");
                    fgets(input, sizeof(input), stdin);
                    if (sscanf(input, "%d", &idx) == 1 && idx >= 1 && idx <= count) {
                        char filename[100];
						snprintf(filename, sizeof(filename), "vocab_%s.txt", currentUser); // �û������������ղر�
                        FILE* fav = fopen(filename, "a");
                        if (fav != NULL) {
                            fprintf(fav, "%s\t%s\n", words[idx - 1], meanings[idx - 1]);
                            fclose(fav);
                            printf("�������ղص��ղر���\n");
                        }
                        else {
                            printf("�޷����ղر��ļ���\n");
                        }
                    }
                    else {
                        printf("������Ч��\n");
                    }
                    system("pause");
                } break;
				// case 6 �� case 7 �൱�ڽ��ȹ��ܣ�ͨ����ǩ������ͼ��ص�ǰ�����ҳ������
                case 6:
                {
                    saveProgress();// ���浱ǰ���ȵ��ļ�
                    goto F1;
                }
                case 7:
                {
                    loadProgress();// �����ϴα���Ľ���
                    goto F1;
                }
                }
            }
        }
    }
}

//����ȫ�ֱ���page��ͨ������Ͷ�ȡpage��ֵ��ʵ����ǩ����
// ���浱ǰ���ȵ��ļ�
void saveProgress() {
    FILE* fp;
    if ((fp = fopen("bookmark.txt", "w")) == NULL) {
        printf("\n\nCannot open bookmark.txt file!\n");
        system("pause");
    }
    if ((fprintf(fp, "%d", page)) == NULL){
        printf("����ʧ�ܣ�(�����������)");
        getch();
    }
    else {
        printf("����ɹ���(�����������)");
        getch();
    }
    fclose(fp);
}

// �����ϴα���Ľ���
void loadProgress() {
    FILE* fp;
    if ((fp = fopen("bookmark.txt", "r")) == NULL) {
        printf("\n\nCannot open bookmark.txt file!\n");
        system("pause");
    }
    if ((fscanf(fp, "%d", &page)) == NULL) {
        printf("\n��ǩ������(�����������)");
        getch();
    }
    fclose(fp);
}
//-----------------------------------------------------------------------------------------------

// ��ѯ����   Powerby ������
void searchWord() {
    char xz[8];
    system("cls");
    printf("\n\n                    0--�˳�");
    printf("\n\n                    1--Ӣ�Ĳ��");
    printf("\n\n                    2--���Ĳ��");
    printf("\n\n\n                    ��ѡ��: (0, 1, 2): ");
    do {
        fgets(xz, 8, stdin);
    } while (xz[0] != '0' && xz[0] != '1' && xz[0] != '2' && xz[0] != '3');
    switch (xz[0]) {
    case '0': return;
    case '1': {
        char ch[50];   int find;    FILE* fp;
        Word x;      // ���嵥�ʵĽṹ�����x
        if ((fp = fopen("words.txt", "r")) == NULL) {
            printf("\n\nCannot open words.txt file!\n");
            system("pause"); break;
        }
    F1: system("cls");
        printf("\n     Input English Word Which You Want To Know ");
        printf("\n==================================================");
        printf("\n English Word : ");    gets(ch);    // ����һ�����ʵ��ַ�����ch
        find = 0;
        rewind(fp);    // ��λ���ļ�ͷ
        fscanf(fp, "%s\t%s", x.english, x.chinese);   // �Ӵʵ��ж�ȡһ������
        while (!feof(fp)) {
            if (strcmp(x.english, ch) == 0) {    // ����ڴʵ����ҵ���Ӣ��Ϊch�ĵ��ʽṹ��
                printf("\n English:%s\n chinese:%s\n", x.english, x.chinese);    // ��ӡ���ʽṹ���Ա
                find = 1;
                break;
            }
            fscanf(fp, "%s\t%s", x.english, x.chinese);  //ѭ����ȡ
        }
        if (!find) {
            printf("\n�Բ���,δ��ѯ��������ĵ��� (���n��?)\n");
        }
        printf("==================================================");
        printf("\n\n\n   �����������ѯ������ (y/n)  ");
        do {
            fgets(ch, 50, stdin);
        } while (!(ch[0] == 'y' || ch[0] == 'n' || ch[0] == 'Y' || ch[0] == 'N'));
        if (ch[0] == 'y' || ch[0] == 'Y') goto F1;    // ʵ�����ǹ���ѭ��
        else fclose(fp);
        break;
    }
    case '2': {
        char ch[50];   int find;    FILE* fp;
        Word x;      // ���嵥�ʵĽṹ�����x
        if ((fp = fopen("words.txt", "r")) == NULL) {
            printf("\n\nCannot open words.txt file!\n");
            system("pause"); break;
        }
    F2: system("cls");
        printf("\n     Input Chinese Word Which You Want To Know ");
        printf("\n==================================================");
        printf("\n Chinese Word : ");    gets(ch);    // ����һ��ѧ�ŵ��ַ�����ch
        find = 0;
        rewind(fp);    // ��λ���ļ�ͷ
        fscanf(fp, "%s\t%s", x.english, x.chinese);   // �Ӵʵ��ж�ȡһ������
        while (!feof(fp)) {
            if (strcmp(x.chinese, ch) == 0) {    // ����ڴʵ����ҵ�������Ϊch�ĵ��ʽṹ��
                printf("\n English:%-s\n chinese:%-s\n", x.english, x.chinese);    // ��ӡ���ʽṹ���Ա
                find = 1;
                break;
            }
            fscanf(fp, "%s\t%s", x.english, x.chinese);    // ��ѧ���ļ��ж�ȡһ��ѧ����¼
        }
        if (!find) {
            printf("\n�Բ���,δ��ѯ��������ĵ��� (���n��?)\n");
        }
        printf("==================================================");
        printf("\n\n\n   �����������ѯ������ (y/n)  ");
        do {
            fgets(ch, 50, stdin);
        } while (!(ch[0] == 'y' || ch[0] == 'n' || ch[0] == 'Y' || ch[0] == 'N'));
        if (ch[0] == 'y' || ch[0] == 'Y') goto F2;    // ʵ�����ǹ���ѭ��
        else fclose(fp);
        break;
    }
    }
}
//-----------------------------------------------------------------------------------------------

// Ĭд����   Powerby ���
void selfStudy() {
    char choice[10];  // �洢�û������ѡ��

    while (1) {
        system("cls");  // ����
        // ��ʾ�˵�����
        printf("\n\n\t\t\t===== Ӣ�ﵥ�ʲ���ϵͳ =====\n");
        printf("\t=======================================================\n");
        printf("\n\t\t\t��ѡ�����ģʽ��\n\n");
        printf("\t\t1. Ӣ�ĵ��� -> �������� (English to Chinese)\n");
        printf("\t\t2. �������� -> Ӣ�ĵ��� (Chinese to English)\n");
        printf("\n\t\t0. �˳�ϵͳ (Exit)\n");
        printf("\n\t\t--------------------------------------------\n");
        printf("\t\t��ʾ�������Ӧ���ֲ���Enter��ȷ��ѡ��\n");
        printf("\t=======================================================\n");

        // ��ȡ�û�ѡ��
        printf("\n\t\t��ѡ�� (0-2): ");
        if (fgets(choice, sizeof(choice), stdin) != NULL) {
            choice[strcspn(choice, "\n")] = 0;  // �Ƴ����з�

            // ��֤�����Ƿ�Ϊ��Ч����
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
                    printf("\n\t������Ч����ѡ��0-2֮������֣�\n");
                    getch();  // ��ͣ�鿴��ʾ
                    break;
                }
            }
            else {
                printf("\n\t��������Ч�����֣�\n");
                getch();  // ��ͣ�鿴��ʾ
            }
        }
    }
}

void testWordsCtoE() {
    Word words[300], learnedwords[300];
    int count = 0;         // ���ʿ�����
    int score = 0;         // ��ȷ����
    int total = 0;         // �ܲ�������
    int learned = 0;       // ��ѧϰ������
    int current = 0;       // ��ǰ��������
    char userAnswer[200];  // �û�����Ĵ�
    clock_t startTime, endTime;
    double totalTime = 0.0;

    FILE* fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printf("�޷��򿪵����ļ�!\n");
        getch();
        return;
    }
    while (fscanf(fp, "%s\t%s", words[count].english, words[count].chinese) != EOF && count < 300) {
        count++;
    }
    fclose(fp);

    // ������ѧϰ����
    FILE* fp1 = fopen("learnedwords.txt", "r+");
    if (fp1 == NULL) {
        fp1 = fopen("learnedwords.txt", "w");
        if (fp1 == NULL) {
            printf("�޷�������ѧϰ�����ļ�!\n");
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
        printf("���ʿ�Ϊ�գ��޷����в���!\n");
        getch();
        return;
    }

    srand(time(NULL));
    startTime = clock();
    system("cls");
    printf("\n\n\t=============== ����ѧϰ��ʼ ===============\n");
    printf("\t\t�������������Ӧ��Ӣ�ĵ���\n");
    printf("\t\t��ESC����ʱ�˳�ѧϰ\n");
    printf("\t\t��L�����������յ���\n\n");

    while (1) {
        // ����δѧϰ�ĵ���
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

        // ����Ƿ����е��ʶ���ѧϰ
        if (current >= count) {
            printf("\n\n\t���е�����ѧϰ���!\n");
            break;
        }

        total++;
        printf("\n�� %d ��: ������ \"%s\" ��Ӧ��Ӣ�ĵ���: ", total, words[current].chinese);

        int ch;
        int i = 0;
        while ((ch = getch()) != '\r') {
            if (ch == 27) { // ESC��
                printf("\n\n\t�û�ѡ���˳�ѧϰ...\n");
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
                printf("\n�ѽ��õ��ʱ��Ϊ������\n");
                printf("�Ѽ�ס %d ������\n", learned);
                break;
            }

            if (i < sizeof(userAnswer) - 1) {
                userAnswer[i++] = ch;
                putchar(ch);
            }
        }
        userAnswer[i] = '\0'; // �ַ���������

        if (strcmp(userAnswer, words[current].english) == 0) {
            printf("\n�ش���ȷ! ��ϲ���1��\n");
            score++;
        }
        else if (ch == 'L' || ch == 'l') {
            current++;
            score++;
        }
        else {
            printf("\n�ش����! ��ȷ����: %s\n", words[current].english);
        }

        current++;

        // ��Enter������ESC�˳�
        printf("\n��Enter���������ԣ���ESC���˳�: ");
        while (1) {
            ch = getch();
            if (ch == 27) { // ESC��
                printf("\n�û�ѡ���˳�����...\n");
                goto exitTest;
            }
            if (ch == '\r') { // Enter��
                printf("\n");
                break;
            }
        }
    }

exitTest:
    // ������ѧϰ����
    fp1 = fopen("learnedwords.txt", "w");
    if (fp1 == NULL) {
        printf("�޷�����ѧϰ�����ļ�!\n");
        getch();
        return;
    }
    for (int i = 0; i < learned; i++) {
        fprintf(fp1, "%s\t%s\n", learnedwords[i].english, learnedwords[i].chinese);
    }
    fclose(fp1);

    // ���㲢��ʾͳ����Ϣ
    endTime = clock();
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	system("cls");
    printf("\n\n\t=============== ����ѧϰ���� ===============\n");
    printf("\t������: %d\n", total);
    printf("\t��ȷ��: %d\n", score);
    printf("\t��ȷ��: %.1f%%\n", total > 0 ? (float)score / total * 100 : 0);
    printf("\t����ʱ: %.2f��\n", totalTime);
    if (total > 0) {
        printf("\tƽ��ÿ����ʱ: %.2f ��\n", totalTime / total);
    }
    printf("\t��������������˵�...\n");
    getch();
}

void testWordsEtoC() {
    Word words[300], learnedwords[300];
    int count = 0;         // ���ʿ�����
    int score = 0;         // ��ȷ����
    int total = 0;         // �ܲ�������
    int learned = 0;       // ��ѧϰ������
    int current = 0;       // ��ǰ��������
    char userAnswer[200];  // �û�����Ĵ�
    clock_t startTime, endTime;
    double totalTime = 0.0;

    FILE* fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printf("�޷��򿪵����ļ�!\n");
        getch();
        return;
    }
    while (fscanf(fp, "%s\t%s", words[count].english, words[count].chinese) != EOF && count < 300) {
        count++;
    }
    fclose(fp);

    // ������ѧϰ����
    FILE* fp1 = fopen("learnedwords.txt", "r+");
    if (fp1 == NULL) {
        fp1 = fopen("learnedwords.txt", "w");
        if (fp1 == NULL) {
            printf("�޷�������ѧϰ�����ļ�!\n");
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
        printf("���ʿ�Ϊ�գ��޷����в���!\n");
        getch();
        return;
    }

    srand(time(NULL));
    startTime = clock();
    system("cls");
    printf("\n\n\t=============== ����ѧϰ��ʼ ===============\n");
    printf("\t\t����Ӣ�������Ӧ������\n");
    printf("\t\t��ESC����ʱ�˳�����\n");
    printf("\t\t��L�����������յ���\n\n");

    while (1) {
        // ����δѧϰ�ĵ���
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

        // ����Ƿ����е��ʶ���ѧϰ
        if (current >= count) {
            printf("\n\n\t���е�����ѧϰ���!\n");
            break;
        }

        total++;
        printf("\n�� %d ��: ������ \"%s\" ��Ӧ����������: ", total, words[current].english);

        int ch;
        int i = 0;
        while ((ch = getch()) != '\r') {
            if (ch == 27) { // ESC��
                printf("\n\n\t�û�ѡ���˳�����...\n");
                goto exitTest;
            }

            if (ch == '\b' && i > 0) { // �˸��
                i--;
                printf("\b \b");
                continue;
            }

            if (ch == 'L' || ch == 'l') { // ���Ϊ��ѧϰ
                if (learned < 300) {
                    strcpy(learnedwords[learned].english, words[current].english);
                    strcpy(learnedwords[learned].chinese, words[current].chinese);
                    learned++;
                }
                printf("\n�ѽ��õ��ʱ��Ϊ������\n");
                printf("�Ѽ�ס %d ������\n", learned);
                break;
            }

            if (i < sizeof(userAnswer) - 1) {
                userAnswer[i++] = ch;
                putchar(ch);
            }
        }
        userAnswer[i] = '\0'; // �ַ���������

        if (strcmp(userAnswer, words[current].chinese) == 0) {
            printf("\n�ش���ȷ! ��ϲ���1��\n");
            score++;
        }
        else if (ch == 'L' || ch == 'l') {
            current++;
            score++;
        }
        else {
            printf("\n�ش����! ��ȷ����: %s\n", words[current].chinese);
        }

        current++;

        // ��Enter������ESC�˳�
        printf("\n��Enter���������ԣ���ESC���˳�: ");
        while (1) {
            ch = getch();
            if (ch == 27) { // ESC��
                printf("\n�û�ѡ���˳�����...\n");
                goto exitTest;
            }
            if (ch == '\r') { // Enter��
                printf("\n");
                break;
            }
        }
    }

exitTest:
    // ������ѧϰ����
    fp1 = fopen("learnedwords.txt", "w");
    if (fp1 == NULL) {
        printf("�޷�����ѧϰ�����ļ�!\n");
        getch();
        return;
    }
    for (int i = 0; i < learned; i++) {
        fprintf(fp1, "%s\t%s\n", learnedwords[i].english, learnedwords[i].chinese);
    }
    fclose(fp1);

    // ���㲢��ʾͳ����Ϣ
    endTime = clock();
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	system("cls");
    printf("\n\n\t=============== ����ѧϰ���� ===============\n");
    printf("\t������: %d\n", total);
    printf("\t��ȷ��: %d\n", score);
    printf("\t��ȷ��: %.1f%%\n", total > 0 ? (float)score / total * 100 : 0);
    printf("\t����ʱ: %.2f��\n", totalTime);
    if (total > 0) {
        printf("\tƽ��ÿ����ʱ: %.2f ��\n", totalTime / total);
    }
    printf("\t��������������˵�...\n");
    getch();
}

void exitTest() {
    system("cls");
    printf("\n\n\t\t����Ĭд���ò���,�´��ٽ�����Ŷ��~^o^~\n");
    printf("\n\t\t��������˳�...");
    getch();
}
//-----------------------------------------------------------------------------------------------

// �����ղر�   Powerby ���ڿ�
void vocabularyBook() {
    FILE* fp;
    char filename[100];
	snprintf(filename, sizeof(filename), "vocab_%s.txt", currentUser); // ʹ�õ�ǰ�û������������ղر�
    char words[100][50];
    char meanings[100][50];
    int count = 0;

    // ����ļ����������½�
    fp = fopen(filename, "a+");
    if (fp == NULL) {
        printf("�޷���������ղر��ļ�!\n");
        return;
    }
    fclose(fp);

reload:
    // ��ȡ����
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
        printf("\n\t\t\t�����ղر� (��%dҳ/��%dҳ, ��%d������)\n\n", page + 1, totalPages > 0 ? totalPages : 1, count);

        // ��ʾ��ǰҳ����
        for (int i = page * wordsPerPage; i < (page + 1) * wordsPerPage && i < count; i++) {
            printf(" %d. %s - %s\n", i + 1, words[i], meanings[i]);
        }

        printf("\n\n 0:�ر��ղر�   1:��һҳ   2:��һҳ   3:��������   4:�Ƴ�����   5:��ʼ��\n");
        printf("\n ��ѡ�����: ");

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
                    printf("�������µ���: ");
                    fgets(newWord, sizeof(newWord), stdin);
                    newWord[strcspn(newWord, "\n")] = 0;
                    printf("�����뵥�ʺ���: ");
                    fgets(newMeaning, sizeof(newMeaning), stdin);
                    newMeaning[strcspn(newMeaning, "\n")] = 0;

                    // ��鵥���Ƿ��Ѵ���
                    int exists = 0;
                    for (int i = 0; i < count; i++) {
                        if (strcmp(words[i], newWord) == 0) {
                            exists = 1;
                            break;
                        }
                    }
                    if (exists) {
                        printf("�õ����Ѵ��ڣ��޷��ظ���ӣ�\n");
                        system("pause");
                        break;
                    }

                    fp = fopen(filename, "a");
                    if (fp != NULL) {
                        fprintf(fp, "%s\t%s\n", newWord, newMeaning);
                        fclose(fp);
                        printf("�µ��������!\n");
                        system("pause");
                        goto reload;
                    } else {
                        printf("�޷����ղر��ļ�!\n");
                        system("pause");
                    }
                    break;
                }
                case 4: {
                    if (count == 0) {
                        printf("�ղر�Ϊ�գ��޿��Ƴ����ʡ�\n");
                        system("pause");
                        break;
                    }
                    int delIdx;
                    printf("������Ҫ�Ƴ��ĵ������: ");
                    fgets(input, sizeof(input), stdin);
                    if (sscanf(input, "%d", &delIdx) == 1 && delIdx >= 1 && delIdx <= count) {
                        delIdx--; // תΪ�±�
                        // �Ƴ�����
                        for (int i = delIdx; i < count - 1; i++) {
                            strcpy(words[i], words[i + 1]);
                            strcpy(meanings[i], meanings[i + 1]);
                        }
                        count--;
                        // ����д���ļ�
                        fp = fopen(filename, "w");
                        for (int i = 0; i < count; i++) {
                            fprintf(fp, "%s\t%s\n", words[i], meanings[i]);
                        }
                        fclose(fp);
                        printf("�������Ƴ�!\n");
                        system("pause");
                        goto reload;
                    } else {
                        printf("������Ч��\n");
                        system("pause");
                    }
                    break;
                }
                case 5: {
                    printf("\nȷ��Ҫ��ʼ���ղر��𣿴˲�������������ղص��ʣ�(y/n): ");
                    fgets(input, sizeof(input), stdin);
                    if (input[0] == 'y' || input[0] == 'Y') {
						fp = fopen(filename, "w"); // ����ļ�����
                        if (fp) fclose(fp);
                        printf("�ղر��ѳ�ʼ����\n");
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

// ��������   Powerby ������
void enhanceMemory() { //���ڴ������Խ��ĵ��ʣ��ڱ����ʵ�ʱ����ִ���Խ��
    test t[300];
    test transmit;
    int i;     //sum�ǳ�����Ŀ������i���м�¼�ı���������
    int j, k;
    int mistake1[300];//�ñ���ֻ�������������û��ʵ������
F1:srand((unsigned)time(NULL));
    i = 0;
    FILE* fp;
    if ((fp = fopen("errorwords.txt", "r")) == NULL) {
        printf("���ܴ򿪴���ͳ���ļ���");
        system("pause");
    }
    while (!feof(fp)) {
        fscanf(fp, "%s\t%s\t%d", t[i].english, t[i].chinese, &t[i].errornumber);//���ļ��ж�ȡ��������Լ��������
        i++;
    }
    //����ð�����򷨽���������϶�ĵ��������ṹ�����鿿ǰλ��
    for (j = 1; j < i; j++) {        //��j��������j-1������
        for (k = 0; k <= i - 1 - j; k++) {    //��j�������t[i-1-j].errornumber����λ
            if (t[k].errornumber < t[k + 1].errornumber) {  //������λ�����ϴ��������ĵ��ʵ���ǰ��
                transmit = t[k];
                t[k] = t[k + 1];
                t[k + 1] = transmit;
            }
        }
    }
    for (j = 0; j <= i - 1; j++) {
        mistake1[j] = rand() % (j + 1);    //������Խ��ǰ�ĵ��ʵ�λ��Խ���ױ�������鵽
    }
    for (j = 0; j <= i - 1; j++) {   //���ṹ����mistake2��Ա��ֵΪ0��
        t[j].mistake2 = 0;
    }
    for (j = 0; j <= i - 1; j++) {       //ͳ�Ƹ�����������ֵĴ���
        for (k = 0; k <= i - 1; k++) {
            if (mistake1[k] == j) {
                t[j].mistake2++;
            }
        }
    }
    //����ð�����򷨽��������ѡ�н϶�����ĵ��������ṹ�����鿿ǰλ��
    for (j = 1; j < i; j++) {        //��j��������j-1������
        for (k = 0; k <= i - 1 - j; k++) {    //��j�������t[i-1-j].errornumber����λ
            if (t[k].mistake2 < t[k + 1].mistake2) {  //������λ���������ѡ�н϶�����ĵ��ʵ���ǰ��
                transmit = t[k];
                t[k] = t[k + 1];
                t[k + 1] = transmit;
            }
        }
    }
    fclose(fp);

    //����ҳ�����
    char xz[8]; int total = 0;
    printf("                 ��������               \n");
    printf("=============================================\n");
    printf("              ��ѡ��ѧϰģʽ��\n");
    printf("       1. Ӣ�ĵ��� �� �������� (ѡ����)\n");
    printf("       2. �������� �� Ӣ�ĵ��� (ѡ����)\n");
    printf("           0. �˳� (Exit)\n");
    printf("---------------------------------------------\n");
    printf("      ��ʾ�������Ӧ���ֲ���Enter��ȷ��ѡ��\n");
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
            printf("����Ӣ�ĵ���ѡ����Ӧ�����ģ���10�⣩\n");
            printf("�� %d �⣺%s\n", j, t[j - 1].english);
            printf("--------------------------------------------\n");
            printf("     A,%s\n", options[0].option);
            printf("     B,%s\n", options[1].option);
            printf("     C,%s\n", options[2].option);
            printf("     D,%s\n", options[3].option);
            printf("--------------------------------------------\n");
            printf("��ѡ��A-D����");
            while (1) {
                fgets(xz, 8, stdin);
                if (xz[0] >= 'A' && xz[0] <= 'D') {
                    break;
                }
            }

            if (options[xz[0] - 'A'].isCorrect) {
                total++;
                printf("�ش���ȷ����ȷ����:%s(�����������)", t[j - 1].chinese);
                getch();
            }
            else {
                printf("�ش������ȷ����:%s(�����������)", t[j - 1].chinese);
                getch();
            }
            system("cls");
        }
        printf("\n\n\n\t���Խ�����\n\n");
        printf("\t��ɹ������%d����\n\n", total);
        printf("\n\t�Ƿ���Ҫ�ٴβ��飨y/n����");
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
            printf("��������ѡ����Ӧ��Ӣ�ĵ��ʣ���10�⣩\n");
            printf("�� %d �⣺%s\n", j, t[j - 1].chinese);
            printf("--------------------------------------------\n");
            printf("     A,%s\n", options[0].option);
            printf("     B,%s\n", options[1].option);
            printf("     C,%s\n", options[2].option);
            printf("     D,%s\n", options[3].option);
            printf("--------------------------------------------\n");
            printf("��ѡ��A-D����");
            while (1) {
                fgets(xz, 8, stdin);
                if (xz[0] >= 'A' && xz[0] <= 'D') {
                    break;
                }
            }
            
            if (options[xz[0] - 'A'].isCorrect) {
                total++;
                printf("�ش���ȷ����ȷ����:%s(�����������)", t[j - 1].english);
                getch();
            }
            else {
                printf("�ش������ȷ����:%s(�����������)", t[j - 1].english);
                getch();
            }
            system("cls");
        }
        printf("\n\n\n\t���Խ�����\n\n");
        printf("\t��ɹ������%d����\n\n", total);
        printf("\n\t�Ƿ���Ҫ�ٴβ��飨y/n����");
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
        printf("�޷��򿪵����ļ�!\n");
        getch();
        return 0;
    }

    while (fscanf(fp, "%s\t%s", words[count].english, words[count].chinese) != EOF && count < 100) {
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("���ʿ�Ϊ�գ��޷�����ѧϰ!\n");
        getch();
    }
    if (count <= 1) return; // ������Ҫ2�����ʲ������ɴ���ѡ��

    if (mode == 1) {
        // ������ȷѡ��
        strcpy(options[0].option, word.chinese);
        options[0].isCorrect = 1;

        for (int i = 1; i < 4; i++) {
            int randIndex;
            do {
                randIndex = rand() % count;
            } while (strcmp(words[randIndex].english, word.english) == 0); // ����ѡ��ͬһ����
            strcpy(options[i].option, words[randIndex].chinese);
            options[i].isCorrect = 0;
        }
    }

    else {
        // ������ȷѡ��
        strcpy(options[0].option, word.english);
        options[0].isCorrect = 1;

        // ����3������ѡ��
        for (int i = 1; i < 4; i++) {
            int randIndex;
            do {
                randIndex = rand() % count;
            } while (strcmp(words[randIndex].chinese, word.chinese) == 0); // ����ѡ��ͬһ����
            strcpy(options[i].option, words[randIndex].english);
            options[i].isCorrect = 0;
        }
    }

    // �������ѡ��˳��
    for (int i = 0; i < 4; i++) {
        int j = rand() % 4;
        Option temp = options[i];
        options[i] = options[j];
        options[j] = temp;
    }
}
//-----------------------------------------------------------------------------------------------

// ���ʲ���   Powerby ���
void selfTest() {
    char choice[10];  // �洢�û������ѡ��

    while (1) {
        system("cls");

        // ��ʾ�˵�����
        printf("\n\n\t\t\t===== Ӣ�ﵥ�ʱ��� =====\n");
        printf("\t=======================================================\n");
        printf("\n\t\t\t��ѡ��ѧϰģʽ��\n\n");
        printf("\t\t1. Ӣ�ĵ��� �� �������� (ѡ����)\n");
        printf("\t\t2. �������� �� Ӣ�ĵ��� (ѡ����)\n");
        printf("\n\t\t0. �˳�ϵͳ (Exit)\n");
        printf("\n\t\t--------------------------------------------\n");
        printf("\t\t��ʾ�������Ӧ���ֲ���Enter��ȷ��ѡ��\n");
        printf("\t=======================================================\n");

        // ��ȡ�û�ѡ��
        printf("\n\t\t��ѡ�� (0-2): ");
        if (fgets(choice, sizeof(choice), stdin) != NULL) {
            choice[strcspn(choice, "\n")] = 0;

            // ��֤�����Ƿ�Ϊ��Ч����
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
                    printf("\n\t������Ч����ѡ��0-2֮������֣�\n");
                    getch();
                    break;
                }
            }
            else {
                printf("\n\t��������Ч�����֣�\n");
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
        printf("�޷��򿪵����ļ�!\n");
        getch();
        return 0;
    }

    while (fscanf(fp, "%s\t%s", words[count].english, words[count].chinese) != EOF && count < 100) {
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("���ʿ�Ϊ�գ��޷�����ѧϰ!\n");
        getch();
    }

    if (count <= 1) return; // ������Ҫ2�����ʲ������ɴ���ѡ��

    if (mode == 1) {
        // ������ȷѡ��
        strcpy(options[0].option, word.chinese);
        options[0].isCorrect = 1;

        for (int i = 1; i < 4; i++) {
            int randIndex;
            do {
                randIndex = rand() % count;
            } while (strcmp(words[randIndex].english, word.english) == 0); // ����ѡ��ͬһ����
            strcpy(options[i].option, words[randIndex].chinese);
            options[i].isCorrect = 0;
        }
    }

    else {
        // ������ȷѡ��
        strcpy(options[0].option, word.english);
        options[0].isCorrect = 1;

        // ����3������ѡ��
        for (int i = 1; i < 4; i++) {
            int randIndex;
            do {
                randIndex = rand() % count;
            } while (strcmp(words[randIndex].chinese, word.chinese) == 0); // ����ѡ��ͬһ����
            strcpy(options[i].option, words[randIndex].english);
            options[i].isCorrect = 0;
        }
    }

    // �������ѡ��˳��
    for (int i = 0; i < 4; i++) {
        int j = rand() % 4;
        Option temp = options[i];
        options[i] = options[j];
        options[j] = temp;
    }
}

void learnWordsEtoC() {
    Word words[300];             // ���ʽṹ������
    errorwords errorwords[300], error[300];  // ��ʱ���󵥴�����
    FILE* fp1;

    int count = 0;              // ���ʿ�����
    int errorcount = 0;         // ����ѧϰ�д��󵥴�����
    int errorFileCount = 0;     // ���󵥴��ļ��е�����

    FILE* fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printf("�޷��򿪵����ļ�!\n");
        getch();
        return;
    }

    while (fscanf(fp, "%49s\t%199s", words[count].english, words[count].chinese) != EOF && count < 300) {
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("���ʿ�Ϊ�գ��޷�����ѧϰ!\n");
        getch();
        return;
    }

    int score = 0;
    int total = 0;
    char userChoice;              // �û�ѡ���ѡ��
    clock_t startTime, endTime;   // ��ʱ����
    double totalTime = 0.0;       // ��ʱ��

    srand(time(NULL));            // ��ʼ�����������
    startTime = clock();          // ��ʼ��ʱ
    system("cls");
    printf("\n\n\t=============== ������ģʽ��ʼ ===============\n");
    printf("\t\t����Ӣ�ĵ���ѡ����ȷ����������\n");
    printf("\t\tѡ�A/B/C/D����ESC����ʱ�˳�\n");
    printf("\n");

    while (1) {
        if (total >= count) {
            printf("\n\n���е�����ѧϰ���!\n");
            break;
        }

        int randIndex = rand() % count;
        total++;

        Option options[4];          // 4��ѡ��
        generateOptions(options, words[randIndex], 1);  // ����ѡ��
        system("cls");
        printf("\n�� %d ��: ���� \"%s\" �����������ǣ�\n", total, words[randIndex].english);
        printf("------------------------------------\n");

        // ��ʾ4��ѡ��
        for (int i = 0; i < 4; i++) {
            printf("    %c. %s\n", 'A' + i, options[i].option);
        }
        printf("------------------------------------\n");
        printf("��ѡ�� (A-D): ");

        // ��ȡ�û�ѡ��
        while (1) {
            int ch = getch();
            if (ch == 27) {         // ESC��
                endTime = clock();
                totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
                printf("\n\n�û�ѡ���˳�ѧϰ...\n");
                goto exitLearn;
            }

            if (ch >= 'A' && ch <= 'D' || ch >= 'a' && ch <= 'd') {
                userChoice = toupper(ch);
                printf("%c\n", userChoice);
                break;
            }
            else {
                printf("\n������A-D֮���ѡ��: ");
            }
        }

        // �ж�ѡ���Ƿ���ȷ
        int choiceIndex = userChoice - 'A';
        if (options[choiceIndex].isCorrect) {
            printf("\nѡ����ȷ! ��ϲ���1��\n");
            score++;
        }
        else {
            printf("\nѡ�����! ��ȷѡ����: ");
            for (int i = 0; i < 4; i++) {
                if (options[i].isCorrect) {
                    // ��¼���󵥴�
                    strcpy(errorwords[errorcount].chinese, options[i].option);
                    strcpy(errorwords[errorcount].english, words[randIndex].english);
                    errorwords[errorcount].errorcount = 1;
                    errorcount++;
                    printf("%c. %s\n", 'A' + i, options[i].option);
                    break;
                }
            }
        }

        // ��Enter����
        printf("\n��Enter������ѧϰ����ESC���˳�: ");
        while (1) {
            int ch = getch();
            if (ch == 27) {     // ESC��
                endTime = clock();
                totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
                printf("\n�û�ѡ���˳�ѧϰ...\n");
                goto exitLearn;
            }
            if (ch == '\r') {    // Enter��
                printf("\n");
                break;
            }
        }
    }

    endTime = clock();              // ������ʱ
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC; // ������ʱ��

exitLearn:
    // ������󵥴��ļ�
    fp1 = fopen("errorwords.txt", "r+");
    if (fp1 == NULL) {
        fp1 = fopen("errorwords.txt", "w");
        if (fp1 == NULL) {
            printf("�޷��������󵥴��ļ�!\n");
            getch();
            return;
        }
        fclose(fp1);
        fp1 = fopen("errorwords.txt", "r+");
    }

    // ��ȡ���д��󵥴�
    while (fscanf(fp1, "%49s\t%199s\t%d\n", error[errorFileCount].english, error[errorFileCount].chinese, &error[errorFileCount].errorcount) != EOF && errorFileCount < 300) {
        errorFileCount++;
    }

    // ��鲢���´��󵥴�
    for (int i = 0; i < errorcount; i++) {
        int found = 0;
        for (int j = 0; j < errorFileCount; j++) {
            if (strcmp(error[j].english, errorwords[i].english) == 0) {
                error[j].errorcount++;
                found = 1;
                break;
            }
        }
        // ����µĴ��󵥴�
        if (!found && errorFileCount < 300) {
            error[errorFileCount] = errorwords[i];
            errorFileCount++;
        }
    }

    // ����д����󵥴��ļ�
    fseek(fp1, 0, SEEK_SET);

    for (int i = 0; i < errorFileCount; i++) {
        fprintf(fp1, "%s\t%s\t%d\n", error[i].english, error[i].chinese, error[i].errorcount);
    }
    fclose(fp1);

    system("cls");
    printf("\n\n\t=============== ������ģʽ���� ===============\n");
    printf("\t������: %d\n", total);
    printf("\t��ȷ��: %d\n", total > 0 ? score : 0);
    printf("\t��ȷ��: %.1f%%\n", total > 0 ? (float)score / total * 100 : 0);
    printf("\t����ʱ: %.2f ��\n", totalTime);
    if (total > 0) {
        printf("\tƽ��ÿ����ʱ: %.2f ��\n", totalTime / total);
    }
    printf("\n\n\t��������������˵�...\n");
    getch();
}

void learnWordsCtoE() {
    Word words[300];
    errorwords errorwords[300], error[300];  // ��ʱ���󵥴�����// ���ʽṹ������
    int count = 0;
    int errorcount = 0;         // ����ѧϰ�д��󵥴�����
    int errorFileCount = 0;
    FILE* fp1;
    FILE* fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printf("�޷��򿪵����ļ�!\n");
        getch();
        return 0;
    }

    while (fscanf(fp, "%s\t%s", words[count].english, words[count].chinese) != EOF && count < 100) {
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("���ʿ�Ϊ�գ��޷�����ѧϰ!\n");
        getch();
    }
    if (count == 0) return;

    int score = 0;
    int total = 0;
    char userChoice;      // �û�ѡ���ѡ��
    clock_t startTime, endTime; // ��ʱ����
    double totalTime = 0.0;    // ��ʱ��

    srand(time(NULL)); // ��ʼ�����������
    startTime = clock(); // ��ʼ��ʱ
    system("cls");
    printf("\n\n\t=============== ������ģʽ��ʼ ===============\n");
    printf("\t\t������������ѡ����ȷ��Ӣ�ĵ���\n");
    printf("\t\tѡ�A/B/C/D����ESC����ʱ�˳�\n");
    printf("\t\t��ǰʱ��: %s", ctime(&startTime)); // ��ʾ��ʼʱ��
    printf("\n");

    while (1) {
        if (total >= count) {
            printf("\n\n���е�����ѧϰ���!\n");
            break;
        }

        // ���������������
        int randIndex = rand() % count;
        total++;

        Option options[4]; // 4��ѡ��
        generateOptions(options, words[randIndex], 2);
        system("cls");
        printf("\n�� %d ��: ���� \"%s\" ��Ӧ��Ӣ�ĵ����ǣ�\n", total, words[randIndex].chinese);
        printf("------------------------------------\n");

        // ��ʾ4��ѡ��
        for (int i = 0; i < 4; i++) {
            printf("    %c. %s\n", 'A' + i, options[i].option);
        }
        printf("------------------------------------\n");
        printf("��ѡ�� (A-D): ");

        while (1) {
            int ch = getch();
            if (ch == 27) { // ESC��
                endTime = clock(); // ������ʱ
                totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
                printf("\n\n�û�ѡ���˳�ѧϰ...\n");
                goto exitLearn;
            }

            if (ch >= 'A' && ch <= 'D' || ch >= 'a' && ch <= 'd') {
                userChoice = toupper(ch);
                printf("%c\n", userChoice);
                break;
            }
            else {
                printf("\n������A-D֮���ѡ��: ");
            }
        }

        // �ж�ѡ���Ƿ���ȷ
        int choiceIndex = userChoice - 'A';
        if (options[choiceIndex].isCorrect) {
            printf("\nѡ����ȷ! ��ϲ���1��\n");
            score++;
        }
        else {
            printf("\nѡ�����! ��ȷѡ����: ");
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

        // ��Enter������ESC�˳�
        printf("\n��Enter������ѧϰ����ESC���˳�: ");
        while (1) {
            int ch = getch();
            if (ch == 27) {
                endTime = clock();
                totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
                printf("\n�û�ѡ���˳�ѧϰ...\n");
                goto exitLearn;
            }
            if (ch == '\r') {
                printf("\n");
                break;
            }
        }
    }

    endTime = clock();
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC; // ������ʱ��

exitLearn:
    // ������󵥴��ļ�
    fp1 = fopen("errorwords.txt", "r+");
    if (fp1 == NULL) {

        fp1 = fopen("errorwords.txt", "w");
        if (fp1 == NULL) {
            printf("�޷��������󵥴��ļ�!\n");
            getch();
            return;
        }
        fclose(fp1);
        fp1 = fopen("errorwords.txt", "r+");
    }

    // ��ȡ���д��󵥴�
    while (fscanf(fp1, "%49s\t%199s\t%d\n", error[errorFileCount].english, error[errorFileCount].chinese, &error[errorFileCount].errorcount) != EOF && errorFileCount < 300) {
        errorFileCount++;
    }

    // ��鲢���´��󵥴�
    for (int i = 0; i < errorcount; i++) {
        int found = 0;
        for (int j = 0; j < errorFileCount; j++) {
            if (strcmp(error[j].english, errorwords[i].english) == 0) {
                error[j].errorcount++;
                found = 1;
                break;
            }
        }
        // ����µĴ��󵥴�
        if (!found && errorFileCount < 300) {
            error[errorFileCount] = errorwords[i];
            errorFileCount++;
        }
    }

    // ����д����󵥴��ļ�
    fseek(fp1, 0, SEEK_SET);

    for (int i = 0; i < errorFileCount; i++) {
        fprintf(fp1, "%s\t%s\t%d\n", error[i].english, error[i].chinese, error[i].errorcount);
    }
    fclose(fp1);
    system("cls");
    system("color 07");
    printf("\n\n\t=============== ������ģʽ���� ===============\n");
    printf("\t������: %d\n", total);
    printf("\t��ȷ��: %d\n", total > 0 ? score : 0);
    printf("\t��ȷ��: %.1f%%\n", total > 0 ? (float)score / total * 100 : 0);
    printf("\t����ʱ: %.2f ��\n", totalTime);
    if (total > 0) {
        printf("\tƽ��ÿ����ʱ: %.2f ��\n", totalTime / total);
    }
    printf("\t��������������˵�...\n");
    getch();
}

void exitStudyProgram() {
    system("cls");
    printf("\n\n\t\t�������úܺã��ٽ�����Ŷ��  (^��^)/\n");
    printf("\t\t��������˳�...\n\n");
    getch();
}
//-----------------------------------------------------------------------------------------------

// �˳�����   Powerby ���ڿ�
void exitProgram() {
    system("cls");
    printf("\n\n\n\t\t��л��ʹ�����ǵ�Ӣ����Ӵʵ�!\n\n\t\t�ڴ��������ٴ�������  =^_^=");
    printf("\n\n\t\t��������˳�...\n\n\n");
    getch(); // �ȴ��û�����
}