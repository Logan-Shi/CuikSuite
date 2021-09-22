function file=open(file,filename,mode)
% opens and associate a file to a file object
% this function opens a file referenced by filanme in the mode specified by
% mode and associates it to the input file object. If the object already has
% an associated file, it is closed and the new file is associated.
%
% file=open(file,filename,mode) return a modified version of the file 
% object passed as argument after associating the new file.
% 
% See also file

if isa(file,'file')
    if file.id~=-1
        fclose(file.id);
        file.id=-1;
        file.filename=[];
        file.line=0;
    end
    if ischar(filename) && ischar(mode)
        file.id=fopen(filename,mode);
        if file.id==-1
            error('file - Impossible to open the file');
        else
            file.filename=filename;
            file.line=0;
        end
    else
        error=('file - Invalid filename');
    end
else
    error('file - Invalid file object');
end