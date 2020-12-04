
struct Dish{
    char name[255];
    int price, quantity;
    Dish *prev, *next;
}*headDish, *tailDish, *currDish;

struct Order {
    char name[255];
    int quantity, price;
    Order *prev, *next;
}*currOrder;

struct Customer {
    char name[255];
    Order *headOrder, *tailOrder;
    Customer *prev, *next;    
}*headCustomer[26], *tailCustomer[26], *currCustomer;

int totalCustomer = 0, totalOrder = 0;
void popHeadDish(), popTailDish(); //prototypes
bool validName(char* name), validPrice(int price), validQuantity(int quantity), validDeletingDish(char *name), validCustomer(char *name), validCustomerPresent(char *name), validDishQuantity(char *str, char *name), validIndex(int i);
