r1 = rect( -1, -1, 1, 1 );
r2 = rect();
r3 = rect();

hold off;
r1.plot('-r','LineWidth',3);

r2.copy(r1);
r2.translate(1,1.2);

r3.copy(r1);
r3.translate(3,2.1);

hold on;
r2.plot('-b','LineWidth',3);
r3.plot('-g','LineWidth',3);

axis equal;

%c2 = r1.collide(r2);
%c3 = r1.collide(r3);

%fprintf('c2 = %d\n', c2 );
%fprintf('c3 = %d\n', c3 );
