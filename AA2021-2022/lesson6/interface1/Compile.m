clc;
clear functions;
[~,mexLoaded] = inmem('-completenames');

old_dir = cd(fileparts(which(mfilename)));

CMD   = 'mex -largeArrayDims ';
MROOT = matlabroot;

CMD = [ CMD, ' -output minq minq.cc mex_minq.cc ' ];
if ismac
  CMD = [CMD, ' CXXFLAGS="\$CXXFLAGS -Wall -O2 -g"'];
  CMD = [CMD, ' -I/usr/local/include/eigen3 '];
elseif isunix
  % Workaround for MATLAB 2020 that force dynamic link with old libstdc++
  % solution: link with static libstdc++
  ARCH  = computer('arch');
  PATH1 = [MROOT, '/bin/', ARCH];
  PATH2 = [MROOT, '/extern/bin/', ARCH];
  CMD   = [ CMD, ...
    ' CXXFLAGS="\$CXXFLAGS -Wall -O2 -g"' ...
    ' LDFLAGS="\$LDFLAGS -static-libgcc -static-libstdc++"' ...
    ' LINKLIBS="-L' PATH1 ' -L' PATH2 ' -lMatlabDataArray -lmx -lmex -lmat -lm "' ...
  ];
  CMD = [CMD, ' -I/usr/local/include/eigen3 '];
elseif ispc
  CMD = [CMD, ' -I/usr/local/include/eigen3 '];
end
disp(CMD);
eval(CMD);

cd(old_dir);

disp('----------------------- DONE ----------------------------');
