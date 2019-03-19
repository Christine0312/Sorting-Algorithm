/****************************************************************************
  FileName     [ heapSort ]
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
static vector<string> heapSort_text;
static vector<string>::iterator it;
static vector<int> heapSort_index;
static vector<int>::iterator it_index;

//my funcition definition
//int accumulated_order(AlgParser& p,int i);
void heapSort(AlgParser& p);
void max_heapify(int i,int size);
void build_max_heap();
void set_vector(AlgParser& p);
void file_write(AlgParser& p,char* outputfilename);
void max_heapify(int i);

int main(int argc,char *argv[]) {
   // Declare the functional objects
   p.Parse(argv[1]);
   t.Begin();
   cout << "##############################" << endl;
   cout << "1. Reading in the file..." << endl;
   set_vector(p);
   cout << "2. Processing heap sort..." << endl;
   heapSort(p);
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
      heapSort_text.push_back(p.QueryString(i));
      heapSort_index.push_back(i+1);
   }
}

void file_write(AlgParser& p,char *outputfilename){

   fstream myfile((string)outputfilename,ios::out);
   myfile << p.QueryTotalStringCount() << endl;
   for( int i = 0 ; i < p.QueryTotalStringCount() ; i++ )
   {
      myfile << heapSort_text[i] << " " << heapSort_index[i] << endl;
   }
}

void max_heapify(int i,int size){
   int left = i * 2;
   int right = i * 2 + 1;
   int heap_size = size;
   int largest;
   if(left <= heap_size && (int)heapSort_text[left-1][0] > (int)heapSort_text[i-1][0]){
      largest = left;
   }
   else{
      largest = i;
   }
   if(right <= heap_size && (int)heapSort_text[right-1][0] > (int)heapSort_text[largest-1][0]){
      largest = right;
   }
   if(largest != i){
      string tmp = heapSort_text[i-1];
      int tmp_index = heapSort_index[i-1];
      heapSort_text[i-1] = heapSort_text[largest-1];
      heapSort_index[i-1] = heapSort_index[largest-1];
      heapSort_text[largest-1] = tmp;
      heapSort_index[largest-1] = tmp_index;
      max_heapify(largest,heap_size);
   }
}
void build_max_heap(){
   int length = p.QueryTotalStringCount();
   for(int i = length/2 ; i >=1 ; i--){
      max_heapify(i,length);
   }
}

void heapSort(AlgParser& p){
   build_max_heap();
   /*cout << "max_heapify :" << endl;
   for (int i = 0; i < p.QueryTotalStringCount(); i++) {
      cout << heapSort_text[i] << " ";
   }
   cout << endl;*/
   int length = p.QueryTotalStringCount();
   for (int i = p.QueryTotalStringCount(); i >= 2; i--) {
      string tmp = heapSort_text[i-1];
      int tmp_index = heapSort_index[i-1];
      heapSort_text[i-1] = heapSort_text[0];
      heapSort_index[i-1] = heapSort_index[0];
      heapSort_text[0] = tmp;
      heapSort_index[0] = tmp_index;
      length --;
      /*cout << "my max_heapify :" << endl;
      for (int i = 0; i < p.QueryTotalStringCount(); i++) {
         cout << heapSort_text[i] << " ";
      }
      cout << endl;*/
      max_heapify(1,length);
   }
}
