function drawSaxis(p,pair,t)

  % t -> first atom whre the symmetry applies (typically 1)
  % Atoms beyond 't' with no symmety have pair(i)=0

  hold on;

%   o=(p(:,1)+p(:,pair(1)))/2;
%   % director vector of the axis of symmetry
%   v1=p(:,1)-p(:,pair(1));
%   v2=p(:,2)-p(:,pair(2));
%   v=cross(v1,v2);
%   nv=norm(v);
%   if nv<1e-10
%     v=(p(2,:)+p(pair(2),:))/2-o;
%     nv=norm(v);
%     if nv<1e-10
%       error('Can not determine symmetry axis');
%     end
%   end
%   v=v/nv;
%   e=o+5*v;
%   line([o(1) e(1)],[o(2) e(2)],[o(3) e(3)],'color','b');
  
  o=(p(:,t)+p(:,pair(t)))/2;
  % director vector of the axis of symmetry
  v1=p(:,t)-p(:,pair(t));
  v2=p(:,t+1)-p(:,pair(t+1));
  v=cross(v1,v2);
  nv=norm(v);
  if nv<1e-10
    v=(p(t+1,:)+p(pair(t+1),:))/2-o;
    nv=norm(v);
    if nv<1e-10
      error('Can not determine symmetry axis');
    end
  end
  v=v/nv;
  
  % draw the axis
  e=o+5*v;
  o=o-5*v;
  line([o(1) e(1)],[o(2) e(2)],[o(3) e(3)],'color','r');
  
  % associate the pairs
  n=size(pair,2);
  for i=1:n
    k=pair(i);
    if i<k
      line([p(1,i) p(1,k)],[p(2,i) p(2,k)],[p(3,i) p(3,k)],'color','g');
    end
  end
  