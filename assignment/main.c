#include <stdio.h>
#include "webshop.h"

int main() {
    struct ProductSet webshopStore, cart;
    loadWebshop(&webshopStore);
    loadWebshop(&cart);

    printf("\n****************************************************************************");
    printf("\n\n                         WELCOME TO MY SHOP!\n");
    printf("\n****************************************************************************\n");

    int choice;
    do {
        printf("\n\tMenu:\n\n");
        printf("\t1. Load webshop store from a file\n");
        printf("\t2. Write the content of the store to a file\n");
        printf("\t3. Insert an item to cart\n");
        printf("\t4. Get the price of cart\n");
        printf("\t5. Buy the products\n");
        printf("\t6. Exit\n\n");
        printf("\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                loadWebstore(&webshopStore);
                break;
            case 2:
                writeFile(&webshopStore);
                break;
            case 3:
                toCart(&cart, &webshopStore);
                break;
            case 4:
                cartPrice(&cart);
                break;
            case 5:
                buy(&webshopStore, &cart);
                break;
            case 6:
                break;
            default:
                printf("Invalid choice. Pleasw try again.\n");
        }
    } while (choice != 6);

    freeProductSet(&webshopStore);
    freeProductSet(&cart);

    return 0;
}
