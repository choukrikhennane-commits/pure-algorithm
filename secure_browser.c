## There is a second code using linkedlist and files , A dynamic browser history simulator in C using LIFO stack linked lists with automated file saving, loading, and mass-deletion features.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node{
    char url[100];
    struct Node *next;
};
 struct Node *push(struct Node *head, char newurl[]){
    struct Node *newnod = (struct Node *)malloc(sizeof(struct Node));
    strcpy(newnod->url, newurl );
    newnod->next = head ;
    head = newnod;
    return head;
 }
struct Node *load(struct Node *head){
    FILE *file = fopen("history.txt", "r");
    if (file == NULL){
        return head;
    }
    char line[100];
    struct Node *tempss = NULL;
    while(fgets(line , sizeof(line), file)){
        line[strcspn(line , "\n")] = 0;
        if( strlen(line) > 0){
            tempss = push(tempss , line);
        }
    }
    fclose(file);
    while(tempss != NULL){
        head = push(head, tempss->url);
        struct Node *tofree = tempss;
        tempss=tempss->next;
        free(tofree);
    }
    return head;
}
 void save(struct Node *head){
    FILE *file=fopen("history.txt", "w");
    if(file == NULL){
        printf("ERROR !! The file couldn't been opened or created !\n");
        return;
    }
    struct Node *temp = head;
    while(temp != NULL){
        fprintf(file," %s\n",temp->url);
        temp = temp->next;
    }
    fclose(file);
    printf("Your history has been saved succesfully !\n");
 }
 struct Node *pop(struct Node *head){
    if (head == NULL){
        printf(" the history is empty !\n");
        return head;
    }
    int x;
    printf("how many pages do you want to delete ? : \n");
    scanf("%d",&x);
    struct Node *temp = head;
    for(int i = 0 ; i< x ; i++){
        temp = head;
        if (temp == NULL){
            printf("there is no more pages to delete ! your history is empty.\n");
            return head;
        }
        else {
            printf("[POP] the page %s has been deleted\n", head->url);
            head = head->next;
            free(temp);
        }
    }
    return head;
 }
 void display(struct Node *head){
    struct Node *temp = head;
      printf("=== You're history ===\n");
      while(temp != NULL){
        printf("-> %s\n", temp->url);
        temp = temp->next;
      }
 }
int main(){
    char saisi[100];
    struct Node *head = NULL;
    head = load(head);
    int i = 0;
    while(i==0){
        int k;
        printf("what do you want to do ( 0 = STOP , 1 = PUSH , 2 = POP ) : \n");
        scanf("%d", &k);
        if (k == 1) {
           printf("which web site you wish to visit ? : \n");
           scanf("%s", saisi);
           head = push(head, saisi);
        }
        if ( k == 2){
            head = pop(head);
        }
        if( k == 0 ){
            i = 1;
        }
    }  
    display(head);
    save(head);
    return 0;
    

}
