% Plot the cube
function plot_state(~, state)

% Define the cube elements
F3d = define_cube_3d();
F2d = define_cube_2d();

% Color map
col = color_map();

% Plot the cube in 2D
subplot(2,1,2);
hold on;
axis equal;
xlim([0 24]);
ylim([0 18]);
% Fill faces colors
for i = 1:54
    fill(F2d(1,:,i), F2d(2,:,i), cell2mat(col(1+state(i))), 'LineWidth', 1);
end
hold off;

% Plot the cube in 3D
subplot(2,1,1);
hold on;
view(150,30);
axis equal;
xlim(5*[-1 1]);
ylim(5*[-1 1]);
zlim(5*[-1 1]);
% Fill faces colors
for i = 1:54
    fill3(squeeze(F3d(i,1,:)), squeeze(F3d(i,2,:)), squeeze(F3d(i,3,:)), cell2mat(col(1+state(i))), 'LineWidth', 1);
end
hold off;

end

%==== Functions ===========================================================

% Define the 3D cube
function faces = define_cube_3d()

%==== Vertices coordinates ================================================

% Vertices of the front face

v333   = [3,3,3]';
v313   = [3,1,3]';
v331   = [3,3,1]';
v311   = [3,1,1]';

v3m3m3 = [3,-3,-3]';
v3m1m3 = [3,-1,-3]';
v3m3m1 = [3,-3,-1]';
v3m1m1 = [3,-1,-1]';

v33m3  = [3,3,-3]';
v31m3  = [3,1,-3]';
v33m1  = [3,3,-1]';
v31m1  = [3,1,-1]';

v3m33  = [3,-3,3]';
v3m13  = [3,-1,3]';
v3m31  = [3,-3,1]';
v3m11  = [3,-1,1]';

% Vertices of the rear face

vm333   = [-3,3,3]';
vm313   = [-3,1,3]';
vm331   = [-3,3,1]';
vm311   = [-3,1,1]';

vm3m3m3 = [-3,-3,-3]';
vm3m1m3 = [-3,-1,-3]';
vm3m3m1 = [-3,-3,-1]';
vm3m1m1 = [-3,-1,-1]';

vm33m3  = [-3,3,-3]';
vm31m3  = [-3,1,-3]';
vm33m1  = [-3,3,-1]';
vm31m1  = [-3,1,-1]';

vm3m33  = [-3,-3,3]';
vm3m13  = [-3,-1,3]';
vm3m31  = [-3,-3,1]';
vm3m11  = [-3,-1,1]';

% Vertices of the middle-front face

v133   = [1,3,3]';
v113   = [1,1,3]';
v131   = [1,3,1]';
%v111   = [1,1,1];

v1m3m3 = [1,-3,-3]';
v1m1m3 = [1,-1,-3]';
v1m3m1 = [1,-3,-1]';
%v1m1m1 = [1,-1,-1];

v13m3  = [1,3,-3]';
v11m3  = [1,1,-3]';
v13m1  = [1,3,-1]';
%v11m1  = [1,1,-1];

v1m33  = [1,-3,3]';
v1m13  = [1,-1,3]';
v1m31  = [1,-3,1]';
%v1m11  = [1,-1,1];

% Vertices of the middle-rear face

vm133   = [-1,3,3]';
vm113   = [-1,1,3]';
vm131   = [-1,3,1]';
%vm111   = [-1,1,1];

vm1m3m3 = [-1,-3,-3]';
vm1m1m3 = [-1,-1,-3]';
vm1m3m1 = [-1,-3,-1]';
%vm1m1m1 = [-1,-1,-1];

vm13m3  = [-1,3,-3]';
vm11m3  = [-1,1,-3]';
vm13m1  = [-1,3,-1]';
%vm11m1  = [-1,1,-1];

vm1m33  = [-1,-3,3]';
vm1m13  = [-1,-1,3]';
vm1m31  = [-1,-3,1]';
%vm1m11 = [-1,-1,1];

