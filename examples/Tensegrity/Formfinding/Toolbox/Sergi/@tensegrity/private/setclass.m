function t=setclass(t,class)
% sets the class of the tensegrity structure
% this private functions change the maximum number of rigid edges attached
% to a single node.
%
% t=setclass(t,class) returns a modified version of the tensegrity structure
% with the new class.
%
% The tensegrity object must be initialized before calling this function
% and the class parameter must be an integer between 1 and 5.
%
% See also tensegrity

if isa(t,'tensegrity')
    if (~isnumeric(class))
        error('tensegrity - The class value must be an integer');
    else
        if (class<1 || class>5)
            error('tensegrity - Invalid class value');
        else
            if class<t.class
                for i=1:1:t.num_nodes
                    old_class=0;
                    for j=1:1:n.num_edges
                        if strcmp(t.edges(t.nodes(i).inc_edges(j).name).type,'strut')
                            old_class=old_class+1;
                            if old_class>class
                                error('tensegrity - Impossible to change the class');
                            end
                        end
                    end
                end
            end
            t.class=class;
        end
    end
else
    error('tensegrity - Invalid tensegrity structure');    
end
