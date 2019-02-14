a  = 0;
ya = 1;
b  = 2;
yb = 0;
N  = 100;
[L,D,U,r] = mex_bvp(a,b,ya,yb,N);
M = sparse( N, N );
for k=1:N
  M(k,k) = D(k);
end
for k=1:N-1
  M(k+1,k) = L(k+1);
  M(k,k+1) = U(k);
end
x   = a:(b-a)/(N-1):b;
sol = M\r.';