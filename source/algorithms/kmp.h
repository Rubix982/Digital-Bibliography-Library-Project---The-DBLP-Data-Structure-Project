#include <bits/stdc++.h>
using namespace std;

void create_lps_table(string, int []);
int KMP(int ips[], string pattern, string txt);
string txt_from_file(string);
string pat_from_file(string);

string txt_from_file(string && fileName) {

	string text, buffer;
	ifstream InFile( fileName.c_str() );
	
    if( InFile.is_open() ) {
		while(!InFile.eof()) {
		    getline(InFile,buffer);
		    text.append(buffer);
		}
	} else cout<<"\nText file Not Found\n";

	InFile.close();
    return text;
}

string pat_from_file(string && fileName) {
    
	string patt, buffer;
	ifstream InFile( fileName.c_str() );

	if( InFile.is_open() ) {
		while( !InFile.eof() ) {
		    getline(InFile,buffer);
		    patt.append(buffer);
		}
	} else cout<<"\nPattern file Not Found\n";
	
    InFile.close();
    return patt;
}

void create_lps_table(string pattern,int arr[]) {
	int i = 0,j = 1;
	while( j != pattern.length() ) {

        if( pattern[i] == pattern[j] ) {
            arr[j] = i + 1, i++, j++;
		} else if ( i == 0 ) j++;
		else i = arr[i-1];
        
	}
	
    cout << "\n\n";
	for( i = 0 ; i < pattern.length() ; i++ ) cout << arr[i] << "   ";
}

int KMP(int lps[],string pattern,string txt) {

	if(pattern==txt) {
        cout<<"\nEqual\n";
	    return 0;
    }

	create_lps_table(pattern,lps);
	
    int i = 0, j = -1, index = -5, flag = 0, check = 0;
	cout<<"\nChecking If the String matches...\n";
	
    while( i < txt.length() ) {
	
    	if(pattern[j+1]==txt[i])
		{
			check++, i++, j++;

			if( flag != 1 ) index = i;
			
            flag = 1;
			if( check == pattern.length() ) break;
		} else {
			
            if( j != -1 ) j = lps[j]-1;
			
            flag = 0, check = 0, index = -5, i++;
		}
	}

	if( index == -5 ) {
		cout<<"\nPattern Not Found!"<<endl;
		return -1;
	}

	return index - 1;
}