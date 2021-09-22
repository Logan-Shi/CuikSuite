% Parameters
%   id: Identifier of the contact (1,2,3)
%   fname: Prefix for the file where to store the information. The lsst part
%          of the file name corresponts to the object name
%   po: Contact point in global coordinates
%   objName: Object namen in the world file
%   To: Pose of the object
%   link: String identifying the link in the world file.
%   Tl: Pose of the link in contact with the object.
% 
% To use this function with a new object XXX you have to define two new
% functions:
%     CorrectXXXPoint -> That takes an approximated point on the object
%                        and corrects its position. It also returns the
%                        normal at this point.
%     PrintXXXEqs -> Prints the equations of a point on the object and of
%                    the corresponding normal.
%
%  See CorrectSetrillPoint, CorrectCanPoint, PrintSetrillEqs, PrintCanEqs
%  for examples of how to do this.
%

function GenerateContactEqs(id,fname,po,objName,To,link,Tl)

  fprintf('Generating contact constants, variables, equations, and solutions for contact %u\n',id);
 
  objFnName=objName;
  objFnName(1)=upper(objFnName(1));
  

  fn=sprintf('%s_contact_%u.cuik',fname,id);
  fprintf('  Generating file %s\n',fn);
  fid=fopen(fn,'w');
  if fid<0
    error('Can not open file to store contact equations');
  end
  
  % Coordinates in local of object
  pol=To\po; 
    
  s=['[pol no minP maxP minN maxN p]=Correct' objFnName 'Point(id,pol);'];
  
  eval(s);
  
  % Coordinates in local of link
  pl=Tl\(To*pol);
  
  % Normal in link
  Ro=To(1:3,1:3);
  Rl=Tl(1:3,1:3);
  nl=Rl\(Ro*no);
  nl=nl/norm(nl);
  
  fprintf(fid,'[CONSTANTS]\n');
  fprintf(fid,'  f_%u_x:=%.16f\n',id,pl(1)); % point in link (in local)
  fprintf(fid,'  f_%u_y:=%.16f\n',id,pl(2));
  fprintf(fid,'  f_%u_z:=%.16f\n\n',id,pl(3));
  fprintf(fid,'  n_%u_x:=%.16f\n',id,nl(1)); % normal in link (in local)
  fprintf(fid,'  n_%u_y:=%.16f\n',id,nl(2));
  fprintf(fid,'  n_%u_z:=%.16f\n\n',id,nl(3));
  np=size(p,2);
  for i=1:np
    fprintf(fid,'  p_%u_%u:=%.16f\n',i,id,p(i));
  end;
  fprintf(fid,'\n');
  
  % Add three variables for the position of the contact point on the
  % object and corresponding normal
  
  fprintf(fid,'[SYSTEM VARS]\n');
  fprintf(fid,'  %% Point on object (in local coordinates) \n');
  fprintf(fid,'  o_%u_x:[%.12f,%.12f]\n',id,minP(1),maxP(1));
  fprintf(fid,'  o_%u_y:[%.12f,%.12f]\n',id,minP(2),maxP(2));
  fprintf(fid,'  o_%u_z:[%.12f,%.12f]\n\n',id,minP(3),maxP(3));
  
  fprintf(fid,'  %% Normal on object (in local coordinates) \n');
  fprintf(fid,'  no_%u_x:[%.12f,%.12f]\n',id,minN(1),maxN(1));
  fprintf(fid,'  no_%u_y:[%.12f,%.12f]\n',id,minN(2),maxN(2));
  fprintf(fid,'  no_%u_z:[%.12f,%.12f]\n\n',id,minN(3),maxN(3));
  
  fprintf(fid,'  %% Norm of the normal on object \n');
  mn=max(abs([minN maxN]));
  fprintf(fid,'  l_%u:[0,%.12f]\n\n',id,sqrt(3)*mn);
    
  fprintf(fid,'[SYSTEM EQS]\n');
  
  s=['Print' objFnName 'Eqs(fid,id,pol);'];
  eval(s);
  
  % Equation defining the squared norm of the normal
  fprintf(fid,'  %% Squared norm of the normal on the object \n');
  fprintf(fid,'    no_%u_x^2+no_%u_y^2+no_%u_z^2-l_%u^2=0;\n\n',id,id,id,id);
  
  % Points on the link and on the object must coincide
  fprintf(fid,'  %% Points in finger and in object must coincide \n');
  fprintf(fid,'    %s_u_x*o_%u_x +%s_v_x*o_%u_y +%s_w_x*o_%u_z -%s_wp_x*o_%u_z +%s_r_x\n',objName,id,objName,id,objName,id,objName,id,objName);
  fprintf(fid,'     -%s_u_x*f_%u_x -%s_v_x*f_%u_y -%s_w_x*f_%u_z +%s_wp_x*f_%u_z -%s_r_x=0;\n',link,id,link,id,link,id,link,id,link);
  fprintf(fid,'    %s_u_y*o_%u_x +%s_v_y*o_%u_y +%s_w_y*o_%u_z -%s_wp_y*o_%u_z +%s_r_y\n',objName,id,objName,id,objName,id,objName,id,objName);
  fprintf(fid,'     -%s_u_y*f_%u_x -%s_v_y*f_%u_y -%s_w_y*f_%u_z +%s_wp_y*f_%u_z -%s_r_y=0;\n',link,id,link,id,link,id,link,id,link);
  fprintf(fid,'    %s_u_z*o_%u_x +%s_v_z*o_%u_y +%s_w_z*o_%u_z -%s_wp_z*o_%u_z +%s_r_z\n',objName,id,objName,id,objName,id,objName,id,objName);
  fprintf(fid,'     -%s_u_z*f_%u_x -%s_v_z*f_%u_y -%s_w_z*f_%u_z +%s_wp_z*f_%u_z -%s_r_z=0;\n\n',link,id,link,id,link,id,link,id,link);
  
  % Normals on the link and on the object must coincide
  fprintf(fid,'  %% Normals in finger and in object must be aligned \n');
  fprintf(fid,'    %s_u_x*no_%u_x +%s_v_x*no_%u_y +%s_w_x*no_%u_z -%s_wp_x*no_%u_z\n',objName,id,objName,id,objName,id,objName,id);
  fprintf(fid,'     -%s_u_x*n_%u_x*l_%u -%s_v_x*n_%u_y*l_%u -%s_w_x*n_%u_z*l_%u +%s_wp_x*n_%u_z*l_%u=0;\n',link,id,id,link,id,id,link,id,id,link,id,id);
  fprintf(fid,'    %s_u_y*no_%u_x +%s_v_y*no_%u_y +%s_w_y*no_%u_z -%s_wp_y*no_%u_z\n',objName,id,objName,id,objName,id,objName,id);
  fprintf(fid,'     -%s_u_y*n_%u_x*l_%u -%s_v_y*n_%u_y*l_%u -%s_w_y*n_%u_z*l_%u +%s_wp_y*n_%u_z*l_%u=0;\n',link,id,id,link,id,id,link,id,id,link,id,id);
  fprintf(fid,'    %s_u_z*no_%u_x +%s_v_z*no_%u_y +%s_w_z*no_%u_z -%s_wp_z*no_%u_z\n',objName,id,objName,id,objName,id,objName,id);
  fprintf(fid,'     -%s_u_z*n_%u_x*l_%u -%s_v_z*n_%u_y*l_%u -%s_w_z*n_%u_z*l_%u +%s_wp_z*n_%u_z*l_%u=0;\n\n',link,id,id,link,id,id,link,id,id,link,id,id);
  
  
  fclose(fid);
  
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  % Sample
  
  % fn=sprintf('%s_contact_%u.sample',fname,id);
  % fid=fopen(fn,'w');
  % if fid<0
  %   error('Can not open file to store contact sample');
  % end
  
  % fprintf(fid,'  %.12f %.12f %.12f ',pol(1),pol(2),pol(3));
  % fprintf(fid,'  %.12f %.12f %.12f ',no(1),no(2),no(3));
  % fprintf(fid,'  %.12f\n\n',norm(no));
  
  % fclose(fid);
  
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  % Solution
  
  fn=sprintf('%s_contact_%u.sol',fname,id);
  fprintf('  Generating file %s\n',fn);
  fid=fopen(fn,'w');
  if fid<0
    error('Can not open file to store contact solution');
  end
  
  fprintf(fid,'  { 7 o_%u_x:[%.16f,%.16f] o_%u_y:[%.16f,%.16f] o_%u_z:[%.16f,%.16f] ',id,pol(1),pol(1),id,pol(2),pol(2),id,pol(3),pol(3));
  fprintf(fid,'  no_%u_x:[%.16f,%.16f] no_%u_y:[%.16f,%.16f] no_%u_z:[%.16f,%.16f] ',id,no(1),no(1),id,no(2),no(2),id,no(3),no(3));
  fprintf(fid,'  l_%u:[%.16f,%.16f] }\n\n',id,norm(no),norm(no));
  
  fclose(fid);
  
end
