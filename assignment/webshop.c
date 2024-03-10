#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "webshop.h"

void loadWebshop(struct ProductSet *productSet) {
    productSet->products = malloc(10 * sizeof(struct Product));
    productSet->numProducts = 0;
    productSet->capacity = 10;
}

void insertProduct(struct ProductSet *productSet, const char *name, int price, int quantity) {
    if (productSet->numProducts == productSet->capacity) {
        productSet->capacity *= 2;
        productSet->products = realloc(productSet->products, productSet->capacity * sizeof(struct Product));
    }

    int i;
    for (i = 0; i < productSet->numProducts; ++i) {
        if (strcmp(productSet->products[i].name, name) == 0) {
            productSet->products[i].quantity += quantity;
            return;
        }
    }

    strcpy(productSet->products[i].name, name);
    productSet->products[i].price = price;
    productSet->products[i].quantity = quantity;
    productSet->numProducts++;
}

void loadWebstore(struct ProductSet *webshopStore) {
    char filename[100];
    printf("Enter the name of the file to load the webshop store from: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    while (fscanf(file, "%s %d %d", webshopStore->products[webshopStore->numProducts].name,
                  &webshopStore->products[webshopStore->numProducts].price,
                  &webshopStore->products[webshopStore->numProducts].quantity) == 3) {
        webshopStore->numProducts++;
    }

    fclose(file);
}

void writeFile(const struct ProductSet *productSet) {
    char filename[100];
    printf("Enter the name of the file to write the webshop store to: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < productSet->numProducts; ++i) {
        fprintf(file, "%s %d %d\n", productSet->products[i].name, productSet->products[i].price,
                productSet->products[i].quantity);
    }

    fclose(file);
    printf("Webshop store data has been written to the file '%s' successfully.\n", filename);
}

void toCart(struct ProductSet *cart, const struct ProductSet *webshopStore) {
    char itemName[100];
    int quantity;

    printf("Enter the name of the product to insert to the cart: ");
    scanf("%s", itemName);

    int isFound = 0;
    for (int i = 0; i < webshopStore->numProducts; ++i) {
        if (strcmp(itemName, webshopStore->products[i].name) == 0) {
            isFound = 1;
            printf("Enter the quantity to insert to the cart: ");
            scanf("%d", &quantity);

            if (quantity <= webshopStore->products[i].quantity) {
                insertProduct(cart, itemName, webshopStore->products[i].price, quantity);
                printf("Product(s) added to the cart successfully.\n");
            } else {
                printf("Insufficient quantity in the webshop store.\n");
            }

            break;
        }
    }

    if (!isFound) {
        printf("Product not found in the webshop store.\n");
    }
}

void cartPrice(const struct ProductSet *cart) {
    int totalPrice = 0;

    printf("Cart Contents:\n");
    for (int i = 0; i < cart->numProducts; ++i) {
        printf("%s - Quantity: %d - Price: %d\n", cart->products[i].name, cart->products[i].quantity,
               cart->products[i].price * cart->products[i].quantity);
        totalPrice += cart->products[i].price * cart->products[i].quantity;
    }

    printf("Total Price of Cart: %d\n", totalPrice);
}

void buy(struct ProductSet *webshopStore, struct ProductSet *cart) {
    for (int i = 0; i < cart->numProducts; ++i) {
        for (int j = 0; j < webshopStore->numProducts; ++j) {
            if (strcmp(cart->products[i].name, webshopStore->products[j].name) == 0) {
                if (cart->products[i].quantity <= webshopStore->products[j].quantity) {
                    webshopStore->products[j].quantity -= cart->products[i].quantity;
                    if (webshopStore->products[j].quantity < 0) {
                        webshopStore->products[j].quantity = 0;
                    }

                    printf("Purchase of %d %s(s) was successful.\n", cart->products[i].quantity,
                           cart->products[i].name);
                } else {
                    int lacking = cart->products[i].quantity - webshopStore->products[j].quantity;
                    webshopStore->products[j].quantity = 0;

                    printf("We are sorry, but our store lacks %d %s.\n", lacking, cart->products[i].name);
                }
                break;
            }
        }
    }
}

void freeProductSet(struct ProductSet *productSet) {
    free(productSet->products);
    productSet->numProducts = 0;
    productSet->capacity = 0;
}

