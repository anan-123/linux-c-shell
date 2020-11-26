To run the shell:


make
./a.out


the funcitonalities implemented:

1.cd:
cd is implemented in this file.
it changes the directory
    the commands implemented are:
    cd
    cd ..
    cd .
    cd ~
    cd <directory>
    cd - (this changes into the previous working directory.


2.pwd : pwd is implemented in this file.
         it gives the present working directory
	 
3.echo: echo is implemented in this file.
          it prints the message on the terminal
	  
4.ls: ls command is implemented in this file
        it lists the contents of the directory
        the commands implemented are:
        ls
        ls .
        ls ..
        ls -l
        ls -a
        ls -al
        ls -la
        ls <directory>
        ls ~
	

5.background : background command is implemented in this file
                runs a process specified by & in background.
		

6.foreground: foreground is implemented in this file.
                runs a process in foreground.
		

7.pinfo: prints process info of current shell if no arguments and prints  the process info of process with the argument as pid.

8.environment variables:
	setenv :to set the environment variable to a given value
	unsetenv:to destroy the variable

9.bg : changes a stopped background job to a running background job

10.fg : brings a running or a stopped background job with given job number to foreground

11.jobs : prints a list of all background processes

12.kjobs : takes the job id of a running job and sends a signal value to that process

13.pipe with redirection:one or more commands can be piped.pipe also can be combined with redirection

14.redirection:output can be redirected to another file and input can be taken from a given file.

15.CTRL_C:sends SIGINT to the foreground processes of shell
   CTRL_Z:send SIGINT and SIGTSTP to foreground process and makes it background process
