/****************************************************************************
  FileName     [ mergeSort ]
  PackageName  [ Sorting ]
  Author       [ Wan Cyuan Fan , NTUEE ]
****************************************************************************/
#include <cstdio>
#include <iostream>
#include <vector>
#include "parser.h"
#include <fstream>
#include "limits.h"

using namespace std;
// global variable
static AlgParser p;
static AlgTimer t;
static vector<string> mergeSort_L;
static vector<string> mergeSort_R;
static vector<int> mergeSort_L_index;
static vector<int> mergeSort_R_index;

static vector<string> mergeSort_text;
static vector<int> mergeSort_index;

//my funcition definition
//int accumulated_order(AlgParser& p,int i);
void mergeSort(AlgParser& p,int start,int end);
void merge(AlgParser& p,int start,int middle,int end);
void set_vector(AlgParser& p);
void file_write(AlgParser& p,char* outputfilename);

int main(int argc,char *argv[]) {
   // Declare the functional objects
   p.Parse(argv[1]);
   t.Begin();
   cout << "##############################" << endl;
   cout << "1. Reading in the file..." << endl;
   set_vector(p);
   cout << "2. Processing merge sort..." << endl;
   mergeSort(p,0,p.QueryTotalStringCount()-1);
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
      mergeSort_text.push_back(p.QueryString(i));
      mergeSort_index.push_back(i+1);
   }

}

void file_write(AlgParser& p,char *outputfilename){

   fstream myfile((string)outputfilename,ios::out);
   myfile << p.QueryTotalStringCount() << endl;
   for( int i = 0 ; i < p.QueryTotalStringCount() ; i++ )
   {
      myfile << mergeSort_text[i] << " " << mergeSort_index[i] << endl;
   }
}

void mergeSort(AlgParser& p,int start,int end){
   if(start < end){
      int middle = (start + end)/2;
      mergeSort(p,start,middle);
      mergeSort(p,middle + 1,end);
      merge(p,start,middle,end);
   }
}

void merge(AlgParser& p,int start,int middle,int end){
   int n_1 = middle - start + 1;
   int n_2 = end - middle;
   mergeSort_L.clear();
   mergeSort_R.clear();
   mergeSort_L_index.clear();
   mergeSort_R_index.clear();
   //set the new array L[] &R[]
   for (int i = 1; i <= n_1; i++) {
      mergeSort_L.push_back(mergeSort_text[start + i - 1]);
      mergeSort_L_index.push_back(mergeSort_index[start + i - 1]);
   }
   for (int i = 1; i <= n_2; i++){
      mergeSort_R.push_back(mergeSort_text[middle + i]);
      mergeSort_R_index.push_back(mergeSort_index[middle + i]);
   }
   /*
   for (int i = 0; i < mergeSort_L_index.size(); i++) {
      cout << mergeSort_L_index[i] << " ";
   }
   cout << endl;
   for (int i = 0; i < mergeSort_R_index.size(); i++) {
      cout << mergeSort_R_index[i] << " ";
   }
   cout << endl;
   */
   int i = 0,j = 0;
   for (int k = start; k <= end; k++) {
      if( i == n_1 || j == n_2){
         if (i == n_1){
            mergeSort_text[k] = mergeSort_R[j];
            mergeSort_index[k] = mergeSort_R_index[j];
            j++;
         }
         else if(j == n_2){
            mergeSort_text[k] = mergeSort_L[i];
            mergeSort_index[k] = mergeSort_L_index[i];
            i++;
         }
      }
      else{
         //cout << "  " << mergeSort_L[i] << (int)mergeSort_L[i][0]
         //<< " " << mergeSort_R[j] << (int)mergeSort_R[j][0] << endl;
         if ((int)mergeSort_L[i][0] <= (int)mergeSort_R[j][0]) {
            mergeSort_text[k] = mergeSort_L[i];
            mergeSort_index[k] = mergeSort_L_index[i];
            i++;
         }
         else if((int)mergeSort_R[j][0] < (int)mergeSort_L[i][0]){
            mergeSort_text[k] = mergeSort_R[j];
            mergeSort_index[k] = mergeSort_R_index[j];
            j++;
         }
      }
      //cout << i << j <<endl;
   }
   //cout << "my text : ";
   //for (int i = 0; i < mergeSort_text.size(); i++) {
   //   cout << mergeSort_text[i] << " ";
   //}
}
   /*
   for (int i = 0; i < p.QueryTotalStringCount(); i++) {
      string now_pos = mergeSort_text[i];
      int now_index = i + 1;
      it = mergeSort_text.begin();
      it = it + i;
      it_index = mergeSort_index.begin();
      it_index = it_index + i;
      mergeSort_text.erase(it);
      mergeSort_index.erase(it_index);

      if(i != 0){
         for (int j = i-1; j >= 0 ; j--) {
            string point_pos = mergeSort_text[j];
            if((int)now_pos[0] < (int)point_pos[0]){
               it--;
               it_index--;
            }
         }
         mergeSort_text.insert(it,now_pos);
         mergeSort_index.insert(it_index,now_index);
      }
      else{
         mergeSort_text.insert(it,now_pos);
         mergeSort_index.insert(it_index,now_index);
      }
   }
   */
