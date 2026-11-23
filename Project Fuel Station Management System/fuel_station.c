#include <stdio.h>
#include <stdlib.h>

#define REGULAR_PRICE 3.00
#define PREMIUM_PRICE 4.00
#define DIESEL_PRICE 3.50

#define REGULAR_MAX 200
#define PREMIUM_MAX 200
#define DIESEL_MAX 400

double regStock = 1000.0, premStock = 1000.0, dieselStock = 1000.0;
double regSold = 0, premSold = 0, dieselSold = 0;

int customerCount = 0;
double totalRevenue = 0;
double totalTax = 0;
double totalDiscounts = 0;
double totalPayments = 0;

int motorcycles = 0, cars = 0, trucks = 0;

int readInt() {
    char buffer[100];
    int value;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return -1;

    if (sscanf(buffer, "%d", &value) != 1)
        return -1;

    return value;
}

double readDouble() {
    char buffer[100];
    double value;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return -1;

    if (sscanf(buffer, "%lf", &value) != 1)
        return -1;

    return value;
}


void pause() {
    printf("\nPress ENTER to continue...");
    getchar();
    getchar();
}

void printWelcome() {
    printf("=========================================================\n");
    printf("   WELCOME TO TurboFill FUEL STATION MANAGEMENT SYSTEM\n");
    printf("=========================================================\n");
    printf("========= CURRENT PRICING & POLICIES =========\n");
    printf("Fuel Rates:\n");
    printf("  Regular Gas : $3.00/gal (Max: 200 gal/transaction)\n");
    printf("  Premium Gas : $4.00/gal (Max: 200 gal/transaction)\n");
    printf("  Diesel      : $3.50/gal (Max: 400 gal/transaction)\n\n");
    printf("State Fuel Tax Rates:\n");
    printf("  Motorcycle  : 2%%\n");
    printf("  Car         : 3%%\n");
    printf("  Truck       : 1%%\n\n");
    printf("Bulk Discount Rates:\n");
    printf("  30+ gallons : 5%% off total\n");
    printf("  50+ gallons : 10%% off total\n");
    printf("Loyalty Program: Additional 2%% off total\n");
    printf("=============================================\n");
}

const char* stockStatus(double stock) {
    if (stock < 50) return "CRITICAL";
    if (stock < 200) return "LOW";
    return "NORMAL";
}

void showInventory() {
    printf("\n==========================================\n");
    printf("         FUEL INVENTORY STATUS\n");
    printf("==========================================\n");

    printf("REGULAR GAS:\n");
    printf("  Current Stock : %.1f gal\n", regStock);
    printf("  Sold Today    : %.1f gal\n", regSold);
    printf("  Stock Status  : %s\n\n", stockStatus(regStock));

    printf("PREMIUM GAS:\n");
    printf("  Current Stock : %.1f gal\n", premStock);
    printf("  Sold Today    : %.1f gal\n", premSold);
    printf("  Stock Status  : %s\n\n", stockStatus(premStock));

    printf("DIESEL:\n");
    printf("  Current Stock : %.1f gal\n", dieselStock);
    printf("  Sold Today    : %.1f gal\n", dieselSold);
    printf("  Stock Status  : %s\n", stockStatus(dieselStock));
}

int receiptNo = 1;

void printReceipt(
    int fuel, int vehicle, double qty, double price, int loyalty,
    double base, double tax, double bulkDisc, double loyaltyDisc, double total
) {
    const char *fuelName =
        fuel == 1 ? "Regular Gas" :
        fuel == 2 ? "Premium Gas" : "Diesel";

    const char *vehicleName =
        vehicle == 1 ? "Motorcycle" :
        vehicle == 2 ? "Car" : "Truck";

    printf("\n==========================================\n");
    printf("          FUEL RECEIPT #%03d\n", receiptNo++);
    printf("==========================================\n");
    printf(" Fuel Type    : %s\n", fuelName);
    printf(" Vehicle Type : %s\n", vehicleName);
    printf(" Quantity     : %.2f   gal\n", qty);
    printf(" Rate         : $%.2f /gal\n", price);
    printf(" Loyalty      : %s\n", loyalty ? "Yes" : "No");
    printf("==========================================\n");
    printf(" Base Cost    : $%.2f\n", base);
    printf(" State Tax    : $%.2f\n", tax);
    if (bulkDisc > 0)
        printf(" Bulk Discount: -$%.2f\n", bulkDisc);
    if (loyaltyDisc > 0)
        printf(" Loyalty Disc.: -$%.2f\n", loyaltyDisc);
    printf("==========================================\n");
    printf(" TOTAL PAYABLE: $%.2f\n", total);
    printf("==========================================\n");
    printf("\nTransaction completed succesfully!");
}


