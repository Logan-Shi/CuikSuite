% CONFIGURATION i
%X = textread('proof_path.sol'); %CUIKSYSTEM
tic
E=1;
X = textread('RSShand_kin.links'); 
[q b] = size(X);
X(:,b) = '';
[q b] = size(X);
for i=1:q
    
% on CUIKSYSTEM
   p22_u_x  = X(i,1);
   p22_u_y  = X(i,2);
   p22_u_z  = X(i,3);
   p22_v_x  = X(i,4);
   p22_v_y  = X(i,5);
   p22_v_z  = X(i,6);
   p23_u_x  = X(i,7);
   p23_u_y  = X(i,8);
   p23_u_z  = X(i,9);
   p23_v_x  = X(i,10);
   p23_v_y  = X(i,11);
   p23_v_z  = X(i,12);
   p24_u_x  = X(i,13);
   p24_u_y  = X(i,14);
   p24_u_z  = X(i,15);
   p24_v_x  = X(i,16);
   p24_v_y  = X(i,17);
   p24_v_z  = X(i,18);
   p32_u_x  = X(i,19);
   p32_u_y  = X(i,20);
   p32_u_z  = X(i,21);
   p32_v_x  = X(i,22);
   p32_v_y  = X(i,23);
   p32_v_z  = X(i,24);
   p33_u_x  = X(i,25);
   p33_u_y  = X(i,26);
   p33_u_z  = X(i,27);
   p33_v_x  = X(i,28);
   p33_v_y  = X(i,29);
   p33_v_z  = X(i,30);
   p34_u_x  = X(i,31);
   p34_u_y  = X(i,32);
   p34_u_z  = X(i,33);
   p34_v_x  = X(i,34);
   p34_v_y  = X(i,35);
   p34_v_z  = X(i,36);
   p40_u_x  = X(i,37);
   p40_u_y  = X(i,38);
   p40_u_z  = X(i,39);
   p40_v_x  = X(i,40);
   p40_v_y  = X(i,41);
   p40_v_z  = X(i,42);
   p42_u_x  = X(i,43);
   p42_u_y  = X(i,44);
   p42_u_z  = X(i,45);
   p42_v_x  = X(i,46);
   p42_v_y  = X(i,47);
   p42_v_z  = X(i,48);
   p43_u_x  = X(i,49);
   p43_u_y  = X(i,50);
   p43_u_z  = X(i,51);
   p43_v_x  = X(i,52);
   p43_v_y  = X(i,53);
   p43_v_z  = X(i,54);
   p44_u_x  = X(i,55);
   p44_u_y  = X(i,56);
   p44_u_z  = X(i,57);
   p44_v_x  = X(i,58);
   p44_v_y  = X(i,59);
   p44_v_z  = X(i,60);
   object_u_x  = X(i,61);
   object_u_y  = X(i,62);
   object_u_z  = X(i,63);
   object_v_x  = X(i,64);
   object_v_y  = X(i,65);
   object_v_z  = X(i,66);   
   uni_u_palm_p22_x_0  = X(i,67);
   uni_u_palm_p22_y_0  = X(i,68);
   uni_u_palm_p22_z_0  = X(i,69);
   uni_v_palm_p22_x_0  = X(i,70);
   uni_v_palm_p22_y_0  = X(i,71);
   uni_v_palm_p22_z_0  = X(i,72);
   w1_palm_p22_x_0  = X(i,73);
   w1_palm_p22_y_0  = X(i,74);
   w1_palm_p22_z_0  = X(i,75);
   w2_palm_p22_x_0  = X(i,76);
   w2_palm_p22_y_0  = X(i,77);
   w2_palm_p22_z_0  = X(i,78);
   cos_0_palm_p22_0 = X(i,79);
   cos_1_palm_p22_0 = X(i,80);
   w1_p22_p23_x_1  = X(i,81);
   w1_p22_p23_y_1  = X(i,82);
   w1_p22_p23_z_1  = X(i,83);
   w2_p22_p23_x_1  = X(i,84);
   w2_p22_p23_y_1  = X(i,85);
   w2_p22_p23_z_1  = X(i,86);
   cos_p22_p23_1 = X(i,87);
   w1_p23_p24_x_2  = X(i,88);
   w1_p23_p24_y_2  = X(i,89);
   w1_p23_p24_z_2  = X(i,90);
   w2_p23_p24_x_2  = X(i,91);
   w2_p23_p24_y_2  = X(i,92);
   w2_p23_p24_z_2  = X(i,93);
   cos_p23_p24_2 = X(i,94);
   uni_u_palm_p32_x_3  = X(i,95);
   uni_u_palm_p32_y_3  = X(i,96);
   uni_u_palm_p32_z_3  = X(i,97);
   uni_v_palm_p32_x_3  = X(i,98);
   uni_v_palm_p32_y_3  = X(i,99);
   uni_v_palm_p32_z_3  = X(i,100);
   w1_palm_p32_x_3  = X(i,101);
   w1_palm_p32_y_3  = X(i,102);
   w1_palm_p32_z_3  = X(i,103);
   w2_palm_p32_x_3  = X(i,104);
   w2_palm_p32_y_3  = X(i,105);
   w2_palm_p32_z_3  = X(i,106);
   cos_0_palm_p32_3 = X(i,107);
   cos_1_palm_p32_3 = X(i,108);
   w1_p32_p33_x_4  = X(i,109);
   w1_p32_p33_y_4  = X(i,110);
   w1_p32_p33_z_4  = X(i,111);
   w2_p32_p33_x_4  = X(i,112);
   w2_p32_p33_y_4  = X(i,113);
   w2_p32_p33_z_4  = X(i,114);
   cos_p32_p33_4 = X(i,115);
   w1_p33_p34_x_5  = X(i,116);
   w1_p33_p34_y_5  = X(i,117);
   w1_p33_p34_z_5  = X(i,118);
   w2_p33_p34_x_5  = X(i,119);
   w2_p33_p34_y_5  = X(i,120);
   w2_p33_p34_z_5  = X(i,121);
   cos_p33_p34_5 = X(i,122);
   w1_palm_p40_x_6  = X(i,123);
   w1_palm_p40_y_6  = X(i,124);
   w1_palm_p40_z_6  = X(i,125);
   w2_palm_p40_x_6  = X(i,126);
   w2_palm_p40_y_6  = X(i,127);
   w2_palm_p40_z_6  = X(i,128);
   cos_palm_p40_6 = X(i,129);
   uni_u_p40_p42_x_7  = X(i,130);
   uni_u_p40_p42_y_7  = X(i,131);
   uni_u_p40_p42_z_7  = X(i,132);
   uni_v_p40_p42_x_7  = X(i,133);
   uni_v_p40_p42_y_7  = X(i,134);
   uni_v_p40_p42_z_7  = X(i,135);
   w1_p40_p42_x_7  = X(i,136);
   w1_p40_p42_y_7  = X(i,137);
   w1_p40_p42_z_7  = X(i,138);
   w2_p40_p42_x_7  = X(i,139);
   w2_p40_p42_y_7  = X(i,140);
   w2_p40_p42_z_7  = X(i,141);
   cos_0_p40_p42_7 = X(i,142);
   cos_1_p40_p42_7 = X(i,143);
   w1_p42_p43_x_8  = X(i,144);
   w1_p42_p43_y_8  = X(i,145);
   w1_p42_p43_z_8  = X(i,146);
   w2_p42_p43_x_8  = X(i,147);
   w2_p42_p43_y_8  = X(i,148);
   w2_p42_p43_z_8  = X(i,149);
   cos_p42_p43_8 = X(i,150);
   w1_p43_p44_x_9  = X(i,151);
   w1_p43_p44_y_9  = X(i,152);
   w1_p43_p44_z_9  = X(i,153);
   w2_p43_p44_x_9  = X(i,154);
   w2_p43_p44_y_9  = X(i,155);
   w2_p43_p44_z_9  = X(i,156);   
   cos_p43_p44_9 = X(i,157);
   object_r_x = X(i,158);
   object_r_y = X(i,159);
   object_r_z = X(i,160);
   p24_r_x = X(i,161);
   p24_r_y = X(i,162);
   p24_r_z = X(i,163);
   p34_r_x = X(i,164);
   p34_r_y = X(i,165);
   p34_r_z = X(i,166);
   p44_r_x = X(i,167);
   p44_r_y = X(i,168);
   p44_r_z = X(i,169);
   o_x1_x = X(i,170);
   o_x1_y = X(i,171);
   o_x1_z = X(i,172);
   o_x2_x = X(i,173);
   o_x2_y = X(i,174);
   o_x2_z = X(i,175);
   o_x3_x = X(i,176);
   o_x3_y = X(i,177);
   o_x3_z = X(i,178);
   
   % local vectors
