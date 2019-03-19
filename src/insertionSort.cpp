/****************************************************************************
  FileName     [ insertionSort ]
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
static int base = 0;
static int accumulated = 0;
static AlgParser p;
static AlgTimer t;
static vector<string> insertionSort_text;
static vector<string>::iterator it;
static vector<int> insertionSort_index;
static vector<int>::iterator it_index;

//my funcition definition
//int accumulated_order(AlgParser& p,int i);
void insertionSort(AlgParser& p);
void set_vector(AlgParser& p);
void file_write(AlgParser& p,char* outputfilename);

int main(int argc,char *argv[]) {
   // Declare the functional objects
   p.Parse(argv[1]);
   t.Begin();
   cout << "##############################" << endl;
   cout << "1. Reading in the file..." << endl;
   set_vector(p);
   cout << "2. Processing insertion sort..." << endl;
   insertionSort(p);
   cout << "3. Write the data into the file \"" << argv[2] << "\""<< endl;
   file_write(p,argv[2]);
   cout << "The execution spends " << t.End() << " seconds" << endl;
   getchar();
   cout << "Processing complete!" << endl;
   cout << "##############################" << endl;
   return 0;
}

void set_vector(AlgParser& p){

   for( int i = 0 ; i < p.QueryTotalStringCount() ; i++ )
   {
      insertionSort_text.push_back(p.QueryString(i));
      insertionSort_index.push_back(i+1);
   }

}

void file_write(AlgParser& p,char *outputfilename){

   fstream myfile((string)outputfilename,ios::out);
   myfile << p.QueryTotalStringCount() << endl;
   for( int i = 0 ; i < p.QueryTotalStringCount() ; i++ )
   {
      myfile << insertionSort_text[i] << " " << insertionSort_index[i] << endl;
   }
}

void insertionSort(AlgParser& p){
   for (int i = 0; i < p.QueryTotalStringCount(); i++) {
      string now_pos = insertionSort_text[i];
      int now_index = i + 1;
      it = insertionSort_text.begin();
      it = it + i;
      it_index = insertionSort_index.begin();
      it_index = it_index + i;
      insertionSort_text.erase(it);
      insertionSort_index.erase(it_index);

      if(i != 0){
         for (int j = i-1; j >= 0 ; j--) {
            string point_pos = insertionSort_text[j];
            if((int)now_pos[0] < (int)point_pos[0]){
               it--;
               it_index--;
            }
         }
         insertionSort_text.insert(it,now_pos);
         insertionSort_index.insert(it_index,now_index);
      }
      else{
         insertionSort_text.insert(it,now_pos);
         insertionSort_index.insert(it_index,now_index);
      }
   }

}

/* garbage to be delete

int accumulated_order(AlgParser& p,int i){

   accumulated = (int)p.QueryWordOrder(i) + base;
   if( i+1 < p.QueryTotalStringCount() && (int)p.QueryWordOrder(i+1) == 1){
      base += (int)p.QueryWordOrder(i);
   }

   return accumulated;

}
*/