void serveCustomer() {
    customerCount++;

    int fuel, vehicle, loyalty;
    double qty;
    double price = 0, taxRate = 0;
    double *stock;

    printf("\n--- CUSTOMER #%d ---\n", customerCount);
    printf("1. Regular Gas ($3.00) - Stock: %.1f\n", regStock);
    printf("2. Premium Gas ($4.00) - Stock: %.1f\n", premStock);
    printf("3. Diesel ($3.50) - Stock: %.1f\n", dieselStock);
    printf("Fuel Choice: ");
    while (1) {
    printf("Fuel Choice: ");
    fuel = readInt();

    if (fuel >= 1 && fuel <= 3)
        break;

    printf("Invalid fuel selection. Try again.\n");
}


    if (fuel == 1) { price = REGULAR_PRICE; stock = &regStock; }
    else if (fuel == 2) { price = PREMIUM_PRICE; stock = &premStock; }
    else if (fuel == 3) { price = DIESEL_PRICE; stock = &dieselStock; }
    else {
        printf("Invalid fuel selection!\n");
        return;
    }

    int max = (fuel == 3) ? DIESEL_MAX : REGULAR_MAX;

while (1) {
    printf("Enter quantity in gallons (Max: %d): ", max);
    qty = readDouble();

    if (qty <= 0 || qty > max) {
        printf("Invalid quantity! Enter a proper amount (max %d gal):\n", max);
        continue;
    }

    if (qty > *stock) {
        printf("Insufficient stock! Available: %.1f gal\n", *stock);
        printf("Transaction cancelled due to insufficient stock.\n");
        return;   // this one DOES exit, because stock failure cancels transaction
    }

    break;  // valid quantity
}


    printf("Select Vehicle:\n1. Motorcycle\n2. Car\n3. Truck\n");
    while (1) {
    printf("Vehicle Choice: ");
    vehicle = readInt();

    if (vehicle >= 1 && vehicle <= 3) {
        if (fuel == 3 && vehicle == 1) {
            printf("Invalid combination! Motorcycles cannot use diesel fuel.\n");
            continue;
        }
        break;
    }

    printf("Invalid vehicle selection. Try again.\n");
}

    if (fuel == 3 && vehicle == 1) {
        printf("Invalid combination! Motorcycles cannot use diesel.\n");
        return;
    }

    if (vehicle == 1) taxRate = 0.02;
    if (vehicle == 2) taxRate = 0.03;
    if (vehicle == 3) taxRate = 0.01;

    while (1) {
    printf("Is customer a loyalty member? (1=Yes, 0=No): ");
    loyalty = readInt();

    if (loyalty == 0 || loyalty == 1)
        break;

    printf("Invalid input. Enter 1 or 0.\n");
}


    double base = qty * price;
    double tax = base * taxRate;
    double total = base + tax;

    double bulkDisc = 0, loyaltyDisc = 0;

    if (qty >= 50) bulkDisc = total * 0.10;
    else if (qty >= 30) bulkDisc = total * 0.05;

    total -= bulkDisc;

    if (loyalty == 1) {
        loyaltyDisc = total * 0.02;
        total -= loyaltyDisc;
    }

    *stock -= qty;
    if (fuel == 1) regSold += qty;
    if (fuel == 2) premSold += qty;
    if (fuel == 3) dieselSold += qty;

    totalRevenue += base;
    totalTax += tax;
    totalDiscounts += (bulkDisc + loyaltyDisc);
    totalPayments += total;

    if (vehicle == 1) motorcycles++;
    if (vehicle == 2) cars++;
    if (vehicle == 3) trucks++;

    printReceipt(fuel, vehicle, qty, price, loyalty,
             base, tax, bulkDisc, loyaltyDisc, total);

}

void summary() {
    double totalFuel = regSold + premSold + dieselSold;
    double avgPay = (customerCount > 0) ? totalPayments / customerCount : 0;
    double avgFuel = (customerCount > 0) ? totalFuel / customerCount : 0;

    printf("\n==========================================\n");
    printf("         CURRENT DAY SUMMARY\n");
    printf("==========================================\n");
    printf(" Total Customers    : %d\n", customerCount);
    printf(" Total Fuel Sold    : %.2f gal\n", totalFuel);
    printf(" Sales Revenue      : $%.2f\n", totalRevenue);
    printf(" State Tax Collected: $%.2f\n", totalTax);
    printf(" Total Discounts    : $%.2f\n", totalDiscounts);
    printf(" Customer Payments  : $%.2f\n", totalPayments);
    printf(" Station Net Income : $%.2f\n", totalPayments - totalTax);

    printf("\nVehicle Distribution:\n");
    printf(" Motorcycles        : %d\n", motorcycles);
    printf(" Cars               : %d\n", cars);
    printf(" Trucks             : %d\n", trucks);

    printf("\n Average Payment    : $%.2f\n", avgPay);
    printf(" Avg Fuel/Customer  : %.2f gal\n", avgFuel);
    printf("==========================================\n");
}


int main() {
    int mainChoice, dailyChoice, internChoice;

    printWelcome();   // print once only

    while (1) {

        // SYSTEM MODE SELECTION (loop until valid)
        while (1) {
            printf("\n========= SYSTEM MODE SELECTION =========\n");
            printf("1. Daily Operations (Customer Service)\n");
            printf("2. Station Management (Administrative)\n");
            printf("3. Exit System\n");
            printf("=========================================\n");
            printf("Select Mode: ");

            mainChoice = readInt();

            if (mainChoice >= 1 && mainChoice <= 3)
                break;

            printf("Invalid choice. Try again.\n");
        }

        if (mainChoice == 1) {
            // DAILY OPERATIONS MENU
            while (1) {
                printf("\n========= DAILY OPERATIONS MODE =========\n");
                printf("1. Serve New Customer\n");
                printf("2. View Current Day Summary\n");
                printf("3. Return to Main Menu\n");
                printf("========================================\n");
                printf("Choice: ");

                dailyChoice = readInt();

                if (dailyChoice == 1) serveCustomer();
                else if (dailyChoice == 2) summary();
                else if (dailyChoice == 3) break;
                else printf("Invalid choice. Try again.\n");
            }
        }
        else if (mainChoice == 2) {
            while (1) {
                printf("\n========= STATION MANAGEMENT MODE =========\n");
                printf("1. Show Fuel Inventory Status\n");
                printf("2. Return to Main Menu\n");
                printf("========================================\n");
                printf("Choice: ");

                internChoice = readInt();

                if (internChoice == 1) showInventory();
                else if (internChoice == 2) break; 
                else printf("Invalid choice. Try again.\n");
        }
    }
        else if (mainChoice == 3) {
            printf("\nExiting system...\n");
            break;
        }
    }

    return 0;
}
