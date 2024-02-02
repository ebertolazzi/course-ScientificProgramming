#pragma once

#ifndef RECT_dot_HH
#define RECT_dot_HH

namespace GEOM {

  class rect {
    double m_min_x;
    double m_min_y;
    double m_max_x;
    double m_max_y;

  public:

    rect()
    : m_min_x(0)
    , m_min_y(0)
    , m_max_x(0)
    , m_max_y(0)
    {}

    rect(
      double min_x,
      double min_y,
      double max_x,
      double max_y
    )
    : m_min_x(min_x)
    , m_min_y(min_y)
    , m_max_x(max_x)
    , m_max_y(max_y)
    {}

    void
    setup(
      double min_x,
      double min_y,
      double max_x,
      double max_y
    ) {
      m_min_x = min_x;
      m_min_y = min_y;
      m_max_x = max_x;
      m_max_y = max_y;
    }

    void
    get_data(
      double & min_x,
      double & min_y,
      double & max_x,
      double & max_y
    ) {
      min_x = m_min_x;
      min_y = m_min_y;
      max_x = m_max_x;
      max_y = m_max_y;
    }

    ~rect() {}

    rect &
    operator = ( rect const & r ) {
      m_min_x = r.m_min_x;
      m_min_y = r.m_min_y;
      m_max_x = r.m_max_x;
      m_max_y = r.m_max_y;
      return *this;
    }

    rect &
    translate( double dx, double dy ) {
      m_min_x += dx;
      m_min_y += dy;
      m_max_x += dx;
      m_max_y += dy;
      return *this;
    }

    bool
    collide( rect const & r ) const {
      if ( r.m_min_x >= m_max_x ) return false;
      if ( r.m_max_x <= m_min_x ) return false;
      if ( r.m_min_y >= m_max_y ) return false;
      if ( r.m_max_y <= m_min_y ) return false;
      return true;
    }
  }; // class
} // namespace

#endif