q21x =  -4.3;
q21y =   0;
q21z = 150.15;
q21 = [q21x q21y q21z 1]';

q23x_2 = 67.8;
q23y_2 =  0;
q23z_2 =  0;
q23_2 = [q23x_2 q23x_2 q23x_2 1]';

q24x_3 = 30;
q24y_3 =  0;
q24z_3 =  0;
q24_3 = [q24x_3 q24x_3 q24x_3 1]';


q31x =  -4.3;
q31y =  40.165;
q31z = 145.43;
q31 = [q31x q31y q31z 1]';

q33x_2 = 67.8;
q33y_2 =  0;
q33z_2 =  0;
q33_2 = [q33x_2 q33x_2 q33x_2 1]';

q34x_3 = 30;
q34y_3 =  0;
q34z_3 =  0;
q34_3 = [q34x_3 q34x_3 q34x_3 1]';


q40x = -3;
q40y = 27.1;
q40z =  0;
q40 = [q40x q40y q40z 1]';

q41x_0= 97;
q41y_0=  6;
q41z_0=-87;
q41_0 = [q41x_0 q41y_0 q41z_0 1]';

q43x_2 = 67.8;
q43y_2 =  0;
q43z_2 =  0;
q43_2 = [q43x_2 q43x_2 q43x_2 1]';

