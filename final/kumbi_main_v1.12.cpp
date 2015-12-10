#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int table_height, table_width; //+2 a keret miatt, az jatek ter bal felso sarka: (1;1)
int tick=0;
int radius;
int activating_time=3;
int doc_x=4, doc_y=4;
int del_x=1, del_y=1;
int esc_x, esc_y;

int table[100][100];
int health_table[100][100];
int distance_table[100][100];
int path_table[100][100];
int temp_table[100][100];
int danger_table[100][100];
int safe_x, safe_y;


void add_table();
void draw_table(char c);
void show_tick();
void move_doc(char c);
void put_bomb(char c, int turns_to_activate, int dmg);
char shortest_path(char c);
int can_escape(char c);
bool van_bomba();
void compute();
bool inDanger();
void create_path(int cel_x, int cel_y);
char follow_path();
char escape_path();
void find_safe_place();


int main()
{
    add_table();
    show_tick();
    draw_table('r');
    //draw_table('h');
    bool quit=false;
    do
    {
        char i;
        cin>>i;
        create_path(del_x,del_y);
        if(inDanger())
        {
            find_safe_place();
            create_path(safe_x, safe_y);
            move_doc(escape_path());
        }
        else move_doc(follow_path());
        show_tick();
        draw_table('r');
        draw_table('p');
        //draw_table('d');

        compute();
    }while(quit!=true);

    return 0;
}

void find_safe_place()
{

    for(int i=0;i<table_height;i++)
    {
        for(int j=0;j<table_width;j++)
        {
            distance_table[j][i]=-3;
            if(table[j][i]==-1) distance_table[j][i]=-1;
            if(table[j][i]==1) distance_table[j][i]=-5;
        }
    }

    int depth=0;
    bool quit=false;
    distance_table[doc_x][doc_y]=0;

    do
    {
        for(int i=1;i<table_height-1;i++)
        {
            for(int j=1;j<table_width-1;j++)
            {
                if(distance_table[j][i]==depth && quit==false)
                {
                    if(distance_table[j][i-1]>depth || distance_table[j][i-1]==-3 || distance_table[j][i-1]==-2 || distance_table[j][i-1]==-5)
                    {
                        if(danger_table[j][i-1]==0) {safe_x=j; safe_y=i-1; quit=true;}
                        else if(distance_table[j][i-1]==-5)
                        {
                            distance_table[j][i-1]=depth+1+health_table[j][i-1]*3;
                        }
                        else distance_table[j][i-1]=depth+1;
                    }

                    if(distance_table[j][i+1]>depth || distance_table[j][i+1]==-3 || distance_table[j][i+1]==-2 || distance_table[j][i+1]==-5)
                    {
                        if(danger_table[j][i+1]==0) {safe_x=j; safe_y=i+1; quit=true;}
                        else if(distance_table[j][i+1]==-5)
                        {
                            distance_table[j][i+1]=depth+1+health_table[j][i+1]*3;
                        }
                        else distance_table[j][i+1]=depth+1;
                    }

                    if(distance_table[j-1][i]>depth || distance_table[j-1][i]==-3 || distance_table[j-1][i]==-2 || distance_table[j-1][i]==-5)
                    {
                        if(danger_table[j-1][i]==0) {safe_x=j-1; safe_y=i; quit=true;}
                        else if(distance_table[j-1][i]==-5)
                        {
                            distance_table[j-1][i]=depth+1+health_table[j-1][i]*3;
                        }
                        else distance_table[j-1][i]=depth+1;
                    }

                    if(distance_table[j+1][i]>depth || distance_table[j+1][i]==-3 || distance_table[j+1][i]==-2 || distance_table[j+1][i]==-5)
                    {
                        if(danger_table[j+1][i]==0) {safe_x=j+1; safe_y=i; quit=true;}
                        else if(distance_table[j+1][i]==-5)
                        {
                            distance_table[j+1][i]=depth+1+health_table[j+1][i]*3;
                        }
                        else distance_table[j+1][i]=depth+1;
                    }
                }
            }
        }
                //draw_table('d');
        depth++;
    }while(quit!=true);
}

