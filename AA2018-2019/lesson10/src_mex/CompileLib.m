clc;
clear functions;

NAMES = { 'CubicSegment2' };

for k=1:length(NAMES)
  N=NAMES{k};
  disp('---------------------------------------------------------');
  fprintf(1,'Compiling: %s\n',N);

  CMD = [ 'while mislocked(''' N '''); munlock(''' N '''); end;'];
  eval(CMD);

  CMD = [ 'mex -I../src -I/usr/local/include/eigen3 -output ../matlab/mex_', N ];
  CMD = [ CMD, ' -largeArrayDims ../src_mex/mex_', N ];
  CMD = [ CMD, '.cc ' ];
  if isunix
    if ismac
      CMD = [CMD, ' -lstdc++ CXXFLAGS="\$CXXFLAGS -Wall -O2 -g0"'];
    else
      CMD = [CMD, ' -lstdc++ CXXFLAGS="\$CXXFLAGS -Wall -O2 -g0"'];
    end
  elseif ispc
  end
  disp(CMD);
  eval(CMD);
end

disp('----------------------- DONE ----------------------------');
