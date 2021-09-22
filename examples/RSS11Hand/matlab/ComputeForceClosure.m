function ComputeForceClosure(fname)

  fprintf('Initialize...\n');
  [m,vc,va,contacts, object object_R,axes] = Init(fname);
  
  ffc=zeros(m,1);
  int=zeros(m,1);

  fprintf('Evaluating force closure in all samples...\n');
  tic;
  for i=1:m,
  
    [J, G, n1, n2, n3] = GetMatrices(i,vc,va,axes,object,object_R,contacts);
    [d1,d2] = ForceClosureOneConfiguration(J, G, n1, n2, n3);
    
    % Index 1: how far is the grasp from losing frictional form closure
    ffc(i) = d1;
    
    % Index 2: chech whether the intersection of the null space of the jacobian 
    %          transpose and the grasp matrix is void or not.
    int(i) = d2;
    
  end
  
  
%flag = 0;

%if d2==0 % internal forces are controllable, hence the index is how far the grasp is from loosing frictional form closure
%    D=d1; 
%else
%    D=0;
%    flag = 1;
%end

  
  fprintf('Ellapsed time %f\n',toc);
  
  %scale for ellipsoids
  s_max = 1;
  s_min = 1;
  %permutation/selector matrix: two major axis and worst axis of a 6D
  %ellipsoid
  PR = [1 0 ; 0 0; 0 0; 0 0; 0 0; 0 1];
  
  %printing index

  fprintf(['Printing FFC (far from losing f.f.c.) in: ' fname '_with_contacts_with_eigens_ffc.cost\n']);
  % re-scaling to [0,1]
  [d,i_min] = min(ffc);
  [D,i_max] = max(ffc);
  fprintf('Maximum of Index 1: Chart %d (%g)\n',i_max,D);
  fprintf('Minimum of Index 1: Chart %d (%g)\n',i_min,d);
  fprintf('Ratio: %g\n',D/d);
  ffc=(ffc-d)/(D-d);
  save([fname '_with_contacts_with_eigens_ffc.cost'],'ffc','-ascii');
  
  %printing index

  fprintf(['Printing INT (internal forces are controllable or not) in: ' fname '_with_contacts_with_eigens_int.cost\n']);
  % re-scaling to [0,1]
  [d,i_min] = min(int);
  [D,i_max] = max(int);
  fprintf('Maximum of Index 1: Chart %d (%g)\n',i_max,D);
  fprintf('Minimum of Index 1: Chart %d (%g)\n',i_min,d);
  fprintf('Ratio: %g\n',D/d);
  for i=1:m  % this measure is binary and inverted, 0, hence 1, the forces are controllable, >0, hence 0, they are not.
    if abs(int(i))<1e-6
      int(i)=1;
    else
      int(i)=0;
    end
  end
  save([fname '_with_contacts_with_eigens_int.cost'],'int','-ascii');
  
%   %printing ellipsoids at the min and max configurations
%   %fprintf(['Writing max ellipsoid in: '  fname '_index1_max_ellipse.off\n']);
%   [index1 index2 index3 u]= ManipulabilityOneConfiguration(i_max,vc,va,H,axes,object,object_R,contacts);
%   %o = transpose(object(i_max,:));
%   o = [0;0];
%   R = [(1/index1)*index3 0; 0 index3];
%   plotEllipsoid(s_max*R,o,[fname '_index1_max_' sprintf('%d',i_max)]);
%   
%   %fprintf(['Writing min ellipsoid in: '  fname '_index1_min_ellipse.off\n']);
%   [index1 index2 index3 u]= ManipulabilityOneConfiguration(i_min,vc,va,H,axes,object,object_R,contacts);  
%   %o = transpose(object(i_min,:));
%   o = [0;0];
%   R = [(1/index1)*index3 0; 0 index3];
%   plotEllipsoid(s_min*R,o,[fname '_index1_min_' sprintf('%d',i_min)]);
  
   exit;

