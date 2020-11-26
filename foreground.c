#include"headers.h"

void foreground(char* token[])
{
  //  printf("foreground called");
    pid_t pid;

    //create the child process
    pid=fork();
    if(pid<0)
    {
        perror("fork failed:");
        return;
    }

   /* strcpy(current_fore.name,token[0]);
    current_fore.pid=pid;*/

    if(pid == 0)
    {
      //execute the child process
      setpgid(0, 0);
      int b = execvp(token[0],token);
      if(b<0)
      {
        perror("execvp error");
       
      }
      exit(0);
    }
    else
    {//used to store status  of child
      int status;
      childpid =pid;
      fjob.pid=pid;
      strcpy(fjob.name,token[0]);
      fjob.is_back=0;
      //0:wait for any child process
      waitpid(-1, NULL, WUNTRACED);
    }
}
