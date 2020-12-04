#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "../Models/models.cpp"

void clear(void)
{
#ifdef _WIN32
    system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    system("clear");
#endif
}

Dish *createDish(char *name, int price, int quantity)
{
  Dish *temp = (Dish*)malloc(sizeof(Dish));
  strcpy(temp->name, name);
  temp->price = price;
  temp->quantity = quantity;
  temp->next = temp->prev = NULL;
  return temp;
}


void pushDish(struct Dish *temp)
{
   if(!headDish){
       headDish = tailDish = temp;
   }else{
       tailDish->next = temp;
       temp->prev = tailDish;
       tailDish = temp;
   }
}

void addDish(){
   char name[255];
   int price, quantity;
   clear();
   do
   {
   printf("Insert the name of the dish [Lowercase letters]: ");
   getchar();
   scanf("%[^\n]", &name);
   }while(!validName(name));
   
   do
   {
   printf("Insert the price of the dish [1000..50000]: ");
   scanf("%d", &price);
   }while(!validPrice(price));

   do{
   printf("Insert the quantity of the dish [1..999]: ");
   scanf("%d", &quantity);
   }while(!validQuantity(quantity));
    
   pushDish(createDish(name, price, quantity));
   puts("The dish has been added!");
   puts("Press enter to continue...");
   getchar();
   getchar();
}

void popHeadDish()
{
   if(headDish && headDish == tailDish)
   {
	   headDish = tailDish = NULL;	   
	   free(headDish);
   }else{
	   Dish *temp = headDish->next; 
	   headDish->next = temp->prev = NULL;
	   free(headDish);	
	   headDish= temp;					  
   }
}

void popTailDish()
{
	if(headDish && headDish == tailDish)
	{
		headDish = tailDish = NULL;
		free(headDish);
	}else{
		Dish *temp = tailDish->prev;
		tailDish->prev = temp->next = NULL;
		free(tailDish);
		tailDish = temp;
	}
}

int findLongestName(int *num)
{
	int leng, max = 0;
	currDish = headDish;
	while(currDish)
	{
	leng = strlen(currDish->name);
	if(leng > max)
	{
		max = leng;
	}
	currDish = currDish->next;
	(*num)++;
    }
    if(max < 4)
    {
    	max = 4;
	}
    return max;
}

int findLengthNum(int i, int ctr)
{
	while(i > 0)
	{
		i /= 10;
		ctr++;
	}
	return ctr;
}

void printCenter(char *str, int width)
{
	int leng = strlen(str), space = (width - leng) / 2;
	if((width - leng) % 2 != 0)
	{
      printf("%*s%s%*s", space, "", str, space + 1, "");
    }
	else
	{
      printf("%*s%s%*s", space, "", str, space, "");
	}
} 


void printSpace(int space)
{
	while(space--)
	{
		printf(" ");
	}
}

void printNumber(int num, int flag)
{
	if(flag == 1)
	{
	printf("%*s%03d%*s", 2, "", num, 3, "");
    }
    else
    {
    printf("%*sRp%d%*s", 1, "", num, 1, "");
	}
}


void printDish()
{
	int num = 1, maxLengthName, maxLengthNum, totalLength, extraSpace;
	maxLengthName = findLongestName(&num);
	maxLengthNum = findLengthNum(num, 1);
    if(maxLengthNum < 3)
    {
    	maxLengthNum = 3;
	}
	totalLength = maxLengthName + maxLengthNum + 21;
	printCenter((char*)"Bude's Menu", totalLength);
	puts("");
	while(totalLength--)
	{
		printf("=");
	}
	puts("");
	printf(" No.");
	extraSpace = maxLengthNum - 2;
	printSpace(extraSpace);
	printCenter((char*)"Name", maxLengthName);
	printf(" Quantity ");
	printf("  Price  ");
	puts(" ");
	maxLengthNum++;
	currDish = headDish;
	int i = 1;
	while(currDish)
	{
		printf(" %d.", i);
		extraSpace = maxLengthNum - findLengthNum(i, 1);
		printSpace(extraSpace);
		printCenter(currDish->name, maxLengthName);
		printf(" ");
		printNumber(currDish->quantity, 1);
		printf(" ");
		printNumber(currDish->price, 0);
		printf(" \n");
		currDish = currDish->next;
		i++;
	}
}


void tableDish()
{
	clear();
	char name[255];
	if(!headDish)
	{
		puts("There is no dish in the menu!\n");
	}
	else
	{
	printDish();
	
	do
	{
	printf("Insert dish's name to be deleted: ");
	getchar();
	scanf("%[^\n]", name);
	}while(!validDeletingDish(name));
	puts("The dish has been removed");
    }
	puts("Press enter to continue...");
	getchar();
	getchar();
}
Customer *createCustomer(char *name)
{
	Customer *temp = (Customer*) malloc(sizeof(Customer));
	strcpy(temp->name, name);
	temp->next = temp->prev = NULL;
	temp->headOrder = temp->tailOrder = NULL;
	return temp;
}

unsigned long long int djb3(char *str)
{

        unsigned long long int djb3 = 5381, c;
        while ((c = *str++))
            djb3 = ((djb3 << 5) + djb3) + c;
        return djb3 % 26;
}

void pushCustomer(struct Customer *temp, int hash)
{
	
	if(headCustomer[hash])
	{
		tailCustomer[hash]->next = temp;
		tailCustomer[hash] = temp;
	}
	else
	{
		headCustomer[hash] = tailCustomer[hash] = temp;
	}
	totalCustomer++;
}

