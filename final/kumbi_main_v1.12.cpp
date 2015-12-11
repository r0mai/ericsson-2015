#include "kumbi_main_v1.12.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include "Elements.hpp"
#include "State.hpp"
#include "Global.hpp"
#include "BMResponseHelper.hpp"
#include <chrono>

bool Kumbi::would_survive(char c)
{
    int temp_table[100][100];

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

    for(int i=0;i<table_height;i++)
    {
        for(int j=0;j<table_width;j++)
        {
            distance_table[j][i]=-3;
            if(temp_table[j][i]==-1) distance_table[j][i]=-1;
            if(temp_table[j][i]==1) distance_table[j][i]=-5;
            if(temp_table[j][i]==2) distance_table[j][i]=-6;
        }
    }

    int depth=0;
    bool quit=false;
    distance_table[doc_x][doc_y]=0;



    //!!!!!!!!!!!!!!!!!!!

    for(int i=0;i<table_height;i++)
    {
        for(int j=0;j<table_width;j++)
        {
            danger_table[j][i]=temp_table[j][i];
            if(temp_table[j][i]==-2) danger_table[j][i]=0;
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

    //!!!!!!!!!!!!!!!!!!!


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
                        if(danger_table[j][i-1]==0) {safe_x=j; safe_y=i-1; return true;}
                        else if(distance_table[j][i-1]==-5)
                        {
                            distance_table[j][i-1]=depth+1+health_table[j][i-1]*3;
                        }
                        else distance_table[j][i-1]=depth+1;
                    }

                    if(distance_table[j][i+1]>depth || distance_table[j][i+1]==-3 || distance_table[j][i+1]==-2 || distance_table[j][i+1]==-5)
                    {
                        if(danger_table[j][i+1]==0) {safe_x=j; safe_y=i+1; return true;}
                        else if(distance_table[j][i+1]==-5)
                        {
                            distance_table[j][i+1]=depth+1+health_table[j][i+1]*3;
                        }
                        else distance_table[j][i+1]=depth+1;
                    }

                    if(distance_table[j-1][i]>depth || distance_table[j-1][i]==-3 || distance_table[j-1][i]==-2 || distance_table[j-1][i]==-5)
                    {
                        if(danger_table[j-1][i]==0) {safe_x=j-1; safe_y=i; return true;}
                        else if(distance_table[j-1][i]==-5)
                        {
                            distance_table[j-1][i]=depth+1+health_table[j-1][i]*3;
                        }
                        else distance_table[j-1][i]=depth+1;
                    }

                    if(distance_table[j+1][i]>depth || distance_table[j+1][i]==-3 || distance_table[j+1][i]==-2 || distance_table[j+1][i]==-5)
                    {
                        if(danger_table[j+1][i]==0) {safe_x=j+1; safe_y=i; return true;}
                        else if(distance_table[j+1][i]==-5)
                        {
                            distance_table[j+1][i]=depth+1+health_table[j+1][i]*3;
                        }
                        else distance_table[j+1][i]=depth+1;
                    }
                }
            }
        }
        depth++;
    }while(depth!=activating_time);
    return false;
}

void Kumbi::bomb_places()
{
    for(int i=0;i<table_height;i++)
    {
        for(int j=0;j<table_width;j++)
        {
            if(path_table[j][i]==3)
            {
                int iranyok[4];
                for(int i=0;i<4;i++) iranyok[i]=0;
                int sugar=0;
                int kesz=0;
                do
                {
                    kesz=0;
                    sugar++;
                    if(table[j][i-sugar]==0 && iranyok[0]==0) path_table[j][i-sugar]=2;
                    else {iranyok[0]=1;}
                    if(table[j][i+sugar]==0 && iranyok[1]==0) path_table[j][i+sugar]=2;
                    else {iranyok[1]=1;}
                    if(table[j-sugar][i]==0 && iranyok[2]==0) path_table[j-sugar][i]=2;
                    else {iranyok[2]=1;}
                    if(table[j+sugar][i]==0 && iranyok[3]==0) path_table[j+sugar][i]=2;
                    else {iranyok[3]=1;}

                    for(int i=0;i<4;i++) if(iranyok[i]==1) kesz++;
                }while(kesz!=4 && sugar!=radius);

            }
        }
    }
}

void Kumbi::find_safe_place()
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
    }while(quit!=true && depth!=activating_time);
    if(!quit) cout<<"MEGHALTAL"<<endl;
}

