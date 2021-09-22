function file=close(file)
% closes the file associated to an object
% this function closes the file associated to an object an set all
% attribute to its default value.
%
% file=close(file) return a modified version of the file object passed as
% argument after closing the file.
% 
% See also file

if file.id~=-1
    if fclose(file.id)==-1
        error('file - Impossible to close the file');
    else
        file.id=-1;
        file.filename='none';
        file.line=0;
    end
else
    error('file - File already closed');
end