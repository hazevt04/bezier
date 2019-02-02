
#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

using std::cout;
using std::endl;
using std::vector;
using std::time_t;

typedef vector<vector<int>> VoV;

int binomial( int n_val, int k_val ) {
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
}

double bezier_basis( int num, double t_val, int weights[] ) {
   double sum = 0.0;
   for ( int index = 0; index < num; index++ ) {
      sum += weights[index] * binomial(num,index) * 
         (pow((double)(1-t_val),(double)(num-index))) * 
         (pow(t_val,(double)index));

      cout << index << ": sum is " << sum << endl; 
   }
   return sum;
}

double bezier_basis_order_2( double t_val, int weights[] ) {
   double t_squared = t_val * t_val;
   double mt = 1 - t_val;
   double mt_squared = mt * mt;
   return mt_squared * weights[0] + 
      ( 2 * mt * t_val ) * weights[1] + 
      t_squared * weights[2];
}

double bezier_basis_order_3( double t_val, int weights[] ) {
   double t_squared = t_val * t_val;
   double t_cubed = t_squared * t_val;
   double mt = 1- t_val;
   double mt_squared = mt * mt;
   double mt_cubed = mt_squared * mt;
   return mt_cubed * weights[0] + 
      ( 2 * mt_squared * t_val ) * weights[1] + 
      ( 3 * mt * t_squared ) * weights[2] + 
      t_cubed * weights[3];
}

int main( int argc, char* argv[] ) {
   double result;

   int x_values[] = { 120, 35, 220, 220 };
   int y_values[] = { 160, 200, 260, 40 };

   double x_results[ 200 ];
   double y_results[ 200 ];
   
   clock_t start_time = clock();
   int scaled_index = 0;
   for ( double t_index = 0.0; t_index <= 1.000; t_index += 0.005 ) {
      x_results[ scaled_index ] = bezier_basis_order_3( t_index, x_values );
      cout << "bezier_basis_order_3(" << t_index << ", x ) is " 
         << x_results[ scaled_index ] << endl; 
      y_results[ scaled_index ] = bezier_basis_order_3( t_index, y_values );
      cout << "bezier_basis_order_3(" << t_index << ", y ) is " 
         << y_results[ scaled_index ] << endl; 
      scaled_index++;
   }
   cout << endl; 
   double duration = (double)( clock() - start_time )/
      (double)( CLOCKS_PER_SEC );
   
   cout << "Overal duration was " << duration 
      << " seconds." << endl;
   cout << endl;

   return 0;
}
