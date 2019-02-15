classdef CubicSegment < BaseHermite

  properties (SetAccess = protected, Hidden = true)
    P0; % initial point
    P1; % final point
    T0; % intial tangent
    T1; % final tangent
  end

  methods

    function self = CubicSegment()
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function delete(~)
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function copy( self, rhs )
      self.P0 = rhs.P0;
      self.P1 = rhs.P1;
      self.T0 = rhs.T0;
      self.T1 = rhs.T1;
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function [P0,P1,T0,T1] = get_data( self )
      P0 = self.P0;
      P1 = self.P1;
      T0 = self.T0;
      T1 = self.T1;
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function build( self, p0, p1, t0, t1 )
      %
      % Build a cubic given points and tangents
      %
      self.P0 = p0(:);
      self.P1 = p1(:);
      self.T0 = t0(:);
      self.T1 = t1(:);
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function p = eval( self, t )
      [h0,h1,l0,l1] = self.base( t );
      p = self.P0 * h0.' + ...
          self.P1 * h1.' + ...
          self.T0 * l0.' + ...
          self.T1 * l1.' ;
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function p_D = eval_D( self, t )
      [h0,h1,l0,l1] = self.base_D( t );
      p = self.P0 * h0.' + ...
          self.P1 * h1.' + ...
          self.T0 * l0.' + ...
          self.T1 * l1.' ;
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function p_DD = eval_DD( self, t )
      [h0,h1,l0,l1] = self.base_DD( t );
      p = self.P0 * h0.' + ...
          self.P1 * h1.' + ...
          self.T0 * l0.' + ...
          self.T1 * l1.' ;
    end
    %
    % - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function p_DDD = eval_DDD( self, t )
      [h0,h1,l0,l1] = self.base_DDD( t );
      p = self.P0 .* h0 + ...
          self.P1 .* h1 + ...
          self.T0 .* l0 + ...
          self.T1 .* l1 ;
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
