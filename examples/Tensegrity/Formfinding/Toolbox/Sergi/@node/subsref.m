function out=subsref(n,index)
% Subscripted reference for objects
% this function allows to retrieve the value of internal node object 
% atributs. All internal attributes can be accessed by () and . 
% indexing modes
%
% A(i) returns the element at the i-th position
% 
% A.i return the field identified by i
%
% See also node

switch index(1).type
    case '()'
        if size(index,2)>1
            try
                out=subsref(n(index(1).subs{:}),index(2:size(index,2)));
            catch
                rethrow(lasterror);
            end
        else
            out=n(index(1).subs{:});
        end
    case '.'
        switch index(1).subs
            case 'name'
                out=n.name;
            case 'num_edges'
                out=n.num_edges;
            case 'inc_edges'
                if size(index,2)>1
                    if strcmp(index(2).type,'()')
                        try
                            out=getincidentedge(n,index(2).subs{:});
                        catch
                            rethrow(lasterror);
                        end
                    else
                        error('node - Invalid indexing type');
                    end
                else
                    out=n.inc_edges;
                end
        end
    case '{}'
        error('node - cell array indexing not supported by node objects');
end