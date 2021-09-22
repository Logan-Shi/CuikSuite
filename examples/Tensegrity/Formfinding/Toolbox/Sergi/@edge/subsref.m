function out=subsref(edge,index)
% Subscripted reference for objects
% this function allows to retrieve the value of internal edge object 
% atributs. All internal attributes can be accessed by () and . 
% indexing modes
%
% A(i) returns the element at the i-th position
% 
% A.i return the field identified by i
%
% See also edge

global error;
switch index(1).type
    case '()'
        if size(index,2)>1
            try
                out=subsref(edge(index(1).subs{:}),index(2:size(index,2)));
            catch
                rethrow(lasterror);
            end
        else
            out=edge(index(1).subs{:});
        end
    case '.'
        switch index(1).subs
            case 'name'
                out=edge.name;
            case 'type'
                out=edge.type;
            case 'origin'
                out=edge.origin;
            case 'end'
                out=edge.end;
        end
    case '{}'
        error('edge - cell array indexing not supported by edge objects');
end