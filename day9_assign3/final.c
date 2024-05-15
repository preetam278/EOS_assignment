#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
    int r1,r2,r3,r4,r5,r6, err,s,es;
    r1=fork();
    if(r1==0){
        err = execlp("gcc", "gcc", "-c", "circle.c", NULL);
        _exit(0);
    }
    r2=fork();
    if(r2==0){
        err = execlp("gcc", "gcc", "-c", "square.c", NULL);
        _exit(0);
    }
    r3=fork();
    if(r3==0){
        err = execlp("gcc", "gcc", "-c", "rectangle.c", NULL);
        _exit(0);
    }
    r4=fork();
    if(r4==0){
        err = execlp("gcc", "gcc", "-c", "main.c", NULL);
        _exit(0);
    }    

    for(int i=0;i<=4;i++){
        waitpid(-1,&s,0);
        es = WEXITSTATUS(s);
        printf("child exit: %d\n", es);
    }

    if(es == 0){
        r5=fork();
        if(r5==0){
            err = execlp("gcc", "gcc", "-o", "prog.out", "circle.o", "square.o", "rectangle.o", "main.o", NULL);
            _exit(0);
        }
    }
    else{
        printf("Compilation Failed, exit status: %d\n", es);
    }

    waitpid(-1,&s,0);
    es = WEXITSTATUS(s);
    printf("child exit: %d\n", es);

    if(es==0){
        r6=fork();
        if(r6==0){
            err = execlp("./prog.out", "./prog.out", NULL);
        _exit(0);
        }
    }
    else{
        printf("Failed\n");
    }

}
			
