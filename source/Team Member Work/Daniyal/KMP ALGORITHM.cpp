#include<Bits/stdc++.h>
using namespace std;
void create_lps_table(string,int []);
int KMP(int ips[],string pattern,string txt);
string txt_from_file(void);
string pat_from_file(void);
int main()
{
	string txt=txt_from_file();
	cout<<"\nData from file is : "<<txt<<endl;
	string pattern=pat_from_file();
	cout<<"\n\npattern to find in the above string : ";
	cout<<pattern;
	if(pattern.length()>=txt.length() && pattern!=txt)
	{
	cout<<"\nImpossible!\n";	
	return 0;}
	int lps[pattern.length()]={0};
	cout<<"\n\nPattern Found at index position : "<<KMP(lps,pattern,txt);
	return 0;
}
string txt_from_file(void)
{
	string text;
	fstream Infile;
	Infile.open("Text.txt",ios::in);
	if(Infile.is_open())
	{
		string x;
		while(!Infile.eof())
		{
		getline(Infile,x);
		text.append(x);
		}
	}
	else
	{
		cout<<"\nTextFile Not Found\n";
	}
	Infile.close();
	return text;
}
string pat_from_file(void)
{
	string patt;
	fstream infil;
	infil.open("Pattern.txt",ios::in);
	if(infil.is_open())
	{
		string x;
		while(!infil.eof())
		{
		getline(infil,x);
		patt.append(x);
		}
	}
	else
	cout<<"\nPatternFile Not Found\n";
	return patt;
}
void create_lps_table(string pattern,int arr[])
{
	int x=pattern.length();
	int i=0,j=1;
	while(j!=x)
	{
		if(pattern[i]==pattern[j])
			{
				arr[j]=i+1;
				i++;
				j++;
			}
			else
			{
				if(i==0)
				{
					j++;
				}
				else
				{
					i=arr[i-1];
				}
			}
	}
	cout<<endl<<endl;
	for(i=0;i<x;i++)
	{
		cout<<arr[i]<<"   ";
	}
}
int KMP(int lps[],string pattern,string txt)
{
	int x=txt.length();
	if(pattern==txt)
	{cout<<"\nEqual\n";
	return 0;}
	create_lps_table(pattern,lps);
	int i=0,j=-1;
	int ind=-5,flg=0;
	int check=0;
	cout<<"\nChecking If the String matches...\n";
	while(i<x)
	{
		if(pattern[j+1]==txt[i])
		{
			check++;
			i++;
			j++;
			if(flg!=1)
			ind=i;
			flg=1;
			if(check==pattern.length())
			{
				break;
			}
		}
		else
		{
			if(j!=-1)
			j=lps[j]-1;
			flg=0;
			check=0;
			ind=-5;
			i++;
		}
	}
	if(ind==-5)
	{
		cout<<"\nPattern Not Found!"<<endl;
		exit(1);
	}
	return (ind-1);
}
