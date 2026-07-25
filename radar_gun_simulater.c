## Okay this time i tried something new , A real-time, interrupt-driven traffic radar simulator in C that tracks driver recidivism, dynamic speed limits, and calculates gravity-based offense scores. Features an integrated logging system and a post-simulation algorithm to extract the session's worst offender.



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
struct Node{
    char matt[30];
    char brand[15];
    int count ;
    int point;
    int maxspeed;
    struct Node *next ;

};
struct Node *flash(struct Node *head , struct Node *new){
    if( head == NULL){
        head = new;
    }
    else {
        struct Node *temp = head; 
        while ( temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new;
        new->next = NULL;
    }
    return head;

}
struct Vec{
     char mat[30];
     char brand[15];
     int limit;
     float vit;
     char fine[50];
     int count; 
     int point; 

};
void save(struct Vec v , int f){
    FILE *file = fopen("rapport.txt", "a");
    if ( file == NULL){
        printf("The file couldn't be opened or created !");
        return ;
    }
    if (f == -1){
       fprintf(file , "Brand = %s | Plate = %s | Speed = %f | Speed limit = %d | Fine = %s \n", v.brand , v.mat , v.vit, v.limit , v.fine);
    }
    else if ( f == 50 ){
        fprintf(file , "Brand = %s | Plate = %s | Speed = %f | Speed limit = %d | Fine = %s EUR\n", v.brand , v.mat , v.vit, v.limit , v.fine);
    }
    else if (f == 20){
        fprintf(file , "Brand = %s | Plate = %s | Speed = %f | Speed limit = %d | Fine = %s EUR\n", v.brand , v.mat , v.vit, v.limit , v.fine);
    }
    else if (f == 0){
        fprintf(file , "Brand = %s | Plate = %s | Speed = %f | Speed limit = %d | Fine = %s \n", v.brand , v.mat , v.vit, v.limit , v.fine);
    }
    fclose(file);
}
int calcule(int limit , float vit){
    float seuil = (limit*10/100)+limit;
    float seuil2 = (limit*20/100)+limit;
    float seuil3 = (limit*30/100)+limit;
    if ( vit > seuil && vit <= seuil2){
       return 20;
    }
    else if(vit > seuil2 && vit <= seuil3){
       return 50;
    }
    else if(vit > limit && vit <= seuil){
        return 0;
    }
    else if ( vit > seuil3){
        return -1;
    }
    else{
        return 1;
    }
}
int main(){
    struct Node *head = NULL;
    srand(time(NULL));  
    char *matricul[] = {"84509-123-08","00192-109-47","39826-117-31","91628-197-12","16732-121-16"};
    char *brands[] = {"Peugeot", "Renault", "Citroen", "Toyota", "Volkswagen", 
    "BMW", "Mercedes", "Audi", "Ford", "Fiat"};
    int limitt[] ={50 , 80 , 120};
    int index3 = rand()%3;
    if(index3 == 0){
        printf(" === URBAN ROAD ===\n");
      }
    else if(index3 == 1){
        printf("=== SECONDERY ROAD/FOREST ROAD ===\n");
      }
    else{
        printf("=== HIGHWAY ===\n");
      }
   while(!kbhit()){
      struct Vec car;
      if(index3 == 0){
        car.vit = 40 + rand()%50;
      }
      else if(index3 == 1){
        car.vit = 70 + rand()%60;
      }
      else{
       car.vit = 105 + rand()%75;
      }
      int index = rand()%10;
      int index2 = rand() % 5;
      strcpy(car.brand , brands[index]);
      strcpy(car.mat , matricul[index2]);
      car.limit = limitt[index3];
      int returnn = calcule(car.limit , car.vit);
      if ( returnn == -1){
        int gravity = 7;
        struct Node *temp = head;
        int flag = 0;
        while(temp != NULL){
            if(strcmp(car.brand , temp->brand) == 0 && strcmp(car.mat , temp->matt) == 0){
               if ( temp->maxspeed < car.vit){
                    temp->maxspeed = car.vit;
               }
               temp->count++;
               temp->point += gravity;
               flag = 1;
               car.count = temp->count;
               car.point = temp->point;
               break;
            }
            temp = temp->next;
        }
        if(flag == 0){
            struct Node *new = (struct Node *)malloc(sizeof(struct Node));
            strcpy(new->brand , car.brand);
            strcpy( new->matt , car.mat);
            new->count = 1 ;
            new->point = gravity;
            new->maxspeed = car.vit;
            new->next = NULL;
            car.count = 1;
            car.point = gravity;
            head = flash (head , new);
        }
        sprintf(car.fine , "DIRECT TO COURT");
        if(car.count == 1){
           printf("FLASH ! Brand = %s , Speed = %.2f , Plate = %s , DIRECT TO COURT !\n",car.brand , car.vit , car.mat );
           save(car,returnn);
        }
        else{
            printf("FLASH ! Brand = %s , Speed = %.2f , Plate = %s , DIRECT TO COURT ! , this car has been flashed %d times !\n",car.brand , car.vit , car.mat , car.count);
            save(car,returnn);
        }
      }
      else if ( returnn == 50 ){
        int gravity = 5;
        struct Node *temp = head;
        int flag = 0;
        while(temp != NULL){
            if(strcmp(car.brand , temp->brand) == 0 && strcmp(car.mat , temp->matt) == 0){
                if ( temp->maxspeed < car.vit){
                   temp->maxspeed = car.vit;
                }
               temp->count++;
               temp->point += gravity;
               flag = 1;
               car.count = temp->count;
               car.point = temp->point;
               break;
            }
            temp = temp->next;
        }
        if(flag == 0){
            struct Node *new = (struct Node *)malloc(sizeof(struct Node));
            strcpy(new->brand , car.brand);
            strcpy( new->matt , car.mat);
            new->count = 1 ;
            new->point = gravity;
            new->maxspeed = car.vit;
            new->next = NULL;
            car.count = 1;
            car.point = gravity;
            head = flash (head , new);
        }
        sprintf(car.fine , "%d", 50*car.count);
        if(car.count == 1){
           printf("FLASH ! Brand = %s , Speed = %.2f , Plate = %s , Fine = %s EUR\n",car.brand , car.vit , car.mat , car.fine );
           save(car,returnn);
        }
        else{
            printf("FLASH ! Brand = %s , Speed = %.2f , Plate = %s , Fine = %s EUR , this car has been flashed %d times !\n",car.brand , car.vit , car.mat, car.fine , car.count);
            save(car,returnn);
        }

      }
      else if ( returnn == 20 ){
        int gravity = 3;
        struct Node *temp = head;
        int flag = 0;
        while(temp != NULL){
            if(strcmp(car.brand , temp->brand) == 0 && strcmp(car.mat , temp->matt) == 0){
                if ( temp->maxspeed < car.vit){
                   temp->maxspeed = car.vit;
                }
               temp->count++;
               temp->point += gravity;
               flag = 1;
               car.count = temp->count;
               car.point = temp->point;
               break;
            }
            temp = temp->next;
        }
        if(flag == 0){
            struct Node *new = (struct Node *)malloc(sizeof(struct Node));
            strcpy(new->brand , car.brand);
            strcpy( new->matt , car.mat);
            new->count = 1 ;
            new->point = gravity;
            new->maxspeed = car.vit;
            new->next = NULL;
            car.count = 1;
            car.point = gravity;
            head = flash (head , new);
        }
        sprintf(car.fine , "%d", 20*car.count);
        if(car.count == 1){
           printf("FLASH ! Brand = %s , Speed = %.2f , Plate = %s , Fine = %s EUR\n",car.brand , car.vit , car.mat , car.fine );
           save(car,returnn);
        }
        else{
            printf("FLASH ! Brand = %s , Speed = %.2f , Plate = %s , Fine = %s EUR , this car has been flashed %d times !\n",car.brand , car.vit , car.mat, car.fine , car.count);
            save(car,returnn);
        }
      }
      else if ( returnn == 0){
        sprintf(car.fine , "Warning ! You have exceeded the limit");
        printf("FLASH ! Brand = %s , Speed = %.2f , Plate = %s , Warning ! You have exceeded the limit\n",car.brand,car.vit,car.mat);
        save(car,returnn);
      }
      else if ( returnn == 1 ){
        printf("FLASH ! Brand = %s , Speed = %.2f ,Plate = %s , Speed's car is correct.\n", car.brand , car.vit,car.mat);
      }
      usleep(2000000);
  }
    int maxg = -1;
    int maxv = 0;
    struct Node *worst = NULL;
    struct Node *temp = head;
    while ( temp != NULL){
        if(temp->point > maxg){
            maxg = temp->point;
            worst = temp;
        }
        else if(temp->point == maxg && temp->maxspeed > maxv){
            maxv = temp->maxspeed;
            worst = temp;
        }
        temp = temp->next;
    }
    if( worst != NULL){
    printf("The worst driver today was :\n");
    printf(" Brand = %s , Point = %d , Plate = %s , Speed = %d  \n", worst->brand , worst->point , worst->matt , worst->maxspeed);
    }
    temp = head;
    while ( temp != NULL){
       struct Node *seconde = temp->next;
       free(temp);
       temp = seconde;
    }
 printf("\n--- SIMULATION ENDED. ALL FLASHS SAVED IN rapport.txt ---\n");
    return 0;
    

}
