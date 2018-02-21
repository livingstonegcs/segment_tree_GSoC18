#define BOOST_TEST_MODULE segment_tree_test_cases
#include "segmentTree.hpp"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (suite1)

//defining new node_type
typedef struct node{
  long seg_sum, pref_sum, suff_sum, max_sum;
}node;

//defining create_node function
node make_node1(long a){
  node nw;
  nw.seg_sum=a;
  nw.pref_sum=nw.suff_sum=nw.max_sum=a;//max(0L, a);
  return nw;
}
//defining a new way of merging nodes
node merge_nodes1(node a, node b){
  node c;
  c.seg_sum = a.seg_sum+b.seg_sum;
  c.max_sum = max(a.suff_sum+b.pref_sum, max(a.max_sum, b.max_sum));
  c.pref_sum = max(a.seg_sum+b.pref_sum, a.pref_sum );
  c.suff_sum = max(a.suff_sum+b.seg_sum, b.suff_sum );
  return c;
}

BOOST_AUTO_TEST_CASE(maximum_sum_test){

  long arr[] = { 10, 8, -2, 0, -4, 1, 7 };
  vector<long> a_vec(arr, arr + 7);
  segment_tree::SegmentTree<node,long,make_node1,merge_nodes1> st1(a_vec, make_node1(0));

  //checking if rangeQuery() works properly for each possible range
  int sum_;
  //every possible range
  for(int c_i=0; c_i<7; c_i++){
    for(int c_j=c_i; c_j<7; c_j++){
      sum_=0;
      //every sub-range in range[c_i, c_j]
      for(int c_k=c_i; c_k<=c_j; c_k++){
        int temp=0;
        for(int c_l=c_k; c_l<=c_j; c_l++){
          temp+=a_vec[c_l];
          sum_=max(sum_, temp);
        }
      }
      BOOST_CHECK(st1.rangeQuery(c_i,c_j).max_sum == sum_);
    }
  }
  //checking if pointUpdate() works for each point
  for(int c_i=0;c_i<7;c_i++){
    st1.pointUpdate(c_i,c_i*2);
    BOOST_CHECK( st1.pointQuery(c_i).max_sum == (long)(c_i*2) );
    node nd=st1.pointQuery(c_i);
  }
}

BOOST_AUTO_TEST_CASE(range_sum_test){

  int arr[] = { 18, 17, 13, 19, 15, 11, 20 };
  vector<int> a_vec(arr, arr + 7);
  segment_tree::SegmentTree<int,int > st1(a_vec, 0);

  //checking if every leaf node is properly initialized and if pointQuery() is working
  for(int c_i=0;c_i<7;c_i++){
    BOOST_CHECK(st1.pointQuery(c_i) == a_vec[c_i]);
  }

  //checking if rangeQuery() works properly for each possible range
  int sum_=0;
  for(int c_i=0;c_i<7;c_i++){
    sum_=0;
    for(int c_j=c_i;c_j<7;c_j++){
      sum_+=a_vec[c_j];
      BOOST_CHECK(st1.rangeQuery(c_i,c_j) == sum_);
    }
  }

  //checking if pointUpdate() works for each point
  for(int c_i=0;c_i<7;c_i++){
    st1.pointUpdate(c_i,c_i*2);
    BOOST_CHECK( st1.pointQuery(c_i) == c_i*2 );
    //updating back to original data
    st1.pointUpdate(c_i, a_vec[c_i]);
  }

  //checking the effect of rangeUpdate() and its effect on rangeQuery()
  for(int c_i=0;c_i<7;c_i++){
    sum_=0;
    for(int c_j=c_i;c_j<7;c_j++){
      sum_=(c_i+c_j)*(c_j-c_i+1);
      st1.rangeUpdate(c_i,c_j,c_i+c_j);
      BOOST_CHECK(st1.rangeQuery(c_i,c_j) == sum_);
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()
