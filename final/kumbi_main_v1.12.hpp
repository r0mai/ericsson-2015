#ifndef KUMBI_HPP
#define KUMBI_HPP

#include <iostream>
#include <string>
#include <fstream>
#include "Elements.hpp"
#include "Global.hpp"
#include "State.hpp"
#include "BMResponseHelper.hpp"
#include <vector>

using namespace std;

struct Kumbi {

public:

    int table_height, table_width; //+2 a keret miatt, az jatek ter bal felso sarka: (1;1)
	int tick=0;
	int radius;
	int activating_time=2;
	int dmg=6;
	int doc_x=4, doc_y=4;
	int del_x=1, del_y=1;
	int esc_x, esc_y;

	int table[100][100];
	int health_table[100][100];
	int distance_table[100][100];
	int path_table[100][100];
	int temp_table[100][100];
	int danger_table[100][100];
	int time_table[100][100];
	int save_table[100][100];
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
	void bomb_places();


    ResponseHelper  rH;
    bm::Doc *doc;


};

#endif