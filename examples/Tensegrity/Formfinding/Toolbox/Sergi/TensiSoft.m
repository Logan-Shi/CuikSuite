function varargout = TensiSoft(varargin)
% TENSISOFT M-file for TensiSoft.fig
%      TENSISOFT, by itself, creates a new TENSISOFT or raises the existing
%      singleton*.
%
%      H = TENSISOFT returns the handle to a new TENSISOFT or the handle to
%      the existing singleton*.
%
%      TENSISOFT('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in TENSISOFT.M with the given input arguments.
%
%      TENSISOFT('Property','Value',...) creates a new TENSISOFT or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before TensiSoft_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to TensiSoft_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help TensiSoft

% Last Modified by GUIDE v2.5 06-Mar-2008 17:40:37

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @TensiSoft_OpeningFcn, ...
                   'gui_OutputFcn',  @TensiSoft_OutputFcn, ...
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


% --- Executes just before TensiSoft is made visible.
function TensiSoft_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to TensiSoft (see VARARGIN)

% Choose default command line output for TensiSoft
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes TensiSoft wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = TensiSoft_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



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


% --- Executes on button press in BrowseTopology.
function BrowseTopology_Callback(hObject, eventdata, handles)
% hObject    handle to BrowseTopology (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function NumNodes_Callback(hObject, eventdata, handles)
% hObject    handle to NumNodes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of NumNodes as text
%        str2double(get(hObject,'String')) returns contents of NumNodes as a double


% --- Executes during object creation, after setting all properties.
function NumNodes_CreateFcn(hObject, eventdata, handles)
% hObject    handle to NumNodes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function NumStruts_Callback(hObject, eventdata, handles)
% hObject    handle to NumStruts (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of NumStruts as text
%        str2double(get(hObject,'String')) returns contents of NumStruts as a double


% --- Executes during object creation, after setting all properties.
function NumStruts_CreateFcn(hObject, eventdata, handles)
% hObject    handle to NumStruts (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function NumCables_Callback(hObject, eventdata, handles)
% hObject    handle to NumCables (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of NumCables as text
%        str2double(get(hObject,'String')) returns contents of NumCables as a double


% --- Executes during object creation, after setting all properties.
function NumCables_CreateFcn(hObject, eventdata, handles)
% hObject    handle to NumCables (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Class_Callback(hObject, eventdata, handles)
% hObject    handle to Class (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Class as text
%        str2double(get(hObject,'String')) returns contents of Class as a double


% --- Executes during object creation, after setting all properties.
function Class_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Class (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in EditTopology.
function EditTopology_Callback(hObject, eventdata, handles)
% hObject    handle to EditTopology (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function ConstraintsFile_Callback(hObject, eventdata, handles)
% hObject    handle to ConstraintsFile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ConstraintsFile as text
%        str2double(get(hObject,'String')) returns contents of ConstraintsFile as a double


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


% --- Executes on button press in BrowseConstraints.
function BrowseConstraints_Callback(hObject, eventdata, handles)
% hObject    handle to BrowseConstraints (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function NumPassVar_Callback(hObject, eventdata, handles)
% hObject    handle to NumPassVar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of NumPassVar as text
%        str2double(get(hObject,'String')) returns contents of NumPassVar as a double


% --- Executes during object creation, after setting all properties.
function NumPassVar_CreateFcn(hObject, eventdata, handles)
% hObject    handle to NumPassVar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function NumFixedVar_Callback(hObject, eventdata, handles)
% hObject    handle to NumFixedVar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of NumFixedVar as text
%        str2double(get(hObject,'String')) returns contents of NumFixedVar as a double


% --- Executes during object creation, after setting all properties.
function NumFixedVar_CreateFcn(hObject, eventdata, handles)
% hObject    handle to NumFixedVar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function NumActVar_Callback(hObject, eventdata, handles)
% hObject    handle to NumActVar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of NumActVar as text
%        str2double(get(hObject,'String')) returns contents of NumActVar as a double


% --- Executes during object creation, after setting all properties.
function NumActVar_CreateFcn(hObject, eventdata, handles)
% hObject    handle to NumActVar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function NumParam_Callback(hObject, eventdata, handles)
% hObject    handle to NumParam (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of NumParam as text
%        str2double(get(hObject,'String')) returns contents of NumParam as a double


% --- Executes during object creation, after setting all properties.
function NumParam_CreateFcn(hObject, eventdata, handles)
% hObject    handle to NumParam (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function NumEqConst_Callback(hObject, eventdata, handles)
% hObject    handle to NumEqConst (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of NumEqConst as text
%        str2double(get(hObject,'String')) returns contents of NumEqConst as a double


% --- Executes during object creation, after setting all properties.
function NumEqConst_CreateFcn(hObject, eventdata, handles)
% hObject    handle to NumEqConst (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function NumIneqConst_Callback(hObject, eventdata, handles)
% hObject    handle to NumIneqConst (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of NumIneqConst as text
%        str2double(get(hObject,'String')) returns contents of NumIneqConst as a double


% --- Executes during object creation, after setting all properties.
function NumIneqConst_CreateFcn(hObject, eventdata, handles)
% hObject    handle to NumIneqConst (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in EditConstraints.
function EditConstraints_Callback(hObject, eventdata, handles)
% hObject    handle to EditConstraints (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in GenerateConstraints.
function GenerateConstraints_Callback(hObject, eventdata, handles)
% hObject    handle to GenerateConstraints (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function EnvironmentFile_Callback(hObject, eventdata, handles)
% hObject    handle to EnvironmentFile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of EnvironmentFile as text
%        str2double(get(hObject,'String')) returns contents of EnvironmentFile as a double


% --- Executes during object creation, after setting all properties.
function EnvironmentFile_CreateFcn(hObject, eventdata, handles)
% hObject    handle to EnvironmentFile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in BrowseEnvironment.
function BrowseEnvironment_Callback(hObject, eventdata, handles)
% hObject    handle to BrowseEnvironment (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in ShowEnvironemnt.
function ShowEnvironemnt_Callback(hObject, eventdata, handles)
% hObject    handle to ShowEnvironemnt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of ShowEnvironemnt


% --- Executes on button press in EditEnvironment.
function EditEnvironment_Callback(hObject, eventdata, handles)
% hObject    handle to EditEnvironment (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


