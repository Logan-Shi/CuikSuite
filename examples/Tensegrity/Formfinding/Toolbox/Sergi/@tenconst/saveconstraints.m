function saveconstraints(tc,filename)
% saves the constraints associated to a tensegrity structure
% this function save into a file the constraints associated to a tensegrity
% structure. See the documentation for constfile for information about the
% file format.
%
% saveconstraints(tc,filename) opens the desired filename or creates it if
% it does not exist and save all the constraints for the tensegrity
% structure.
%
% The tensegrtiy constriaint object must be initialized before calling this
% function, and filename must be a string terminated by *.cst.
%
% See also tenconst,constfile

if isa(tc,'tenconst')
    if ischar(filename)
        try
            tc_file=constfile(filename,'w');
            tc_file=writefieldstring(tc_file,'Topology File: ',tc.tensegrity.filename);
            tc_file=writecmconstraints(tc_file,tc.cm);
            tc_file=writecoplanarsets(tc_file,tc.cop_sets,tc.num_cop_sets);
            for i=1:1:tc.tensegrity.num_nodes
                tc_file=writenodeconst(tc_file,tc.tensegrity.nodes(i));
            end
            for i=1:1:tc.tensegrity.num_edges
                tc_file=writeedgeconst(tc_file,tc.tensegrity.edges(i));
            end
            tc_file=writecostfunc(tc_file,func2str(tc.cost_func_h));
        catch
            rethrow(lasterror);
        end
    else
        error('tenconst - Invalid filename');
    end
else
    error('tenconst - Invalid tensegrity constraints file');
end