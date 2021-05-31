x = [1, 2, 3, 4, 5, 2, 3, 4, 1, -2];
y = [2, 2, 2, 2, 2, 2, 2, 2, 2, 2]+0.5*sin(x)+0.2*x;

[A,B] = minq( x, y );

fprintf( 'A = %g, B = %g\n', A, B );
 

hold off;
plot( x, y, 'o', 'MarkerSize', 15, 'MarkerFaceColor', 'red' );

xx = -3:0.001:6;
yy = A*xx+B;

hold on;
plot( xx, yy, '-', 'Color', 'blue', 'LineWidth', 3 );

axis equal
