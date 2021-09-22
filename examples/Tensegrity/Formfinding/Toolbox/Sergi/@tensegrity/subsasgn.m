function t=subsasgn(t,index,val)
% Subscripted assignment for objects
% this function allows to modify the value of some internal tensegrity object 
% atributs. The number of nodes, edges, cables and struts are automatically
% updated when nodes and edges are added and removed, and can not be
% modified using this function.
%
% See also file

switch index(1).type
    case '()'
        if size(index,2)>1
            try
                t(index(1).subs{:})=subasgn(tsegrity(t(index(1).subs{:})),index(2:size(index,2)));
            catch
                rethrow(lasterror);
            end
        else
            if isa(val,'tensegrity')
                t(index(1).subs{:})=val;
            else
                error('tensegrity - Invalid parameter value');
            end
        end
    case '.'
        switch index(1).subs
            case 'class'
                try 
                    t=setclass(t,val);
                catch
                    rethrow(lasterror);
                end
            case 'dimension'
                try
                    t=setdimension(t,val);
                catch
                    rethrow(lasterror);
                end
            case 'name'
                try
                    t=setname(t,val);
                catch
                    rethrow(lasterror);
                end
            case 'nodes'
                if size(index,2)>1
                    switch index(2).type
                        case '()'
                            if size(index,2)>2
                                try
                                    t.nodes(index(2).subs{:})=subsasgn(t.nodes(index(2).subs{:}),index(3:size(index,2)),val);
                                catch
                                    rethrow(lasterror);
                                end
                            else
                                t.nodes(index(2).subs{:})=val;
                            end
                        case '.'
                            error('tensegrity - field indexing not supported by tensegrity objects');
                        case '{}'
                            error('tensegrity - cell array indexing not supported by tensegrity objects');
                    end
                else
                    if isa(val,'node')
                        error('tensegrity - Impossible to modify an internal node');
                    else
                        error('tensegrity - Invalid parameter value');
                    end
                end
            case 'edges'
                if size(index,2)>1
                    switch index(2).type
                        case '()'
                            if size(index,2)>2
                                try
                                    t.edges(index(2).subs{:})=subsasgn(t.edges(index(2).subs{:}),index(3:size(index,2)),val);
                                catch
                                    rethrow(lasterror);
                                end
                            else
                                t.edges(index(2).subs{:})=val;
                            end
                        case '.'
                            error('tensegrity - field indexing not supported by tensegrity objects');
                        case '{}'
                            error('tensegrity - cell array indexing not supported by tensegrity objects');
                    end
                else
                    if isa(val,'edge')
                        error('tensegrity - Impossible to madify an internal edge');
                    else
                        error('tensegrity - Invalid parameter value');
                    end
                end
            otherwise
                error('tensegrity - Impossible to access private members');
        end
    case '{}'
        error('tensegrity - cell array indexing not supported by tensegrity objects');
end
