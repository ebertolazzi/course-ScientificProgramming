
x = -5:0.001:5;
x = x+rand(size(x));
y = x+1;
y = y+0.01*rand(size(x));

tic
for k=1:10
  [A,B] = minq( x, y );
end
toc

fprintf( 'A = %g, B = %g\n', A, B );
 
hold off;
plot( x, y, 'o', 'MarkerSize', 15, 'MarkerFaceColor', 'red' );

xx = -3:0.001:6;
yy = A*xx+B;

hold on;
plot( xx, yy, '-', 'Color', 'blue', 'LineWidth', 3 );

axis equal
