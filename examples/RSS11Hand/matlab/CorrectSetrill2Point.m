% Ensures that the given point is on the setrill
% Parametres
%   id: Contact number. Each contact is on a different part of the setrill
%       on a surface defined by different constraints.
%   pol: Approximated point on the setrill
%
% Outputs
%   po1: Exact point on the setrill
%   no: (not-normalized) normal vector on pol.
%   minP maxP: min/Max coordinates for any point on the setrill (in x,y,z)
%   minN maxN: min/Max coordinates for any noorma on the setrill (in x,y,z)
%   par: Parameters defining the surface on the setrill (the cone
%         parameters in this case).
%
function [pol no minP maxP minN maxN par]=CorrectSetrill2Point(id,pol)

  % we could select the cone according to pol(2) ... in this way we could
  % even find out if two fingers are in the same cone or even use the
  % cylinder equations in some parts of the setrill
  switch id
      case 1
        x1=-50; % large cone for the low part of the setrill
        y1=-100;
        x2=-10;
        y2=0;
      case 2
        x1=0; % small cone on the top of the setrill
        y1=100;
        x2=8.5;
        y2=91.5;
      case 3
        x1=10; % medium cone at the center of the setrill
        y1=20;
        x2=23;
        y2=40;
      otherwise
          error('Unknown contact point in CorrectSetrillPoint');
  end
  
  [x0 y0 c]=ConeConstants(x1,y1,x2,y2);
  % fprintf('Cone parametes: x0=%f y0=%f\n',x0,y0);
  
  par=[x0 y0 c];
  
  x=pol(1);y=pol(2);z=pol(3);
  % fprintf('Coordinates on object: [%f %f %f]\n',x,y,z);
  
  % e=x^2+z^2-c^2*(y-y0)^2;
  % fprintf('Error in cone %.12f\n',e);
  
  % correcting cone
  x=sign(x)*sqrt(abs(c^2*(y-y0)^2-z^2));
  pol(1)=x;
  
  % fprintf('Corrected coordinates on object: [%.12f %.12f %.12f]\n',x,y,z);
  
  R=max(abs([x1 x2]))+1;
  
  minP=[-R min(y1,y2) -R];
  maxP=[ R max(y1,y2)  R];
    
  % Normal in object
  no=[pol(1) -c^2*(pol(2)-y0) pol(3)]';
  
  minN=[minP(1) min(-c^2*(minP(2)-y0),-c^2*(maxP(2)-y0)) minP(3)];
  maxN=[maxP(1) max(-c^2*(minP(2)-y0),-c^2*(maxP(2)-y0)) maxP(3)];
  
end

% Auxiliary function defining the cone parameters from 4 points on the cone
function [x0 y0 c]=ConeConstants(x1,y1,x2,y2)
  dx=x2-x1;
  dy=y2-y1;
  x0=x1-y1*dx/dy; % r
  y0=y1-x1*dy/dx; % h
  c=abs(x0)/abs(y0); % r/h
end