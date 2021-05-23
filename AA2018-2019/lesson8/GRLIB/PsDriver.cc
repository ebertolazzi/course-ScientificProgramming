#include "PsDriver.hh"
#include <cmath>
#include <iostream>

using namespace std ;

namespace Gr {

  static char const * ps_macros[] = {
      "/dl{2 mul} bind def",
      "/M {moveto} bind def",
      "/L {lineto} bind def",
      "/R {rmoveto} bind def",
      "/V {rlineto} bind def",
      "/TT {translate} bind def",
      "/RR {rotate} bind def",
      "/SS {scale} bind def",
      "/VV {gsave newpath 0 0 M (o) true charpath",
      "     flattenpath pathbbox grestore",
      "     exch pop exch pop exch pop} def",
      "/HH {dup stringwidth pop} def",
      "/showAT {/posy exch def /posx exch def gsave TT RR newpath 0 0 M",
      "         HH posx mul VV posy mul R show stroke grestore} def",
      "/LDshowAT {-1 -1 showAT} def",
      "/RDshowAT {0 -1 showAT} def", 
      "/CDshowAT {-0.5 -1 showAT} def",
      "/LCshowAT {-1 -0.5 showAT} def",
      "/RCshowAT {0 -0.5 showAT} def", 
      "/CCshowAT {-0.5 -0.5 showAT} def",
      "/LUshowAT {-1 0 showAT} def",
      "/RUshowAT {0 0 showAT} def", 
      "/CUshowAT {-0.5 0 showAT} def",
      "/SAVE {/cmtx matrix currentmatrix def} def",
      "/CHVIEW {/ty exch def /tx exch def /dy exch def /dx exch def /ndy {dy neg} def",
      "         SAVE [dx dy ndy dx tx ty] concat} def",
      "/RESTORE {cmtx setmatrix} def",
      "/ELL {gsave SAVE TT SS newpath 0 0 1 0 360 arc RESTORE closepath stroke grestore} def",
      "/ELLF{gsave SAVE TT SS newpath 0 0 1 0 360 arc RESTORE closepath fill grestore} def",
      "/BOX {gsave SAVE TT SS newpath 0 0 M 1 0 L 1 1 L 0 1 L 0 0 L RESTORE closepath stroke grestore} def",
      "/BOXF{gsave SAVE TT SS newpath 0 0 M 1 0 L 1 1 L 0 1 L 0 0 L RESTORE closepath fill grestore} def",
      "/LINE{newpath M L stroke} def",
      "/ARPATH  {newpath 0 -0.025 M 0.8 -0.025 L 0.8 -0.1 L 1 0 L 0.8 0.1 L 0.8 0.025 L 0 0.025 L closepath} def",
      "/ARPATHB {newpath 0 0 M 0.8 0 L 0.8 -0.1 L 1 0 L 0.8 0.1 L 0.8 0 L closepath} def",
      "/ARS {CHVIEW newpath 0 0 M 1 0 L 0.8 0.025 M 0 1 L 0.8 -0.025 L",
      "      RESTORE stroke grestore} def",
      "/ARE  {gsave CHVIEW ARPATH RESTORE stroke grestore} def",
      "/ARF  {gsave CHVIEW ARPATH RESTORE fill grestore} def",
      "/ARSE {gsave CHVIEW ARPATHB RESTORE stroke grestore} def",
      "/ARSF {gsave CHVIEW ARPATHB RESTORE fill grestore} def",
      "/SE {gsave SAVE TT dup SS newpath -1 -1 M 1 -1 L 1 1 L -1 1 L RESTORE closepath stroke grestore} def", 
      "/SF {gsave SAVE TT dup SS newpath -1 -1 M 1 -1 L 1 1 L -1 1 L RESTORE closepath fill grestore} def", 
      "/DE {gsave SAVE TT dup SS newpath 0 -1 M 1 0 L 0 1 L -1 0 L RESTORE closepath stroke grestore} def", 
      "/DF {gsave SAVE TT dup SS newpath 0 -1 M 1 0 L 0 1 L -1 0 L RESTORE closepath fill grestore} def", 
      "/P  {gsave SAVE TT dup SS newpath 0 -1 M 0 1 L -1 0 M 1 0 L RESTORE stroke grestore} def", 
      "/C  {gsave SAVE TT dup SS newpath -1 -1 M 1 1 L -1 1 M 1 -1 L RESTORE stroke grestore} def", 
      "/SPATH {newpath 0 1 M -0.196 0.27 L -0.95 0.31 L -0.32 -0.103 L",
      "        -0.59 -0.81 L 0 -0.333333 L 0.59 -0.81 L 0.32 -0.103 L",
      "        0.95 0.31 L 0.196 0.27 L closepath} def",
      "/STARE { gsave SAVE TT dup SS SPATH RESTORE stroke grestore} def",
      "/STARF { gsave SAVE TT dup SS SPATH RESTORE fill grestore} def",
      "/TR   {/size exch def /Times-Roman findfont size scalefont setfont} def",
      "/TRB  {/size exch def /Times-Bold findfont size scalefont setfont} def",
      "/TRO  {/size exch def /Times-Italic findfont size scalefont setfont} def",
      "/TRBO {/size exch def /Times-BoldItalic findfont size scalefont setfont} def",
      "/HE   {/size exch def /Helvetica findfont size scalefont setfont} def",
      "/HEB  {/size exch def /Helvetica-Bold findfont size scalefont setfont} def",
      "/HEO  {/size exch def /Helvetica-Oblique findfont size scalefont setfont} def",
      "/HEBO {/size exch def /Helvetica-BoldOblique size findfont scalefont setfont} def",
      "/CO   {/size exch def /Courier findfont size scalefont setfont} def",
      "/COB  {/size exch def /Courier-Bold findfont size scalefont setfont} def",
      "/COO  {/size exch def /Courier-Oblique findfont size scalefont setfont} def",
      "/COBO {/size exch def /Courier-BoldOblique findfont size scalefont setfont} def",
      NULL } ;

