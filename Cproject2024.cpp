#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user {
    char username[50];
    char password[50];
    char pincode[10];
};

struct question {
    char questiont[200];
    char options[4][100];
    char correctOption;
};

void registerf();
int loginf();
void forgotPassword();
void addQuestion();
void takeQuiz();
int getQn();
void deleteAccount();
void deleteQuestion();
void showAllUsers();

int main() {
    int choice;
    int loggedIn = 0;

    printf("\n\t\t\tWELCOME TO OUR QUIZ BANK\n");
    printf("\t\t\tPLEASE REGISTER FIRST IF YOU ARE NEW USER\n");

    while (!loggedIn) {
        printf("\n1: Register\n2: Login\n3: Forgot Password\n4: Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                registerf();
                break;
            case 2:
                if (loginf()) {
                    printf("Login successful\n");
                    loggedIn = 1;
                } else {
                    printf("No username or pin code matching\n");
                }
                break;
            case 3:
                forgotPassword();
                break;
            case 4:
                printf("Thank you for using our quiz bank. Goodbye!\n");
                exit(0);
            default:
                printf("Not a valid choice\n");
        }
    }

    while (1) {
        printf("\n1: Add Question\n2: Take Quiz\n3: Delete Account\n4: Delete Question\n5: Show All Users\n6: Logout\n7: Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                addQuestion();
                break;
            case 2:
                takeQuiz();
                break;
            case 3:
                deleteAccount();
                break;
            case 4:
                deleteQuestion();
                break;
            case 5:
                showAllUsers();
                break;
            case 6:
                loggedIn = 0;
                main(); 
                break;
            case 7:
                printf("Thank you for using our quiz bank. Goodbye!\n");
                exit(0);
            default:
                printf("Not a valid choice\n");
        }
    }
}

void registerf() {
    FILE *ptr;
    struct user s;
    ptr = fopen("kist23.txt", "a");
    if (ptr == NULL) {
        printf("File not opened");
        exit(1);
    }
    printf("Enter username: \n");
    scanf("%s", s.username);
    getchar();
    printf("Enter password: \n");
    scanf("%s", s.password);
    getchar();
    printf("Enter pin code: \n");
    scanf("%s", s.pincode);
    getchar();
    fwrite(&s, sizeof(struct user), 1, ptr);
    fclose(ptr);
    printf("Welcome to our quiz family: \n");
}

int loginf() {
    FILE *ptr;
    struct user s;
    char username[100], password[50], pincode[10];
    int a = 0;
    ptr = fopen("kist23.txt", "r");
    if (ptr == NULL) {
        printf("File not opening: ");
        exit(1);
    }
    printf("Enter username: ");
    scanf("%s", username);
    getchar();
    printf("Enter password: ");
    scanf("%s", password);
    getchar();
    printf("Enter pin code: ");
    scanf("%s", pincode);
    getchar();
    while (fread(&s, sizeof(struct user), 1, ptr)) {
        if (strcmp(s.username, username) == 0 && strcmp(s.password, password) == 0 && strcmp(s.pincode, pincode) == 0) {
            a = 1;
            break;
        }
    }
    fclose(ptr);
    return a;
}

void forgotPassword() {
    FILE *ptr, *temp;
    struct user s;
    char username[50], newPassword[50], pincode[10];
    int found = 0;
    ptr = fopen("kist23.txt", "r");
    temp = fopen("BIT24.txt", "w");
    if (ptr == NULL || temp == NULL) {
        printf("Not opening file\n");
        return;
    }
    printf("Enter username: ");
    scanf("%s", username);
    getchar();
    printf("Enter pin code: ");
    scanf("%s", pincode);
    getchar();
    while (fread(&s, sizeof(struct user), 1, ptr)) {
        if (strcmp(s.username, username) == 0 && strcmp(s.pincode, pincode) == 0) {
            found = 1;
            printf("Enter new password: ");
            scanf("%s", newPassword);
            getchar();
            strcpy(s.password, newPassword);
        }
        fwrite(&s, sizeof(struct user), 1, temp);
    }
    fclose(ptr);
    fclose(temp);
    ptr = fopen("kist23.txt", "w");
    temp = fopen("BIT24.txt", "r");
    while (fread(&s, sizeof(struct user), 1, temp)) {
        fwrite(&s, sizeof(struct user), 1, ptr);
    }
    fclose(ptr);
    fclose(temp);
    if (found) {
        printf("Password reset success\n");
    } else {
        printf("Username or pin code not found\n");
    }
}

