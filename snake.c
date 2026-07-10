## All core algorithmic logic—including linked list management, collision handling, and growth—was **entirely designed and coded by myself**. 
As low-level system programming was not yet covered in my first-year university courses, I used **AI as a research assistant** specifically to implement ANSI escape codes (`\033[H`) for smooth terminal rendering and non-blocking input via `<conio.h>`.


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
 struct Node{
    int x; 
    int y; 
    struct Node *next;
 };
 void removee(struct Node *head){
    struct Node *temp = head;
    while(temp->next->next != NULL){
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;

 }
 int load(){
    FILE *file=fopen("score.txt","r");
    if(file == NULL){
        return 0;
    }
    int record = 0;
    fscanf(file , "%d", &record);
    fclose(file);
    return record;
 }
 void save(int *score,int *record){
    FILE *file = fopen ("score.txt","w");
    if(file==NULL){
        printf("The file couldn't be created or opened !");
    }
    if( *score > *record){
        fprintf(file , "%d", *score);
        printf("New record congrats !! Your highest score has been saved succesfully.");
    }
    else{
        fprintf(file , "%d", *record);
        printf("Try to beat your best performance ;)");
    }
    fclose(file);
 }
 struct Node *push( struct Node *head, int x , int y){
    struct Node *newbody=(struct Node *)malloc(sizeof(struct Node));
    newbody->x = x;
    newbody->y = y;
    newbody->next = head;
    head = newbody;
    return head;
 }
 int checkover(struct Node *snake){
    if(snake->x >=  21 || snake->x < 0 || snake->y >= 21  || snake->y < 0){
        return 1;
    }
    struct Node *temp = snake->next;
    while(temp != NULL){
        if(snake->x == temp->x && snake->y == temp->y){
            return 1;
        }
        temp = temp->next;
    }

 }
 struct Node *move(struct Node *snake, char d, int *px, int *py,int *score){
     int newx = snake->x;
     int newy = snake->y;
     if (d == 'z') newy--;
     else if (d == 'd') newx++;
     else if (d == 's') newy++;
     else if (d == 'q') newx--;
     snake = push(snake,newx,newy);
    if(snake->x == *px && snake->y == *py){
        *px = rand() %20;
        *py = rand() %20;
        *score += 10;
    }
    else {
        removee(snake);
       
    }
    return snake;
 }
 int main(){

    struct Node *snake = NULL;
    int record = load();
    int score = 0;
    int px;
    int py;
    int gamer=0;
    char d='d';
    printf("\033[?25l");
    snake=push(snake,8,10);
    snake=push(snake,9,10);
    snake=push(snake,10,10);
    py = rand()%20;
    px = rand()%20;
    printf("\033[2J\033[H");
    while(gamer == 0){
        printf("\033[H");
        for(int y = 0; y <= 20; y++){
          for(int x = 0; x <= 20; x++){
              struct Node *temp = snake;
              int f = 0;
        while ( temp != NULL){
            if (temp->x == x && temp->y == y){
               if (temp == snake){
                   f = 1;   
            }
                else{
                    f = 2;  
                }
             break;
            }
            temp = temp->next;
        }
        if(f==1){
            printf("O");
        }
        else if ( f==2){
            printf("o");
        }
        else if (px == x && py == y){
            printf("X");
        }
        else{
            printf(".");
        }
       }
       printf("\n");
    }
        printf("the score is = %d   ||    the record is = %d\n", score,record);
        if(_kbhit()){
            char dir = _getch();
            if( dir == 'z' && d != 's') d = 'z';
            else if( dir == 's' && d != 'z') d = 's';
            else if( dir == 'q' && d != 'd') d = 'q';
            else if( dir == 'd' && d != 'q') d = 'd';
        }
        snake = move(snake, d, &px , &py, &score);
        if(checkover(snake)== 1){
          printf("\n GAME OVER! \n");
          gamer = 1;
        }
        usleep(200000);
    }
    save(&score, &record);
    while (snake != NULL){
        struct Node *temp = snake;
        snake = snake->next;
        free(temp);
    }
    printf("\033[?25h");
    return 0;
 }
