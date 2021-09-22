function printCML(p,G)

  fprintf('<molecule>\n');
  fprintf('  <atomArray>\n');
  n=size(p,2);
  for i=1:n
    fprintf('    <atom id="a%u" elementType="C" x3="%.6f" y3="%.6f" z3="%.6f"/>\n',i,p(1,i),p(2,i),p(3,i));
  end
  fprintf('  </atomArray>\n');
  fprintf('  <bondArray>\n');
  n=size(G,2);
  for i=1:n
    edge=G{i};
    fprintf('    <bond atomRefs2="a%u a%u" order="1"/>\n',edge(1),edge(2));
  end
  fprintf('  </bondArray>\n');
  fprintf('</molecule>\n');