void create_path(int cel_x, int cel_y)
{
    if(cel_x!=doc_x || cel_y!=doc_y)
    {
        for(int i=0;i<table_height;i++)
        {
            for(int j=0;j<table_width;j++)
            {
                distance_table[j][i]=-3;
                if(table[j][i]==-1) distance_table[j][i]=-1;
                if(table[j][i]==1) distance_table[j][i]=-5;
            }
        }

        int depth=0;
        bool quit=false;
        distance_table[doc_x][doc_y]=0;
        distance_table[cel_x][cel_y]=-2;

        do
        {
            for(int i=1;i<table_height-1;i++)
            {
                for(int j=1;j<table_width-1;j++)
                {
                    if(distance_table[j][i]==depth && quit==false)
                    {
                        if(distance_table[j][i-1]>depth || distance_table[j][i-1]==-3 || distance_table[j][i-1]==-2 || table[j][i-1]==1)
                        {
                            if(distance_table[j][i-1]==-2) quit=true;
                            else if(table[j][i-1]==1)
                            {
                                distance_table[j][i-1]=depth+1+health_table[j][i-1]*8;
                            }
                            else distance_table[j][i-1]=depth+1;
                        }

                        if(distance_table[j][i+1]>depth || distance_table[j][i+1]==-3 || distance_table[j][i+1]==-2 || table[j][i+1]==1)
                        {
                            if(distance_table[j][i+1]==-2) quit=true;
                            else if(table[j][i+1]==1)
                            {
                                distance_table[j][i+1]=depth+1+health_table[j][i+1]*8;
                            }
                            else distance_table[j][i+1]=depth+1;
                        }

                        if(distance_table[j-1][i]>depth || distance_table[j-1][i]==-3 || distance_table[j-1][i]==-2 || table[j-1][i]==1)
                        {
                            if(distance_table[j-1][i]==-2) quit=true;
                            else if(table[j-1][i]==1)
                            {
                                distance_table[j-1][i]=depth+1+health_table[j-1][i]*8;
                            }
                            else distance_table[j-1][i]=depth+1;
                        }

                        if(distance_table[j+1][i]>depth || distance_table[j+1][i]==-3 || distance_table[j+1][i]==-2 || table[j+1][i]==1)
                        {
                            if(distance_table[j+1][i]==-2) quit=true;
                            else if(table[j+1][i]==1)
                            {
                                distance_table[j+1][i]=depth+1+health_table[j+1][i]*8;
                            }
                            else distance_table[j+1][i]=depth+1;
                        }
                    }
                }
            }
                //draw_table('d');
            depth++;
        }while(quit!=true);

            //draw_table('d');

        int minimum=5000;
        int aktiv_x=cel_x;
        int aktiv_y=cel_y;
        int temp_x;
        int temp_y;
        quit=false;

            //cout<<"??"<<aktiv_x<<" "<<aktiv_y<<"??";

        string irany;
        string ut="";

        for(int i=0;i<table_height;i++)
        {
            for(int j=0;j<table_width;j++)
            {
                path_table[j][i]=0;
            }
        }

        do
        {
            if(distance_table[aktiv_x][aktiv_y-1]==0 || distance_table[aktiv_x][aktiv_y+1]==0 ||
                distance_table[aktiv_x-1][aktiv_y]==0 || distance_table[aktiv_x+1][aktiv_y]==0)
            {
                if(distance_table[aktiv_x][aktiv_y-1]==0) irany="d";
                else if(distance_table[aktiv_x][aktiv_y+1]==0) irany="u";
                else if(distance_table[aktiv_x-1][aktiv_y]==0) irany="r";
                else if(distance_table[aktiv_x+1][aktiv_y]==0) irany="l";
                quit=true;
            }
            else
            {
                if(distance_table[aktiv_x][aktiv_y-1]<minimum && distance_table[aktiv_x][aktiv_y-1]>0)
                {
                    temp_x=aktiv_x;
                    temp_y=aktiv_y-1;
                    minimum=distance_table[aktiv_x][aktiv_y-1];
                    irany="d";
                }
                if(distance_table[aktiv_x][aktiv_y+1]<minimum && distance_table[aktiv_x][aktiv_y+1]>0)
                {
                    temp_x=aktiv_x;
                    temp_y=aktiv_y+1;
                    minimum=distance_table[aktiv_x][aktiv_y+1];
                    irany="u";
                }
                if(distance_table[aktiv_x-1][aktiv_y]<minimum && distance_table[aktiv_x-1][aktiv_y]>0)
                {
                    temp_x=aktiv_x-1;
                    temp_y=aktiv_y;
                    minimum=distance_table[aktiv_x-1][aktiv_y];
                    irany="r";
                }
                if(distance_table[aktiv_x+1][aktiv_y]<minimum && distance_table[aktiv_x+1][aktiv_y]>0)
                {
                    temp_x=aktiv_x+1;
                    temp_y=aktiv_y;
                    minimum=distance_table[aktiv_x+1][aktiv_y];
                    irany="l";
                }
                aktiv_x=temp_x;
                aktiv_y=temp_y;

                path_table[aktiv_x][aktiv_y]=1;
            }
            ut=ut+irany;
        }while(quit!=true);

        string temp_ut=ut;
        ut="";
        for(int i=temp_ut.length()-1;i>-1;i--) ut=ut+temp_ut[i];

        for(int i=0;i<table_height;i++)
        {
            for(int j=0;j<table_width;j++)
            {
                if(path_table[j][i]==1 && table[j][i]==1)
                {
                    if(path_table[j][i-1]==1 && table[j][i-1]==0) path_table[j][i-1]=2;
                    if(path_table[j][i+1]==1 && table[j][i+1]==0) path_table[j][i+1]=2;
                    if(path_table[j-1][i]==1 && table[j-1][i]==0) path_table[j-1][i]=2;
                    if(path_table[j+1][i]==1 && table[j+1][i]==0) path_table[j+1][i]=2;
                }
            }
        }
        path_table[cel_x][cel_y]=1;
    }
}

