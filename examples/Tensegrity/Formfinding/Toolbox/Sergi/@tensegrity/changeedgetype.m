function [t,edge]=changeedgetype(t,edge,new_type)
% changes the type of and edge
% this function changes the type of an edge included into a tensegrity
% object, updating the number of cables and struts, and also contrlling
% that the class of the tensegrity is verified at any time.
%
% [t,edge]=changeedgetype(t,edge,new_type) return the modified version of
% both the tensegrity object and the edge object.
%
% Both the tensegrity object and the edge object must be initialized before
% calling this function. The new_type parameter must be a srting equal to
% either 'cable' or 'strut'.
%
% See also tensegrity,edge

if ~isa(t,'tensegrity')
    error('temsegrity - Invalid tensegrity structure');
end
if ~isa(edge,'edge')
    error('tensegrity - Invalid edge structure');
end
if ~ischar(new_type)
    error('tensegrity - The new type value must be a string');
end
if ~strcmp(edge.type,new_type)
    try
        if strcmp(new_type,'cable')
            t.num_struts=t.num_struts-1;
            t.num_cables=t.num_cables+1;
        else
            % check the class of the tensegrity
            n=t.nodes(getnodeindex(t,edge.origin));
            class=1;
            for i=1:1:n.num_edges
                if strcmp(t.edges(getedgeindex(t,n.inc_edges(i).name)).type,'strut')
                    class=class+1;
                    if class>t.class
                        error('tensegrity - Impossible to add strut');
                    end
                end
            end
            n=t.nodes(getnodeindex(t,edge.end));        
            class=1;
            for i=1:1:n.num_edges
                if strcmp(t.edges(getedgeindex(t,n.inc_edges(i).name)).type,'strut')
                    class=class+1;
                    if class>t.class
                        error('tensegrity - Impossible to add strut');
                    end
                end
            end
            t.num_struts=t.num_struts+1;
            t.num_cables=t.num_cables-1;
        end
        edge.type=new_type;    
    catch
        rethrow(lasterror);
    end
end
