#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <colors>
#include <conio.h>
#include<strings.h>
#include <time.h>
#define SIZE 30
#include <string.h>
FILE*f1;
FILE*f2;
FILE*f3;
FILE*top;
typedef struct{
char name[20];
int score;
}rankok;
rankok rankarray[10]={"...",0};
int c_move=1;//indication for number computer movements

char points[6];

typedef struct
{
    char name[20] ;
    char letter ;
    int moves;
    int score;
} players;


time_t start, end ;
void delete_array(int s,int array[s],int size,char a[size][size]);
void computer_move(int  size, char a[size] [size],int *ii,int *jj);
void Read_first(char points[5],int n,int *x);
void check_box(int n,int size,char a[size][size],char letter,int *w) ;
void Read_points(char points[5],int n);
void print_arr(int size,char a[size][size]);
void analyze_points(char points[5],int n,int *x) ;
void find_index(char points[5],int n,int size,char a[size][size], int turn,int *x) ;
void remove_box(int index1,int index2,int size,char a[size][size]);
void det_winner(players player1,players player2) ;
void change_save(char *slot);
int check_file(char slot);
void save(int size,char a[size][size],players x,players y,char type[2],int turn,int total_lines, int clock,char slot,char mode);
void print_word();
void How_to_play()
{
    setTextColor(stdout, TC_YELLOW);
    printf(" To make aline, you should choose two points.\n To choose a point choose row,column respectively.\n");
        setTextColor(stdout, TC_LIGHTGRAY);

}

void undo_turn (int turn, players *player1, players *player2,int w );
void general_turn (int turn, players (*player1), players (*player2),int w );
void display (players player1, players player2, int y, int time,int tutn);
void display2 (players player1, players computer, int y, int time, int turn);
void who_turn(players x, players y,int turn);
void Winner(players x,players y);

