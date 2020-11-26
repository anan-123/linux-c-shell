#include"headers.h"

job bjob[1000];
job fjob;
int bjob_count=0;
int shellid =0;
int childpid=-1;
int mode;
struct utsname uinfo;

void print_prompt(char *username,char *sysname)
{
    char cwd[1000];
    getcwd(cwd,sizeof(cwd));
    strcpy(prompt,"<");
    strcat(prompt,username);
    strcat(prompt,"@");
    strcat(prompt,sysname);
    strcat(prompt,":");

   int q;
   char dir[1000];
   int flag = 0;

    if(strcmp(cwd,homedir_path)==0)
    {
        strcat(prompt,"~");
    }
    else
    {

       // printf("strlen of cwd is %ld\n",strlen(cwd));
       // printf("strlen of home dir is %ld\n",strlen(homedir_path));
        if(strlen(cwd)>strlen(homedir_path))
        {
            for(int i=0;i<strlen(homedir_path);i++)
            {
                if(cwd[i]!=homedir_path[i])
                {
                    flag=1;
                    break;
                }
            }
            if(!flag)
            {
            strcat(prompt,"~");
            int ref=0;
            for(q=strlen(homedir_path);cwd[q];q++)
            {
                dir[ref++]=cwd[q];
            }
            dir[ref]='\0';
            strcat(prompt,dir);
            }
            else
            {
                strcat(prompt,cwd);
            }


        }
        else
        {
            strcat(prompt,cwd);
        }

    }

    strcat(prompt,">");
    printf("%s",prompt);
}

int check(char *token,char c)
{   //redirection
    if(c=='r')
    {
        int len=strlen(token);
        for(int i=0;i<len;i++)
        {
            if (token[i] == '<' || (token[i] == '>' && token[i + 1] != '>'))
                return 2;
            if (token[i] == '>' && token[i + 1] == '>')
                return 3;
        }
        return 0;
    }
    //pipe
    if(c=='p')
    {
        int len = strlen(token);
        for(int i=0;i<len;i++)
        {
             if(token[i] == '|')
            {
                return 1;
            }
        }
        return 0;
    }
}
void child_sig(int signo)
{
    pid_t pid;
    int status;
    pid=waitpid(WAIT_ANY,&status,WNOHANG);
    for(int i=1;i<=bjob_count;i++)
    {
        if(bjob[i].pid==pid)
        {
            if(WEXITSTATUS(status)==0)
            {
                printf("\n%s whose pid %d exited normal\n",bjob[i].name,bjob[i].pid);
            }
            else
            {
                printf("\n%s whose pid %d exited with status %d\n",bjob[i].name,bjob[i].pid,WEXITSTATUS(status));
            }
            print_prompt(uinfo.nodename,uinfo.sysname);
            fflush(stdout);
            break;
        }
    }
    signal(SIGCHLD,child_sig);
}

void ctrl_c(int signo)
{
    pid_t pid;
    pid=getpid();
    if(pid==shellid)
    {
        if(childpid!=-1)
        {
            kill(childpid,SIGINT);
        }
        signal(SIGINT,ctrl_c);
    }
}

void ctrl_z(int signo)
{
    pid_t pid;
    pid =getpid();
    if(pid==shellid)
    {
        if(childpid!=-1)
        {
            kill(childpid,SIGTTIN);
            kill(childpid,SIGTSTP);
            bjob_count++;
            bjob[bjob_count].is_back=1;
            bjob[bjob_count].pid=childpid;
            strcpy(bjob[bjob_count].name,fjob.name);

        }
        signal(SIGTSTP,ctrl_z);
    }
}

int main(int argc,char *argv)
{
    shellid= getpid();

    //code to get the username and systemname
    char* username = (char *)malloc(100*sizeof(char));
    char* sysname = (char *)malloc(100*sizeof(char));
    register struct passwd *pw;
    register uid_t uid;
    uid = geteuid ();
    pw = getpwuid (uid);
    if (uname(&uinfo) != 0)
    {
        perror("uname");
        exit(EXIT_FAILURE);
    }
    if (!pw)
    {
        printf("error in getting the username\n");
        return 0;
    }
    strcpy(username,pw->pw_name);
    gethostname(sysname,sizeof(sysname));

    //getting the home directory
    if (getcwd(homedir_path, sizeof(homedir_path)) == NULL)
    {
        perror("getcwd() error");
       return 0;
    }
    //print prompt
    print_prompt(username,sysname);

    //variables for taking input
    size_t size_i = 100;
    char* input_str = (char *)malloc(size_i*sizeof(char));
    char *token_arr[1000];

    while(1)
    {
        childpid = -1;

        //taking input
        if(getline(&input_str,&size_i,stdin)==-1)
        {
            printf("error\n");
            return 0;
        }

        //handling the segmentation fault
        if (strcmp(input_str, "\n") == 0)
        {
             print_prompt(username,sysname);
            continue;
        }

   //signal(SIGCHLD, SIG_IGN);
//signal(SIGCHLD, child_signal);
    signal(SIGINT, ctrl_c);
    signal(SIGTSTP, ctrl_z);
        //tokenizing into semicolon
        char *token_arr[1000];
        char *rest_arr = input_str;
        int no_semicolon=0;
        while(token_arr[no_semicolon]=strtok_r(rest_arr,";",&rest_arr))
        {
                no_semicolon++;
        }

        //running each of the semicolon commands
        for(int i=0;i<no_semicolon;i++)
        {
            char *token[1000];
            char *rest = token_arr[i];
            int arg_no=0;

            //piping and redirection
            if(check(token_arr[i],'p'))
            {
                pipe_fn(token_arr[i]);
                continue;
            }
            int r = check(token_arr[i],'r');
            if(r==2 || r==3)
            {
                redirect(token_arr[i],(r-2));
                continue;
            }
            while(token[arg_no]=strtok_r(rest," \t\n\r",&rest))
            {
                //    printf(" %s",token[i]);
                 arg_no++;
            }

            //executing each command
            if(strcmp(token[0],"cd")==0)
            {
                cd(token,arg_no);
            }
            else if(strcmp(token[0],"pwd")==0)
            {
                pwd();
            }
            else if(strcmp(token[0],"echo")==0)
            {
                echo(token,arg_no);
            }
            else if(strcmp(token[0],"ls")==0)
            {
                ls(token,arg_no);
            }
            else if(strcmp(token[0],"pinfo")==0)
            {
                pinfo(token,arg_no);
            }

            else if(strcmp(token[0],"setenv")==0)
            {
                env(token,arg_no);
            }
            else if(strcmp(token[0],"unsetenv")==0)
            {
                unset(token,arg_no);
            }
            else if(strcmp(token[arg_no-1],"&")==0)
            {
                 background(token);
            }
            else if(strcmp(token[0],"exit")==0)
            {
                exit(0);
            }
            else if(strcmp(token[0],"quit")==0)
            {

                 exit(0);
            }
             else if(strcmp(token[0],"bg")==0)
            {
                bg(token,arg_no);
            }
            else if(strcmp(token[0],"fg")==0)
            {
                fg(token,arg_no);
            }
            else if(strcmp(token[0],"kjob")==0)
            {
                kjob(token,arg_no);
            }
            else if(strcmp(token[0],"jobs")==0)
            {
                job_print();
             }
             else if(strcmp(token[0],"overkill")==0)
             {
               overkill();
             }
            else
            {
                 foreground(token);
            }


        }
        print_prompt(username,sysname);
    }
    return 0;
}
