#include<bits/stdc++.h>
#include<fstream>
using namespace std;
int search(const char *a,string pat)
{
	string str;
	ifstream file(a);
	if(!file)
	cout<<"error";
	else{
		while(!file.eof())
		{
			string a;
			getline(file,a);
			str.append(a);
		}
	}
	file.close();
    int M = pat.length();  
    int N = str.length();
    int q=101;   //prime
	int d=256; 
    int i, j;  
    int p = 0;   
    int t = 0;   
    int h = 1;  
  
    for (i=0;i<M-1;i++)  
    {
	h=(h*d)%q;
	}  
  
    for(i=0;i<M;i++)  
    {  
        p=(d*p+pat[i])%q;  
        t=(d*t+str[i])%q;  
    }  
   
    for(i=0;i<=N-M;i++)  
    {  
        if(p==t)  
        {  
           for (j=0;j<M;j++)  
            {  
                if (str[i+j]!=pat[j])  
                    break;  
            }  
            if (j==M)  
               return i;
        }  
        if(i<N-M )  
        {  
        t=(d*(t-str[i]*h)+str[i+M])%q;  
  
            if(t<0)     //if t is negative;
            t=(t+q);  
        }  
    }  	

}
int main()
{
	int a=search("file1.txt","aba");
	cout<<a;
}
