#include "GrDriver.hh"

namespace Gr {

  RgbGolor::RgbGolor()
  : r(0), g(0), b(0)
  {}

  RgbGolor::RgbGolor( valueType rr,
                      valueType gg,
                      valueType bb )
  : r(rr), g(gg), b(bb)
  {}

  static valueType xf[8] = { 0, 0.8, 0.8, 1, 0.8, 0.8, 0, 0.8} ;
  static valueType yf[8] = { -0.025, -0.025, -0.1, 0, 0.1, 0.025, 0.025, 0 } ;
              
  void
  Driver::arrow( valueType xx, 
                 valueType yy,
                 valueType dx,
                 valueType dy,
                 ArrowType at ) {
                  
    valueType x[8], y[8] ;

    for ( int i=0 ; i < 8 ; i++ ) {
      x[i] = xx+(dx*xf[i]-dy*yf[i]) ;
      y[i] = yy+(dy*xf[i]+dx*yf[i]) ;
    }
      
    switch (at) {
    case GR_ARROW_SIMPLE:
      line(xx,yy,x[3],y[3]) ;
      line(x[3],y[3],x[2],y[2]) ;
      line(x[3],y[3],x[4],y[4]) ;
      break ;
                                  
    case GR_ARROW_EMPTY:
      poly(7,x,y,true,false) ; 
      break ;
              
    case GR_ARROW_FILL:
      poly(7,x,y,true,true) ; 
      break ;
                                  
    case GR_ARROW_SIMPLE_EMPTY:
      line(xx,yy,x[7],y[7]) ;
      poly(3,x+2,y+2,true,false) ; 
      break ;
          
    case GR_ARROW_SIMPLE_FILL:
      line(xx,yy,x[7],y[7]) ;
      poly(3,x+2,y+2,true,true) ; 
      break ;
    }
  } ;

  void
  Driver::square( valueType x,
                  valueType y,
                  valueType r,
                  bool      fill ) {
    box(x-r,y-r,x+r,y+r,fill) ;
  } ;

  void
  Driver::diamond( valueType xx,
                   valueType yy,
                   valueType r,
                   bool      fill ) {
    valueType x[4], y[4] ;
    x[0] = xx   ; y[0] = yy-r ;
    x[1] = xx+r ; y[1] = yy   ;
    x[2] = xx   ; y[2] = yy+r ;
    x[3] = xx-r ; y[3] = yy   ;
    poly(4,x,y,true,fill) ; 
  }

  void
  Driver::plus( valueType x, valueType y, valueType r ) {
    line(x,y-r,x,y+r) ;
    line(x-r,y,x+r,y) ;
  }

  void
  Driver::cross( valueType x, valueType y, valueType r ) {
    line(x-r,y-r,x+r,y+r) ;
    line(x+r,y-r,x-r,y+r) ;
  }

  void
  Driver::star( valueType xx, valueType yy, valueType r, bool fill ) {
    valueType x[10], y[10] ;
    x[0] = xx             ; y[0] = yy + r          ;
    x[1] = xx - 0.196 * r ; y[1] = yy + 0.27 * r   ;
    x[2] = xx - 0.95 * r  ; y[2] = yy + 0.31 * r   ;
    x[3] = xx - 0.32 * r  ; y[3] = yy - 0.103 * r  ;
    x[4] = xx - 0.59 * r  ; y[4] = yy - 0.81 * r   ;
    x[5] = xx             ; y[5] = yy - 0.33333* r ;
    x[6] = xx + 0.59 * r  ; y[6] = yy - 0.81 * r   ;
    x[7] = xx + 0.32 * r  ; y[7] = yy - 0.103 * r  ;
    x[8] = xx + 0.95 * r  ; y[8] = yy + 0.31 * r   ; 
    x[9] = xx + 0.196 * r ; y[9] = yy + 0.27 * r   ;
    poly(10,x,y,true,fill) ; 
  }

}
