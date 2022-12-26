#include <stdio.h>

struct book {
    char name[40];
    float price;
    float quantity;
    struct book *next;
};


int main(void){
    struct book b1 = {.name="Happy Every Day",
    .price = 30};
    b1.quantity = 20;
    struct book b2 = {.price = 10, .quantity=29};
    b1.next = &b2;

    printf("%f",b1.next->price);

    getchar();
    
}
