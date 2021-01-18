#include <stdio.h>
#include <stdlib.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 */
typedef struct
{
    char *name;
    int starting_time;
    int remaining_time;
} Process;
/*
 *
 */
typedef struct Node
{
    Process data;
    struct Node* next;
} Node;
/*
 *
 */
typedef struct
{
    Node *front,*end;
} Queue;
/*
 *
 */
Queue* init()
{
    Queue *q = malloc(sizeof(Queue));
    q->front=q->end=NULL;
    return q;
}

Node* newNode(Process value)
{
    Node *n = malloc(sizeof(Node));
    n->data = value;
    n->next = NULL;
    return n;
}
/*
 *
 */
int isEmpty(Queue *q)
{
    if(q->front==NULL)
        return 1;
    return 0;
}
/*
 *
 */
Process dequeue(Queue *q)
{
    if(q->front)
    {
        Process val;
        Node *temp = q->front;
        val = temp->data;
        q->front=temp->next;
        free(temp);
        if(q->front == NULL)
            q->end=NULL;
        return val;
    }
}
/*
 *
 */
void enqueue(Queue *q, Process val)
{
    Node *n=newNode(val);
    if(q->front==NULL)
        q->front=q->end=n;
    else{
        q->end->next=n;
        q->end = n;
    }
}
/*
 *
 */
void destroy(Queue *q)
{
    while(!isEmpty(q))
    {
        dequeue(q);
    }
}
/*
 * RoundRobin Scheduling
 */
void RoundRobin(char* filename)
{
    Process *process;
    process = malloc(100*sizeof(Process));
    Queue *q=init();
    char *temp;
    temp=malloc(50);
    int x;
    int c=0;

    FILE *f1;
    f1=fopen(filename,"r");
    if(f1==NULL)
    {
        printf("Error Reading File");
        exit(0);
    }
    fscanf(f1,"%s %s %s %s %d",temp,temp,temp,temp,&x);
    //printf("%d\n",x);


    while(!feof(f1))
    {
        (process+c)->name = malloc(5);
        fscanf(f1,"%s %d %d",(process+c)->name,&((process+c)->starting_time),&((process+c)->remaining_time));
        //printf("%s - %d - %d\n",(process+c)->name,((process+c)->starting_time),((process+c)->remaining_time));
        c++;
    }
    fclose(f1);
    int i,j;
    for(i=0;i<x;i++)
    {
        for(j=0;j<c;j++)
        {
            if((process+j)->starting_time==i)
            {
                enqueue(q,*(process+j));
            }
        }
        if(!isEmpty(q))
        {
            Process temp;
            temp=dequeue(q);
           printf("%s (%d-->%d)",temp.name,i,i+1);
           (temp.remaining_time)--;
           //if(temp.remaining_time!=0)

            if(temp.remaining_time==0)
                printf(" %s aborts",temp.name);
                else
                    enqueue(q,temp);
            printf("\n");
        }
        else
            printf("Idle (%d-->%d)\n",i,i+1);

    }
    printf("Stop\n");


}
/*
 *
 */
int main()
{
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
            RoundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }


    return 0;
}
