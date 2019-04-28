classdef RubiksCube < handle
    
    properties (SetAccess = protected, Hidden = true)
        objectHandle; % Store the pointer of the C++ class
    end
    
    methods
        
        %==== CPP METHODS =================================================
        
        % Constructor: initialize the state
        function self = RubiksCube()
            self.objectHandle = mex_RubiksCubeClass('new');
        end
        
        % Destructor
        function delete(self)
            % Destroy the C++ class instance
            if self.objectHandle ~= 0
                mex_RubiksCubeClass('delete', self.objectHandle);
            end
            self.objectHandle = 0; % avoid double destruction of object
        end
        
        % Return the actual state of the cube
        function act_state = get_state(self)
            act_state = mex_RubiksCubeClass('get_state', self.objectHandle);
        end
        
        % Shuffle the cube by applying "n" random moves
        function [shuffle_seq] = rand_shuffle(self, n)
            shuffle_seq = mex_RubiksCubeClass('rand_shuffle', self.objectHandle, n);
        end
        
        % Apply a move or a sequence of moves
        function move(self, str)
            mex_RubiksCubeClass('move', self.objectHandle, str);
        end
        
        % Solve the cube
        function [is_solved, moves_num , solve_seq] = solve(self)
            [is_solved, moves_num , solve_seq ] = mex_RubiksCubeClass('solve', self.objectHandle);
        end
        
        % Print the state in 2D with integers as colors
        function print(self)
            mex_RubiksCubeClass('print', self.objectHandle);
        end
        
        % Main method
        function is_this_water(self)
            mex_RubiksCubeClass('is_this_water', self.objectHandle);
        end
        
        %==== MATLAB METHODS ==============================================
                
        % Plot the sequence of moves in 3D and 2D with colors
        function cplot(self, init_state, move_seq)
            
            % Optimize the solving sequence
            move_seq = self.optimize_seq(move_seq);
            
            % Figure options
            dim = get(0,'screensize');
            fig1 = figure(1);
            hx = dim(3)/5;
            hy = dim(4)/1.5;
            fig1.Position = [dim(3)/2 - hx/2 , dim(4)/2 - hy/2 , hx , hy];
            
            % Cycle over the moves in move_seq
            new_state = init_state;
            for move = move_seq  
                
                % Plot and move the cube 3D and 2D
                self.plot_move(new_state, move);
                
                % Update the state for next plot
                new_state = self.update_state(new_state, move);
                
            end
            
        end
        
        % Recursively optimize a sequence of moves
        opt_seq = optimize_seq(self, move_seq)
        
    end % end of public methods
    
    methods (Access = private)
        
        % Update the state given a certain move and the actual state
        up_state = update_state(self, act_state, move);
        
        % Plot and move the cube
        plot_move(self, new_state, move);
        
        % Plot the cube
        plot_state(self, state);
        
    end % end of private methods
    
end
