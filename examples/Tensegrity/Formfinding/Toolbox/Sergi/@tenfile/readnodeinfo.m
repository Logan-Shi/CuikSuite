function [node,t_file]=readnodeinfo(t_file,node)
% reads the topological information of a node from a file
% this funciton reads from the associated file the topological information of
% a node which consist of
%   * the name of the node
%   * the number of incident edges
%   * the list of incident edges
%
% [node,t_file]=readnodeinfo(t_file,node) return a modified version of the
% file object passed as argument after reading the topological information
% of the node from the file, as well as the modified version of a node
% object updated with the information read from the file.
%
% Both the node object and the file object must be initialized before 
% calling this function.
% 
% See also tenfile,file,node,readfieldstring,readfieldint

% file tag txt
NumEdgesTxt='Num. Edges:';
EdgesTxt='Edges:';

if isa(t_file,'tenfile')
    try
        % red the node name
        [node.name,t_file]=readline(t_file);
        % read the number of incident edges
        [num_edges,t_file]=readfieldint(t_file,NumEdgesTxt);
        % read the names of the incident edges
        [tmp_string,t_file]=readfieldstring(t_file,EdgesTxt);
        inc_edges.name=[];
        for i=1:1:num_edges
            [edge_name,tmp_string]=strtok(tmp_string,',');
            node=addincidentedge(node,edge_name);
        end
    catch
        rethrow(lasterror);
    end
else
    error('tenfile - Invalid file structure');
    return;
end

