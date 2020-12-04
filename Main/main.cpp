#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "../Controller/controller.cpp"
#include "../Controller/validate.cpp"
const char *detectOS()
{
#if _WIN64
    return "Windows 64-bit";
#elif _WIN32
    return "Windows 32-bit";
#elif __APPLE__ || __MACH__
    return "Mac OSX";
#elif __linux__
    return "Linux";
#elif __FreeBSD__
    return "FreeBSD";
#elif __unix || __unix__
    return "Unix";
#else
    return "Other";
#endif
}

void mainMenu()
{
  time_t current = time(NULL);
  clear();
  printf("System: %s\n", detectOS());
  printf("%s\n", ctime(&current));
  puts("1. Add Dish");
  puts("2. Remove Dish");
  puts("3. Add Customer");
  puts("4. Search Customer");
  puts("5. View Warteg");
  puts("6. Order");
  puts("7. Payment");
  puts("8. Exit Warteg");
}

int main(){
 int input;
 bool online = true;
 while(online){
 mainMenu();
 do
 {
   printf(">> ");
   scanf("%d", &input); 
 }while(input < 1 || input > 8);
 
 switch(input)
 {
   case 1:
   addDish();
   break;

   case 2:
   tableDish();
   break;

   case 3:
   addCustomer();
   break;

   case 4:
   searchCustomer();
   break;

   case 5:
   viewWarteg();
   break;

   case 6:
   orderDish();
   break;

   case 7:
   paymentOrder();
   break;

   case 8:
   exitWarteg();
   online = false;
   break;
 }
 
 }
   return 0;
}
