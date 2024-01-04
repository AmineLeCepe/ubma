#include <stdio.h>

// Global variables

int prod;

struct product{
    int quantity;
    int unit_price;
    int danger;
    int date[3];
};

struct product catalog[30];

// Functions

void prod_info(){ // Checking product information
    do {
        scanf("%d", &prod);
    } while (prod<0 || prod>29);
    if (catalog[prod].date[1]==0){
        printf("There is no product with that code. Please retry with an existing product or add a new one.\n");
    } else {
        printf("Quantity: %d units\n", catalog[prod].quantity);
        printf("Unit price: %d$\n", catalog[prod].unit_price);
        printf("Dangerous? : ");
        if (catalog[prod].danger == 1){
            printf("Yes\n");
        } else {
            printf("No\n");
        }
        printf("Date of product: ");
        for(int i=0; i<3; i++){
            printf("%d/", catalog[prod].date[i]);
        }
    }
}

void prod_add(){ // Adds a new product to the catalog
    int confirm;

    printf("Product code? \n");
    do{
        scanf("%d", &prod);
    }while(prod<0 || prod>29);
    if(catalog[prod].date[1]!=0){
        printf("Product exists. Overwriting... \n");
    }
    printf("Quantity? \n");
    do{
        scanf("%d", &catalog[prod].quantity);
    } while(catalog[prod].quantity<0);
    printf("Unit price? \n");
    do {
        scanf("%d", &catalog[prod].unit_price);
    } while(catalog[prod].unit_price<0);
    printf("Dangerous? (1 if yes, 0 if no) \n");
    do{
        scanf("%d", &catalog[prod].danger);
    } while(catalog[prod].danger < 0 || catalog[prod].danger > 1);
    printf("Date? (DD/MM/YYYY)\n");
    printf("Year: \n");
    do {
        scanf("%d", &catalog[prod].date[2]);
    } while(catalog[prod].date[2]<0);
    printf("Month:\n");
    do {
        scanf("%d", &catalog[prod].date[1]);
    } while(catalog[prod].date[1]<0 || catalog[prod].date[1]>12);
    printf("Day: \n");
    do {
        scanf("%d", &catalog[prod].date[0]);
    } while(catalog[prod].date[0]<0 || catalog[prod].date[0]>31);
}

void qt_add(){
    int units;

    scanf("%d", &prod);
    if(catalog[prod].date[1] == 0){
        printf("Product does not exist, please add it first. \n");
    } else {
        printf("How much units do you want to add to that product? %d units currently in stock\n", catalog[prod].quantity);
        scanf("%d", &units);
        catalog[prod].quantity = catalog[prod].quantity + units;
        printf("Added %d units, for a total of %d units. \n", units, catalog[prod].quantity);
    }
}

void show_danger(){ // Shows dangerous products' code and quantity of each of them, as well as their total.
    int danger_count = 0;

    printf("The codes of the dangerous products are as well as their respective quantity: ");
    for(int i=0; i<30; i++){
        if(catalog[i].danger == 1){
            printf("%d: %d, ", i, catalog[i].quantity);
            danger_count++;
        }
    }
    printf("\n");
    printf("The number of dangerous product sets: %d\n", danger_count);
}

void total_price(){ // Calculates the price of all products
    int total_price=0;

    for(int i=0; i<30; i++){
        total_price= catalog[i].unit_price*catalog[i].quantity + total_price;
    }
    printf("Total price: %d$ \n", total_price);
}

void prod_remove(){ // Removes a product and fills empty cells
    // Part 1: product removal
    scanf("%d", &prod);
    printf("Emptying product %d's information... \n", prod);
    catalog[prod].quantity=0;
    catalog[prod].unit_price=0;
    catalog[prod].danger=0;
    catalog[prod].date[0]=0;
    catalog[prod].date[1]=0;
    catalog[prod].date[2]=0;

    // Part 2: filling empty cells
    printf("Filling empty cells... \n");
    for(int i=prod; i<30; i++){
        catalog[i].quantity=catalog[i+1].quantity;
        catalog[i].unit_price=catalog[i+1].unit_price;
        catalog[i].danger=catalog[i+1].danger;
        catalog[i].date[0]=catalog[i+1].date[0];
        catalog[i].date[1]=catalog[i+1].date[1];
        catalog[i].date[2]=catalog[i+1].date[2];
    }
    printf("Operation completed.\n\n");
}

