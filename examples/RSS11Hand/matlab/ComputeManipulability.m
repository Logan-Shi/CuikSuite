function ComputeManipulability(fname,e)
   
  % e is the extra degrees of freedom due to releasing contact constraints
 
  fprintf('Initialize...\n');
  [m,vc,va,contacts, object object_R,axes] = Init(fname);
  
  mani1=zeros(m,1);
  mani2=zeros(m,1);
  mani3=zeros(m,1);

  fprintf('Evaluating manipulability in all samples...\n');
  tic;

  for i=1:m,
  

    [J, G, n1, n2, n3] = GetMatrices(i,vc,va,axes,object,object_R,contacts);
    [index1, index2, index3, u] = ManipulabilityOneConfiguration(J, G);
    
    % Index 1: inverse of the condition number of the ratio matrix
    mani1(i) = index1;

    % Index 2: determinant of the ratio matrix
    mani2(i) = index2;

    % Index 3: the minimum of the sngular values
    mani3(i) = index3;
    
  end
  
  fprintf('Ellapsed time %f\n',toc);
  
  %scale for ellipsoids
  s_max = 1;
  s_min = 1;
  %permutation/selector matrix: two major axis and worst axis of a 6D
  %ellipsoid
  PR = [1 0 ; 0 0; 0 0; 0 0; 0 0; 0 1];
  
  %printing index

  fprintf(['Printing Index 1 (cond. number) in: ' fname '_with_contacts_with_eigens_index1.cost\n']);
  % re-scaling to [0,1]
  [d,i_min] = min(mani1);
  [D,i_max] = max(mani1);
  fprintf('Maximum of Index 1: Chart %d (%g)\n',i_max,D);
  fprintf('Minimum of Index 1: Chart %d (%g)\n',i_min,d);
  fprintf('Ratio: %g\n',D/d);
  mani1=(mani1-d)/(D-d);
  save([fname '_with_contacts_with_eigens_index1.cost'],'mani1','-ascii');
  
%    %printing ellipsoids at the min and max configurations
%    %fprintf(['Writing max ellipsoid in: '  fname '_index1_max_ellipse.off\n']);
%    [index1 index2 index3 u]= ManipulabilityOneConfiguration(i_max,vc,va,H,axes,object,object_R,contacts);
%    %o = transpose(object(i_max,:));
%    o = [0;0];
%    R = [(1/index1)*index3 0; 0 index3];
%    plotEllipsoid(s_max*R,o,[fname '_index1_max_' sprintf('%d',i_max)]);
%    
%    %fprintf(['Writing min ellipsoid in: '  fname '_index1_min_ellipse.off\n']);
%    [index1 index2 index3 u]= ManipulabilityOneConfiguration(i_min,vc,va,H,axes,object,object_R,contacts);  
%    %o = transpose(object(i_min,:));
%    o = [0;0];
%    R = [(1/index1)*index3 0; 0 index3];
%    plotEllipsoid(s_min*R,o,[fname '_index1_min_' sprintf('%d',i_min)]);
  
  
  fprintf(['Printing Index 2 (determinant) in: ' fname '_with_contacts_with_eigens_index2.cost\n']);
  % re-scaling to [0,1]
  [d,i_min] = min(mani2);
  [D,i_max] = max(mani2);
  fprintf('Maximum of Index 2: Chart %d (%g)\n',i_max,D);
  fprintf('Minimum of Index 2: Chart %d (%g)\n',i_min,d);
  fprintf('Ratio: %g\n',D/d);
  mani2=(mani2-d)/(D-d);
  save([fname '_with_contacts_with_eigens_index2.cost'],'mani2','-ascii');
  
%    %printing ellipsoids at the min and max configurations
%    %fprintf(['Writing max ellipsoid in: '  fname '_index2_max_ellipse.off\n']);
%    [index1 index2 index3 u]= ManipulabilityOneConfiguration(i_max,vc,va,H,axes,object,object_R,contacts);
%    %o = transpose(object(i_max,:));
%    o = [0;0];
%    R = [(1/index1)*index3 0; 0 index3];
%    plotEllipsoid(s_max*R,o,[fname '_index2_max_' sprintf('%d',i_max)]);
% 
%    %fprintf(['Writing min ellipsoid in: '  fname '_index2_min_ellipse.off\n']);   
%    [index1 index2 index3 u]= ManipulabilityOneConfiguration(i_min,vc,va,H,axes,object,object_R,contacts);  
%    %o = transpose(object(i_min,:));
%    o = [0;0];
%    R = [(1/index1)*index3 0; 0 index3];
%    plotEllipsoid(s_min*R,o,[fname '_index2_min_' sprintf('%d',i_min)]);
   

  fprintf(['Printing Index 3 (min. sing. value) in: ' fname '_with_contacts_with_eigens_index3.cost\n']);
  % re-scaling to [0,1]
  [d,i_min] = min(mani3);
  [D,i_max] = max(mani3);
  fprintf('Maximum of Index 3: Chart %d (%g)\n',i_max,D);
  fprintf('Minimum of Index 3: Chart %d (%g)\n',i_min,d);
  fprintf('Ratio: %g\n',D/d);
  mani3=(mani3-d)/(D-d);
  save([fname '_with_contacts_with_eigens_index3.cost'],'mani3','-ascii');
  
%    %printing ellipsoids at the min and max configurations
%    %fprintf(['Writing max ellipsoid in: '  fname '_index3_max_ellipse.off\n']);  
%    [index1 index2 index3 u]= ManipulabilityOneConfiguration(i_max,vc,va,H,axes,object,object_R,contacts);
%    %o = transpose(object(i_max,:));
%    o = [0;0];
%    R =  [(1/index1)*index3 0; 0 index3];
%    plotEllipsoid(s_max*R,o,[fname '_index3_max_' sprintf('%d',i_max)]);
% 
%    %fprintf(['Writing min ellipsoid in: '  fname '_index3_min_ellipse.off\n']);
%    [index1 index2 index3 u]= ManipulabilityOneConfiguration(i_min,vc,va,H,axes,object,object_R,contacts);  
%    %o = transpose(object(i_min,:));
%    o = [0;0];
%    R =  [(1/index1)*index3 0; 0 index3];
%    plotEllipsoid(s_min*R,o,[fname '_index3_min_' sprintf('%d',i_min)]);
   
 
  exit