q44x_3 = 30;
q44y_3 =  0;
q44z_3 =  0;
q44_3 = [q44x_3 q44x_3 q44x_3 1]';



% Local point on finger 1
  f_x1_x=32.000000000000;
  f_x1_y=0.000000000000;
  f_x1_z=11.000000000000;
  f_x1_x = [f_x1_x f_x1_y f_x1_z 1]';


% Local point on finger 2
  f_x2_x=32.000000000000;
  f_x2_y=0.000000000000;
  f_x2_z=11.000000000000;
  f_x2_x = [f_x2_x f_x2_y f_x2_z 1]';

% Local point on finger 3
  f_x3_x=35.000000000000;
  f_x3_y=0.000000000000;
  f_x3_z=9.000000000000;
  f_x3_x = [f_x3_x f_x3_y f_x3_z 1]';


% Local normal on finger 1
  f_n1_x=-0.370978008315;
  f_n1_y=0.000001203274;
  f_n1_z=-0.928641651736;
  f_n1 = [f_n1_x f_n1_y f_n1_z]';

% Local normal on finger 2
  f_n2_x=-0.504500226990;
  f_n2_y=-0.018296824687;
  f_n2_z=-0.863217670788;
  f_n2 = [f_n2_x f_n2_y f_n2_z]';

% Local normal on finger 3
  f_n3_x=-0.631749040004;
  f_n3_y=0.000056310180;
  f_n3_z=-0.775172978936;
  f_n3 = [f_n3_x f_n3_y f_n3_z]';

% Radius for each contact point on object
  r1=21.800089389209;
  r2=22.427742642054;
  r3=22.116598832962;
   
%% building the reference frames
P22_R = [[p22_u_x p22_u_y p22_u_z]' [p22_v_x p22_v_y p22_v_z]' cross([p22_u_x p22_u_y p22_u_z]',[p22_v_x p22_v_y p22_v_z]')];
P23_R = [[p23_u_x p23_u_y p23_u_z]' [p23_v_x p23_v_y p23_v_z]' cross([p23_u_x p23_u_y p23_u_z]',[p23_v_x p23_v_y p23_v_z]')];
P24_R = [[p24_u_x p24_u_y p24_u_z]' [p24_v_x p24_v_y p24_v_z]' cross([p24_u_x p24_u_y p24_u_z]',[p24_v_x p24_v_y p24_v_z]')];

P32_R = [[p32_u_x p32_u_y p32_u_z]' [p32_v_x p32_v_y p32_v_z]' cross([p32_u_x p32_u_y p32_u_z]',[p32_v_x p32_v_y p32_v_z]')];
P33_R = [[p33_u_x p33_u_y p33_u_z]' [p33_v_x p33_v_y p33_v_z]' cross([p33_u_x p33_u_y p33_u_z]',[p33_v_x p33_v_y p33_v_z]')];
P34_R = [[p34_u_x p34_u_y p34_u_z]' [p34_v_x p34_v_y p34_v_z]' cross([p34_u_x p34_u_y p34_u_z]',[p34_v_x p34_v_y p34_v_z]')];

