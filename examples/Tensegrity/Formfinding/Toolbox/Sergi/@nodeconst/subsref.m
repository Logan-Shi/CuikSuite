function out=subsref(nc,index)
% Subscripted reference for objects
% this function allows to retrieve the value of internal nodeconst object 
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
                out=subsref(nc(index(1).subs{:}),index(2:size(index,2)));
            catch
                rethrow(lasterror);
            end
        else
            out=nc(index(1).subs{:});
        end
    case '.'        
        switch index(1).subs
            case 'position'
                if size(index,2)>1
                    try
                        out=subsref(nc.position,index(2:size(index,2)));
                    catch
                        rethrow(lasterror);
                    end
                else
                    out=nc.position;
                end
            case 'num_forces'
                out=nc.num_forces;
            case 'forces'
                if size(index,2)>1
                    try
                        out=subsref(nc.forces,index(2:size(index,2)));
                    catch
                        rethrow(lasterror);
                    end
                else
                    out=nc.forces;
                end
            otherwise
                try
                    out=subsref(nc.node,index);
                catch
                    rethrow(lasterror);
                end
        end
    case '{}'
        error('nodeconst - Cell array indexing not allowed for node constraint objects');
end