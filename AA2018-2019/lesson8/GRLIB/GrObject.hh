#ifndef GR_OBJ_H
#define GR_OBJ_H

#include "GrDriver.hh"
#include <string>

namespace Gr {

  using namespace std ;

  typedef struct { valueType x, y ; } GrXY ;
  typedef struct { GrXY min, max  ; } Bbox ;

  /*
  //    ___  _     _           _   
  //   / _ \| |__ (_) ___  ___| |_ 
  //  | | | | '_ \| |/ _ \/ __| __|
  //  | |_| | |_) | |  __/ (__| |_ 
  //   \___/|_.__// |\___|\___|\__|
  //             |__/               
  */

  class Object {
  protected:
    Bbox bb ; // bounding box
    void setbb( valueType xm, valueType ym, valueType xM, valueType yM ) ;

  public:
    Object() ;
    Object( valueType _cx, valueType _cy, valueType _hdx, valueType _hdy ) ;

    virtual ~Object() {} ;
    virtual void draw(Driver *gr) = 0 ;
      
    valueType wx() const { return bb.max.x-bb.min.x ; }
    valueType wy() const { return bb.max.y-bb.min.y ; }
    valueType cx() const { return (bb.max.x+bb.min.x)/2 ; }
    valueType cy() const { return (bb.max.y+bb.min.y)/2 ; }
  } ;

  /*
  //   ____           _                    _      
  //  |  _ \ ___  ___| |_ __ _ _ __   __ _| | ___ 
  //  | |_) / _ \/ __| __/ _` | '_ \ / _` | |/ _ \
  //  |  _ <  __/ (__| || (_| | | | | (_| | |  __/
  //  |_| \_\___|\___|\__\__,_|_| |_|\__, |_|\___|
  //                                 |___/        
  */
  class Rectangle : public Object {
    bool filled ;
  public:
    Rectangle( valueType xm, valueType ym,
               valueType xM, valueType yM,
               bool e) ;
    virtual void draw(Driver *gr) ;
  } ;

  /*
  //   ____                       _ ____           _                    _      
  //  |  _ \ ___  _   _ _ __   __| |  _ \ ___  ___| |_ __ _ _ __   __ _| | ___ 
  //  | |_) / _ \| | | | '_ \ / _` | |_) / _ \/ __| __/ _` | '_ \ / _` | |/ _ \
  //  |  _ < (_) | |_| | | | | (_| |  _ <  __/ (__| || (_| | | | | (_| | |  __/
  //  |_| \_\___/ \__,_|_| |_|\__,_|_| \_\___|\___|\__\__,_|_| |_|\__, |_|\___|
  //                                                              |___/        
  */
  class RoundRectangle : public Object {
    bool      filled ;
    valueType ray ;
  public:
    RoundRectangle( valueType xm, valueType ym,
                    valueType xM, valueType yM,
                    valueType r,  bool e) ;		
    virtual void draw(Driver *gr) ;
  } ;

  /*
  //   _____ _ _ _                
  //  | ____| | (_)_ __  ___  ___ 
  //  |  _| | | | | '_ \/ __|/ _ \
  //  | |___| | | | |_) \__ \  __/
  //  |_____|_|_|_| .__/|___/\___|
  //              |_|             
  */
  class Ellipse : public Object {
    bool      filled ;
    valueType ray1, ray2 ;
  public:
    Ellipse( valueType x, valueType y,
             valueType r1, valueType r2,
             bool e) ;
    virtual void draw(Driver *gr) ;
  } ;

  /*
  //   ____                  _           _ 
  //  / ___| _   _ _ __ ___ | |__   ___ | |
  //  \___ \| | | | '_ ` _ \| '_ \ / _ \| |
  //   ___) | |_| | | | | | | |_) | (_) | |
  //  |____/ \__, |_| |_| |_|_.__/ \___/|_|
  //         |___/                         
  */
  class Symbol : public Object {
  public:
    Symbol(valueType _cx, valueType _cy, valueType _hdx, valueType _hdy) ;
    virtual ~Symbol() {} ;
    void move(valueType xx, valueType yy);
  } ;

  /*
  //   ____                             
  //  / ___|  __ _ _   _  __ _ _ __ ___ 
  //  \___ \ / _` | | | |/ _` | '__/ _ \
  //   ___) | (_| | |_| | (_| | | |  __/
  //  |____/ \__, |\__,_|\__,_|_|  \___|
  //            |_|                     
  */
  class Square : public Symbol {
    bool filled ;
  public:
    Square(valueType x, valueType y, valueType r, bool e) ;
    virtual void draw(Driver *gr) ;
  } ;