void addCustomer()
{
	char name[255];
	int hash;
	clear();
	do
	{
	  printf("Insert the customer's name [Without space]: ");
	  getchar();
	  scanf("%[^\n]", name);
	}while(!validCustomer(name) || validCustomerPresent(name));
	
	hash = djb3(name);
	pushCustomer(createCustomer(name), hash);
    puts("Customer has been added!");
	puts("Press enter to continue...");
	getchar();
	getchar();
}

void searchCustomer()
{
	getchar();
	char name[255];
	clear();
	printf("Insert the customer's name to be searched: ");
	scanf("%[^\n]", name);
	bool present = validCustomerPresent(name);
	(present) ? printf("%s is present.\n", name) : printf("%s is not present.\n", name);
	puts("Press enter to continue...");
	getchar();
	getchar();
}

void printCustomer()
{
	int flag, flagTitle = 0;
	for(int i = 0;i < 26;i++)
	{
		currCustomer = headCustomer[i];
		flag = 0;
		while(currCustomer)
		{
		    if(flagTitle == 0)
		    {
		            puts("Customer List");
		            flagTitle = 1;
			}
			if(flag == 0)
			{
				    printf("%d. ", i);
					printf("%s", currCustomer->name);
					flag = 1;
			}
			else
			{
					printf(" -> ");
					printf("%s", currCustomer->name);
			}
			currCustomer = currCustomer->next;
		}
		if(flag == 1)
		{
			puts("");
		}
	}
	
	if(flagTitle == 0)
	{
		puts("There is no customer in the warteg!");
	}
}

void viewWarteg()
{
	clear();
	printCustomer();
	puts("Press enter to continue...");
	getchar();
	getchar();
}



Order *createOrder(char *str, int quantity, int price)
{
   Order *temp = (Order*)malloc(sizeof(Order));
   strcpy(temp->name, str);
   temp->quantity = quantity;
   temp->price = price;
   temp->next = temp->prev = NULL;
   return temp;
}

void pushOrder(struct Order *temp, char *name)
{
	for(int i = 0;i < 26;i++){
	currCustomer = headCustomer[i];
	while(currCustomer)
	{
		 if(strcmp(currCustomer->name, name) == 0)
		 {
            if(!currCustomer->headOrder)
			{
			   totalOrder++;
               currCustomer->headOrder = currCustomer->tailOrder = temp;
			}
			else
			{
               currCustomer->tailOrder->next = temp;
			   temp->prev = currCustomer->tailOrder;
			   currCustomer->tailOrder = temp;
			}
		 }
		 currCustomer = currCustomer->next;
	}
  }
}

void orderDish()
{
	clear();
	char name[255], dish[255];
	int amount;
	if(!headDish)
	{
		puts("There is no dish in the menu!\n");
	}
	else if(totalCustomer <= 0)
	{
		puts("There is no customer in the warteg!\n");
	}
	else
	{
	do
	{
	getchar();
    printf("Insert the customer's name: ");
	scanf("%[^\n]", name);
	}while(!validCustomerPresent(name));
   
    printf("Insert amount of dish: ");
	scanf("%d", &amount);
	for(int i = 0;i < amount;i++)
	{
		do
		{
		getchar();
		printf("[%d] Insert the dish's name and quantity: ", i + 1);
		scanf("%[^\n]", dish);
		}while(!validDishQuantity(dish, name));
	}
	puts("Order success!");
    }
	puts("Press enter to continue...");
	getchar();
	getchar();
}

void removeCustomer(int i)
{
	if(headCustomer[i] == tailCustomer[i])
	{
		headCustomer[i] = tailCustomer[i] = NULL;
		free(headCustomer[i]);
	}
	else
	{
		Customer *temp = headCustomer[i]->next;
		headCustomer[i]->next = temp->prev = NULL;
		free(headCustomer[i]);
		headCustomer[i] = temp;
	}	
	totalCustomer--;
	totalOrder--;
}

void paymentOrder()
{
   clear();
   int index, i = 1, total = 0;
   if(totalOrder <= 0)
   {
   	 puts("Customers have not ordered yet!\n");
   }
   else
   {
   do
   {
   	 printf("Insert the customer index: ");
   	 scanf("%d", &index);
   }while(index < 0 || index > 25 || !validIndex(index));
   
   printf("%s\n", headCustomer[index]->name);
   currOrder = headCustomer[index]->headOrder;
   while(currOrder)
   {
   	 printf("[%d] %s x%d\n", i++, currOrder->name, currOrder->quantity);
   	 total += (currOrder->price * currOrder->quantity);
   	 currOrder = currOrder->next;
   }
   removeCustomer(index);
   printf("Total: Rp%d\n", total);
   }
   puts("Press enter to continue...");
   getchar();
   getchar();
}

void printAlgorithmBootcamp()
{
   clear();
   char text[255];
   FILE *fp = fopen("../Controller/splash-screen.txt", "r");
   while(fscanf(fp, "%[^\n]%*c", text) != EOF)
   {
      printf("%s\n", text);
   }
   fclose(fp);
}


void exitWarteg()
{
  clear();
  puts("Please expand your terminal to full screen!");
  puts("Press enter to continue...");
  getchar();
  getchar();
  printAlgorithmBootcamp();
}
