classdef rect < handle

  properties (SetAccess = private, Hidden = true)
    min_x;
    min_y;
    max_x;
    max_y;
  end

  methods

    function self = rect( varargin )
      if nargin == 4
        self.min_x = varargin{1};
        self.min_y = varargin{2};
        self.max_x = varargin{3};
        self.max_y = varargin{4};
      else
        self.min_x = 0;
        self.min_y = 0;
        self.max_x = 0;
        self.max_y = 0;
      end
    end
    % --------------------------------------------------------------------
    %
    function delete(self)
    end
    % --------------------------------------------------------------------
    function copy( self, obj )
      if isa(obj,'rect')
        self.min_x = obj.min_x;
        self.min_y = obj.min_y;
        self.max_x = obj.max_x;
        self.max_y = obj.max_y;
      else
        error('bad object type for copy');
      end
    end
    % --------------------------------------------------------------------
    function translate( self, dx, dy )
      self.min_x = self.min_x+dx;
      self.min_y = self.min_y+dy;
      self.max_x = self.max_x+dx;
      self.max_y = self.max_y+dy;
    end
    % --------------------------------------------------------------------
    function res = collide( self, obj )
      res = false;
      if obj.min_x >= self.max_x; return; end;
      if obj.max_x <= self.min_x; return; end;
      if obj.min_y >= self.max_y; return; end;
      if obj.max_y <= self.min_y; return; end;
      res = true;
    end
    % --------------------------------------------------------------------
    function plot( self, varargin )
      % border of the rectangle
      xb = [ self.min_x, self.max_x, self.max_x, self.min_x, self.min_x];
      yb = [ self.min_y, self.min_y, self.max_y, self.max_y, self.min_y];
      plot( xb, yb, varargin{:} );
    end
  end
end
