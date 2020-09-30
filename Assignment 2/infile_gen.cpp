#include<fstream>
#include<bits/stdc++.h>
using namespace std;


int main(){

ofstream fout("infile");
srand(time(NULL));
// int n=1+int(rand()%100000);
int k=1+int(1+rand()%100);
int n=0;
// fout << n << " " << k << endl;

int bag[k];
for (int i=0;i<k;i++){
	bag[i]=1+int(rand()%1000);
	n+=bag[i];
}

fout << n << " " << k << endl;
for (int i=0;i<k;i++) fout << bag[i] << " ";

}