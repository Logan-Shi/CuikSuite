function t=generatecomplete(t,num)
% generates a tensegrity with all edges
% this function generates a tensegrity with num nodes and all edges
% present. The number of nodes must be even because each strut needs to
% exclusive nodes.
%
% t=generatecomplete(t,num) returns a modified version of a
% tensegrity object equivalent to tensegrity with num nodes and all
% possible edges.
%
% The tensegrity (t) object must be initialized before calling this 
% function and the rows and columns parameters must be positive integers.
%
% See also tensegrity

if isa(t,'tensegrity')
    if mod(num,2)
        error('tensegrity - The number of nodes must be even');
    else
        try
            t.dimension=3;
            t.class=1;
            nodes=node();
            num_nodes=0;
            for i=1:1:num
                num_nodes=num_nodes+1;
                nodes(num_nodes)=node(['node',num2str(num_nodes)],0,[]);
            end
            num_edges=0;
            edges=edge();
            for i=1:1:num
                for j=i+1:1:num
                    num_edges=num_edges+1;
                    if j>num_nodes/2 && i==(j-num/2)
                        edges(num_edges)=edge(['edge',num2str(num_edges)],'strut','none','none');
                    else
                        edges(num_edges)=edge(['edge',num2str(num_edges)],'cable','none','none');
                    end
                    [nodes(i),edges(num_edges)]=addincidentedge(nodes(i),edges(num_edges));
                    [nodes(j),edges(num_edges)]=addincidentedge(nodes(j),edges(num_edges));
                end
            end
            % afegir els nodes i arestes al tensegrity
            for i=1:1:num_nodes
                t=addnode(t,nodes(i));
            end
            for i=1:1:num_edges
                t=addedge(t,edges(i));
            end
        catch
            rethrow(lasterror);
        end
    end
else
    error('tensegrity - Invalid tensegrity structure');
end