char follow_path()
{
    if(path_table[doc_x][doc_y-1]==1 && danger_table[doc_x][doc_y-1]==0) return 'u';
    else if(path_table[doc_x][doc_y-1]==2) put_bomb('u',activating_time,2);
    if(path_table[doc_x][doc_y+1]==1 && danger_table[doc_x][doc_y+1]==0) return 'd';
    else if(path_table[doc_x][doc_y+1]==2) put_bomb('d',activating_time,2);
    if(path_table[doc_x-1][doc_y]==1 && danger_table[doc_x-1][doc_y]==0) return 'l';
    else if(path_table[doc_x-1][doc_y]==2) put_bomb('l',activating_time,2);
    if(path_table[doc_x+1][doc_y]==1 && danger_table[doc_x+1][doc_y]==0) return 'r';
    else if(path_table[doc_x+1][doc_y]==2) put_bomb('r',activating_time,2);
    return 's';
}

char escape_path()
{
    if(path_table[doc_x][doc_y-1]==1) return 'u';
    if(path_table[doc_x][doc_y+1]==1) return 'd';
    if(path_table[doc_x-1][doc_y]==1) return 'l';
    if(path_table[doc_x+1][doc_y]==1) return 'r';
    return 's';
}

bool inDanger()
{
    for(int i=0;i<table_height;i++)
    {
        for(int j=0;j<table_width;j++)
        {
            danger_table[j][i]=table[j][i];
            if(table[j][i]==-2) danger_table[j][i]=0;
        }
    }

    for(int i=0;i<table_height;i++)
    {
        for(int j=0;j<table_width;j++)
        {
            if(danger_table[j][i]==2)
            {
                int iranyok[4];
                for(int i=0;i<4;i++) iranyok[i]=0;
                int sugar=0;
                int kesz=0;
                do
                {
                    kesz=0;
                    sugar++;
                    if((danger_table[j][i-sugar]==0 || danger_table[j][i-sugar]==-3) && iranyok[0]==0) danger_table[j][i-sugar]=5;
                    else {iranyok[0]=1;}
                    if((danger_table[j][i+sugar]==0 || danger_table[j][i+sugar]==-3) && iranyok[1]==0) danger_table[j][i+sugar]=5;
                    else {iranyok[1]=1;}
                    if((danger_table[j-sugar][i]==0 || danger_table[j-sugar][i]==-3) && iranyok[2]==0) danger_table[j-sugar][i]=5;
                    else {iranyok[2]=1;}
                    if((danger_table[j+sugar][i]==0 || danger_table[j+sugar][i]==-3) && iranyok[3]==0) danger_table[j+sugar][i]=5;
                    else {iranyok[3]=1;}

                    for(int i=0;i<4;i++) if(iranyok[i]==1) kesz++;
                }while(kesz!=4 && sugar!=radius);

            }
        }
    }
    if(danger_table[doc_x][doc_y]==5) return true;
    else return false;
}

