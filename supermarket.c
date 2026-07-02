## This time i write the other type of queue , FIFO , and this code show us dynamic supermarket queue simulator in C utilizing a FIFO queue structure with integrated data persistence and memory safety controls.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node{
    char name[100];
    struct Node *next;
};
struct Queue{
    struct Node *front;
    struct Node *rear;
};
 void enqueue(struct Queue *q, char newname[]){
    struct Node *newnode= (struct Node*)malloc(sizeof(struct Node));
    if( newnode == NULL){
       printf("No enough memory !");
       return;
    }
    strcpy(newnode->name , newname);
    newnode->next = NULL;
    if (q->rear == NULL){
        q->front = newnode;
        q->rear = newnode;
    }
    else {
        q->rear->next = newnode;
        q->rear = newnode;
    }
    printf("[ADDED] %s has been succesfully added to the chaine of costumers !\n ",newnode->name );
 }
 void dequeue(struct Queue *q){
    if(q->front == NULL){
        printf("No costumers yet , the seller is resting\n");
        return;
    }
    struct Node *temp= q->front;
    printf("Is the turn of %s to paye and leave the market\n",temp->name);
    q->front = q->front->next;
    if ( q->front == NULL){
        q->rear = NULL;
    }
    free(temp);

 }
 void dequeue2(struct Queue *q){
    if(q->front == NULL){
        return;
    }
    struct Node *temp= q->front;
    q->front = q->front->next;
    if ( q->front == NULL){
        q->rear = NULL;
    }
    free(temp);

 }
 void display(struct Queue *q){
    struct Node *temp = q->front;
    printf("=== The Queue ===\n");
    if(temp == NULL){
        printf("No costumers for the moment ! \n");
    }
    while(temp != NULL){
        printf("-> %s\n",temp->name);
        temp = temp->next;
    }

 }
 void save(struct Queue *q){
    FILE *file=fopen("queue.txt","w");
    if(file == NULL ){
        printf("ERROR !! Unable to open or create the file !");
        return ;
    }
    struct Node *temp= q->front;
    while (temp != NULL){
       fprintf(file,"%s\n",temp->name);
       temp = temp->next;
    }
    fclose(file);
    printf("Your client's history has been saved succesfully !\n");
 }
 void load(struct Queue *q){
    FILE *file=fopen("queue.txt","r");
    if(file==NULL){
        return ;
    }
    char line[50];
    while(fgets(line,sizeof(line), file)){
        line[strcspn(line , "\n")]=0;
        if(strlen(line) > 0){
            enqueue(q , line);
        }
    }
    fclose(file);
 }
 int main(){
    struct Queue lo;
    lo.front = NULL;
    lo.rear = NULL;
    load(&lo);
    char cname[20];
    int c=10;
    while(c != 0){
        printf("Choose an action to do : \n");
        printf("1. Customer arrives (ENQUEUE)\n");
        printf("2. Process next customer (DEQUEUE)\n");
        printf("3. Display full queue\n");
        printf("0. Close checkout and save system\n");
        printf("Your choice: ");
        scanf("%d", &c);
        if (c==1){
            printf("Customer comming , what's his name ? : \n");
            scanf("%s",cname);
            enqueue(&lo , cname);
        }
        if(c==2){
            dequeue(&lo);
        }
        if(c==3){
            display(&lo);
        }
        if(c==0)
            save(&lo);
    }
    while(lo.front != NULL){
        dequeue2(&lo);
    }
    return 0;
 }
