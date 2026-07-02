## After the first program , one year left , I wrote this one . A dynamic task manager in C using priority-sorted linked lists with automatic file-based saving and loading features.




#include <stdio.h>
#include <stdlib.h>
struct Node{
    int id;
    int p;
    int st;
    struct Node *next;
};
struct Node* sort(struct Node *head, struct Node *neww ){
    struct Node *temp = head;
    if (head == NULL || neww->p > head->p ){
        neww->next = head ;
        head = neww;
    }
    else {
        temp = head ;
        while (temp->next != NULL && temp->next->p > neww->p){
            temp = temp->next;
        }
        neww->next = temp->next;
        temp->next = neww;
        }
    return head;
}
struct Node* load(struct Node *head, int *kp){
    FILE *file=fopen("task.txt","r");
    if(file==NULL){
        return head;
    }
    int id;
    int p;
    int st;
    while(fscanf(file ,"Task's ID : %d | Priority : %d | Statut : %d\n" , &id, &p, &st)==3){
        struct Node *oldtask=(struct Node *)malloc(sizeof(struct Node));
        oldtask->id= id;
        oldtask->p = p;
        oldtask->st = st;
        oldtask->next = NULL;
        head = sort(head, oldtask);
        if (id > *kp){
            *kp = id;
        }
    }
    fclose(file);
    return head;
}
void display(struct Node *head){
    struct Node *temp = head;
    while(temp!=NULL){
        printf("Task's ID : %d | Priority : %d | Statut : %s\n", temp->id, temp->p, (temp->st == 1)? "DONE" : "PENDING");
        temp= temp->next;
    }
}
void save(struct Node *head){
    FILE *file;
    struct Node *temp = head;
    file = fopen("task.txt","w");
    if (file == NULL){
        printf("Windows couldn't open or create the file ! ");
        return ;}
    while(temp!=NULL){
        fprintf(file,"Task's ID : %d | Priority : %d | Statut : %d\n", temp->id, temp->p, temp->st);
        temp = temp->next;
    }
    printf("Your're Tasks has been saved succesfully !\n");
    fclose(file);
    
}
int main(){
    struct Node *head = NULL;
    int check = 1;
    int s;
    int k = 0;
    head = load(head,&k);
   while(check == 1){
     printf("How much Tasks you have ? : \n");
     scanf("%d", &s);
     for(int i = 0; i<s; i++){
        struct Node *neww = (struct Node *)malloc(sizeof(struct Node));
        neww->id = k+1;
        neww->next = NULL;
        printf("=== Create Task ID °%d ===\n",k+1);
        printf("Choose the priority (1-5) : \n");
        scanf("%d",&neww->p);
        while(neww->p <1 || neww->p > 5){
            printf("Please sir , Choose a number within this interval (1-5) : \n");
            scanf("%d",&neww->p);
           }
        printf("Choose the statut ( 1 = done , 0 = not yet ) : \n");
        scanf("%d",&neww->st);
        while(neww->st != 1  && neww->st != 0){
            printf("Please sir , Choose only '1' or '0' : \n");
            scanf("%d",&neww->st);
           } 
              head = sort(head ,neww);
              k += 1;
        }
     display(head);
     save(head);
     printf("Do you want to add another tasks ? ( 1 = yes , 0 = no ) :  \n");
     scanf("%d", &check);
   }

    return 0;
}
