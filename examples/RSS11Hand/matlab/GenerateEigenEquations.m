function GenerateEigenEquations(fname,neqs)

  hm='new_hand_motions';

  fprintf('\nReading samples: %s.links\n',hm);
  cuik=load([hm '.links']);
  
  fprintf('Reading variable mask: %s.vmask\n',hm);
  mask=load([hm '.vmask']);
  nv=size(mask,2);

  % the position of the ref. frames for the last phalanx must not be used
  mask((nv-9):nv)=0;
  mask=(mask>0.1);
    
  % Remove the dimensions with no variance
  t=max(cuik);
  b=min(cuik);
  d=t-b;
  mask(d<1e-6)=0;
  
  % Actual dimension of the points
  dim=sum(mask);
  
  fprintf('Selecting variables\n');
  cuikGood=cuik(:,mask);

  fprintf('Performing principal component analysis\n');
  [E S l] = princomp(cuikGood);
  fprintf('Variance: %g\n',sum(l(1:(dim-neqs)))/sum(l))
  
  %E=rand(sum(dim));
  
  fprintf('Reading variable names: %s.vname\n',hm);
  names=textread([hm '.vname'],'%s');
  
  n=size(names,1); 
  
  if n~=nv
    error('Dimension missmatch in GenerateEigenEquations');
  end
  
  names=names(mask);
  
  % Read the seed sample
  
  f=[fname '_with_contacts_with_eigens.links'];
  fprintf('Reading center: %s\n',f);
  center=load(f);
  center=center(1:nv); % keep the open loop variables (nv first ones)
  center=center(mask);
  
  % The less relevant eigenvectors define the sub-space to keep
  % (the good ponits are those in the orthogonal complement of these
  % vectors).
  Eqs=E(:,(dim-neqs+1):end)';
  
  m=mean(cuikGood);
  e=sqrt(norm(center-m)^2-norm(Eqs*(center-m)')^2);
  fprintf('Error of center with respect to eigen-subspcace: %g\n',e);
  
  fprintf('Computing offset\n');
  % offset=E(:,(dim-neqs+1):end)'*center';
  offset=Eqs*center';
  
  fname=[fname '_eigens.cuik'];
  fprintf('Generating equations %s\n',fname);
  f=fopen(fname,'w');
  fprintf(f,'[SYSTEM EQS]\n');
  for i=1:neqs
    for j=1:dim
      if abs(E(j,i+(dim-neqs)))>1e-8
        % fprintf(f,'%+.12g*%s',E(j,i+(dim-neqs)),names{j});
        fprintf(f,'%+.12g*%s',Eqs(i,j),names{j});
      end
    end
    fprintf(f,'=%.12g;\n',offset(i));
  end
  fclose(f);
  
  exit;  

