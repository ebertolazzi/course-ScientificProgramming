function [A,B,ierr] = minq( x, y )
  %disp('using MATLAB minq');

  A    = 0;
  B    = 0;
  ierr = 1;
  npts = length(x);

  if npts < 2; return; end;
  if length(y) ~= npts; return; end;

  M      = zeros( npts, 2 );
  M(:,1) = x;
  M(:,2) = 1;

  % initialize the object QR that perform QR decomoposition
  % and di QR decomposition of its argument
  [Q, R] = qr(M);
  % Q*R*x = rhs --> R*x = Q^T * rhs -> x = R^(-1)* (Q^T*x)|_the first 2 rows
  rhs = Q.'*y(:);
  sol = R(1:2,1:2)\(rhs(1:2));
  A   = sol(1);
  B   = sol(2);
  ierr = 0;
end
