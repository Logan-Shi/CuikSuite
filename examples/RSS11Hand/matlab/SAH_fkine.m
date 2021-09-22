p=0;
%function  [J,G,C1,C2,C3,C4] = SAH_fkine(Q,Tw_h,p,color)
%
% Forward kinematics of the SAH, provided the configuration Q and hand
% position Tw_h respect to the world, the function returns the frames at
% the contact points at the fingertips and the jacobian respect to the
% world to them, as well as the grasp matrix defined at the contact points. 
% The values 'p' and 'color' are used for plotting.
%
% Q should be introduced as follows
%      |     THUMB     |   INDEX   |  MIDDLE   |   RING    |
%      |bas abd prx dst|abd prx dst|abd prx dst|abd prx dst|  
%        1   2   3   4   5   6   7   8   9   10  11  12  13
% Q = [ q40 q41 q42 q43 q31 q32 q33 q21 q22 q23 q11 q12 q13 ];
%
% Qhome = [0 0 -4 4 0 -4 4 0 -4 4 0 -4 4]*pi/180;
% Qany = [pi/2 0 0 3*pi/16 -pi/16  1.2*pi/16  pi/8 -pi/16 1.35*pi/16 pi/8  0 0 0];
% Qtop = [90 0 90 90 0 90 90 0 90 90 0 90 90]*pi/180;
%
% Tw_h is the homogeneous transformation matrix that defines the position and orientation of the hand
% respect to a world frame. If the hand is the global, then Tw_h = eye(4)
%Tw_h = [xx   yx   zx  x;
%        xy   yy   zy  y;
%        xz   yz   zz  z;
%        0    0    0   1];
%
%Q = [0 0 -4 4 0 -4 4 0 -4 4 0 -4 4]*pi/180

deg2rad = pi/180;

%DH parameters of a finger
% DH = {a,alfa,d,theta_min,theta_max}
%
SAHDH = [0     0     0    -15*deg2rad 15*deg2rad;
	 0    -pi/2  0    -4*deg2rad  75*deg2rad;
	 67.8  0     0     4*deg2rad  75*deg2rad;
	 30.0  0     0    4*deg2rad-pi/2  75*deg2rad-pi/2;
	 0    -pi/2  29.5  0          0]; 

    
% general origin
o=[0 0 0 1]';

% REFERENCE FRAMES
% up to the one in the fingertip contact point

% FINGER 1 RING
% transformation matrices
T101=[0 0 1 -4.3; -0.034301 -0.99941 0 -40.165; 0.99941 -0.034301 0 145.43; 0 0 0 1];
T112=DH(SAHDH(1,1),SAHDH(1,2),SAHDH(1,3),1*Q(11));
T123=DH(SAHDH(2,1),SAHDH(2,2),SAHDH(2,3),-1*Q(12));
T134=DH(SAHDH(3,1),SAHDH(3,2),SAHDH(3,3),-1*Q(13));
T145=DH(SAHDH(4,1),SAHDH(4,2),SAHDH(4,3),-1*Q(13)-pi/2);
% phalanges frames in global frame
T11=Tw_h*T101; %base
T12=Tw_h*T101*T112; %abd
T13=Tw_h*T101*T112*T123; %prx
T14=Tw_h*T101*T112*T123*T134; %dst
T15=Tw_h*T101*T112*T123*T134*T145; %dst
C1=Tw_h*T101*T112*T123*T134*T145*[eye(3) [0; 29.5; 0]; 0 0 0 1 ]; %contact
%%phalanges vectors
p1b = T11(1:3,4) - Tw_h(1:3,4); %constant
p14 = T14(1:3,4) - T13(1:3,4); %proximal phalanx
p15 = T15(1:3,4) - T14(1:3,4); %distal phalanx
p1p = C1(1:3,4)-T15(1:3,4); % fingertip (point to contact point)

                                                                
% FINGER 2 MIDDLE
T201=[0 0 1 -4.3; 0 -1 0 0; 1 0 0 150.15; 0 0 0 1];
T212=DH(SAHDH(1,1),SAHDH(1,2),SAHDH(1,3),1*Q(8));
T223=DH(SAHDH(2,1),SAHDH(2,2),SAHDH(2,3),-1*Q(9));
T234=DH(SAHDH(3,1),SAHDH(3,2),SAHDH(3,3),-1*Q(10));
T245=DH(SAHDH(4,1),SAHDH(4,2),SAHDH(4,3),-1*Q(10)-pi/2);
% phalanges frames in global frame
T21=Tw_h*T201;
T22=Tw_h*T201*T212;
T23=Tw_h*T201*T212*T223;
T24=Tw_h*T201*T212*T223*T234;
T25=Tw_h*T201*T212*T223*T234*T245;
C2=Tw_h*T201*T212*T223*T234*T245*[eye(3) [0; 29.5; 0]; 0 0 0 1 ]; %contact
%%phalanges vectors
p2b = T21(1:3,4) - Tw_h(1:3,4);
p24 = T24(1:3,4) - T23(1:3,4);
p25 = T25(1:3,4) - T24(1:3,4);
p2p = C2(1:3,4)-T25(1:3,4);

