classdef CubicSegment2 < handle

  properties (SetAccess = protected, Hidden = true)
    % P0; % initial point
    % P1; % final point
    % T0; % intial tangent
    % T1; % final tangent
    objectHandle; % Store the pointer of the C++ class
  end

  methods

    function self = CubicSegment2()
      self.objectHandle = mex_CubicSegment2( 'new' );
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function delete(self)
      %% Destroy the C++ class instance
      if self.objectHandle ~= 0
        mex_CubicSegment2( 'delete', self.objectHandle );
      end
      self.objectHandle = 0; % avoid double destruction of object
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function [h0,h1,l0,l1] = base( self, tt )
      %
      % compute hermite bases at sampled points tt
      %
      % p(x) = p0 * h0(x) + p1 * h1(x) + dp0 * l0(x) + dp1 * l1(x)
      %
      % p(x) = cubic polynomial with
      % p(0) = p0, p(1) = p1, p'(0) = dp0, p'(1) = dp1
      %
      % [h0(0),h1(0),l0(0),l1(0)]     == [1,0,0,0]
      % [h0(1),h1(1),l0(1),l1(1)]     == [0,1,0,0]
      % [h0'(0),h1'(0),l0'(0),l1'(0)] == [0,0,1,0]
      % [h0'(1),h1'(1),l0'(1),l1'(1)] == [0,0,0,1]
      %
      [h0,h1,l0,l1] = mex_CubicSegment2( 'base', self.objectHandle, tt );
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function [dh0,dh1,dl0,dl1] = base_D( self, tt )
      [h0,h1,l0,l1] = mex_CubicSegment2( 'base_D', self.objectHandle, tt );
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function [ddh0,ddh1,ddl0,ddl1] = base_DD( self, tt )
      [h0,h1,l0,l1] = mex_CubicSegment2( 'base_DD', self.objectHandle, tt );
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function [dddh0,dddh1,dddl0,dddl1] = base_DDD( self, tt )
      [h0,h1,l0,l1] = mex_CubicSegment2( 'base_DDD', self.objectHandle, tt );
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function [P0,P1,T0,T1] = get_data( self )
      [P0,P1,T0,T1] = mex_CubicSegment2( 'get_data', self.objectHandle );
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function build( self, p0, p1, t0, t1 )
      %
      % Build a cubic given points and tangents
      %
      mex_CubicSegment2( 'build', self.objectHandle, p0, p1, t0, t1 );
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function p = eval( self, t )
      p = mex_CubicSegment2( 'eval', self.objectHandle, t );
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function p_D = eval_D( self, t )
      p_D = mex_CubicSegment2( 'eval_D', self.objectHandle, t );
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function p_DD = eval_DD( self, t )
      p_DD = mex_CubicSegment2( 'eval_DD', self.objectHandle, t );
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function p_DDD = eval_DDD( self, t )
      p_DDD = mex_CubicSegment2( 'eval_DDD', self.objectHandle, t );
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function plot( self, varargin )
      t = 0:1/400:1 ;
      p = self.eval(t) ;
      if size(p,1) == 2
        plot( p(1,:), p(2,:), varargin{:} );
      elseif size(p,1) == 3
        plot3( p(1,:), p(2,:), p(3,:), varargin{:} );
      end
    end

  end
end
