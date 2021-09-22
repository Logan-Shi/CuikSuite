function [planes,num,ef]=readplanes(ef)

if isa(ef,'envfile')
    % file tag txt
    NumPlanesTxt='Num. Planes:';
    NxTxt='Nx:';
    NyTxt='Ny:';
    NzTxt='Nz:';
    OffxTxt='Offx:';
    OffyTxt='Offy:';
    OffzTxt='Offz:';    
    try
        [num,ef]=readfieldint(ef,NumPlanesTxt);
        if num>0
            for i=1:1:num
                [planes(i).name,ef]=readline(ef);
                planes(i).normal=[tenvar(),tenvar(),tenvar()];
                [normal,ef]=readfieldstring(ef,NxTxt);
                if strncmp(normal,'fixed',size('fixed',2))
                    value=str2num(normal(size('fixed',2)+1,size(normal,2)));
                    planes(i).normal(1)=tenvar('fixed',['Nx_',planes(i).name],value);
                else
                    planes(i).normal(1)=tenvar('parameter',['Nx_',planes(i).name]);
                end
                [normal,ef]=readfieldstring(ef,NyTxt);
                if strncmp(normal,'fixed',size('fixed',2))
                    value=str2num(normal(size('fixed',2)+1,size(normal,2)));
                    planes(i).normal(2)=tenvar('fixed',['Ny_',planes(i).name],value);
                else
                    planes.normal(2)=tenvar('parameter',['Ny_',planes(i).name]);
                end
                [normal,ef]=readfieldstring(ef,NzTxt);
                if strncmp(normal,'fixed',size('fixed',2))
                    value=str2num(normal(size('fixed',2)+1,size(normal,2)));
                    planes(i).normal(3)=tenvar('fixed',['Nz_',planes(i).name],value);
                else
                    planes(i).normal(3)=tenvar('parameter',['Nz_',planes(i).name]);
                end
                planes(i).offset=[tenvar(),tenvar(),tenvar()];
                [offset,ef]=readfieldstring(ef,OffxTxt);
                if strncmp(offset,'fixed',size('fixed',2))
                    value=str2num(offset(size('fixed',2)+1,size(offset,2)));
                    planes(i).offset(1)=tenvar('fixed',['Offx_',planes(i).name],value);
                else
                    planes(i).offset(1)=tenvar('parameter',['Offx_',planes(i).name]);
                end
                [offset,ef]=readfieldstring(ef,OffyTxt);
                if strncmp(offset,'fixed',size('fixed',2))
                    value=str2num(offset(size('fixed',2)+1,size(offset,2)));
                    planes(i).offset(2)=tenvar('fixed',['Offy_',planes(i).name],value);
                else
                    planes(i).offset(2)=tenvar('parameter',['Offy_',planes(i).name]);
                end
                [offset,ef]=readfieldstring(ef,OffzTxt);
                if strncmp(offset,'fixed',size('fixed',2))
                    value=str2num(offset(size('fixed',2)+1,size(offset,2)));
                    planes(i).offset(3)=tenvar('fixed',['Offz_',planes(i).name],value);
                else
                    planes(i).offset(3)=tenvar('parameter',['Offz_',planes(i).name]);
                end
            end
        else
            planes=[];
        end
    catch
        rethrow(lasterror);
    end
else
    error('envfile - Invalid environment file object');
end