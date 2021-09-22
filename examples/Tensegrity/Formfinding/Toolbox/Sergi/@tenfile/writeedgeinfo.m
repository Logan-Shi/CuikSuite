function t_file=writeedgeinfo(t_file,edge_in)
% writes the topological information of an edge into a file
% this funciton writes to the associated file the topological information of
% an edge, which consist of:
%   * the name of the edge
%   * the type
%   * the name of the origin node
%   * the name of the final node
%
% t_file=writeedgeinfo(t_file,edge_in) return a modified version of the
% file object passed as argument after writing the topological information
% of the edge into the file.
%
% edge_in must be an initialized edge object and the file object (t_file) 
% must be initialized before calling this function.
% 
% See also tenfile,file,edge,writefieldstring,writefieldint

% file tag txt
TypeTxt='Type:';
OrgNodeTxt='Origin:';
EndNodeTxt='End:';

if isa(t_file,'tenfile')
    if ~isa(edge_in,'edge') 
        error('tenfile - Invalid edge object');
    end
    % write the name of the edge
    t_file=writefieldstring(t_file,'',edge_in.name);
    % write the type of the edge
    t_file=writefieldstring(t_file,TypeTxt,edge_in.type);
    % write the name of the origin node
    t_file=writefieldstring(t_file,OrgNodeTxt,edge_in.origin);
    % write the name of the end node
    t_file=writefieldstring(t_file,EndNodeTxt,edge_in.end);
else
    error('tenfile - Invalid file structure');
end