void addQuestion() {
    FILE *ptr;
    struct question q;
    ptr = fopen("questions123.txt", "a");
    if (ptr == NULL) {
        printf("File not opened");
        exit(1);
    }
    printf("Enter question: \n");
    scanf(" %[^\n]s", q.questiont);
    for (int i = 0; i < 4; i++) {
        printf("Enter option %c: \n", 'A' + i);
        scanf(" %[^\n]s", q.options[i]);
    }
    printf("Enter correct option (A/B/C/D): \n");
    scanf(" %c", &q.correctOption);
    getchar();
    fwrite(&q, sizeof(struct question), 1, ptr);
    fclose(ptr);
    printf("Question added successfully\n");
}

int getQn() {
    FILE *ptr;
    struct question q;
    int count = 0;
    ptr = fopen("questions123.txt", "r");
    if (ptr == NULL) {
        return 0;
    }
    while (fread(&q, sizeof(struct question), 1, ptr)) {
        count++;
    }
    fclose(ptr);
    return count;
}

void takeQuiz() {
    FILE *ptr;
    struct question q;
    int numQn = getQn();
    int score = 0;
    if (numQn == 0) {
        printf("No questions available in the quiz bank.\n");
        return;
    }
    int numQnT;
    if (numQn > 5) {
        numQnT = 5;
    } else {
        numQnT = numQn;
    }
    ptr = fopen("questions123.txt", "r");
    if (ptr == NULL) {
        printf("File not opened\n");
        return;
    }
    for (int i = 0; i < numQnT; i++) {
        fread(&q, sizeof(struct question), 1, ptr);
        printf("%d: %s\n", i + 1, q.questiont);
        for (int k = 0; k < 4; k++) {
            printf("%c: %s\n", 'A' + k, q.options[k]);
        }
        char answer;
        printf("Please select your answer: ");
        scanf(" %c", &answer);
        getchar();
        if (answer == q.correctOption) {
            score++;
        } else {
            printf("Wrong answer. The correct answer is: %c\n", q.correctOption);
        }
    }
    fclose(ptr);
    printf("Quiz completed. Your score: %d/%d\n", score, numQnT);
}

void deleteAccount() {
    FILE *ptr, *temp;
    struct user s;
    char username[50], password[50], pincode[10];
    int found = 0;
    ptr = fopen("kist23.txt", "r");
    temp = fopen("BIT24.txt", "w");
    if (ptr == NULL || temp == NULL) {
        printf("Not opening file\n");
        return;
    }
    printf("Enter username to delete: ");
    scanf("%s", username);
    getchar();
    printf("Enter password to confirm: ");
    scanf("%s", password);
    getchar();
    printf("Enter pin code: ");
    scanf("%s", pincode);
    getchar();
    while (fread(&s, sizeof(struct user), 1, ptr)) {
        if (strcmp(s.username, username) == 0 && strcmp(s.password, password) == 0 && strcmp(s.pincode, pincode) == 0) {
            found = 1;
            printf("Account deleted successfully\n");
            continue;
        }
        fwrite(&s, sizeof(struct user), 1, temp);
    }
    fclose(ptr);
    fclose(temp);
    ptr = fopen("kist23.txt", "w");
    temp = fopen("BIT24.txt", "r");
    while (fread(&s, sizeof(struct user), 1, temp)) {
        fwrite(&s, sizeof(struct user), 1, ptr);
    }
    fclose(ptr);
    fclose(temp);
    if (!found) {
        printf("Username, password, or pin code combination not found\n");
    }
}

void deleteQuestion() {
    FILE *ptr, *temp;
    struct question q;
    char question[200];
    int found = 0;
    ptr = fopen("questions123.txt", "r");
    temp = fopen("BIT24.txt", "w");
    if (ptr == NULL || temp == NULL) {
        printf("Error opening file\n");
        return;
    }
    printf("Enter the question to delete: ");
    scanf(" %[^\n]s", question);
    getchar();
    while (fread(&q, sizeof(struct question), 1, ptr)) {
        if (strcmp(q.questiont, question) == 0) {
            found = 1;
            printf("Question deleted successfully\n");
            continue;
        }
        fwrite(&q, sizeof(struct question), 1, temp);
    }
    fclose(ptr);
    fclose(temp);
    ptr = fopen("questions123.txt", "w");
    temp = fopen("BIT24.txt", "r");
    while (fread(&q, sizeof(struct question), 1, temp)) {
        fwrite(&q, sizeof(struct question), 1, ptr);
    }
    fclose(ptr);
    fclose(temp);
    if (!found) {
        printf("Question not found\n");
    }
}

void showAllUsers() {
    FILE *ptr;
    struct user s;
    ptr = fopen("kist23.txt", "r");
    if (ptr == NULL) {
        printf("File not opened");
        exit(1);
    }
    printf("\nList of all users:\n");
    while (fread(&s, sizeof(struct user), 1, ptr)) {
        printf("Username: %s, Password: %s, Pin code: %s\n", s.username, s.password, s.pincode);
    }
    fclose(ptr);
}
