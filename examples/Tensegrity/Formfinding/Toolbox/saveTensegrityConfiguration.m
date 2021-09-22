% Saves an equilibrium point, i.e, a solution of the form-finding
% problem in a form that can be used in the CuikSuite.
%
% Inputs
%     T: The tensegrity including the solution point to save.
% Outputs
%     A .links file
%
function saveTensegrityConfiguration(T) 
 
  % Here we first give the solution for the bars (struts) and then the
  % solution for the cables 
 
  % Construct the solution
  sol=[];
  for i=1:T.nBars
    a=T.bars{i}(1);
    b=T.bars{i}(2);
    v=T.p(ndx(b))-T.p(ndx(a));
    l=norm(v);        % length of the bar
    v=v/l;            % director vector
    f=-T.compression(i); % compression force
    
    sol=[sol v(1) v(2) v(3)];
    
    if isfield(T,'prismaticBars') && T.prismaticBars(i)
      r=l+f/T.stiffnessBar(i); % Rest length if any
      sol=[sol l r f];
    else
      sol=[sol f];
    end
  end
  
  if isfield(T,'extensionBars')
    n=size(T.extensionBars,2);
    for i=1:n
      a=T.extensionBars{i}(1);
      b=T.extensionBars{i}(2);
      v=T.p(ndx(b))-T.p(ndx(a));
      l=norm(v);        % length of the bar
      v=v/l;            % director vector
      
      sol=[sol v(1) v(2) v(3)];
    end
  end
  
  % Director vector and length for the strings
  for i=1:T.nStrings
    if ~isfield(T,'virtualString') || ~T.virtualString(i)
      a=T.strings{i}(1);
      b=T.strings{i}(2);
      v=T.p(ndx(b))-T.p(ndx(a));
      l=norm(v);        % length of the bar
      v=v/l;            % director vector
     
      f=T.tension(i);
      
      if isfield(T,'restString')
        %r=T.restString(i);
        r=l-f/T.stiffnessString(i);
      else
        r=0.0;
      end
      
      if isfield(T,'fixedStrings')
        fixedLength=T.fixedStrings(i);
      else
        fixedLength=false;
      end
      
      sol=[sol v(1) v(2) v(3)];
      
      if ~fixedLength
        sol=[sol l r];
      end
      sol=[sol f];
    end
  end

  % In some cases we have to add the pose of the platform (or part of it).
  if isfield(T,'platform')
    if isfield(T.platform,'u')
      sol=[sol T.platform.u];
    end
    if isfield(T.platform,'v')
      sol=[sol T.platform.v];
    end
    if isfield(T.platform,'w')
      sol=[sol T.platform.w];
    end
    if isfield(T.platform,'r')
      sol=[sol T.platform.r];
    end    
  end
  
  fname=[T.name '.links'];
  
  fprintf('Saving configuration to  : %s\n',fname);
  
  fid=fopen(fname,'w');
  
  % print the solution
  k=size(sol,2);
  for i=1:k
    fprintf(fid,'%.16f ',sol(i));
  end
  fprintf(fid,'\n');
  
  fclose(fid); 