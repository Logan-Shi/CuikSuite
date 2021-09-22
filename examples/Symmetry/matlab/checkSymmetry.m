function s=checkSymmetry(atoms,pair,G)
  
  % Set pair(i)=0 for atoms without any pair
  
  nac=size(pair,2); % number of atoms in the molecule = number of pairings
  if (nac<3)
    error('At least 3 correspondances are necessary in checkSymmetry');
  end
  
  if (size(atoms,2)~=3)
    Error('checkSymmetry is only valid for 3D points');
  end
  
  n=size(G,2); % number of edges in the graph
  
  m=size(atoms,1)/nac; % number of conformations
  s=zeros(m,1);  % evaluation of the symmetry conditions for each conf.
  
  range=1:nac; % range of atoms pos. for the current conf.
  
  for j=1:n  % for all edges, check if they exits under the symmetry
    edge=G{j};
    a=edge(1); % edge origin
    b=edge(2); % edge end
    
    as=pair(a); % pairing edge, if any
    bs=pair(b);
    
    if (a>0)&&(b>0)&&(as>0)&&(bs>0)
      
      % os<->es must be connected by an edge in the graph
      found=false;
      k=1;
      while (~found)&&(k<=n)
        edge1=G{k};
        found=(((edge1(1)==as)&&(edge1(2)==bs))||((edge1(1)==bs)&&(edge1(2)==as)));
        k=k+1;
      end
      
      if (~found)
        s=s+1;
      end
    end
  end
  
  for i=1:m
    data=atoms(range,:);
    
    % search the firsst two atoms to include in the symmetry check
    a1=1;
    while pair(a1)==0
      a1=a1+1;
    end
    a2=a1+1;
    while pair(a2)==0
      a2=a2+1;
    end
    
    % origin of the axis of symmetry
    o=(data(a1,:)+data(pair(a1),:))/2;
    % director vector of the axis of symmetry
    v1=data(a1,:)-data(pair(a1),:);
    v2=data(a2,:)-data(pair(a2),:);
    v=cross(v1,v2);
    nv=norm(v);
    if nv<1e-10
      v=(data(a2,:)+data(pair(a2),:))/2-o;
      nv=norm(v);
      if nv<1e-10
        error('Can not determine symmetry axis');
      end
      v=v/norm(v);
    else
      v=v/nv;
    end
    
    ns=0;
    for j=(a2+1):nac
      % For the rest of couples of points check that their middle
      % point is on the line o,v
      
      k=pair(j);
      if (k>j) % avoid testing the same couple twice (also ensures k>0)
        % The average must be on the symmetry axis (v)
        m=(data(j,:)+data(k,:))/2-o;
        nm=norm(m);
        if nm<1e-10
          e1=0; % both points are on the axis
        else
          m=m/norm(m);
          e1=abs(1-abs(v*m'));
        end
          
        % and check that their connection is orthogobal to symmetry axis (v)
        w=(data(j,:)-data(k,:));
        e2=abs(v*w');
      
        % accumulate errors
        s(i)=s(i)+max(e1+e2);
        ns=ns+1;
      end
    end
    s(i)=s(i)/ns;
    
    range=range+nac;
  end
  
   
  