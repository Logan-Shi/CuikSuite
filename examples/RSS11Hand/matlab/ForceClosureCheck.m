function [d1,d2] = ForceClosureCheck(J,G,H1,H2,H3,Ng,mu,nc,N)

% nc is the number of contacts

n1 = N(1:3,1);
n2 = N(1:3,2);
n3 = N(1:3,3);

[m,n] = size(G);
[mj,nj] = size(J);

% STEP 1: rank(G) = nv (6 in 3D general case)

if not(rank(G) == 6)
    % this is not force closure.
    d1 = 0;
    d2 = -1; % this is a code to know that it exited by the rank condition
    return;
end

% STEP 2: solve for frictional form closure

% friction cone approximation

S1 = GenerateAproximatedCone(Ng,mu,n1);
S2 = GenerateAproximatedCone(Ng,mu,n2);
S3 = GenerateAproximatedCone(Ng,mu,n3);

% face constraint formulation

% construction of F1
for i=1:Ng
    F1(i,:) = transpose(cross(S1(:,i),S1(:,i+1)));
end

% construction of F2
for i=1:Ng
    F2(i,:) = transpose(cross(S2(:,i),S2(:,i+1)));
end

% construction of F3
for i=1:Ng
    F3(i,:) = transpose(cross(S3(:,i),S3(:,i+1)));
end

F = blkdiag(F1,F2,F3);

[mf, nf] = size(F);

e1 = H1(1,1:3);
e2 = H2(1,1:3);
e3 = H3(1,1:3);

e = [ e1 e2 e3 ];
%e = [0 0 1 0 0 1 0 0 1 ];

E = blkdiag(e1,e2,e3);

[me, ne] = size(E);

% PROBLEM ADAPTATION
%
% X = [lambda ; d];
%
% f = [0 ; -1];
% 
% [G 0] * [lambda ; d] = 0
% 
% [-F +1]*[lambda ; d] <= 0
% 
% [0 -1]* [lambda ; d] <= 0
% 
% [e 0]*[lambda ; d] <= nc

options = optimset('LargeScale', 'off', 'Simplex', 'on','MaxIter',500,'Display','off');
f = [zeros(n,1) ; -1];
A = [-F ones(mf,1); zeros(1,nf) -1 ;  e 0 ];
b = [ zeros(mf,1) ; 0 ; nc];
Aeq = [G zeros(m,1)];
beq = zeros(m,1); 
lb = [ -Inf(nf,1) ; 0];  %
ub = [  Inf(nf,1) ; Inf]; % 
X0 = []; 

[X, fval,exitflag,output] = linprog(f,A,b,Aeq,beq,lb,ub,X0,options);

if (exitflag==1)
d1 = X(nf+1);
%elseif (exitflag==0)
%d1 = -1; % just a code to know if there were at least that ran out of iterations
else
d1 = 0;
end


% STEP 3:solve for internal force control

% PROBLEM ADAPTATION
%
% X = [lambda ; d];
%
% f = [0 ; -1];
% 
% [G 0] * [lambda ; d] = 0
%
% [Jt 0] * [lambda ; d] = 0
% 
% [-E +1]*[lambda ; d] <= 0
% 
% [0 -1]* [lambda ; d] <= 0
% 
% [e 0]*[lambda ; d] <= nc

options = optimset('LargeScale', 'off', 'Simplex', 'on','MaxIter',500,'Display','off');
f = [zeros(n,1) ; -1];
A = [-E ones(me,1);  zeros(1,ne) -1 ; e 0 ];
b = [ zeros(me,1);  0; nc ];
Aeq = [G zeros(m,1) ; transpose(J) zeros(nj,1)];
beq = zeros(m+nj,1);
lb = [-Inf(nf,1);0];
ub = [Inf(nf,1);Inf];

[X, fval,exitflag,output] = linprog(f,A,b,Aeq,beq,lb,ub,X0,options);

if (exitflag==1)
d2 = X(nf+1);
else
d2 = -2; %% this is a code to know that the simplex didn't converged to a solution
end



