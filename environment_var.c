#include"headers.h"

void env(char* token[],int arg_no)
{
  //  printf("entered setenv");
     if(arg_no == 3)
     {
        // printf("2 args");
        int flag = setenv(token[0],token[1],1);
        if(flag<0)
        {
            perror("setenv:");
        }
        
     }
     if(arg_no == 2)
     {
        // printf("2 args");
        int flag = setenv(token[0],"",1);
        if(flag<0)
        {
            perror("setenv:");
        }
        
     }
     else
     {
         printf("please provide the arguments in proper format\n");
     }
    

    return;
}

void unset(char* token[],int arg_no)
{
 //   printf("entered unsetenv");
   if(arg_no >= 2)
   {
       int flag;
       for(int i=2;i<=arg_no;i++)
       {
            flag = unsetenv(token[i-1]);
            if(flag<0)
            {
                perror("unsetenv:");
            }
       }
        
   }
   else
   {
       printf("please provide the arguments\n");
   }
   
   
    return;
}