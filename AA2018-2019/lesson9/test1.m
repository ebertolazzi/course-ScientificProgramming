a  = 0;
ya = 1;
b  = 2;
yb = 0;
N  = 100;
[M,r] = mex_bvp1(a,b,ya,yb,N);
x   = a:(b-a)/(N-1):b;
sol = M\r;

plot(x,sol);