% All the 56 vertices
%verts = [ v333  v313  v331  v311  v3m33  v3m13  v3m31  v3m11  v33m3  v31m3  v33m1  v31m1  v3m3m3  v3m1m3  v3m3m1  v3m1m1 ...
%          v133  v113  v131        v1m33  v1m13  v1m31         v13m3  v11m3  v13m1         v1m3m3  v1m1m3  v1m3m1         ...
%         vm133 vm113 vm131       vm1m33 vm1m13 vm1m31        vm13m3 vm11m3 vm13m1        vm1m3m3 vm1m1m3 vm1m3m1         ...
%         vm333 vm313 vm331 vm311 vm3m33 vm3m13 vm3m31 vm3m11 vm33m3 vm31m3 vm33m1 vm31m1 vm3m3m3 vm3m1m3 vm3m3m1 vm3m1m1 ];

%==== Faces coordinates ===============================================

faces = NaN(54,3,4);

% Groups of verteces of white (U) face

faces(1,:,:)  = [vm1m33 , vm1m13 , vm3m13 , vm3m33 ];
faces(2,:,:)  = [vm113  , vm1m13 , vm3m13 , vm313  ];
faces(3,:,:)  = [vm133  , vm113  , vm313  , vm333  ];

faces(4,:,:)  = [v1m33  , v1m13  , vm1m13 , vm1m33 ];
faces(5,:,:)  = [vm1m13 , v1m13  , v113   , vm113  ];
faces(6,:,:)  = [vm133  , vm113  , v113   , v133   ];

faces(7,:,:)  = [v3m33  , v3m13  , v1m13  , v1m33  ];
faces(8,:,:)  = [v1m13  , v3m13  , v313   , v113   ];
faces(9,:,:)  = [v333   , v313   , v113   , v133   ];

% Groups of verteces of orange (L) face

faces(10,:,:) = [vm3m33  , vm1m33  , vm1m31 , vm3m31   ];
faces(11,:,:) = [vm1m33  , v1m33   , v1m31  , vm1m31   ];
faces(12,:,:) = [v1m33   , v3m33   , v3m31  , v1m31    ];

faces(22,:,:) = [vm3m31  , vm1m31  , vm1m3m1 , vm3m3m1 ];
faces(23,:,:) = [v1m31   , v1m3m1  , vm1m3m1 , vm1m31  ];
faces(24,:,:) = [v1m31   , v3m31   , v3m3m1  , v1m3m1  ];

faces(34,:,:) = [vm3m3m1 , vm1m3m1 , vm1m3m3 , vm3m3m3 ];
faces(35,:,:) = [vm1m3m1 , v1m3m1  , v1m3m3  , vm1m3m3 ];
faces(36,:,:) = [v1m3m1  , v3m3m1  , v3m3m3  , v1m3m3  ];

% Groups of verteces of green (F) face

faces(13,:,:) = [v3m33  , v3m13  , v3m11  , v3m31  ];
faces(14,:,:) = [v3m11  , v3m13  , v313   , v311   ];
faces(15,:,:) = [v333   , v313   , v311   , v331   ];

faces(25,:,:) = [v3m31  , v3m11  , v3m1m1 , v3m3m1 ];
faces(26,:,:) = [v3m1m1 , v3m11  , v311   , v31m1  ];
faces(27,:,:) = [v33m1  , v31m1  , v311   , v331   ];

faces(37,:,:) = [v3m3m1 , v3m1m1 , v3m1m3 , v3m3m3 ];
faces(38,:,:) = [v31m1  , v3m1m1 , v3m1m3 , v31m3  ];
faces(39,:,:) = [v33m1  , v31m1  , v31m3  , v33m3  ];

% Groups of verteces of red (R) face

faces(16,:,:) = [v133   , v333   , v331  , v131    ];
faces(17,:,:) = [vm133  , v133   , v131  , vm131   ];
faces(18,:,:) = [vm333  , vm133  , vm131 , vm331   ];

faces(28,:,:) = [v131   , v331   , v33m1  , v13m1  ];
faces(29,:,:) = [v131   , v13m1  , vm13m1 , vm131  ];
faces(30,:,:) = [vm331  , vm131  , vm13m1 , vm33m1 ];

faces(40,:,:) = [v13m1  , v33m1  , v33m3  , v13m3  ];
faces(41,:,:) = [vm13m1 , v13m1  , v13m3  , vm13m3 ];
faces(42,:,:) = [vm33m1 , vm13m1 , vm13m3 , vm33m3 ];

% Groups of verteces of blue (B) face

