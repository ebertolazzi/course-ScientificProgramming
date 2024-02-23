classdef stupid_class < handle

  properties (SetAccess = private, Hidden = true)
    m_object_handle;
    m_call_delete;
  end

  methods
    function self = stupid_class()
      fprintf('pass from contructor method\n');
      self.m_call_delete   = true;
      % stupid_class_mex_wrapper instantiate a new class "stupid_class"
      % and return a "pointer" to the new class
      self.m_object_handle = stupid_class_mex_wrapper( 'new' );
    end
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    function delete( self )
      fprintf('pass from delete method\n');
      if self.m_call_delete
        % stupid_class_mex_wrapper delete the "stupid_class"
        % pointed by m_object_handle
        stupid_class_mex_wrapper( 'delete', self.m_object_handle );
      end
      self.m_call_delete   = false;
      self.m_object_handle = 0;
    end
    %
    %
    %
    function print_status( self )
      % stupid_class_mex_wrapper execute method print_status of the
      % class "stupid_class" pointed by m_object_handle
      msg = stupid_class_mex_wrapper( 'print_status', self.m_object_handle );
      fprintf( 'status = %s\n', msg );
    end
    %
    %
    %
    function change_status( self, new_status )
      fprintf('change status\n');
      % stupid_class_mex_wrapper execute method change_status of the
      % class "stupid_class" pointed by m_object_handle
      % with argument new_status
      stupid_class_mex_wrapper( 'change_status', self.m_object_handle, new_status );
    end

  end
end
