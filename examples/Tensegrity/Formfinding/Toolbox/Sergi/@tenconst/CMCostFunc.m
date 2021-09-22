function cost_func=CMCostFunc(tc)
% computes the cost function associated to a problem
% this function generates a cost function from the information inside a
% tenconst object.
%
% cost_func=MinimumEnergy(tc) returns the cost function in symbolic format
% from the constraint information in the tc object.
%
% The tensegrity constraint object must be initialized before calling this
% function.
%
% See also: tenconst,tenopt,constfile

cost_func=sym('0');
for i=1:1:tc.tensegrity.num_edges
    if strcmp(tc.tensegrity.edges(i).type,'cable')
        cost_func=cost_func+tc.tensegrity.edges(i).length.var*tc.tensegrity.edges(i).length.var;        
    else
        cost_func=cost_func-tc.tensegrity.edges(i).length.var*tc.tensegrity.edges(i).length.var;        
    end
end
