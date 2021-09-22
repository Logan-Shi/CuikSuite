function out=subsref(t,index)
% Subscripted reference for objects
% this function allows to retrieve the value of internal tensegrity object 
% atributs. All internal attributes can be accessed by () and . 
% indexing modes
%
% A(i) returns the element at the i-th position
% 
% A.i return the field identified by i
%
% See also tensegrity

switch index(1).type
    case '()'
        if size(index,2)>1
            if size(t,2)>1
                try
                    out=subsref(t(index(1).subs{:}),index(2:size(index,2)));
                catch
                    rethrow(lasterror);
                end
            else
                error('tensegrity - Invalid element index');
            end
        else
            out=t(index(1).subs);
        end
    case '.'
        switch index(1).subs
            case 'name'
                out=t.name;
            case 'filename'
                out=t.filename;
            case 'dimension'
                out=t.dimension;
            case 'class'
                out=t.class;
            case 'num_nodes'
                out=t.num_nodes;
            case 'num_edges'
                out=t.num_edges;
            case 'num_cables'
                out=t.num_cables;
            case 'num_struts'
                out=t.num_struts;
            case 'nodes'
                if size(index,2)>1
                    switch index(2).type
                        case '()'
                            if size(index,2)>2
                                try
                                    out=subsref(t.nodes,index(2:size(index,2)));
                                catch
                                    rethrow(lasterror);
                                end
                            else
                                try
                                    out=getnode(t,index(2).subs{:});
                                catch
                                    rethrow(lasterror);                                    
                                end
                            end
                        case '.'
                            error('tensegrity - field indexing not supported by tensegrity objects');
                        case '{}'
                            error('tensegrity - cell array indexing not supported by tensegrity objects');
                    end
                else
                    out=t.nodes;
                end
            case 'edges'
                if size(index,2)>1
                    switch index(2).type
                        case '()'
                            if size(index,2)>2
                                try
                                    out=subsref(t.edges,index(2:size(index,2)));
                                catch
                                    rethrow(lasterror);                                    
                                end
                            else
                                try
                                    out=getedge(t,index(2).subs{:});
                                catch
                                    rethrow(lasterror);                                    
                                end
                            end
                        case '.'
                            error('tensegrity - field indexing not supported by tensegrity objects');
                        case '{}'
                            error('tensegrity - cell array indexing not supported by tensegrity objects');
                    end
                else
                    out=t.edges;
                end
        end
    case '{}'
        error('tensegrity - cell array indexing not supported by tensegrity objects');
end