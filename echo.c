#include"headers.h"

void echo(char* token[],int arg_no)
{
    char temp[10000];
    if(arg_no < 2)
    {
        printf("pls provide input to echo\n");
        return;
    }
    strcpy(temp,token[1]);
    strcat(temp," ");
    for(int w = 2;w <arg_no ;w++)
    {
        strcat(temp,token[w]);
        strcat(temp," ");
    }
    int len = strlen(temp);
    if(temp[0]=='"' && temp[len -2] == '"')
    {
        temp[len-2]='\0';
        printf("%s\n",&temp[1]);
    }
    else
    {
        printf("%s\n",temp);
    }
    return;
 
}