void Kumbi::create_path(int cel_x, int cel_y)
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
                            else if(table[j][i-1]==1 && distance_table[j][i-1]==-5)
                            {
                                if(table[j][i-1]==1) distance_table[j][i-1]=depth+1+health_table[j][i-1]*8;
                            }
                            else if(table[j][i-1]!=1) distance_table[j][i-1]=depth+1;
                        }

                        if(distance_table[j][i+1]>depth || distance_table[j][i+1]==-3 || distance_table[j][i+1]==-2 || table[j][i+1]==1)
                        {
                            if(distance_table[j][i+1]==-2) quit=true;
                            else if(table[j][i+1]==1 && distance_table[j][i+1]==-5)
                            {
                                if(table[j][i+1]==1) distance_table[j][i+1]=depth+1+health_table[j][i+1]*8;
                            }
                            else if(table[j][i+1]!=1) distance_table[j][i+1]=depth+1;
                        }

                        if(distance_table[j-1][i]>depth || distance_table[j-1][i]==-3 || distance_table[j-1][i]==-2 || table[j-1][i]==1)
                        {
                            if(distance_table[j-1][i]==-2) quit=true;
                            else if(table[j-1][i]==1 && distance_table[j-1][i]==-5)
                            {
                                if(table[j-1][i]==1) distance_table[j-1][i]=depth+1+health_table[j-1][i]*8;
                            }
                            else if(table[j-1][i]!=1) distance_table[j-1][i]=depth+1;
                        }

                        if(distance_table[j+1][i]>depth || distance_table[j+1][i]==-3 || distance_table[j+1][i]==-2 || table[j+1][i]==1)
                        {
                            if(distance_table[j+1][i]==-2) quit=true;
                            else if(table[j+1][i]==1 && distance_table[j+1][i]==-5)
                            {
                                if(table[j+1][i]==1) distance_table[j+1][i]=depth+1+health_table[j+1][i]*8;
                            }
                            else if(table[j+1][i]!=1) distance_table[j+1][i]=depth+1;
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
                if(path_table[j][i]==1 && table[j][i]==1)
                {
                    path_table[j][i]=3;
                }
            }
        }
        bomb_places();
        path_table[cel_x][cel_y]=1;
    }
}

char Kumbi::follow_path()
{
    inDanger();
    //draw_table('a');
    //draw_table('p');
    //cout<<"!!!"<<path_table[doc_x][doc_y-1]<<"!!"<<danger_table[doc_x][doc_y-1]<<endl;
    if(path_table[doc_x][doc_y-1]==1 && danger_table[doc_x][doc_y-1]==0) return 'u';
    else if(path_table[doc_x][doc_y-1]==2)
    {
        if(would_survive('u')) {
            if (table[doc_x][doc_y-1] == 8) {
                return 'u';
            } else {
                put_bomb('u',activating_time,2);
            }
        }
        else
        {
            path_table[doc_x][doc_y-1]=1;
            return follow_path();
        }
    }
    else if(path_table[doc_x][doc_y-1]==3)
    {
        if(table[doc_x][doc_y+1]==0 && danger_table[doc_x][doc_y+1]==0) return 'd';
        if(table[doc_x-1][doc_y]==0 && danger_table[doc_x-1][doc_y]==0) return 'l';
        if(table[doc_x+1][doc_y]==0 && danger_table[doc_x+1][doc_y]==0) return 'r';
    }

    if(path_table[doc_x][doc_y+1]==1 && danger_table[doc_x][doc_y+1]==0) return 'd';
    else if(path_table[doc_x][doc_y+1]==2)
    {
        if(would_survive('d'))
            if (table[doc_x][doc_y+1] == 8) {
                return 'd';
            } else {
                put_bomb('d',activating_time,2);
            }
        else
        {
            path_table[doc_x][doc_y+1]=1;
            return follow_path();
        }
    }
    else if(path_table[doc_x][doc_y+1]==3)
    {
        if(table[doc_x][doc_y-1]==0 && danger_table[doc_x][doc_y-1]==0) return 'u';
        if(table[doc_x-1][doc_y]==0 && danger_table[doc_x-1][doc_y]==0) return 'l';
        if(table[doc_x+1][doc_y]==0 && danger_table[doc_x+1][doc_y]==0) return 'r';
    }

    if(path_table[doc_x-1][doc_y]==1 && danger_table[doc_x-1][doc_y]==0) return 'l';
    else if(path_table[doc_x-1][doc_y]==2)
    {
        if(would_survive('l'))
            if (table[doc_x-1][doc_y] == 8) {
                return 'l';
            } else {
                put_bomb('l',activating_time,2);
            }
        else
        {
            path_table[doc_x-1][doc_y]=1;
            return follow_path();
        }
    }
    else if(path_table[doc_x-1][doc_y]==3)
    {
        if(table[doc_x][doc_y+1]==0 && danger_table[doc_x][doc_y+1]==0) return 'd';
        if(table[doc_x][doc_y-1]==0 && danger_table[doc_x][doc_y-1]==0) return 'u';
        if(table[doc_x+1][doc_y]==0 && danger_table[doc_x+1][doc_y]==0) return 'r';
    }

    if(path_table[doc_x+1][doc_y]==1 && danger_table[doc_x+1][doc_y]==0) return 'r';
    else if(path_table[doc_x+1][doc_y]==2)
    {
        if(would_survive('r'))
            if (table[doc_x+1][doc_y] == 8) {
                return 'r';
            } else {
                put_bomb('r',activating_time,2);
            }
        else
        {
            path_table[doc_x+1][doc_y]=1;
            return follow_path();
        }
    }
    else if(path_table[doc_x+1][doc_y]==3)
    {
        if(table[doc_x][doc_y+1]==0 && danger_table[doc_x][doc_y+1]==0) return 'd';
        if(table[doc_x][doc_y-1]==0 && danger_table[doc_x][doc_y-1]==0) return 'u';
        if(table[doc_x-1][doc_y]==0 && danger_table[doc_x-1][doc_y]==0) return 'l';
    }
    //cout<<"ASD"<<endl;
    return 's';
}

