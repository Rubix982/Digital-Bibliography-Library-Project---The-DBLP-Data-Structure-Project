#include "RabinKarp.h"
using namespace std;

int rabinKarp(const char *a,string pat) {
	
    string str, buffer;
	ifstream file(a);
	
    if( !file.is_open() ) cout<<"error";
    else {

		while(!file.eof()) {
			getline(file, buffer);
			str.append(buffer);
		}
	}

	file.close();
    
    int M = pat.length(), N = str.length(), q = 101,
        p = 0, t = 0, h = 1;  

    for ( int i = 0 ; i < M - 1 ; i++ ) h = ( h * 256 ) % q;

    for ( int i = 0 ; i < M ; i++ ) {  
        p = ( 256 * p + pat[i] ) % q;  
        t = ( 256 * t + str[i] ) % q;  
    }  

    for ( int i = 0 ; i <= N - M ; i++ ) {  
        
        if( p == t ) {  
    
            int j = 0;
            for ( ; j < M ; j++ )   
                if (str[i+j]!=pat[j])  
                    break;  
    
            if ( j == M ) return i;
        }

        if( i < N - M ) {  
        
            t = ( 256 * ( t - str[i] * h ) + str[i + M]) % q;  
    
            // if t is negative
            if( t < 0 ) t += q;  
    
        }  
    }  	
}