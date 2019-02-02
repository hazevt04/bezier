#ifndef _BEZIERCURVE_H_
#define _BEZIERCURVE_H_

// Header File for BezierCurve Class

class BezierCurve {
   public:
      BezierCurve() {}
      ~BezierCurve() {}
      double n_order_calc( int num, double t_val, int weights[] );
      double second_order_calc( double t_val, int weights[] );
      double third_order_calc( double t_val, int weights[] );
   private:
      int binomial( int n_val, int k_val );
         
};




// end of header file for BezierCurve Class
#endif
