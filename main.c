#include <stdio.h>
#include <string.h>

int main() {
    FILE *f1;
    // we run through the input.txt and count the amount of '\n' -> this value + 1 is equal to the amount of strings in the file
    // but the first line is the given amount of strings, so amountofstrings is the needed value
    f1 = fopen("input.txt", "r");
    int amountofstrings = 0;
    char strings;
    while ((strings = fgetc(f1)) != EOF) {
        if (strings == '\n' || strings == '\0') {
            amountofstrings++;
        }
    }
    amountofstrings--;
    fclose(f1);

    FILE *f2;
    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");
    // reading the necessary number of strings and comparing it with the real one
    int n = 0;
    fscanf(f1, "%d", &n);
    if (amountofstrings != n) {
        fputs("Error in the input.txt", f2);
        fclose(f1);
        fclose(f2);
        return 0;
    }
    // if the number of strings n doesn't suit the terms, we output the error
    if (n > 100 || n < 0) {
        fputs("Error in the input.txt", f2);
        fclose(f1);
        fclose(f2);
        return 0;
    }
    // creating the array for strings, then read them one by one and check whether they consist only of English letters
    // and the first letter is the capital one
    char mas[n][2000];
    for (int i = 0; i < n; ++i) {
        fscanf(f1, "%s", &mas[i]);
        int lengthofstr = 0;
        for (int j = 0; j < 2000; ++j) {
            if (mas[i][j] == '\0' || mas[i][j] == '\n') {
                break;
            }
            lengthofstr++;
        }

        int flag = 0;
        if (mas[i][0] <'A' || mas[i][0] >'Z') { // capital letter check
            flag = 1;
        }
        // English letter check
        for (int j = 1; j < lengthofstr; ++j) {
            if (mas[i][j] < 'a' || mas[i][j] > 'z') {
                flag = 1;
            }
        }
        if (flag == 1) {
            fputs("Error in the input.txt", f2);
            fclose(f1);
            fclose(f2);
            return 0;
        }
    }
    // here we are sorting our mas with strings according to Lexicographic Order
    for (int times = 0; times < n; ++times) {
        for (int i = 0; i < n - 1; ++i) {
            if (strcmp(mas[i], mas[i+1]) > 0) {
                char midres[2000];
                strcpy(midres, mas[i]);
                strcpy(mas[i], mas[i+1]);
                strcpy(mas[i+1], midres);
            }
        }
    }
    // outputing the sorted strings in the file 
    for (int i = 0; i < n; ++i) {
        fputs(mas[i], f2);
        fputs("\n", f2);
    }

    fclose(f1);
    fclose(f2);
}
