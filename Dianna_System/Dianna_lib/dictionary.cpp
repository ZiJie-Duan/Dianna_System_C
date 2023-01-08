#include "dictionary.h"


DICTIONARY::DICTIONARY(){
    char head_str[] = "head";
    struct DIC_PAGE page;
    page.key = NULL;
    page.value = NULL;
    page.next = NULL;

    head = &page;
    num_page = 1;
}

void DICTIONARY::add(char *key, char *value){
    struct DIC_PAGE page;
    page.key = key;
    page.value = value;
    page.next = NULL;

    struct DIC_PAGE *last_page = head;
    for (int i=0; i<num_page-1; i++){
        last_page = last_page->next;
    }
    last_page->next = &page;
    num_page + 1;

    //printf("here!:::%s\n",head->key);
    // last_page = last_page->next;
    // printf("kill:::%s\n",last_page->key);
}

void DICTIONARY::print(void){
    //only str in keys and values
    printf("\n1");
    printf("here!:::%s\n",head->key);
    struct DIC_PAGE *last_page = head;
    printf("\n1");
    for (int i=0; i<num_page; i++){
        printf("\n2");
        last_page = last_page->next;
        printf("\n2");
        printf("kill:::%s\n",last_page->key);
        printf("\n2");
    }
}