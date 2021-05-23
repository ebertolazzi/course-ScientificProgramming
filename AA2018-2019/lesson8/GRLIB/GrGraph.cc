#include <cmath>
#include <iostream>
#include "GrGraph.hh"

namespace Gr {

  using namespace std ;

  indexType TITLE_SIZE    = 18 ;
  indexType SUBTITLE_SIZE = 14 ;
  indexType LABEL_SIZE    = 12 ;

  indexType LEGEND_SIZE   = 12 ;
  FontType  LEGEN_FONT    = GR_HELVETICA ;
  FontFace  LEGEND_FACE   = GR_NORMAL ;

  indexType TICS_LEN      = 3 ;
  indexType ITEM_SEP      = 3 ;

  valueType LINE_WIDTH    = 0.6 ;
  indexType LINE_STYLE    = 0 ;

  Graph::Graph(valueType x, valueType y, valueType x1, valueType y1)
  : Title(NULL)
  , subTitle(NULL)
  , xLabel(NULL)
  , yLabel(NULL)
  , xlog(false)
  , ylog(false)
  , drawAxes(false)
  , drawGrid(false)
  {
    setbb(x,y,x1,y1) ;
    title_space     = TITLE_SIZE+4 ;
    subtitle_space  = SUBTITLE_SIZE+4 ;
    label_space     = 2*LABEL_SIZE+4 ;
    item_sep        = ITEM_SEP ;
    legend.size     = LEGEND_SIZE ;
    legend.font     = LEGEN_FONT ;
    legend.face     = LEGEND_FACE ;
    legend.position = 0 ;
    
    gc.min.x = gbb.min.x = bb.min.x+label_space ;
    gc.min.y = gbb.min.y = bb.min.y+label_space ;
    gc.max.x = gbb.max.x = bb.max.x-label_space ;
    gc.max.y = gbb.max.y = bb.max.y-title_space-subtitle_space ;
    
    tras.x  = tras.y = 0 ;
    scale.x = scale.y = 1 ;
    step.x  = step.y = .2 ;
    fmtx = fmty = "%.2lg" ;
  } ;

  Graph::~Graph() {
    if ( Title    != NULL ) delete Title ;
    if ( subTitle != NULL ) delete subTitle ;
    if ( xLabel   != NULL ) delete xLabel ;
    if ( yLabel   != NULL ) delete yLabel ;
  } ;

  void
  Graph::setTitle( string const & s ) {
    if ( Title == NULL ) {
      Title = new Text(cx(),
                       bb.max.y-title_space/2,
                       s,
                       GR_HELVETICA,
                       GR_BOLD,
                       TITLE_SIZE,
                       GR_ALIGN_CENTER) ;
    } else {
      Title -> setText(s) ;
    }
  } ;

  void
  Graph::setSubTitle( string const & s ) {
    if ( subTitle == NULL ) {
      subTitle = new Text(cx(),
                          bb.max.y-title_space-subtitle_space/2,
                          s,
                          GR_HELVETICA,
                          GR_NORMAL,
                          SUBTITLE_SIZE,
                          GR_ALIGN_CENTER) ;
    } else {
      subTitle->setText(s) ;
    }
  }

  void
  Graph::setXlabel( string const & s ) {
    if ( xLabel == NULL ) {
      xLabel = new Text( cx(),
                         bb.min.y+LABEL_SIZE/2+1,
                         s,
                         GR_HELVETICA,
                         GR_NORMAL,
                         LABEL_SIZE,
                         GR_ALIGN_CENTER ) ;
    } else {
      xLabel -> setText(s) ;
    }
  }

  void
  Graph::setYlabel( string const & s ) {
    if ( yLabel == NULL ) {
      yLabel = new Text( bb.min.x+LABEL_SIZE/2+1,
                         cy(),
                         s,
                         GR_HELVETICA,
                         GR_NORMAL,
                         LABEL_SIZE,
                         GR_ALIGN_CENTER,90 ) ;
    } else {
      yLabel -> setText(s) ;
    }
  }

