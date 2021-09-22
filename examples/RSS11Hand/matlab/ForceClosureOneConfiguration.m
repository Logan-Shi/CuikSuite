function [d1,d2]=ForceClosureOneConfiguration(J,G,n1,n2,n3)

% FORCE CLOSURE SCRIPT
 % write in workspace d1 and d2 associated to force closure evaluation.
 %
 % if d1=0, then frictional form closure does not exists, and if d1>0, then it does,
 % with d1 a measure of how far is from losing the closureness. 
 %
 % if d2>0, then internal forces are not controllable, and if d2=0, the it does.
 %
 % Configuration i is force closure if rank(G)=nv, d1>0 and d2=0.
 %
 % The labeling of being or not a configuraion with force closure is done
 % outside the function, this routine provides just the mere evaluation.-
    
  
    % SELECTION MATRICES
    
    %free model
    Hn = zeros(6,6);
    %frictionless model
    Hpwof =  [1 0 0  zeros(1,3)] ; 
    %hard friction model
    Hhf = [eye(3) zeros(3,3)];%; zeros(3,6)];
    %soft friction model
    Hsf = [eye(3) zeros(3,3); zeros(1,3) 1 0 0];
    %rigid model
    Hr = eye(6);

    H1 = Hhf;
    H2 = Hhf;
    H3 = Hhf;

    H = blkdiag(H1,H2,H3);
 
 
    % Applying selection matrices     

    % full jacobian in the contact frame
    J = H*J;
    
    % full grasp matrix
    Gt = H*G'; % the "t" is for transposed, just to keep nomenclature
    G = Gt';   

% PARAMETERS FOR THE FORCE CLOSURE CHECK

% friction cone caracteristics
Ng = 30; % number of generators
mu = 1; % tangent of the friction coefficient

% height of the cone, it is not really critical, just for plotting the real cone
h = 50; 
L = 200;
%gcl_cone('examples/RSS11Hand/bodies/cone1.off',c1(1),c1(2),c1(3),n1(1),n1(2),n1(3),mu,Ng,h);
%gcl_cone('examples/RSS11Hand/bodies/cone2.off',c2(1),c2(2),c2(3),n2(1),n2(2),n2(3),mu,Ng,h);
%gcl_cone('examples/RSS11Hand/bodies/cone3.off',c3(1),c3(2),c3(3),n3(1),n3(2),n3(3),mu,Ng,h);
%gcl_cone('examples/RSS11Hand/bodies/cone1n.off',c1(1),c1(2),c1(3),-n1(1),-n1(2),-n1(3),mu,Ng,h);
%gcl_cone('examples/RSS11Hand/bodies/cone2n.off',c2(1),c2(2),c2(3),-n2(1),-n2(2),-n2(3),mu,Ng,h);
%gcl_cone('examples/RSS11Hand/bodies/cone3n.off',c3(1),c3(2),c3(3),-n3(1),-n3(2),-n3(3),mu,Ng,h);
%gcl_plane('examples/RSS11Hand/bodies/plane.off',c1,c2,c3,L);


nc = 3; % number of contacts
N = [n1 n2 n3];

[d1,d2] = ForceClosureCheck(J,G,H1,H2,H3,Ng,mu,nc,N);

   
    

