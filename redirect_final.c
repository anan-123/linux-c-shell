#include"headers.h"
void redirect(char *buf, int type)
{
    int i,k=0,pid,status,in,out;
    char *temp;
    char *temp2;
    int save_stdout=dup(STDOUT_FILENO);

    char *op[2];
    op[0] = strtok(buf, ">");
    op[1] = strtok(NULL, ">");
    
    char *ip[2];
    ip[0] = strtok(op[0], "<");
    ip[1] = strtok(NULL, "<");
    
    char command[100][100];
    temp=strtok(ip[0], " \n\t\r");
    while(temp != NULL)
    {
        strcpy(command[k++], temp);
        temp=strtok(NULL," \n\t\r");
    }
    char *com[k + 1];

    for(i = 0; i < k; i++)
    {com[i] = command[i];
    }
    com[i] = NULL;

    pid=fork();
    if(ip[1]!=NULL)
    {
        temp2=strtok(ip[1], " \n\t\r");
        if(temp2 != NULL)
        { in=open(temp2, O_RDONLY);
            if(pid==0)
            {   if(in<0)
                {printf("there is no such file\n");
                return;
                }
                else
                {dup2(in, 0);}
            }
        }
        else
        {   if(pid==0)
            {printf("Invalid input file\n");
            return;
            }
        }
    }
    if(op[1]!=NULL)
    {
        temp2=strtok(op[1], " \n\t\r");
        if(temp2!=NULL)
        {
            if(type==0)
            {out=open(temp2, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
            }
            else
             { out=open(temp2, O_APPEND | O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR); }
            if(pid==0)
            { dup2(out, 1);
            }
        }
        else
        {   if(pid==0)
            {printf("not valid output file\n");
            return;}
        }
    }
    if(pid==0)
    {   if(execvp(com[0], com) == -1)
        {dup2(save_stdout, 1);  
         printf("command error\n");
        }
        return;
    }
    else
    {
        while(wait(&status)!= pid);
    }
    return;
}