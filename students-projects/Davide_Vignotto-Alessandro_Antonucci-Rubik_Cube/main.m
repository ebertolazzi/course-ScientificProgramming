% =========================================================================
% Name   : main.m
% Authors: Alessandro Antonucci and Davide Vignotto
%          University of Trento
%
%          Shuffles, solves and plots a 3x3x3 Rubik's cube.
%          PhD course of Scientific Programming - prof. Bertolazzi.
%==========================================================================

% Initialize MATLAB
clc;
clear all;
close all;

% Folder tree
addpath('./RubiksCube');
addpath('./matlabmex');
pause(0.01);
clc;

%% Initialize the instance of the cube class

% Create a cube class instance
cube = RubiksCube();

%% Shuffle and solve the cube for n times

n = 1000;                 % Number of time the cube will be solved
s = 300;                  % Number of moves used to shuffle the cube each time
num_moves     = NaN(1,n); % Number of moves used to solve the cube each time 
num_moves_opt = NaN(1,n); % Optimized number of moves used to solve the cube each time 
par_l         = 40;       % Print parameter for the new-line (just for better visualization)

for i = 1:n

    % Shuffle randomly the cube with "s" moves
    % input:  (integer) number of moves used to shuffle 
    % output: (string)  the sequence of moves used to shuffle the cube 
    shuffle_seq = cube.rand_shuffle(s);

    % Solve the cube and optimize the solving sequence
    % input:   (none) 
    % outputs: (boolean) true if the solution is reached
    %          (integer) number of moves used to solve the cube 
    %          (string)  the sequence of moves used to solve the cube 
    [solved, nm, solve_seq] = cube.solve();

    % Check if cube is solved
    if solved == true
        
        % input:  (string) non optimized solving sequence
        % output: (string) optimized solving sequence (basically avoiding unuseful moves)
        opt_seq = cube.optimize_seq(solve_seq);
        
        % Saving useful variables 
        num_moves(i) = nm;
        num_moves_opt(i) = length(opt_seq);
        
    else % The cube is not solved
    
        fprintf('\tCube not solved!\n');
        
    end

end

% Histogram of the number  of moves used each time
histfit(num_moves);

% Print the statistics: average and standard deviation of the number of moves used to solve the cube
clc;
fprintf('\nAverage moves (+-std) over %d tests: %3.0f +-%3.0f ', n, mean(num_moves), std(num_moves));
fprintf('\nAverage opt moves difference (+-std) over %d tests: %3.0f +-%3.0f \n', n, mean(num_moves-num_moves_opt), std(num_moves-num_moves_opt));

% Print of the last sequence used to shuffle the cube
a = ceil(length(shuffle_seq)/par_l);
fprintf('\nLast sequence used to shuffle:\n');
for i = 1:a
    d = (i-1)*par_l+1;
    if i < a; fprintf('%s\n', shuffle_seq( d:d+par_l ));
    else;     fprintf('%s\n', shuffle_seq( d:end ));
    end
end

% Print of the last sequence used to solve the cube
a = ceil(length(solve_seq)/par_l);
fprintf('\nLast sequence used to solve:  \n');
for i = 1:a
    d = (i-1)*par_l+1;
    if i < a; fprintf('%s\n', solve_seq( d:d+par_l ));
    else;     fprintf('%s\n', solve_seq( d:end ));
    end
end

% Print of the last sequence used to solve the cube optimized
a = ceil(length(opt_seq)/par_l);
fprintf('\nLast solving sequence optimized:  \n');
for i = 1:a
    d = (i-1)*par_l+1;
    if i < a; fprintf('%s\n', opt_seq( d:d+par_l ));
    else;     fprintf('%s\n', opt_seq( d:end ));
    end
end

clear a d par_l n num_moves num_moves_opt i nm solved solve_seq opt_seq shuffle_seq;


%% Plot the cube in 3D and 2D while solving it

close all

% Bring the cube back to the solved state
cube.solve();

% Get the current (solved) state of the cube
% input:  (none)
% output: (int vector) the vector defining the state of the cube
solved_state    = cube.get_state();

% Shuffling the cube with "s" moves
shuffle_seq     = cube.rand_shuffle(s);

% Get the current (shuffle) state of the cube
shuffled_state  = cube.get_state();

% Solve the cube and optimize the solving sequence
[~,~,solve_seq] = cube.solve();
opt_seq         = cube.optimize_seq(solve_seq);

% Plot the solving sequence in time applied on the shuffle cube in 2D and 3D
% input:  (int vector) the vector defining the state of the cube
%         (string)     the sequence to be applied on the cube for the plot
cube.cplot(shuffled_state, solve_seq);

clear opt_seq shuffle_seq solve_seq shuffled_state solved_state ans
