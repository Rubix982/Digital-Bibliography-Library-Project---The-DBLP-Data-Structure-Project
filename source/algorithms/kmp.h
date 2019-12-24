#ifndef KMP_H
#define KMP_H

#include "allHeadersForAlgorithms.h"
using namespace std;

void create_lps_table(string pattern, int arr[]);
int KMP(int ips[], string pattern, string txt);
string txt_from_file(string && fileName);
string pat_from_file(string && fileName);

#endif