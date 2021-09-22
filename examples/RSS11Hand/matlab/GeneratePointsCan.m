% Input parameters
%   po1,po2,po3: Contact points on the object in global coordinates
%   To: Transform for the object.
%   T1,T2,T3. Transforms for the contact links
%
function GeneratePointsCan()
  % Radius of the can (can is aligned along the Y axis!!)
  R=22.24;
    
  % Object pose
  To=[1.000000000000 0.000000000000 0.000000000000 57.596000000000 
      0.000000000000 1.000000000000 0.000000000000 28.845000000000 
      0.000000000000 0.000000000000 1.000000000000 243.568000000000 
      0.000000000000 0.000000000000 0.000000000000 1.000000000000 ];
  
  % First contact point p24-object
  p1=[40.522861480713,-1.912901401520,257.712280273438 1]';
  T1=[0.642530662151 -0.000000000000 0.766259974288 12.547753504825 
      0.000000000000 -1.000000000000 0.000000000000 0.000000000000 
      0.766259974288 -0.000000000000 -0.642530662151 244.071714995558 
      0.000000000000 0.000000000000 0.000000000000 1.000000000000 ];
  ymin_1=-50; % section of the can
  ymax_1=50;
  l1name='p24';
  
  % Second contact point p34-object
  p2=[38.334320068359,36.298660278320,254.638565063477 1]';
  T2=[0.627077982476 -0.000000000000 0.778956483954 10.666074992979 
     -0.027641276608 -0.999370208806 0.022251866857 36.820897731313 
      0.778465904020 -0.035485007414 -0.626683054285 239.610512449165 
      0.000000000000 0.000000000000 0.000000000000 1.000000000000 ];
  ymin_2=-50; % section of the can
  ymax_2=50;
  l2name='p34';
  
  % Third contact point p44-object
  p3=[74.326339721680,52.021595001221,229.022140502930 1]';
  T3=[0.020779007972 -0.166023994756 -0.985902767007 83.828632056040 
      0.003498365227 0.986121713160 -0.165987132862 47.802957941938 
      0.999777972486 -0.000000000000 0.021071443509 194.778285709141 
      0.000000000000 0.000000000000 0.000000000000 1.000000000000 ];
  ymin_3=-50; % section of the can
  ymax_3=50;
  l3name='p44';
  
  % Generate the equations for each contact point

  fprintf('--------------------------------------------------------------\n');
  fprintf('--------------------------------------------------------------\n');
  GenerateContactEqs(1,p1,To,ymin_1,ymax_1,R,T1,l1name);
  fprintf('--------------------------------------------------------------\n');
  fprintf('--------------------------------------------------------------\n');
  GenerateContactEqs(2,p2,To,ymin_2,ymax_2,R,T2,l2name);
  fprintf('--------------------------------------------------------------\n');
  fprintf('--------------------------------------------------------------\n');
  GenerateContactEqs(3,p3,To,ymin_3,ymax_3,R,T3,l3name);
  fprintf('--------------------------------------------------------------\n');
  fprintf('--------------------------------------------------------------\n');
  
end

