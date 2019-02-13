#include "GrObject.hh"

namespace Gr {

  /*
  //    ___  _     _           _   
  //   / _ \| |__ (_) ___  ___| |_ 
  //  | | | | '_ \| |/ _ \/ __| __|
  //  | |_| | |_) | |  __/ (__| |_ 
  //   \___/|_.__// |\___|\___|\__|
  //             |__/               
  */

  Object::Object()
  {} ;

  Object::Object( valueType _cx,
                  valueType _cy,
                  valueType _hdx,
                  valueType _hdy)
  { setbb(_cx-_hdx,_cy-_hdy,_cx+_hdy,_cy+_hdy) ; }

  void
  Object::setbb( valueType xm,
                 valueType ym,
                 valueType xM,
                 valueType yM ) {
    bb.min.x = xm ;
    bb.max.x = xM ;
    bb.min.y = ym ;
    bb.max.y = yM ;
  }

  /*
  //   ____           _                    _      
  //  |  _ \ ___  ___| |_ __ _ _ __   __ _| | ___ 
  //  | |_) / _ \/ __| __/ _` | '_ \ / _` | |/ _ \
  //  |  _ <  __/ (__| || (_| | | | | (_| | |  __/
  //  |_| \_\___|\___|\__\__,_|_| |_|\__, |_|\___|
  //                                 |___/        
  */

  Rectangle::Rectangle( valueType xm,
                        valueType ym,
                        valueType xM,
                        valueType yM,
                        bool e )
  : filled(e)
  { setbb(xm, ym, xM, yM) ; }

  void
  Rectangle::draw(Driver *gr) {
    gr -> box(bb.min.x,bb.min.y,bb.max.x,bb.max.y,filled) ;
  } ;

  /*
  //   ____                       _ ____           _                    _      
  //  |  _ \ ___  _   _ _ __   __| |  _ \ ___  ___| |_ __ _ _ __   __ _| | ___ 
  //  | |_) / _ \| | | | '_ \ / _` | |_) / _ \/ __| __/ _` | '_ \ / _` | |/ _ \
  //  |  _ < (_) | |_| | | | | (_| |  _ <  __/ (__| || (_| | | | | (_| | |  __/
  //  |_| \_\___/ \__,_|_| |_|\__,_|_| \_\___|\___|\__\__,_|_| |_|\__, |_|\___|
  //                                                              |___/        
  */

  RoundRectangle::RoundRectangle( valueType xm,
                                  valueType ym,
                                  valueType xM,
                                  valueType yM,
                                  valueType r,
                                  bool e )
  : ray(r)
  , filled(e)
  { setbb(xm, ym, xM, yM) ; }

  void
  RoundRectangle::draw(Driver *gr) {
    gr -> roundBox(bb.min.x,bb.min.y,bb.max.x,bb.max.y,ray,filled) ;
  } ;

  /*
  //   _____ _ _ _                
  //  | ____| | (_)_ __  ___  ___ 
  //  |  _| | | | | '_ \/ __|/ _ \
  //  | |___| | | | |_) \__ \  __/
  //  |_____|_|_|_| .__/|___/\___|
  //              |_|             
  */

  Ellipse::Ellipse( valueType x,  valueType y,
                    valueType r1, valueType r2,
                    bool e )
  : Object(x,y,r1,r2)
  , ray1(r1)
  , ray2(r2)
  , filled(e)
  {}

  void
  Ellipse::draw(Driver *gr) {
    gr -> ellipse(cx(),cy(),ray1,ray2,filled) ;
  } ;

  /*
  //   ____                  _           _ 
  //  / ___| _   _ _ __ ___ | |__   ___ | |
  //  \___ \| | | | '_ ` _ \| '_ \ / _ \| |
  //   ___) | |_| | | | | | | |_) | (_) | |
  //  |____/ \__, |_| |_| |_|_.__/ \___/|_|
  //         |___/                         
  */

  Symbol::Symbol( valueType _cx,
                  valueType _cy,
                  valueType _hdx,
                  valueType _hdy )
  : Object(_cx,_cy,_hdx,_hdy)
  {}

  void
  Symbol::move( valueType xx, valueType yy ) {
    valueType tx = xx - cx(), ty = yy - cy() ;
    bb.min.x += tx ; bb.max.x += tx ;
    bb.min.y += ty ; bb.max.y += ty ;
  }

  /*
  //   ____                             
  //  / ___|  __ _ _   _  __ _ _ __ ___ 
  //  \___ \ / _` | | | |/ _` | '__/ _ \
  //   ___) | (_| | |_| | (_| | | |  __/
  //  |____/ \__, |\__,_|\__,_|_|  \___|
  //            |_|                     
  */

  Square::Square( valueType x,
                  valueType y,
                  valueType r,
                  bool e )
  : Symbol(x,y,r,r)
  , filled(e)
  {}

  void
  Square::draw(Driver *gr) {
    gr -> box(bb.min.x,bb.min.y,bb.max.x,bb.max.y,filled) ;
  }

  /*
  //    ____ _          _      
  //   / ___(_)_ __ ___| | ___ 
  //  | |   | | '__/ __| |/ _ \
  //  | |___| | | | (__| |  __/
  //   \____|_|_|  \___|_|\___|
  */

  Circle::Circle( valueType x,
                  valueType y,
                  valueType r,
                  bool e )
  : Symbol(x,y,r,r)
  , ray(r)
  , filled(e)
  {}

  void
  Circle::draw(Driver *gr) {
    gr -> circle(cx(),cy(),ray,filled) ;
  }

