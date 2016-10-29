#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>

using namespace std;

class node
{
  public:
    vector<int> _point;
    int _axis, _value;
    node *_left, *_right;
    node( int value, vector<int> &point );
    node( int axis, int value, node *left, node *right );
};

class cmp
{
  int param;
  public:
    cmp( int _param ) : param(_param) {}
    bool operator()(vector<int> i, vector<int> j);
};

class sum
{
  int param;
  public:
    sum( int _param ) : param(_param) {}
    int operator()(int i, vector<int> j);
};

node* kd_tree( vector< pair< int, vector< int > > > change_vec );
void nns(vector<int> &q, node &n, int &p, int &w);