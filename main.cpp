#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>

struct product {
    char prod_name[10];
    int price;
    int quantity;
};

struct category {
    char cat_name[10];
    int prod_count;
    struct product products[3];
};

struct store {
    int cat_count;
    struct category categories[3];
};
//intialize
void initialization(struct store *s) {
    s->cat_count = 3;

    for (int i = 0; i < 3; i++) {
        printf("Enter category name: ");
        scanf("%s", s->categories[i].cat_name);
        printf("Enter product count for %s: ", s->categories[i].cat_name);
        scanf("%d", &s->categories[i].prod_count);

        for (int j = 0; j < s->categories[i].prod_count; j++) {
            printf("Enter product name for %s - product %d: ", s->categories[i].cat_name, j + 1);
            scanf("%s", s->categories[i].products[j].prod_name);
            printf("Enter price for %s - product %d: ", s->categories[i].cat_name, j + 1);
            scanf("%d", &s->categories[i].products[j].price);
            printf("Enter quantity for %s - product %d: ", s->categories[i].cat_name, j + 1);
            scanf("%d", &s->categories[i].products[j].quantity);
        }
    }
}
//display
void display(struct store *s) {
    for (int i = 0; i < s->cat_count; i++) {
        printf("Category: %s\n", s->categories[i].cat_name);
        printf("Product Count: %d\n", s->categories[i].prod_count);

        for (int j = 0; j < s->categories[i].prod_count; j++) {
            printf("  Product %d: %s\n", j + 1, s->categories[i].products[j].prod_name);
            printf("    Price: %d\n", s->categories[i].products[j].price);
            printf("    Quantity: %d\n", s->categories[i].products[j].quantity);
        }
        printf("\n");
    }
}
//add category
void add_category(struct store *s){
char new_cat[10];
int cat_count=0;
 if ( s->cat_count<10)
 {
         printf("enter new name category");
         scanf("%s", new_cat);
         strcpy(s->categories[s->cat_count].cat_name, new_cat);

        s->cat_count++;
 }
     s->cat_count++;
}
//remove category
void remove_category(struct store *s) {
    char cat_to_remove[10];

    if (s->cat_count > 0) {
        printf("Enter the name of the category to remove: ");
        scanf("%s", cat_to_remove);

        int index = -1;
        for (int i = 0; i < s->cat_count; i++) {
            if (strcmp(s->categories[i].cat_name, cat_to_remove) == 0) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            for (int i = index; i < s->cat_count - 1; i++) {
                strcpy(s->categories[i].cat_name, s->categories[i + 1].cat_name);
            }

            s->cat_count--;

            printf("Category '%s' removed successfully.\n", cat_to_remove);
        } else {
            printf("Category '%s' not found.\n", cat_to_remove);
        }
    } else {
        printf("No categories to remove.\n");
    }
}

//add product
void add_product(struct store *s) {
    char p_name[10] ,c_name[10];
    int price, quantity ;

    printf("Enter product Name: ");
    scanf("%s", p_name);

    printf("Enter category Name: ");
    scanf("%s", c_name);

    printf("Enter product price: ");
    scanf("%d", &price);

    printf("Enter product quantity: ");
    scanf("%d", &quantity);

    int cat_index = -1;
    for (int i = 0; i < s->cat_count; i++) {
        if (strcmp(s->categories[i].cat_name, c_name) == 0) {
            cat_index = i;
            break;
        }
    }

    if (cat_index != -1 && s->categories[cat_index].prod_count< 10)
{
         strcpy(s->categories[cat_index].products[s->categories[cat_index].prod_count].prod_name, p_name);

            s->categories[cat_index].products[s->categories[cat_index].prod_count].price = price;
             s->categories[cat_index].products[s->categories[cat_index].prod_count].quantity = quantity;

        s->categories[cat_index].prod_count++;

        printf("Product '%s' added successfully to category '%s'.\n", p_name, c_name);
    } else {
        printf("Category not found or maximum number of products reached for the selected category.\n");
    }
}

//remove product
void remove_product(struct store *s) {
    char p_name[10], c_name[10];

    printf("Enter category Name: ");
    scanf("%s", c_name);

    printf("Enter product Name to remove: ");
    scanf("%s", p_name);

    int cat_index = -1;
    for (int i = 0; i < s->cat_count; i++) {
        if (strcmp(s->categories[i].cat_name, c_name) == 0) {
            cat_index = i;
            break;
        }
    }

    if (cat_index != -1) {
        int prod_index = -1;
        for (int i = 0; i < s->categories[cat_index].prod_count; i++) {
            if (strcmp(s->categories[cat_index].products[i].prod_name, p_name) == 0) {
                prod_index = i;
                break;
            }
        }

        if (prod_index != -1) {
            // Shifting
            for (int i = prod_index; i < s->categories[cat_index].prod_count - 1; i++) {
                strcpy(s->categories[cat_index].products[i].prod_name, s->categories[cat_index].products[i + 1].prod_name);
                s->categories[cat_index].products[i].price = s->categories[cat_index].products[i + 1].price;
                s->categories[cat_index].products[i].quantity = s->categories[cat_index].products[i + 1].quantity;
            }

            // Clear the last product
            strcpy(s->categories[cat_index].products[s->categories[cat_index].prod_count - 1].prod_name, "");
            s->categories[cat_index].products[s->categories[cat_index].prod_count - 1].price = 0;
            s->categories[cat_index].products[s->categories[cat_index].prod_count - 1].quantity = 0;

            s->categories[cat_index].prod_count--;

            printf("Product '%s' removed successfully from category '%s'.\n", p_name, c_name);
        } else {
            printf("Product '%s' not found in category '%s'.\n", p_name, c_name);
        }
    } else {
        printf("Category '%s' not found.\n", c_name);
    }
}