% FINGER 3 INDEX (FORE)
T301=[0 0 1 -4.3; 0.035485 -0.99937 0 40.165; 0.99937 0.035485 0 145.43; 0 0 0 1];
T312=DH(SAHDH(1,1),SAHDH(1,2),SAHDH(1,3),1*Q(5));
T323=DH(SAHDH(2,1),SAHDH(2,2),SAHDH(2,3),-1*Q(6));
T334=DH(SAHDH(3,1),SAHDH(3,2),SAHDH(3,3),-1*Q(7));
T345=DH(SAHDH(4,1),SAHDH(4,2),SAHDH(4,3),-1*Q(7)-pi/2);
% phalanges frames in global frame
T31=Tw_h*T301;
T32=Tw_h*T301*T312;
T33=Tw_h*T301*T312*T323;
T34=Tw_h*T301*T312*T323*T334;
T35=Tw_h*T301*T312*T323*T334*T345;
C3=Tw_h*T301*T312*T323*T334*T345*[eye(3) [0; 29.5; 0]; 0 0 0 1 ]; %contact
%%phalanges vectors
p3b = T31(1:3,4) - Tw_h(1:3,4);
p34 = T34(1:3,4) - T33(1:3,4);
p35 = T35(1:3,4) - T34(1:3,4);
p3p = C3(1:3,4)-T35(1:3,4);

% FINGER 4 THUMB
T400 = transform(-3, 27.1, 0, 0, 0, -1*Q(1));
T401=[0 -1 0 -9; 0.57358 0 -0.81915 114; 0.81915 0 0.57358 97.0; 0 0 0 1];
T412=DH(SAHDH(1,1),SAHDH(1,2),SAHDH(1,3),1*Q(2));
T423=DH(SAHDH(2,1),SAHDH(2,2),SAHDH(2,3),-1*Q(3));
T434=DH(SAHDH(3,1),SAHDH(3,2),SAHDH(3,3),-1*Q(4));
T445=DH(SAHDH(4,1),SAHDH(4,2),SAHDH(4,3),-1*Q(4)-pi/2);
% phalanges frames in global frame
T40=Tw_h*T400;%base
T41=Tw_h*T400*T401; %cons
T42=Tw_h*T400*T401*T412; %abd
T43=Tw_h*T400*T401*T412*T423; %prx
T44=Tw_h*T400*T401*T412*T423*T434; %dst
T45=Tw_h*T400*T401*T412*T423*T434*T445; %dst
C4=Tw_h*T400*T401*T412*T423*T434*T445*[eye(3) [0; 29.5; 0]; 0 0 0 1 ]; %contact
%%phalanges vectors
p4b = T40(1:3,4) - Tw_h(1:3,4);
p41 = T41(1:3,4) - T40(1:3,4);
p44 = T44(1:3,4) - T43(1:3,4);
p45 = T45(1:3,4) - T44(1:3,4);
p4p = C4(1:3,4)-T45(1:3,4);


% SELECTION MATRICES

%free model
Hn = zeros(6,6);
%frictionless model
Hpwof = [ [1 0 0 ; zeros(2,3)] zeros(3,3); zeros(3,6) ];
%hard friction model
Hhf = [eye(3) zeros(3,3); zeros(3,6)];
%soft friction model
Hsf = [eye(3) zeros(3,3); zeros(3,3) [1 0 0 ; zeros(2,3)] ];
%rigid model
Hr = eye(6);

H1 = Hhf;
H2 = Hhf;
H3 = Hhf;
H4 = Hhf;

H = blkdiag(H4,H3,H2,H1);

% ROTATION MATRICES

R1 = blkdiag(C1(1:3,1:3),C1(1:3,1:3));
R2 = blkdiag(C2(1:3,1:3),C2(1:3,1:3));
R3 = blkdiag(C3(1:3,1:3),C3(1:3,1:3));
R4 = blkdiag(C4(1:3,1:3),C4(1:3,1:3));

% HAND JACOBIAN (w.r.t. the world)

Z1 = [zeros(3,10) transpose(skew(C1(1:3,4)-T12(1:3,4)))*T12(1:3,3) transpose(skew(C1(1:3,4)-T13(1:3,4)))*T13(1:3,3) transpose(skew(C1(1:3,4)-T14(1:3,4)))*T14(1:3,3);
      zeros(3,10) T12(1:3,3) T13(1:3,3) T14(1:3,3)];
  
Z2 = [zeros(3,7) transpose(skew(C2(1:3,4)-T22(1:3,4)))*T22(1:3,3) transpose(skew(C2(1:3,4)-T23(1:3,4)))*T23(1:3,3) transpose(skew(C2(1:3,4)-T24(1:3,4)))*T24(1:3,3) zeros(3,3);
      zeros(3,7) T22(1:3,3) T23(1:3,3) T24(1:3,3) zeros(3,3)];
  
