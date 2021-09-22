function [p G S]=example1Coord(noise)

  % generates coordinates for example1
  % example2 is only different in the connections but coordinates are the same

  d=1.526;  % bond length
  a=1.9111; % bond angle
  
  s=d*sqrt(2*(1-cos(a)));
  
  x=d*cos(a);
  y=s/2;
  z=d*sqrt((1-2*cos(a)^2+cos(a))/2);
  
  n=@(r)(2*r*rand(3,1)-r);
  
  % atom pos (half of them)
  p1 =[0 0 0]'+n(noise);
  p6 =[0 s+d 0]'+n(noise);
  p7 =[x y+d z]'+n(noise);
  p8 =[x y z]'+n(noise);
  
  
  p9 =[0 0 4*z+d]'+n(noise);
  p14 =[0 s+d 4*z+d]'+n(noise);
  p15 =[x y+d 3*z+d]'+n(noise);
  p16 =[x y 3*z+d]'+n(noise);
 
  
  % axes of symmetry along Z 
  xc=d/2;
  yc=(s+d)/2;
  
  % Symmetric atoms (half of them)
  
  p2 =[2*xc-p6(1) 2*yc-p6(2) p6(3)]';
  p3 =[2*xc-p7(1) 2*yc-p7(2) p7(3)]';
  p4 =[2*xc-p8(1) 2*yc-p8(2) p8(3)]';
  p5 =[2*xc-p1(1) 2*yc-p1(2) p1(3)]';

  p10 =[2*xc-p14(1) 2*yc-p14(2) p14(3)]';
  p11 =[2*xc-p15(1) 2*yc-p15(2) p15(3)]';
  p12 =[2*xc-p16(1) 2*yc-p16(2) p16(3)]';
  p13 =[2*xc-p9(1) 2*yc-p9(2) p9(3)]';

 

  p=[p1 p2 p3 p4 p5 p6 p7 p8 p9 p10 p11 p12 p13 p14 p15 p16 ];
  G={[1 2],[2 3],[3 4],[4 5],[5 6],[6 7],[7 8],[8,1],[9 10],[10 11],[11 12],[12 13],[13 14],[14 15],[15 16],[16 9],[8 16],[4 12]};
  
  S{1}=[5 6 7 8 1 2 3 4 13 14 15 16 9 10 11 12];
