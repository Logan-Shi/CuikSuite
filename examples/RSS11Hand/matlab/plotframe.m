function plotframe(T,s)
%function plotframe(T,s)
%
%Plots a frame defined by T
%T is a 4x4 homogeneous transformation matrix, a frame seen from another
%s is the scale for unit vectors

quiver3(T(1,4),T(2,4),T(3,4),T(1,1),T(2,1),T(3,1),s,'r')
hold on
quiver3(T(1,4),T(2,4),T(3,4),T(1,2),T(2,2),T(3,2),s,'g')
quiver3(T(1,4),T(2,4),T(3,4),T(1,3),T(2,3),T(3,3),s,'b')
