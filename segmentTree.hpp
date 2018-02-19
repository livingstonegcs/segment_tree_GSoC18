#include<vector>
using namespace std;

namespace segment_tree{
  //make_node() function creates a node of the type'type_stree' when provided with a value of type 'type_arr'
  template<typename type_stree, typename type_arr>
  type_stree make_node_val(type_arr val){
    return val;
  }

  //merge_nodes_add() function [by default adds two nodes]
  //this can be replaced with user defined funtion and passed into the constructor which returns
  //node of the type'type_stree' when provided with two 'type_stree' nodes
  template<typename type_stree>
  type_stree merge_nodes_add(type_stree l_part, type_stree r_part){
      return l_part+r_part;
  }

  template<typename type_stree,typename type_arr, type_stree (*make_node)(type_arr )=make_node_val, type_stree (*merge_nodes)(type_stree , type_stree )=merge_nodes_add>
  class SegmentTree{
    private:
      vector<type_arr> arr;
      vector<type_stree> stree;
      size_t size__;
      type_stree default_val;

      //build() function initializes the tree for the first time
      void build(int v, int tl, int tr){
        if(tl==tr){
          stree[v]=make_node(arr[tl]);
        }
        else{
          int tm=(tl+tr)>>1;
          build((2*v), tl, tm);
          build((2*v)+1, tm+1, tr);
          stree[v]=merge_nodes(stree[(2*v)], stree[(2*v)+1])  ;
        }
      }

      //This funtion updates a single point node or segment containing node stree[pos:pos]
      void pointUpdate(int v, int tl, int tr, int pos, type_arr val){
        if(tl==tr){
          stree[v]=make_node(val);
        //if we need to reflect changes in the original(referenced array inside the class) array as well then the below line has to be uncommented
        //arr[pos]=val;
        }
        else{
          int tm=(tl+tr)>>1;
          if(pos<=tm)
            pointUpdate((2*v), tl, tm, pos, val);
          else
            pointUpdate((2*v)+1, tm+1, tr, pos, val);
          stree[v]=merge_nodes(stree[(2*v)], stree[(2*v)+1]);
        }
      }
      //This function updates the values of nodes in particular range[l:r] or the segment containing node stree[l:r]
      void rangeUpdate(int v, int tl, int tr, int l, int r, type_arr val){
        if(l>r)
          return;
        //Nonlazy updation
        if(tl==tr){
          stree[v]=make_node(val);
          //if we need to reflect changes in the original(referenced array inside the class) array as well then the below line has to be uncommented
          //arr[tl]=val;
        }
        else{
          int tm=(tl+tr)>>1;
          rangeUpdate((2*v), tl, tm, l, min(tm, r), val);
          rangeUpdate((2*v)+1, tm+1, tr, max(l,tm+1), r, val);
          stree[v]=merge_nodes(stree[(2*v)], stree[(2*v)+1]);
        }
      }
      //This function queries for a range[l:r] based value in the segmentTree
      type_stree rangeQuery(int v, int tl, int tr, int l, int r){
        if(l>r)
          return make_node(default_val);
        if(tl==l && tr==r)
          return stree[v];
        int tm=(tl+tr)>>1;
        return merge_nodes(rangeQuery(2*v, tl, tm, l, min(tm, r)), rangeQuery((2*v)+1, tm+1, tr, max(tm+1, l), r) );
      }
      //This funtion initializes the arr , size__ , builds the segmentTree
      void initialize_values(vector<type_arr > &vec){
        arr=vec;
        size__ = (size_t)vec.size();
        stree.assign(4*size__, default_val);
        build(1, 0, size__-1);
      }
    public:
      //This function is pointUpdate() utility for the user
      void pointUpdate(int pos, type_arr val){
        pointUpdate(1, 0, size__-1, pos, val );
      }
      //This funtion is rangeUpdate() utility for the user
      void rangeUpdate(int l, int r, type_arr val){
        rangeUpdate(1, 0, size__-1, l, r, val );
      }
      //This funtion is rangeQuery() utility for the user
      type_stree rangeQuery(int l, int r){
        return rangeQuery(1, 0, size__-1, l, r);
      }
      //This is pointQuery() utility for the user
      type_stree pointQuery(int pos){
        return rangeQuery(pos, pos);
        /*if the changes would have been reflected changes in the original(referenced array inside the class) array as well
        then the below line could have been uncommented for O(1) access instead of above rangeQuery() call*/
        //return arr[pos];
      }
      //class constructor which only takes vector of values and builds a segmentTree
      SegmentTree(vector<type_arr > &vec){
        default_val=0;
        initialize_values(vec);
      }
      //constructor which takes vector of values and a default value of type_stree to initialize segmentTree
      SegmentTree(vector<type_arr> &vec, type_stree d_val){
        default_val=d_val;
        initialize_values(vec);
      }
  };
}
