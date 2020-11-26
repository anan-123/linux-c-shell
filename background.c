#include"headers.h"

void background(char *token[])
{
    //create the child process
    int pid=fork();
    
    if(pid<0)
    {
        perror("fork failed:");
        return;
    }
    childpid = pid;
    if(pid == 0)
    {
      setpgid(0,0);
      //execute the child process
      int b = execvp(token[0],token);
      if(b<0)
      {
        perror("execvp error");
       
      }
  
    }
    else
    {
        bjob_count++;
        printf("[%d] %d\n",bjob_count,pid);
    }
    bjob[bjob_count].is_back = 1;
    strcpy(bjob[bjob_count].name,token[0]);
    bjob[bjob_count].pid=pid;
    return;

}