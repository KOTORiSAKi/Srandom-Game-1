#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
//------------------------
//*release V.1.0.1
//------------------------
struct character{
    int hp;
}player = {0}, enemy = {0};
//------------------------
int log[6] = {0,0,0,0};//build and reset to 0
int if_no_config = 0;
//
int lvl_rate = 0;
int exp[22] = {0,0,10000,25000,40000,65000,95000,130000,170000,220000,280000,350000,430000,520000,620000,730000,850000,980000,1100000,2200000,3300000,5000000}; 
int atk[21] = {0,100,150,220,300,400,480,560,620,700,800,900,1000,1200,1500,2000,3000,5000,8000,10000,12000};
int hp[21]= {0,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,12000,14000,16000,18000,20000,25000,40000,60000,80000,100000};
int potion[6] = {0,1000,3500,7000,10000,15000};
char *rank_name[] = {"\0","Newbie","Common Player","Pro Player","Epic Player","Legend Player"};
char *enemy_name[] = {"\0","Noob","Common","Pro","Pro Max","Ultra Pro Max"};
//? Newbie 1-4 | Common 5-8 | Pro 9-12 | Epic 13-16 | Legend 17-20
//------------------------
void game_name_UI(){printf("\t\t\\__________________/ \n\t\t/                  \\ \n\t\t| Welcome to Game 1|\n\t\t\\__________________/ \n\t\t/                  \\ \n\n\n");}
void lvl_information(){
    system("cls");//!clear
    printf("LVL  ATK         HP     EXP\n");
    for(int i = 1; i<=20; i++){
        if(i==20){printf(" %d : %d - %d | %d | %d", i, atk[i], atk[i]+atk[i]-1, hp[i], exp[i]);continue;}
        printf(" %d : %d - %d | %d | %d - %d\n", i, atk[i], atk[i]+atk[i]-1, hp[i], exp[i] , exp[i+1]-1);
    }
    printf("\n\n\nDatas were stored from \"config.txt\"\nEXP : %d\nlvl : %d\n", log[1], log[2]);
    printf("COIN : %d\n\n", log[3]);
    printf("Your HP left : %d\n", log[4]);
    printf("Enemy's HP left : %d\n", log[5]);
    printf("\n\n\tPress Enter to continue...");
    getchar();
    getchar();
}
void build_file(){
    if_no_config = 0;
    char filename[] = "config.txt";
    FILE *fp = fopen(filename, "w");
    fprintf(fp ,"No value");fclose(fp);
}
void read_file(){
    char filename[] = "config.txt";
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        log[0] = 0;//*confirmation
        log[1] = 0;//?exp
        log[2] = 0;//?lvl
        log[3] = 0;//?coin
        log[4] = 0;//?player HP
        log[5] = 0;//?enemy HP
        if_no_config = 1;
        return 1;
    }
    int i = 0;
    while (fscanf(fp, "%d", &log[i])==1){
        ++i;
    }
    fclose(fp);
}
void write_file(){
    if_no_config = 0;
    char filename[] = "config.txt";
    FILE *fp = fopen(filename, "w");
    if (fp == NULL){
        printf("Error opening the file %s", filename);
        return -1;
    }
    fprintf(fp , "%d\n%d\n%d\n%d\n%d\n%d",log[0],log[1],log[2],log[3],log[4],log[5]);
    fclose(fp);
    for(int i = 0; i<=5; ++i){
        log[i] = '\0';
    }
    read_file();
}
//------------------------
int main(){
    printf("\nBy Saki\n");
    system("cls");//!clear
    srand(time(NULL));//*activate random number function
    setup();
    //printf("\n%d | %d | %d\n", log[1], log[2], log[3]);//!debugger
    if(if_no_config == 1){
        printf("There is no save file to store or has no any current data!");
        printf("\nPress Enter to continue...");
        getchar();
    }
    start_menu();
    exit(0);
}
void setup(){
    read_file();
}
void set_lvl_rate(){
    if(log[2] >= 1 && log[2] <= 4){lvl_rate = 1;}
    if(log[2] >= 5 && log[2] <= 8){lvl_rate = 2;}
    if(log[2] >= 9 && log[2] <= 12){lvl_rate = 3;}
    if(log[2] >= 13 && log[2] <= 16){lvl_rate = 4;}
    if(log[2] >= 17 && log[2] <= 20){lvl_rate = 5;}
}
void start_menu(){
    char choice1[100], choice2[100];
    int temp1 = 0, temp2 = 0;
    while(1){
        system("cls");
        game_name_UI();
        switch(log[0]){
            case 1:
            printf("[1] New game\n[2] Current game {level %d}\n[3] leave", log[2]);
            break;
            case 0:
            printf("[1] New game\n[2] Current game {No current save}\n[3] leave");
            break;
        }
        if(temp1 == 1){
            printf("\nOnly 1 - 3 can be used");
        }
        if(temp2 >= 2){printf("\t\tSeriously!");}
        printf("\nchoose => ");
        scanf("%s", &choice1);
        ++temp2;
        if(strcmp(choice1,"1") == 0 || strcmp(choice1,"2") == 0 || strcmp(choice1,"3") == 0 || strcmp(choice1,"LVL_information") == 0){temp1 = 0;temp2 = 0;break;}
        temp1 = 1;
    }
    if(strcmp(choice1,"LVL_information")==0){
        lvl_information();
        start_menu();
    }
    if(log[0] == 0 && strcmp(choice1,"2") == 0){
        system("cls");//!clear
        printf("This option is not available!\nPress Enter to continue...");
        getchar();
        getchar();
        system("cls");//!clear
        start_menu();
    }
    if(strcmp(choice1,"3") == 0){
        exit(0);
    }
    //-----------------
    if(strcmp(choice1,"1") == 0){
        system("cls");//!clear
        while(1){
            printf("\n\n Are you really sure to delete your current data (y/n)=> ");
            scanf("%s", &choice2);
            if(strcmp(choice2,"y")==0){break;}
            if(strcmp(choice2,"n")==0){start_menu();}
            system("cls");//!clear
            printf("Only (y & n)");
        }
        new_game();
    }
    if(strcmp(choice1,"2") == 0){
        current_game();
    }
}
void new_game(){
    system("cls");//!clear
    log[0] = 1;
    log[1] = 0;
    log[2] = 1;
    log[3] = 0;
    log[4] = hp[log[2]];
    log[5] = hp[log[2]];
    write_file();
    printf("Starting");
    Sleep(300);
    for(int i = 1; i <= 3; ++i){
        printf(".");
        Sleep(300);
    }
    system("cls");//!clear
    logic_game();
}
void current_game(){
    char choice1[100];
    system("cls");//!clear
    printf("Loading");
    Sleep(300);
    for(int i = 1; i <= 3; ++i){
        printf(".");
        Sleep(300);
    }
    while(1){
        system("cls");//!clear
        printf("\n----Your current save----\n");
        printf("EXP : %d\n", log[1]);
        printf("COIN : %d\n", log[3]);
        printf("Your HP left : %d\n", log[4]);
        printf("Your atk : %d-%d\n", atk[log[2]], atk[log[2]]+atk[log[2]]-1);
        printf("Enemy's HP left : %d\n", log[5]);
        printf("Enemy's atk : %d-%d\n", atk[log[2]], atk[log[2]]+atk[log[2]]-1);
        printf("\n\n\n\tAccept (y/n) => ");
        scanf("%s", &choice1);
        if(strcmp(choice1,"y") == 0){
            system("cls");//!clear
            printf("Loading");
            Sleep(300);
            for(int i = 1; i <= 3; ++i){
                printf(".");
                Sleep(300);
            }
            logic_game();
        }
        if(strcmp(choice1,"n") == 0){
            start_menu();
        }
        system("cls");//!clear
        printf("Try again");
        Sleep(2000);
        }
}
void logic_game(){
    system("cls");//!clear
    set_lvl_rate();
    int temp1 = 0;
    int exp_temp = 0;
    int switcher = 0;
    int damage = 0;
    int temp_coin = 0;
    int temp_bonus_coin = 0;
    int temp_bonus_exp = 0;
    char choice1[100];
    char choice2[100];
    char choice3[100];
    char choice4[100];
    char choice5[100];
    printf("Your current status\n-----------------\n");
    if(log[2] == 20){
        printf("LVL : MAXIMUM\n");
    }else{ 
        printf("LVL : %d\n" , log[2]);
    }
    player.hp = log[4];
    enemy.hp = log[5];
    printf("EXP : %d\tNext lvl at %d exp\n", log[1], exp[log[2]+1]);
    printf("COIN : %d\n", log[3]);
    printf("\n-----------------\n");
    printf("Player's rank : %s\n", rank_name[lvl_rate]);
    printf("Your HP left : %d\n", player.hp);
    printf("Your atk : %d-%d\n\n", atk[log[2]], atk[log[2]]+atk[log[2]]-1);
    printf("Enemy's type : %s\n", enemy_name[lvl_rate]);
    printf("Enemy's HP left : %d\n", enemy.hp);
    printf("Enemy's atk : %d-%d\n", atk[log[2]], atk[log[2]]+atk[log[2]]-1);
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    system("cls");//!clear
    printf("\n\n\t\tWELCOME TO HELL!!\n\n\n");
    Sleep(2000);
    for(int i = 3; i>=1; --i){
        switcher = rand()%2+1;
        system("cls");//!clear
        printf("\n\n\t\t%d turns left", i);
        Sleep(1500);
        system("cls");//!clear
        switch(switcher){
            case 1:
            printf("\n\tPlayer damaged enemy\n\n");
            damage = atk[log[2]] + rand()%atk[log[2]];
            printf("Enemy HP -%d", damage);
            enemy.hp -= damage;
            temp_coin += damage;
            printf("\n\n\tPress Enter to continue...");
            getchar();
            exp_temp += damage*2;
            if(enemy.hp <= 0){enemy.hp = 0;goto skip_enemy;}//set 0
            system("cls");//!clear
            printf("Enemy's HP left : %d\n", enemy.hp);
            printf("You got %d coin\nNow you have %d coin in wallet", damage, log[3]+temp_coin);
            printf("\n\n\tPress Enter to continue...");
            getchar();
            break;
            //--------------------------
            case 2:
            printf("\n\tEnemy has attacked you\n\n");
            damage = atk[log[2]] + rand()%atk[log[2]];
            printf("Enemy HP -%d", damage);
            player.hp -= damage;
            printf("\n\n\tPress Enter to continue...");
            getchar();
            if(player.hp <= 0){player.hp = 0;goto skip_player;}//set 0
            system("cls");//!clear
            printf("Your HP left : %d\n", player.hp);
            printf("\n\n\tPress Enter to continue...");
            getchar();
            break;
        }
    }
    system("cls");//!clear
    printf("\n\n\n\t\t\tFight has ended");
    Sleep(2000);
    //-------------------------
    system("cls");//!clear
    if(player.hp > 0){
        log[3] += temp_coin;
        log[1] += exp_temp;
        if(enemy.hp <= 0){//if enemy die
            skip_enemy:
            temp_bonus_coin = hp[log[2]]/2;
            temp_bonus_exp = exp[log[2]+1]/9;
            log[3] += temp_bonus_coin;
            log[1] += temp_bonus_exp;
            system("cls");//!clear
            printf("\n\n\t\tYOU WIN!\n\n\n");
            printf("You got %d coin bonus and %d exp bonus", temp_bonus_coin, temp_bonus_exp);
            Sleep(2000);
            system("cls");//!clear
            printf("\n\n\t\tYOU WIN!\n\n\n");
            printf("EXP : %d\tNext lvl at %d exp\n", log[1], exp[log[2]+1]);
            printf("COIN : %d\n", log[3]);
            printf("\n\n\n\nPress Enter to continue...");
            getchar();
            player.hp = hp[log[2]];
            enemy.hp = hp[log[2]];
            printf("You got renew HP : %d\n", player.hp);
            temp1 = 1;
        }
        if(log[1] >= exp[log[2]+1]){// Lvl up!
            loop1:
            log[2] += 1;
            if(log[2] >= 21){max_lvl();}
            if(log[1] >= exp[log[2]+1]){goto loop1;}
            player.hp = hp[log[2]];
            enemy.hp = hp[log[2]];
            system("cls");//!clear
            printf("\n\n\t\tLVL UP!!\n\n\tYou got %d lvl\n\n\n\n\t", log[2]);
            printf("Press Enter to continue...");
            getchar();
            system("cls");//!clear
            printf("Your hp has renewed at %d\n\n\n", player.hp);
            printf("Press Enter to continue...");
            getchar();
            temp1 = 1;
        }
        set_lvl_rate();
        if(log[3] >= potion[lvl_rate] && temp1 != 1 && hp[log[2]] > player.hp){
            loop2:
            temp1 = 0;
            printf("\n\n\tCOIN : %d\n\tYour HP left : %d\n\tEnemy's HP left : %d\n\n\tNeed to use potion?\tUse %d coin\n\t (y/n)=> ", log[3], player.hp, enemy.hp, potion[lvl_rate]);
            scanf("%s", choice1);
            system("cls");//!clear
            if(strcmp(choice1,"y")==0 && log[3] >= potion[lvl_rate]){
                log[3] -= potion[lvl_rate];
                player.hp += (hp[log[2]]-player.hp)/2;
                printf("\n\n\tYour HP left : %d\n", player.hp);
                printf("Press Enter to continue...");
                getchar();
                getchar();
            }
            if(strcmp(choice1,"y") != 0 && strcmp(choice1,"n") != 0){system("cls");printf("Try again");goto loop2;}
        }
        temp1 = 0;
        log[4] = player.hp;
        log[5] = enemy.hp;
        while(1){
            system("cls");//!clear
            printf("Your HP left : %d\n", log[4]);
            printf("Enemy's HP left : %d\n\n\n", log[5]);
            printf("Want to continue (y/n) => ");
            scanf("%s", &choice2);
            if(strcmp(choice2,"y") == 0){
                write_file();
                logic_game();
            }
            if(strcmp(choice2,"n") == 0){
                write_file();
                start_menu();
            }
            system("cls");//!clear
            printf("Try again");
            Sleep(2000);
        }
    }
    else{
        skip_player:
        system("cls");//!clear
        printf("\n\n\n\t\t\tYOU DIED!\n\t\t\tGAME OVER\n\n\n\n");
        printf("\t\tPress Enter to continue...");
        getchar();
        system("cls");//!clear
        printf("You will be stored back to the last status\n\n\n");
        printf("\t\tPress Enter to continue...");
        getchar();
        while(1){
            system("cls");//!clear
            printf("Want to continue (y/n) => ");
            scanf("%s", &choice5);
            if(strcmp(choice5,"y") == 0){
                log[4] = hp[log[2]];
                log[5] = hp[log[2]];
                write_file();
                logic_game();
            }
            if(strcmp(choice5,"n") == 0){
                log[4] = hp[log[2]];
                log[5] = hp[log[2]];
                write_file();
                start_menu();
            }
            system("cls");//!clear
            printf("Try again");
            Sleep(2000);
        }
    }
    write_file();
}
void max_lvl(){
    system("cls");//!clear
    printf("\n\n\n\n\t\tThank you for playing my game\n\n\n\n\n\tYou have done all game here. You are a hero!\n");
    printf("Press Enter to continue...");
    getchar();
    for(int i = 0; i <= 5; i++){
        log[i] = 0;
    }
    write_file();
    start_menu();
}