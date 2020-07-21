#include<iostream>
#include<conio.h>
#include<fstream>

using namespace std;

struct node{
	int data;
	int kmro;
	string nalo;
	string address;
	string phone;
	node *next;
	node *rptr, *lptr;
};

 
struct hotel
{
	node *root, *head, *last;
	hotel(){
		root = NULL;
		head = NULL;
		last = NULL;
	}
	int room_no;
	string name;
	string address;
	string phone;
 
	void add()
	{
		int r,flag;
		ofstream fout("Record.txt", ios::app);	
		cout<<"\n\n\n\t\t\t\t\t   Enter Customer Detalis";
		cout<<"\n\t\t\t\t\t   **********************";
		cout<<"\n\n\t\t\t\t\t\t   Room no: ";
		cin>>r;
		flag=check(r);
		if(flag)
			cout<<"\n\n\t\t\t\t\t   Sorry..!!!Room is already booked";
		else
		{
			room_no=r;
			cout<<"\n\t\t\t\t\t   Enter name in one word: ";
			cin.ignore();
			getline(cin,name);
			cout<<"\n\t\t\t\t\t   City: ";
			getline(cin,address);
			cout<<"\n  \t\t\t\t\t   Phone No: ";
			getline(cin,phone);
			fout<<room_no<<"   "<<name<<"   "<<address<<"   "<<phone<<endl;
			cout<<"\n  \t\t\t\t\t   Room is booked!!!";
		}
		cout<<"\n\n\t\t\t\t\t   Press any key to continue!!";
		getch();
	//	system("CLS");
		fout.close();
	}
	
	
	
 
	void display()
	{
		ifstream fin("Record.txt",ios::in);
		int r,flag;
		cout<<"\n\n\t\t\t\t\t   Enter room no: ";
		cin>>r;
		while(!fin.eof())
		{
			fin>>room_no>>name>>address>>phone;
			if(room_no==r)
			{
				cout<<"\n\n\t\t\t\t\t   Cusromer Details";
				cout<<"\n\t\t\t\t\t   ****************";
				cout<<"\n\t\t\t\t\t\t   Room no: "<<room_no;
				cout<<"\n\t\t\t\t\t\t   Name: "<<name;
				cout<<"\n\t\t\t\t\t\t   City: "<<address;
				cout<<"\n\t\t\t\t\t\t   Phone no: "<<phone;
				flag=1;
				break;
			}
		}
		if(flag==0)
			cout<<"\n\t\t\t\t\t\t   Sorry Room no. not found or vacant!!";
		cout<<"\n\t\t\t\t\t   Press any key to continue!!";
//		getch();
//		system("CLS");
		fin.close();
	}
 
 
	int check(int r)
	{
		int flag=0;
		ifstream fin("Record.txt",ios::in);
		while(fin>>room_no)
		{
			if(room_no==r)
			{
				flag=1;
				break;
			}
		}
		fin.close();
		return(flag);
	}
 
	void modify(int r)
	{
		int flag=0;
		char ch;
		ifstream fin("Record.txt",ios::in);
		ofstream fout("temp.txt",ios::out);
		while(fin>>room_no)
		{
			fin>>name>>address>>phone;
			if(room_no==r)
			{
//				cout<<"\n\t\t\t\t\t    Name: "<<name;
//				cout<<"\n\t\t\t\t\t    Address: "<<address;
//				cout<<"\n\t\t\t\t\t    Pone No: "<<phone<<endl;
//			//	cout<<"\n\n Do you want to delete this record(y/n): ";
//			//	cin>>ch;
				
				cout<<"\n\t\t\t\t\t Enter New Details";
				cout<<"\n\t\t\t\t\t *****************";
				cout<<"\n\t\t\t\t\t Name: ";
				cin.ignore();
				getline(cin,name);
				cout<<"\n\t\t\t\t\t City: ";
				getline(cin,address);
				cout<<"\n\t\t\t\t\t Phone no: ";
				getline(cin,phone);
					fout<<room_no<<"   "<<name<<"   "<<address<<"   "<<phone<<endl;
					flag=1;
			}
			else
				fout<<room_no<<"   "<<name<<"   "<<address<<"   "<<phone<<endl;
		}
	
		fin.close();
		fout.close();
		if(flag==0)
			cout<<"\n Sorry room no. not found or vacant!!";
		else
		{
			remove("Record.txt");
			rename("temp.txt","Record.txt");
		}
	}
	
	void equeue(int room, string name, string add, string phone){
			node* newNode=new node;
			newNode->kmro=room;
			newNode->nalo=name;
			newNode->address=add;
			newNode->phone=phone;
			newNode->next=NULL;
			if(head==NULL){
				head=newNode;
				last=newNode;
			}
			else{
				last->next=newNode;
				last=newNode;
				
			}
	}

	void insert(int room, string name, string add, string phone){
		node *newNode = new node;
		node *parent = NULL;
		newNode->lptr = NULL;
		newNode->rptr = NULL;
		newNode->kmro = room;
		newNode->nalo = name;
		newNode->address = add;
		newNode->phone = phone;

		if(root == NULL){
				root = newNode;
		}
		else{
			node *currNode = root;
			while(currNode!=NULL){
				parent = currNode;
				if(name>currNode->nalo)
					currNode = currNode->rptr;
				else
					currNode = currNode->lptr;
			}
			if(name>parent->nalo)
				parent->rptr = newNode;
			else
				parent->lptr = newNode;
		}
		
	}

	
	void print(node *ptr){
		if(ptr!=NULL){
			cout<<"\n\t\t\t "<<ptr->kmro<<"\t\t"<<ptr->nalo<<"\t\t"<<ptr->address<<"\t\t"<<ptr->phone<<"\n";
			print(ptr->lptr);
			print(ptr->rptr);
		}
	}
	
	
	node* FindMin(node* root)
	{
		while(root->lptr != NULL) root = root->lptr;
		return root;
	}

