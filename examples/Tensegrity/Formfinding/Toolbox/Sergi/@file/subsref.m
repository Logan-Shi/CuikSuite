function out=subsref(file,index)
% Subscripted reference for objects
% this function allows to retrieve the value of internal file object 
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
                out=subsref(file(index(1).subs{:}),index(2:size(index,2)));
            catch
                rethrow(lasterror)
            end
        else
            try
                out=file(index(1).subs{:});
            catch
                rethrow(lasterror)
            end
        end
    case '.'
        switch index(1).subs
            case 'id'
                out=file.id;
            case 'filename'
                out=file.filename;
            case 'line'
                out=file.line;
        end
    case '{}'
        error('file - cell array indexing not supported by file objects');
end