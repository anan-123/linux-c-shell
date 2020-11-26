#include"headers.h"

void pinfo(char* token[],int arg_no)
{
    char pid_str[1000];
    if(arg_no == 1)
    {
        sprintf(pid_str,"%d",getpid());
    }
    else
    {
        strcpy(pid_str,token[1]);
    }
    char file_stat[1000],file_exe[1000],file_statm[1000];
    strcpy(file_stat,"/proc/");
    strcpy(file_exe,"/proc/");
    strcpy(file_statm,"/proc/");
    strcat(file_stat,pid_str);
    strcat(file_exe,pid_str);
    strcat(file_statm,pid_str);
    strcat(file_stat,"/stat");
    strcat(file_exe,"/exe");
    strcat(file_statm,"/statm");

    FILE *fp;
    if((fp=fopen(file_stat,"r"))==NULL)
    {
        printf("file doesn't exist\n");
        return;
    }

    int pid;
    char status;
    long int memory;
   
 
    fscanf(fp,"%d",&pid);
    printf("pid -- %d\n", pid);

    char str[1000];
    fscanf(fp,"%s",str);
    fseek(fp,1,SEEK_CUR);
    fscanf(fp,"%c",&status);
    printf("Process Status --- %c\n", status);
    fclose(fp);

    //virtual memory size

    FILE *fd;
    if((fd=fopen(file_statm,"r"))==NULL)
    {
        perror("pinfo error:");
        return;
    }
    fscanf(fd,"%ld",&memory);
    printf("Memory(virtual) --- %ld KB\n", memory);

    char path[1000];
    int x = readlink(file_exe,path,1000);
    path[x]='\0';
    
    int q;
    char dir[1000];
    char final_path[1000];

    if(strcmp(path,homedir_path)==0)
    {
        strcpy(final_path,"~");
    }
    else
    {
        int flag=0;
        if(strlen(path)>strlen(homedir_path))
        {
            
            for(int i=0;i<strlen(homedir_path);i++)
            {
                if(path[i]!=homedir_path[i])
                {
                    flag=1;
                    break;
                }
            }
            if(!flag)
            {
            strcpy(final_path,"~");
            int ref=0;
            for(q=strlen(homedir_path);path[q];q++)
            {
                dir[ref++]=path[q];
            }
            dir[ref]='\0';
            strcat(final_path,dir);
            }
            else
            {
                 strcpy(final_path,path);
            }
            

        }
        else
        {
            strcpy(final_path,path);
        }
        
    }
   

        
    printf("Executable Path---  %s\n",final_path);




}