void compute()
{
    if(van_bomba())
    {
        for(int i=0;i<table_height;i++)
        {
            for(int j=0;j<table_width;j++)
            {
                if(table[j][i]==2)
                {
                    health_table[j][i]--;
                    if(health_table[j][i]==0)
                    {
                        table[j][i]=0;
                        int iranyok[4];
                        for(int i=0;i<4;i++) iranyok[i]=0;
                        int sugar=0;
                        int kesz=0;
                        do
                        {
                            sugar++;
                            int a;
                            if((table[j][i-sugar]==0 || table[j][i-sugar]==-3) || iranyok[0]==1) a++;
                            else
                            {
                                iranyok[0]=1; kesz++;
                                if(table[j][i-sugar]==1) health_table[j][i-sugar]--;
                            }
                            if((table[j][i+sugar]==0 || table[j][i+sugar]==-3) || iranyok[1]==1) a++;
                            else
                            {
                                iranyok[1]=1; kesz++;
                                if(table[j][i+sugar]==1) health_table[j][i+sugar]--;
                            }
                            if((table[j-sugar][i]==0 || table[j-sugar][i]==-3) || iranyok[2]==1) a++;
                            else
                            {
                                iranyok[2]=1; kesz++;
                                if(table[j-sugar][i]==1) health_table[j-sugar][i]--;
                            }
                            if((table[j+sugar][i]==0 || table[j+sugar][i]==-3) || iranyok[4]==1) a++;
                            else
                            {
                                iranyok[3]=1; kesz++;
                                if(table[j+sugar][i]==1) health_table[j+sugar][i]--;
                            }
                        }while(kesz!=4 && sugar!=radius);
                    }
                }
            }
        }
    }
    for(int i=0;i<table_height;i++)
    {
        for(int j=0;j<table_width;j++)
        {
            if(table[j][i]==1 && health_table[j][i]==0) table[j][i]=0;
        }
    }
}

bool van_bomba()
{
    for(int i=0;i<table_height;i++)
    {
        for(int j=0;j<table_width;j++)
        {
            if(table[j][i]==2)return true;
        }
    }
    return false;
}

void add_table()
{

    ifstream file("input.txt");
    if(file.is_open())
    {
        file>>table_height;
        file>>table_width;
        file>>radius;
        string sor;

        for(int i=0; i<table_height;i++)
        {
            file>>sor;
            for(int j=0;j<table_width;j++)
            {
                switch(sor[j])
                {
                    case 'W': table[j][i]=-1; break;
                    case 'C': table[j][i]=1; break;
                    case '.': table[j][i]=0; break;
                    case 'D': table[j][i]=-3; break;
                    case 'L': table[j][i]=-2; break;
                    case 'A': health_table[j][i]=0; break;
                    case 'B': health_table[j][i]=1; break;
                }
            }
        }

        for(int i=0; i<table_height;i++)
        {
            file>>sor;
            for(int j=0;j<table_width;j++)
            {
                switch(sor[j])
                {
                    case '0': health_table[j][i]=0; break;
                    case '1': health_table[j][i]=1; break;
                    case '2': health_table[j][i]=2; break;
                    case '3': health_table[j][i]=3; break;
                    case '4': health_table[j][i]=4; break;
                    case '5': health_table[j][i]=5; break;
                    case '6': health_table[j][i]=6; break;
                    case '7': health_table[j][i]=7; break;
                    case '8': health_table[j][i]=8; break;
                    case '9': health_table[j][i]=9; break;
                }
            }
        }

        for(int i=1;i<table_height-1;i++)
        {
            for(int j=1;j<table_width-1;j++)
            {
                if(table[j][i]==-3)
                {
                    doc_x=j;
                    doc_y=i;
                }
                else if(table[j][i]==-2)
                {
                    del_x=j;
                    del_y=i;
                }
            }
        }
    }
}

