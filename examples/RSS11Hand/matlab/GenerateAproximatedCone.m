function [S] = GenerateAproximatedCone(Ng,mu,n)

%alpha = atan(mu);



%t = ortonormalvector(n,1);
%w = cross(n,t);
%R = [n t w];


S = zeros(3,Ng);

%Ty = transform(0,0,0,0,alpha,0);
%Tx = transform(0,0,0,2*pi/Ng,0,0);

%Ry = Ty(1:3,1:3);
%Rx = Tx(1:3,1:3);

%S1 = eye(3);

for i=1:Ng+1, %the last column should be exactly as the first one, this facilitates the calculation of the face normals
%    R = R*Rx;
%    S1 = R*Ry;
     S(1:3,i) =  [1; mu*cos(2*pi*i/Ng) ; mu*sin(2*pi*i/Ng)] ; %S1(1:3,1);%
end


% 
% quiver3(0,0,0,n(1),n(2),n(3),'b');
% hold on;
% for i=1:Ng,
%     quiver3(0,0,0,S(1,i),S(2,i),S(3,i),'r');
% end


