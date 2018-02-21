#include"segmentTree.hpp"
#include<bits/stdc++.h>
using namespace std;

string make_node1(string s){
  return s;
}
string merge_nodes1(string s1, string s2){
  return s1+"~"+s2;
}

int main(){

  //Segment with string concatenation
  cout<<"---------------String concatenation in ranges----------------"<<endl;
  string s_arr[] = { "live", "code", "eat", "repeat", "develop"};
  string val="";
  vector<string> s_vec(s_arr, s_arr+5);
	segment_tree::SegmentTree<string , string, make_node1, merge_nodes1> st2(s_vec ,val);

  cout<<"The string source array:\n";
  for(int i=0;i<5;i++)
  cout<<s_arr[i]<<", ";
  cout<<"\n\n";
  //rangeQuery
  cout<<"rangeQuery(3,4)="<<st2.rangeQuery(3, 4)<<endl;
  //pointUpdate
  cout<<"pointUpdate(3, \"play\")\n";
  st2.pointUpdate(3, "play");
  //pointQuery
  cout<<"pointQuery(3)="<<st2.pointQuery(3)<<endl;
  //rangeUpdate()
  cout<<"rangeUpdate(3,4, \"code\")\n";
  st2.rangeUpdate(3,4, "code");
  //rangeQuery()
  cout<<"rangeQuery(3,4)="<<st2.rangeQuery(3,4)<<endl;

  return 0;
}
