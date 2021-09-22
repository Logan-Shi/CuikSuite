function [sym_const,tc_file]=readsymmetryconstraints(tc_file)
if isa(tc_file,'constfile')
    sym_const.num_sets=0;
    sym_const.sets.num_edges=0;
    sym_const.sets.edges.name=[];
    try
        [num,tc_file]=readfieldint(tc_file,'Num. Sym. Sets:');
        sym_const.num_sets=num;
        for i=1:1:num
            [sym_edges,tc_file]=readfieldstring(tc_file,'Set:');
            [num_edges,sym_edges]=strtok(sym_edges,',');
            sym_const.sets(i).num_edges=str2num(num_edges);
            for j=1:1:sym_const.sets(i).num_edges-1
                [edge_name,sym_edges]=strtok(sym_edges(2:size(sym_edges,2)),',');
                sym_const.sets(i).edges(j).name=edge_name;
            end
            sym_const.sets(i).edges(j+1).name=sym_edges(2:size(sym_edges,2));
        end
    catch
        rethrow(lasterror);
    end
else
    error('constfile - Invalid constraint file structure');
end