void prod_remove_old(){ // Removing products made before 1990 and filling empty cells

    // Part 1: Removing products made before 1990
    printf("Removing obsolete products... \n");
    for(int i=0; i<30; i++){
        if(catalog[i].date[2]<1990){
            catalog[i].quantity=0;
            catalog[i].unit_price=0;
            catalog[i].danger=0;
            catalog[i].date[0]=0;
            catalog[i].date[1]=0;
            catalog[i].date[2]=0;
        }
    }
    // Part 2: filling empty cells
    printf("Filling empty cells... \n");
    for(int i=0; i<29; i++){
        if(catalog[i].date[0]==0){
            catalog[i].quantity=catalog[i+1].quantity;
            catalog[i].unit_price=catalog[i+1].unit_price;
            catalog[i].danger=catalog[i+1].danger;
            catalog[i].date[0]=catalog[i+1].date[0];
            catalog[i].date[1]=catalog[i+1].date[1];
            catalog[i].date[2]=catalog[i+1].date[2];
        }
    }
}

void menu(){  // Menu
    int entry;

    do {
        // Possible entries start

        printf("\n\n");
        printf("1: Get info on a product (0-29) \n");
        printf("2: Add a new product \n");
        printf("3: Add a quantity to a product \n");
        printf("4: Show dangerous products and their details \n");
        printf("5: Show the total price of the catalog \n");
        printf("6: Remove a product \n");
        printf("7: Remove products made before 1990 \n");
        printf("\n\n0: Exit program \n");


        scanf("%d", &entry);

        // Possible entries end

        // Processing entry start

        switch(entry) {
            case 0:
                printf("Exiting program... \n");
                break;
            case 1:
                printf("Enter the number of the product you want to get info about:\n");
                prod_info();
                break;
            case 2:
                printf("Enter the information about the product you'd like to add: \n");
                prod_add();
                break;
            case 3:
                printf("Which product's stock do you want to refill ? (Enter it's code) \n");
                qt_add();
                break;
            case 4:
                printf("Showing dangerous products and their details... \n");
                show_danger();
                break;
            case 5:
                printf("Calculating total price... \n");
                total_price();
                break;
            case 6:
                printf("Which product would you like to remove ?");
                prod_remove();
                break;
            case 7:
                printf("Removing obsolete products...");
                prod_remove_old();
                break;
            default:;
        }



    } while(entry !=0);
}

void save_data() { // Saves variables in a text file
    FILE *file = fopen("product_data.txt", "w");

    if (file != NULL) {
        for (int i = 0; i < 30; i++) {
            fprintf(file, "%d %d %d %d %d %d %d\n", catalog[i].quantity, catalog[i].unit_price, catalog[i].danger, catalog[i].date[0], catalog[i].date[1], catalog[i].date[2], i);
        }

        fclose(file);
        printf("Data saved successfully.\n");
    } else {
        printf("Error opening file for writing.\n");
    }
}

void load_data() { // Loads variables from the text file
    FILE *file = fopen("product_data.txt", "r");

    if (file != NULL) {
        int temp_quantity, temp_unit_price, temp_danger, temp_date_0, temp_date_1, temp_date_2, temp_prod;

        while (fscanf(file, "%d %d %d %d %d %d %d", &temp_quantity, &temp_unit_price, &temp_danger, &temp_date_0, &temp_date_1, &temp_date_2, &temp_prod) == 7) {
            catalog[temp_prod].quantity = temp_quantity;
            catalog[temp_prod].unit_price = temp_unit_price;
            catalog[temp_prod].danger = temp_danger;
            catalog[temp_prod].date[0] = temp_date_0;
            catalog[temp_prod].date[1] = temp_date_1;
            catalog[temp_prod].date[2] = temp_date_2;
        }

        fclose(file);
        printf("Data loaded successfully.\n");
    } else {
        printf("Error opening file for reading.\n");
    }
}

// Main shit

int main(){

    // Loading data

    load_data();

    // Program start

    menu();

    // Saving data before closing

    save_data();

    return 0;
}
