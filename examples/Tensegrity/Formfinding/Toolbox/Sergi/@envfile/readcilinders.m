function [cilinders,num,ef]=readcilinders(ef)

if isa(ef,'envfile')
    % file tag txt
    NumCilindersTxt='Num. Cilinders:';
    RTxt='R:';
    LTxt='L:';
    PxTxt='Px:';
    PyTxt='Py:';
    PzTxt='Pz:';    
    UxTxt='Ux:';
    UyTxt='Uy:';
    UzTxt='Uz:';
    try
        [num,ef]=readfieldint(ef,NumCilindersTxt);
        if num>0
            for i=1:1:num
                [cilinders(i).name,ef]=readline(ef);
                [radius,ef]=readfieldstring(ef,RTxt);
                if strncmp(radius,'fixed',size('fixed',2))
                    value=str2num(radius(size('fixed',2)+1,size(radius,2)));
                    cilinders(i).radius=tenvar('fixed',['R_',cilinders(i).name],value);
                else
                    cilinders(i).radius=tenvar('parameter',['R_',cilinders(i).name]);
                end
                [length,ef]=readfieldstring(ef,LTxt);
                if strncmp(length,'fixed',size('fixed',2))
                    value=str2num(length(size('fixed',2)+1,size(length,2)));
                    cilinders(i).length=tenvar('fixed',['L_',cilinders(i).name],value);
                else
                    cilinders(i).length=tenvar('parameter',['L_',cilinders(i).name]);
                end
                cilinders(i).origin=[tenvar(),tenvar(),tenvar()];
                [origin,ef]=readfieldstring(ef,PxTxt);
                if strncmp(origin,'fixed',size('fixed',2))
                    value=str2num(origin(size('fixed',2)+1,size(origin,2)));
                    cilinders(i).origin(1)=tenvar('fixed',['Px_',cilinders(i).name],value);
                else
                    cilinders(i).origin(1)=tenvar('parameter',['Px_',cilinders(i).name]);
                end
                [origin,ef]=readfieldstring(ef,PyTxt);
                if strncmp(origin,'fixed',size('fixed',2))
                    value=str2num(origin(size('fixed',2)+1,size(origin,2)));
                    cilinders(i).origin(2)=tenvar('fixed',['Py_',cilinders(i).name],value);
                else
                    cilinders(i).origin(2)=tenvar('parameter',['Py_',cilinders(i).name]);
                end
                [origin,ef]=readfieldstring(ef,PzTxt);
                if strncmp(origin,'fixed',size('fixed',2))
                    value=str2num(origin(size('fixed',2)+1,size(origin,2)));
                    cilinders(i).origin(3)=tenvar('fixed',['Pz_',cilinders(i).name],value);
                else
                    cilinders(i).origin(3)=tenvar('parameter',['Pz_',cilinders(i).name]);
                end
                cilinders(i).orientation=[tenvar(),tenvar(),tenvar()];
                [orientation,ef]=readfieldstring(ef,UxTxt);
                if strncmp(orientation,'fixed',size('fixed',2))
                    value=str2num(orientation(size('fixed',2)+1,size(orientation,2)));
                    cilinders(i).orientation(1)=tenvar('fixed',['Ux_',cilinders(i).name],value);
                else
                    cilinders(i).orientation(1)=tenvar('parameter',['Ux_',cilinders(i).name]);
                end
                [orientation,ef]=readfieldstring(ef,UyTxt);
                if strncmp(orientation,'fixed',size('fixed',2))
                    value=str2num(orientation(size('fixed',2)+1,size(orientation,2)));
                    cilinders(i).orientation(2)=tenvar('fixed',['Uy_',cilinders(i).name],value);
                else
                    cilinders(i).orientation(2)=tenvar('parameter',['Uy_',cilinders(i).name]);
                end
                [orientation,ef]=readfieldstring(ef,UzTxt);
                if strncmp(orientation,'fixed',size('fixed',2))
                    value=str2num(orientation(size('fixed',2)+1,size(orientation,2)));
                    cilinders(i).orientation(3)=tenvar('fixed',['Uz_',cilinders(i).name],value);
                else
                    cilinders(i).orientation(3)=tenvar('parameter',['Uz_',cilinders(i).name]);
                end
            end
        else
            cilinders=[];
        end
    catch
        rethrow(lasterror);
    end
else
    error('envfile - Invalid environment file object');
end