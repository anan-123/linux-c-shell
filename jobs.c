#include"headers.h"

void job_print()
{
    int j;
    j=0;
    char status;
    int p;
    long unsigned mem;
    for(int i=1;i<=bjob_count;i++)
    {
        if(bjob[i].is_back==1)
        {
            j++;
            char pid_str[1000];
            sprintf(pid_str,"%d",bjob[i].pid);
            char file_stat[1000];
            strcpy(file_stat,"/proc/");
            strcat(file_stat,pid_str);
            strcat(file_stat,"/stat");
            FILE *fp;
            if((fp=fopen(file_stat,"r"))==NULL)
            {
                 printf("[%d] %s %s [%d]\n", j, "Done", bjob[i].name, bjob[i].pid);
            }
            else
            {
                 fscanf(fp, "%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &p, &status, &mem);
                fclose(fp);
                printf("[%d] ", j);
                if (status == 'T')
                    printf("%s ", "Stopped");
                else 
                    printf("%s ", "Running");
                printf("%s [%d]\n", bjob[i].name, bjob[i].pid);
            }
            
        }
    }
}