% Ensures that the given point is on the screwdriver
% Parametres
%   id: Contact number. Each contact is on a different part of the tornavis
%       on a surface defined by different constraints.
%   pol: Approximated point on the can
%
% Outputs
%   po1: Exact point on the screwdriver
%   no: (not-normalized) normal vector on pol.
%   minP/maxP: min/Max coordinates for any point on the tornavis (in x,y,z)
%   minN/maxN: min/Max coordinates for any noorma on the tornavis (in x,y,z)
%   par: Parameters defining the surface on the tornavis (either the radius of 
%        the cylinder in the body, or the plane in the top).
%
function [pol no minP maxP minN maxN par]=CorrectTornavis2Point(id,pol)

if (id==2) || (id==3)

        % Radius of the tornavis body (the tornavis is aligned along the Y axis!!)
        % Same parameter for contact points 1 and 3.
        R=3.81;
      
        % contact in the body of the tornavis, a cylinder correction

        x=pol(1);y=pol(2);z=pol(3);
        % fprintf('Coordinates on object: [%f %f %f]\n',x,y,z);
  
        % e=x^2+z^2-R^2;
        % fprintf('Error in cylinder %.12f\n',e);
  
        % correcting cylinder
        x=sign(x)*sqrt(abs(R^2-z^2));
        pol(1)=x;
        % fprintf('Corrected coordinates on object: [%.12f %.12f %.12f]\n',x,y,z);
  
        minP=[-R-1 -63 -R-1];
        maxP=[ R+1  17  R+1];

        % Normal in object reference frame
        no=[pol(1) 0 pol(3)]';
  
        minN=[-R-1 0 -R-1];
        maxN=[ R+1 0  R+1];
          
        par=R;
      
else
  
  if (id==1) % contact in the top of the tornavis, a plane correction (the plane is orthogonal to the Y axis)
              
    x=pol(1);y=pol(2);z=pol(3);
    % fprintf('Coordinates on object: [%f %f %f]\n',x,y,z);
    
    
    % correcting plane
    y=-90.167;
    pol(2)=y;
    
    %fprintf('Corrected coordinates on object: [%.12f %.12f %.12f]\n',x,y,z);   

    % The contact point is fixed
    minP=[-10 y -10];
    maxP=[ 10 y  10];
    
    % Normal in object
    no=[0 -1 0]';
    
    minN=[0 -1 0];
    maxN=[0 -1 0];
    
    par=y;
    
  else
    error('Unknown contact point in CorrectTornavis2Point');
  end

end