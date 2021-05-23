addpath('../src_mex');
cs = CubicSegment2();
p0 = [1,0];
p1 = [2,0];
t0 = [0,1];
t1 = [1,2];
cs.build( p0, p1, t0, t1 );

cs.plot();
