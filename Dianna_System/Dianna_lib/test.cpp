#include "dictionary.h"

int main(void){
    DICTIONARY dict = DICTIONARY();
    printf("start\n");
    char a[] = "hello";
    printf("start\n");
    char b[] = "test";
    printf("start\n");
    dict.add(a,b);
    printf("start\n");
    dict.print();
    printf("start\n");
}