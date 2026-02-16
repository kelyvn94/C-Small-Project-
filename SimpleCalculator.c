#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
   char operator;
   float num1, num2, result;
   
   printf("Simple Calculator\n");
   printf("Enter first number: ");
   scanf("%f", &num1);
   
   printf("Enter operator (+, -, *, /): ");
   scanf(" %c", &operator);
   
   printf("Enter second number: ");
   scanf("%f", &num2);
   
   switch(operator)
   {
      case '+':
         result = num1 + num2;
         break;
      case '-':
         result = num1 - num2;
         break;
      case '*':
         result = num1 * num2;
         break;
      case '/':
         if(num2 != 0)
            result = num1 / num2;
         else
         {
            printf("Error: Division by zero\n");
            return 1;
         }
         break;
      default:
         printf("Invalid operator\n");
         return 1;
   }
   
   printf("Result: %.2f\n", result);
   return 0;
}