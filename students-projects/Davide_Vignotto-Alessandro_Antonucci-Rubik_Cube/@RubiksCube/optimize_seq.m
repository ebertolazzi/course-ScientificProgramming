% Recursively optimize a sequence of moves
function opt_seq = optimize_seq(self,move_seq)
initial_length = length(move_seq);
i = 1;

while i <= length(move_seq) % For all moves in the sequence...
    
    % Defining the opposite iof the i-th move
    move = move_seq(i);
    if isstrprop(move,'upper'); inv_move = lower(move);
    else; inv_move = upper(move);
    end
    
    % Searching for groups of 3 equal moves and substitute them
    % with the inverse move
    if i<=length(move_seq)-2 && move_seq(i) == move_seq(i+1) && move_seq(i) == move_seq(i+2)
        tmp         = move_seq(i); 
        move_seq(i) = inv_move;
        inv_move    = tmp;
        clear tmp
        move_seq(i+1:end-2) = move_seq(i+3:end);
        move_seq = move_seq(1:end-2);
    end
    
    % Searching for "move inv(move)" pairs and delete them from
    % the sequence
    if i<=length(move_seq)-1 && move_seq(i+1) == inv_move
        move_seq(i:end-2) = move_seq(i+2:end);
        move_seq = move_seq(1:end-2);
    end
    i = i+1;
    
end

final_length = length(move_seq);

% Recursion
if final_length == initial_length
    opt_seq = move_seq;
    return
else
    opt_seq = self.optimize_seq(move_seq);
end
end