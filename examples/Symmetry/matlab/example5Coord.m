function [p G S]=example5Coord(noise)

  % parameters
  d=1.526;  % bond length
  a=1.9111; % bond angle
    
  % Cts to get the position of the atoms
  
  s=d*sqrt(2*(1-cos(a)));
  
  x=d*cos(a);
  y=s/2;
  z=d*sqrt((1-2*cos(a)^2+cos(a))/2);
  
  x1=x-sqrt(d^2-z^2);
  y1=s/2;
  z1=2*z;
  
  n=@(r)(2*r*rand(3,1)-r);
  
  % atom positions
  p1=[0 0 0]'+n(noise);
  p2=[d 0 0]'+n(noise);
  p3=[d-x y z]'+n(noise);
  
  p7=[0 0 2*z+d]'+n(noise);
  p8=[d 0 2*z+d]'+n(noise);
  p9=[d-x y 3*z+d]'+n(noise);
  
  p13=[x1 y1 z1]'+n(noise);
  p14=[x1 y1 z1+d]'+n(noise);
  
  % axes of symmetry along Z 
  xc=d/2;
  yc=s/2;
  
  p4 =[2*xc-p1(1) 2*yc-p1(2) p1(3)]';
  p5 =[2*xc-p2(1) 2*yc-p2(2) p2(3)]';
  p6 =[2*xc-p3(1) 2*yc-p3(2) p3(3)]';
  p10=[2*xc-p7(1) 2*yc-p7(2) p7(3)]';
  p11=[2*xc-p8(1) 2*yc-p8(2) p8(3)]';
  p12=[2*xc-p9(1) 2*yc-p9(2) p9(3)]';
  p15=[2*xc-p13(1) 2*yc-p13(2) p13(3)]';
  p16=[2*xc-p14(1) 2*yc-p14(2) p14(3)]';
 

  p=[p1 p2 p3 p4 p5 p6 p7 p8 p9 p10 p11 p12 p13 p14 p15 p16];
  
  G={[1 2],[2 3],[3 4],[4 5],[5 6],[6 1],[7 8],[8 9],[9 10],[10 11],[11 12],[12 7],[6 13],[13 14],[14 12],[3 15],[15 16],[16 9]};
  
  S{1}=[4 5 6 1 2 3 10 11 12 7 8 9 15 16 13 14]; % Z
  S{2}=[4 5 6 1 2 3 0 0 0 0 0 0 0 0 0 0]; % Z lower ring
  S{3}=[0 0 0 0 0 0 10 11 12 7 8 9 0 0 0 0]; % Z upper ring
  