faces(19,:,:) = [vm333  , vm313   , vm311   , vm331  ];
faces(20,:,:) = [vm3m11 , vm3m13  , vm313   , vm311  ];
faces(21,:,:) = [vm3m33 , vm3m13  , vm3m11  , vm3m31 ];

faces(31,:,:) = [vm33m1 , vm31m1  , vm311   , vm331  ];
faces(32,:,:) = [vm3m1m1, vm3m11  , vm311   , vm31m1 ];
faces(33,:,:) = [vm3m31 , vm3m11  , vm3m1m1 , vm3m3m1];

faces(43,:,:) = [vm33m1 , vm31m1  , vm31m3  , vm33m3 ];
faces(44,:,:) = [vm31m1 , vm3m1m1 , vm3m1m3 , vm31m3 ];
faces(45,:,:) = [vm3m3m1, vm3m1m1 , vm3m1m3 , vm3m3m3];

% Groups of verteces of yellow (D) face

faces(46,:,:) = [v3m3m3  , v3m1m3  , v1m1m3  , v1m3m3  ];
faces(47,:,:) = [v1m1m3  , v3m1m3  , v31m3   , v11m3   ];
faces(48,:,:) = [v33m3   , v31m3   , v11m3   , v13m3   ];

faces(49,:,:) = [v1m3m3  , v1m1m3  , vm1m1m3 , vm1m3m3 ];
faces(50,:,:) = [vm1m1m3 , v1m1m3  , v11m3   , vm11m3  ];
faces(51,:,:) = [vm13m3  , vm11m3  , v11m3   , v13m3   ];

faces(52,:,:) = [vm1m3m3 , vm1m1m3 , vm3m1m3 , vm3m3m3 ];
faces(53,:,:) = [vm11m3  , vm1m1m3 , vm3m1m3 , vm31m3  ];
faces(54,:,:) = [vm13m3  , vm11m3  , vm31m3  , vm33m3  ];

end

% Define the 2D cube
function faces = define_cube_2d()

% Vertices coordinates

v1  = [ 6, 18]';
v2  = [ 8, 18]';
v3  = [10, 18]';
v4  = [12, 18]';

v5  = [ 6, 16]';
v6  = [ 8, 16]';
v7  = [10, 16]';
v8  = [12, 16]';

v9  = [ 6, 14]';
v10 = [ 8, 14]';
v11 = [10, 14]';
v12 = [12, 14]';

v13 = [ 0, 12]';
v14 = [ 2, 12]';
v15 = [ 4, 12]';
v16 = [ 6, 12]';
v17 = [ 8, 12]';
v18 = [10, 12]';
v19 = [12, 12]';
v20 = [14, 12]';
v21 = [16, 12]';
v22 = [18, 12]';
v23 = [20, 12]';
v24 = [22, 12]';
v25 = [24, 12]';

v26 = [ 0, 10]';
v27 = [ 2, 10]';
v28 = [ 4, 10]';
v29 = [ 6, 10]';
v30 = [ 8, 10]';
v31 = [10, 10]';
v32 = [12, 10]';
v33 = [14, 10]';
v34 = [16, 10]';
v35 = [18, 10]';
v36 = [20, 10]';
v37 = [22, 10]';
v38 = [24, 10]';

v39 = [ 0,  8]';
v40 = [ 2,  8]';
v41 = [ 4,  8]';
v42 = [ 6,  8]';
v43 = [ 8,  8]';
v44 = [10,  8]';
v45 = [12,  8]';
v46 = [14,  8]';
v47 = [16,  8]';
v48 = [18,  8]';
v49 = [20,  8]';
v50 = [22,  8]';
v51 = [24,  8]';

v52 = [ 0,  6]';
v53 = [ 2,  6]';
v54 = [ 4,  6]';
v55 = [ 6,  6]';
v56 = [ 8,  6]';
v57 = [10,  6]';
v58 = [12,  6]';
v59 = [14,  6]';
v60 = [16,  6]';
v61 = [18,  6]';
v62 = [20,  6]';
v63 = [22,  6]';
v64 = [24,  6]';

v65 = [ 6,  4]';
v66 = [ 8,  4]';
v67 = [10,  4]';
v68 = [12,  4]';

v69 = [ 6,  2]';
v70 = [ 8,  2]';
v71 = [10,  2]';
v72 = [12,  2]';

