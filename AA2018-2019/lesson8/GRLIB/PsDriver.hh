#ifndef PSDRV_H
#define PSDRV_H

#include <fstream>
#include "GrDriver.hh"

namespace Gr {

  using namespace std ;

  class PsDriver : public Driver {

    ofstream  psf ;
    bool	  blackandwhite  ;
    valueType width, height ;

    void moveto(valueType x, valueType y) ;
    void rmove(valueType x, valueType y) ;
    void lineto(valueType x, valueType y) ;
    void rline(valueType x, valueType y) ;
    void outstr(const char str[]) ;
    void translate(valueType tx, valueType ty) ;
    void rotate(valueType angle) ;
    void rotate(valueType dx, valueType dy) ;
    void scale(valueType sx, valueType sy) ;
    void arcto(valueType x1, valueType y1, valueType x2, valueType y2, valueType r) ;
    void newpath() ;
    void closepath() ;
    void stroke() ;
    void close_fill(bool c, bool f) ;

  public:

    PsDriver( string const & of, valueType w, valueType h, bool bw, bool ls) ;	
    ~PsDriver() ;
      
    void setLineCap(indexType i) ;
    void setLineJoin(indexType i) ;
    void setLineMiterLimit(valueType d) ;

    GR_DRIVER_INTERFACE() ;

  } ;
}

#endif
