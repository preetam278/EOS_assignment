#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MQ_KEY 0x1234

typedef struct msg {
	long type;
	int n1;
	int n2;
	int sum;
}
msg_t;

int main()
	{
		int mqid,ret,s;
		 //create message queue
		 mqid = msgget(MQ_KEY,IPC_CREAT | 0600);
		 if(mqid < 0)
		 {
			 perror("msgget() failed");
			 exit(1);
		 }
		 ret = fork();
		 if(ret ==0)
		 {
			 // Child process: initialize and send the message
        msg_t m1;
        m1.type = 1;
        printf("sender: enter two numbers for the addition: ");
        scanf("%d %d", &m1.n1, &m1.n2);
        ret = msgsnd(mqid, &m1, sizeof(m1) - sizeof(long), 0);  // Correct size calculation
        if (ret < 0) {
            perror("msgsnd() failed");
            exit(1);
        }
        printf("sender: message sent\n");

        // Receive the sum from the parent
        ret = msgrcv(mqid, &m1, sizeof(m1) - sizeof(long), 1, 0);  // Correct size calculation
        if (ret < 0) {
            perror("msgrcv() failed");
            exit(1);
        }
        printf("sender: received sum from the parent is %d\n", m1.sum);
        exit(0);
    } else if (ret > 0) {
        // Parent process: receive the message and print it
        msg_t m2;
        printf("receiver: waiting for the message...\n");
        ret = msgrcv(mqid, &m2, sizeof(m2) - sizeof(long), 1, 0);  // Correct size calculation
        if (ret < 0) {
            perror("msgrcv() failed");
            exit(1);
        }
        printf("receiver: message received: %d %d\n", m2.n1, m2.n2);

        // Calculate sum and send it back to the child
        m2.sum = m2.n1 + m2.n2;
        ret = msgsnd(mqid, &m2, sizeof(m2) - sizeof(long), 0);  // Correct size calculation
        if (ret < 0) {
            perror("msgsnd() failed");
            exit(1);
        }
        printf("receiver: sent addition to the child\n");

        // Wait for child to terminate and clean up
        wait(&s);

        // Destroy the message queue
        msgctl(mqid, IPC_RMID, NULL);
    } else {
        perror("fork() failed");
        exit(1);
    }

    return 0;
}
