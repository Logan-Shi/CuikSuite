function [edge,t_file]=readedgeinfo(t_file,edge)
% reads the topological information of an edge from a file
% this funciton reads from the associated file the topological information of
% an edge, which consist of:
%   * the name of the edge
%   * the type
%   * the name of the origin node
%   * the name of the final node
%
% [edge,t_file]=readedgeinfo(t_file,edge) return a modified version of the
% file object passed as argument after reading the topological information
% of the edge from the file, as well as the modified version of an edge
% object updated with the information rad from the file.
%
% Both the edge object and the file object must be initialized before 
% calling this function.
% 
% See also tenfile,file,edge,readfieldstring,readfieldint

% file tag txt
TypeTxt='Type:';
OrgNodeTxt='Origin:';
EndNodeTxt='End:';

if isa(t_file,'tenfile')
    try
        % read the edge name
        [edge.name,t_file]=readline(t_file);
        % read the type of the edge
        [edge.type,t_file]=readfieldstring(t_file,TypeTxt);
        % read the name of the origin node
        [edge.origin,t_file]=readfieldstring(t_file,OrgNodeTxt);
        % read the name of the end node
        [edge.end,t_file]=readfieldstring(t_file,EndNodeTxt);
    catch
        rethrow(lasterror);
    end
else
    error('tenfile - Invalid file structure');
end
