function out=subsref(v,index)
% Subscripted reference for objects
% this function allows to retrieve the value of internal tenvar object 
% atributs. All internal attributes can be accessed by () and . 
% indexing modes
%
% A(i) returns the element at the i-th position
% 
% A.i return the field identified by i
%
% See also edge

switch index(1).type
    case '()'
        if size(index,2)>1
            try
                out=subsref(v(index(1).subs{:}),index(2:size(index,2)));
            catch
                rethrow(lasterror);
            end
        else
            out=v(index(1).subs{:});
        end
    case '.'
        switch index(1).subs
            case 'type'
                out=v.type;
            case 'name'
                out=v.name;
            case 'var'
                out=v.var;
            case 'value'
                if size(index,2)>1
                    switch index(2).type
                        case '()'
                            out=v.value(index(2).subs{:});
                        otherwise
                            error('tenvar - Invalid indexing mode');
                    end
                else
                    out=v.value;
                end
        end
    case '{}'
        error('tenvar - cell array indexing not supported by node objects');
 end