void draw_table(char c)
{
    for(int i=0;i<table_width;i++)
    {
        for(int j=0;j<table_width;j++)
        {
            if(c=='r')
            {
                switch(table[j][i])
                {
                    case -3: cout<<"D"; break;
                    case -2: cout<<"L"; break;
                    case -1: cout<<"W"; break;
                    case 0: cout<<"."; break;
                    case 1: cout<<"C"; break;
                    case 2: cout<<"B"; break;
                }
            }

            else if(c=='d')
            {
                cout<<distance_table[j][i]<<"  ";
            }

            else if(c=='p')
            {
                cout<<path_table[j][i];
            }

            else if(c=='t')
            {
                cout<<temp_table[j][i]<<"  ";
            }

            else if(c=='h')
            {
                cout<<health_table[j][i];
            }

            else if(c=='a')
            {
                cout<<danger_table[j][i];
            }
        }
        cout<<endl;
    }
}

void show_tick()
{
    cout<<endl<<"tick: "<<tick<<endl;
}

void move_doc(char c)
{
    switch(c)
    {
        case 'u':
        {
            table[doc_x][doc_y]=0;
            doc_y--;
            table[doc_x][doc_y]=-3;
        }
        break;

        case 'd':
        {
            table[doc_x][doc_y]=0;
            doc_y++;
            table[doc_x][doc_y]=-3;
        }
        break;

        case 'l':
        {
            table[doc_x][doc_y]=0;
            doc_x--;
            table[doc_x][doc_y]=-3;
        }
        break;


        case 'r':
        {
            table[doc_x][doc_y]=0;
            doc_x++;
            table[doc_x][doc_y]=-3;
        }
        break;

        case 's': break;
    }

    tick++;
}

void put_bomb(char c, int turns_to_activate, int dmg)
{
    switch(c)
    {
          case 'u': if(table[doc_x][doc_y-1]==0)
          {
              table[doc_x][doc_y-1]=2;
              health_table[doc_x][doc_y-1]=activating_time+1;
          }
          break;

          case 'd': if(table[doc_x][doc_y+1]==0)
          {
              table[doc_x][doc_y+1]=2;
              health_table[doc_x][doc_y+1]=activating_time+1;
          }
          break;

          case 'l': if(table[doc_x-1][doc_y]==0)
          {
              table[doc_x-1][doc_y]=2;
              health_table[doc_x-1][doc_y]=activating_time+1;
          }
          break;

           case 'r': if(table[doc_x+1][doc_y]==0)
          {
              table[doc_x+1][doc_y]=2;
              health_table[doc_x+1][doc_y]=activating_time+1;
          }
          break;
    }
    tick++;
}