% Parameters
%  id: Identifier of the contact (1,2,3).
%  po: Contact point in global coordinates.
%  To: Pose of the object.
%  R: Radius of the can.
%  Tl: Pose of the link in contact with the object.
%  link: String identifying the link.
function GenerateContactEqs(id,po,To,ymin,ymax,R,Tl,link)
  fprintf('Contact constants, variables, and equations for contact object -- %s\n\n',link);

  % Coordinates in local of object
  pol=To\po; 
    
  x=pol(1);y=pol(2);z=pol(3);
  % fprintf('Coordinates on object: [%f %f %f]\n',x,y,z);
  
  % e=x^2+z^2-R^2;
  % fprintf('Error in cylinder %.12f\n',e);
  
  % correcting cylinder
  x=sign(x)*sqrt(abs(R^2-z^2));
  pol(1)=x;
  % fprintf('Corrected coordinates on object: [%.12f %.12f %.12f]\n',x,y,z);
  
  % Normal in object reference frame
  no=[pol(1) 0 pol(3)]';
  
  % Coordinates in local of link
  pl=Tl\(To*pol);
  
  % Normal in link reference frame
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
  fprintf('  R_%u:=%.12f\n',id,R);  % object parameters
  
  % Add three variables for the position of the contact point on the
  % object and corresponding normal
  
  fprintf('%% Variables to add for contact %u\n',id);
  fprintf('  o_%u_x:[%.12f,%.12f]\n',id,-R-1,R+1);
  fprintf('  o_%u_y:[%.12f,%.12f]\n',id,ymin,ymax);
  fprintf('  o_%u_z:[%.12f,%.12f]\n\n',id,-R-1,R+1);
  
  fprintf('  no_%u_x:[%.12f,%.12f]\n',id,-R-1,R+1);
  fprintf('  no_%u_y:[0,0]\n',id);
  fprintf('  no_%u_z:[%.12f,%.12f]\n\n',id,-R-1,R+1);
    
  fprintf('%% Equations to add for contact %u\n',id);
  
  % Equation for the cylinder defining the object
  fprintf('  %% Points on the object must be on the cylinder \n');
  fprintf('  o_%u_x^2+o_%u_z^2-R_%u^2=0;\n\n',id,id,id);
  
  % Equations defining the normal (in local coordinates)
  fprintf('  %% (Not normalized) Normal on the object \n');
  fprintf('  o_%u_x-no_%u_x=0;\n',id,id); 
  fprintf('  no_%u_y=0;\n',id);
  fprintf('  o_%u_z-no_%u_z=0;\n\n',id,id); 
  
  % The squared norm of the normal vector is R^2
  
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
  fprintf('     -%s_u_x*n_%u_x*R_%u -%s_v_x*n_%u_y*R_%u -%s_w_x*n_%u_z*R_%u +%s_wp_x*n_%u_z*R_%u=0;\n',link,id,id,link,id,id,link,id,id,link,id,id);
  fprintf('    object_u_y*no_%u_x +object_v_y*no_%u_y +object_w_y*no_%u_z -object_wp_y*no_%u_z\n',id,id,id,id);
  fprintf('     -%s_u_y*n_%u_x*R_%u -%s_v_y*n_%u_y*R_%u -%s_w_y*n_%u_z*R_%u +%s_wp_y*n_%u_z*R_%u=0;\n',link,id,id,link,id,id,link,id,id,link,id,id);
  fprintf('    object_u_z*no_%u_x +object_v_z*no_%u_y +object_w_z*no_%u_z -object_wp_z*no_%u_z\n',id,id,id,id);
  fprintf('     -%s_u_z*n_%u_x*R_%u -%s_v_z*n_%u_y*R_%u -%s_w_z*n_%u_z*R_%u +%s_wp_z*n_%u_z*R_%u=0;\n\n',link,id,id,link,id,id,link,id,id,link,id,id);
  
  if id==1
    % Fix the object rotation and translation around the y axis
    fprintf('  %% Equations to fix object rotation and translation\n');  
    fprintf('    o_%u_x=%.16f;\n',id,pol(1));
    fprintf('    o_%u_y=%.16f;\n',id,pol(2));
    fprintf('    o_%u_z=%.16f;\n\n',id,pol(3));
  end
  
  fprintf('%% Solution for o_%u, no_%u and l_%u\n',id,id,id);
  fprintf('  o_%u =(%.12f,%.12f,%.12f)\n',id,pol(1),pol(2),pol(3));
  fprintf('  no_%u=(%.12f,%.12f,%.12f)\n',id,no(1),no(2),no(3));
  
  fprintf('%% Solution for o_%u, no_%u, and l_%u in box form\n',id,id,id);
  fprintf('  o_%u_x:[%.12f,%.12f] o_%u_y:[%.12f,%.12f] o_%u_z:[%.12f,%.12f]\n',id,pol(1),pol(1),id,pol(2),pol(2),id,pol(3),pol(3));
  fprintf('  no_%u_x:[%.12f,%.12f] no_%u_y:[%.12f,%.12f] no_%u_z:[%.12f,%.12f]\n',id,no(1),no(1),id,no(2),no(2),id,no(3),no(3));
  
end




  