  PsDriver::PsDriver( string const & of,
                      valueType      w,
                      valueType      h,
                      bool           bw,
                      bool           landscape )
  : width(w)
  , height(h)
  , blackandwhite(bw) {
    psf.open(of.c_str()) ;
    psf << "%%!PS-Adobe-2.0 EPSF-2.0\n"
        << "%%Creator: EasyGraph\n"
        << "%%Title: " << of << "\n"
        << "%%CreationDate: no date\n"
        << "%%%%BoundingBox: -1 -1 " << width+1 << " " << height+1 << "\n"
        << "%%%%EndComments\n"
        << "%%%%EndProlog\n" ;

    for ( char const **ppstr = ps_macros ; *ppstr != NULL ; ppstr++ )
      psf << *ppstr << endl ;

    psf << "24 TR" << endl
        << "gsave" << endl
        << (landscape?"-90 RR\n":"\n") ;
  }

  PsDriver::~PsDriver() {
    psf << "showpage grestore\n%%%%Trailer\n" ;
    psf.close() ;
  }

  void
  PsDriver::moveto(valueType x, valueType y) {
    psf << " " << x << " " << y << " M" ;
  }

  void
  PsDriver::rmove (valueType x, valueType y) {
    psf << " " << x << " " << y << " R" ;
  }

  void
  PsDriver::lineto(valueType x, valueType y) {
    psf << " " << x << " " << y << " L" ;
  }

  void
  PsDriver::rline (valueType x, valueType y) {
    psf << " " << x << " " << y << " V" ;
  }

  void
  PsDriver::arcto( valueType x1, valueType y1,
                   valueType x2, valueType y2,
                   valueType r) {
    psf << " " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << r << " arcto" ;
  }

  void
  PsDriver::translate(valueType tx, valueType ty) {
    psf << " " << tx << " " << ty << " TT" ;
  }

  void
  PsDriver::rotate(valueType angle) {
    psf << " " << angle << " RR" ;
  }

  void
  PsDriver::rotate(valueType dx, valueType dy) {
    psf << " " << dy << " " << dx << " atan RR" ;
  }

  void
  PsDriver::scale(valueType sx, valueType sy) {
    psf << " " << sx << " " << sy << " SS" ;
  }

  void
  PsDriver::newpath()	{
    psf << " newpath" ;
  }

  void
  PsDriver::closepath() {
    psf << " closepath" ;
  }

  void
  PsDriver::close_fill(bool c, bool f) {
    psf << (c?" closepath":"") << ( f? " fill" : " stroke") << endl ;
  }