void gotoxy(int x, int y)  //display ouput where you want .
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int main()
{ int k=37;
print_word();
      gotoxy(24,18);
    printf("please wait........loading");
    gotoxy(30,20);
    for(int i=0;i<80;i++){
     if(i%2==0)
        setTextColor(stdout, TC_DARKGRAY);
        Beep(k,20);
        k+=100;
         printf("%c",219);
              Sleep(20);
     setTextColor(stdout, TC_LIGHTGRAY);
    }

    printf("\n\n \t\t\t\t\t\t\t\t successfully loaded");
    Sleep(1000);
label :
new_one:
setTextColor(stdout, TC_YELLOW);
    char  slot;    //the game points
    system("cls");
    print_word();
    setTextColor(stdout, TC_YELLOW);
    gotoxy(40,10);
    printf(" \t\t Welcome to Dots & Boxs: \n\n");
    gotoxy(45,12);
    printf("1.New game.");
        gotoxy(45,13);
    printf("2.Load game.");
        gotoxy(45,14);
    printf("3.Top ten.");
        gotoxy(45,15);
    printf("4.EXit.\n");
    gotoxy(40,16);
    printf("please, press 1:4 to make your choise: ");
    char game ;
    scanf(" %c",&game);
    while(getchar()!='\n');
    system("cls");
    while (game!='1'&&game!='2'&&game!='3'&&game!='4')
    {
        gotoxy(45,12);
       printf("1.New game.");
        gotoxy(45,13);
       printf("2.Load game.");
        gotoxy(45,14);
      printf("3.Top ten.");
        gotoxy(45,15);
       printf("4.EXit.\n");
        gotoxy(40,16);
        printf("please,Enter a valid choice: ");
        scanf(" %c",&game);
        while(getchar()!='\n');
        system("cls");

    }
    system("cls");
    if(game=='1') //New game loop
    {   char mode;
        load:if(game=='1'||game=='2'){
        if(game=='1'){
                print_word();
        setTextColor(stdout, TC_YELLOW);
                gotoxy(45,12);
                printf("Choose the game mode :");
                gotoxy(45,13);
                printf("1.Beginner.");
                gotoxy(45,14);
                printf("2.Expert.");
                gotoxy(40,16);
                printf("please, press 1:2 to make your choise: ");
                scanf(" %c",&mode);
                while(getchar()!='\n');
                system("cls");
        while (mode!='1'&&mode !='2')
        {
            print_word();
            setTextColor(stdout, TC_YELLOW);
                gotoxy(45,12);
                printf("Choose the game mode :");
                gotoxy(45,13);
                printf("1.Beginner.");
                gotoxy(45,14);
                printf("2.Expert.");
                gotoxy(40,16);
                printf(" please,Enter a valid choice: ");
                scanf(" %c",&mode);
                while(getchar()!='\n');
                system("cls");
        }}
        else{
                if(slot=='a'){
                    f1=fopen("file1.txt","r");
                    mode=getc(f1);
                    }
                else if(slot=='b'){
                        f2=fopen("file2.txt","r");
                        mode=getc(f2);
                        }
                else{
                     f3=fopen("file3.txt","r");
                     mode=getc(f3);
                }
        }
        int n,m ;
        if(mode=='1')
        {
            n=2;
            m=3;
        }
        else
        {
            n=5;    // set the mode of game
            m=6;
        }

        int size = (n+1)*2 ; //size of array to show grid ./
        char a[size][size] ; // size of array is (n+1)*2 ;
        int i,j,row=49,col=49; // initial value for row,col is the asci code for no 1.
        for(i=0; i<size; i++)
        {
            for(j=0; j<size; j++)
            {
                if(i==0&&j%2!=0)
                {
                    a[i][j]=row;
                    row++;
                }
                else if(j==0&&i%2!=0 )
                {
                    a[i][j]=col;
                    col++;
                }
                else if (i%2!=0 && j%2!=0)
                {
                    a[i][j]=254;
                }
                else
                    a[i][j]=' ' ;
            }
        }
        system("cls");
        char type[2];
        if(game=='1'){
                print_word();
               setTextColor(stdout, TC_YELLOW);
                        gotoxy(45,12);
                        printf("Choose the game type :");
                        gotoxy(45,13);
                        printf("1.Human vs Human.");
                        gotoxy(45,14);
                        printf("2.Human vs computer.");
                        gotoxy(40,16);
                        printf("please, press 1:2 to make your choice: ");
                        scanf("%s",type);
                        system("cls");
        while ( (strcmp(type,"1")!=0 && strcmp(type,"2")!=0 ) || strlen(type)>1 )
        {
            print_word();
            setTextColor(stdout, TC_YELLOW);
                        gotoxy(45,12);
                        printf("Choose the game type :");
                        gotoxy(45,13);
                        printf("1.Human vs Human.");
                        gotoxy(45,14);
                        printf("2.Human vs computer.");
                        gotoxy(40,16);
                        printf("please,Enter a valid choice: ");
                        scanf("%s",type);
                        system("cls");
        }
        system("cls");
        setTextColor(stdout, TC_LIGHTGRAY);
        }
        else{
            if(slot=='a'){
                fgets(type,2,f1);
                    }
                else if(slot=='b'){
                         fgets(type,2,f2);
                        }
                else{
                   fgets(type,2,f3);
                }

        }

        if(strcmp(type,"1")==0) // human vs human loop
        {
            players player1;
            players player2;
            int turn,x=0,total_lines,score,w,time_taken,move_time;
            if(game=='1'){
            setTextColor(stdout, TC_LIGHTRED);
            gotoxy(43,10);
            printf("enter first player name: ");
            scanf("%s",player1.name);
            setTextColor(stdout, TC_LIGHTGRAY);
            system("cls");
            setTextColor(stdout, TC_LIGHTBLUE);
            gotoxy(43,10);
            printf("enter second player name: ");
            scanf("%s",player2.name);
            system("cls");
            setTextColor(stdout, TC_LIGHTGRAY);
            How_to_play();
            Sleep(3000);
            system("cls");
            turn=1;
            player1.score=0;
            player1.moves=0;
            player2.score=0;
            player2.moves=0;
            w=0;score=0;x=0;
            total_lines=size*n;
            time_taken=0;
            }
            else{
                 if(slot=='a'){
                 fread(a,sizeof(char),size*size,f1);
                 turn=getw(f1);
                 fread(&player1,sizeof(players),4,f1);
                 fread(&player2,sizeof(players),4,f1);
                 total_lines=getw(f1);
                 time_taken=getw(f1);
                  fclose(f1);

                    }
                else if(slot=='b'){
                fread(a,sizeof(char),size*size,f2);
                 turn=getw(f2);
                 fread(&player1,sizeof(players),4,f2);
                 fread(&player2,sizeof(players),4,f2);
                 total_lines=getw(f2);
                 time_taken=getw(f2);
                  fclose(f2);

                        }
                else{
                 fread(a,sizeof(char),size*size,f3);
                 turn=getw(f3);
                 fread(&player1,sizeof(players),4,f3);
                 fread(&player2,sizeof(players),4,f3);
                 total_lines=getw(f3);
                 time_taken=getw(f3);
                  fclose(f3);

                }
            }
            print_arr(size,a);
            while(1)
            {
                w=0;
                move_time=0;
                if(turn==1)

                {
                    if(total_lines==0)
                         {system("cls");
                    det_winner( player1,player2);
                    Sleep(5000);
        char b[2];
        system("cls");
        setTextColor(stdout, TC_YELLOW);
        printf("\n\n\n\n\n\n\n\t\t\t\t\t\t1.To main menu\n");
        printf("\t\t\t\t\t\t any key.To Exit\n ");
        printf("\t\t\t\t\t\press 1:any key  >>> ");
        scanf("%s",b);
        setTextColor(stdout, TC_LIGHTGRAY);
        system("cls");
        if(strcmp(b,"1")!=0){
            goto newm ;
        }
        else
            goto label ;






                    }
                    start =time(NULL);
                    who_turn(player1,player2,turn);
                    system("cls");
                    score = 0;
                    display(player1,player2,total_lines,time_taken,turn);
                    print_arr(size,a);
                    find_index(points,n,size,a,turn,&x);
                    if(strcmp(points,"Undo")==0||strcmp(points,"U")==0||strcmp(points,"undo")==0||strcmp(points,"u")==0)
                    {
                        check_box(n,size,a,' ',&w);
                        if(w==0)
                        {
                            turn=0;
                        }
                        score=w;
                        undo_turn(turn,&player1,&player2,score);
                        total_lines+=2 ;
                    }
                    else if(strcmp(points,"Redo")==0||strcmp(points,"R")==0||strcmp(points,"redo")==0||strcmp(points,"r")==0) //redo
                    {
                        check_box(n,size,a,'A',&w);
                        score=w;
                        general_turn(turn,&player1,&player2,score);
                    }
                    else if(strcmp(points,"Save")==0||strcmp(points,"S")==0||strcmp(points,"save")==0||strcmp(points,"s")==0) //redo
                    {

                     system("cls");
                     w=-1;
                     change_save(&slot);
                     save(size,a,player1,player2,type,turn,total_lines,time_taken,slot,mode);
                        total_lines+=1;
                        x=0;
                    }
                         else if(strcmp(points,"Exit")==0||strcmp(points,"E")==0||strcmp(points,"exit")==0||strcmp(points,"e")==0) //redo
                    {system("cls");
                        goto new_one;

                    }


                    else
                    {
                        check_box(n,size,a,'A',&w);
                        print_arr(size,a);
                        score =w;
                        general_turn(turn,&player1,&player2,score);
                    }
                    system("cls");
                    if (w!=0)
                        turn=1;

                    else
                        turn=0;

                    total_lines--;
                    end =time(NULL);
                    move_time=end-start;
                    time_taken+=move_time;

                }
                move_time=0;
                if(turn==0)
                {
                    if(total_lines==0)
                         {system("cls");
                    det_winner( player1,player2);
                    Sleep(5000);
        char b[2];
        system("cls");
        setTextColor(stdout, TC_YELLOW);
        printf("\n\n\n\n\n\n\n\t\t\t\t\t\t1.To main menu\n");
        printf("\t\t\t\t\t\t any key.To Exit\n ");
        printf("\t\t\t\t\t\press 1:any key  >>> ");
        scanf("%s",b);
        setTextColor(stdout, TC_LIGHTGRAY);
        system("cls");
        if(strcmp(b,"1")!=0){
            goto newm ;
        }
        else
            goto label ;






                    }
                    start =time(NULL);
                    who_turn(player1,player2,turn);
                    system("cls");
                    score =0 ;
                    display(player1,player2,total_lines,time_taken,turn);
                    print_arr(size,a);
                    find_index(points,n,size,a,turn,&x);
                    if(strcmp(points,"Undo")==0||strcmp(points,"U")==0||strcmp(points,"undo")==0||strcmp(points,"u")==0)
                    {
                        check_box(n,size,a,' ',&w);
                        if(w==0)
                        {
                            turn=1;
                        }
                        score=w;
                        undo_turn(turn,&player1,&player2,score);
                        total_lines +=2 ;
                    }
                    else if(strcmp(points,"Redo")==0||strcmp(points,"R")==0||strcmp(points,"redo")==0||strcmp(points,"r")==0)
                    {
                        check_box(n,size,a,'B',&w);
                        score=w;
                        general_turn(turn,&player1,&player2,score);

                    }
                    else if(strcmp(points,"Save")==0||strcmp(points,"S")==0||strcmp(points,"save")==0||strcmp(points,"s")==0) //redo
                    {
                     system("cls");
                     w=-1;
                     change_save(&slot);
                     x=0;
                     save(size,a,player1,player2,type,turn,total_lines,time_taken,slot,mode);
                        total_lines+=1;
                    }
                      else if(strcmp(points,"Exit")==0||strcmp(points,"E")==0||strcmp(points,"exit")==0||strcmp(points,"e")==0) //redo
                    {system("cls");
                        goto new_one;

                    }
                    else
                    {
                        check_box(n,size,a,'B',&w);
                        print_arr(size,a);
                        score=w ;
                        general_turn(turn,&player1,&player2,score);
                    }
                    system("cls");
                    if (w!=0)
                        turn=0;
                    else
                        turn=1;
                    total_lines--;
                    end =time(NULL);
                    move_time=end-start;
                    time_taken+=move_time;

                }


            }


        }
        else   //  player vs computer
        {
            int s=2,array[SIZE],g=0,x=0;
            int turn,total_lines,score,w,time_taken,move_time;
            players player1;
           players comp= {"Computer",'B',0,0};;
            if(game=='1'){
            gotoxy(43,10);
            setTextColor(stdout, TC_LIGHTRED);
            printf("enter player name: ");
            scanf("%s",player1.name);
            setTextColor(stdout, TC_LIGHTGRAY);
            system("cls");
            How_to_play();
            Sleep(3000);
            system("cls");
            turn=1;
            player1.score=0;
            player1.moves=0;
            w=0;score=0;
            total_lines=size*n;
            time_taken=0;
            x=0;
            }
            else{
                        if(slot=='a'){
               fread(a,sizeof(char),size*size,f1);
                 turn=getw(f1);
                 fread(&player1,sizeof(players),4,f1);
                 fread(&comp,sizeof(players),4,f1);
                 total_lines=getw(f1);
                 time_taken=getw(f1);
                  fclose(f1);

                    }
                else if(slot=='b'){
                 fread(a,sizeof(char),size*size,f2);
                 turn=getw(f2);
                 fread(&player1,sizeof(players),4,f2);
                 fread(&comp,sizeof(players),4,f2);
                 total_lines=getw(f2);
                 time_taken=getw(f2);
                  fclose(f2);
                        }
                else{
                 fread(a,sizeof(char),size*size,f3);
                 turn=getw(f3);
                 fread(&player1,sizeof(players),4,f3);
                 fread(&comp,sizeof(players),4,f3);
                 total_lines=getw(f3);
                 time_taken=getw(f3);
                 fclose(f3);
                }

            }
             print_arr(n,a);
            while(1)
            {
                //to know if he closed a box or not
                w=0;
                move_time=0;
                if(turn==1)

                {
                    start =time(NULL);
                    system("cls");
                    score = 0;
                    display2(player1,comp,total_lines,time_taken,turn);
                    print_arr(size,a);
                    find_index(points,n,size,a,turn,&x);
                    if(strcmp(points,"Undo")==0||strcmp(points,"U")==0||strcmp(points,"undo")==0||strcmp(points,"u")==0)
                    {
                        total_lines+=2;
                        if(g==1) //that means that player has closed the box
                        {
                            check_box(n,size,a,' ',&w);
                            score=w;
                            undo_turn(turn,&player1,&comp,score);
                        }
                        else
                        {
                            turn=0;
                            for(int c=0; c<s; c+=2)
                            {
                                a[array[c]][array[c+1]]=' ';
                            }
                            int un_done=0;
                            check_box(n,size,a,' ',&un_done);
                            undo_turn(turn,&player1,&comp,un_done);
                            comp.moves=comp.moves-s/2+1;
                            turn=1;
                            undo_turn(turn,&player1,&comp,g);

                            total_lines+=s/2;

                        }

                        w=1;


                    }
                    else if (strcmp(points,"Redo")==0||strcmp(points,"R")==0||strcmp(points,"redo")==0||strcmp(points,"r")==0)
                    {
                        check_box(n,size,a,'A',&w);
                        score=w;
                        general_turn(turn,&player1,&comp,score);
                    }
                   else if(strcmp(points,"Exit")==0||strcmp(points,"E")==0||strcmp(points,"exit")==0||strcmp(points,"e")==0) //redo
                    {system("cls");
                        goto new_one;

                    }
                      else if(strcmp(points,"Save")==0||strcmp(points,"S")==0||strcmp(points,"save")==0||strcmp(points,"s")==0) //redo
                    {
                     system("cls");
                     w=-1;
                     change_save(&slot);
                     save(size,a,player1,comp,type,turn,total_lines,time_taken,slot,mode);
                    total_lines+=1;
                    x=0;
                    }
                    else
                    {
                        check_box(n,size,a,'A',&w);
                        print_arr(size,a);
                        score =w;
                        general_turn(turn,&player1,&comp,score);
                    }
                    system("cls");
                    if (w!=0)
                    {
                        turn=1;
                        g=1;
                    }


                    else
                    {
                        turn=0;
                        g=0;
                    }

                    total_lines--;
                    end =time(NULL);
                    move_time=end-start;
                    time_taken+=move_time;
                    s=2;
                    if(total_lines==0)
                    {system("cls");
                    det_winner( player1,comp);
                    Sleep(5000);
        char b[2];
        system("cls");
        setTextColor(stdout, TC_YELLOW);
        printf("\n\n\n\n\n\n\n\t\t\t\t\t\t1.To main menu\n");
        printf("\t\t\t\t\t\t any key.To Exit\n ");
        printf("\t\t\t\t\t\press 1:any key  >>> ");
        scanf("%s",b);
        setTextColor(stdout, TC_LIGHTGRAY);
        system("cls");
        if(strcmp(b,"1")!=0){
            goto newm ;
        }
        else
            goto label ;






                    }
                }
                move_time=0;

                if(turn==0)
                {
                    //moves of the computer will be put in array s;
                    int i,j,temp;
                    start =time(NULL);
                    system("cls");
                    score =0 ;
                    display2(player1,comp,total_lines,time_taken,turn);
                    print_arr(size,a);
                    computer_move(size,a,&i,&j);
                    array[s-2]=i;
                    array[s-1]=j;
                    check_box(n,size,a,'B',&w);
                    print_arr(size,a);
                    score=w ;
                    general_turn(turn,&player1,&comp,score);
                    system("cls");
                    if (w!=0)
                    {
                        turn=0;
                        s+=2;
                    }//computer plays again
                    else
                    {
                        turn=1;
                    }//computer stops playing and it returns to 1 again
                    total_lines--;
                    end =time(NULL);
                    move_time=end-start;
                    time_taken+=move_time;
                    if(total_lines==0)
                      {system("cls");
                    det_winner( player1,comp);
                    Sleep(5000);
        char b[2];
        system("cls");
        setTextColor(stdout, TC_YELLOW);
        printf("\n\n\n\n\n\n\n\t\t\t\t\t\t1.To main menu\n");
        printf("\t\t\t\t\t\tAny key.To Exit\n ");
        printf("\t\t\t\t\t\tpress 1:Any key >>");
        scanf("%s",b);
        setTextColor(stdout, TC_LIGHTGRAY);
        system("cls");
        if(strcmp(b,"1")!=0){
            goto newm ;
        }
        else
            goto label ;
                    }

                }


            }

        }







    }}
  else if (game=='2'){
        while(1){
    printf("Pick which Slot:\ta:slot1    \n    \t\t\tb:slot2       \n   \t\t\tc:slot3  \n");
    printf("1.To go back main menu\n");
    scanf("   %c",&slot);fflush(stdin);
    if(slot=='1'){
        system("cls");
        goto label;}
    if(slot!='a'&&slot!='b'&&slot!='c'){
        printf("\t\t\tError enter valid Input");
        Sleep(2000);
        system("cls");}
     else {
            c_move=check_file(slot);
            if(c_move==0){
                printf("\t\t\tError.File is empty!\a\n");
                Sleep(1000);
                system("cls");}


            else
                break;

     }
}
goto load;


  }
else if (game =='3'){
top=fopen("rank.txt","r");
fread(rankarray,sizeof(rankok),10,top);
printf("Names\tScore\n");
for(int i=9;i>=0;i--){
printf("%s\t%d\n",rankarray[i].name,rankarray[i].score);
}
fclose(top);
       char b[2];
        setTextColor(stdout, TC_YELLOW);
        printf("\t\t\t\t\t1.To main menu\n");
        printf("\t\t\t\t\tAny key.To Exit\n ");
        printf("\t\t\t\t\tpress 1:Any key  >> ");
        scanf("%s",b);
        setTextColor(stdout, TC_LIGHTGRAY);
        system("cls");
        if(strcmp(b,"1")!=0){
            goto newm ;
        }
        else
            goto label ;
  }
  else if (game=='4'){
        newm :
            setTextColor(stdout, TC_YELLOW);
        gotoxy(25,25);
    printf("Thanks for playing Dots And Boxes");
    print_word();
    setTextColor(stdout, TC_LIGHTGRAY);
  }

getch();
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void print_arr(int size,char a[size][size])
{
    int position_x=60,position_y=10,i,j;
    for( i=0; i<size; i++)
    {
        gotoxy(position_x,position_y);
        for( j=0; j<size; j++)
        {
            if(a[i][j]=='z')
            {
                setTextColor(stdout, TC_LIGHTRED);
                printf("%c%c%c%c%c%c%c%c",196,196,196,196,196,196,196,196);
                setTextColor(stdout, TC_LIGHTGRAY);
            }
            else if(a[i][j]=='x')
            {
                setTextColor(stdout, TC_LIGHTRED);
                gotoxy(position_x+(j/2)*8+(j+1)/2,position_y-1);
                printf("%c",179);
                gotoxy(position_x+(j/2)*8+(j+1)/2,position_y);
                printf("%c",179);
                gotoxy(position_x+(j/2)*8+(j+1)/2,position_y+1);
                printf("%c",179);
                setTextColor(stdout, TC_LIGHTGRAY);
            }
            else if(a[i][j]=='c')
            {
                setTextColor(stdout, TC_LIGHTBLUE);
                printf("%c%c%c%c%c%c%c%c",196,196,196,196,196,196,196,196);
                setTextColor(stdout, TC_LIGHTGRAY);
            }
            else if (a[i][j]=='v')
            {
                setTextColor(stdout, TC_LIGHTBLUE);
                gotoxy(position_x+(j/2)*8+(j+1)/2,position_y-1);
                printf("%c",179);
                gotoxy(position_x+(j/2)*8+(j+1)/2,position_y);
                printf("%c",179);
                gotoxy(position_x+(j/2)*8+(j+1)/2,position_y+1);
                printf("%c",179);
                setTextColor(stdout, TC_LIGHTGRAY);
            }
            else if(a[i][j]=='A')
            {
                setTextColor(stdout, TC_RED);
                gotoxy(position_x+((j-1)/2)*8+j/2+1,position_y);
                printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
                gotoxy(position_x+((j-1)/2)*8+j/2+1,position_y+1);
                printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
                gotoxy(position_x+((j-1)/2)*8+j/2+1,position_y-1);
                printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
                setTextColor(stdout, TC_LIGHTGRAY);

            }
            else if(a[i][j]=='B')
            {
                setTextColor(stdout, TC_BLUE);
                gotoxy(position_x+((j-1)/2)*8+j/2+1,position_y);
                printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
                gotoxy(position_x+((j-1)/2)*8+j/2+1,position_y+1);
                printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
                gotoxy(position_x+((j-1)/2)*8+j/2+1,position_y-1);
                printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
                setTextColor(stdout, TC_LIGHTGRAY);
            }
            else if(i%2==0 && j%2!=0 )
            {
                printf("%c",a[i][j]);
            }
            else if (a[i][j]==' ' &&  j!=0)
            {
                printf("        ");
            }
            else
                printf("%c",a[i][j]);

        }
        if(i!=0)
            position_y+=2;
        else
            position_y++ ;
    }
}
void Read_points(char points[5],int n)
{
    gotoxy(0,30);
    printf(" Enter the input: ");
    scanf("%s",points);
    while( strlen(points)>4)
    {
        gotoxy(0,31);
        printf("Error,Invalid input!");
        gotoxy(0,30);
        printf(" Enter the input: ");
        scanf("%s",points);
    }
}
void Read_first(char points[5],int n,int *x)
{
    static int i;

    if((*x)!=0)
    {
        gotoxy(5,33);
        printf("e:Exit"); //save is after exit
        gotoxy(0,0);
        if(i==0)
        {
            gotoxy(0,15);
            printf("Enter Point Coordinates or (u) to undo last play");
        }
        else
        {
            gotoxy(0,15);
            printf("Enter Point coordinates or pass (r) to redo");

        }
        while(1)
        {
            Read_points(points,n);
            if (strcmp(points,"Exit")==0||strcmp(points,"E")==0||strcmp(points,"e")==0||strcmp(points,"exit")==0)
            {
                break;
                //Exit
            }
            else if (strcmp(points,"Save")==0||strcmp(points,"S")==0||strcmp(points,"s")==0||strcmp(points,"save")==0)
            {
                break;
                //Save
            }

            else if (strcmp(points,"Undo")==0||strcmp(points,"U")==0||strcmp(points,"undo")==0||strcmp(points,"u")==0)
            {

                if(i==1)
                {
                    gotoxy(0,31);
                    printf("Error,Invalid input!");
                }
                else
                {
                    i=1;
                    (*x)--;
                    break;
                    //undo
                }
            }
            else if(strcmp(points,"Redo")==0||strcmp(points,"R")==0||strcmp(points,"redo")==0||strcmp(points,"r")==0)
            {
                if(i==0)
                {
                    gotoxy(0,31);
                    printf("Error,Invalid input!");
                }
                else
                {
                    i=0;
                    (*x)++;
                    break;
                }
            }//redo
            else
            {
                i=0;

                if ((points[0]<'1')||(points[0]>n+'1')||(points[1]<'1')||(points[1]>n+'1')||(points[2]<'1')||(points[2]>n+'1')||(points[3]<'1')||(points[3]>n+'1'))
                {
                    gotoxy(0,31);
                    printf("Error,Invalid input!");


                }
                else
                {
                    (*x)++;
                    break;
                }
            }

        }
    }

    else
    {
        (*x)++;
        while(1)
        {
            Read_points(points,n);
            if ((points[0]<'1')||(points[0]>n+'1')||(points[1]<'1')||(points[1]>n+'1')||(points[2]<'1')||(points[2]>n+'1')||(points[3]<'1')||(points[3]>n+'1'))
                printf("Error,Invalid input!");
            else
            {

                i=0;
                break;

            }


        }

    }
}
void analyze_points(char points[5],int n,int *x)  //check relation bet.2 points
{

    while(1)
    {
        Read_first(points,n,&(*x));


        if (strcmp(points,"Exit")==0||strcmp(points,"E")==0||strcmp(points,"e")==0||strcmp(points,"exit")==0)
        {
            break;
            //Exit
        }
        else if (strcmp(points,"Save")==0||strcmp(points,"S")==0||strcmp(points,"s")==0||strcmp(points,"save")==0)
        {
            break;
            //Save
        }
        else if (strcmp(points,"Undo")==0||strcmp(points,"U")==0||strcmp(points,"undo")==0||strcmp(points,"u")==0)
        {

            break;
            //undo
        }
        else if(strcmp(points,"Redo")==0||strcmp(points,"R")==0||strcmp(points,"redo")==0||strcmp(points,"r")==0)
        {


            break;
        }//redo
        else
        {
            if ((points[0]==points[2])&&( points[1]-points[3]==1 || points[3]-points[1]==1))
            {
                break;

            }
            else if ((points[1]== points[3])&&( points[0]-points[2]==1 || points[2]-points[0]==1))
            {
                break ;
            }
            else
            {
                gotoxy(0,31);
                printf("Error,Invalid input!");
            }
        }

    }
}
void find_index(char points[5],int n,int size,char a[size][size], int turn,int *x)
{
    static  int index1,index2 ;
    int v=1;
    while(1)
    {
        analyze_points(points,n,&(*x));
        if (strcmp(points,"Exit")==0||strcmp(points,"E")==0||strcmp(points,"e")==0||strcmp(points,"exit")==0)
        {
            v=0;
            break;



            //Exit
        }
        else if (strcmp(points,"Save")==0||strcmp(points,"S")==0||strcmp(points,"s")==0||strcmp(points,"save")==0)
        {
            break;
            //Save
        }
        else if (strcmp(points,"Undo")==0||strcmp(points,"U")==0||strcmp(points,"undo")==0||strcmp(points,"u")==0)
        {

            //undo
            a[index1][index2]=' ';
            v=0;
            break;



        }
        else if(strcmp(points,"Redo")==0||strcmp(points,"R")==0||strcmp(points,"redo")==0||strcmp(points,"r")==0)
        {
            v=0;
            if(index1%2==1)
            {
                if(turn==1)
                    a[index1][index2]='z' ;
                else
                    a[index1][index2]='c';
            }
            else
            {
                if(turn==1)
                    a[index1][index2]='x';
                else
                    a[index1][index2]='v';

            }
            break;

        }//redo
        else
        {

            index1 = (points[0]+points[2]-1)-2*'0';
            index2=(points[3]+points[1]-1)-2*'0';

            if(a[index1][index2]!=' ')
            {

                gotoxy(0,31);
                printf("Error,Invalid input!");

            }
            else
                break;
        }
    } // to check vacancy.
    if(v==1)
    {
        index1 = (points[0]+points[2]-1)-2*'0';
        index2=(points[3]+points[1]-1)-2*'0';
        if(turn==1)
        {
            if(points[0]==points[2]) // set line if it is horizontal.
                a[index1][index2]='z';
            else // set line if it is vertical.
                a[index1][index2]='x';
        }
        else
        {
            if(points[0]==points[2]) // set line if it is horizontal.
                a[index1][index2]='c';
            else // set line if it is vertical.
                a[index1][index2]='v';

        }
    }
}


void   check_box(int n,int size,char a[size][size],char letter,int *w)
{
    int c1,c2,i,j; // variables to count loops .
    for(c1=0,i=2; c1<n; c1++,i+=2)
    {
        for(c2=0,j=2; c2<n; c2++,j+=2)
        {
            if(a[i+1][j]!=' ' && a[i-1][j]!=' ' && a[i][j+1]!=' ' && a[i][j-1]!=' ' && a[i][j]==' ')
            {

                a[i][j]=letter ;
                *w=*w+1;
            }
            if((a[i+1][j]==' ' || a[i-1][j]==' ' || a[i][j+1]==' ' || a[i][j-1]==' ') && a[i][j]!=' ')
            {
                a[i][j]=' ';
                *w=*w-1;
            }

        }

    }
}
void general_turn (int turn, players *player1, players *player2,int w )
{
    if(turn==1)
    {
        (*player1).moves++;
        if(w!=0)
            (*player1).score+=w;
    }
    else
    {
        (*player2).moves++;
        if(w!=0)
            (*player2).score+=w;
    }
}
void who_turn(players x, players y,int turn)
{
    if(turn==1)
    {
        system("cls");
        gotoxy(60,12);
        setTextColor(stdout, TC_LIGHTRED);
        printf("This %s`s Turn\n",x.name );
        setTextColor(stdout, TC_LIGHTGRAY);
        Sleep(1000);
        system("cls");

    }
    else
    {

        system("cls");
        gotoxy(60,12);
        setTextColor(stdout, TC_LIGHTBLUE);
        printf("This %s`s Turn\n",y.name );
        setTextColor(stdout, TC_LIGHTGRAY);
        Sleep(1000);
        system("cls");
    }

}



void display (players player1, players player2, int y, int time, int turn)
{
    gotoxy(0,0);
    setTextColor(stdout, TC_LIGHTCYAN);
    printf("Players Names :");
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(30,0);
    setTextColor(stdout, TC_LIGHTRED);
    printf("%s",player1.name);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(60,0);
    setTextColor(stdout, TC_LIGHTBLUE);
    printf("%s",player2.name);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(0,2);
    setTextColor(stdout, TC_LIGHTCYAN);
    printf("Moves :");
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(30,2);
    setTextColor(stdout, TC_LIGHTRED);
    printf("%d",player1.moves);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(60,2);
    setTextColor(stdout, TC_LIGHTBLUE);
    printf("%d",player2.moves);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(0,4);
    setTextColor(stdout, TC_LIGHTCYAN);
    printf("Score :");
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(30,4);
    setTextColor(stdout, TC_LIGHTRED);
    printf("%d",player1.score);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(60,4);
    setTextColor(stdout, TC_LIGHTBLUE);
    printf("%d",player2.score);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(90,0);
    setTextColor(stdout, TC_LIGHTGREEN);
    printf("Time : %d : %d",time/60,time%60);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(0,10);
    setTextColor(stdout, TC_LIGHTMAGENTA);
    printf("Total lines left :     %d",y);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(0,6);
    setTextColor(stdout, TC_LIGHTCYAN);
    printf("Player Turn :");
    setTextColor(stdout, TC_LIGHTGRAY);
    if(turn==1)
    {
        gotoxy(30,6);
        setTextColor(stdout, TC_LIGHTRED);
        printf("^");
        setTextColor(stdout, TC_LIGHTGRAY);
    }
    else
    {
        gotoxy(60,6);
        setTextColor(stdout, TC_LIGHTBLUE);
        printf("^");
        setTextColor(stdout, TC_LIGHTGRAY);
    }


}
void display2 (players player1, players computer, int y, int time, int turn)
{
    gotoxy(0,0);
    setTextColor(stdout, TC_LIGHTCYAN);
    printf("Players Names :");
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(30,0);
    setTextColor(stdout, TC_LIGHTRED);
    printf("%s",player1.name);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(60,0);
    setTextColor(stdout, TC_LIGHTBLUE);
    printf("%s",computer.name);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(0,2);
    setTextColor(stdout, TC_LIGHTCYAN);
    printf("Moves :");
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(30,2);
    setTextColor(stdout, TC_LIGHTRED);
    printf("%d",player1.moves);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(60,2);
    setTextColor(stdout, TC_LIGHTBLUE);
    printf("%d",computer.moves);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(0,4);
    setTextColor(stdout, TC_LIGHTCYAN);
    printf("Score :");
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(30,4);
    setTextColor(stdout, TC_LIGHTRED);
    printf("%d",player1.score);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(60,4);
    setTextColor(stdout, TC_LIGHTBLUE);
    printf("%d",computer.score);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(90,0);
    setTextColor(stdout, TC_LIGHTGREEN);
    printf("Time : %d : %d",time/60,time%60);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(0,10);
    setTextColor(stdout, TC_LIGHTMAGENTA);
    printf("Total lines left :     %d",y);
    setTextColor(stdout, TC_LIGHTGRAY);
    gotoxy(0,6);
    setTextColor(stdout, TC_LIGHTCYAN);
    printf("Player Turn :");
    setTextColor(stdout, TC_LIGHTGRAY);
    if(turn==1)
    {
        gotoxy(30,6);
        setTextColor(stdout, TC_LIGHTRED);
        printf("^");
        setTextColor(stdout, TC_LIGHTGRAY);
    }
    else
    {
        gotoxy(60,6);
        setTextColor(stdout, TC_LIGHTBLUE);
        printf("^");
        setTextColor(stdout, TC_LIGHTGRAY);
    }
}
void undo_turn (int turn, players (*player1), players (*player2),int w )
{
    if(turn==1)
    {

        (*player1).moves--;
        if(w!=0)
            (*player1).score+=w;
    }
    else
    {
        (*player2).moves--;
        if(w!=0)
            (*player2).score+=w;
    }
}
// function to set a line for a computer move .
void computer_move(int  size, char a[size] [size],int *ii,int *jj)
{
    int i,j,flag=0;
    // set horizontal line :
    for(i=1; i<size; i+=2)
    {
        for(j=2; j<size; j+=2)
        {
            if(a[i][j] == ' ')
            {
                *ii=i;
                *jj=j;
                a[i][j] = 'c';
                flag=1;
                break;
            }
        }
        if(flag==1)
            break;
    }
    if(flag==0)
    {
        //set vertical line.
        for(i=2; i<size; i+=2)
        {
            for(j=1; j<size; j+=2)
            {
                if(a[i][j] == ' ')
                {
                    *ii=i;
                    *jj=j;
                    a[i][j] = 'v';
                    flag=1;
                    break;
                }
            }
            if(flag==1)
                break;
        }
    }
}
void delete_array(int s,int array[s],int size,char a[size][size])
{
    for(int i=0; i<s; i+=2)
    {
        a[i][i+1]=' ';
    }


}

void det_winner(players player1,players player2)
{

    if(player1.score>player2.score)

    {
        gotoxy(50,1);
        printf("%s Wins",player1.name);
    }
    else if(player1.score<player2.score)

    {
        gotoxy(50,1);
        printf("%s Wins",player2.name);


    }
    else
    {
        gotoxy(50,1);
        printf("DRAW");
    }
    gotoxy(0,4);
    Winner(player1,player2);
}


void save(int size,char a[size][size],players x,players y,char type[2],int turn,int total_lines, int clock,char slot,char mode)
{
    if(slot=='a')
    {
    f1=fopen("file1.txt","w");
    putc(mode,f1);
    fputs(type,f1);
    fwrite(a,sizeof(char),size*size,f1);
    putw(turn,f1);
    fwrite(&x,sizeof(players),4,f1);
    fwrite(&y,sizeof(players),4,f1);
    putw(total_lines,f1);
    putw(clock,f1);
    fclose(f1);
    }
    else if(slot=='b')
    {
     f2=fopen("file2.txt","w");
    putc(mode,f2);
    fputs(type,f2);
    fwrite(a,sizeof(char),size*size,f2);
    putw(turn,f2);
    fwrite(&x,sizeof(players),4,f2);
    fwrite(&y,sizeof(players),4,f2);
    putw(total_lines,f2);
    putw(clock,f2);
    fclose(f2);
    }
    else if(slot=='c')
    {
    f3=fopen("file3.txt","w");
    putc(mode,f3);
    fputs(type,f3);
    fwrite(a,sizeof(char),size*size,f3);
    putw(turn,f3);
    fwrite(&x,sizeof(players),4,f3);
    fwrite(&y,sizeof(players),4,f3);
    putw(total_lines,f3);
    putw(clock,f3);
    fclose(f3);
    }
}
void change_save(char *slot)
{
    gotoxy(30,0);
    printf("Enter which slot you want to save");
    gotoxy(25,1);
    printf("a:slot1\tb:slot2\tc:slot3");
    scanf(" %c",&(*slot));
}
int check_file(char slot){
    int x,len;
 if(slot=='a'){
     f1=fopen("file1.txt","r");
     if(f1==NULL)
        x=0;
     else x=1;
fclose(f1);

}
 else if(slot=='b'){
     f2=fopen("file2.txt","r");
     if(f2==NULL)
        x=0;
     else x=1;
     fclose(f2);

}
 else {
     f3=fopen("file3.txt","r");
     if(f3==NULL)
        x=0;
     else x=1;
     fclose(f3);
}
return x;
}



void Winner(players x,players y){
    int l;
    strlwr(x.name);
    strlwr(y.name);
    top=fopen("rank.txt","r");
    fread(rankarray,sizeof(rankok),10,top);
    fclose(top);
    l=0;
    if(x.score>y.score)
   {for(int i=0;i<10;i++){
       if(l==0){
   if(strcmp(x.name,rankarray[i].name)==0)
   {
       if(x.score>rankarray[i].score)
        rankarray[i].score=x.score;
        break;
   }

       }
   else {
    if(rankarray[i].score<x.score){
        strcpy(rankarray[i].name,x.name);
        rankarray[i].score=x.score;
        break;
    }}
    if(i==9){
        l=1;
        i=0;
        }


   }

    }
    else if(x.score<y.score){
    if(strcmp(y.name,"computer")!=0){
         for(int i=0;i<10;i++){
                if(l==0){
   if(strcmp(y.name,rankarray[i].name)==0)
   {
       if(y.score>rankarray[i].score)
        rankarray[i].score=y.score;
       break;
   }}
   else{
     if(rankarray[i].score<y.score){
         strcpy(rankarray[i].name,y.name);
        rankarray[i].score=y.score;
          break;
   }}
   if(i==9){
        l=1;
        i=0;}

   }

}}
    else
    {



    }


for(int j=9;j>0;j--){
    for(int i=0;i<10-j;i++){
        if(rankarray[i].score>rankarray[i+1].score){
            rankok temp=rankarray[i];
            rankarray[i]=rankarray[i+1];
            rankarray[i+1]=temp;
        }
    }
}


for(int i=9;i>=0;i--){
printf("%s\t%d\n",rankarray[i].name,rankarray[i].score);

}
top=fopen("rank.txt","w");
fwrite(rankarray,sizeof(rankok),10,top);
  fclose(top);
}
void print_word()
{
    setTextColor(stdout, TC_BROWN);
    gotoxy(30,2);
 printf(" ______   _______ _________ _______      __      ______   _______           _______  _______ ");
   gotoxy(30,3);
   printf("(  __  \\ (  ___  )\__   __/(  ____ \\    /__\\    (  ___ \\ (  ___  )|\\     /|(  ____ \\(  ____ \\ ");
   gotoxy(30,4);
   printf("| (  \\  )| (   ) |   ) (   | (    \\/   ( \\/ )   | (   ) )| (   ) |( \\   / )| (    \\/| (    \\/");
   gotoxy(30,5);
   printf("| |   ) || |   | |   | |   | (_____     \\  /    | (__/ / | |   | | \\ (_) / | (__    | (_____");
   gotoxy(30,6);
   printf("| |   | || |   | |   | |   (_____  )    /  \\/\\  |  __ (  | |   | |  ) _ (  |  __)   (_____  )");
   gotoxy(30,7);
   printf("| |   ) || |   | |   | |         ) |   / /\\  /  | (  \\ \\ | |   | | / ( ) \\ | (            ) |");
   gotoxy(30,8);
   printf("| (__/  )| (___) |   | |   /\\____) |  (  \\/  \\  | )___) )| (___) |( /   \\ )| (____/\\/\\____) |");
   gotoxy(30,9);
   printf("(______/ (_______)   )_(   \\_______)   \\___/\\/  |/ \\___/ (_______)|/     \\|(_______/\\_______)");
        setTextColor(stdout, TC_LIGHTGRAY);

}
