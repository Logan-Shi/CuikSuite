function file=subsasgn(file,index,val)
% Subscripted assignment for objects
% this function allows to modify the value of internal file object 
% atributs. All file class attributes are private and can not be modified
% externally to the object
%
% See also file

switch index.type
    case '()'
        error('file - vector indexing not supported by file objects');
    case '.'
        error('file - Impossible to access private members');
    case '{}'
        error('file - cell array indexing not supported by file objects');
end