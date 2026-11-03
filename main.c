#include <stdio.h>
#include <string.h>

#define MAX 100

// Structure for item information
struct ItemDetails {
    char name[50];
    char category[30];
    char description[100];
    char location[50];
    char date[20];
};

// Separate structure for lost items
struct LostItem {
    int id;
    struct ItemDetails item;
    int status;
};

// Separate structure for found items
struct FoundItem {
    int id;
    struct ItemDetails item;
    int status;
};

// Function declarations
void addLostItem();
void addFoundItem();

int loadLostItems(struct LostItem lost[]);
int loadFoundItems(struct FoundItem found[]);

void saveLostItems(struct LostItem lost[], int n);
void saveFoundItems(struct FoundItem found[], int n);

void getDetails(struct ItemDetails *item);
void displayDetails(struct ItemDetails item);

void viewLostItems();
void viewFoundItems();

void searchItems();
void matchItems();

void returnItem();
void displayStatistics();

void showStatus(int status);


// MAIN FUNCTION
int main()
{
    int choice;

    do {
        printf("\n====================================");
        printf("\n   COLLEGE LOST AND FOUND SYSTEM");
        printf("\n====================================");

        printf("\n1. Report Lost Item");
        printf("\n2. Report Found Item");
        printf("\n3. View Lost Items");
        printf("\n4. View Found Items");
        printf("\n5. Search Item");
        printf("\n6. Match Lost and Found Items");
        printf("\n7. Mark Item as Returned");
        printf("\n8. Display Statistics");
        printf("\n0. Exit");

        printf("\n====================================");
        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input!\n");

            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        switch (choice) {

            case 1:
                addLostItem();
                break;

            case 2:
                addFoundItem();
                break;

            case 3:
                viewLostItems();
                break;

            case 4:
                viewFoundItems();
                break;

            case 5:
                searchItems();
                break;

            case 6:
                matchItems();
                break;

            case 7:
                returnItem();
                break;

            case 8:
                displayStatistics();
                break;

            case 0:
                printf("\nThank you for using our system!\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 0);

    return 0;
}


// FUNCTION TO INPUT ITEM DETAILS
void getDetails(struct ItemDetails *item)
{
    printf("\nEnter item name: ");
    scanf(" %49[^\n]", item->name);

    printf("Enter category: ");
    scanf(" %29[^\n]", item->category);

    printf("Enter description: ");
    scanf(" %99[^\n]", item->description);

    printf("Enter location: ");
    scanf(" %49[^\n]", item->location);

    printf("Enter date (DD-MM-YYYY): ");
    scanf(" %19[^\n]", item->date);

    while (getchar() != '\n');
}


// FUNCTION TO DISPLAY ITEM DETAILS
void displayDetails(struct ItemDetails item)
{
    printf("\nItem Name   : %s", item.name);
    printf("\nCategory    : %s", item.category);
    printf("\nDescription : %s", item.description);
    printf("\nLocation    : %s", item.location);
    printf("\nDate        : %s", item.date);
}


// DISPLAY STATUS
void showStatus(int status)
{
    if (status == 1)
        printf("Open");
    else if (status == 2)
        printf("Returned");
}


// LOAD LOST ITEMS FROM FILE
int loadLostItems(struct LostItem lost[])
{
    FILE *fp;
    int n = 0;

    fp = fopen("lost.txt", "r");

    if (fp == NULL)
        return 0;

    while (n < MAX &&
        fscanf(fp,
        "%d|%49[^|]|%29[^|]|%99[^|]|%49[^|]|%19[^|]|%d",
        &lost[n].id,
        lost[n].item.name,
        lost[n].item.category,
        lost[n].item.description,
        lost[n].item.location,
        lost[n].item.date,
        &lost[n].status) == 7) {

        n++;
    }

    fclose(fp);
    return n;
}


// LOAD FOUND ITEMS FROM FILE
int loadFoundItems(struct FoundItem found[])
{
    FILE *fp;
    int n = 0;

    fp = fopen("found.txt", "r");

    if (fp == NULL)
        return 0;

    while (n < MAX &&
        fscanf(fp,
        "%d|%49[^|]|%29[^|]|%99[^|]|%49[^|]|%19[^|]|%d",
        &found[n].id,
        found[n].item.name,
        found[n].item.category,
        found[n].item.description,
        found[n].item.location,
        found[n].item.date,
        &found[n].status) == 7) {

        n++;
    }

    fclose(fp);
    return n;
}


// SAVE LOST ITEMS TO FILE
void saveLostItems(struct LostItem lost[], int n)
{
    FILE *fp;
    int i;

    fp = fopen("lost.txt", "w");

    if (fp == NULL) {
        printf("\nFile opening error!\n");
        return;
    }

    for (i = 0; i < n; i++) {

        fprintf(fp,
        "%d|%s|%s|%s|%s|%s|%d\n",
        lost[i].id,
        lost[i].item.name,
        lost[i].item.category,
        lost[i].item.description,
        lost[i].item.location,
        lost[i].item.date,
        lost[i].status);
    }

    fclose(fp);
}


// SAVE FOUND ITEMS TO FILE
void saveFoundItems(struct FoundItem found[], int n)
{
    FILE *fp;
    int i;

    fp = fopen("found.txt", "w");

    if (fp == NULL) {
        printf("\nFile opening error!\n");
        return;
    }

    for (i = 0; i < n; i++) {

        fprintf(fp,
        "%d|%s|%s|%s|%s|%s|%d\n",
        found[i].id,
        found[i].item.name,
        found[i].item.category,
        found[i].item.description,
        found[i].item.location,
        found[i].item.date,
        found[i].status);
    }

    fclose(fp);
}


// ADD LOST ITEM
void addLostItem()
{
    struct LostItem lost[MAX];
    int n, i;

    n = loadLostItems(lost);

    if (n >= MAX) {
        printf("\nMaximum records reached!\n");
        return;
    }

    if (n == 0)
        i = 1001;
    else
        i = lost[n - 1].id + 1;

    lost[n].id = i;
    lost[n].status = 1;

    printf("\n===== REPORT LOST ITEM =====\n");

    getDetails(&lost[n].item);

    n++;

    saveLostItems(lost, n);

    printf("\nLost item registered successfully!");
    printf("\nYour Lost Item ID is: %d\n", i);
}


// ADD FOUND ITEM
void addFoundItem()
{
    struct FoundItem found[MAX];
    int n, i;

    n = loadFoundItems(found);

    if (n >= MAX) {
        printf("\nMaximum records reached!\n");
        return;
    }

    if (n == 0)
        i = 2001;
    else
        i = found[n - 1].id + 1;

    found[n].id = i;
    found[n].status = 1;

    printf("\n===== REPORT FOUND ITEM =====\n");

    getDetails(&found[n].item);

    n++;

    saveFoundItems(found, n);

    printf("\nFound item registered successfully!");
    printf("\nYour Found Item ID is: %d\n", i);
}


// VIEW ALL LOST ITEMS
void viewLostItems()
{
    struct LostItem lost[MAX];
    int n, i;

    n = loadLostItems(lost);

    printf("\n========== LOST ITEMS ==========\n");

    if (n == 0) {
        printf("\nNo lost items found.\n");
        return;
    }

    for (i = 0; i < n; i++) {

        printf("\nLost Item ID: %d", lost[i].id);

        displayDetails(lost[i].item);

        printf("\nStatus: ");
        showStatus(lost[i].status);

        printf("\n--------------------------------");
    }

    printf("\nTotal Lost Items: %d\n", n);
}


// VIEW ALL FOUND ITEMS
void viewFoundItems()
{
    struct FoundItem found[MAX];
    int n, i;

    n = loadFoundItems(found);

    printf("\n========== FOUND ITEMS ==========\n");

    if (n == 0) {
        printf("\nNo found items available.\n");
        return;
    }

    for (i = 0; i < n; i++) {

        printf("\nFound Item ID: %d", found[i].id);

        displayDetails(found[i].item);

        printf("\nStatus: ");
        showStatus(found[i].status);

        printf("\n--------------------------------");
    }

    printf("\nTotal Found Items: %d\n", n);
}


// SEARCH LOST AND FOUND ITEMS
void searchItems()
{
    struct LostItem lost[MAX];
    struct FoundItem found[MAX];

    char key[50];
    int n1, n2, i, count = 0;

    printf("\nEnter item name to search: ");
    scanf(" %49[^\n]", key);

    n1 = loadLostItems(lost);
    n2 = loadFoundItems(found);

    printf("\n========== SEARCH RESULTS ==========\n");

    for (i = 0; i < n1; i++) {

        if (strstr(lost[i].item.name, key) != NULL) {

            printf("\nLost Item ID: %d", lost[i].id);
            displayDetails(lost[i].item);

            printf("\nStatus: ");
            showStatus(lost[i].status);

            printf("\n");
            count++;
        }
    }

    for (i = 0; i < n2; i++) {

        if (strstr(found[i].item.name, key) != NULL) {

            printf("\nFound Item ID: %d", found[i].id);
            displayDetails(found[i].item);

            printf("\nStatus: ");
            showStatus(found[i].status);

            printf("\n");
            count++;
        }
    }

    if (count == 0)
        printf("\nNo matching items found.\n");
    else
        printf("\nTotal matching items: %d\n", count);
}


// MATCH LOST AND FOUND ITEMS
void matchItems()
{
    struct LostItem lost[MAX];
    struct FoundItem found[MAX];

    int n1, n2, i, j, count = 0;

    n1 = loadLostItems(lost);
    n2 = loadFoundItems(found);

    printf("\n======= POSSIBLE MATCHES =======\n");

    for (i = 0; i < n1; i++) {

        if (lost[i].status == 2)
            continue;

        for (j = 0; j < n2; j++) {

            if (found[j].status == 2)
                continue;

            if (strcmp(lost[i].item.name,
                       found[j].item.name) == 0 &&
                strcmp(lost[i].item.category,
                       found[j].item.category) == 0) {

                printf("\nPossible Match Found!");

                printf("\nLost ID  : %d", lost[i].id);
                printf("\nFound ID : %d", found[j].id);

                printf("\nItem Name: %s",
                       lost[i].item.name);

                printf("\nCategory : %s",
                       lost[i].item.category);

                printf("\n------------------------------");

                count++;
            }
        }
    }

    if (count == 0)
        printf("\nNo possible matches found.\n");

    printf("\nTotal possible matches: %d\n", count);
    printf("Please verify ownership before returning.\n");
}


// MARK LOST AND FOUND ITEMS AS RETURNED
void returnItem()
{
    struct LostItem lost[MAX];
    struct FoundItem found[MAX];

    int n1, n2, lostID, foundID;
    int i, lostFound = 0, foundFound = 0;

    n1 = loadLostItems(lost);
    n2 = loadFoundItems(found);

    printf("\n===== RETURN ITEM =====");

    printf("\nEnter Lost Item ID: ");
    scanf("%d", &lostID);

    printf("Enter corresponding Found Item ID: ");
    scanf("%d", &foundID);

    for (i = 0; i < n1; i++) {

        if (lost[i].id == lostID &&
            lost[i].status == 1) {

            lostFound = 1;
            break;
        }
    }

    for (i = 0; i < n2; i++) {

        if (found[i].id == foundID &&
            found[i].status == 1) {

            foundFound = 1;
            break;
        }
    }

    if (lostFound && foundFound) {

        lost[i = 0].status = lost[i].status;
        // Status updates are performed below.

        for (i = 0; i < n1; i++) {
            if (lost[i].id == lostID)
                lost[i].status = 2;
        }

        for (i = 0; i < n2; i++) {
            if (found[i].id == foundID)
                found[i].status = 2;
        }

        saveLostItems(lost, n1);
        saveFoundItems(found, n2);

        printf("\nItem successfully marked as returned!\n");
    }
    else {
        printf("\nInvalid IDs or item already returned.\n");
        printf("Please check both item records.\n");
    }
}


// DISPLAY PROJECT STATISTICS
void displayStatistics()
{
    struct LostItem lost[MAX];
    struct FoundItem found[MAX];

    int n1, n2, i;
    int returned = 0;

    n1 = loadLostItems(lost);
    n2 = loadFoundItems(found);

    for (i = 0; i < n1; i++) {
        if (lost[i].status == 2)
            returned++;
    }

    printf("\n======= PROJECT STATISTICS =======");

    printf("\nTotal Lost Items  : %d", n1);
    printf("\nTotal Found Items : %d", n2);
    printf("\nReturned Lost Records: %d", returned);

    printf("\n==================================\n");
}