clear functions; %#ok<CLFUNC>

name = 'RubiksCubeClass';

disp('---------------------------------------------------------');
fprintf(1,'Compiling: %s\n',name);

CMD = [ 'while mislocked(''' name '''); munlock(''' name '''); end;'];
eval(CMD);

CMD = [ 'mex -I../src ../src/RubiksCubeClass.cpp -output mex_', name ];
CMD = [ CMD, ' -largeArrayDims mex_', name ];
CMD = [ CMD, '.cpp ' ];

if isunix
    if ismac
        CMD = [CMD, ' -lstdc++ CXXFLAGS="\$CXXFLAGS -O2 -g0"'];
    else
        CMD = [CMD, ' -lstdc++ CXXFLAGS="\$CXXFLAGS -Wall -O2 -g0"'];
    end
elseif ispc

end

disp(CMD);
eval(CMD);

clear name CMD;

disp('----------------------- DONE ----------------------------');