  /*
  //   _____                         ____ _          _      
  //  |  ___|   _ _ __  _ __  _   _ / ___(_)_ __ ___| | ___ 
  //  | |_ | | | | '_ \| '_ \| | | | |   | | '__/ __| |/ _ \
  //  |  _|| |_| | | | | | | | |_| | |___| | | | (__| |  __/
  //  |_|   \__,_|_| |_|_| |_|\__, |\____|_|_|  \___|_|\___|
  //                          |___/                         
  */

  FunnyCircle::FunnyCircle( valueType x,
                            valueType y,
                            valueType r )
  : Symbol(x,y,r,r)
  , ray(r)
  {}

  void
  FunnyCircle::draw(Driver *gr) {
    gr -> arc(cx(),cy(),ray,-45,45,true) ;
    gr -> arc(cx(),cy(),ray,90-45,90+45,false) ;
    gr -> arc(cx(),cy(),ray,180-45,180+45,true) ;
    gr -> arc(cx(),cy(),ray,270-45,270+45,false) ;
  }

  /*
  //   ____  _                                 _ 
  //  |  _ \(_) __ _ _ __ ___   ___  _ __   __| |
  //  | | | | |/ _` | '_ ` _ \ / _ \| '_ \ / _` |
  //  | |_| | | (_| | | | | | | (_) | | | | (_| |
  //  |____/|_|\__,_|_| |_| |_|\___/|_| |_|\__,_|
  */

  Diamond::Diamond( valueType _x,
                    valueType _y,
                    valueType _r,
                    bool _e )
  : Symbol(_x,_y,_r,_r)
  , filled(_e)
  {}

  void
  Diamond::draw(Driver *gr) {
    gr -> diamond(cx(),cy(),bb.max.x-cx(),filled) ;
  }

  /*
  //   ____  _             
  //  / ___|| |_ __ _ _ __ 
  //  \___ \| __/ _` | '__|
  //   ___) | || (_| | |   
  //  |____/ \__\__,_|_|   
  */

  Star::Star( valueType _x,
              valueType _y,
              valueType _r,
              bool _e )
  : Symbol(_x,_y,_r,_r)
  , filled(_e)
  {}

  void
  Star::draw(Driver *gr) {
    gr -> star(cx(),cy(),bb.max.x-cx(),filled) ;
  }

  /*
  //   ____  _           
  //  |  _ \| |_   _ ___ 
  //  | |_) | | | | / __|
  //  |  __/| | |_| \__ \
  //  |_|   |_|\__,_|___/
  */

  Plus::Plus( valueType x, valueType y, valueType r )
  : Symbol(x,y,r,r)
  {}

  void
  Plus::draw(Driver *gr) {
    gr -> plus(cx(),cy(),bb.max.x-cx()) ;
  }

  /*
  //    ____                   
  //   / ___|_ __ ___  ___ ___ 
  //  | |   | '__/ _ \/ __/ __|
  //  | |___| | | (_) \__ \__ \
  //   \____|_|  \___/|___/___/
  */

  Cross::Cross( valueType x, valueType y, valueType r )
  : Symbol(x,y,r,r)
  {}

  void
  Cross::draw(Driver *gr) {
    gr -> cross(cx(),cy(),bb.max.x-cx()) ;
  }

  /*
  //   ____  _            ____                   
  //  |  _ \| |_   _ ___ / ___|_ __ ___  ___ ___ 
  //  | |_) | | | | / __| |   | '__/ _ \/ __/ __|
  //  |  __/| | |_| \__ \ |___| | | (_) \__ \__ \
  //  |_|   |_|\__,_|___/\____|_|  \___/|___/___/
  */

  PlusCross::PlusCross( valueType x, valueType y, valueType r )
  : Symbol(x,y,r,r)
  {}

  void
  PlusCross::draw(Driver *gr) {				
    gr -> plus(cx(),cy(),bb.max.x-cx()) ;
    gr -> cross(cx(),cy(),bb.max.x-cx()) ;
  }

  /*
  //      _                           
  //     / \   _ __ _ __ _____      __
  //    / _ \ | '__| '__/ _ \ \ /\ / /
  //   / ___ \| |  | | | (_) \ V  V / 
  //  /_/   \_\_|  |_|  \___/ \_/\_/  
  */

  Arrow::Arrow( valueType   _x,
                valueType   _y,
                valueType   _dx,
                valueType   _dy,
                ArrowType at )
  : x(_x)
  , y(_y)
  , dx(_dx)
  , dy(_dy)
  , artype(at)
  , Gr::Object(_x+0.5*_dx, _y+0.5*_dy, 0.5*(_dx>0?_dx:-_dx), 0.5*(_dy>0?_dy:-_dy))
  {}

  void
  Arrow::draw(Driver *gr) {				
    gr->arrow(x,y,dx,dy,artype) ;
  }

  /*
  //   _____         _   
  //  |_   _|____  _| |_ 
  //    | |/ _ \ \/ / __|
  //    | |  __/>  <| |_ 
  //    |_|\___/_/\_\\__|
  */

  Text::Text( valueType      x,
              valueType      y,
              string const & _str,
              FontType       _font,
              FontFace       _face,
              indexType      _size,
              FontAlign      _align,
              valueType      _angle )
  : font(_font)
  , face(_face)
  , size(_size)
  , align(_align)
  , angle(_angle)
  {
    setText(_str) ;
    Gr::Object::setbb(x,y,x,y) ;
  }

  void
  Text::draw(Driver *gr) {
    gr -> setFont(font,face,size) ;
    gr -> drawText(bb.min.x,bb.min.y,str.c_str(),align,angle) ;
  }
}
