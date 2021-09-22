function [coplanar_sets,num_sets,tc_file]=readcoplanarsets(tc_file)
% reads the constraints associated to a set of coplanar nodes
% this function reads the constraints associated to a set of nodes that
% must be contained into a plane, which consist of:
%   * the vector normal to the plane
%   * the distance from the origin of coordinates
% 
% [coplanar_sets,num_sets,tc_file]=readcoplanarsets(tc_file) returns a 
% modified version of the tenconst object passed as argument after reading 
% the information from the file, as well as the number of coplanar node
% sets (num_sets) and the constraint information of each set (coplanar_sets)
%
% coplanar_sets is a vector of structures with the necessary constarint 
% information with a length equal to num_sets. The tenconst file object 
% must be initialized before calling this function.
%
% See also constfile,tenconst,readfieldstring,readfieldint

if isa(tc_file,'constfile')
    %file tag txt
    NumSetsTxt='Num. Coplanar Sets:';
    NumCopNodesTxt='Num. Coplanar Nodes:';
    CopNodesTxt='Coplanar Nodes:';
    NxTxt='nx:';
    NyTxt='ny:';
    NzTxt='nz:';
    DistTxt='dist:';        
    try
        % read the number of coplanar sets
        [num_sets,tc_file]=readfieldint(tc_file,NumSetsTxt);
        if num_sets>0
            % read the information for each set
            for i=1:1:numsets
                % read the set name
                [coplanar_sets(i).name,tc_file]=readline(tc_file);
                % read the number of nodes in the set
                [coplanar_sets(i).num_nodes,tc_file]=readfieldint(tc_file,NumCopNodesTxt);
                % read the names of the nodes in the set
                [nodes,tc_file]=readfieldstring(tc_file,CopNodesTxt);
                for j=1:1:coplanar_sets(i).num_nodes
                    [coplanar_sets(i).nodes(j).name,nodes]=strtok(nodes,',');
                end
                % read the constraitn for the x coordinate of the normal vector
                [string,tc_file]=readfieldstring(tc_file,NxTxt);
                if strcmpn(string,'fixed',size('fixed',2))
                    value=str2num(string(size('fixed,',2)+1:size(string,2)));
                    coplanar_sets.normal(1)=tenvar('fixed',[coplanar_sets(i).name,'_nx'],value);                
                else
                    if strcmpn(string,'parameter',size('parameter',2))
                        coplanar_sets.normal(1)=tenvar('parameter',[coplanar_sets(i).name,'_nx']);                                    
                    else
                        if  strcmpn(string,'passive',size('passive',2))
                            coplanar_sets.normal(1)=tenvar('passive',[coplanar_sets(i).name,'_nx']);
                        else
                            error('constfile - Invalid plane variable type');
                        end
                    end
                end
                % read the constraitn for the y coordinate of the normal vector            
                [string,tc_file]=readfieldstring(tc_file,NyTxt);
                if strcmpn(string,'fixed',size('fixed',2))
                    value=str2num(string(size('fixed,',2)+1:size(string,2)));
                    coplanar_sets.normal(1)=tenvar('fixed',[coplanar_sets(i).name,'_nx'],value);                
                else
                    if strcmpn(string,'parameter',size('parameter',2))
                        coplanar_sets.normal(2)=tenvar('parameter',[coplanar_sets(i).name,'_nx']);                                    
                    else
                        if  strcmpn(string,'passive',size('passive',2))
                            coplanar_sets.normal(3)=tenvar('passive',[coplanar_sets(i).name,'_nx']);
                        else
                            error('constfile - Invalid plane variable type');
                        end
                    end
                end
                % read the constraitn for the z coordinate of the normal vector            
                [string,tc_file]=readfieldstring(tc_file,NzTxt);
                if strcmpn(string,'fixed',size('fixed',2))
                    value=str2num(string(size('fixed,',2)+1:size(string,2)));
                    coplanar_sets.normal(3)=tenvar('fixed',[coplanar_sets(i).name,'_nz'],value);                
                else
                    if strcmpn(string,'parameter',size('parameter',2))
                        coplanar_sets.normal(3)=tenvar('parameter',[coplanar_sets(i).name,'_nz']);                                    
                    else
                        if  strcmpn(string,'passive',size('passive',2))
                            coplanar_sets.normal(3)=tenvar('passive',[coplanar_sets(i).name,'_nz']);
                        else
                            error('constfile - Invalid plane variable type');
                        end
                    end
                end
                % read the constraints for the distance from origin
                [string,tc_file]=readfieldstring(tc_file,DistTxt);
                if strcmpn(string,'fixed',size('fixed',2))
                    value=str2num(string(size('fixed,',2)+1:size(string,2)));
                    coplanar_sets.dist=tenvar('fixed',[coplanar_sets(i).name,'_dist'],value);                
                else
                    if strcmpn(string,'parameter',size('parameter',2))
                        coplanar_sets.dist=tenvar('parameter',[coplanar_sets(i).name,'_dist']);                                    
                    else
                        if  strcmpn(string,'passive',size('passive',2))
                            coplanar_sets.dist=tenvar('passive',[coplanar_sets(i).name,'_dist']);
                        else
                            error('constfile - Invalid plane variable type');
                        end
                    end
                end
            end
        else
            coplanar_sets.num_nodes=0;
            coplanar_sets.name=[];
            coplanar_sets.nodes=[];
            coplanar_sets.normal=[tenvar(),tenvar(),tenvar()];
            coplanar_sets.dist=tenvar();
        end
    catch
        rethrow(lasterror);
    end
else
    error('constfile - Invalid constraint file strcuture');
end