char Kumbi::escape_path()
{
    if(path_table[doc_x][doc_y-1]==1) return 'u';
    if(path_table[doc_x][doc_y+1]==1) return 'd';
    if(path_table[doc_x-1][doc_y]==1) return 'l';
    if(path_table[doc_x+1][doc_y]==1) return 'r';
    return 's';
}

bool Kumbi::inDanger()
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

void Kumbi::compute()
{
    for(int i=0;i<table_height;i++)
    {
        for(int j=0;j<table_width;j++)
        {
            if(time_table[j][i]>0) time_table[j][i]--;
        }
    }


    if(van_bomba())
    {
        for(int i=0;i<table_height;i++)
        {
            for(int j=0;j<table_width;j++)
            {
                if(table[j][i]==2)
                {
                    health_table[j][i]--;
                    //cout<<"XXX"<<j<<"XXX"<<i<<"XXX"<<endl;
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
                                if(health_table[j][i-sugar]>0)
                                {
                                    save_table[j][i-sugar]=table[j][i-sugar];
                                    table[j][i-sugar]=0;
                                    time_table[j][i-sugar]=dmg;
                                }
                            }
                            if((table[j][i+sugar]==0 || table[j][i+sugar]==-3) || iranyok[1]==1) a++;
                            else
                            {
                                iranyok[1]=1; kesz++;
                                if(table[j][i+sugar]==1) health_table[j][i+sugar]--;
                                if(health_table[j][i-sugar]>0)
                                {
                                    save_table[j][i+sugar]=table[j][i+sugar];
                                    table[j][i+sugar]=0;
                                    time_table[j][i+sugar]=dmg;
                                }
                            }
                            if((table[j-sugar][i]==0 || table[j-sugar][i]==-3) || iranyok[2]==1) a++;
                            else
                            {
                                iranyok[2]=1; kesz++;
                                if(table[j-sugar][i]==1) health_table[j-sugar][i]--;
                                if(health_table[j][i-sugar]>0)
                                {
                                    save_table[j-sugar][i]=table[j-sugar][i];
                                    table[j-sugar][i]=0;
                                    time_table[j-1][sugar]=dmg;
                                }
                            }
                            if((table[j+sugar][i]==0 || table[j+sugar][i]==-3) || iranyok[3]==1) a++;
                            else
                            {
                                iranyok[3]=1; kesz++;
                                if(table[j+sugar][i]==1) health_table[j+sugar][i]--;
                                if(health_table[j][i-sugar]>0)
                                {
                                    save_table[j+sugar][i]=table[j+sugar][i];
                                    table[j+sugar][i]=0;
                                    time_table[j+1][sugar]=dmg;
                                }
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
            if(time_table[j][i]==0 && save_table[j][i]!=0)
            {
                table[j][i]=save_table[j][i];
            }
            if(table[j][i]==1 && health_table[j][i]==0) table[j][i]=0;
        }
    }
}

bool Kumbi::van_bomba()
{
    for(int i=0;i<table_height;i++)
    {
        for(int j=0;j<table_width;j++)
        {
            if(table[j][i]==2) return true;
        }
    }
    return false;
}

bool Kumbi::build_order() {
    if (docCount != 2) {
        return false;
    }
    switch (tick) {
        default: return false;
        case 1: move_doc('d'); return true;
        case 2: put_bomb('u',3,2); return true;
        case 3: move_doc('d'); return true;
        case 4: move_doc('d'); return true;
        case 5: move_doc('s'); return true;
        case 6: move_doc('u'); return true;
        case 7: move_doc('u'); return true;
        case 8: move_doc('u'); return true;
        case 9: move_doc('l'); return true;
        case 10: move_doc('r'); return true;
        case 11: move_doc('r'); return true;
        case 12: move_doc('l'); return true;
        case 13: move_doc('d'); return true;
        case 14: put_bomb('u',3,2); return true;
        case 15: move_doc('d'); return true;
        case 16: move_doc('d'); return true;
        case 17: move_doc('s'); return true;
        case 18: move_doc('u'); return true;
        case 19: move_doc('u'); return true;
        case 20: move_doc('u'); return true;
        case 21: move_doc('l'); return true;
        case 22: move_doc('l'); return true;
        case 23: move_doc('r'); return true;
        case 24: move_doc('r'); return true;
        case 25: move_doc('r'); return true;
        case 26: move_doc('r'); return true;
        case 27: move_doc('r'); return true;
    }
}

void Kumbi::add_table(bm::State& state, bm::Doc& doci)
{

    table_height = state.height;
    table_width = state.width;
    tick = state.tick;

    this->doc = doci;
    radius = doci.informations.next_flux_capatitor.radius;

    docCount = 0;
        for(int i=0; i<table_height;i++)
        {
            for(int j=0;j<table_width;j++)
            {
                if(state.fields[j][i].is(bm::ElementType::WALL)) table[j][i]=-1;
                else if(state.fields[j][i].is(bm::ElementType::CHEST)) table[j][i]=1;
                else if(state.fields[j][i].is(bm::ElementType::BLANK)) table[j][i]=0;
                else if(state.fields[j][i].is(bm::ElementType::DELOREAN)) table[j][i]=-2;
                else if(state.fields[j][i].is(bm::ElementType::DOC)) {
                    ++docCount;
                    if (state.fields[j][i].as<bm::Doc>().id == state.our_doc_id) {
                        table[j][i]=-3;
                    } else {
                        table[j][i]= 1;
                        health_table[j][i] = 1;
                    }
                }
                else if(state.fields[j][i].is(bm::ElementType::FLUXCAPATITOR)) table[j][i]=2;
                else if(state.fields[j][i].is(bm::ElementType::CAPABILITY)) table[j][i]=8;
            }
        }

        for(int i=0; i<table_height;i++)
        {
            for(int j=0;j<table_width;j++)
            {
                if(state.fields[j][i].is<bm::Chest>())
                    health_table[j][i] = state.fields[j][i].as<bm::Chest>().survive_timetravels;
                else
                    health_table[j][i] = 0;
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

    rH.nothing();
}

void Kumbi::draw_table(char c)
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
                cout<<danger_table[j][i]<<"   ";
            }
        }
        cout<<endl;
    }
}

