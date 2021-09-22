function [p G S]=example3Coord(noise)

  % generates coordinates for example3

  d=1.526;  % bond length
  a=1.9111; % bond angle
  
  s=d*sqrt(2*(1-cos(a)));
  
  x=d*cos(a);
  y=s/2;
  z=d*sqrt((1-2*cos(a)^2+cos(a))/2);
  
  n=@(r)(2*r*rand(3,1)-r);
  
  % Atom positions
  p1=[0 0 2*z]'+n(noise);
  p2=[d 0 2*z]'+n(noise);
  p3=[d-x y z]'+n(noise);
  p4=[d-x y+d z]'+n(noise);
  p5=[d s+d 0]'+n(noise);
  p6=[0 s+d 0]'+n(noise);
  p7=[x y+d z]'+n(noise);
  p8=[x y z]'+n(noise);
  

  % Symmetry along Y axis
    
  xc=d/2;
  zc=(4*z+d)/2;
  
  p9 =[2*xc-p2(1) p2(2) 2*zc-p2(3)]';
  p10=[2*xc-p1(1) p1(2) 2*zc-p1(3)]';
  p11=[2*xc-p8(1) p8(2) 2*zc-p8(3)]';
  p12=[2*xc-p7(1) p7(2) 2*zc-p7(3)]';
  p13=[2*xc-p6(1) p6(2) 2*zc-p6(3)]';
  p14=[2*xc-p5(1) p5(2) 2*zc-p5(3)]';
  p15=[2*xc-p4(1) p4(2) 2*zc-p4(3)]';
  p16=[2*xc-p3(1) p3(2) 2*zc-p3(3)]';
 

  p=[p1 p2 p3 p4 p5 p6 p7 p8 p9 p10 p11 p12 p13 p14 p15 p16 ];
  G={[1 2],[2 3],[3 4],[4 5],[5 6],[6 7],[7 8],[8,1],[9 10],[10 11],[11 12],[12 13],[13 14],[14 15],[15 16],[16 9],[8 15],[4 11]};
  
  S{1}=[10 9 16 15 14 13 12 11 2 1 8 7 6 5 4 3];
