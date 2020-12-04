#include<stdio.h>
#include<string.h>

bool validName(char *str)
{
  int leng = strlen(str);
  for(int i = 0;i < leng;i++)
  {
     if(str[i] != ' ' && str[i] < 'a' || str[i] > 'z')
     {
        return false;
     }
  }
  return true;
}

bool validPrice(int price)
{
   if(price < 1000 || price > 50000)
   {
       return false;
   }   
   return true;
}

bool validQuantity(int quantity)
{
    if(quantity < 1 || quantity > 999)
    {
        return false;
    }
    return true;
}

bool validDeletingDish(char *name) //Valid then delete dish
{
	if(strcmp(headDish->name, name) == 0)
	{
		popHeadDish();
		return true;
	}else if(strcmp(tailDish->name, name) == 0)
	{
		popTailDish();
		return true;
	}else{
	currDish = headDish;
	while(currDish)
	{
		 if(strcmp(currDish->name, name) == 0)
		 {
		 	currDish->prev->next = currDish->next;
		 	currDish->next->prev = currDish->prev;
		 	currDish->prev = currDish->next = NULL;
		 	free(currDish);
		 	return true;
		 }
	     currDish = currDish->next;
	}
	return false;
    }
}

bool validCustomer(char *str)
{
	int leng = strlen(str);
	for(int i = 0;i < leng;i++)
	{
		if(str[i] == ' ')
		{
			return false;
		}
	}
	return true;
}

bool validCustomerPresent(char *str)
{
	for(int i = 0; i < 26;i++)
	{
		if(headCustomer[i])
		{
			currCustomer = headCustomer[i];
			while(currCustomer)
			{
				if(strcmp(currCustomer->name, str) == 0){
					return true;
				}
				currCustomer = currCustomer->next;
			}
		}
	}
	return false;
}

bool validDish(char *str, int quantity, char *name)
{
	currDish = headDish;
	while(currDish)
	{
        if(strcmp(currDish->name, str) == 0)
		{
		   if(quantity < 1 || quantity > currDish->quantity) //quantity cannot be less than one (quantity 1..99) and quantity cannot be more than the quantity of the dish
		   {
              return false;
		   }
		   pushOrder(createOrder(currDish->name, quantity, currDish->price), name);
           return true;
		}
		currDish = currDish->next;
	}
	return false;
}

int dishQuantity(char *str) //quantity is in string, then we need to convert to integer
{
   int leng = strlen(str), power = 1, quantity = 0;
   for(int i = leng-1;i>=0;i--)
   {
       quantity += ((str[i] - '0') * power);
	   power *= 10;
   }
   return quantity;
}


bool validDishQuantity(char *str, char *name)
{
   char strTemp[255], numTemp[255];
   int leng = strlen(str), idxStr = 0, idxNum = 0, flagNum = 0;
   for(int i = 0;i < leng;i++)
   {
	   if(str[i] == 'x' && i + 1 < leng && str[i+1] >= '0' && str[i+1] <= '9') //if the next character 'x' is a number
	   {
          flagNum = 1;
	   }
	   else if(flagNum == 1 && str[i] >= '0' && str[i] <= '9') //after character 'x', then put the character number in numTemp
	   {
          numTemp[idxNum++] = str[i];
	   }
	   else //put the character name in strTemp
	   {
		  strTemp[idxStr++] = str[i];
	   }
   }
   if(idxStr > 0 && strlen(numTemp) < 4) //if the idxStr > 0 (atleast there is a character), and numTemp < 4 (because the max quantity is 999 which the max length is 3)
   {
       strTemp[idxStr - 1] = '\0'; //remove space behind x (ex: telur x4) then become telur
	   if(validDish(strTemp, dishQuantity(numTemp), name)){
		   return true;
	   }else{
		   return false;
	   }
   }
   else
   {
	   return false;
   } 
}

bool validIndex(int i)
{
	return (headCustomer[i] && headCustomer[i]->headOrder) ? true : false;
}