  void PsDriver::stroke() {
    psf << " stroke" ;
  }

  void
  PsDriver::outstr(const char *s) {
    psf << " (" ;
    for ( const char *pc = s ; *pc != 0 ; ++pc ) {
      psf << ( ( *pc == '(' || *pc == ')' || *pc == '\\' ) ? "\\" : "" ) << *pc ;
    }
    psf	<< ") " ;
  }

  void
  PsDriver::window(valueType xm, valueType xM, valueType ym, valueType yM) {
    translate(xm,ym) ;
    scale(width/(xM-xm),height/(yM-ym)) ;
    psf << "\n" ;
  }

  void
  PsDriver::clip(valueType x1, valueType y1, valueType x2, valueType y2) {
    newpath() ;
    moveto(x1,y1) ;
    lineto(x1,y2) ;
    lineto(x2,y2) ;
    lineto(x2,y1) ;
    psf	<< " closepath clip\n" ;
  }

  void
  PsDriver::setFont(FontType f, FontFace fa, indexType size) {
    psf << " " << size ;
    switch (f) {
    case GR_TIMES:        psf << " TR" ; break ;
    case GR_HELVETICA:    psf << " HE" ; break ;
    case GR_COURIER:      psf << " CO" ; break ;
    }
      
    switch (fa) {
    case GR_NORMAL:       psf << "\n"   ; break ;
    case GR_BOLD:         psf << "B\n"  ; break ;
    case GR_OBLIQUE:      psf << "O\n"  ; break ;
    case GR_BOLDOBLIQUE:  psf << "BO\n" ; break ;
    }
  }

  static char const * align_show[] = {
    " LUshowAT", " CUshowAT", " RUshowAT",
    " LCshowAT", " CCshowAT", " RCshowAT",
    " LDshowAT", " CDshowAT", " RDshowAT"
  };

  void
  PsDriver::drawText( valueType      x,
                      valueType      y,
                      string const & s,
                      FontAlign      align,
                      valueType      angle ) {
    outstr(s.c_str()) ;
    psf << angle << " " << x << " " << y << align_show[align] << "\n" ;
  }

  void
  PsDriver::rgbColor(valueType r, valueType g, valueType b) {
    if (blackandwhite)
      psf << " " << (3*r+2*g+b)/6 << " setgray\n" ;
    else
      psf << " " << r << " " << g << " " << b << " setrgbcolor\n" ;
  }

  void
  PsDriver::hsbColor(valueType h, valueType s, valueType l) {
    if (blackandwhite)
      psf << " " << l << " setgray\n" ;
    else
      psf << " " << h << " " << s << " " << l << " sethsbcolor\n" ;
  }

  //  lcap, 0= butt, 1=round, 2=projecting square
  void
  PsDriver::setLineCap(indexType i) {
    psf << i << " setlinecap\n" ;
  }

  void
  PsDriver::setLineJoin(indexType i) {
    psf << i << " setlinejoin\n" ;
  }

  void
  PsDriver::setLineMiterLimit(valueType d) {
    psf << d << " setmiterlimit\n" ;
  }

  void
  PsDriver::setLineWidth(valueType w) {
    psf << w << " setlinewidth\n" ;
  }

  void
  PsDriver::setLineStyle( string const & s ) {
      psf << "[" << s << "] 0 setdash\n" ;
  }

  void
  PsDriver::setLineStyle(indexType i) {
    static char const * defline[] = {
      "", "1 dl 2 dl", "4 dl 2 dl", "2 dl 3 dl",
      "1 dl 1.5 dl", "5 dl 2 dl 1 dl 2 dl", "4 dl 3 dl 1 dl 3 dl",
      "2 dl 2 dl 2 dl 4 dl", "2 dl 2 dl 2 dl 2 dl 2 dl 4 dl",
      "2 dl 2 dl 2 dl 2 dl 2 dl 2 dl 2 dl 4 dl"} ;
    setLineStyle(defline[i<0 ? 0 : ( i>9 ? 9 : i)]) ;
  }

  void
  PsDriver::line(valueType x1, valueType y1, valueType x2, valueType y2) {
    psf << " " << x1 << " " << y1
        << " " << x2 << " " << y2
        << " LINE\n" ;
  }

