function S=skew(v)

if length(v)==3
S = [ 0    -v(3)  v(2);
     v(3)   0   -v(1);
    -v(2)  v(1)   0  ];
elseif length(v)==2
S = [-v(2)  v(1)];
end    
   