//move
void move_product(struct store *s) {
    char product_name[10];
    char source_category[10];
    char target_category[10];
    printf("\nEnter the name of the product to move: ");
    scanf("%s", product_name);

    printf("Enter the source category: ");
    scanf("%s", source_category);

    printf("Enter the target category: ");
    scanf("%s", target_category);

    int source_index = -1;
    int target_index = -1;

    for (int i = 0; i < s->cat_count; i++) {
        if (strcmp(s->categories[i].cat_name, source_category) == 0) {
            source_index = i;
            break;
        }
    }

    if (source_index != -1) {
        for (int i = 0; i < s->cat_count; i++) {
            if (strcmp(s->categories[i].cat_name, target_category) == 0) {
                target_index = i;
                break;
            }
        }

        if (target_index != -1) {
            int product_index = -1;

            for (int i = 0; i < s->categories[source_index].prod_count; i++) {
                if (strcmp(s->categories[source_index].products[i].prod_name, product_name) == 0) {
                    product_index = i;
                    break;
                }
            }

            if (product_index != -1) {
                strcpy(s->categories[target_index].products[s->categories[target_index].prod_count].prod_name, product_name);
                s->categories[target_index].products[s->categories[target_index].prod_count].price = s->categories[source_index].products[product_index].price;
                s->categories[target_index].products[s->categories[target_index].prod_count].quantity = s->categories[source_index].products[product_index].quantity;
                s->categories[target_index].prod_count++;

                for (int i = product_index; i < s->categories[source_index].prod_count - 1; i++) {
                    strcpy(s->categories[source_index].products[i].prod_name, s->categories[source_index].products[i + 1].prod_name);
                    s->categories[source_index].products[i].price = s->categories[source_index].products[i + 1].price;
                    s->categories[source_index].products[i].quantity = s->categories[source_index].products[i + 1].quantity;
                }

                s->categories[source_index].prod_count--;

                printf("Product '%s' moved successfully from '%s' to '%s'.\n", product_name, source_category, target_category);
            } else {
                printf("Product '%s' not found in the source category '%s'.\n", product_name, source_category);
            }
        } else {
            printf("Target category '%s' not found.\n", target_category);
        }
    } else {
        printf("Source category '%s' not found.\n", source_category);
    }
}

//sell
void sell(struct store *s) {
    char product_name[10];
    char category_name[10];
    int quantity_to_sell;

    // Display categories for user reference
    printf("Categories:\n");
    for (int i = 0; i < s->cat_count; i++) {
        printf("%d. %s\n", i + 1, s->categories[i].cat_name);
    }

    // Get user input for product name, category, and quantity to sell
    printf("\nEnter the name of the product to sell: ");
    scanf("%s", product_name);

    printf("Enter the category: ");
    scanf("%s", category_name);

    printf("Enter the quantity to sell: ");
    scanf("%d", &quantity_to_sell);

    int category_index = -1;

    // Find the index of the specified category
    for (int i = 0; i < s->cat_count; i++) {
        if (strcmp(s->categories[i].cat_name, category_name) == 0) {
            category_index = i;
            break;
        }
    }

    if (category_index != -1) {
        int product_index = -1;

        // Find the index of the specified product in the category
        for (int i = 0; i < s->categories[category_index].prod_count; i++) {
            if (strcmp(s->categories[category_index].products[i].prod_name, product_name) == 0) {
                product_index = i;
                break;
            }
        }

        if (product_index != -1) {
            // Check if there is enough quantity to sell
            if (s->categories[category_index].products[product_index].quantity >= quantity_to_sell) {
                // Update the quantity and inform the user about the sale
                s->categories[category_index].products[product_index].quantity -= quantity_to_sell;
                printf("Sold %d units of '%s' from category '%s'.\n", quantity_to_sell, product_name, category_name);
            } else {
                printf("Insufficient quantity available for '%s' in category '%s'.\n", product_name, category_name);
            }
        } else {
            printf("Product '%s' not found in category '%s'.\n", product_name, category_name);
        }
    } else {
        printf("Category '%s' not found.\n", category_name);
    }
}


int getChoice() {
    int choice;
    while (1) {
        printf("Enter your choice: ");
        int result = scanf("%d", &choice);

        if (result == 1) {
            // Valid integer input
            break;
        } else {
            // Clear input buffer
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
        }
    }
    return choice;
}



int main() {
    struct store myStore;
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Initialize data\n");
        printf("2. Display data\n");
        printf("3. add_category\n");
        printf("4. remove_category\n");
        printf("5. add_product\n");
        printf("6. remove_product\n");
        printf("7. move_product\n");
        printf("8. sell\n");
        printf("9. Exit\n");

        choice = getChoice();

        switch (choice) {
            case 1:
                initialization(&myStore);
                break;
            case 2:
                display(&myStore);
                break;
            case 3:
                add_category(&myStore);
                break;
            case 4:
                remove_category(&myStore);
                break;
            case 5:
                add_product(&myStore);
                break;
            case 6:
                remove_product(&myStore);
                break;
            case 7:
                move_product(&myStore);
                break;
            case 8:
                sell(&myStore);
                break;
            case 9:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 9);

    return 0;
}
