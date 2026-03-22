#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define max 100
void input(char *str);
void count(char *str, int *vowels, int *consonants);
void display(char *str, int vowels, int consonants);
int main(){
    char str1[max];
    input(str1);
    int vCount=0, cCount=0;
    count(str1, &vCount, &cCount);
    display(str1, vCount, cCount);
    return 0;
}
void input(char *str){
    printf("Enter a string :");
    fgets(str, max, stdin);
    str[strcspn(str, "\n")] = '\0';
}
void count(char *str, int *vowels, int *consonants){
    int i=0;
    char ch;
    while(str[i]!='\0'){
        ch = tolower((unsigned char)str[i]);
        if(isalpha(ch)){
            if(ch == 'a' ||ch == 'e'||ch == 'i'||ch == 'o'||ch == 'u'){
                (*vowels)++;
            }
            else{
                (*consonants)++;
            }
        }
        i++;
    }
}
void display(char *str, int vowels, int consonants){
    printf("\n--- Results ---");
    printf("\nInput String: \"%s\"", str);
    printf("\nVowels:       %d", vowels);
    printf("\nConsonants:   %d\n", consonants);
}