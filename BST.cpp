#include "BST.h"

BST::BST()
{
	nulltree = true;
	root = NULL;
	current = NULL;
	pred = NULL;
};

bool BST::isEmpty()
{
	return nulltree;
};

bool BST::insert(string f_title, string f_day, string f_hour)
{
	link addednode;
	addednode = new node;
	addednode->title = f_title;
	addednode->day = f_day;
	addednode->hour = f_hour;
	addednode->Right = NULL;
	addednode->Left = NULL;


	if (root == NULL)   //empty tree
	{
		addednode->Left = NULL;
		addednode->Right = NULL;
		root = addednode;
		nulltree = false;
		return 1;
	}

	if (root != NULL)
	{
		current = root;
		while (1)
		{
			if ((stoi(f_day) == stoi(current->day)) && (stoi(f_hour) == stoi(current->hour)))  // data conflict (same day andd hour) 
			{
				cout << "Conflict"<<" "<<f_day<<" "<<f_hour<< endl;
				return 0;
			}

			if (stoi(f_day) < stoi(current->day))   
			{
				if (current->Left == NULL) { current->Left = addednode; return 1; }
				else { current = current->Left;  continue; }				
			}
			
			if (stoi(f_day) > stoi(current->day))
			{
				if (current->Right == NULL) { current->Right = addednode; return 1; }
				else { current = current->Right;  continue; }
			}

			if ((stoi(f_hour) < stoi(current->hour)) && (stoi(f_day) == stoi(current->day)))
			{
				if (current->Left == NULL) { current->Left = addednode; return 1; }
				else { current = current->Left;  continue; }
			}

			if ((stoi(f_hour) > stoi(current->hour)) && (stoi(f_day) == stoi(current ->day)))
			{
				if (current->Right == NULL) { current->Right = addednode; return 1; }
				else { current = current->Right;  continue; }
			}

		}
	}
	
};



string BST::find(string f_day, string f_hour)
{
	if (root == NULL) //empty list (error)
	{
		return "Empty day hour";
	}
	current = root;
	while (1)
	{

		if (current == NULL)  // data not found 
		{
			return "Empty day hour";
		}

		if ((stoi(f_day) == stoi(current->day)) && (stoi(f_hour) == stoi(current->hour)))  // data found 
		{
			return current->title;
		}

		if (stoi(f_day) < stoi(current->day))
		{
			pred = current;
			current = current->Left;
			continue;
		}

		if (stoi(f_day) > stoi(current->day))
		{
			pred = current;
			current = current->Right;
			continue;
		}

		if ((stoi(f_day) == stoi(current->day)) && (stoi(f_hour) < stoi(current->hour)))
		{
			pred = current;
			current = current->Left;
			continue;
		}

		if ((stoi(f_day) == stoi(current->day)) && (stoi(f_hour) > stoi(current->hour)))
		{
			pred = current;
			current = current->Right;
			continue;
		}
	}
};


bool BST::mod(string f_title, string f_day, string f_hour)
{
	if (find(f_day, f_hour) != "Empty day hour")
		current->title = f_title;
	else
		cout << "Empty"<<" "<<f_day<<" "<<f_hour<< endl;
	return 1;
	
};

bool BST::remove(string f_day, string f_hour)
{
	bool entered = false;

	if (find(f_day, f_hour) != "Empty day hour")
	{
		bool Right = true;
		link temp = current;
		while (current != NULL)
		{
			if (current->Right != NULL)
			{
				current->title = current->Right->title;
				current->day = current->Right->day;
				current->hour = current->Right->hour;
				temp = current;
				current = current->Right;
				entered = true;
				Right = true;
			}
			else if (current->Left != NULL)
			{
				current->title = current->Left->title;
				current->day = current->Left->day;
				current->hour = current->Left->hour;
				temp = current;
				current = current->Left;
				entered = true;
				Right = false;
			}
			else
			{
				if (!entered)
				{
					if (stoi(f_day) < stoi(pred->day))
					{
						pred->Left = NULL;
					}

					else if (stoi(f_day) > stoi(pred->day))
					{
						pred->Right = NULL;
					}

					else if ((stoi(f_day) == stoi(pred->day)) && (stoi(f_hour) < stoi(pred->hour)))
					{
						pred->Left = NULL;
					}
					else if ((stoi(f_day) == stoi(pred->day)) && (stoi(f_hour) > stoi(pred->hour)))
					{
						pred->Right = NULL;
					}
			    }
				if (Right) { temp->Right = NULL; }
				else { temp->Left = NULL;}
				delete current;
				current = NULL;
			}
		}

	}
	else
		cout << "Empty "<<f_day<<" "<<f_hour<< endl;
	


	return 1;
};


void BST::inordertraverse(link currentpos)
{
	
	if (currentpos != NULL)
	{

		inordertraverse(currentpos->Left);

		cout << currentpos->title <<" "<<currentpos->day<<" "<<currentpos->hour<< endl;

		inordertraverse(currentpos->Right);
	}
};


bool BST::printall()
{

	if (isEmpty())
	{
		cout << "Empty Planner" << endl;
		return 1;
	}
	current = root;
	inordertraverse(current);
	return 1;

};


BST::~BST()
{
	int countttttt = 0;
	current = root;
	while (1)
	{
		if (current->Left == NULL && current->Right == NULL)
		{
			break;
			
		}
		else
		{
			remove(current->day, current->hour);
			current = root;
			countttttt++;
		}
	}
	delete current;
};
