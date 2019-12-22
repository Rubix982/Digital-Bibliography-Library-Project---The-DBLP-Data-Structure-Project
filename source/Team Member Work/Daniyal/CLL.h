#include<iostream>
using namespace std;

class node{

	public:
	int word;
	node *next;
	node()
	{	
		word=0;
		next=NULL;

	}
	node(int wrd,node *nex)
	{
		word=wrd;
		next=nex;
	}
};

class CLL{
	public:
	node *head;
	node *tail;
	int size;
	CLL()
	{
		head=NULL;
		size=0;
		tail=NULL;
	}
	void add_to_head(int n)
	{
		size++;
		if(head==NULL)
		{
			tail=head=new node(n,head);
			head->next=head;
		}
		else
		{
			head=new node(n,head);
			tail->next=head;
		}
	}
	void add_to_tail(int n)
	{
		size++;
		if(tail==NULL)
		{
			head=tail=new node(n,head);
		}
		else
		{
			tail->next=new node(n,head);
			tail=tail->next;
		}
	}
	void display()
	{
		int flg=0;
		node *temp;
		cout<<"Displaying CLL\nSize of Circular Link List : "<<size<<"\n\n";
		for(temp=head;flg==0;temp=temp->next)
		{
			cout<<endl<<"Value : "<<temp->word<<endl;
			if(temp->next==head)
			{flg=1;}
		}
	}
	void even_sort()
	{
		node *temp;
		int flg=0,eve=0;
		for(temp=head;flg==0;temp=temp->next)
		{
			if(temp->word % 2 ==0)
			{
				eve++;
			}
			if(temp->next==head)
			{flg=1;}
		}
		if(eve==0 || eve == size)
		{
			cout<<"\nAlready Sorted.\n";
		}
		else
		{
			node *temp2;
			int i;
			int e;
		for(i=1;i<=size;i++)
		{
			flg=0;
		for(temp2=head;flg==0;temp2=temp2->next)
		{
			if((temp2->word % 2 ==1) && (temp2->next->word % 2 ==0))
			{
				e=temp2->word;
				temp2->word=temp2->next->word;
				temp2->next->word=e;
			}
			if(temp2->next->next==head)
			{flg=1;}		
		}
		}
	}
	}
	void swap_sort(int ind1,int ind2)
	{
		node *temp1;
		node *temp2=NULL,*temp3=NULL;
		int flg=1,count=1;
		if(ind2<ind1)
		{
			swap(ind2,ind1);
		}
		for(temp1=head;flg==1;temp1=temp1->next)
		{
			if(ind1==1 && ind2-1==count)
			{
				temp2=head;
				temp3=temp1;
			}
			else
			{
				if(ind1-1==count)
				{
					temp2=temp1;
				}
				else if(ind2-1==count){
					temp3=temp1;
				}
			}
			count++;
			if(temp1->next==head)
			{
				flg=0;
			}
		}
		if(ind1==1)
		{
			if(ind1==1 && ind2==size)
			{
				//temp1=temp3->next->next;
				temp3->next->next=temp2->next;
				temp1=temp3->next;
				temp3->next=temp2;
				temp2->next=temp1;
				temp1=tail;
				tail=head;
				head=temp1;
			}
			else
			{
				temp1=temp2;
				temp2=temp3->next;
				temp3->next=temp1;
				temp1=temp2->next;
				temp2->next=temp3->next->next;
				temp3->next->next=temp1;
				head=temp2;	
				tail->next=head;		
			}
		}
		else
		{
			if(ind2==size)
			{
				temp1=temp2->next;
				tail=temp1;
				temp2->next=temp3->next;
				temp3->next=temp1;
				temp1=temp2->next->next;
				temp2->next->next=temp3->next->next;
				temp3->next->next=temp1;
				tail->next=head;
			}
			else
			{
				temp1=temp2->next;
				temp2->next=temp3->next;
				temp3->next=temp1;
				temp1=temp2->next->next;
				temp2->next->next=temp3->next->next;
				temp3->next->next=temp1;
			}
		}
	}
};