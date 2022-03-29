#pragma once

#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class BST
{
public:

	BST();  //construcor
	bool insert(string f_title, string f_day, string f_hour);
	bool isEmpty();
	string find(string f_day, string f_hour);
	bool mod(string f_title, string f_day, string f_hour);
	bool remove(string f_day, string f_hour);
	bool printall();
	
    ~BST(); //deconstructor

private:

	struct node;
	typedef node* link;

	struct node
	{
		string title;
		string day;
		string hour;
		link Right;
		link Left;
	};
	bool nulltree;
	link current;
	link root;
	link pred;

	void inordertraverse(link currentpos);
};