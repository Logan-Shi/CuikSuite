function t_file=writenodeinfo(t_file,node_in)
% writes the topological information of a node into a file
% this funciton write to the associated file the topological information of
% a node  which consist of:
%   * the name of the node
%   * the number of incident edges
%   * the list of incident edges
%
% t_file=writenodeinfo(t_file,node_in) return a modified version of the
% file object passed as argument after writing the topological information
% of the node into the file.
%
% node_in must be an initialized node object and the file object must be
% initialized before calling this function.
% 
% See also tenfile,file,node,writefieldstring,writefieldint

%file tag txt
NumEdgesTxt='Num. Edges:';
EdgesTxt='Edges:';

if isa(t_file,'tenfile')
    if ~isa(node_in,'node')
        error('tenfile - Invalid node structure');
    end
    try
        % write the node name
        t_file=writefieldstring(t_file,'',node_in.name);
        % write the number of incident edges
        t_file=writefieldint(t_file,NumEdgesTxt,node_in.num_edges);
        % write the name of the incident edges
        edge_list='';
        inc_edges=node_in.inc_edges;    
        for i=1:1:node_in.num_edges
            edge_list=[edge_list,inc_edges(i).name];
            if i<node_in.num_edges
                edge_list=[edge_list,','];
            end
        end
        t_file=writefieldstring(t_file,EdgesTxt,edge_list);
    catch
        rethrow(lasterror);
    end
else
    error('tenfile - Invalid file structure');
end

