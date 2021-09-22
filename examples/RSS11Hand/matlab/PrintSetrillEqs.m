% Prints the equations defining a point on the setrill and its
% corresponding normal. 
% Moreover, for one of the contact points we fix the contact point on the
% setrill so that it can not rotate while being held.
%
% The equations are added to the file given by 'fid'
%
function PrintSetrillEqs(fid,id,pol)

  % Equation for the cone defining the object
  fprintf(fid,'  %% Points on the object must be on the cone \n');
  fprintf(fid,'    o_%u_x^2+o_%u_z^2-p_3_%u^2*o_%u_y^2+2*p_3_%u^2*p_2_%u*o_%u_y-p_3_%u^2*p_2_%u^2=0;\n\n',id,id,id,id,id,id,id,id,id);
  
  % Equations defining the normal
  fprintf(fid,'  %% (Not normalized) Normal on the object \n');
  fprintf(fid,'    o_%u_x-no_%u_x=0;\n',id,id); 
  fprintf(fid,'    -p_3_%u^2*o_%u_y+p_3_%u^2*p_2_%u-no_%u_y=0;\n',id,id,id,id,id); 
  fprintf(fid,'    o_%u_z-no_%u_z=0;\n\n',id,id); 
  
  if (id==1)
    % Fix the object rotation around the y axis
    fprintf(fid,'  %% Equations to fix object rotation\n');    
    fprintf(fid,'    %.16f*o_%u_x%+.16f*o_%u_z=0;\n\n',pol(3),id,-pol(1),id);
  end
  