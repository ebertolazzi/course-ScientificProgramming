#ifndef GR_GRAPH_H
#define GR_GRAPH_H

#include "GrObject.hh"
#include <list>
#include <vector>

namespace Gr {

  using namespace std ;

  typedef struct { valueType xvalue, yvalue ; } Point2D ;

  typedef struct {
    string         name ;
    list<Point2D>  pnts ;
    RgbGolor       color ;
    Symbol *       symbol ;
    valueType      width ;
    indexType      lineStyle ;
  } GraphItem ;

  typedef struct {
    FontType  font ;
    FontFace  face ;
    indexType size ;
    indexType position ;
  } Legend ;

  class Graph : public Object {
    bool		drawAxes, drawGrid ;

    Text		*Title, *subTitle, *xLabel, *yLabel ;
    Legend      legend ;

    valueType	title_space, subtitle_space, label_space, item_sep ;
    
    Bbox        gbb, gc ;
    GrXY		step ;
    string		fmtx, fmty ;
        
    vector<GraphItem> items ;
    
    bool		xlog, ylog ;
    GrXY		tras, scale ;
    valueType X(valueType x) { return (x+tras.x)*scale.x ; }
    valueType Y(valueType y) { return (y+tras.y)*scale.y ; }

  public:

    Graph(valueType x, valueType y, valueType dx, valueType dy) ;
    virtual ~Graph() ;
    
    void setTitle    ( string const & s ) ;
    void setSubTitle ( string const & s ) ;
    void setXlabel   ( string const & s ) ;
    void setYlabel   ( string const & s ) ;
    
    void xRange(valueType _xmin, valueType _xmax) ;
    void yRange(valueType _ymin, valueType _ymax) ;

    void setXstep(valueType _xstep) { step.x = _xstep ; }
    void setYstep(valueType _ystep) { step.y = _ystep ; }
    
    void setFormatX(string const & s) { fmtx = s ; }
    void setFormatY(string const & s) { fmty = s ; }

    void setAxesLogarithmic(bool _xlog, bool _ylog) { xlog = _xlog ; ylog = _ylog ; }
    void setAxesVisible(bool _axes) { drawAxes = _axes ; }
    void setGridVisible(bool _grid) { drawGrid = _grid ; }
    
    void setLegendPosition(indexType pos) { legend.position = pos ; } ;
    
    void newCurve( string const & name,
                   Symbol *  sy,
                   valueType w,
                   indexType st,
                   valueType r,
                   valueType g,
                   valueType b ) ;

    void addPoint(valueType x, valueType y) ;
    void addToCurve(indexType i, valueType x, valueType y) ;
    
    void drawTics(Driver *gr) ;
    void drawCurves(Driver *gr) ;
    void drawLegend(Driver *gr) ;
    
    virtual void draw(Driver *gr) ;
  } ;
}

# endif
