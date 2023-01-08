#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <string.h>

struct DIC_PAGE{
    char *key;
    char *value;
    struct DIC_PAGE *next;
};

class DICTIONARY{

    private:
        struct DIC_PAGE *head;
        int num_page;

    public:
        DICTIONARY(void);
        void add(char *key, char *value);
        void print(void);

};

#endif
