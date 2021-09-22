% Input parameters
%   po1,po2,po3: Contact points on the object in global coordinates
%   To: Transform for the object.
%   T1,T2,T3. Transforms for the contact links
%
function GeneratePointsSetrill()

  % Object pose
  To=[0.890660733092 -0.454668514994 0.000000000000 103.398000000000 
      0.052079713205 0.102020161971 -0.993418134535 29.507000000000 
      0.451675947998 0.884798523973 0.114544358115 162.512000000000 
      0.000000000000 0.000000000000 0.000000000000 1.000000000000 ];
  
  % First contact point p24-object
  p1=[116.170806884766 10.212795257568 148.584259033203 1]';
  T1=[0.918312521966 -0.000000000000 -0.395856175902 91.432149038060 
      0.000000000000 -1.000000000000 0.000000000000 0.000000000000 
     -0.395856175902 0.000000000000 -0.918312521966 167.506748586575 
     0.000000000000 0.000000000000 0.000000000000 1.000000000000 ];
  x1_1=-50; % large cone for the low part of the setrill
  y1_1=-100;
  x2_1=-10;
  y2_1=0;
  l1name='p24';
  
  % Second contact point p34-object
  p2=[56.956134796143 38.639499664307 247.560806274414 1]';
  T2=[0.762906095334 -0.000000000000 0.646509311380 24.747243714601 
     -0.022941387708 -0.999370208806 0.027071728449 37.026758228788 
      0.646102145509 -0.035485007414 -0.762425623794 233.812828769802 
      0.000000000000 0.000000000000 0.000000000000 1.000000000000 ];
  x1_2=0; % small cone on the top of the setrill
  y1_2=100;
  x2_2=8.5;
  y2_2=91.5; 
  l2name='p34';
  
  % Third contact point p44-object
  p3=[101.796264648438 44.733097076416 198.509933471680 1]';
  T3=[-0.091381736171 -0.249723495895 -0.963995619229 116.196687498353 
      -0.421640669886 0.886691727004 -0.189728560738 59.838151169233 
       0.902146619897 0.389122033377 -0.186321011558 173.382573070964 
       0.000000000000 0.000000000000 0.000000000000 1.000000000000 ];
  x1_3=10; % medium cone at the center of the setrill
  y1_3=20;
  x2_3=23;
  y2_3=40;
  l3name='p44';
  
  % Generate the equations for each contact point

  fprintf('--------------------------------------------------------------\n');
  fprintf('--------------------------------------------------------------\n');
  GenerateContactEqs(1,p1,To,x1_1,y1_1,x2_1,y2_1,T1,l1name);
  fprintf('--------------------------------------------------------------\n');
  fprintf('--------------------------------------------------------------\n');
  GenerateContactEqs(2,p2,To,x1_2,y1_2,x2_2,y2_2,T2,l2name);
  fprintf('--------------------------------------------------------------\n');
  fprintf('--------------------------------------------------------------\n');
  GenerateContactEqs(3,p3,To,x1_3,y1_3,x2_3,y2_3,T3,l3name);
  fprintf('--------------------------------------------------------------\n');
  fprintf('--------------------------------------------------------------\n');
  
end

