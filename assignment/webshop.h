#ifndef WEBSHOP_H
#define WEBSHOP_H

struct Product {
    char name[100];
    int price;
    int quantity;
};

struct ProductSet {
    struct Product *products;
    int numProducts;
    int capacity;
};

void loadWebshop(struct ProductSet *productSet);
void insertProduct(struct ProductSet *productSet, const char *name, int price, int quantity);
void loadWebstore(struct ProductSet *webshopStore);
void writeFile(const struct ProductSet *productSet);
void toCart(struct ProductSet *cart, const struct ProductSet *webshopStore);
void cartPrice(const struct ProductSet *cart);
void buy(struct ProductSet *webshopStore, struct ProductSet *cart);
void freeProductSet(struct ProductSet *productSet);

#endif
