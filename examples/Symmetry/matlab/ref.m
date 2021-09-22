function [T iT]=ref(c,px,py)


  vx=px-c;
  vx=vx/norm(vx);
  
  vy=py-c;
  vy=vy/norm(vy);
  
  vz=cross(vx,vy);
  vz=vz/norm(vz);
  
  vy=cross(vz,vx);
  
  T=[vx vy vz c ; 0 0 0 1];
  iT=inv(T);
  
  line([c(1) c(1)+vx(1)],[c(2) c(2)+vx(2)],[c(3) c(3)+vx(3)],'color','red','linewidth',2);
  line([c(1) c(1)+vy(1)],[c(2) c(2)+vy(2)],[c(3) c(3)+vy(3)],'color','green','linewidth',2);
  line([c(1) c(1)+vz(1)],[c(2) c(2)+vz(2)],[c(3) c(3)+vz(3)],'color','blue','linewidth',2);
  