	node* Delete(struct node *root, int data) {
		if(root == NULL) return root; 
		else if(data < root->data) root->lptr = Delete(root->lptr,data);
		else if (data > root->data) root->rptr = Delete(root->rptr,data);
		else {
			if(root->lptr == NULL && root->rptr == NULL) { 
				delete root;
				root = NULL;
			}
			else if(root->lptr == NULL) {
				node *temp = root;
				root = root->rptr;
				delete temp;
			}
			else if(root->rptr == NULL) {
				node *temp = root;
				root = root->lptr;
				delete temp;
			}
			else { 
				node *temp = FindMin(root->rptr);
				root->data = temp->data;
				root->rptr = Delete(root->rptr,temp->data);
			}
		}
		return root;
	}


	void delete_rec(int r)
	{
		int flag=0;
		char ch;
		ifstream fin("Record.txt",ios::in);
		ofstream fout("temp.txt",ios::out);
		while(fin>>room_no)
		{
			fin>>name>>address>>phone;
			if(room_no==r)
			{
				cout<<"\n\t\t\t\t\t Name: "<<name;
				cout<<"\n\t\t\t\t\t Address: "<<address;
				cout<<"\n\t\t\t\t\t Pone No: "<<phone;
				cout<<"\n\t\t\t\t\t Do you want to delete this record(y/n): ";
				cin>>ch;
				if(ch=='n')
				{
					fout<<room_no<<"   "<<name<<"   "<<address<<"   "<<phone<<endl;
				
				}
				else
					flag=1;
			}
			else
				fout<<room_no<<"   "<<name<<"   "<<address<<"   "<<phone<<endl;
		}
	
		fin.close();
		fout.close();
		if(flag==0)
			cout<<"\n\t\t\t\t\t Sorry room no. not found or vacant!!";
		else
		{
			remove("Record.txt");
			rename("temp.txt","Record.txt");
		}
	}
	
	
	void sent_to_tree(){
		node *disp = head;
		while(disp!=NULL){
			insert(disp->kmro,disp->nalo,disp->address,disp->phone);
			disp = disp->next;
		}
	}
	

	
	
	
	
	

	
	
};
 

 
int main()
{
	hotel h;
	int r;
	string n, ad, ph;
    ifstream fin("Record.txt", ios::in);
	while(fin>>r){
    	fin>>n>>ad>>ph;
    	h.equeue(r,n,ad,ph);
	}
	fin.close();
	cout<<"\n\t\t\t\t\t****************************";
	cout<<"\n\t\t\t\t\t* HOTEL MANAGEMENT PROJECT *";
	cout<<"\n\t\t\t\t\t****************************";
	
	cout<<"\n\t\t\t\t\t     Made By:";
	cout<<"Nouman Ali";
	cout<<"\n\n\t\t\t\t\tPress any key to continue!!";
	getch();
	int choice;
	while(choice!=6)
	{
		cout<<"\n\n\t\t\t\t\t\t*************";
		cout<<"\n\t\t\t\t\t\t* MAIN MENU *";
		cout<<"\n\t\t\t\t\t\t*************";
		cout<<"\n\n\n\t\t\t\t\t   1.Book A Room";
		cout<<"\n\t\t\t\t\t   2.Customer Record";
		cout<<"\n\t\t\t\t\t   3.Rooms Allotted";
		cout<<"\n\t\t\t\t\t   4.Edit Record";
		cout<<"\n\t\t\t\t\t   5.Delete";
		cout<<"\n\t\t\t\t\t   6.Exit";
		cout<<"\n\n\t\t\t\t\t   Enter Your Choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1: 
					h.add();
					system("cls");
					main();
					break;
			case 2: 
					h.display();
					break;
			case 3: 
					cout<<"\n\n\t\t\t\t\t   List Of Rooms Allotted";
					cout<<"\n\n\t\t\t\t\t   *********************";
					cout<<"\n\n\t\t\tRoom No.\tName\t\tCity\t\tPhone No.\n";
					h.sent_to_tree();
					h.print(h.root);
					cout<<"\n\t\t\t\t\t\t      Press any key ";
//					getch();
//					system("CLS");
					break;
			case 4: 
					int r;
					cout<<"\n\t\t\t\t\t   Enter room no: ";
					cin>>r;
					h.modify(r);
					cout<<"\n\t\t\t\t\t   Record Modified ^_^";
					getch();
					system("cls");
					main();
					break;
			case 5:
					int f;
					cout<<"\n\t\t\t\t\t   Enter room no: ";
					cin>>f;
					h.delete_rec(f);
					h.root = h.Delete(h.root,f);
					cout<<"\n\t\t\t\t\t   Room delete Successfully ^_^";
					getch();
					system("cls");
					main();
					cout<<"\n\t\t\t\t\t Press any key ";
					break;
			case 6:
					exit(true);
					break;
			default:
					{
						cout<<"\n\n\t\t\t\t\t   Wrong choice!!!";
						cout<<"\n\t\t\t\t\tPress any key to continue!!";
						getch();
					}
		}
		getch();
		system("CLS");
	}
	
	
	return 0;
}
