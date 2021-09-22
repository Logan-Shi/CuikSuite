% Prints the equations defining a point on the can and its
% corresponding normal. 
% Moreover, for one of the contact points we fix the contact point on the
% can so that it can not rotate while being held.
%
% The equations are added to the file given by 'fid'
%
function PrintTornavisEqs(fid,id,pol)

if (id==1) || (id==3)

  % Equation for the cylinder defining the object
  fprintf(fid,'  %% Points on the object must be on the cylinder \n');
  fprintf(fid,'  o_%u_x^2+o_%u_z^2-p_1_%u^2=0;\n\n',id,id,id);
  
  % Equations defining the normal (in local coordinates)
  fprintf(fid,'  %% (Not normalized) Normal on the object \n');
  fprintf(fid,'  o_%u_x-no_%u_x=0;\n',id,id); 
  fprintf(fid,'  no_%u_y=0;\n',id);
  fprintf(fid,'  o_%u_z-no_%u_z=0;\n\n',id,id); 

  if (id==1)
    % Fix the object rotation around the y axis
    fprintf(fid,'  %% Equations to fix object rotation\n');
    fprintf(fid,'    %.16f*o_%u_x%+.16f*o_%u_z=0;\n\n',pol(3),id,-pol(1),id);
  end

else

  if (id==2)
    fprintf(fid,'  %% Points on the object must be on the plane \n');
    fprintf(fid,'  o_%u_x*p_1_%u+o_%u_y*p_2_%u+o_%u_z*p_3_%u+p_4_%u=0;\n\n',id,id,id,id,id,id,id);
    
    % Equations defining the normal (in local coordinates)
    fprintf(fid,'  %% (Not normalized) Normal on the object \n');
    fprintf(fid,'  no_%u_x=0;\n',id);
    fprintf(fid,'  no_%u_y=-1;\n',id);
    fprintf(fid,'  no_%u_z=0;\n\n',id);
  else
    error('Unknown contact point in PrintTornavisEqs');
  end
  
end
