classdef rect < handle

  properties (SetAccess = private, Hidden = true)
    objectHandle; % Handle to the underlying C++ class instance
  end

  methods

    function self = rect( varargin )
      self.objectHandle = mexRectWrapper( 'new', varargin{:} );
    end
    % --------------------------------------------------------------------
    %
    function delete(self)
      mexRectWrapper( 'delete', self.objectHandle );
    end
    % --------------------------------------------------------------------
    function copy( self, obj )
      if isa(obj,'rect')
        mexRectWrapper( 'copy', self.objectHandle, obj.objectHandle );
      else
        error('bad object type for copy');
      end
    end
    % --------------------------------------------------------------------
    function translate( self, dx, dy )
      mexRectWrapper( 'translate', self.objectHandle, dx, dy );
    end
    % --------------------------------------------------------------------
    function res = collide( self, obj )
      if isa(obj,'rect')
        res = mexRectWrapper( 'collide', self.objectHandle, obj.objectHandle );
      else
        res = false;
      end
    end
    % --------------------------------------------------------------------
    function plot( self, varargin )
      [ min_x, min_y, max_x, max_y ] = mexRectWrapper( 'get_data', self.objectHandle );
      % border of the rectangle
      xb = [ min_x, max_x, max_x, min_x, min_x];
      yb = [ min_y, min_y, max_y, max_y, min_y];
      plot( xb, yb, varargin{:} );
    end
  end
end
