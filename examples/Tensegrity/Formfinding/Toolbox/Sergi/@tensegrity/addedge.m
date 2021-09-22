function t=addedge(t,e)
% adds an edge to the tensegrity structure
% this function adds a previously initialized edge in the internal edge
% list. The total number of edges is automatically updated, as well as the
% number of struts or cables depending on the type of the edge.
%
% t=addedge(t,e) return a modified version of the tensegrity object (t)
% with the edge (e) added.
%
% Both the tensegrity object and the edge object must be initialized before
% calling this function.
%
% See also tensegrity,edge

if isa(t,'tensegrity')
    if isa(e,'edge')
        for i=1:1:t.num_edges
            if strcmp(t.edges(i).name,e.name)==1
                error('tensegrity - Edge already present');
            end
        end
        t.num_edges=t.num_edges+1;
        if strcmp(e.type,'cable') t.num_cables=t.num_cables+1;
        else t.num_struts=t.num_struts+1;
        end
        if t.num_edges==1
            t.edges=e;
        else
            t.edges(t.num_edges)=e;
        end
    else
        error('tensegrity - Invalid edge structure');
    end
else
    error('tensegrity - Invalid tensegrity structure');    
end