P40_R = [[p40_u_x p40_u_y p40_u_z]' [p40_v_x p40_v_y p40_v_z]' cross([p40_u_x p40_u_y p40_u_z]',[p40_v_x p40_v_y p40_v_z]')];
P42_R = [[p42_u_x p42_u_y p42_u_z]' [p42_v_x p42_v_y p42_v_z]' cross([p42_u_x p42_u_y p42_u_z]',[p42_v_x p42_v_y p42_v_z]')];
P43_R = [[p43_u_x p43_u_y p43_u_z]' [p43_v_x p43_v_y p43_v_z]' cross([p43_u_x p43_u_y p43_u_z]',[p43_v_x p43_v_y p43_v_z]')];
P44_R = [[p44_u_x p44_u_y p44_u_z]' [p44_v_x p44_v_y p44_v_z]' cross([p44_u_x p44_u_y p44_u_z]',[p44_v_x p44_v_y p44_v_z]')];

OBJ_R = [[object_u_x object_u_y object_u_z]' [object_v_x object_v_y object_v_z]' cross([object_u_x object_u_y object_u_z]',[object_v_x object_v_y object_v_z]')];

OBJ_M = [OBJ_R [object_r_x object_r_y object_r_z]'; 0 0 0 1];

P22_M = [P22_R q21(1:3); 0 0 0 1];
a = P22_M*q23_2;
P23_M = [P23_R a(1:3); 0 0 0 1];
P24_M = [P24_R [p24_r_x p24_r_y p24_r_z]'; 0 0 0 1];

P32_M = [P32_R q31(1:3); 0 0 0 1];
a = P32_M*q33_2;
P33_M = [P33_R a(1:3); 0 0 0 1];
P34_M = [P34_R [p34_r_x p34_r_y p34_r_z]'; 0 0 0 1];

P40_M = [P40_R q40(1:3); 0 0 0 1];
a = P40_M*q41_0;
P42_M = [P42_R a(1:3); 0 0 0 1];
a = P42_M*q43_2;
P43_M = [P43_R a(1:3); 0 0 0 1];
P44_M = [P44_R [p44_r_x p44_r_y p44_r_z]'; 0 0 0 1];





% ----- EQS.



% joint locations and contact frames finger 2 contact 1
j21 =  P22_M(1:3,4);
j22 = P22_M(1:3,4);
j23 = P23_M(1:3,4);
j24 = P24_M(1:3,4);
r21 = [1 0 0]';
r22 = P22_R(1:3,2);
r23 = -P23_R(1:3,2);
r24 = -P24_R(1:3,2);

c1 = P24_M*f_x1_x;
c1 = c1(1:3);
n1 = P24_R*f_n1;
t1 = ortonormalvector(n1,0.1);
t2 = cross(n1,t1);
R1 = [n1 t1 t2]; 
R1 = blkdiag(R1,R1); 

% joint locations and contact frames finger 3 contact 2
j31 =  P32_M(1:3,4);
j32 = P32_M(1:3,4);
j33 = P33_M(1:3,4);
j34 = P34_M(1:3,4);
r31 = [1 0 0]';
r32 = P32_R(1:3,2);
r33 = -P33_R(1:3,2);
r34 = -P34_R(1:3,2);

c2 = P34_M*f_x2_x;
c2 = c2(1:3);
n2 = P34_R*f_n2;
t1 = ortonormalvector(n2,0.1);
t2 = cross(n2,t1);
R2 = [n2 t1 t2]; 
R2 = blkdiag(R2,R2);

% joint locations and contact frames finger 4 contact 3
j40 =  P40_M(1:3,4);
j41 = P42_M(1:3,4);
j42 = P42_M(1:3,4);
j43 = P43_M(1:3,4);
j44 = P44_M(1:3,4);
r40 = [0 0 -1]';
r41 = P40_R*[0.573580 0 0.81915]';
r42 = P42_R(1:3,2);
r43 = -P43_R(1:3,2);
r44 = -P44_R(1:3,2);

c3 = P44_M*f_x3_x;
c3 = c3(1:3);
n3 = P44_R*f_n3;
t1 = ortonormalvector(n3,0.1);
t2 = cross(n3,t1);
R3 = [n3 t1 t2]; 
R3 = blkdiag(R3,R3);

o = OBJ_M(1:3,4);




% jacobian matrices
Z1 = [skew(c1-j21)'*r21 skew(c1-j22)'*r22 skew(c1-j23)'*r23 skew(c1-j24)'*r24 zeros(3,9); r21 r22 r23 r24 zeros(3,9)];

Z2 = [zeros(3,4) skew(c2-j31)'*r31 skew(c2-j32)'*r32 skew(c2-j33)'*r33 skew(c2-j34)'*r34 zeros(3,5); zeros(3,4) r31 r32 r33 r34 zeros(3,5)];

Z3 = [zeros(3,8) skew(c3-j40)'*r40 skew(c3-j41)'*r41 skew(c3-j42)'*r42 skew(c3-j43)'*r43 skew(c3-j44)'*r44; zeros(3,8) r40 r41 r42 r43 r44];

% whole jacobian in the contact frame
J = [ R1'*Z1 ; R2'*Z2 ; R3'*Z3 ];

% grasp matrices
P1 = [eye(3) zeros(3,3);skew(c1-o) eye(3)]; 
P2 = [eye(3) zeros(3,3);skew(c2-o) eye(3)]; 
P3 = [eye(3) zeros(3,3);skew(c3-o) eye(3)]; 

% whole grasp
Gt = [R1'*P1'; R2'*P2' ; R3'*P3'];

% selection matrices: transmit forces in the normal and tangent directions, hard friction contact
H1 = [ [1 0 0]' [0 1 0]' [0 0 1]' zeros(3,3); zeros(3,6)];
H2 = [ [1 0 0]' [0 1 0]' [0 0 1]' zeros(3,3); zeros(3,6)];
H3 = [ [1 0 0]' [0 1 0]' [0 0 1]' zeros(3,3); zeros(3,6)];

% whole selection matrices
H = blkdiag(H1,H2,H3);

% manipulation matrix
M = H*[-Gt J*E];

% coordinated motions
C = null(M);

% mobility
n = rank(C);

% dimensions
[m,no] = size(Gt);
[m,ni] = size(J*E);

% internal motion matrix: when object and passive joints are locked
A23 = null(H*J*E);
Nr = rank(A23); % redundancy
Or = zeros(no,Nr);
Ar = [Or ; A23];

% uncontrollable motion matrix: when active joints are locked
A11 = null(H*Gt); 
Ni = rank(A11); %indetermincay
Oi = zeros(ni,Ni);
Ai = [A11 ; Oi];

% coordinated motion matrix: both active joints and object move fulfilling 
% the contact constraints

% connectivity
Nc = n-Nr-Ni;

% gram smith orthogonalization using the two previous matrices as a starting base
A = [Ar Ai];
for t=1:n,
    [ms,ns] = size(A);
    v = C(:,t);
    for j=1:ns,
        v = v-dot(v,A(:,j))*A(:,j);
    end
    if norm(v)>1e-6
        v = v/norm(v);
        A = [A v];
    end
end

Ac = A(:,Ni+Nr+1:n);
A12 = Ac(1:no,:);
A22 = Ac(no+1:no+ni,:);


%% we can leave it like this, or we can additionally reduce A12 to find an even nicer base
%R = rref([A12' eye(Nc)]);

%% get the operations
%T = transpose(R(:,no+1:Nc+no));

%% get the nicer base for the object motions
%A12 = transpose(R(:,1:no));

%%apply the corresponding operations
%A22 = A22*T;

%% concatenate the reduced Ac
%Ac = [A12 ; A22]; 

% the new mobility matrix
A = [Ai Ac Ar];


% MANIPULABILITY

% weight matrices for the output and input spaces
Wu = eye(no);
Wq = eye(ni);

% projector matrices in the case of internal or uncontrollable motions
P1w = projmatrix(A11,Wu);
P2w = projmatrix(A23,Wq);

B1 = A12'*P1w'*Wu*P1w*A12;
B2 = A22'*P2w'*Wq*P2w*A22;

% getting the eigenvalues and eigenvectors
[U,V,Y,C,S] = gsvd(B1,B2);
%[U,S,V]) = svd(B2\B1);
SIGMA = sqrt(diag(C'*C)./diag(S'*S));

% first manipulability index: inverse of the condition number of the ratio matrix
mani1(i) = 1/(SIGMA(length(SIGMA)) / SIGMA(1));


% second manipulability index: determinant of the ratio matrix

mani2(i) = prod(SIGMA);

% third manipulability index: the minimum of the sngular values
mani3(i) = SIGMA(1);


% calculate the ratios for each of the coordinated motions that minimizes redundancy and indeterminacy, and the corresponding motions
% Ra = (xc'*B1*xc)/(xc'*B2*xc);
% u = P1*A12*xc;
% q = P2*A22*xc;


xc = 1/sqrt(SIGMA(length(SIGMA)))*U(:,1);
u1 = P1w*A12*xc;
q1 = P2w*A22*xc;
%%Ra1 = (xc'*B1*xc)/(xc'*B2*xc);

xc = 1/sqrt(SIGMA(length(SIGMA)-1))*U(:,2);
u2 = P1w*A12*xc;
q2 = P2w*A22*xc;
%%Ra2 = (xc'*B1*xc)/(xc'*B2*xc);

xc = 1/sqrt(SIGMA(length(SIGMA)-2))*U(:,3);
u3 = P1w*A12*xc;
q3 = P2w*A22*xc;
%%Ra3 = (xc'*B1*xc)/(xc'*B2*xc);

xc = 1/sqrt(SIGMA(length(SIGMA)-3))*U(:,4);
u4 = P1w*A12*xc;
q4 = P2w*A22*xc;
%%Ra1 = (xc'*B1*xc)/(xc'*B2*xc);

xc = 1/sqrt(SIGMA(length(SIGMA)-4))*U(:,5);
u5 = P1w*A12*xc;
q5 = P2w*A22*xc;
%%Ra2 = (xc'*B1*xc)/(xc'*B2*xc);

xc = 1/sqrt(SIGMA(length(SIGMA)-5))*U(:,6);
u6 = P1w*A12*xc;
q6 = P2w*A22*xc;
%%Ra3 = (xc'*B1*xc)/(xc'*B2*xc);



%% null space of J transposed (defective) direction in which the forces are supported by the structure
%F = null( (H*J*E)' );

%% null space of G (graspable) internal forces
%I = null( (H*Gt)' );

%% their intersection should be null if we want to control all internal forces !


%%%% PLOTs

%line([0 0.5],[0 0],[0 0],'Color','red');
%line([0 0],[0 0.5],[0 0],'Color','green');
%line([0 0],[0 0],[0 0.5],'Color','blue');

plotEllipsoid(10*[u6(1) u5(1) u4(1);u6(2) u5(2) u4(2);u6(3) u5(3) u4(3)],[o(1); o(2); o(3)]);

%end

end

toc



d = min(mani1);
mani1=mani1-d;
D = max(mani1);
F = fopen('mani1','w');
for i=1:length(mani1)
fprintf(F,'%f\n',mani1(i)/D);
end
fclose(F);


d = min(mani2);
mani2=mani2-d;
D = max(mani2);
F = fopen('mani2','w');
for i=1:length(mani2)
fprintf(F,'%f\n',mani2(i)/D);
end
fclose(F);

d = min(mani3);
mani3=mani3-d;
D = max(mani3);
F = fopen('mani3','w');
for i=1:length(mani3)
fprintf(F,'%f\n',mani3(i)/D);
end
fclose(F);



c = 1;
for i=1:length(mani2)
    if mani2(i)==min(mani2)
        index(c) = i;
        c=c+1;
    end
end



X = textread('RSShand_kin_simp.center'); %SIMPLIFIED CUIKSYSTEM 
[q b] = size(X);
X(:,b) = '';
[q b] = size(X);
F = fopen('simp.sol','w');
for i=1:q
    fprintf(F,'%s%d','{ ',b);
    for j=1:b
        fprintf(F,'%s%f%s%f%s',' [',X(i,j),',',X(i,j),']');
    end
    fprintf(F,'%s\n','}');
end
fclose(F);


F = fopen('dumb','w');
for i=1:50000
fprintf(F,'%f\n',1);
end
fclose(F);