v73 = [ 6,  0]';
v74 = [ 8,  0]';
v75 = [10,  0]';
v76 = [12,  0]';

% Faces coordinates

faces = NaN(2,4,54);

% Groups of vertices of white (U) face

faces(:,:,1)  = [ v1,  v2,  v6,  v5];
faces(:,:,2)  = [ v2,  v3,  v7,  v6];
faces(:,:,3)  = [ v3,  v4,  v8,  v7];

faces(:,:,4)  = [ v5,  v6, v10,  v9];
faces(:,:,5)  = [ v6,  v7, v12, v10];
faces(:,:,6)  = [ v7,  v8, v12, v11];

faces(:,:,7)  = [ v9, v10, v17, v16];
faces(:,:,8)  = [v10, v11, v18, v17];
faces(:,:,9)  = [v11, v12, v19, v18];

% Groups of vertices of orange (L) face

faces(:,:,10) = [v13, v14, v27, v26];
faces(:,:,11) = [v14, v15, v28, v27];
faces(:,:,12) = [v15, v16, v29, v28];

faces(:,:,22) = [v26, v27, v40, v39];
faces(:,:,23) = [v27, v28, v41, v40];
faces(:,:,24) = [v28, v29, v42, v41];

faces(:,:,34) = [v39, v40, v53, v52];
faces(:,:,35) = [v40, v41, v54, v53];
faces(:,:,36) = [v41, v42, v55, v54];

% Groups of vertices of green (F) face

faces(:,:,13) = [v16, v17, v30, v29];
faces(:,:,14) = [v17, v18, v31, v30];
faces(:,:,15) = [v18, v19, v32, v31];

faces(:,:,25) = [v29, v30, v43, v42];
faces(:,:,26) = [v30, v31, v44, v43];
faces(:,:,27) = [v31, v32, v45, v44];

faces(:,:,37) = [v42, v43, v56, v55];
faces(:,:,38) = [v43, v44, v57, v56];
faces(:,:,39) = [v44, v46, v58, v57];

% Groups of vertices of red (R) face

faces(:,:,16) = [v19, v20, v33, v32];
faces(:,:,17) = [v20, v21, v34, v33];
faces(:,:,18) = [v21, v22, v35, v34];

faces(:,:,28) = [v32, v33, v46, v45];
faces(:,:,29) = [v33, v34, v47, v46];
faces(:,:,30) = [v34, v35, v48, v47];

faces(:,:,40) = [v45, v46, v59, v58];
faces(:,:,41) = [v46, v47, v60, v59];
faces(:,:,42) = [v47, v48, v61, v60];

% Groups of vertices of blue (B) face

faces(:,:,19) = [v22, v23, v36, v35];
faces(:,:,20) = [v23, v24, v37, v36];
faces(:,:,21) = [v24, v25, v38, v37];

faces(:,:,31) = [v35, v36, v49, v48];
faces(:,:,32) = [v36, v37, v50, v49];
faces(:,:,33) = [v37, v38, v51, v50];

faces(:,:,43) = [v48, v49, v62, v61];
faces(:,:,44) = [v49, v50, v63, v62];
faces(:,:,45) = [v50, v51, v64, v63];

% Groups of vertices of yellow (D) face

faces(:,:,46) = [v55, v56, v66, v65];
faces(:,:,47) = [v56, v57, v67, v66];
faces(:,:,48) = [v57, v58, v68, v67];

faces(:,:,49) = [v65, v66, v70, v69];
faces(:,:,50) = [v66, v67, v71, v70];
faces(:,:,51) = [v67, v68, v72, v71];

faces(:,:,52) = [v69, v70, v74, v73];
faces(:,:,53) = [v70, v71, v75, v74];
faces(:,:,54) = [v71, v72, v76, v75];

end

% Color map: from number (state) to color
function colors = color_map()

o = [0.970, 0.730, 0.250];
colors = {'w','w','w','w','w','w','w','w','w',...
    o , o , o ,'g','g','g','r','r','r','b','b','b',...
    o , o , o ,'g','g','g','r','r','r','b','b','b',...
    o , o , o ,'g','g','g','r','r','r','b','b','b',...
    'y','y','y','y','y','y','y','y','y'};

end