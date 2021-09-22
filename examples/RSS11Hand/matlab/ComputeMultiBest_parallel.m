function ComputeMultiBest_parallel(fname)

  nf = 3; % number of fingers
  vf = 3; % number of components per finger
  nc = 3; % number of contacts
  vc = 7; % numbers of components per contact [point normal length]
  va = 6; % number of components per joint [point vector]
  vl = 6; % number of variables per link [vector_u vector_v]
  
  % read information about the axes
  fprintf(['Reading joint information: ' fname '_kin.axes\n']);
    axes = load([fname '_kin.axes']); %  in the order of appearance in .world file
  % read information about the contact
  
  fprintf(['Reading object information: ' fname '_kin.links\n']);
    full = load([fname '_kin.links']); % last columns, in the order of fingers in .world file
    
    [m,n] = size(full);
    
    %contacts = full(:,n-(nc*(vc)-1):n);
%    object = full(:,n-(nc*vc+nf*vf+2):n-(nc*vc+nf*vf));
    object_R = full(:,n-5:n);
  
  % weights for multiobjective
  w1 = 1; % force-closure 
  w2 = 1; % manipulability

  tic;
  
  % CONTACT MODELS
    %free model
%    Hn = zeros(6,6);
%    %frictionless model
%    Hpwof =  [1 0 0  zeros(1,3)] ; 
    %hard friction model
%    Hhf = [eye(3) zeros(3,3)];%; zeros(3,6)];
     Hhf = [1 0 0 0 0 0 ; 0 0 1 0 0 0 ];
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
  
  fc1=zeros(m,1);
%  intF=zeros(m,1);

  for i=1:m,
  
    [D]=ForceClosureOneConfiguration(i,vc,va,H,axes,object_R);

    [index1 index2 index3 u]=ManipulabilityOneConfiguration(i,vc,va,H,axes,object_R);

    
    multi(i) = w1*D + w2*index1;
 
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
  [D,i_max] = max(multi);
  fprintf('Maximum of Index 1: Chart %d (%g)\n',i_max,D);
  fprintf('Minimum of Index 1: Chart %d (%g)\n',i_min,d);
  fprintf('Ratio: %g\n',D/d);
  multi=(multi-d)/(D-d); % normalization step
  save([fname '_kin_multi.cost'],'multi','-ascii');
  

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

