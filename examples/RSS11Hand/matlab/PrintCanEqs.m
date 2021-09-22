% Prints the equations defining a point on the can and its
% corresponding normal. 
% Moreover, for one of the contact points we fix the contact point on the
% can so that it can not rotate while being held.
%
% The equations are added to the file given by 'fid'
%
function PrintCanEqs(fid,id,pol)

  % Equation for the cylinder defining the object
  fprintf(fid,'  %% Points on the object must be on the cylinder \n');
  fprintf(fid,'  o_%u_x^2+o_%u_z^2-p_1_%u^2=0;\n\n',id,id,id);
  
  % Equations defining the normal (in local coordinates)
  fprintf(fid,'  %% (Not normalized) Normal on the object \n');
  fprintf(fid,'  o_%u_x-no_%u_x=0;\n',id,id); 
  fprintf(fid,'  no_%u_y=0;\n',id);
  fprintf(fid,'  o_%u_z-no_%u_z=0;\n\n',id,id); 
  
  if id==1
    % Fix the object rotation and translation around the y axis
    fprintf(fid,'  %% Equations to fix object rotation and translation\n');  
    fprintf(fid,'    o_%u_x=%.16f;\n',id,pol(1));
    fprintf(fid,'    o_%u_y=%.16f;\n',id,pol(2));
    fprintf(fid,'    o_%u_z=%.16f;\n\n',id,pol(3));
  end