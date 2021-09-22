function plotExample(p,G)

  clf;
  hold on;
  
  n=size(G,2);
  for i=1:n
    edge=G{i};
    s=edge(1);
    e=edge(2);
    line([p(1,s) p(1,e)],[p(2,s) p(2,e)],[p(3,s) p(3,e)],'color','black','linewidth',2,'marker','o');
  end
  axis equal
  