void Kumbi::show_tick()
{
    cout<<endl<<"tick: "<<tick<<endl;
}

void Kumbi::move_doc(char c)
{
    switch(c)
    {
        case 'u':
        {
            rH.moveUp();
        }
        break;

        case 'd':
        {
            rH.moveDown();
        }
        break;

        case 'l':
        {
            rH.moveLeft();
        }
        break;


        case 'r':
        {
            rH.moveRight();
        }
        break;

        case 's': /*rH.nothing();*/ break;
    }
}

void Kumbi::put_bomb(char c, int turns_to_activate, int dmg)
{
    if(this->doc.flux_capatitors.size()>0) {

        cerr << "Belep a putba\n";
        cerr << "Irany: " << c <<"\n";

        switch (c) {
            case 'u': {
                rH.putUp(this->doc.flux_capatitors[0].id, dmg);
            }
                break;

            case 'd': {
                rH.putDown(this->doc.flux_capatitors[0].id, dmg);
            }
                break;

            case 'l': {
                rH.putLeft(this->doc.flux_capatitors[0].id, dmg);
            }
                break;

            case 'r': {
                rH.putRight(this->doc.flux_capatitors[0].id, dmg);
            }
                break;
        }
    }
}

char Kumbi::shortest_path(char c)
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
    assert(false);
    return 'X';
    //cout<<"!!"<<ut<<"!!"<<endl;
}

int Kumbi::can_escape(char c)
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
                    if((temp_table[j+sugar][i]==0 || temp_table[j+sugar][i]==-3) && iranyok[3]==0) temp_table[j+sugar][i]=5;
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
    return false;
}
