% Auxiliary function to compute the resultant force in a node
%
% Inputs
%     i: node num
%     T: Tensegrity structure
%
% Outputs
%     v: The resulting vector (must be 0 for force-balanced nodes).
%
function v=forceInNode(i,T)
  v=[0 0 0]';
  if ~isfield(T,'equilibriumNode') || T.equilibriumNode(i)
    for j=1:T.nBars
      n1=T.bars{j}(1);
      n2=T.bars{j}(2);
      if (n1==i)||(n2==i)
        if (n1==i)
          sg=-1;
        else
          sg=+1;
        end
        t=T.p(ndx(n2))-T.p(ndx(n1));
        l=norm(t);
        w=sg*t;
        w=w/l; % must be normal along the bar
        v=v+w*T.compression(j);
      end
    end
    
    for j=1:T.nStrings
      n1=T.strings{j}(1);
      n2=T.strings{j}(2);
      if (n1==i)||(n2==i)
        if (n1==i)
          sg=+1;
        else
          sg=-1;
        end
        t=T.p(ndx(n2))-T.p(ndx(n1));
        l=norm(t);
        w=sg*t;
        w=w/l; % normal along the string
        v=v+w*T.tension(j);
      end
    end
  end