char shortest_path(char c)
{
    if(c=='l')
    {
        for(int i=0;i<table_height;i++)
        {
            for(int j=0;j<table_width;j++)
            {
                distance_table[j][i]=-3;
                if(table[j][i]==-1) distance_table[j][i]=-1;
                if(table[j][i]==1) distance_table[j][i]=-5;
            }
        }

        int depth=0;
        bool quit=false;
        distance_table[doc_x][doc_y]=0;
        distance_table[del_x][del_y]=-2;

        do
        {
            for(int i=1;i<table_height-1;i++)
            {
                for(int j=1;j<table_width-1;j++)
                {
                    if(distance_table[j][i]==depth && quit==false)
                    {
                        if(distance_table[j][i-1]>depth || distance_table[j][i-1]==-3 || distance_table[j][i-1]==-2 || distance_table[j][i-1]==-5)
                        {
                            if(distance_table[j][i-1]==-2) quit=true;
                            else if(distance_table[j][i-1]==-5)
                            {
                                distance_table[j][i-1]=depth+1+health_table[j][i-1]*3;
                            }
                            else distance_table[j][i-1]=depth+1;
                        }

                        if(distance_table[j][i+1]>depth || distance_table[j][i+1]==-3 || distance_table[j][i+1]==-2 || distance_table[j][i+1]==-5)
                        {
                            if(distance_table[j][i+1]==-2) quit=true;
                            else if(distance_table[j][i+1]==-5)
                            {
                                distance_table[j][i+1]=depth+1+health_table[j][i+1]*3;
                            }
                            else distance_table[j][i+1]=depth+1;
                        }

                        if(distance_table[j-1][i]>depth || distance_table[j-1][i]==-3 || distance_table[j-1][i]==-2 || distance_table[j-1][i]==-5)
                        {
                            if(table[j-1][i]==-2) quit=true;
                            else if(distance_table[j-1][i]==-5)
                            {
                                distance_table[j-1][i]=depth+1+health_table[j-1][i]*3;
                            }
                            else distance_table[j-1][i]=depth+1;
                        }

                        if(distance_table[j+1][i]>depth || distance_table[j+1][i]==-3 || distance_table[j+1][i]==-2 || distance_table[j+1][i]==-5)
                        {
                            if(distance_table[j+1][i]==-2) quit=true;
                            else if(distance_table[j+1][i]==-5)
                            {
                                distance_table[j+1][i]=depth+1+health_table[j+1][i]*3;
                            }
                            else distance_table[j+1][i]=depth+1;
                        }
                    }
                }
            }
            //draw_table('d');
            depth++;
        }while(quit!=true);

        //draw_table('d');

        int minimum=5000;
        int aktiv_x=del_x;
        int aktiv_y=del_y;
        int temp_x;
        int temp_y;
        quit=false;

        //cout<<"??"<<aktiv_x<<" "<<aktiv_y<<"??";

        string irany;
        string ut="";

        for(int i=0;i<table_height;i++)
        {
            for(int j=0;j<table_width;j++)
            {
                path_table[j][i]=0;
            }
        }

        do
        {
            if(distance_table[aktiv_x][aktiv_y-1]==0 || distance_table[aktiv_x][aktiv_y+1]==0 ||
               distance_table[aktiv_x-1][aktiv_y]==0 || distance_table[aktiv_x+1][aktiv_y]==0)
            {
                if(distance_table[aktiv_x][aktiv_y-1]==0) irany="d";
                else if(distance_table[aktiv_x][aktiv_y+1]==0) irany="u";
                else if(distance_table[aktiv_x-1][aktiv_y]==0) irany="r";
                else if(distance_table[aktiv_x+1][aktiv_y]==0) irany="l";

                quit=true;
            }
            else
            {
                if(distance_table[aktiv_x][aktiv_y-1]<minimum && distance_table[aktiv_x][aktiv_y-1]>0)
                {
                    temp_x=aktiv_x;
                    temp_y=aktiv_y-1;
                    minimum=distance_table[aktiv_x][aktiv_y-1];
                    irany="d";
                }
                if(distance_table[aktiv_x][aktiv_y+1]<minimum && distance_table[aktiv_x][aktiv_y+1]>0)
                {
                    temp_x=aktiv_x;
                    temp_y=aktiv_y+1;
                    minimum=distance_table[aktiv_x][aktiv_y+1];
                    irany="u";
                }
                if(distance_table[aktiv_x-1][aktiv_y]<minimum && distance_table[aktiv_x-1][aktiv_y]>0)
                {
                    temp_x=aktiv_x-1;
                    temp_y=aktiv_y;
                    minimum=distance_table[aktiv_x-1][aktiv_y];
                    irany="r";
                }
                if(distance_table[aktiv_x+1][aktiv_y]<minimum && distance_table[aktiv_x+1][aktiv_y]>0)
                {
                    temp_x=aktiv_x+1;
                    temp_y=aktiv_y;
                    minimum=distance_table[aktiv_x+1][aktiv_y];
                    irany="l";
                }
                aktiv_x=temp_x;
                aktiv_y=temp_y;

                path_table[aktiv_x][aktiv_y]=1;
            }
            ut=ut+irany;
        }while(quit!=true);

        string temp_ut=ut;
        ut="";
        for(int i=temp_ut.length()-1;i>-1;i--) ut=ut+temp_ut[i];

        for(int i=0;i<table_height;i++)
        {
            for(int j=0;j<table_width;j++)
            {
                if(path_table[j][i]==1 && table[j][i]==1)
                {
                    if(path_table[j][i-1]==1 && table[j][i-1]==0) path_table[j][i-1]=2;
                    if(path_table[j][i+1]==1 && table[j][i+1]==0) path_table[j][i+1]=2;
                    if(path_table[j-1][i]==1 && table[j-1][i]==0) path_table[j-1][i]=2;
                    if(path_table[j+1][i]==1 && table[j+1][i]==0) path_table[j+1][i]=2;
                }
            }
        }
        return ut[0];
    }

    if(c=='e')
    {
        int minimum=5000;
        int aktiv_x=esc_x;
        int aktiv_y=esc_y;
        int temp_x;
        int temp_y;
        bool quit=false;

        //cout<<"??"<<aktiv_x<<" "<<aktiv_y<<"??";

        string irany;
        string ut="";

        for(int i=0;i<table_height;i++)
        {
            for(int j=0;j<table_width;j++)
            {
                path_table[j][i]=0;
            }
        }

        do
        {
            if(distance_table[aktiv_x][aktiv_y-1]==0 || distance_table[aktiv_x][aktiv_y+1]==0 ||
               distance_table[aktiv_x-1][aktiv_y]==0 || distance_table[aktiv_x+1][aktiv_y]==0)
            {
                if(distance_table[aktiv_x][aktiv_y-1]==0) irany="d";
                else if(distance_table[aktiv_x][aktiv_y+1]==0) irany="u";
                else if(distance_table[aktiv_x-1][aktiv_y]==0) irany="r";
                else if(distance_table[aktiv_x+1][aktiv_y]==0) irany="l";

                quit=true;
            }
            else
            {
                if(distance_table[aktiv_x][aktiv_y-1]<minimum && distance_table[aktiv_x][aktiv_y-1]>0)
                {
                    temp_x=aktiv_x;
                    temp_y=aktiv_y-1;
                    minimum=distance_table[aktiv_x][aktiv_y-1];
                    irany="d";
                }
                if(distance_table[aktiv_x][aktiv_y+1]<minimum && distance_table[aktiv_x][aktiv_y+1]>0)
                {
                    temp_x=aktiv_x;
                    temp_y=aktiv_y+1;
                    minimum=distance_table[aktiv_x][aktiv_y+1];
                    irany="u";
                }
                if(distance_table[aktiv_x-1][aktiv_y]<minimum && distance_table[aktiv_x-1][aktiv_y]>0)
                {
                    temp_x=aktiv_x-1;
                    temp_y=aktiv_y;
                    minimum=distance_table[aktiv_x-1][aktiv_y];
                    irany="r";
                }
                if(distance_table[aktiv_x+1][aktiv_y]<minimum && distance_table[aktiv_x+1][aktiv_y]>0)
                {
                    temp_x=aktiv_x+1;
                    temp_y=aktiv_y;
                    minimum=distance_table[aktiv_x+1][aktiv_y];
                    irany="l";
                }
                aktiv_x=temp_x;
                aktiv_y=temp_y;

                path_table[aktiv_x][aktiv_y]=1;
            }
            ut=ut+irany;
        }while(quit!=true);

        string temp_ut=ut;
        ut="";
        for(int i=temp_ut.length()-1;i>-1;i--) ut=ut+temp_ut[i];

        for(int i=0;i<table_height;i++)
        {
            for(int j=0;j<table_width;j++)
            {
                if(path_table[j][i]==1 && table[j][i]==1)
                {
                    if(path_table[j][i-1]==1 && table[j][i-1]==0) path_table[j][i-1]=2;
                    if(path_table[j][i+1]==1 && table[j][i+1]==0) path_table[j][i+1]=2;
                    if(path_table[j-1][i]==1 && table[j-1][i]==0) path_table[j-1][i]=2;
                    if(path_table[j+1][i]==1 && table[j+1][i]==0) path_table[j+1][i]=2;
                }
            }
        }
        return ut[0];
    }

    //cout<<"!!"<<ut<<"!!"<<endl;
}

