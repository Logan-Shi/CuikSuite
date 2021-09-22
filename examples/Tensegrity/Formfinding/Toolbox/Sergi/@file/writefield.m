function file=writefield(file,field,value)
% writes a generic parameter into the file associated to the object
% this function writes a generic parameter following the field identifier 
% to the file associated to the object.
%
% file=writefield(file,field,calue) return a modified version of the
% file object passed as argument after writing the real value into the file.
%
% field must be a string with a text which would be put before the desired
% string ('' can be used if no tag is required). The file object must be
% initialized before calling this function.
% 
% See also file

if isa(file,'file')
    if file.id==-1
        error('file - The file is not opened');
    else
        line=[field,value];
        written=fprintf(file.id,'%s\n',line);
        if written~=(size(line,2)+1)
            error('file - Impossible to write to file');
        end
    end
else
    error('file - Invalid file structure');
end
