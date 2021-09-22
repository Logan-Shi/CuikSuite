function tc_file=writecoplanarsets(tc_file,coplanar_sets,num_sets)
% writes the constraints associated to a set of coplanar nodes
% this function writes the constraints associated to a set of nodes that
% must be containde into a plane, which consist of:
%   * the vector normal to the plane
%   * the distance from the origin of coordinates
% 
% tc_file=writecoplanarsets(tc_file,coplanar_sets,num_sets) returns a 
% modified version of the tenconst object passed as argument after writing 
% the information into the file.
%
% coplanar_sets must be a vector of structures with the necessary
% constarint information with a length equal to num_sets. The tenconst file
% object must be initialized before calling this function.
%
% See also constfile,tenconst,writefieldstring,writefieldint

if isa(tc_file,'constfile')
    % file tag text
    NumSetsTxt='Num. Coplanar Sets:';
    NumCopNodesTxt='Num. Coplanar Nodes:';
    CopNodesTxt='Coplanar Nodes:';
    NxTxt='nx:';
    NyTxt='ny:';
    NzTxt='nz:';
    DistTxt='dist:';        
    try
        % write the number of node coplanar sets
        tc_file=writefieldint(tc_file,NumSetsTxt,num_sets);
        % write the information of each set
        for i=1:1:num_sets
            % write the name of the set
            tc_file=writefieldstring(tc_file,'',coplanar_sets(i).name);
            % write the number of nodes in the set
            tc_file=writefieldint(tc_file,NumCopNodesTxt,coplanar_sets(i).num_nodes);
            nodes='';
            for j=1:1:coplanar_sets(i).num_nodes
                nodes=[nodes,coplanar_sets(i).nodes(j).name];
                if j<coplanar_sets(i).num_nodes
                    nodes=[nodes,','];
                end
            end
            % write the names of the nodes in the set
            tc_file=writefieldstring(tc_file,CopNodesTxt,nodes);
            % write the information of the normal vector
            string=coplanar_sets(i).normal(1).type;
            if strncmp(string,'fixed',size('fixed',2))
                string=[string,',',num2str(coplanar_sets(i).normal(1).value)];
            end
            tc_file=writefieldstring(tc_file,NxTxt,string);
            string=coplanar_sets(i).normal(2).type;
            if strncmp(string,'fixed',size('fixed',2))
                string=[string,',',num2str(coplanar_sets(i).normal(2).value)];
            end
            tc_file=writefieldstring(tc_file,NyTxt,string);
            string=coplanar_sets(i).normal(3).type;
            if strncmp(string,'fixed',size('fixed',2))
                string=[string,',',num2str(coplanar_sets(i).normal(3).value)];
            end
            tc_file=writefieldstring(tc_file,NzTxt,string);
            % write the information of the distance from the origin
            string=coplanar_sets(i).dist.type;
            if strncmp(string,'fixed',size('fixed',2))
                string=[string,',',num2str(coplanar_sets(i).dist.value)];
            end
            tc_file=writefieldstring(tc_file,DistTxt,string);
        end
    catch
        rethrow(lasterror);
    end
else
    error('constfile - Invalid constraint file strcuture');
end