  void
  Graph::xRange( valueType _xmin, valueType _xmax ) {
    gc.min.x = _xmin ;
    gc.max.x = _xmax ;
    scale.x  = (gbb.max.x-gbb.min.x)/(_xmax-_xmin) ;
    tras.x   = - _xmin + gbb.min.x/scale.x ;
  }
          
  void
  Graph::yRange( valueType _ymin, valueType _ymax ) {
    gc.min.y = _ymin ;
    gc.max.y = _ymax ;
    scale.y  = (gbb.max.y-gbb.min.y)/(_ymax-_ymin) ;
    tras.y   = - _ymin + gbb.min.y/scale.y ;
  }

  void
  Graph::newCurve( string const & n,
                   Symbol       * sy,
                   valueType      w,
                   indexType      st,
                   valueType      r,
                   valueType      g,
                   valueType      b ) {
    GraphItem bf_item ;
      
    bf_item.name      = n ;
    bf_item.color     = RgbGolor(r,g,b) ;
    bf_item.symbol    = sy ;
    bf_item.width     = w ;
    bf_item.lineStyle = st ;
      
    items.push_back(bf_item) ;
  }

  void
  Graph::addToCurve( indexType i, valueType x, valueType y ) {
    Point2D bf ;
    bf.xvalue = x ;
    bf.yvalue = y ;
    items[i-1].pnts.push_back(bf) ;
  }

  void
  Graph::addPoint( valueType x, valueType y ) {
    addToCurve(items.size(),x,y) ;
  }

  void
  Graph::drawTics( Driver *gr ) {
    gr -> black() ;
    if ( drawAxes ) {
      gr->line(gbb.min.x,Y(0),gbb.max.x,Y(0)) ;
      gr->line(X(0),gbb.min.y,X(0),gbb.max.y) ;
    }

    string str ;

    if ( step.x > 0 ) {
      valueType ymi, yma ;
      if ( drawGrid ) {
        ymi = gbb.min.y ;
        yma = gbb.max.y ;
      } else {
        ymi = gbb.min.y-TICS_LEN ;
        yma = gbb.min.y ;
      }
      indexType is = gc.min.x/step.x - 0.1,
                ie = gc.max.x/step.x + 0.1 ;
      for ( int i = is ; i <= ie ; i++ ) {
        char msg[1000] ;
        valueType xx = i*step.x ;
        sprintf(msg,fmtx.c_str(),xx) ;
        xx = X(xx) ;
        gr -> line(xx,ymi,xx,yma) ;
        gr -> drawText(xx,ymi-0.6*LABEL_SIZE,msg,GR_ALIGN_CENTER,0) ;
      }
    }
    
    if ( step.y > 0 ) {
      valueType xmi, xma ;
      if ( drawGrid ) {
        xmi = gbb.min.x ;
        xma = gbb.max.x ;
      } else {
        xmi = gbb.min.x-TICS_LEN ;
        xma = gbb.min.x ;
      }
      indexType js = gc.min.y/step.y - 0.1,
                je = gc.max.y/step.y + 0.1 ; 
      for ( int j = js ; j <= je ; j++ ) {
        valueType yy = j*step.y ;
        char msg[1000];
        sprintf( msg, fmty.c_str(),yy) ;
        yy = Y(yy) ;
        gr -> line(xmi,yy,xma,yy) ;
        gr -> drawText(xmi-0.6*LABEL_SIZE,yy,msg,GR_ALIGN_CENTER,90) ;
      }
    }
  }