int can_escape(char c)
{
    for(int i=0;i<table_height;i++)
    {
        for(int j=0;j<table_width;j++)
        {
            temp_table[j][i]=table[j][i];
        }
    }

    switch(c)
    {
        case 'u': temp_table[doc_x][doc_y-1]=2; break;
        case 'd': temp_table[doc_x][doc_y+1]=2; break;
        case 'l': temp_table[doc_x-1][doc_y]=2; break;
        case 'r': temp_table[doc_x+1][doc_y]=2; break;
    }

    draw_table('t');
    cout<<endl;
    for(int i=0;i<table_height;i++)
    {
        for(int j=0;j<table_width;j++)
        {
            cout<<table[j][i]<<"  ";
        }
        cout<<endl;
    }
    cout<<endl;

    for(int i=0;i<table_height;i++)
    {
        for(int j=0;j<table_width;j++)
        {
            if(temp_table[j][i]==2)
            {
                int iranyok[4];
                for(int i=0;i<4;i++) iranyok[i]=0;
                int sugar=0;
                int kesz=0;
                do
                {
                    sugar++;
                    if((temp_table[j][i-sugar]==0 || temp_table[j][i-sugar]==-3) && iranyok[0]==0) temp_table[j][i-sugar]=5;
                    else {iranyok[0]=1; kesz++;}
                    if((temp_table[j][i+sugar]==0 || temp_table[j][i+sugar]==-3) && iranyok[1]==0) temp_table[j][i+sugar]=5;
                    else {iranyok[1]=1; kesz++;}
                    if((temp_table[j-sugar][i]==0 || temp_table[j-sugar][i]==-3) && iranyok[2]==0) temp_table[j-sugar][i]=5;
                    else {iranyok[2]=1; kesz++;}
                    if((temp_table[j+sugar][i]==0 || temp_table[j+sugar][i]==-3) && iranyok[4]==0) temp_table[j+sugar][i]=5;
                    else {iranyok[3]=1; kesz++;}
                }while(kesz!=4 && sugar!=radius);
            }
        }
    }

    draw_table('t');


    //-----------------------//

    for(int i=0;i<table_height;i++)
    {
        for(int j=0;j<table_width;j++)
        {
            distance_table[j][i]=-3;
            if(table[j][i]==-1) distance_table[j][i]=-1;
            if(table[j][i]==1) distance_table[j][i]=-1;
        }
    }

    int depth=0;
    bool quit=false;
    distance_table[doc_x][doc_y]=0;

    do
    {
        for(int i=1;i<table_height-1;i++)
        {
            for(int j=1;j<table_width-1;j++)
            {
                if(distance_table[j][i]==depth && quit==false)
                {
                    if(distance_table[j][i-1]>depth || distance_table[j][i-1]==-3 || (temp_table[j][i-1]!=5 && table[j][i-1]==0 && temp_table[j][i-1]!=2))
                    {
                        if(temp_table[j][i-1]!=5 && table[j][i-1]==0 && temp_table[j][i-1]!=2)
                        {
                            esc_x=j;
                            esc_y=i-1;
                            quit=true;
                        }
                        else distance_table[j][i-1]=depth+1;
                    }

                    if(distance_table[j][i+1]>depth || distance_table[j][i+1]==-3 || (temp_table[j][i+1]!=5 && table[j][i+1]==0 && temp_table[j][i+1]!=2))
                    {
                        if(temp_table[j][i+1]!=5 && table[j][i+1]==0 && temp_table[j][i+1]!=2)
                        {
                            esc_x=j;
                            esc_y=i+1;
                            quit=true;
                        }
                        else distance_table[j][i+1]=depth+1;
                    }

                    if(distance_table[j-1][i]>depth || distance_table[j-1][i]==-3 || (temp_table[j-1][i]!=5 && table[j-1][i]==0 && temp_table[j-1][i]!=2))
                    {
                        if(temp_table[j-1][i]!=5 && table[j-1][i]==0 && temp_table[j-1][i]!=2)
                        {
                            esc_x=j-1;
                            esc_y=i;
                            quit=true;
                        }
                        else distance_table[j-1][i]=depth+1;
                    }

                    if(distance_table[j+1][i]>depth || distance_table[j+1][i]==-3 || (temp_table[j+1][i]!=5 && table[j+1][i]==0 && temp_table[j+1][i]!=2))
                    {
                        if(temp_table[j+1][i]!=5 && table[j+1][i]==0 && temp_table[j+1][i]!=2)
                        {
                            esc_x=j+1;
                            esc_y=i;
                            quit=true;
                        }
                        else distance_table[j+1][i]=depth+1;
                    }
                }
            }
        }
        //draw_table('d');
        depth++;
    }while(quit!=true && depth!=activating_time);

    if(quit==true)
    {
        //cout<<"!!"<<esc_x<<"!!"<<esc_y<<"!!"<<table[esc_x][esc_y]<<endl;
        return true;
    }
}
