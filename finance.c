#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_ENTRIES 100
#define MAX_CATEGORY_LENGTH 30

typedef struct {
    char source[MAX_CATEGORY_LENGTH];
    float amount;
} Income;

typedef struct {
    char category[MAX_CATEGORY_LENGTH];
    float amount;
} Expense;

Income incomes[MAX_ENTRIES];
Expense expenses[MAX_ENTRIES];
int incomeCount = 0;
int expenseCount = 0;

void displayMenu();
void addIncome();
void addExpense();
void viewSummary();
void removeEntry(const char* type);
void listExpensesByCategory();
bool isValidIncome(float amount);
bool isValidExpense(float amount);
void toUpperCase(char* str);

int main() {
    while (true) {
        displayMenu();
        int choice = get_int("What would you like to do? ");

        if (choice == 1) addIncome();
        else if (choice == 2) addExpense();
        else if (choice == 3) viewSummary();
        else if (choice == 4) removeEntry("income");
        else if (choice == 5) removeEntry("expense");
        else if (choice == 6) listExpensesByCategory();
        else if (choice == 7) {
            printf("Thanks for using the Personal Finance Manager! Have a great day!\n");
            break; // Exit the program
        } else {
            printf("Oops! That's not a valid option. Please try again.\n");
        }
    }
    return 0;
}

void displayMenu() {
    printf("\n==============================\n");
    printf("    Personal Finance Manager   \n");
    printf("==============================\n");
    printf("1. Add Income\n");
    printf("2. Add Expense\n");
    printf("3. View Summary\n");
    printf("4. Remove Income\n");
    printf("5. Remove Expense\n");
    printf("6. List Expenses by Category\n");
    printf("7. Exit\n");
    printf("==============================\n");
}

void addIncome() {
    if (incomeCount >= MAX_ENTRIES) {
        printf("Oh no! You've reached the maximum income entries.\n");
        return;
    }

    string source = get_string("What is the source of your income? ");
    strncpy(incomes[incomeCount].source, source, MAX_CATEGORY_LENGTH - 1);
    incomes[incomeCount].source[MAX_CATEGORY_LENGTH - 1] = '\0'; // Ensure null termination
    toUpperCase(incomes[incomeCount].source);

    float amount;
    do {
        amount = get_float("How much did you earn? ");
    } while (!isValidIncome(amount) && printf("Please enter a non-negative amount.\n"));

    incomes[incomeCount].amount = amount;
    incomeCount++;
    printf("Great! Your income has been added successfully!\n");
}

void addExpense() {
    if (expenseCount >= MAX_ENTRIES) {
        printf("Oh no! You've reached the maximum expense entries.\n");
        return;
    }

    string category = get_string("What category does this expense fall under? ");
    strncpy(expenses[expenseCount].category, category, MAX_CATEGORY_LENGTH - 1);
    expenses[expenseCount].category[MAX_CATEGORY_LENGTH - 1] = '\0'; // Ensure null termination
    toUpperCase(expenses[expenseCount].category);

    float amount;
    do {
        amount = get_float("How much did you spend? ");
    } while (!isValidExpense(amount) && printf("Please enter a positive amount.\n"));

    expenses[expenseCount].amount = amount;
    expenseCount++;
    printf("Awesome! Your expense has been recorded!\n");
}

void viewSummary() {
    float totalIncome = 0, totalExpense = 0;
    for (int i = 0; i < incomeCount; i++) totalIncome += incomes[i].amount;
    for (int i = 0; i < expenseCount; i++) totalExpense += expenses[i].amount;

    printf("\n==============================\n");
    printf("         Financial Summary     \n");
    printf("==============================\n");
    printf("Total Income:     ₹%.2f\n", totalIncome);
    printf("Total Expenses:   ₹%.2f\n", totalExpense);
    printf("Remaining Balance: ₹%.2f\n", totalIncome - totalExpense);
    printf("==============================\n");
}

void removeEntry(const char* type) {
    char prompt[MAX_CATEGORY_LENGTH];
    snprintf(prompt, MAX_CATEGORY_LENGTH, "%s", (strcmp(type, "income") == 0) ? "income source" : "expense category");
    string toRemove = get_string("Which %s would you like to remove? ", prompt);
    toUpperCase(toRemove);

    int count = (strcmp(type, "income") == 0) ? incomeCount : expenseCount;

    for (int i = 0; i < count; i++) {
        if (strcmp((strcmp(type, "income") == 0) ? incomes[i].source : expenses[i].category, toRemove) == 0) {
            for (int j = i; j < count - 1; j++) {
                if (strcmp(type, "income") == 0) {
                    incomes[j] = incomes[j + 1];
                } else {
                    expenses[j] = expenses[j + 1];
                }
            }

            // Decrement the appropriate count
            if (strcmp(type, "income") == 0) {
                incomeCount--;
            } else {
                expenseCount--;
            }

            printf("Done! The %s has been removed.\n", prompt);
            return;
        }
    }
    printf("Hmm, I couldn't find that %s.\n", prompt);
}


void listExpensesByCategory() {
    char categories[MAX_ENTRIES][MAX_CATEGORY_LENGTH];
    float totals[MAX_ENTRIES] = {0};
    int uniqueCount = 0;

    for (int i = 0; i < expenseCount; i++) {
        bool found = false;
        for (int j = 0; j < uniqueCount; j++) {
            if (strcmp(expenses[i].category, categories[j]) == 0) {
                totals[j] += expenses[i].amount;
                found = true;
                break;
            }
        }
        if (!found) {
            strncpy(categories[uniqueCount], expenses[i].category, MAX_CATEGORY_LENGTH - 1);
            categories[uniqueCount][MAX_CATEGORY_LENGTH - 1] = '\0'; // Ensure null termination
            totals[uniqueCount++] += expenses[i].amount;
        }
    }

    printf("\n==============================\n");
    printf("   Expenses by Category       \n");
    printf("==============================\n");
    for (int i = 0; i < uniqueCount; i++) {
        printf("%-20s: ₹%.2f\n", categories[i], totals[i]);
    }
    printf("==============================\n");
}

bool isValidIncome(float amount) {
    return amount >= 0;
}

bool isValidExpense(float amount) {
    return amount > 0;
}

void toUpperCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}
