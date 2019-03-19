/****************************************************************************
  FileName     [ quickSort ]
  PackageName  [ Sorting ]
  Author       [ Wan Cyuan Fan , NTUEE ]
****************************************************************************/
#include <cstdio>
#include <iostream>
#include <vector>
#include "parser.h"
#include <fstream>

using namespace std;
// global variable
static AlgParser p;
static AlgTimer t;
static vector<string> quickSort_text;
static vector<string>::iterator it;
static vector<int> quickSort_index;
static vector<int>::iterator it_index;

//my funcition definition
//int accumulated_order(AlgParser& p,int i);
void quickSort(AlgParser& p,int index_p,int index_r);
int partition(int index_p,int index_r);

void set_vector(AlgParser& p);
void file_write(AlgParser& p,char* outputfilename);

int main(int argc,char *argv[]) {
   // Declare the functional objects
   p.Parse(argv[1]);
   t.Begin();
   cout << "##############################" << endl;
   cout << "1. Reading in the file..." << endl;
   set_vector(p);
   cout << "2. Processing quick sort..." << endl;
   quickSort(p,1,p.QueryTotalStringCount());
   cout << "3. Write the data into the file \"" << argv[2] << "\""<< endl;
   file_write(p,argv[2]);
   cout << "The execution spends " << t.End() << " seconds" << endl;
   getchar();
   cout << "Processing complete!" << endl;
   cout << "##############################" << endl;
   return 0;
}

void quickSort(AlgParser& p,int index_p,int index_r){
   if (index_p < index_r){
      int index_q = partition(index_p,index_r);
      quickSort(p,index_p,index_q);
      quickSort(p,index_q + 1,index_r);
   }
}

int partition(int index_p,int index_r){
   string x = quickSort_text[index_p - 1];
   int i = index_p - 2;
   int j = index_r;
   while(true){
      //cout << i << j << endl;
      do {
         j--;
         //cout << "j--" << endl;
      } while((int)quickSort_text[j][0] > (int)x[0]);
      do {
         i++;
         //cout << "i--" << endl;
      } while((int)quickSort_text[i][0] < (int)x[0]);
      if ( i < j) {
         string tmp = quickSort_text[i];
         int tmp_index = quickSort_index[i];
         quickSort_text[i] = quickSort_text[j];
         quickSort_index[i] = quickSort_index[j];
         quickSort_text[j] = tmp;
         quickSort_index[j] = tmp_index;
      }
      else{
         return j+1;
      }
   }
}

void set_vector(AlgParser& p){

   for( int i = 0 ; i < p.QueryTotalStringCount() ; i++ )
   {
      quickSort_text.push_back(p.QueryString(i));
      quickSort_index.push_back(i+1);
   }
}

void file_write(AlgParser& p,char *outputfilename){

   fstream myfile((string)outputfilename,ios::out);
   myfile << p.QueryTotalStringCount() << endl;
   for( int i = 0 ; i < p.QueryTotalStringCount() ; i++ )
   {
      myfile << quickSort_text[i] << " " << quickSort_index[i] << endl;
   }
}