% Parameters
%  id: Identifier of the contact (1,2,3)
%  po: Contact point in global coordinates
%  To: Pose of the object
%  x1,y1,x2,y2: Points on a line defining the cone on the object
%  Tl: Pose of the link in contact with the object.
%  link: String identifying the link.
function GenerateContactEqs(id,po,To,x1,y1,x2,y2,Tl,link)
  fprintf('Contact constants, variables, and equations for contact object -- %s\n\n',link);
  [x0 y0 c]=ConeConstants(x1,y1,x2,y2);
  % fprintf('Cone parametes: x0=%f y0=%f\n',x0,y0);

  % Coordinates in local of object
  pol=To\po; 
    
  x=pol(1);y=pol(2);z=pol(3);
  
  % fprintf('Coordinates on object: [%f %f %f]\n',x,y,z);
  
  % e=x^2+z^2-c^2*(y-y0)^2;
  % fprintf('Error in cone %.12f\n',e);
  
  % correcting cone
  x=sign(x)*sqrt(abs(c^2*(y-y0)^2-z^2));
  pol(1)=x;
  
  % fprintf('Corrected coordinates on object: [%.12f %.12f %.12f]\n',x,y,z);
  
  % Normal in object
  no=[pol(1) -c^2*(pol(2)-y0) pol(3)]';
  
  % Coordinates in local of link
  pl=Tl\(To*pol);
  
  % Normal in link
  Ro=To(1:3,1:3);
  Rl=Tl(1:3,1:3);
  nl=Rl\(Ro*no);
  nl=nl/norm(nl);
  
  fprintf('%% Constants to add for contact %u\n',id);
  fprintf('  f_%u_x:=%.12f\n',id,pl(1)); % point in link (in local)
  fprintf('  f_%u_y:=%.12f\n',id,pl(2));
  fprintf('  f_%u_z:=%.12f\n\n',id,pl(3));
  fprintf('  n_%u_x:=%.12f\n',id,nl(1)); % normal in link (in local)
  fprintf('  n_%u_y:=%.12f\n',id,nl(2));
  fprintf('  n_%u_z:=%.12f\n\n',id,nl(3));
  fprintf('  c_%u:=%.12f\n',id,c);  % object parameters
  fprintf('  x0_%u:=%.12f\n',id,x0);
  fprintf('  y0_%u:=%.12f\n\n',id,y0);
  
  % Add three variables for the position of the contact point on the
  % object and corresponding normal
  
  fprintf('%% Variables to add for contact %u\n',id);
  fprintf('  o_%u_x:[%.12f,%.12f]\n',id,min(x1,x2),max(x1,x2));
  fprintf('  o_%u_y:[%.12f,%.12f]\n',id,min(y1,y2),max(y1,y2));
  fprintf('  o_%u_z:[%.12f,%.12f]\n\n',id,min(x1,x2),max(x1,x2));
  
  m=max(abs([x1,x2,c*y1,c*y2]));
  fprintf('  no_%u_x:[%.12f,%.12f]\n',id,-m,m);
  fprintf('  no_%u_y:[%.12f,%.12f]\n',id,-m,m);
  fprintf('  no_%u_z:[%.12f,%.12f]\n\n',id,-m,m);
  
  fprintf('  l_%u:[0,%.12f]\n\n',id,sqrt(3*m^2));
    
  fprintf('%% Equations to add for contact %u\n',id);
  
  % Equation for the cone defining the object
  fprintf('  %% Points on the object must be on the cone \n');
  fprintf('    o_%u_x^2+o_%u_z^2-c_%u^2*o_%u_y^2+2*c_%u^2*y0_%u*o_%u_y-c_%u^2*y0_%u^2=0;\n\n',id,id,id,id,id,id,id,id,id);
  
  % Equations defining the normal
  fprintf('  %% (Not normalized) Normal on the object \n');
  fprintf('    o_%u_x-no_%u_x=0;\n',id,id); 
  fprintf('    -c^2*o_%u_y+c^2*y0_%u-no_%u_y=0;\n',id,id,id); 
  fprintf('    o_%u_z-no_%u_z=0;\n\n',id,id); 
  
  % Equation defining the squared norm of the normal
  fprintf('  %% Squared norm of the normal on the object \n');
  fprintf('    no_%u_x^2+no_%u_y^2+no_%u_z^2-l_%u^2=0;\n\n',id,id,id,id);
  
  % Points on the link and on the object must coincide
  fprintf('  %% Points in finger and in object must coincide \n');
  fprintf('    object_u_x*o_%u_x +object_v_x*o_%u_y +object_w_x*o_%u_z -object_wp_x*o_%u_z +object_r_x\n',id,id,id,id);
  fprintf('     -%s_u_x*f_%u_x -%s_v_x*f_%u_y -%s_w_x*f_%u_z +%s_wp_x*f_%u_z -%s_r_x=0;\n',link,id,link,id,link,id,link,id,link);
  fprintf('    object_u_y*o_%u_x +object_v_y*o_%u_y +object_w_y*o_%u_z -object_wp_y*o_%u_z +object_r_y\n',id,id,id,id);
  fprintf('     -%s_u_y*f_%u_x -%s_v_y*f_%u_y -%s_w_y*f_%u_z +%s_wp_y*f_%u_z -%s_r_y=0;\n',link,id,link,id,link,id,link,id,link);
  fprintf('    object_u_z*o_%u_x +object_v_z*o_%u_y +object_w_z*o_%u_z -object_wp_z*o_%u_z +object_r_z\n',id,id,id,id);
  fprintf('     -%s_u_z*f_%u_x -%s_v_z*f_%u_y -%s_w_z*f_%u_z +%s_wp_z*f_%u_z -%s_r_z=0;\n\n',link,id,link,id,link,id,link,id,link);
  
  % Normals on the link and on the object must coincide
  fprintf('  %% Normals in finger and in object must be aligned \n');
  fprintf('    object_u_x*no_%u_x +object_v_x*no_%u_y +object_w_x*no_%u_z -object_wp_x*no_%u_z\n',id,id,id,id);
  fprintf('     -%s_u_x*n_%u_x*l_%u -%s_v_x*n_%u_y*l_%u -%s_w_x*n_%u_z*l_%u +%s_wp_x*n_%u_z*l_%u=0;\n',link,id,id,link,id,id,link,id,id,link,id,id);
  fprintf('    object_u_y*no_%u_x +object_v_y*no_%u_y +object_w_y*no_%u_z -object_wp_y*no_%u_z\n',id,id,id,id);
  fprintf('     -%s_u_y*n_%u_x*l_%u -%s_v_y*n_%u_y*l_%u -%s_w_y*n_%u_z*l_%u +%s_wp_y*n_%u_z*l_%u=0;\n',link,id,id,link,id,id,link,id,id,link,id,id);
  fprintf('    object_u_z*no_%u_x +object_v_z*no_%u_y +object_w_z*no_%u_z -object_wp_z*no_%u_z\n',id,id,id,id);
  fprintf('     -%s_u_z*n_%u_x*l_%u -%s_v_z*n_%u_y*l_%u -%s_w_z*n_%u_z*l_%u +%s_wp_z*n_%u_z*l_%u=0;\n\n',link,id,id,link,id,id,link,id,id,link,id,id);
  
  if id==2
    % Fix the object rotation around the y axis
    fprintf('  %% Equations to fix object rotation\n');    
    fprintf('    %.12f*o_%u_x-%.12f*o_%u_z=0;\n\n',pol(3),id,pol(1),id);
  end
  
  fprintf('%% Solution for o_%u, no_%u and l_%u\n',id,id,id);
  fprintf('  o_%u =(%.12f,%.12f,%.12f)\n',id,pol(1),pol(2),pol(3));
  fprintf('  no_%u=(%.12f,%.12f,%.12f)\n',id,no(1),no(2),no(3));
  fprintf('  l_%u=%.12f\n\n',id,norm(no));
  
  fprintf('%% Solution for o_%u, no_%u, and l_%u in box form\n',id,id,id);
  fprintf('  o_%u_x:[%.12f,%.12f] o_%u_y:[%.12f,%.12f] o_%u_z:[%.12f,%.12f]\n',id,pol(1),pol(1),id,pol(2),pol(2),id,pol(3),pol(3));
  fprintf('  no_%u_x:[%.12f,%.12f] no_%u_y:[%.12f,%.12f] no_%u_z:[%.12f,%.12f]\n',id,no(1),no(1),id,no(2),no(2),id,no(3),no(3));
  fprintf('  l_%u:[%.12f,%.12f]\n\n',id,norm(no),norm(no));
  
end


function [x0 y0 c]=ConeConstants(x1,y1,x2,y2)
  dx=x2-x1;
  dy=y2-y1;
  x0=x1-y1*dx/dy; % r
  y0=y1-x1*dy/dx; % h
  c=abs(x0)/abs(y0); % r/h
end



  