function varargout = Constraints(varargin)
% CONSTRAINTS M-file for Constraints.fig
%      CONSTRAINTS, by itself, creates a new CONSTRAINTS or raises the existing
%      singleton*.
%
%      H = CONSTRAINTS returns the handle to a new CONSTRAINTS or the handle to
%      the existing singleton*.
%
%      CONSTRAINTS('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in CONSTRAINTS.M with the given input arguments.
%
%      CONSTRAINTS('Property','Value',...) creates a new CONSTRAINTS or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Constraints_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Constraints_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Constraints

% Last Modified by GUIDE v2.5 21-Jan-2008 13:50:18

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Constraints_OpeningFcn, ...
                   'gui_OutputFcn',  @Constraints_OutputFcn, ...
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

% --- Executes just before Constraints is made visible.
function Constraints_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Constraints (see VARARGIN)

% Choose default command line output for Constraints
global error;
handles.output = hObject;

handles.sel_var=1;
handles.sel_node=1;
handles.sel_edge=1;
handles.sel_force=1;
handles.sel_cp_set=1;
handles.ConstraintFile=[];
if nargin>3
    try
        handles.ten_const=tenconst();
        handles.ten_const=loadconstraints(handles.ten_const,varargin{1});
        set(handles.ConstFilename,'String',varargin{1});
        set(handles.TopologyFilename,'String',handles.ten_const.filename);
        set(handles.VarName,'Enable','on');
        set(handles.FixedButton,'Enable','on');
        set(handles.PassiveButton,'Enable','on');
        set(handles.ParameterButton,'Enable','on');
        set(handles.ActuatedButton,'Enable','on');
        set(handles.VarName,'Enable','on');
        set(handles.EdgeName,'Enable','on');
        set(handles.NodeName,'Enable','on');
        set(handles.CreateSet,'Enable','on');
        set(handles.DeleteSet,'Enable','on');
        set(handles.Coplanar_AddNode,'Enable','on');
        set(handles.Coplanar_RemoveNode,'Enable','on');
        set(handles.CM_AddNode,'Enable','on');
        set(handles.CM_RemoveNode,'Enable','on');
        set(handles.MinEnergy,'Enable','on');
        set(handles.Cables,'Enable','on');
        set(handles.Struts,'Enable','on');
        set(handles.FromFileButton,'Enable','on');
        set(handles.CostFuncFile,'Enable','on');
        set(handles.CostFuncBrowse,'Enable','on');
        set(handles.AddForce,'Enable','on');
        set(handles.RemoveForce,'Enable','on');    
        set(handles.MinEnergy,'Enable','on');
        set(handles.FromFileButton,'Enable','on');
    catch
        error=lasterror;
        errordlg(error.message);
        return;
    end
else
    set(handles.VarName,'Enable','off');
    set(handles.FixedButton,'Enable','off');
    set(handles.PassiveButton,'Enable','off');
    set(handles.ParameterButton,'Enable','off');
    set(handles.ActuatedButton,'Enable','off');
    set(handles.TopologyFilename,'Enable','off');
    set(handles.TotalNumVar,'Enable','off');
    set(handles.VarName,'Enable','off');
    set(handles.EdgeName,'Enable','off');
    set(handles.Stiffness,'Enable','off');
    set(handles.RL_Min,'Enable','off');
    set(handles.RL_Default,'Enable','off');
    set(handles.RL_Max,'Enable','off');
    set(handles.NodeName,'Enable','off');
    set(handles.Pos_X,'Enable','off');
    set(handles.Pos_Y,'Enable','off');
    set(handles.Pos_Z,'Enable','off');
    set(handles.NumForces,'Enable','off');
    set(handles.ExternalForces,'Enable','off');
    set(handles.Force_X,'Enable','off');
    set(handles.Force_Y,'Enable','off');
    set(handles.Force_Z,'Enable','off');
    set(handles.CoplanarSet,'Enable','off');
    set(handles.CreateSet,'Enable','off');
    set(handles.DeleteSet,'Enable','off');
    set(handles.Coplanar_AddNode,'Enable','off');
    set(handles.Coplanar_RemoveNode,'Enable','off');
    set(handles.Normal_X,'Enable','off');
    set(handles.Normal_Y,'Enable','off');
    set(handles.Normal_Z,'Enable','off');
    set(handles.OriginDist,'Enable','off');
    set(handles.CM_AddNode,'Enable','off');
    set(handles.CM_RemoveNode,'Enable','off');
    set(handles.CM_Pos_X,'Enable','off');
    set(handles.CM_Pos_Y,'Enable','off');
    set(handles.CM_Pos_Z,'Enable','off');
    set(handles.CM_Rot_X,'Enable','off');
    set(handles.CM_Rot_Y,'Enable','off');
    set(handles.CM_Rot_Z,'Enable','off');
    set(handles.MinEnergy,'Enable','off');
    set(handles.Cables,'Enable','off');
    set(handles.Struts,'Enable','off');
    set(handles.FromFileButton,'Enable','off');
    set(handles.CostFuncFile,'Enable','off');
    set(handles.CostFuncBrowse,'Enable','off');
    set(handles.AddForce,'Enable','off');
    set(handles.RemoveForce,'Enable','off');    
    set(handles.MinEnergy,'Value',1);
    set(handles.FromFileButton,'Value',0);    
    handles.ten_const=[];
end

% Update handles structure
guidata(hObject,handles);

% UIWAIT makes Constraints wait for user response (see UIRESUME)
uiwait(handles.Constraints);

% --- Outputs from this function are returned to the command line.
function varargout = Constraints_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if ~isempty(handles)
    mOutputArgs{1} = handles.ten_const;
else
    mOutputArgs{1}=[];
end
if nargout>0
    [varargout{1:nargout}] = mOutputArgs{:};
end

close

% Get default command line output from handles structure
%varargout{1} = handles.output;

% --- Executes on selection change in VarName.
function VarName_Callback(hObject, eventdata, handles)
% hObject    handle to VarName (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns VarName contents as cell array
%        contents{get(hObject,'Value')} returns selected item from VarName
try
    handles.sel_var=get(handles.VarName,'Value');
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function VarName_CreateFcn(hObject, eventdata, handles)
% hObject    handle to VarName (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on selection change in ConstantsList.
function ConstantsList_Callback(hObject, eventdata, handles)
% hObject    handle to ConstantsList (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns ConstantsList contents as cell array
%        contents{get(hObject,'Value')} returns selected item from ConstantsList

% --- Executes during object creation, after setting all properties.
function ConstantsList_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ConstantsList (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on selection change in OptimizationList.
function OptimizationList_Callback(hObject, eventdata, handles)
% hObject    handle to OptimizationList (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns OptimizationList contents as cell array
%        contents{get(hObject,'Value')} returns selected item from OptimizationList

% --- Executes during object creation, after setting all properties.
function OptimizationList_CreateFcn(hObject, eventdata, handles)
% hObject    handle to OptimizationList (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on selection change in ParameterList.
function ParameterList_Callback(hObject, eventdata, handles)
% hObject    handle to ParameterList (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns ParameterList contents as cell array
%        contents{get(hObject,'Value')} returns selected item from ParameterList

% --- Executes during object creation, after setting all properties.
function ParameterList_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ParameterList (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on selection change in ControlList.
function ControlList_Callback(hObject, eventdata, handles)
% hObject    handle to ControlList (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns ControlList contents as cell array
%        contents{get(hObject,'Value')} returns selected item from ControlList

% --- Executes during object creation, after setting all properties.
function ControlList_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ControlList (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function TotalNumVar_Callback(hObject, eventdata, handles)
% hObject    handle to TotalNumVar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of TotalNumVar as text
%        str2double(get(hObject,'String')) returns contents of TotalNumVar as a double

% --- Executes during object creation, after setting all properties.
function TotalNumVar_CreateFcn(hObject, eventdata, handles)
% hObject    handle to TotalNumVar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on selection change in NodeName.
function NodeName_Callback(hObject, eventdata, handles)
% hObject    handle to NodeName (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns NodeName contents as cell array
%        contents{get(hObject,'Value')} returns selected item from NodeName
try
    handles.sel_node=get(handles.NodeName,'Value');
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function NodeName_CreateFcn(hObject, eventdata, handles)
% hObject    handle to NodeName (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function Pos_X_Callback(hObject, eventdata, handles)
% hObject    handle to Pos_X (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Pos_X as text
%        str2double(get(hObject,'String')) returns contents of Pos_X as a double
try
    pos=handles.ten_const.nodes(handles.sel_node).position(1);
    pos.value=str2num(get(handles.Pos_X,'String'));
    handles.ten_const.nodes(handles.sel_node).position(1)=pos;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function Pos_X_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Pos_X (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function Pos_Z_Callback(hObject, eventdata, handles)
% hObject    handle to Pos_Z (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Pos_Z as text
%        str2double(get(hObject,'String')) returns contents of Pos_Z as a double
try
    pos=handles.ten_const.nodes(handles.sel_node).position(3);
    pos.value=str2num(get(handles.Pos_Z,'String'));
    handles.ten_const.nodes(handles.sel_node).position(3)=pos;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function Pos_Z_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Pos_Z (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function Pos_Y_Callback(hObject, eventdata, handles)
% hObject    handle to Pos_Y (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Pos_Y as text
%        str2double(get(hObject,'String')) returns contents of Pos_Y as a double
try
    pos=handles.ten_const.nodes(handles.sel_node).position(2);
    pos.value=str2num(get(handles.Pos_Y,'String'));
    handles.ten_const.nodes(handles.sel_node).position(2)=pos;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function Pos_Y_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Pos_Y (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on selection change in ExternalForces.
function ExternalForces_Callback(hObject, eventdata, handles)
% hObject    handle to ExternalForces (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns ExternalForces contents as cell array
%        contents{get(hObject,'Value')} returns selected item from ExternalForces
try
    handles.sel_force=get(handles.ExternalForces,'Value');
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function ExternalForces_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ExternalForces (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function Force_X_Callback(hObject, eventdata, handles)
% hObject    handle to Force_X (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Force_X as text
%        str2double(get(hObject,'String')) returns contents of Force_X as a double
try
    force=handles.ten_const.nodes(handles.sel_node).forces(handles.sel_force,1);
    force.value=str2num(get(handles.Force_X,'String'));
    handles.ten_const.nodes(handles.sel_node).forces(handles.sel_force,1)=force;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function Force_X_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Force_X (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function Force_Z_Callback(hObject, eventdata, handles)
% hObject    handle to Force_Z (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Force_Z as text
%        str2double(get(hObject,'String')) returns contents of Force_Z as a double
try
    force=handles.ten_const.nodes(handles.sel_node).forces(handles.sel_force,3);
    force.value=str2num(get(handles.Force_Z,'String'));
    handles.ten_const.nodes(handles.sel_node).forces(handles.sel_force,3)=force;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end
% --- Executes during object creation, after setting all properties.
function Force_Z_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Force_Z (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function Force_Y_Callback(hObject, eventdata, handles)
% hObject    handle to Force_Y (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Force_Y as text
%        str2double(get(hObject,'String')) returns contents of Force_Y as a double
try
    force=handles.ten_const.nodes(handles.sel_node).forces(handles.sel_force,2);
    force.value=str2num(get(handles.Force_Y,'String'));
    handles.ten_const.nodes(handles.sel_node).forces(handles.sel_force,2)=force;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function Force_Y_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Force_Y (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function NumForces_Callback(hObject, eventdata, handles)
% hObject    handle to NumForces (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of NumForces as text
%        str2double(get(hObject,'String')) returns contents of NumForces as a double

% --- Executes during object creation, after setting all properties.
function NumForces_CreateFcn(hObject, eventdata, handles)
% hObject    handle to NumForces (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on selection change in EdgeName.
function EdgeName_Callback(hObject, eventdata, handles)
% hObject    handle to EdgeName (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns EdgeName contents as cell array
%        contents{get(hObject,'Value')} returns selected item from EdgeName
try
    handles.sel_edge=get(handles.EdgeName,'Value');
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function EdgeName_CreateFcn(hObject, eventdata, handles)
% hObject    handle to EdgeName (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function Stiffness_Callback(hObject, eventdata, handles)
% hObject    handle to Stiffness (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Stiffness as text
%        str2double(get(hObject,'String')) returns contents of Stiffness as a double
try
    stiffness=handles.ten_const.edges(handles.sel_edge).stiffness;
    stiffness.value=str2num(get(handles.Stiffness,'String'));
    handles.ten_const.edges(handles.sel_edge).stiffness=stiffness;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function Stiffness_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Stiffness (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function RestLength_Callback(hObject, eventdata, handles)
% hObject    handle to RestLength (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of RestLength as text
%        str2double(get(hObject,'String')) returns contents of RestLength as a double

% --- Executes during object creation, after setting all properties.
function RestLength_CreateFcn(hObject, eventdata, handles)
% hObject    handle to RestLength (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function RL_Min_Callback(hObject, eventdata, handles)
% hObject    handle to RL_Min (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of RL_Min as text
%        str2double(get(hObject,'String')) returns contents of RL_Min as a double
try
    rest_length=handles.ten_const.edges(handles.sel_edge).rest_length;
    rest_length.value(1)=str2num(get(handles.RL_Min,'String'));
    handles.ten_const.edges(handles.sel_edge).rest_length=rest_length;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function RL_Min_CreateFcn(hObject, eventdata, handles)
% hObject    handle to RL_Min (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function RL_Default_Callback(hObject, eventdata, handles)
% hObject    handle to RL_Default (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of RL_Default as text
%        str2double(get(hObject,'String')) returns contents of RL_Default as a double
try
    rest_length=handles.ten_const.edges(handles.sel_edge).rest_length;
    rest_length.value(1)=str2num(get(handles.RL_Default,'String'));
    rest_length.value(2)=str2num(get(handles.RL_Default,'String'));
    handles.ten_const.edges(handles.sel_edge).rest_length=rest_length;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function RL_Default_CreateFcn(hObject, eventdata, handles)
% hObject    handle to RL_Default (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function RL_Max_Callback(hObject, eventdata, handles)
% hObject    handle to RL_Max (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of RL_Max as text
%        str2double(get(hObject,'String')) returns contents of RL_Max as a double
try
    rest_length=handles.ten_const.edges(handles.sel_edge).rest_length;
    rest_length.value(2)=str2num(get(handles.RL_Max,'String'));
    handles.ten_const.edges(handles.sel_edge).rest_length=rest_length;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function RL_Max_CreateFcn(hObject, eventdata, handles)
% hObject    handle to RL_Max (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on selection change in Coplanar_SetNodes.
function Coplanar_SetNodes_Callback(hObject, eventdata, handles)
% hObject    handle to Coplanar_SetNodes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns Coplanar_SetNodes contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Coplanar_SetNodes

% --- Executes during object creation, after setting all properties.
function Coplanar_SetNodes_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Coplanar_SetNodes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on selection change in Coplanar_AllNodes.
function Coplanar_AllNodes_Callback(hObject, eventdata, handles)
% hObject    handle to Coplanar_AllNodes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns Coplanar_AllNodes contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Coplanar_AllNodes

% --- Executes during object creation, after setting all properties.
function Coplanar_AllNodes_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Coplanar_AllNodes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on selection change in CoplanarSet.
function CoplanarSet_Callback(hObject, eventdata, handles)
% hObject    handle to CoplanarSet (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns CoplanarSet contents as cell array
%        contents{get(hObject,'Value')} returns selected item from CoplanarSet
try
    handles.sel_cp_set=get(handles.CoplanarSet,'Value');
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function CoplanarSet_CreateFcn(hObject, eventdata, handles)
% hObject    handle to CoplanarSet (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in CreateSet.
function CreateSet_Callback(hObject, eventdata, handles)
% hObject    handle to CreateSet (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    handles.ten_const=addcoplanarset(handles.ten_const);
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes on button press in DeleteSet.
function DeleteSet_Callback(hObject, eventdata, handles)
% hObject    handle to DeleteSet (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    if handles.ten_const.num_cop_sets>0
        handles.ten_const=removecoplanarset(handles.ten_const,handles.sel_cp_set);
        if handles.sel_cp_set> handles.ten_const.num_cop_sets
            if handles.ten_const.num_cop_sets==0
                handles.sel_cp_set=1;
            else
                handles.sel_cp_set=handles.ten_const.num_cop_sets;
            end
        end
        UpdateInfo(hObject,handles);
    end
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes on button press in Coplanar_AddNode.
function Coplanar_AddNode_Callback(hObject, eventdata, handles)
% hObject    handle to Coplanar_AddNode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    sel_node=get(handles.Coplanar_AllNodes,'Value');
    nc=handles.ten_const.nodes(sel_node);
    handles.ten_const=addcoplanarnode(handles.ten_const,handles.sel_cp_set,nc);
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes on button press in Coplanar_RemoveNode.
function Coplanar_RemoveNode_Callback(hObject, eventdata, handles)
% hObject    handle to Coplanar_RemoveNode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    sel_node=get(handles.Coplanar_SetNodes,'Value');
    nc=handles.ten_const.nodes(sel_node);
    handles.ten_const=removecoplanarnode(handles.ten_const,handles.sel_cp_set,nc);
    set(handles.Coplanar_SetNodes,'Value',1);
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

function Normal_X_Callback(hObject, eventdata, handles)
% hObject    handle to Normal_X (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Normal_X as text
%        str2double(get(hObject,'String')) returns contents of Normal_X as a double
try
    normal=handles.ten_const.cop_sets(handles.sel_cp_set).normal(1);
    normal.value=str2num(get(handles.Normal_X,'String'));
    handles.ten_const.cop_sets(handles.sel_cp_set).normal(1)=normal;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function Normal_X_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Normal_X (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function Normal_Y_Callback(hObject, eventdata, handles)
% hObject    handle to Normal_Y (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Normal_Y as text
%        str2double(get(hObject,'String')) returns contents of Normal_Y as a double
try
    normal=handles.ten_const.cop_sets(handles.sel_cp_set).normal(2);
    normal.value=str2num(get(handles.Normal_Y,'String'));
    handles.ten_const.cop_sets(handles.sel_cp_set).normal(2)=normal;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function Normal_Y_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Normal_Y (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function Normal_Z_Callback(hObject, eventdata, handles)
% hObject    handle to Normal_Z (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Normal_Z as text
%        str2double(get(hObject,'String')) returns contents of Normal_Z as a double
try
    normal=handles.ten_const.cop_sets(handles.sel_cp_set).normal(3);
    normal.value=str2num(get(handles.Normal_Z,'String'));
    handles.ten_const.cop_sets(handles.sel_cp_set).normal(3)=normal;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function Normal_Z_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Normal_Z (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function OriginDist_Callback(hObject, eventdata, handles)
% hObject    handle to OriginDist (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of OriginDist as text
%        str2double(get(hObject,'String')) returns contents of OriginDist as a double
try
    dist=handles.ten_const.cop_sets(handles.sel_cp_set).dist;
    dist.value=str2num(get(handles.OriginDist,'String'));
    handles.ten_const.cop_sets(handles.sel_cp_set).dist=dist;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function OriginDist_CreateFcn(hObject, eventdata, handles)
% hObject    handle to OriginDist (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on selection change in CM_Nodes.
function CM_Nodes_Callback(hObject, eventdata, handles)
% hObject    handle to CM_Nodes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns CM_Nodes contents as cell array
%        contents{get(hObject,'Value')} returns selected item from CM_Nodes

% --- Executes during object creation, after setting all properties.
function CM_Nodes_CreateFcn(hObject, eventdata, handles)
% hObject    handle to CM_Nodes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on selection change in CM_AllNodes.
function CM_AllNodes_Callback(hObject, eventdata, handles)
% hObject    handle to CM_AllNodes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns CM_AllNodes contents as cell array
%        contents{get(hObject,'Value')} returns selected item from CM_AllNodes

% --- Executes during object creation, after setting all properties.
function CM_AllNodes_CreateFcn(hObject, eventdata, handles)
% hObject    handle to CM_AllNodes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in CM_AddNode.
function CM_AddNode_Callback(hObject, eventdata, handles)
% hObject    handle to CM_AddNode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    sel_node=get(handles.CM_AllNodes,'Value');
    nc=handles.ten_const.nodes(sel_node);
    handles.ten_const=addcmnode(handles.ten_const,nc);
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes on button press in CM_RemoveNode.
function CM_RemoveNode_Callback(hObject, eventdata, handles)
% hObject    handle to CM_RemoveNode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    sel_node=get(handles.CM_Nodes,'Value');
    nodes=get(handles.CM_Nodes,'String');
    node_name=nodes(sel_node,:);
    nc=handles.ten_const.nodes(node_name);
    handles.ten_const=removecmnode(handles.ten_const,nc);
    set(handles.CM_Nodes,'Value',1);
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes on button press in Cables.
function Cables_Callback(hObject, eventdata, handles)
% hObject    handle to Cables (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Cables

% --- Executes on button press in Struts.
function Struts_Callback(hObject, eventdata, handles)
% hObject    handle to Struts (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Struts

function CostFuncFile_Callback(hObject, eventdata, handles)
% hObject    handle to CostFuncFile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of CostFuncFile as text
%        str2double(get(hObject,'String')) returns contents of CostFuncFile as a double

% --- Executes during object creation, after setting all properties.
function CostFuncFile_CreateFcn(hObject, eventdata, handles)
% hObject    handle to CostFuncFile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in CostFuncBrowse.
function CostFuncBrowse_Callback(hObject, eventdata, handles)
% hObject    handle to CostFuncBrowse (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    [filename,pathname]=uigetfile({'*.m','Cost function files(*.m)'},'Cost function');
    if filename~=0 
        handles.ten_const=setcostfunction(handles.ten_const,filename);
        set(handles.CostFuncFile,'String',filename);    
        guidata(hObject,handles);
    end
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

function CM_Pos_X_Callback(hObject, eventdata, handles)
% hObject    handle to CM_Pos_X (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of CM_Pos_X as text
%        str2double(get(hObject,'String')) returns contents of CM_Pos_X as a double
try
    position=handles.ten_const.cm.position(1);
    position.value=str2num(get(handles.CM_Pos_X,'String'));
    handles.ten_const.cm.position(1)=position;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function CM_Pos_X_CreateFcn(hObject, eventdata, handles)
% hObject    handle to CM_Pos_X (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function CM_Pos_Y_Callback(hObject, eventdata, handles)
% hObject    handle to CM_Pos_Y (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of CM_Pos_Y as text
%        str2double(get(hObject,'String')) returns contents of CM_Pos_Y as a double
try
    position=handles.ten_const.cm.position(2);
    position.value=str2num(get(handles.CM_Pos_Y,'String'));
    handles.ten_const.cm.position(2)=position;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function CM_Pos_Y_CreateFcn(hObject, eventdata, handles)
% hObject    handle to CM_Pos_Y (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function CM_Pos_Z_Callback(hObject, eventdata, handles)
% hObject    handle to CM_Pos_Z (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of CM_Pos_Z as text
%        str2double(get(hObject,'String')) returns contents of CM_Pos_Z as a double
try
    position=handles.ten_const.cm.position(3);
    position.value=str2num(get(handles.CM_Pos_Z,'String'));
    handles.ten_const.cm.position(3)=position;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function CM_Pos_Z_CreateFcn(hObject, eventdata, handles)
% hObject    handle to CM_Pos_Z (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function CM_Rot_X_Callback(hObject, eventdata, handles)
% hObject    handle to CM_Rot_X (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of CM_Rot_X as text
%        str2double(get(hObject,'String')) returns contents of CM_Rot_X as a double
try
    orientation=handles.ten_const.cm.orientation(1);
    orientation.value=str2num(get(handles.CM_Rot_X,'String'));
    handles.ten_const.cm.orientation(1)=orientation;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function CM_Rot_X_CreateFcn(hObject, eventdata, handles)
% hObject    handle to CM_Rot_X (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function CM_Rot_Y_Callback(hObject, eventdata, handles)
% hObject    handle to CM_Rot_Y (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of CM_Rot_Y as text
%        str2double(get(hObject,'String')) returns contents of CM_Rot_Y as a double
try
    orientation=handles.ten_const.cm.orientation(2);
    orientation.value=str2num(get(handles.CM_Rot_Y,'String'));
    handles.ten_const.cm.orientation(2)=orientation;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function CM_Rot_Y_CreateFcn(hObject, eventdata, handles)
% hObject    handle to CM_Rot_Y (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function CM_Rot_Z_Callback(hObject, eventdata, handles)
% hObject    handle to CM_Rot_Z (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of CM_Rot_Z as text
%        str2double(get(hObject,'String')) returns contents of CM_Rot_Z as a double
try
    orientation=handles.ten_const.cm.orientation(3);
    orientation.value=str2num(get(handles.CM_Rot_Z,'String'));
    handles.ten_const.cm.orientation(3)=orientation;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function CM_Rot_Z_CreateFcn(hObject, eventdata, handles)
% hObject    handle to CM_Rot_Z (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
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

% --- Executes on button press in Import.
function Import_Callback(hObject, eventdata, handles)
% hObject    handle to Import (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    handles.ten_const=tenconst();
    if ~isempty(handles.ConstraintFile)
        handles.ten_const=loadconstraints(handles.ten_const,handles.ConstraintFile);
        set(handles.TopologyFilename,'String',handles.ten_const.filename);
        set(handles.VarName,'Enable','on');
        set(handles.FixedButton,'Enable','on');
        set(handles.PassiveButton,'Enable','on');
        set(handles.ParameterButton,'Enable','on');
        set(handles.ActuatedButton,'Enable','on');
        set(handles.VarName,'Enable','on');
        set(handles.EdgeName,'Enable','on');
        set(handles.NodeName,'Enable','on');
        set(handles.CreateSet,'Enable','on');
        set(handles.DeleteSet,'Enable','on');
        set(handles.Coplanar_AddNode,'Enable','on');
        set(handles.Coplanar_RemoveNode,'Enable','on');
        set(handles.CM_AddNode,'Enable','on');
        set(handles.CM_RemoveNode,'Enable','on');
        set(handles.MinEnergy,'Enable','on');
        set(handles.Cables,'Enable','on');
        set(handles.Struts,'Enable','on');
        set(handles.FromFileButton,'Enable','on');
        set(handles.CostFuncFile,'Enable','on');
        set(handles.CostFuncBrowse,'Enable','on');
        set(handles.AddForce,'Enable','on');
        set(handles.RemoveForce,'Enable','on');    
        set(handles.MinEnergy,'Enable','on');
        set(handles.FromFileButton,'Enable','on');
        UpdateInfo(hObject,handles);
    end
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
    filename=get(handles.ConstFilename,'String');
    if ~isempty(filename)
        if isempty(strfind(filename,'.cst'))
            filename=[filename,'.cst'];
        end
        saveconstraints(handles.ten_const,filename);
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
    
% --- Executes on button press in Browse.
function Browse_Callback(hObject, eventdata, handles)
% hObject    handle to Browse (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filename,pathname]=uigetfile({'*.cst','Tensegrity constraint file (*.cst)'},'Tensegrity constraint file');
if filename~=0 
    handles.ConstraintFile=[pathname,filename];
    set(handles.ConstFilename,'String',filename);    
    guidata(hObject,handles);
end

function FixedButton_Callback(hObject, eventdata, handles)
try
    var=handles.ten_const.variables(handles.sel_var);
    var.type='fixed';
    handles.ten_const=setvariable(handles.ten_const,handles.sel_var,var);
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

function PassiveButton_Callback(hObject, eventdata, handles)
try
    var=handles.ten_const.variables(handles.sel_var);
    var.type='passive';
    handles.ten_const=setvariable(handles.ten_const,handles.sel_var,var);
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

function ParameterButton_Callback(hObject, eventdata, handles)
try
    var=handles.ten_const.variables(handles.sel_var);
    var.type='parameter';
    handles.ten_const=setvariable(handles.ten_const,handles.sel_var,var);
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

function ActuatedButton_Callback(hObject, eventdata, handles)
try
    var=handles.ten_const.variables(handles.sel_var);
    var.type='actuated';
    handles.ten_const=setvariable(handles.ten_const,handles.sel_var,var);
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

function MinEnergy_Callback(hObject, eventdata, handles)
try
    handles.ten_const=setcostfunction(handles.ten_const,'MinimumEnergy');
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

function TopologyFilename_Callback(hObject, eventdata, handles)
% hObject    handle to TopologyFilename (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of TopologyFilename as text
%        str2double(get(hObject,'String')) returns contents of TopologyFilename as a double

% --- Executes during object creation, after setting all properties.
function TopologyFilename_CreateFcn(hObject, eventdata, handles)
% hObject    handle to TopologyFilename (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in AddForce.
function AddForce_Callback(hObject, eventdata, handles)
% hObject    handle to AddForce (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    handles.ten_const.nodes(handles.sel_node)=addexternalforce(handles.ten_const.nodes(handles.sel_node));
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes on button press in RemoveForce.
function RemoveForce_Callback(hObject, eventdata, handles)
% hObject    handle to RemoveForce (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    if handles.ten_const.nodes(handles.sel_node).num_forces>0
        handles.ten_const.nodes(handles.sel_node)=removeexternalforce(handles.ten_const.nodes(handles.sel_node),handles.sel_force);
        if handles.sel_force>handles.ten_const.nodes(handles.sel_node).num_forces
            if handles.ten_const.nodes(handles.sel_node).num_forces==0
                handles.sel_force=1;
            else
                handles.sel_force=handles.ten_const.nodes(handles.sel_node).num_forces;
            end
        end
        UpdateInfo(hObject,handles);
    end
catch
    error=lasterror;
    errordlg(error.message);
    return;
end
    
function UpdateInfo(hObject,handles)
try
    [handles.ten_const,num_var,variables]=getvariables(handles.ten_const);
    var_constants='';
    var_optimization='';
    var_parameters='';
    var_actuated='';
    var_names='';
    set(handles.TotalNumVar,'String',num2str(num_var));
    for i=1:1:num_var
        switch variables(i).type
            case 'fixed'
                var_constants=strvcat(var_constants,variables(i).name);
            case 'passive'
                var_optimization=strvcat(var_optimization,variables(i).name);
            case 'parameter'
                var_parameters=strvcat(var_parameters,variables(i).name);
            case 'actuated'
                var_actuated=strvcat(var_actuated,variables(i).name);
        end
        var_names=strvcat(var_names,variables(i).name);
    end
    set(handles.ConstantsList,'String',var_constants);
    set(handles.OptimizationList,'String',var_optimization);
    set(handles.ParameterList,'String',var_parameters);
    set(handles.ControlList,'String',var_actuated);
    set(handles.VarName,'String',var_names);
    if handles.sel_var>num_var
        handles.sel_var=num_var;
    end
    set(handles.VarName,'Value',handles.sel_var);
    switch variables(handles.sel_var).type
            case 'fixed'
                set(handles.FixedButton,'Value',1);
                set(handles.PassiveButton,'Value',0);
                set(handles.ParameterButton,'Value',0);
                set(handles.ActuatedButton,'Value',0);            
            case 'passive'
                set(handles.FixedButton,'Value',0);
                set(handles.PassiveButton,'Value',1);
                set(handles.ParameterButton,'Value',0);
                set(handles.ActuatedButton,'Value',0);            
            case 'parameter'
                set(handles.FixedButton,'Value',0);
                set(handles.PassiveButton,'Value',0);
                set(handles.ParameterButton,'Value',1);
                set(handles.ActuatedButton,'Value',0);            
            case 'actuated'
                set(handles.FixedButton,'Value',0);
                set(handles.PassiveButton,'Value',0);
                set(handles.ParameterButton,'Value',0);
                set(handles.ActuatedButton,'Value',1);            
    end

    % restriccions dels nodes
    node_names='';
    for i=1:1:handles.ten_const.num_nodes
        node_names=strvcat(node_names,handles.ten_const.nodes(i).name);
    end
    set(handles.NodeName,'String',node_names);
    set(handles.NodeName,'Value',handles.sel_node);
    node=handles.ten_const.nodes(handles.sel_node);
    if strcmp(node.position(1).type,'fixed')
        set(handles.Pos_X,'Enable','on');    
        set(handles.Pos_X,'String',num2str(node.position(1).value));
    else
        set(handles.Pos_X,'Enable','off');
        set(handles.Pos_X,'String','');    
    end
    if strcmp(node.position(2).type,'fixed')
        set(handles.Pos_Y,'Enable','on');    
        set(handles.Pos_Y,'String',num2str(node.position(2).value));
    else
        set(handles.Pos_Y,'Enable','off');
        set(handles.Pos_Y,'String','');        
    end
    if strcmp(node.position(3).type,'fixed')
        set(handles.Pos_Z,'Enable','on');    
        set(handles.Pos_Z,'String',num2str(node.position(3).value));
    else
        set(handles.Pos_Z,'Enable','off');
        set(handles.Pos_Z,'String','');        
    end
    set(handles.NumForces,'String',num2str(node.num_forces));
    if node.num_forces>0
        set(handles.ExternalForces,'Enable','on');
        force_names='';
        for i=1:1:node.num_forces
            force_names=strvcat(force_names,['force_',num2str(i)]);
        end
        set(handles.ExternalForces,'String',force_names);
        set(handles.ExternalForces,'Value',handles.sel_force);
        force=node.forces(handles.sel_force,:);    
        if strcmp(force(1).type,'fixed')
            set(handles.Force_X,'Enable','on');
            set(handles.Force_X,'String',num2str(force(1).value));        
        else
            set(handles.Force_X,'Enable','off');
            set(handles.Force_X,'String','');        
        end
        if strcmp(force(2).type,'fixed')
            set(handles.Force_Y,'Enable','on');
            set(handles.Force_Y,'String',num2str(force(2).value));        
        else
            set(handles.Force_Y,'Enable','off');
            set(handles.Force_Y,'String','');        
        end
        if strcmp(force(3).type,'fixed')
            set(handles.Force_Z,'Enable','on');
            set(handles.Force_Z,'String',num2str(force(3).value));        
        else
            set(handles.Force_Z,'Enable','off');
            set(handles.Force_Z,'String','');        
        end
    else
        set(handles.ExternalForces,'Enable','off');
        set(handles.ExternalForces,'String','none');
        set(handles.Force_X,'Enable','off');
        set(handles.Force_X,'String','');    
        set(handles.Force_Y,'Enable','off');
        set(handles.Force_Y,'String','');        
        set(handles.Force_Z,'Enable','off');
        set(handles.Force_Z,'String','');        
    end
    % restriccions de les arestes
    edge_names='';
    for i=1:1:handles.ten_const.num_edges
        edge_names=strvcat(edge_names,handles.ten_const.edges(i).name);
    end
    set(handles.EdgeName,'String',edge_names);
    set(handles.EdgeName,'Value',handles.sel_edge);
    edge=handles.ten_const.edges(handles.sel_edge);
    if strcmp(edge.stiffness.type,'fixed')
        set(handles.Stiffness,'Enable','on');
        set(handles.Stiffness,'String',num2str(edge.stiffness.value));
    else
        set(handles.Stiffness,'Enable','off');
        set(handles.Stiffness,'String','');
    end
    if strcmp(edge.rest_length.type,'fixed')
        set(handles.RL_Default,'Enable','on');
        value=edge.rest_length.value;
        set(handles.RL_Default,'String',num2str(value(1)));
        set(handles.RL_Min,'Enable','off');
        set(handles.RL_Min,'String','');
        set(handles.RL_Max,'Enable','off');
        set(handles.RL_Max,'String','');
    else
        if strcmp(edge.rest_length.type,'passive') || strcmp(edge.rest_length.type,'actuated')
            set(handles.RL_Default,'Enable','off');
            set(handles.RL_Default,'String','');
            set(handles.RL_Min,'Enable','on');
            value=edge.rest_length.value;
            set(handles.RL_Min,'String',num2str(value(1)));        
            set(handles.RL_Max,'Enable','on');
            set(handles.RL_Max,'String',num2str(value(2)));        
        else
            set(handles.RL_Default,'Enable','off');
            set(handles.RL_Default,'String','');
            set(handles.RL_Min,'Enable','off');
            set(handles.RL_Min,'String','');
            set(handles.RL_Max,'Enable','off');
            set(handles.RL_Max,'String','');
        end
    end
    % restriccions del centre de masses
    set(handles.CM_AllNodes,'String',node_names);
    cm_const=handles.ten_const.cm;
    cm_nodes='';
    for i=1:1:cm_const.num_nodes
        cm_nodes=strvcat(cm_nodes,cm_const.nodes(i).name);
    end
    set(handles.CM_Nodes,'String',cm_nodes);
    if strcmp(cm_const.position(1).type,'fixed')
        set(handles.CM_Pos_X,'String',cm_const.position(1).value);
        set(handles.CM_Pos_X,'Enable','on');
    else
        set(handles.CM_Pos_X,'String','');
        set(handles.CM_Pos_X,'Enable','off');
    end
    if strcmp(cm_const.position(2).type,'fixed')
        set(handles.CM_Pos_Y,'String',cm_const.position(2).value);
        set(handles.CM_Pos_Y,'Enable','on');
    else
        set(handles.CM_Pos_Y,'String','');
        set(handles.CM_Pos_Y,'Enable','off');
    end
    if strcmp(cm_const.position(3).type,'fixed')
        set(handles.CM_Pos_Z,'String',cm_const.position(3).value);
        set(handles.CM_Pos_Z,'Enable','on');
    else
        set(handles.CM_Pos_Z,'String','');
        set(handles.CM_Pos_Z,'Enable','off');
    end
    if strcmp(cm_const.orientation(1).type,'fixed')
        set(handles.CM_Rot_X,'String',cm_const.orientation(1).value);
        set(handles.CM_Rot_X,'Enable','on');
    else
        set(handles.CM_Rot_X,'String','');
        set(handles.CM_Rot_X,'Enable','off');
    end
    if strcmp(cm_const.orientation(2).type,'fixed')
        set(handles.CM_Rot_Y,'String',cm_const.orientation(2).value);
        set(handles.CM_Rot_Y,'Enable','on');
    else
        set(handles.CM_Rot_Y,'String','');
        set(handles.CM_Rot_Y,'Enable','off');
    end
    if strcmp(cm_const.orientation(3).type,'fixed')
        set(handles.CM_Rot_Z,'String',cm_const.orientation(3).value);
        set(handles.CM_Rot_Z,'Enable','on');
    else
        set(handles.CM_Rot_Z,'String','');
        set(handles.CM_Rot_Z,'Enable','off');
    end

    % restriccions de nodes coplanars
    set(handles.Coplanar_AllNodes,'String',node_names);
    if handles.ten_const.num_cop_sets>0
        set_names='';
        for i=1:1:handles.ten_const.num_cop_sets
            set_names=strvcat(set_names,['set_',num2str(i)]);
        end
        set(handles.CoplanarSet,'Enable','on');    
        set(handles.CoplanarSet,'String',set_names);
        set(handles.CoplanarSet,'Value',handles.sel_cp_set);
        cp_const=handles.ten_const.cop_sets(handles.sel_cp_set);
        cp_nodes='';
        for i=1:1:cp_const.num_nodes
            cp_nodes=strvcat(cp_nodes,cp_const.nodes(i).name);
        end
        set(handles.Coplanar_SetNodes,'String',cp_nodes);
        if strcmp(cp_const.normal(1).type,'fixed')
            set(handles.Normal_X,'String',num2str(cp_const.normal(1).value));
            set(handles.Normal_X,'Enable','on');
        else
            set(handles.Normal_X,'String','');
            set(handles.Normal_X,'Enable','off');
        end
        if strcmp(cp_const.normal(2).type,'fixed')
            set(handles.Normal_Y,'String',num2str(cp_const.normal(2).value));
            set(handles.Normal_Y,'Enable','on');
        else
            set(handles.Normal_Y,'String','');
            set(handles.Normal_Y,'Enable','off');
        end
        if strcmp(cp_const.normal(3).type,'fixed')
            set(handles.Normal_Z,'String',num2str(cp_const.normal(3).value));
            set(handles.Normal_Z,'Enable','on');
        else
            set(handles.Normal_Z,'String','');
            set(handles.Normal_Z,'Enable','off');
        end
        if strcmp(cp_const.dist.type,'fixed')
            set(handles.OriginDist,'String',num2str(cp_const.dist.value));
            set(handles.OriginDist,'Enable','on');
        else
            set(handles.OriginDist,'String','');
            set(handles.OriginDist,'Enable','off');
        end
    else
        set(handles.CoplanarSet,'Enable','off');        
        set(handles.CoplanarSet,'String','none');    
        set(handles.Normal_X,'Enable','off');    
        set(handles.Normal_Y,'Enable','off');    
        set(handles.Normal_Z,'Enable','off');    
        set(handles.OriginDist,'Enable','off');    
        set(handles.Coplanar_SetNodes,'String','');
        set(handles.Coplanar_SetNodes,'Value',1);
    end
    % funció de cost
    if ~isempty(handles.ten_const.cost_func)
        if strcmp(handles.ten_const.cost_func,'MinimumEnergy.m')
            set(handles.MinEnergy,'Value',1);
            set(handles.CostFuncFile,'Enable','off');
            set(handles.CostFuncBrowse,'Enable','off');
            set(handles.Cables,'Enable','on');
            set(handles.Struts,'Enable','on');
        else
            set(handles.FromFileButton,'Value',1);
            set(handles.CostFuncFile,'Enable','on');
            set(handles.CostFuncBrowse,'Enable','on');
            set(handles.Cables,'Enable','off');
            set(handles.Struts,'Enable','off');
        end
    end

    guidata(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes on button press in Done.
function Done_Callback(hObject, eventdata, handles)
% hObject    handle to Done (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
uiresume(handles.Constraints);