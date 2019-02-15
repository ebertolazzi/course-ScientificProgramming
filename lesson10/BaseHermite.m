classdef BaseHermite < handle

  methods

    % class constructor
    function self = BaseHermite()
    end

    % class destructor
    function delete(self)
    end

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
      t  = tt(:);
      bt = 1-t ;
      % output with separated columns
      h0 = (1+2*t).*bt.^2;
      h1 = (1+2*bt).*t.^2;
      l0 = t.*bt.^2;
      l1 = -t.^2.*bt;
    end

    function [dh0,dh1,dl0,dl1] = base_D( self, tt )
      t   = tt(:);
      bt  = 1-t;
      dh0 = -6*bt.*t;
      dh1 = 6*bt.*t;
      dl0 = bt.*(1-3*t);
      dl1 = t.*(1-3*bt);
    end

    function [ddh0,ddh1,ddl0,ddl1] = base_DD( self, tt )
      t  = tt(:);
      bt = 1-t;
      ddh0 = 12*t-6;
      ddh1 = 6-12*t;
      ddl0 = 6*t-4;
      ddl1 = 6*t-2;
    end

    function [dddh0,dddh1,dddl0,dddl1] = base_DDD( self, tt )
      t     = tt(:);
      % output with separated columns
      dddh0 = 12*ones(size(t));
      dddh1 = -12*ones(size(t));
      dddl0 = 6*ones(size(t));
      dddl1 = 6*ones(size(t));
    end

  end
end