  /*
  //    ____ _          _      
  //   / ___(_)_ __ ___| | ___ 
  //  | |   | | '__/ __| |/ _ \
  //  | |___| | | | (__| |  __/
  //   \____|_|_|  \___|_|\___|
  */
  class Circle : public Symbol {
    valueType ray ;
    bool      filled ;
  public:
    Circle(valueType x, valueType y, valueType r, bool e) ;
    virtual void draw(Driver *gr) ;
  } ;

  /*
  //   _____                         ____ _          _      
  //  |  ___|   _ _ __  _ __  _   _ / ___(_)_ __ ___| | ___ 
  //  | |_ | | | | '_ \| '_ \| | | | |   | | '__/ __| |/ _ \
  //  |  _|| |_| | | | | | | | |_| | |___| | | | (__| |  __/
  //  |_|   \__,_|_| |_|_| |_|\__, |\____|_|_|  \___|_|\___|
  //                          |___/                         
  */
  class FunnyCircle : public Symbol {
    valueType ray ;
  public:
    FunnyCircle(valueType x, valueType y, valueType r) ;
    virtual void draw(Driver *gr) ;
  } ;

  /*
  //   ____  _                                 _ 
  //  |  _ \(_) __ _ _ __ ___   ___  _ __   __| |
  //  | | | | |/ _` | '_ ` _ \ / _ \| '_ \ / _` |
  //  | |_| | | (_| | | | | | | (_) | | | | (_| |
  //  |____/|_|\__,_|_| |_| |_|\___/|_| |_|\__,_|
  */
  class Diamond : public Symbol {
    bool filled ;
  public:
    Diamond( valueType _x, valueType _y, valueType _r, bool _e ) ;
    virtual void draw(Driver *gr) ;
  } ;

  /*
  //   ____  _             
  //  / ___|| |_ __ _ _ __ 
  //  \___ \| __/ _` | '__|
  //   ___) | || (_| | |   
  //  |____/ \__\__,_|_|   
  */
  class Star : public Symbol {
    bool filled ;
  public:
    Star(valueType _x, valueType _y, valueType _r, bool _e ) ;
    virtual void draw(Driver *gr) ;
  } ;

  /*
  //   ____  _           
  //  |  _ \| |_   _ ___ 
  //  | |_) | | | | / __|
  //  |  __/| | |_| \__ \
  //  |_|   |_|\__,_|___/
  */
  class Plus : public Symbol {
  public:
    Plus(valueType x, valueType y, valueType r) ;
    virtual void draw(Driver *gr) ;
  } ;

  /*
  //    ____                   
  //   / ___|_ __ ___  ___ ___ 
  //  | |   | '__/ _ \/ __/ __|
  //  | |___| | | (_) \__ \__ \
  //   \____|_|  \___/|___/___/
  */
  class Cross : public Symbol {
  public:
    Cross(valueType x, valueType y, valueType r) ;
    virtual void draw(Driver *gr) ;
  } ;

  /*
  //   ____  _            ____                   
  //  |  _ \| |_   _ ___ / ___|_ __ ___  ___ ___ 
  //  | |_) | | | | / __| |   | '__/ _ \/ __/ __|
  //  |  __/| | |_| \__ \ |___| | | (_) \__ \__ \
  //  |_|   |_|\__,_|___/\____|_|  \___/|___/___/
  */
  class PlusCross : public Symbol {
  public:
    PlusCross(valueType x, valueType y, valueType r) ;
    virtual void draw(Driver *gr) ;
  } ;

  /*
  //      _                           
  //     / \   _ __ _ __ _____      __
  //    / _ \ | '__| '__/ _ \ \ /\ / /
  //   / ___ \| |  | | | (_) \ V  V / 
  //  /_/   \_\_|  |_|  \___/ \_/\_/  
  */
  class Arrow : public Object {
    ArrowType artype ; 
    valueType   x, y, dx, dy ;
  public:
    Arrow( valueType _x,
             valueType _y,
             valueType _dx, 
             valueType _dy,
             ArrowType at = GR_ARROW_SIMPLE) ;
    virtual void draw(Driver *gr) ;
  } ;

  /*
  //   _____         _   
  //  |_   _|____  _| |_ 
  //    | |/ _ \ \/ / __|
  //    | |  __/>  <| |_ 
  //    |_|\___/_/\_\\__|
  */
  class Text : public Object {
    FontAlign align ;
    FontType  font ;
    FontFace  face ;
    indexType size ;
    valueType angle ;
    string	  str ;
  public:

    Text( valueType      x,
          valueType      y,
          string const & _str,
          FontType       _font,
          FontFace       _face,
          indexType      _size,
          FontAlign      _align,
          valueType      _angle = 0) ;

    void setText( string const & s ) { str = s ; }
    virtual void draw(Driver *gr) ;

  } ;

}

#endif