  void
  Graph::drawCurves( Driver *gr ) {

    gr -> clip(gbb.min.x,gbb.min.y,gbb.max.x,gbb.max.y) ;

    for ( vector<GraphItem>::iterator i = items . begin() ;
          i != items . end() ; 
          ++i ) {

      Symbol * s = i -> symbol ;

      if ( i -> pnts.size() == 0 ) break ;

      gr -> rgbColor     ( i -> color ) ;
      gr -> setLineWidth ( i -> width ) ;
      gr -> setLineStyle ( i -> lineStyle ) ;

      list<Point2D>::iterator p = i -> pnts . begin() ;
      valueType ox = X(p->xvalue) ;
      valueType oy = Y(p->yvalue) ;
      for ( ++p ; p != i -> pnts . end() ; ++p ) {
        valueType nx = X(p->xvalue) ;
        valueType ny = Y(p->yvalue) ;
        gr -> line(ox,oy,nx,ny) ;
        ox = nx ;
        oy = ny ;
      }

      gr->setLineWidth(LINE_WIDTH) ;
      gr->setLineStyle(LINE_STYLE) ;
      for ( p = i -> pnts . begin() ; p != i->pnts . end() ; ++p ) {
        s -> move(X(p->xvalue),Y(p->yvalue)) ;
        s -> draw(gr) ;
      }
    }
  }

  void
  Graph::drawLegend( Driver *gr ) {
  
    if ( legend.position < 1 || items.size() == 0 ) return ;
      
    gr -> setFont(legend.font, legend.face, legend.size) ;
    
    vector<GraphItem>::const_iterator i ;
      
    valueType msx=0, msy=0 ;
    for ( i = items . begin() ; i != items . end() ; ++i ) {
      Symbol *s = i -> symbol ;
      if ( s->wx() > msx ) msx = s->wx() ;
      if ( s->wy() > msy ) msy = s->wy() ;
    }
      
    // 1  2  3
    // 4  5  6
    // 7  8  9
    valueType xsy, y;
    bool on_left = true ;
    switch ( legend.position % 3 ) {
      case 1:
        xsy = gbb.min.x + msx + item_sep ;
        on_left = false ;
        break ;
      case 2:
        xsy = (gbb.min.x+gbb.max.x)/2 + msx + item_sep ;
        break ;
      default:
        xsy = gbb.max.x - msx - item_sep ;
        break ;
    }

    switch ( legend.position/3 ) {
      case 1:
        y = gbb.max.y+item_sep ;
        break ;
      case 2:
        y = (gbb.min.y+gbb.max.y+items.size()*(msy+item_sep))/2 ;
        break ;
      default:
        y = gbb.min.y+items.size()*(msy+item_sep)+item_sep ;
        break ;
    }

    y -= msy/2 ;
    for ( i = items . begin() ; i != items . end() ; ++i ) {

      gr -> rgbColor     ( i -> color ) ;
      gr -> setLineWidth ( i -> width ) ;
      gr -> setLineStyle ( i -> lineStyle ) ;

      Symbol *s = i -> symbol ;
          
      gr -> line(xsy-msx,y,xsy+msx,y) ;
      gr -> setLineWidth(LINE_WIDTH) ;
      gr -> setLineStyle(LINE_STYLE) ;

      s -> move(xsy,y) ;
      s -> draw(gr) ;

      if ( on_left )
        gr -> drawText(xsy-msx-item_sep,y,i->name,GR_ALIGN_LEFT,0) ;
      else
        gr -> drawText(xsy+msx+item_sep,y,i->name,GR_ALIGN_RIGHT,0) ;
      y -= item_sep+msy ;
    }
  }

  void
  Graph::draw( Driver *gr ) {
    if ( Title    != NULL ) Title    -> draw(gr) ;
    if ( subTitle != NULL ) subTitle -> draw(gr) ;
    if ( xLabel   != NULL ) xLabel   -> draw(gr) ;
    if ( yLabel   != NULL ) yLabel   -> draw(gr) ;

    gr->red() ;
    gr->box(bb.min.x,bb.min.y,bb.max.x,bb.max.y,false) ;
    gr->blue() ;
    gr->box(gbb.min.x,gbb.min.y,gbb.max.x,gbb.max.y,false) ;	

    drawTics(gr) ;
    drawCurves(gr) ;
    drawLegend(gr) ;
  }

}
