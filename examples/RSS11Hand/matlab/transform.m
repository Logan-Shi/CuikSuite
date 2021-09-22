function T=transform(dx,dy,dz,ax,ay,az)

%T=transform(dx,dy,dz,ax,ay,az)
%
%Returns a 4x4 matrix with a given 3D transform
%d = distance of translation
%a = angle of rotation in deg


Trx=[ 1       0        0       0;
      0     cos(ax) -sin(ax)   0;
      0     sin(ax)  cos(ax)   0;
      0       0        0       1];
Try=[cos(ay)   0    sin(ay)   0;
       0       1      0       0;
    -sin(ay)   0    cos(ay)   0;
       0       0      0       1];
Trz=[cos(az) -sin(az)  0       0;
     sin(az)  cos(az)  0       0;
       0        0      1       0;
       0        0      0       1];
Ttx=[ 1       0       0      dx;
      0       1       0       0;
      0       0       1       0;
      0       0       0       1];
Tty=[ 1       0       0       0;
      0       1       0      dy;
      0       0       1       0;
      0       0       0       1];
Ttz=[ 1       0       0       0;
      0       1       0       0;
      0       0       1      dz;
      0       0       0       1];
  
T=Ttx*Tty*Ttz*Trx*Try*Trz;
 