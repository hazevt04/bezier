
#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

typedef vector<vector<int>> VoV;

int binomial( int n_val, int k_val ) {
#if(0)
   VoV lut{
      {1}, 
      {1,1}, 
      {1,2,1},
      {1,3,3,1}, 
      {1,4,6,4,1}, 
      {1,5,10,10,5,1}, 
      {1,6,15,20,15,6,1}
   };
#endif
   VoV lut;
   while( n_val >= lut.size() ) {
      int lut_size = lut.size() ;
      vector<int> next_row(lut_size+1);
      next_row[0] = 1;
      int prev_size = lut_size - 1;
      for ( int index = 1; index < lut_size; index++ ) {
         next_row[index] = lut[prev_size][index-1] + 
            lut[prev_size][index];
      }
      next_row[lut_size] = 1;
      lut.push_back(next_row);
   }
   return lut[n_val][k_val];
#if(0)
   int const lookup_table[7] = {  
      {1}, 
      {1,1}, 
      {1,2,1},
      {1,3,3,1}, 
      {1,4,6,4,1}, 
      {1,5,10,10,5,1}, 
      {1,6,15,20,15,6,1}
   }; 
   while( n_val >= lookup_table.length ) {
      int s_size = lookup_table.length;
      nextRow = new array(s_size+1);
      nextRow[0] = 1;
      int prev = s_size - 1;
      for(int index = 1; index < s_size; index++) {
         nextRow[index] = lookup_table[prev][index-1] + 
            lookup_table[prev][index];
      }
      nextRow[s_size] = 1;
      lookup_table.add(nextRow);
   }
  return lookup_table[n_val][k_val]; 
#endif
}

// TODO : Switch to memoized factorial
int factorial( int num ) {
   int result = 1;
   for ( int index = 1; index <= num; index++ ) {
      result = result * index;
   }
   return result;
}

double bezier( int num, double t ) {
   double sum = 0.0;
   int num_fact = factorial( num );
   for ( int index = 0; index < num; index++ ) {
      // TODO : Switch to memoized factorial
      int index_fact = factorial( index );
      int other_fact = factorial( num - index );
      int temp_fact = index_fact * other_fact;
      
      sum += (num_fact/temp_fact) * (pow((double)(1-t),(double)(num-index))) * (pow(t,(double)index));
      //cout << index << ": sum is " << sum << endl; 
   }
   return sum;
}


int main( int argc, char* argv[] ) {
   
   int n_val;
   if ( argc> 1 ) {
      n_val = std::stoi(argv[1],nullptr);
   } else {
      n_val = 1;
   }

   for ( int k_val = 0; k_val <= n_val; k_val++ ) {
      int result = binomial( n_val, k_val );
      cout << "binomial(" << n_val << "," << k_val << ") is " 
         << result << "." << endl;
   }
   cout << endl;


#if(0)
   for ( double t_index = 0.0; t_index <= 1.000; t_index += 0.005 ) {
      double result = bezier( 3, t_index );
      cout << "bezier(3," << t_index << " is " << result << endl; 
   }

   double result[10][2000];
   
   for ( double index = 0.0; index <= 1.000; index += 0.005 ) {
      int index_adjusted = (index)/0.005;
      cout << "Index adjusted is " << index_adjusted << endl;
      result[0][index_adjusted] = 1;
      result[1][index_adjusted] = (1-index);
      result[2][index_adjusted] = index;
      result[3][index_adjusted] = (1-index)*(1-index);
      result[4][index_adjusted] = 2*(1-index)*index;
      result[5][index_adjusted] = index*index;
      result[6][index_adjusted] = (1-index)*(1-index)*(1-index);
      result[7][index_adjusted] = 3*(1-index)*(1-index)*index;
      result[8][index_adjusted] = 3*(1-index)*index*index;
      result[9][index_adjusted] = index*index*index;
   }
   
   for (int outer_index=0; outer_index < 10; outer_index++) {
      for(int inner_index=0; inner_index < 200; inner_index++) {
         cout << "Result[" << outer_index << "][" << inner_index << "]: " 
               << result[outer_index][inner_index] << endl;
      }
   }
#endif
   return 0;
}
