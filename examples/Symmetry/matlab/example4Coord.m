function [p G S]=example4Coord(noise)
  
  % parameters
  d=1.526;  % bond length
  a=1.9111; % bond angle
    
  % ct to determine the positions of the main atoms
  s=d*sqrt(2*(1-cos(a)));
  
  x=d*cos(a);
  y=s/2;
  z=d*sqrt((1-2*cos(a)^2+cos(a))/2);
  
  % coordinates of p17
  x1=x-sqrt(d^2-z^2);
  y1=s/2;
  z1=2*z;
  
  n=@(r)(2*r*rand(3,1)-r);
   
  % fist we set main group of atoms at the left-bottom part
  p1 =[0 0 0]'+n(noise);
  p6 =[0 s+d 0]'+n(noise);
  p7 =[x y+d z]'+n(noise);
  p8 =[x y z]'+n(noise);
  p17=[x1 y1 z1]'+n(noise);
  p19=[x1 y1+d z1]'+n(noise);
  
  % the rest is set by symmetry
  % first the right part from the left-bottom
  
  % origin of the 1st axis of symmetry (along Z)
  xc=d/2;
  yc=(s+d)/2;
  
  p2 =[2*xc-p6(1) 2*yc-p6(2) p6(3)]';
  p3 =[2*xc-p7(1) 2*yc-p7(2) p7(3)]';
  p4 =[2*xc-p8(1) 2*yc-p8(2) p8(3)]';
  p5 =[2*xc-p1(1) 2*yc-p1(2) p1(3)]';
  p21=[2*xc-p19(1) 2*yc-p19(2) p19(3)]';
  p23=[2*xc-p17(1) 2*yc-p17(2) p17(3)]';
  
  
  % and then the top part
  % origin of the 2nc axis of symmetry (along Y)
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
  p18=[2*xc-p21(1) p21(2) 2*zc-p21(3)]';
  p20=[2*xc-p23(1) p23(2) 2*zc-p23(3)]';
  p22=[2*xc-p17(1) p17(2) 2*zc-p17(3)]';
  p24=[2*xc-p19(1) p19(2) 2*zc-p19(3)]';
 

  p=[p1 p2 p3 p4 p5 p6 p7 p8 p9 p10 p11 p12 p13 p14 p15 p16 p17 p18 p19 p20 p21 p22 p23 p24];
  
  
  G={[1 2],[2 3],[3 4],[4 5],[5 6],[6 7],[7 8],[8,1],[9 10],[10 11],[11 12],[12 13],[13 14],[14 15],[15 16],[16 9],[8 17],[17 18] [18 16] [7 19] [19 20] [20 15] [3 21] [21 22] [22 11] [4 23] [23 24] [24 12]};
 
  S{1}=[5 6 7 8 1 2 3 4 13 14 15 16 9 10 11 12 23 24 21 22 19 20 17 18];
  S{2}=[10 9 16 15 14 13 12 11 2 1 8 7 6 5 4 3 22 21 24 23 18 17 20 19];
  