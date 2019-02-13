#ifndef GR_DRIVER_H
#define GR_DRIVER_H

#include <string>

namespace Gr {

  using namespace std;

  typedef double valueType;
  typedef int    indexType;

  typedef enum { GR_TIMES=0,
                 GR_HELVETICA,
                 GR_COURIER } FontType ;

  typedef enum { GR_NORMAL=0,
                 GR_BOLD,
                 GR_OBLIQUE,
                 GR_BOLDOBLIQUE } FontFace ;

  typedef enum { GR_ALIGN_UP_LEFT=0,
                 GR_ALIGN_UP_CENTER,
                 GR_ALIGN_UP_RIGHT,
                 GR_ALIGN_LEFT,
                 GR_ALIGN_CENTER,
                 GR_ALIGN_RIGHT,
                 GR_ALIGN_DOWN_LEFT,
                 GR_ALIGN_DOWN_CENTER,
                 GR_ALIGN_DOWN_RIGHT } FontAlign ;

  typedef enum { GR_ARROW_SIMPLE=0,
                 GR_ARROW_EMPTY,
                 GR_ARROW_FILL,
                 GR_ARROW_SIMPLE_EMPTY,
                 GR_ARROW_SIMPLE_FILL } ArrowType ;

  class RgbGolor {

    valueType r, g, b ;

  public:

    RgbGolor() ;
    RgbGolor( valueType rr, valueType gg, valueType bb ) ;

    void
    operator () ( valueType rr, 
                  valueType gg, 
                  valueType bb )
    { r = rr ; g = gg ; b = bb ; }

    valueType red()   const { return r ; }
    valueType green() const { return g ; }
    valueType blue()  const { return b ; }
  } ;

  #define GR_DRIVER_INTERFACE(PV) \
    virtual void window( valueType xm, \
                         valueType xM, \
                         valueType ym, \
                         valueType yM ) PV ; \
    \
    virtual void clip  ( valueType x1, \
                         valueType y1, \
                         valueType x2, \
                         valueType y2 ) PV ; \
    \
    virtual void setFont( FontType, FontFace, indexType size ) PV ; \
    \
    virtual void rgbColor( valueType r, valueType g, valueType b ) PV ; \
    virtual void hsbColor( valueType r, valueType g, valueType b ) PV ; \
    \
    virtual void setLineWidth( valueType w ) PV ; \
    virtual void setLineStyle( string const & s ) PV ; \
    virtual void setLineStyle( int s ) PV ; \
    virtual void line( valueType x1, \
                       valueType y1, \
                       valueType x2, \
                       valueType y2 ) PV ; \
    \
    virtual void box( valueType x1, \
                      valueType y1, \
                      valueType x2, \
                      valueType y2, \
                      bool fill = false) PV ; \
    \
    virtual void roundBox( valueType x1, \
                           valueType y1, \
                           valueType x2, \
                           valueType y2, \
                           valueType r, \
                           bool      fill = false) PV ; \
    \
    virtual void circle( valueType x, \
                         valueType y, \
                         valueType r, \
                         bool fill = false) PV ; \
    \
    virtual void ellipse( valueType x, \
                          valueType y, \
                          valueType r1, \
                          valueType r2, \
                          bool fill = false) PV ; \
    \
    virtual void poly( indexType        n,  \
                       valueType const x[], \
                       valueType const y[], \
                       bool close = false,  \
                       bool fill  = false) PV ; \
    \
    virtual void polyOffset( indexType       n,   \
                             valueType const x[], \
                             valueType const y[], \
                             valueType       dx    = 0, \
                             valueType       dy    = 0, \
                             bool            close = false, \
                             bool            fill  = false) PV ; \
    \
    virtual void bezier( valueType x1, valueType y1, \
                         valueType x2, valueType y2, \
                         valueType x3, valueType y3, \
                         valueType x4, valueType y4) PV ; \
    \
    virtual void arc( valueType cx, \
                      valueType cy, \
                      valueType r,  \
                      valueType t1, \
                      valueType t2, \
                      bool fill = false) PV ; \
    \
    virtual void drawText( valueType      x, \
                           valueType      y, \
                           string const & str, \
                           FontAlign      align, \
                           valueType      angle ) PV ; \
    \
    virtual void arrow( valueType   x, \
                        valueType   y, \
                        valueType   dx, \
                        valueType   dy, \
                        ArrowType at) ; \
    \
    virtual void square( valueType x, \
                         valueType y, \
                         valueType r, \
                         bool fill = false) ; \
    \
    virtual void diamond( valueType x, \
                          valueType y, \
                          valueType r, \
                          bool fill = false) ; \
    \
    virtual void plus( valueType x, \
                       valueType y, \
                       valueType r ) ; \
    \
    virtual void cross( valueType x, \
                        valueType y, \
                        valueType r ) ; \
    \
    virtual void star( valueType x, \
                       valueType y, \
                       valueType r, \
                       bool fill = false )

  class Driver {
  public:
    Driver() {} ;   
    ~Driver() {} ;
    
    GR_DRIVER_INTERFACE(=0);

    void rgbColor( RgbGolor const & c)
    { rgbColor(c.red(),c.green(),c.blue()) ; }
      
    void red()    { rgbColor(1,0,0) ; }
    void green()  { rgbColor(0,1,0) ; }
    void blue()   { rgbColor(0,0,1) ; }
    void yellow() { rgbColor(1,1,0) ; }
    void pink()   { rgbColor(1,0,1) ; }
    void cyan()   { rgbColor(0,1,1) ; }
    void white()  { rgbColor(0.9,0.9,0.9) ; }
    void black()  { rgbColor(0,0,0) ; }

  } ;
}

#endif
