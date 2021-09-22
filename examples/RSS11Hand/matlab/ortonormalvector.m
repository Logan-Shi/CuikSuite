function v = ortonormalvector(n,z)
%
% function v = ortonormalvector(n,z)
%
% given any 3D vector n, it provides an arbitrary orthogonal and normal vector
% with the last component equal to the given z/norm(v)
%

[m i]=max(abs(n));

ndx=[1 2 3];
ndx(i)=[];
j=ndx(1);
k=ndx(2);

v(j)=1;
v(k)=1;
v(i)=-(n(k)+n(j))/n(i);

v=v'/norm(v);
