function NewOff(name)
  P=load('points');
  T=load('triangles');
  n=size(P,2);
  np=n/3;
  m=size(T,2);
  nt=m/3;
  f=fopen(name,'w');
  fprintf(f,'OFF %u %u 0\n',np,nt);
  for i=1:3:n
    fprintf(f,'%f %f %f \n',P(i),P(i+1),P(i+2));
  end
    
  for i=1:3:m
    fprintf(f,'3 %u %u %u \n',floor(T(i)),floor(T(i+1)),floor(T(i+2)));
  end
  fclose(f);