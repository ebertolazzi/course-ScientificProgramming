classdef stupid_class < handle

  properties (SetAccess = private, Hidden = true)
    %objectHandle;
    %call_delete;
    m_status;
  end

  methods
    function self = stupid_class()
      fprintf('pass from contructor method\n');
      self.m_status = 'zero';
      %obj.call_delete = true;
      %Spline1DMexWrapper( 'build', self.objectHandle, varargin{:} );
    end
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    function delete( self )
      fprintf('pass from delete method\n');

      %if self.call_delete
      %  Spline1DMexWrapper( 'delete', self.objectHandle );
      %end
      %self.objectHandle = 0;
    end
    %
    %
    %
    function print_status( self )
      fprintf('status = %s\n', self.m_status);
    end
    %
    %
    %
    function change_status( self, new_status )
      fprintf('change status\n');
      self.m_status = new_status;
    end

  end
end
