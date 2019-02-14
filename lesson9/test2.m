a  = 0;
ya = 1;
b  = 2;
yb = 0;
N  = 100;
P  = @(x) x;
[M,r] = mex_bvp2(a,b,ya,yb,N,P,'Q','R');
x   = a:(b-a)/(N-1):b;
sol = M\r;

plot(x,sol);
