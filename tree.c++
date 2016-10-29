#include "tree.h"

node::node( vector<int> &point )
{
  _axis = -1;
  _point = point;
}

node::node( int axis, int value, node *left, node *right )
{
  _axis = axis;
  _value = value;
  _left = left;
  _right = right;
}

bool cmp::operator()(vector<int> i, vector<int> j)
{
  return i[param] < j[param];
}

int sum::operator()(int i, vector<int> j)
{
  return i + j[param];;
}

// Takes in a vector of image points and returns the first node of a kd tree
node* kd_tree( vector< vector< int > > change_vec )
{
  int size = change_vec.size();
  
  if(size > 1)
  {
    int result[3];
    int avg_arr[3];
    int avg;

    for(int axis = 0; axis < 3; ++axis)
    {
      sort(change_vec.begin(), change_vec.end(), cmp(axis) );
      avg = accumulate( change_vec.begin(), change_vec.end(), 0, sum(axis) ) / size;
      avg_arr[ axis ] = (change_vec[size/2-1][axis] + change_vec[size/2][axis])/2;
      result[ axis ] = change_vec[size-1][axis] - change_vec[0][axis];
    }

    int value = INT_MIN;
    int axis;

    for(int i = 0; i < 3; ++i)
    {
      if( result[i] > value )
      {
        axis = i;
        value = result[i];
      }
    }
    sort(change_vec.begin(), change_vec.end(), cmp(axis));

    return new node( axis, avg_arr[axis], kd_tree( vector< vector<int> >(change_vec.begin(), change_vec.begin() + size/2 ) ), kd_tree( vector< vector<int> >(change_vec.begin() + size/2, change_vec.end()) ));
  }
  else
  {
    return new node( change_vec[0]);
  }
}

// Takes in point q, node n, point w, and distance d
// Returns nearest point to q
void nns(vector<int> &q, node &n, int &p, int &w)
{
  if( n._axis < 0 )
  {
    int _w = (q[0]-n._point[0])*(q[0]-n._point[0]) + (q[1]-n._point[1])*(q[1]-n._point[1]) + (q[2]-n._point[2])*(q[2]-n._point[2]);
    if( _w < w)
    {
      w = _w;
      p = n._point[3];
    }
  }
  else
  {
    if( q[n._axis] <= n._value )
    {
      nns(q, *n._left, p, w);
      if( q[n._axis] + sqrt(w) > n._value )
      {
        nns(q, *n._right, p, w);
      }
    }
    else
    {
      nns(q, *n._right, p, w);
      if( q[n._axis] - sqrt(w) <= n._value )
      {
        nns(q, *n._left, p, w);
      }
    }
  }
}