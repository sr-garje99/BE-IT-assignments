//=================================================================================
// Name        : Assignment6.cpp
// Author      : Devashish (23364)
// Version     : 1.0
// Copyright   : GNU Public License
// Description : Graph DFS and BFS
//				 1. DOB and No. of comments
//				 2. Find who has maximum and minimum comments
//				 3. Find who is having birthday this month
//				 4. Find who has maximum friends
//=================================================================================

#include <iostream>
#include <string.h>

using namespace std;

//==============================  Class declarations ==============================

// Date as a user defined data type
class Date
{
	int day;
	int month;
	int year;

	public:

	void getdate()
	{
		cout<<"\n Please enter the date ";
		cout<<"\n Enter the day (dd) - ";
		cin>>day;
		cout<<"\n Enter the month (mm) - ";
		cin>>month;
		cout<<"\n Enter the year (yyyy) - ";
		cin>>year;
	}
	void putdate()
	{
		cout<<"\n Date of birth (dd-mm-yyy) - "<<day<<"-"<<month<<"-"<<year;
	}
};

struct Vertex;

struct Graphedge
{
	int weight;
	Vertex* neighbourlink;
	Graphedge* nextlink;
};

struct Vertex
{
	char* name;
	Date dob;
	int comments;
	bool visited;
	Vertex* downlink;
	Graphedge* edgelink;

	Vertex()
	{
		name = new char[20];
		comments = 0;
		visited = false;
		downlink = NULL;
		edgelink = NULL;
	}

	void makeuser()
	{
		cout<<"\n INFO: Adding new user, Please enter the following details - ";
		cout<<"\n Name - ";
		cin>>name;
		cout<<"\n Date of Birth - ";
		dob.getdate();
		downlink = NULL;
	}

	void putdata()
	{
		cout<<"\n Name - "<<name;
		dob.putdate();
		cout<<"\n Comments - "<<comments;
	}
};

// Starting Node of the graph
struct startnode
{
	int cnt;
	Vertex* start;
};

// Initialize visited flag for all nodes
void initvisit(startnode *startnode)
{
	Vertex *temp = startnode->start;
	while(temp != NULL)
	{
		temp->visited = false;
		temp= temp->downlink;
	}
}

// Depth first traversal
void traversedfs(Vertex* temp)
{
	temp->visited = true;
	temp->putdata();
	Graphedge* g = temp->edgelink;
	while(g!=NULL)
	{
		if(g->neighbourlink->visited != true)
			traversedfs(g->neighbourlink);
		g = g->nextlink;
	}
}

// Add a new user to the network
startnode* addNode(startnode *startn)
{
	cout<<"\n\n INFO: Creating new User in the network";
	startnode *temp = startn;
	Vertex *tempv = temp->start;
	
	if(tempv == NULL)
	{
		tempv = new Vertex;
		tempv->makeuser();
		tempv->downlink = NULL;
		temp->start = tempv;
		return temp;
	}

	while(tempv->downlink!=NULL)
	{
		startn->cnt++;
		tempv=tempv->downlink;
	}

	tempv->downlink = new Vertex;
	tempv = tempv->downlink;
	tempv->downlink = NULL;
	tempv->makeuser();
	
	cout<<"\n\n INFO: User was added successfully in the network";
	return temp;
}

// Add friend 
startnode* addFriend(startnode *startn, char* name1, char* name2)
{
	int flg = 0;

	startnode *temp = startn;
	Vertex *v1 = startn->start; 
	Vertex *v2 = startn->start; 

	while(v1!=NULL)
	{	
		if(strcmp(v1->name,name1) != 0)
			v1=v1->downlink;
		else if(strcmp(v1->name,name1) == 0)
		{
			flg = 1;
			break;
		}
	}

	if(flg == 0)
	{
		cout<<"\n INFO:	The name specified as \" "<<name1<<" \"does not exist in the network, please try again !!!";
		return temp;
	}

	cout<<"\n"<<v1->name;

	flg = 0;
	v2 = startn->start; 

	while(v2!=NULL)
	{	
		if(strcmp(v2->name,name2) != 0)
			v2=v2->downlink;
		else
		{
			flg = 1;
			break;
		}
	}

	if(flg == 0)
	{
		cout<<"\n INFO: The name specified as \" "<<name2<<" \" does not exist in the network, please try again !!!";
		return temp;
	}

	Graphedge *ge1,*ge2;
	
	ge1 = new Graphedge;
	ge1->neighbourlink = v2;
	ge1->nextlink = NULL;
	v1->edgelink = ge1;

	ge2 = new Graphedge;
	ge2->neighbourlink = v1;
	ge2->nextlink = NULL;
	v2->edgelink = ge2;

	return temp;
}
int main()
{
	startnode *graph = new startnode;
	graph->start = NULL;

	char *name1 = new char[20], *name2 = new char[20];
	int choice;
	
	do
	{
		cout<<"\n\n\n ____________________________________";
		cout<<"\n|                                    ";
		cout<<"\n|                MENU                ";
		cout<<"\n|____________________________________";
		cout<<"\n|                                    ";
		cout<<"\n|  1. Create New User   ";
		cout<<"\n|  2. Make friends";
		cout<<"\n|  3. Maximum friends    ";
		cout<<"\n|  4. Maximum and minimum friends";
		cout<<"\n|  5. Users having birthday this month";
		cout<<"\n|  6. Traverse the graph";
		cout<<"\n|  7. Exit                          ";
		cout<<"\n|____________________________________";
		cout<<"\n Enter your choice - ";
		cin>>choice;

		switch(choice)
		{
			case 1:
				graph = addNode(graph);
				break;
			case 2:
				cout<<"\n Enter your name - ";
				cin>>name1;
				cout<<"\n Enter the name of the person whom you want to make friend - ";
				cin>>name2;
				graph = addFriend(graph, name1, name2);
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				initvisit(graph);
				traversedfs(graph->start);
				break;
			case 7:
				return 0;
			default:
				break;
		}
	}while(1);
	return 0;
}