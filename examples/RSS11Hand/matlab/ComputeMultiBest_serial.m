function ComputeMultiBest_serial(fname)

  nf = 3; % number of fingers
  vf = 3; % number of components per finger
  nc = 3; % number of contacts
  vc = 7; % numbers of components per contact [point normal length]
  va = 6; % number of components per joint [point vector]
  vl = 6; % number of variables per link [vector_u vector_v]
  
 % read information about the contact
  fprintf(['Reading contact information: ' fname '_kin_contact.links\n']);
    full = load([fname '_kin_contact.links']); % last columns, in the order of fingers in .world file
    
    [m,n] = size(full);
    
    contacts = full(:,n-(nc*(vc)-1):n);
    object = full(:,n-(nc*vc+nf*vf+2):n-(nc*vc+nf*vf));
    object_R = full(:,10*vl+1:10*vl+6);
  
  % read information about the axes
  fprintf(['Reading joint information: ' fname '_kin_contact.axes\n']);
    axes = load([fname '_kin_contact.axes']); %  in the order of appearance in .world file
  
  
  tic;
  
  % CONTACT MODELS
    %free model
%    Hn = zeros(6,6);
%    %frictionless model
%    Hpwof =  [1 0 0  zeros(1,3)] ; 
    %hard friction model
    Hhf = [eye(3) zeros(3,3)];%; zeros(3,6)];
    %soft friction model
%    Hsf = [eye(3) zeros(3,3); zeros(1,3) 1 0 0];
%    %rigid model
%    Hr = eye(6);
%  
  % model in contact 1
  H1 = Hhf;
  
  % model in contact 2
  H2 = Hhf;
  
  % model in contact 3
  H3 = Hhf;

  % full selection matrix
  H = blkdiag(H1,H2,H3);  
  
  
  fprintf('Evaluating force closure and manipulability in all samples...\n');
  
  ffc=zeros(m,1);
  int=zeros(m,1);
  index1=zeros(m,1);
  index2=zeros(m,1);
  index3=zeros(m,1);
  multi=zeros(m,1);
  
  for i=1:m,
  
    [d1,d2]=ForceClosureOneConfiguration(i,vc,va,H,axes,object,object_R,contacts);

    % Index 1: how far is the grasp from losing frictional form closure
    ffc(i) = d1;

    % Index 2: control of internal forces
    int(i) = d2;

    [index1 index2 index3 u]=ManipulabilityOneConfiguration(i,vc,va,H,axes,object,object_R,contacts);    
    
   % Index 1: inverse of the condition number of the ratio matrix
    mani1(i) = index1;

    % Index 2: determinant of the ratio matrix
    mani2(i) = index2;

    % Index 3: the minimum of the sngular values
    mani3(i) = index3;
 
  end

  [DFC,i_max] = max(ffc);
  
  
  D=0;
  d=100000000;
  for i=1:m,
    if ffc(i)<0.5*DFC,
      multi(i) = -1;
    else
%      multi(i) = 1; % only to plot the reduced search space in blue
      multi(i) = mani2(i);
      
      if multi(i) > D,
         D=multi(i);
         i_max=i;
      end
      
      if multi(i) < d,
         d=multi(i);
         i_min = i;
      end
      
    end
  end
  
  % scaling
  for i=1:m
    if not(ffc(i)<0.5*DFC)
      multi(i)=(multi(i)-d)/(D-d);
    end
  end
    
  

  
  fprintf('Ellapsed time %f\n',toc);
  
  %scale for ellipsoids
  s_max = 1;
  s_min = 1;
  %permutation/selector matrix: two major axis and worst axis of a 6D
  %ellipsoid
  PR = [1 0 ; 0 0; 0 0; 0 0; 0 0; 0 1];
  
  %printing index

  fprintf(['Printing Multi (far from losing f.f.c.) in: ' fname '_kin_fc1.cost\n']);
  % re-scaling to [0,1]
  [d,i_min] = min(multi);
  %[D,i_max] = max(multi);
  fprintf('Maximum of Index 1: Chart %d (%g)\n',i_max,D);
  fprintf('Minimum of Index 1: Chart %d (%g)\n',i_min,d);
  fprintf('Ratio: %g\n',D/d);
  %multi=(multi-d)/(D-d); % normalization step
  save([fname '_kin_contact_multi.cost'],'multi','-ascii');
  

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