Z3 = [zeros(3,4) transpose(skew(C3(1:3,4)-T32(1:3,4)))*T32(1:3,3) transpose(skew(C3(1:3,4)-T33(1:3,4)))*T33(1:3,3) transpose(skew(C3(1:3,4)-T34(1:3,4)))*T34(1:3,3) zeros(3,6);
      zeros(3,4) T32(1:3,3) T33(1:3,3) T34(1:3,3) zeros(3,6)];
  
Z4 = [transpose(skew(C4(1:3,4)-T40(1:3,4)))*T40(1:3,3) transpose(skew(C4(1:3,4)-T42(1:3,4)))*T42(1:3,3) transpose(skew(C4(1:3,4)-T43(1:3,4)))*T43(1:3,3) transpose(skew(C4(1:3,4)-T44(1:3,4)))*T44(1:3,3) zeros(3,9);
      T40(1:3,3) T42(1:3,3) T43(1:3,3) T44(1:3,3) zeros(3,9)];

% the ordering correspond with vector of joint values, but the subindex
% refers to the finger
J = H*[transpose(R4)*Z4 ; transpose(R3)*Z3; transpose(R2)*Z2; transpose(R1)*Z1]; 


% HAND-DEPENDENT GRASP MATRIX (w.r.t. the world)

P1 = [eye(3) zeros(3,3); skew(C1(1:3,4)) eye(3)];
P2 = [eye(3) zeros(3,3); skew(C2(1:3,4)) eye(3)];
P3 = [eye(3) zeros(3,3); skew(C3(1:3,4)) eye(3)];
P4 = [eye(3) zeros(3,3); skew(C4(1:3,4)) eye(3)];

G = [P4*R4 P3*R3 P2*R2 P1*R1]*transpose(H);


if p==1
% Plot the configuration

    s=10;
    plotframe(Tw_h,s);    
    plotframe(T11,s);
    plotframe(T12,s);
    plotframe(T13,s);
    plotframe(T14,s);
    plotframe(T15,s);
    plotframe(C1,s);
    plotframe(T21,s);
    plotframe(T22,s);
    plotframe(T23,s);
    plotframe(T24,s);
    plotframe(T25,s);
    plotframe(C2,s);
    plotframe(T31,s);
    plotframe(T32,s);
    plotframe(T33,s);
    plotframe(T34,s);
    plotframe(T35,s);
    plotframe(C3,s);
    plotframe(T40,s);    
    plotframe(T41,s);
    plotframe(T42,s);
    plotframe(T43,s);
    plotframe(T44,s);
    plotframe(T45,s);
    plotframe(C4,s);

    quiver3(Tw_h(1,4),Tw_h(2,4),Tw_h(3,4),p1b(1),p1b(2),p1b(3),1,'color',[1 0 1]);
    quiver3(T13(1,4),T13(2,4),T13(3,4),p14(1),p14(2),p14(3),1,'color',color);
    quiver3(T14(1,4),T14(2,4),T14(3,4),p15(1),p15(2),p15(3),1,'color',color);
    quiver3(T15(1,4),T15(2,4),T15(3,4),p1p(1),p1p(2),p1p(3),1,'color',color);
    
    quiver3(Tw_h(1,4),Tw_h(2,4),Tw_h(3,4),p2b(1),p2b(2),p2b(3),1,'color',[1 0 1]);    
    quiver3(T23(1,4),T23(2,4),T23(3,4),p24(1),p24(2),p24(3),1,'color',color);
    quiver3(T24(1,4),T24(2,4),T24(3,4),p25(1),p25(2),p25(3),1,'color',color);
    quiver3(T25(1,4),T25(2,4),T25(3,4),p2p(1),p2p(2),p2p(3),1,'color',color);
    
    quiver3(Tw_h(1,4),Tw_h(2,4),Tw_h(3,4),p3b(1),p3b(2),p3b(3),1,'color',[1 0 1]);
    quiver3(T33(1,4),T33(2,4),T33(3,4),p34(1),p34(2),p34(3),1,'color',color);
    quiver3(T34(1,4),T34(2,4),T34(3,4),p35(1),p35(2),p35(3),1,'color',color);
    quiver3(T35(1,4),T35(2,4),T35(3,4),p3p(1),p3p(2),p3p(3),1,'color',color);
    
    quiver3(Tw_h(1,4),Tw_h(2,4),Tw_h(3,4),p4b(1),p4b(2),p4b(3),1,'color',[1 0 1]);
    quiver3(T40(1,4),T40(2,4),T40(3,4),p41(1),p41(2),p41(3),1,'color',color);
    quiver3(T43(1,4),T43(2,4),T43(3,4),p44(1),p44(2),p44(3),1,'color',color);
    quiver3(T44(1,4),T44(2,4),T44(3,4),p45(1),p45(2),p45(3),1,'color',color);
    quiver3(T45(1,4),T45(2,4),T45(3,4),p4p(1),p4p(2),p4p(3),1,'color',color);
end







