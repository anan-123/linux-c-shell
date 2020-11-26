#include"headers.h"

void fg(char *token[],int arg_no)
{
    if(arg_no!=2)
    {
        printf("please provide proper arguments\n");
        return;
    }
    //get the process id
    
    int process = atoi(token[1]);
    if(process <= bjob_count)
    {
        pid_t pid = bjob[process].pid;
        char pid_str[1000];
        sprintf(pid_str,"%d",pid);
        char file_stat[1000];
        strcpy(file_stat,"/proc/");
        strcat(file_stat,pid_str);
        strcat(file_stat,"/stat");

        FILE *fp;
        if((fp=fopen(file_stat,"r"))==NULL)
        {
            printf("process doesnt exist\n");
            return;
        }
        kill(pid, SIGCONT);
        childpid = pid;
        strcpy(fjob.name, bjob[process].name);
        fjob.pid = bjob[process].pid;
        fjob.is_back = 0;
        //delete process from back 
        for(int i=process;i<bjob_count;i++)
        {
            bjob[i]=bjob[i+1];
        }
        waitpid(-1, NULL, WUNTRACED);


    }
    else
    {
        printf("job is invalid\n");
    }
    return;
}