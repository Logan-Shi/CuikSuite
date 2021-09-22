% Ensures that the given point is on the can
% Parametres
%   id: Contact number. 
%   pol: Approximated point on the can
%
% Outputs
%   po1: Exact point on the can
%   no: (not-normalized) normal vector on pol.
%   minP/maxP: min/Max coordinates for any point on the can (in x,y,z)
%   minN/maxN: min/Max coordinates for any noorma on the can (in x,y,z)
%   par: Parameters defining the surface on the can (the radius of the
%        cylinder in this case).
%
function [pol no minP maxP minN maxN par]=CorrectCan2Point(id,pol)

  % Radius of the can (can is aligned along the Y axis!!)
  % Same parameter for all contact points
  R=22.24;
  
  x=pol(1);y=pol(2);z=pol(3);
  % fprintf('Coordinates on object: [%f %f %f]\n',x,y,z);
  
  % e=x^2+z^2-R^2;
  % fprintf('Error in cylinder %.12f\n',e);
  
  % correcting cylinder
  x=sign(x)*sqrt(abs(R^2-z^2));
  pol(1)=x;
  % fprintf('Corrected coordinates on object: [%.12f %.12f %.12f]\n',x,y,z);
  
  minP=[-R-1 -37 -R-1];
  maxP=[ R+1  27  R+1];
  
  
  % Normal in object reference frame
  no=[pol(1) 0 pol(3)]';
  
  minN=[-R-1 0 -R-1];
  maxN=[ R+1 0  R+1];
  
  par=R;
