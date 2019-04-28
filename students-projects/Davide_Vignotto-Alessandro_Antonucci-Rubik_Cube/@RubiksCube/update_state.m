% Update the state given a certain move
function up_state = update_state(~, act_state, move)
    switch move
        case "F"
            up_state = m_permut(36,38,14,12, act_state);
            up_state = m_permut(24,37,26,13, up_state);
            up_state = m_permut( 6,35,47,15, up_state);
            up_state = m_permut( 7,23,46,27, up_state);
            up_state = m_permut( 8,11,45,39, up_state);
        case "f"
            up_state = m_permut(12,14,38,36, act_state);
            up_state = m_permut(13,26,37,24, up_state);
            up_state = m_permut(15,47,35,6, up_state);
            up_state = m_permut(27,46,23,7, up_state);
            up_state = m_permut(39,45,11,8, up_state);
        case "R"
            up_state = m_permut(39,41,17,15, act_state);
            up_state = m_permut(16,27,40,29, up_state);
            up_state = m_permut(2,14,47,42, up_state);
            up_state = m_permut(5,26,50,30, up_state);
            up_state = m_permut(8,38,53,18, up_state);
        case "r"
            up_state = m_permut(15,17,41,39, act_state);
            up_state = m_permut(29,40,27,16, up_state);
            up_state = m_permut(42,47,14,2, up_state);
            up_state = m_permut(30,50,26,5, up_state);
            up_state = m_permut(18,53,38,8, up_state);
        case "U"
            up_state = m_permut(0,6,8,2, act_state);
            up_state = m_permut(1,3,7,5, up_state);
            up_state = m_permut(9,12,15,18, up_state);
            up_state = m_permut(10,13,16,19, up_state);
            up_state = m_permut(11,14,17,20, up_state);
        case "u"
            up_state = m_permut(2,8,6,0, act_state);
            up_state = m_permut(5,7,3,1, up_state);
            up_state = m_permut(18,15,12,9, up_state);
            up_state = m_permut(19,16,13,10, up_state);
            up_state = m_permut(20,17,14,11, up_state);
        case "B"
            up_state = m_permut(42,44,20,18, act_state);
            up_state = m_permut(19,30,43,32, up_state);
            up_state = m_permut(0,17,53,33, up_state);
            up_state = m_permut(1,29,52,21, up_state);
            up_state = m_permut(2,41,51,9, up_state);
        case "b"
            up_state = m_permut(18,20,44,42, act_state);
            up_state = m_permut(32,43,30,19, up_state);
            up_state = m_permut(33,53,17,0, up_state);
            up_state = m_permut(21,52,29,1, up_state);
            up_state = m_permut(9,51,41,2, up_state);
        case "L"
            up_state = m_permut(9,33,35,11, act_state);
            up_state = m_permut(10,21,34,23, up_state);
            up_state = m_permut(45,12,0,44, up_state);
            up_state = m_permut(32,48,24,3, up_state);
            up_state = m_permut(20,51,36,6, up_state);
        case "l"
            up_state = m_permut(11,35,33,9, act_state);
            up_state = m_permut(23,34,21,10, up_state);
            up_state = m_permut(44,0,12,45, up_state);
            up_state = m_permut(3,24,48,32, up_state);
            up_state = m_permut(6,36,51,20, up_state);
        case "D"
            up_state = m_permut(47,45,51,53, act_state);
            up_state = m_permut(46,48,52,50, up_state);
            up_state = m_permut(42,39,36,33, up_state);
            up_state = m_permut(43,40,37,34, up_state);
            up_state = m_permut(44,41,38,35, up_state);
        case "d"
            up_state = m_permut(53,51,45,47, act_state);
            up_state = m_permut(50,52,48,46, up_state);
            up_state = m_permut(33,36,39,42, up_state);
            up_state = m_permut(34,37,40,43, up_state);
            up_state = m_permut(35,38,41,44, up_state);
    end
end

%==== Functions ===========================================================

% Permutation of a move
function state = m_permut(a, b, c, d, state)
    tmp        = state(a+1);
    state(a+1) = state(b+1);
    state(b+1) = state(c+1);
    state(c+1) = state(d+1);
    state(d+1) = tmp;
end