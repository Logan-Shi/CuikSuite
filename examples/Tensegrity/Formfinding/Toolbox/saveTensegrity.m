% Saves the tensegrity information in a form compatible with
% the CuikSuite.
% The output file can be direclty processed by the CuikSuite
% but they can also be used as a starting points to define
% other problems (including symmetries, add-ons, etc.).
%
% Inputs
%     T: The tensegrity to save.
% Outputs
%     A .tens file
%
function saveTensegrity(T)
 
  % Here we first give the solution for the bars (struts) and then the
  % solution for the cables 

  fname=[T.name '.tens'];
  fprintf('Saving tensegrity to     : %s\n',fname);
  
  fid=fopen(fname,'w');
  
  fprintf(fid,'/** \\cond */\n');
  
  if isfield(T,'planar') && T.planar
    if isfield(T,'freeFlying') && T.freeFlying
      fprintf(fid,'[FREE FLYING PLANAR STRUCTURE 1,1]\n\n');
    else
      fprintf(fid,'[PLANAR STRUCTURE]\n\n');
    end
  else
    if isfield(T,'freeFlying') && T.freeFlying
      fprintf(fid,'[FREE FLYING STRUCTURE 1,1,1]\n\n');
    else
      fprintf(fid,'[STRUCTURE]\n\n');
    end
  end
 
  % Construct the solution
  for i=1:T.nBars
    a=T.bars{i}(1);
    b=T.bars{i}(2);
    v=T.p(ndx(b))-T.p(ndx(a));
    l=norm(v);        % length of the bar
    f=-T.stiffnessBar(i)*l; % compression force
    
    if isfield(T,'prismaticBars') && T.prismaticBars(i)
      fprintf(fid,'  prismatic s%u: n%u n%u\n',i,a,b);
      fprintf(fid,'                length [%.12f,%.12f]\n',0.75*l,1.25*l);
      fprintf(fid,'                stiffness %.12f\n',-T.stiffnessBar(i));
      if isfield(T,'radius')
        fprintf(fid,'                radius %.12f\n',T.radius(i));
      end
    else
      fprintf(fid,'  strut s%u: n%u n%u\n',i,a,b);
      fprintf(fid,'            length %.12f\n',l);
      fprintf(fid,'            force [%.12f,0]\n\n',2*f);
      if isfield(T,'radius')
        fprintf(fid,'            radius %.12f\n',T.radius(i));
      end
    end
    fprintf(fid,'\n');
  end
  
  if isfield(T,'extensionBars')
    n=size(T.extensionBars,2);
    for i=1:n
      a=T.extensionBars{i}(1);
      b=T.extensionBars{i}(2);
      v=T.p(ndx(b))-T.p(ndx(a));
      l=norm(v);        % length of the bar
      
      fprintf(fid,'  strut s%u: n%u n%u\n',T.nBars+i,a,b);
      fprintf(fid,'            length %.12f\n',l);
      fprintf(fid,'            force 0\n\n');
    end
  end
  
  % Director vector and length for the strings
  for i=1:T.nStrings
    if ~isfield(T,'virtualString') || ~T.virtualString(i)
      a=T.strings{i}(1);
      b=T.strings{i}(2);
      v=T.p(ndx(b))-T.p(ndx(a));
      l=norm(v);        % length of the bar
      
      if isfield(T,'restString')
        r=T.restString(i);
      else
        r=l;
      end

      if isfield(T,'ctRestString') && T.ctRestString(i)
        fprintf(fid,'  spring c%u: n%u n%u\n',i,a,b);
      else
        fprintf(fid,'  cable c%u: n%u n%u\n',i,a,b);
      end
      
      if isfield(T,'fixedStrings')
        fixedLength=T.fixedStrings(i);
      else
        fixedLength=false;
      end
      if fixedLength
        fprintf(fid,'            length %.12f\n',l);
        f=l*T.stiffnessString(i);
        fprintf(fid,'            force [%.12f,%.12f]\n\n',0.5*f,2*f);
      else
        fprintf(fid,'            length [%.12f,%.12f]\n',0.5*l,2*l);
        fprintf(fid,'            stiffness %.12f\n',T.stiffnessString(i));
        if isfield(T,'ctRestString') && T.ctRestString(i)
          fprintf(fid,'            rest %.12f\n\n',r); 
        else
          fprintf(fid,'            rest [%.12f,%.12f]\n\n',0,2*r);  
        end
      end
    end
  end
  
  if isfield(T,'platform') && isfield(T.platform,'nodes')
    fprintf(fid,'\n[ADDONS]\n\n');
    fprintf(fid,'  platform : (%.12f,%.12f,%.12f) n%u\n',T.platform.p(1),T.platform.p(2),T.platform.p(3),T.platform.nodes(1));
    fprintf(fid,'             (%.12f,%.12f,%.12f) n%u\n',T.platform.p(4),T.platform.p(5),T.platform.p(6),T.platform.nodes(2));
    fprintf(fid,'             (%.12f,%.12f,%.12f) n%u\n\n',T.platform.p(7),T.platform.p(8),T.platform.p(9),T.platform.nodes(3));
  end
  
  if ~isfield(T,'freeFlying') || ~T.freeFlying
    if isfield(T,'fixedPoints')
      n1=T.fixedPoints(1);
      n2=T.fixedPoints(2);
      if ~isfield(T,'planar') || ~T.planar
        n3=T.fixedPoints(3);
      end
    else
      if isfield(T,'equilibriumNode')
        n1=T.bars{1}(1);
        if T.equilibriumNode(n1)
          n1=T.bars{1}(2);
        end
        n2=T.bars{2}(1);
        if T.equilibriumNode(n2)
          n2=T.bars{2}(2);
        end
        if ~isfield(T,'planar') || ~T.planar
          n3=T.bars{3}(1);
          if T.equilibriumNode(n3)
            n3=T.bars{3}(2);
          end
        end
      else
        n1=T.bars{1}(1);
        n2=T.bars{2}(1);
        if ~isfield(T,'planar') || ~T.planar
          n3=T.bars{3}(1);
        end
      end
    end
    
    fprintf(fid,'\n[FIXED POINTS]\n\n');
    fprintf(fid,'  n%u=(0,0,0)\n',n1);
    p=T.p(ndx(n2))-T.p(ndx(1));
    fprintf(fid,'  n%u=(%.12f,%.12f,%.12f)\n',n2,p(1),p(2),p(3));
    if ~isfield(T,'planar') || ~T.planar
      p=T.p(ndx(n3))-T.p(ndx(1));
      fprintf(fid,'  n%u=(%.12f,%.12f,%.12f)\n',n3,p(1),p(2),p(3));
    end
  end
  
  if isfield(T,'equilibriumNode') && size(find(~T.equilibriumNode),2)>0
    fprintf(fid,'\n[FORCES]\n\n');
    
    fprintf(fid,'  No null force: ');
    for i=1:T.nPoints
      if ~T.equilibriumNode(i)
        if i>1
          fprintf(fid,',');
        end
        fprintf(fid,'n%u',i);
      end
    end
    fprintf(fid,'\n\n');
  end
  
  fprintf(fid,'/** \\endcond */\n');
  fprintf(fid,'/**\n');
  fprintf(fid,'   \\file %s/%s.tens\n\n',pwd,T.name);
  fprintf(fid,'   \\brief Automatically generated world file.\n\n');
  fprintf(fid,'   Tensegrity description file automatically generated with\n');
  fprintf(fid,'   the CuikSuite form-finding Matlab toolbox\n');
  fprintf(fid,'   using the <i>define%s.m</i> function.\n\n',T.name);
  fprintf(fid,'*/\n');
  fclose(fid);
    
    
