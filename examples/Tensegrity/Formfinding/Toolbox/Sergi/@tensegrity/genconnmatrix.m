function conn=genconnmatrix(t)
% generates the connection matrix for the tensegrity
% this function generates the connection matrix for the tensegrity which is
% a square matrix of dimension equal to the number of nodes, where a '1' in
% a position indicates that the two nodes are connected through and edge.
%
% conn=genconnmatrix(t) return the connection matrix for the tensegrity
% object.
%
% The tensegrity (t) object must be initialized before calling this 
% function.
% 
% See also tesnegrity

conn=zeros(t.num_nodes,t.num_nodes);
try
    for i=1:1:t.num_edges
        origin_node=t.edges(i).origin;
        end_node=t.edges(i).end;
        index1=getnodeindex(t,origin_node);
        index2=getnodeindex(t,end_node);
        conn(index1,index2)=1;
        conn(index2,index1)=1;
    end
catch
    rethrow(lasterror);
end