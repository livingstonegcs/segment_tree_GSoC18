#include"segmentTree.hpp"
#include<bits/stdc++.h>
using namespace std;

int main(){

  //Segment Tree with integers as values and the task is default (Range Sum Query)
  cout<<"----------------Segment Tree with Range sum query-------------"<<endl;
  int arr[] = { 18, 17, 13, 19, 15, 11, 20 };
  vector<int> a_vec(arr, arr + 7);
  cout<<"Array source:\n";
  for(int i=0;i<7;i++)
    cout<<arr[i]<<" ";
  cout<<"\n\n";
  //construction
  segment_tree::SegmentTree<int,int > st1(a_vec, 0);
  //rangeQuery
  cout<<"rangeQuery(3,4)="<<st1.rangeQuery(3, 4)<<endl;
  //pointUpdate
  cout<<"pointUpdate(3,18)\n";
  st1.pointUpdate(3,18);
  //pointQuery
  cout<<"pointQuery(3)="<<st1.pointQuery(3)<<endl;
  //rangeUpdate()
  cout<<"rangeUpdate(3,4, 1)\n";
  st1.rangeUpdate(3,4, 1);
  //rangeQuery()
  cout<<"rangeQuery(3,4)="<<st1.rangeQuery(3,4)<<endl;

  return 0;
}
