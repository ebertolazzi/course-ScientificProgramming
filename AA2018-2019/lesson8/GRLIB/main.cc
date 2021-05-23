#include <iostream>
#include <cmath>

#include "PsDriver.hh"
#include "GrGraph.hh"

Gr::Graph *G ;

int
main() {

  G = new Gr::Graph(10,10,490,400) ;
  G->setTitle("Titolo") ;
  G->setSubTitle("Sotto Titolo") ;
  G->setXlabel("X label") ;
  G->setYlabel("Y label") ;
  
  G->newCurve("PIPPO", new Gr::Diamond(0,0,5,true),  .5,3,0,0,0) ;
  G->newCurve("PLUTO", new Gr::Circle(0,0,5,false),   1,4,1,0,0) ;
  G->newCurve("Paperino", new Gr::Square(0,0,5,false),1,5,1,0,0) ;
  
  for ( int i=0 ; i <= 20 ; i++ ) {
    Gr::valueType x = 2*i/20.0-1 ;
    G->addToCurve(1,x,x) ;
    G->addToCurve(2,x,x*x) ;
    G->addToCurve(3,x,x*x*x) ;
  }

  G->setLegendPosition(7) ;
  G->xRange(-1,1) ;
  G->yRange(-1,1) ;
  G->setXstep(0.3) ;
  G->setYstep(0.3) ;
  G->setAxesVisible(false) ;

  //
  
  Gr::PsDriver * ps = new Gr::PsDriver("prova.ps",500,500,false,false) ;
  ps->window(0,500,0,500) ;
  ps->blue() ;
  G->draw(ps) ;
  delete ps ;

}