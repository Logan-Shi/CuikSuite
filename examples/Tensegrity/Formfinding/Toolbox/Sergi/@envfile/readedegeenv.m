function [eenv,ef]=readedegeenv(ef,eenv)

if isa(ef,'envfile')
    RadiusTxt='Radius:';
    try
        [eenv.radius,ef]=readfieldreal(ef,RadiusTxt);
    catch
        rethrow(lasterror);
    end
else
    error('tenenv - Invalid tensegrity environment file');
end
