function [p G S]=example2dCoord(noise)
  

  % generates coordinates for example2
  % The coordinates are the same as those in example1 but the graph is not

  d=10;           % bond length
  a=109.5*pi/180; % bond angle
  b=36*pi/180;    % bond angle for the bar connecting the two rings
  
  % ct to compute the atom pos
  c1=cos(a);
  c2=(1-c1);
  c3=sqrt(1-2*c1^2);
  
  
  % noise function
  n=@(r)(2*r*rand(3,1)-r);
  
  % atom pos (half of them)
  p1 =[ 0    0    0]'+n(noise);
  p6 =[ d*c2 d*c2 d*c3]'+n(noise);
  p7 =[-d*c1 d*c2 d*c3]'+n(noise);
  p8 =[ 0    d    0]'+n(noise);
  
  % The rest of atoms are deduced using the symmmetries
  % axes of symmetry along Z 
  xc=d*(1-2*c1)/2;
  yc=d/2;
  
  % Symmetric atoms (half of them)
  
  p2 =[2*xc-p6(1) 2*yc-p6(2) p6(3)]';
  p3 =[2*xc-p7(1) 2*yc-p7(2) p7(3)]';
  p4 =[2*xc-p8(1) 2*yc-p8(2) p8(3)]';
  p5 =[2*xc-p1(1) 2*yc-p1(2) p1(3)]';

  % axes of symmetry along Y 
  
  zc=d*c3+d*tan(b)/2;
    
  p9 =[2*xc-p4(1) p4(2) 2*zc-p4(3)]';
  p10=[2*xc-p3(1) p3(2) 2*zc-p3(3)]';
  p11=[2*xc-p2(1) p2(2) 2*zc-p2(3)]';
  p12=[2*xc-p1(1) p1(2) 2*zc-p1(3)]';
  p13=[2*xc-p8(1) p8(2) 2*zc-p8(3)]';
  p14=[2*xc-p7(1) p7(2) 2*zc-p7(3)]';
  p15=[2*xc-p6(1) p6(2) 2*zc-p6(3)]';
  p16=[2*xc-p5(1) p5(2) 2*zc-p5(3)]';

  % define the positions and the graph
 
  p=[p1 p2 p3 p4 p5 p6 p7 p8 p9 p10 p11 p12 p13 p14 p15 p16 ];
  G={[1 2],[2 3],[3 4],[4 5],[5 6],[6 7],[7 8],[8,1],[9 10],[10 11],[11 12],[12 13],[13 14],[14 15],[15 16],[16 9],[3 10],[7 14]};
  
  
  S{1}=[5 6 7 8 1 2 3 4 13 14 15 16 9 10 11 12]; % Z
  S{2}=[12 11 10 9 16 15 14 13 4 3 2 1 8 7 6 5]; % Y
  S{3}=[16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1]; % X
