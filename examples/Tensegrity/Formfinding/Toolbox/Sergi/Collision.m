function varargout = Collision(varargin)
% COLLISION M-file for Collision.fig
%      COLLISION, by itself, creates a new COLLISION or raises the existing
%      singleton*.
%
%      H = COLLISION returns the handle to a new COLLISION or the handle to
%      the existing singleton*.
%
%      COLLISION('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in COLLISION.M with the given input arguments.
%
%      COLLISION('Property','Value',...) creates a new COLLISION or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Collision_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Collision_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Collision

% Last Modified by GUIDE v2.5 17-Feb-2008 22:01:07

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Collision_OpeningFcn, ...
                   'gui_OutputFcn',  @Collision_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before Collision is made visible.
function Collision_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Collision (see VARARGIN)

% Choose default command line output for Collision
handles.output = hObject;
handles.ten_col=tencol();

% Update handles structure
try
    UpdateInfo(hObject, handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% UIWAIT makes Collision wait for user response (see UIRESUME)
uiwait(handles.Collision);

% --- Outputs from this function are returned to the command line.
function varargout = Collision_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
if ~isempty(handles)
    varargout{1} = handles.ten_col;
end

close

function ConstraintsFile_Callback(hObject, eventdata, handles)
% hObject    handle to ConstraintsFile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ConstraintsFile as text
%        str2double(get(hObject,'String')) returns contents of ConstraintsFile as a double
try
    handles.ten_col.const_file=get(handles.ConstraintsFile,'String');
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function ConstraintsFile_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ConstraintsFile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function GradientFile_Callback(hObject, eventdata, handles)
% hObject    handle to GradientFile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of GradientFile as text
%        str2double(get(hObject,'String')) returns contents of GradientFile as a double
handles.ten_col.grad_file=get(handles.GradientFile,'String');
UpdateInfo(hObject,handles);


% --- Executes during object creation, after setting all properties.
function GradientFile_CreateFcn(hObject, eventdata, handles)
% hObject    handle to GradientFile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function OptFuncFile_Callback(hObject, eventdata, handles)
% hObject    handle to OptFuncFile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of OptFuncFile as text
%        str2double(get(hObject,'String')) returns contents of OptFuncFile as a double
try
    handles.ten_col.func_file=get(handles.OptFuncFile,'String');
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function OptFuncFile_CreateFcn(hObject, eventdata, handles)
% hObject    handle to OptFuncFile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in GenFiles.
function GenFiles_Callback(hObject, eventdata, handles)
% hObject    handle to GenFiles (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    const_file=get(handles.ConstraintsFile,'String');
    if isempty(const_file)
        errordlg('No name for the constraint file has been specified');
        return;
    else
        if isempty(strfind(const_file,'.c'))
            const_file=[const_file,'.c'];
        end
    end
    grad_file=get(handles.GradientFile,'String');
    if isempty(grad_file)
        errordlg('No name for the gradient file has been specified');
        return;
    else
        if isempty(strfind(grad_file,'.c'))
            grad_file=[grad_file,'.c'];
        end
    end
    func_file=get(handles.OptFuncFile,'String');
    if isempty(func_file)
        errordlg('No name for the collision function file has been specified');
        return;
    else
        if isempty(strfind(func_file,'.c'))
            func_file=[func_file,'.c'];
        end
    end
    handles.ten_col=generateconstraints(handles.ten_col);
    handles.ten_col=generateconstfile(handles.ten_col,const_file);
    % generar la funció a optimitzar
    handles.ten_col=generatefunction(handles.ten_col);
    handles.ten_col=generatefuncfile(handles.ten_col,func_file);
    % generar el gradient
    handles.ten_col=generategradient(handles.ten_col);
    handles.ten_col=generategradfile(handles.ten_col,grad_file);

    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

function NumEq_Callback(hObject, eventdata, handles)
% hObject    handle to NumEq (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of NumEq as text
%        str2double(get(hObject,'String')) returns contents of NumEq as a double

% --- Executes during object creation, after setting all properties.
function NumEq_CreateFcn(hObject, eventdata, handles)
% hObject    handle to NumEq (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function NumIneq_Callback(hObject, eventdata, handles)
% hObject    handle to NumIneq (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of NumIneq as text
%        str2double(get(hObject,'String')) returns contents of NumIneq as a double

% --- Executes during object creation, after setting all properties.
function NumIneq_CreateFcn(hObject, eventdata, handles)
% hObject    handle to NumIneq (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function MinPenalty_Callback(hObject, eventdata, handles)
% hObject    handle to MinPenalty (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of MinPenalty as text
%        str2double(get(hObject,'String')) returns contents of MinPenalty as a double
try
    handles.ten_col.penalty(1)=str2num(get(handles.MinPenalty,'String'));
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function MinPenalty_CreateFcn(hObject, eventdata, handles)
% hObject    handle to MinPenalty (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function MaxPenalty_Callback(hObject, eventdata, handles)
% hObject    handle to MaxPenalty (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of MaxPenalty as text
%        str2double(get(hObject,'String')) returns contents of MaxPenalty as a double
try
    handles.ten_col.penalty(2)=str2num(get(handles.MaxPenalty,'String'));
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function MaxPenalty_CreateFcn(hObject, eventdata, handles)
% hObject    handle to MaxPenalty (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function BetaParam_Callback(hObject, eventdata, handles)
% hObject    handle to BetaParam (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of BetaParam as text
%        str2double(get(hObject,'String')) returns contents of BetaParam as a double
try
    handles.ten_col.beta=str2num(get(handles.BetaParam,'String'));
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function BetaParam_CreateFcn(hObject, eventdata, handles)
% hObject    handle to BetaParam (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function SParam_Callback(hObject, eventdata, handles)
% hObject    handle to SParam (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of SParam as text
%        str2double(get(hObject,'String')) returns contents of SParam as a double
try
    handles.ten_col.s=str2num(get(handles.SParam,'String'));
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function SParam_CreateFcn(hObject, eventdata, handles)
% hObject    handle to SParam (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function SigmaParam_Callback(hObject, eventdata, handles)
% hObject    handle to SigmaParam (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of SigmaParam as text
%        str2double(get(hObject,'String')) returns contents of SigmaParam as a double
try
    handles.ten_col.sigma=str2num(get(handles.SigmaParam,'String'));
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function SigmaParam_CreateFcn(hObject, eventdata, handles)
% hObject    handle to SigmaParam (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function PenaltyUpdate_Callback(hObject, eventdata, handles)
% hObject    handle to PenaltyUpdate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of PenaltyUpdate as text
%        str2double(get(hObject,'String')) returns contents of PenaltyUpdate as a double

% --- Executes during object creation, after setting all properties.
function PenaltyUpdate_CreateFcn(hObject, eventdata, handles)
% hObject    handle to PenaltyUpdate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in Browse.
function Browse_Callback(hObject, eventdata, handles)
% hObject    handle to Browse (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    [filename,pathname]=uigetfile({'*.m','Penalty update function (*.m)'},'Penalty update');
    if filename~=0 
        handles.ten_col.penalty_update=str2func(filename);
        set(handles.PenaltyUpdate,'String',filename);    
    end

    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

function Tolerance_Callback(hObject, eventdata, handles)
% hObject    handle to Tolerance (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Tolerance as text
%        str2double(get(hObject,'String')) returns contents of Tolerance as a double
try
    handles.ten_col.tolerance=str2num(get(handles.Tolerance,'String'));
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function Tolerance_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Tolerance (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function ParamFile_Callback(hObject, eventdata, handles)
% hObject    handle to ParamFile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ParamFile as text
%        str2double(get(hObject,'String')) returns contents of ParamFile as a double

% --- Executes during object creation, after setting all properties.
function ParamFile_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ParamFile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in ParamBrowse.
function ParamBrowse_Callback(hObject, eventdata, handles)
% hObject    handle to ParamBrowse (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    [filename,pathname]=uigetfile({'*.col','Collision parameters file (*.col)'},'Collision parameters');
    if filename~=0 
        handles.ParamFilename=[pathname,filename];
        set(handles.ParamFile,'String',filename);    
    end
    guidata(hObject, handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes on button press in Import.
function Import_Callback(hObject, eventdata, handles)
% hObject    handle to Import (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    handles.ten_col=tencol();
    handles.ten_col=loadoptparams(handles.ten_col,handles.ParamFilename);
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes on button press in Export.
function Export_Callback(hObject, eventdata, handles)
% hObject    handle to Export (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    filename=get(handles.ParamFile,'String');
    if ~isempty(filename)
        if isempty(strfind(filename,'.opt'))
            filename=[filename,'.opt'];
        end
        saveoptparams(handles.ten_col,filename);
    else
        errordlg('No file name specified');
        return;
    end
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

function ConstFilename_Callback(hObject, eventdata, handles)
% hObject    handle to ConstFilename (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ConstFilename as text
%        str2double(get(hObject,'String')) returns contents of ConstFilename as a double


% --- Executes during object creation, after setting all properties.
function ConstFilename_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ConstFilename (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in ConstBrowse.
function ConstBrowse_Callback(hObject, eventdata, handles)
% hObject    handle to ConstBrowse (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    [filename,pathname]=uigetfile({'*.cst','Tensegrity constraint file (*.cst)'},'Tensegrity constraint file');
    if filename~=0 
        ten_const=tenconst();
        ten_const=loadconstraints(ten_const,filename);
        handles.ten_col.const=ten_const;
    end
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% funcions pròpies
function UpdateInfo(hObject,handles)

% paràmetres d'optimització
set(handles.MinPenalty,'String',num2str(handles.ten_col.penalty(1)));
set(handles.MaxPenalty,'String',num2str(handles.ten_col.penalty(2)));
set(handles.PenaltyUpdate,'String',handles.ten_col.penalty_update);
set(handles.BetaParam,'String',handles.ten_col.beta);
set(handles.SParam,'String',handles.ten_col.s);
set(handles.SigmaParam,'String',handles.ten_col.sigma);
set(handles.Tolerance,'String',handles.ten_col.tolerance);
% informació de les restriccions
if ~isempty(handles.ten_col.const)
    set(handles.ConstraintsFile,'Enable','on');
    set(handles.GradientFile,'Enable','on');
    set(handles.OptFuncFile,'Enable','on');
    set(handles.GenFiles,'Enable','on');
    ten_const=handles.ten_col.const;    
    set(handles.NumEq,'String',num2str(handles.ten_col.num_eq+handles.ten_col.num_env_eq));
    set(handles.NumIneq,'String',num2str(handles.ten_col.num_ineq+handles.ten_col.num_env_ineq));
    set(handles.ConstFilename,'String',ten_const.const_filename);    
else
    set(handles.ConstraintsFile,'Enable','off');
    set(handles.GradientFile,'Enable','off');
    set(handles.OptFuncFile,'Enable','off');
    set(handles.GenFiles,'Enable','off');
end
if isempty(handles.ten_col.const_file)
    set(handles.ConstraintsFile,'String','none');
else
    set(handles.ConstraintsFile,'String',handles.ten_col.const_file);
end
if isempty(handles.ten_col.grad_file)
    set(handles.GradientFile,'String','none');
else
    set(handles.GradientFile,'String',handles.ten_col.grad_file);
end
if isempty(handles.ten_col.func_file)
    set(handles.OptFuncFile,'String','none');
else
    set(handles.OptFuncFile,'String',handles.ten_col.func_file);
end

guidata(hObject, handles);


% --- Executes on button press in Done.
function Done_Callback(hObject, eventdata, handles)
% hObject    handle to Done (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
uiresume(handles.Collision);