  void
  PsDriver::box(valueType x1, valueType y1, valueType  x2, valueType  y2, bool fill) {
    psf << " " << x2-x1 << " " << y2-y1
        << " " << x1    << " " << y1
        << (fill?" BOXF\n":" BOX\n") ;
  }		

  void
  PsDriver::roundBox( valueType x1,
                      valueType y1,
                      valueType x2,
                      valueType y2,
                      valueType r,
                      bool fill ) {
    newpath() ;
    moveto(x2-r,y1) ;
    arcto(x2,y1,x2,y1+r,r) ;
    lineto(x2,y2-r) ;
    arcto(x2,y2,x2-r,y2,r) ;
    lineto(x1+r,y2) ;
    arcto(x1,y2,x1,y2-r,r) ;
    lineto(x1,y1+r) ;
    arcto(x1,y1,x1+r,y1,r) ;
    lineto(x2-r,y1) ;
    close_fill(true,fill) ;
  }

  void
  PsDriver::circle(valueType x, valueType y, valueType r, bool fill) {
    ellipse(x,y,r,r,fill) ;
  }

  void
  PsDriver::ellipse(valueType x, valueType y, valueType r1,  valueType r2, bool fill) {
    psf << " " << r1 << " " << r2
        << " " << x  << " " << y 
        << (fill? " ELLF\n" : " ELL\n") ;
  }

  void
  PsDriver::poly( indexType       n,
                  valueType const x[],
                  valueType const y[],
                  bool            close,
                  bool            fill) {
    newpath() ;
    moveto(x[0],y[0]) ;
    for (int i=1 ; i < n ; i++ )
      { lineto(x[i],y[i]) ; if ( (i%6) == 0 ) psf << "\n" ; }
    close_fill(close,fill) ;
  }

  void
  PsDriver::polyOffset( indexType       n,
                        valueType const x[],
                        valueType const y[],
                        valueType       dx,
                        valueType       dy,
                        bool            close,
                        bool            fill) {
    newpath() ;
    moveto(dx+x[0],dy+y[0]) ;
    for (int i=1 ; i < n ; i++ )
      { lineto(dx+x[i],dy+y[i]) ; if ( (i%6) == 0 ) psf << "\n" ; }
    close_fill(close,fill) ;
  }

  void
  PsDriver::arc( valueType cx,
                 valueType cy,
                 valueType r,
                 valueType t1,
                 valueType t2,
                 bool      fill ) {
    newpath() ;
    if ( fill) moveto(cx,cy) ;
    psf << " " << cx << " " << cy << " " << r
        << " " << t1 << " " << t2 << " arc" ;
    close_fill(fill,fill) ;
  }

  void
  PsDriver::bezier( valueType x1, valueType y1,
                    valueType x2, valueType y2,
                    valueType x3, valueType y3,
                    valueType x4, valueType y4)  {
    newpath() ;
    moveto(x1,y1) ;
    psf << " " << x2 << " " << y2
        << " " << x3 << " " << y3
        << " " << x4 << " " << y4
        << " curveto stroke"<< endl ;
  }

  static char const *artype[] = {
    " ARS", " ARE", " ARF", " ARSE", " ARSF"
  };

  void
  PsDriver::arrow( valueType xx,
                   valueType yy,
                   valueType dx,
                   valueType dy,
                   ArrowType at ) {
    psf << " " << dx << " " << dy
        << " " << xx << " " << yy
        << artype[at] << "\n" ;
  } ;

  void
  PsDriver::square(valueType x, valueType y, valueType r, bool fill) {
    psf << " " << r << " " << x << " " << y << (fill?" SF\n":" SE\n") ;
  }

  void
  PsDriver::diamond(valueType x, valueType y, valueType r, bool fill) {
    psf << " " << r << " " << x << " " << y << (fill?" DF\n":" DE\n") ;
  }

  void
  PsDriver::plus(valueType x, valueType y, valueType r) {
    psf << " " << r << " " << x << " " << y << " P\n" ;
  }

  void PsDriver::cross(valueType x, valueType y, valueType r) {
    psf << " " << r << " " << x << " " << y << " C\n" ;
  }

  void
  PsDriver::star(valueType x, valueType y, valueType r, bool fill) {
    psf << " " << r << " " << x << " " << y << (fill?" STARF\n":" STARE\n") ;
  }

}
