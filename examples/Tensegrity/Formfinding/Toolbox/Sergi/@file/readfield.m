function [field_out,file]=readfield(file,field)
% reads a generic parameter from the file associated to the object
% this function reads a generic parameter following the field identifier 
% from the file associated ot the object.
%
% [field_out,file]=readfield(file,field) return a modified version of the
% file object passed as argument after reading the real value from the
% file, as well as the string following the field identifier text.
%
% field must be a string with a text which would be put before the desired
% string ('' can be used if no tag is required). The file object must be
% initialized before calling this function.
% 
% See also file

field_out=[];
if isa(file,'file')
    if file.id==-1
        error('file - The file is not opened');
    else
        try
            [line,file]=readline(file);
            if ~strncmp(line,field,size(field,2))
                error('file -Invalid file format');
            else
                field_out=line(size(field,2)+1:size(line,2));
            end
        catch
            rethrow(lasterror);
        end
    end
else
    error('file - Invalid file structure');
end
