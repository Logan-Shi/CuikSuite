function out=subsref(ec,index)
% Subscripted reference for objects
% this function allows to retrieve the value of internal edgeconst object 
% atributs. All internal attributes can be accessed by () and . 
% indexing modes
%
% A(i) returns the element at the i-th position
% 
% A.i return the field identified by i
%
% See also file

switch index(1).type
    case '()'
        if size(index,2)>1
            try
                out=subsref(ec(index(1).subs{:}),index(2:size(index,2)));
            catch
                rethrow(lasterror);
            end
        else
            out=ec(index(1).subs{:});
        end
    case '.'        
        switch index(1).subs
            case 'stiffness'
                if size(index,2)>1
                    try
                        out=subsref(ec.stiffness,index(2:size(index,2)));
                    catch
                        rethrow(lasterror);
                    end
                else
                    out=ec.stiffness;
                end
            case 'rest_length'
                if size(index,2)>1
                    try
                        out=subsref(ec.rest_length,index(2:size(index,2)));
                    catch
                        rethrow(lasterror);
                    end
                else
                    out=ec.rest_length;
                end
            case 'length'
                if size(index,2)>1
                    try
                        out=subsref(ec.length,index(2:size(index,2)));
                    catch
                        rethrow(lasterror);
                    end
                else
                    out=ec.length;
                end
            otherwise
                try
                    out=subsref(ec.edge,index);
                catch
                    rethrow(lasterror);
                end
        end
    case '{}'
        error('edgeconst - Cell array indexing not allowed for edge constraint objects');
end