#include <iostream>
#include <string>
#include <fstream>
#include "kumbi_main_v1.12.hpp"

using namespace std;

int main()
{
    Kumbi kumbi;
	kumbi.add_table();
    kumbi.show_tick();
    kumbi.draw_table('r');

    for(int i=0;i<kumbi.table_height;i++)
    {
        for(int j=0;j<kumbi.table_width;j++)
        {
            kumbi.time_table[j][i]=0;
            kumbi.save_table[j][i]=kumbi.table[j][i];
        }
    }

    //draw_table('h');
    bool quit=false;
    do
    {
        char i;
        cin>>i;
        kumbi.create_path(del_x,del_y);
        if(kumbi.inDanger())
        {
            kumbi.find_safe_place();
            kumbi.create_path(kumbi.safe_x, kumbi.safe_y);
            kumbi.move_doc(kumbi.escape_path());
        }
        else kumbi.move_doc(kumbi.follow_path());
        kumbi.tick++;
        kumbi.compute();
        //kumbi.draw_table('h');
        kumbi.show_tick();
        kumbi.draw_table('r');
        //kumbi.draw_table('p');
    }while(quit!=true);
    return 0;
}