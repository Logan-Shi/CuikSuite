function varargout = Topology(varargin)
% TOPOLOGY M-file for Topology.fig
%      TOPOLOGY, by itself, creates a new TOPOLOGY or raises the existing
%      singleton*.
%
%      H = TOPOLOGY returns the handle to a new TOPOLOGY or the handle to
%      the existing singleton*.
%
%      TOPOLOGY('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in TOPOLOGY.M with the given input arguments.
%
%      TOPOLOGY('Property','Value',...) creates a new TOPOLOGY or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Topology_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Topology_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Copyright 2002-2003 The MathWorks, Inc.

% Edit the above text to modify the response to help Topology

% Last Modified by GUIDE v2.5 21-Jan-2008 13:37:10

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Topology_OpeningFcn, ...
                   'gui_OutputFcn',  @Topology_OutputFcn, ...
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

% --- Executes just before Topology is made visible.
function Topology_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Topology (see VARARGIN)
% Choose default command line output for Topology
handles.output = hObject;
% Initialize the GUI objects
set(handles.RegularPrismButton,'Enable','off');
set(handles.SnelsonXButton,'Enable','off');
set(handles.CompleteButton,'Enable','off');
set(handles.RP_Sides,'Enable','off');
set(handles.RP_Stages,'Enable','off');
set(handles.SX_Rows,'Enable','off');
set(handles.SX_Columns,'Enable','off');
set(handles.C_NumNodes,'Enable','off');
set(handles.N_Dim2,'Enable','off');
set(handles.N_Dim3,'Enable','off');
set(handles.N_Class,'Enable','off');
set(handles.N_Nodes,'Enable','off');
set(handles.N_Cables,'Enable','off');
set(handles.N_Struts,'Enable','off');
set(handles.Generate,'Enable','off');
set(handles.N_NodeNames,'Enable','off');
set(handles.N_NumEdges,'Enable','off');
set(handles.N_IncidentEdges,'Enable','off');
set(handles.N_AllEdges,'Enable','off');
set(handles.N_AddEdge,'Enable','off');
set(handles.N_RemoveEdge,'Enable','off');
set(handles.N_EdgeNames,'Enable','off');
set(handles.N_CableButton,'Enable','off');
set(handles.N_StrutButton,'Enable','off');
set(handles.N_OriginNode,'Enable','off');
set(handles.N_EndNode,'Enable','off');
set(handles.N_Export,'Enable','off');
set(handles.N_FileName,'Enable','off');
set(handles.CreateNode,'Enable','off');
set(handles.DeleteNode,'Enable','off');
set(handles.CreateEdge,'Enable','off');
set(handles.DeleteEdge,'Enable','off');

handles.ten_top=[];
handles.sel_edge=1;
handles.sel_node=1;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Topology wait for user response (see UIRESUME)
uiwait(handles.Topology);

% --- Outputs from this function are returned to the command line.
function varargout = Topology_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if ~isempty(handles)
    mOutputArgs{1} = handles.ten_top;
    if nargout>0
        [varargout{1:nargout}] = mOutputArgs{:};
    end
end
close

% Get default command line output from handles structure
%varargout{1} = handles.output;

% --- Executes on button press in FromFileButton.
function FromFileButton_Callback(hObject, eventdata, handles)
% hObject    handle to FromFileButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% standard topology generation
set(handles.RegularPrismButton,'Enable','off');
set(handles.SnelsonXButton,'Enable','off');
set(handles.CompleteButton,'Enable','off');
set(handles.RP_Sides,'Enable','off');
set(handles.RP_Stages,'Enable','off');
set(handles.SX_Rows,'Enable','off');
set(handles.SX_Columns,'Enable','off');
set(handles.C_NumNodes,'Enable','off');
set(handles.Generate,'Enable','off');
% new topology generation
set(handles.N_Dim2,'Enable','off');
set(handles.N_Dim3,'Enable','off');
set(handles.N_Class,'Enable','off');
set(handles.N_Nodes,'Enable','off');
set(handles.N_Cables,'Enable','off');
set(handles.N_Struts,'Enable','off');
set(handles.N_NodeNames,'Enable','off');
set(handles.N_NumEdges,'Enable','off');
set(handles.N_IncidentEdges,'Enable','off');
set(handles.N_AllEdges,'Enable','off');
set(handles.N_AddEdge,'Enable','off');
set(handles.N_RemoveEdge,'Enable','off');
set(handles.N_EdgeNames,'Enable','off');
set(handles.N_CableButton,'Enable','off');
set(handles.N_StrutButton,'Enable','off');
set(handles.N_OriginNode,'Enable','off');
set(handles.N_EndNode,'Enable','off');
set(handles.N_Export,'Enable','off');
set(handles.N_FileName,'Enable','off');
set(handles.CreateNode,'Enable','off');
set(handles.DeleteNode,'Enable','off');
set(handles.CreateEdge,'Enable','off');
set(handles.DeleteEdge,'Enable','off');
% topology from file
set(handles.TopologyBrowse,'Enable','on');
set(handles.ImportTopology,'Enable','on');

% Update handles structure
guidata(hObject, handles);

% Hint: get(hObject,'Value') returns toggle state of FromFileButton

% --- Executes on button press in StandardTopologyButton.
function StandardTopologyButton_Callback(hObject, eventdata, handles)
% hObject    handle to StandardTopologyButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% standard topology generation
set(handles.RegularPrismButton,'Enable','on');
set(handles.SnelsonXButton,'Enable','on');
set(handles.CompleteButton,'Enable','on');
set(handles.RP_Sides,'Enable','on');
set(handles.RP_Stages,'Enable','on');
set(handles.SX_Rows,'Enable','on');
set(handles.SX_Columns,'Enable','on');
set(handles.C_NumNodes,'Enable','on');
set(handles.Generate,'Enable','on');
% new topology generation
set(handles.N_Dim2,'Enable','off');
set(handles.N_Dim3,'Enable','off');
set(handles.N_Class,'Enable','off');
set(handles.N_Nodes,'Enable','off');
set(handles.N_Cables,'Enable','off');
set(handles.N_Struts,'Enable','off');
set(handles.N_NodeNames,'Enable','off');
set(handles.N_NumEdges,'Enable','off');
set(handles.N_IncidentEdges,'Enable','off');
set(handles.N_AllEdges,'Enable','off');
set(handles.N_AddEdge,'Enable','off');
set(handles.N_RemoveEdge,'Enable','off');
set(handles.N_EdgeNames,'Enable','off');
set(handles.N_CableButton,'Enable','off');
set(handles.N_StrutButton,'Enable','off');
set(handles.N_OriginNode,'Enable','off');
set(handles.N_EndNode,'Enable','off');
set(handles.N_Export,'Enable','on');
set(handles.N_FileName,'Enable','on');
set(handles.CreateNode,'Enable','off');
set(handles.DeleteNode,'Enable','off');
set(handles.CreateEdge,'Enable','off');
set(handles.DeleteEdge,'Enable','off');
% topology from file
set(handles.TopologyBrowse,'Enable','off');
set(handles.ImportTopology,'Enable','off');

% Update handles structure
guidata(hObject, handles);

% Hint: get(hObject,'Value') returns toggle state of StandardTopologyButton

% --- Executes on button press in NewTopologyButton.
function NewTopologyButton_Callback(hObject, eventdata, handles)
% hObject    handle to NewTopologyButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% standard topology generation
set(handles.RegularPrismButton,'Enable','off');
set(handles.SnelsonXButton,'Enable','off');
set(handles.CompleteButton,'Enable','off');
set(handles.RP_Sides,'Enable','off');
set(handles.RP_Stages,'Enable','off');
set(handles.SX_Rows,'Enable','off');
set(handles.SX_Columns,'Enable','off');
set(handles.C_NumNodes,'Enable','off');
set(handles.Generate,'Enable','off');
% new topology generation
set(handles.N_Dim2,'Enable','on');
set(handles.N_Dim3,'Enable','on');
set(handles.N_Class,'Enable','on');
set(handles.N_Nodes,'Enable','off');
set(handles.N_Cables,'Enable','off');
set(handles.N_Struts,'Enable','off');
set(handles.N_NodeNames,'Enable','on');
set(handles.N_NumEdges,'Enable','off');
set(handles.N_IncidentEdges,'Enable','on');
set(handles.N_AllEdges,'Enable','on');
set(handles.N_AddEdge,'Enable','on');
set(handles.N_RemoveEdge,'Enable','on');
set(handles.N_EdgeNames,'Enable','on');
set(handles.N_CableButton,'Enable','on');
set(handles.N_StrutButton,'Enable','on');
set(handles.N_OriginNode,'Enable','on');
set(handles.N_EndNode,'Enable','on');
set(handles.N_Export,'Enable','on');
set(handles.N_FileName,'Enable','on');
set(handles.CreateNode,'Enable','on');
set(handles.DeleteNode,'Enable','on');
set(handles.CreateEdge,'Enable','on');
set(handles.DeleteEdge,'Enable','on');
% topology from file
set(handles.TopologyBrowse,'Enable','off');
set(handles.ImportTopology,'Enable','off');

if isempty(handles.ten_top)
    handles.ten_top=tensegrity();
end

% Update handles structure
guidata(hObject, handles);

% Hint: get(hObject,'Value') returns toggle state of NewTopologyButton

function TopologyFileName_Callback(hObject, eventdata, handles)
% hObject    handle to TopologyFileName (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of TopologyFileName as text
%        str2double(get(hObject,'String')) returns contents of TopologyFileName as a double

% --- Executes during object creation, after setting all properties.
function TopologyFileName_CreateFcn(hObject, eventdata, handles)
% hObject    handle to TopologyFileName (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end

% --- Executes on button press in TopologyBrowse.
function TopologyBrowse_Callback(hObject, eventdata, handles)
% hObject    handle to TopologyBrowse (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% buscar el fitxer de topologis del tensegrity
[filename,pathname]=uigetfile({'*.ten','Tensegrity topology file (*.ten)'},'Tensegrity topology file');
if filename~=0 
    handles.TensegrityFile=[pathname,filename];
    set(handles.TopologyFileName,'String',filename);    
    guidata(hObject,handles);
end

% --- Executes on button press in ImportTopology.
function ImportTopology_Callback(hObject, eventdata, handles)
% hObject    handle to ImportTopology (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% crear el fitxer
try
    ten_filename=get(handles.TopologyFileName,'String');
    handles.ten_file=tenfile(ten_filename,'r');
    handles.ten_top=tensegrity();
    [handles.ten_top,handles.ten_file]=loadtensegrity(handles.ten_top,handles.ten_file);
    handles.sel_edge=1;
    handles.sel_node=1;
    % actaulitzar la pantalla
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

function RP_Sides_Callback(hObject, eventdata, handles)
% hObject    handle to RP_Sides (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of RP_Sides as text
%        str2double(get(hObject,'String')) returns contents of RP_Sides as a double

% --- Executes during object creation, after setting all properties.
function RP_Sides_CreateFcn(hObject, eventdata, handles)
% hObject    handle to RP_Sides (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end

function RP_Stages_Callback(hObject, eventdata, handles)
% hObject    handle to RP_Stages (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of RP_Stages as text
%        str2double(get(hObject,'String')) returns contents of RP_Stages as a double

% --- Executes during object creation, after setting all properties.
function RP_Stages_CreateFcn(hObject, eventdata, handles)
% hObject    handle to RP_Stages (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end

% --- Executes on button press in RegularPrism.
function RegularPrism_Callback(hObject, eventdata, handles)
% hObject    handle to RegularPrism (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of RegularPrism

% --- Executes on button press in SnelsonX.
function SnelsonX_Callback(hObject, eventdata, handles)
% hObject    handle to SnelsonX (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of SnelsonX

function SX_Rows_Callback(hObject, eventdata, handles)
% hObject    handle to SX_Rows (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of SX_Rows as text
%        str2double(get(hObject,'String')) returns contents of SX_Rows as a double

% --- Executes during object creation, after setting all properties.
function SX_Rows_CreateFcn(hObject, eventdata, handles)
% hObject    handle to SX_Rows (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end

function SX_Columns_Callback(hObject, eventdata, handles)
% hObject    handle to SX_Columns (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of SX_Columns as text
%        str2double(get(hObject,'String')) returns contents of SX_Columns as a double

% --- Executes during object creation, after setting all properties.
function SX_Columns_CreateFcn(hObject, eventdata, handles)
% hObject    handle to SX_Columns (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end

function N_Class_Callback(hObject, eventdata, handles)
% hObject    handle to N_Class (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of N_Class as text
%        str2double(get(hObject,'String')) returns contents of N_Class as a double
try
    class=get(handles.N_Class,'String');
    handles.ten_top.class=uint32(str2num(class));
    UpdateInfo(hObject,handles);
catch
    error=lasterror;    
    errordlg(error.message);
    return;
end
% --- Executes during object creation, after setting all properties.
function N_Class_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N_Class (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end

function N_Dim2_Callback(hObject, eventdata, handles)
% hObject    handle to N_Nodes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of N_Nodes as text
%        str2double(get(hObject,'String')) returns contents of N_Nodes as a double
try
    if get(handles.N_Dim2,'Value')~=get(handles.N_Dim2,'Max')
        set(handles.N_Dim2,'Value',1);
    end
    if get(handles.N_Dim3,'Value')~=get(handles.N_Dim3,'Min')
        set(handles.N_Dim3,'Value',0);
    end
    handles.ten_top.dimension=2;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;    
    errordlg(error.message);
    return;
end

function N_Dim3_Callback(hObject, eventdata, handles)
% hObject    handle to N_Nodes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of N_Nodes as text
%        str2double(get(hObject,'String')) returns contents of N_Nodes as a double
try
    if get(handles.N_Dim2,'Value')~=get(handles.N_Dim2,'Min')
        set(handles.N_Dim2,'Value',0);
    end
    if get(handles.N_Dim3,'Value')~=get(handles.N_Dim3,'Max')
        set(handles.N_Dim3,'Value',1);
    end
    handles.ten_top.dimension=3;
    UpdateInfo(hObject,handles);
catch
    error=lasterror;    
    errordlg(error.message);
    return;
end

function N_Nodes_Callback(hObject, eventdata, handles)
% hObject    handle to N_Nodes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of N_Nodes as text
%        str2double(get(hObject,'String')) returns contents of N_Nodes as a double

% --- Executes on button press in CreateNode.
function CreateNode_Callback(hObject, eventdata, handles)
% hObject    handle to CreateNode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    num_nodes=handles.ten_top.num_nodes;
    for i=1:1:num_nodes+1
        new_node=node(['node',num2str(i)],0,[]);
        try
            handles.ten_top=addnode(handles.ten_top,new_node);
        catch
            error=lasterror;
            if ~strfind(error.message,'tensegrity - Node already present')
                rethrow(lasterror);
            end
        end
    end
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes on button press in DeleteNode.
function DeleteNode_Callback(hObject, eventdata, handles)
% hObject    handle to DeleteNode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    handles.ten_top=removenode(handles.ten_top,handles.sel_node);
    if handles.sel_node>handles.ten_top.num_nodes
        if handles.ten_top.num_nodes>0
            handles.sel_node=handles.ten_top.num_nodes;
        else
            handles.sel_node=1;
        end
    end
    UpdateInfo(hObject,handles);
catch
    error=lasterror;    
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function N_Nodes_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N_Nodes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end

function N_Cables_Callback(hObject, eventdata, handles)
% hObject    handle to N_Cables (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of N_Cables as text
%        str2double(get(hObject,'String')) returns contents of N_Cables as a double

% --- Executes during object creation, after setting all properties.
function N_Cables_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N_Cables (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end

function N_Struts_Callback(hObject, eventdata, handles)
% hObject    handle to N_Struts (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of N_Struts as text
%        str2double(get(hObject,'String')) returns contents of N_Struts as a double

% --- Executes during object creation, after setting all properties.
function N_Struts_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N_Struts (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end

% --- Executes on button press in Generate.
function Generate_Callback(hObject, eventdata, handles)
% hObject    handle to Generate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    if get(handles.RegularPrismButton,'Value')
        handles.ten_top=tensegrity();
        num_sides=str2num(get(handles.RP_Sides,'String'));
        num_stages=str2num(get(handles.RP_Stages,'String'));
        handles.ten_top=generateprism(handles.ten_top,num_sides,num_stages);
    else
        if get(handles.SnelsonXButton,'Value')
            handles.ten_top=tensegrity();
            num_rows=str2num(get(handles.SX_Rows,'String'));
            num_columns=str2num(get(handles.SX_Columns,'String'));
            handles.ten_top=generatesnelsonx(handles.ten_top,num_rows,num_columns);
        else
            handles.ten_top=tensegrity();
            num_nodes=str2num(get(handles.C_NumNodes,'String'));
            handles.ten_top=generatecomplete(handles.ten_top,num_nodes);
        end
    end
    UpdateInfo(hObject,handles);
catch
    error=lasterror;    
    errordlg(error.message);
    return;
end

% --- Executes on selection change in N_NodeNames.
function N_NodeNames_Callback(hObject, eventdata, handles)
% hObject    handle to N_NodeNames (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns N_NodeNames contents as cell array
%        contents{get(hObject,'Value')} returns selected item from N_NodeNames
try
    handles.sel_node=get(handles.N_NodeNames,'Value');
    UpdateInfo(hObject,handles);
catch
    error=lasterror;    
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function N_NodeNames_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N_NodeNames (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end

function N_NumEdges_Callback(hObject, eventdata, handles)
% hObject    handle to N_NumEdges (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of N_NumEdges as text
%        str2double(get(hObject,'String')) returns contents of N_NumEdges as a double

% --- Executes during object creation, after setting all properties.
function N_NumEdges_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N_NumEdges (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end

function N_IncidentEdges_Callback(hObject, eventdata, handles)
% hObject    handle to N_IncidentEdges (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of N_IncidentEdges as text
%        str2double(get(hObject,'String')) returns contents of N_IncidentEdges as a double

% --- Executes during object creation, after setting all properties.
function N_IncidentEdges_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N_IncidentEdges (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end

function N_AllEdges_Callback(hObject, eventdata, handles)
% hObject    handle to N_AllEdges (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of N_AllEdges as text
%        str2double(get(hObject,'String')) returns contents of N_AllEdges as a double

% --- Executes during object creation, after setting all properties.
function N_AllEdges_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N_AllEdges (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end

% --- Executes on button press in N_AddEdge.
function N_AddEdge_Callback(hObject, eventdata, handles)
% hObject    handle to N_AddEdge (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    sel_edge=get(handles.N_AllEdges,'Value');
    edge_list=get(handles.N_AllEdges,'String');
    edge_index=getedgeindex(handles.ten_top,edge_list(sel_edge,:));
    sel_node=get(handles.N_NodeNames,'Value');
    node_list=get(handles.N_NodeNames,'String');
    node_index=getnodeindex(handles.ten_top,node_list(sel_node,:));
    [handles.ten_top.nodes(node_index),handles.ten_top.edges(edge_index)]=addincidentedge(handles.ten_top.nodes(node_index),handles.ten_top.edges(edge_index));
    UpdateInfo(hObject,handles);
catch
    error=lasterror;    
    errordlg(error.message);
    return;
end

% --- Executes on button press in N_RemoveEdge.
function N_RemoveEdge_Callback(hObject, eventdata, handles)
% hObject    handle to N_RemoveEdge (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    sel_edge=get(handles.N_IncidentEdges,'Value');
    edge_list=get(handles.N_IncidentEdges,'String');
    edge_index=getedgeindex(handles.ten_top,edge_list(sel_edge,:));
    sel_node=get(handles.N_NodeNames,'Value');
    node_list=get(handles.N_NodeNames,'String');
    node_index=getnodeindex(handles.ten_top,node_list(sel_node,:));
    [handles.ten_top.nodes(node_index),handles.ten_top.edges(edge_index)]=removeincidentedge(handles.ten_top.nodes(node_index),handles.ten_top.edges(edge_index));
    UpdateInfo(hObject,handles);
catch
    error=lasterror;    
    errordlg(error.message);
    return;
end

% --- Executes on selection change in N_EdgeNames.
function N_EdgeNames_Callback(hObject, eventdata, handles)
% hObject    handle to N_EdgeNames (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns N_EdgeNames contents as cell array
%        contents{get(hObject,'Value')} returns selected item from N_EdgeNames
try
    handles.sel_edge=get(handles.N_EdgeNames,'Value');
    UpdateInfo(hObject,handles);
catch
    error=lasterror;    
    errordlg(error.message);
    return;
end

% --- Executes during object creation, after setting all properties.
function N_EdgeNames_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N_EdgeNames (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end

% --- Executes on button press in CreateEdge.
function CreateEdge_Callback(hObject, eventdata, handles)
% hObject    handle to CreateEdge (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    num_edges=handles.ten_top.num_edges;
    for i=1:1:num_edges+1
        try
            handles.ten_top=addedge(handles.ten_top,edge(['edge',num2str(i)],'cable','none','none'));
        catch
            error=lasterror;
            if ~strfind(error.message,'tensegrity - Edge already present')
                rethrow(lasterror);
            end
        end
    end
    UpdateInfo(hObject,handles);
catch
    error=lasterror;    
    errordlg(error.message);
    return;
end

% --- Executes on button press in DeleteEdge.
function DeleteEdge_Callback(hObject, eventdata, handles)
% hObject    handle to DeleteEdge (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    handles.ten_top=removeedge(handles.ten_top,handles.sel_edge);
    if handles.sel_edge>handles.ten_top.num_edges
        if handles.ten_top.num_edges>0
            handles.sel_edge=handles.ten_top.num_edges;
        else
            handles.sel_edge=1;
        end
    end
    UpdateInfo(hObject,handles);
catch
    error=lasterror;    
    errordlg(error.message);
    return;
end

% --- Executes on button press in N_CableButton.
function N_CableButton_Callback(hObject, eventdata, handles)
% hObject    handle to N_CableButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of N_CableButton
try
    [handles.ten_top,handles.ten_top.edges(handles.sel_node)]=changeedgetype(handles.ten_top,handles.ten_top.edges(handles.sel_node),'cable');
    UpdateInfo(hObject,handles);
catch
    error=lasterror;    
    errordlg(error.message);
    return;
end

% --- Executes on button press in N_StrutButton.
function N_StrutButton_Callback(hObject, eventdata, handles)
% hObject    handle to N_StrutButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hint: get(hObject,'Value') returns toggle state of N_StrutButton
try
    [handles.ten_top,handles.ten_top.edges(handles.sel_node)]=changeedgetype(handles.ten_top,handles.ten_top.edges(handles.sel_node),'strut');
    UpdateInfo(hObject,handles);
catch
    error=lasterror;
    errordlg(error.message);
    return;
end

% --- Executes on selection change in N_OriginNode.
function N_OriginNode_Callback(hObject, eventdata, handles)
% hObject    handle to N_OriginNode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns N_OriginNode contents as cell array
%        contents{get(hObject,'Value')} returns selected item from N_OriginNode

% --- Executes during object creation, after setting all properties.
function N_OriginNode_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N_OriginNode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end

% --- Executes on selection change in N_EndNode.
function N_EndNode_Callback(hObject, eventdata, handles)
% hObject    handle to N_EndNode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns N_EndNode contents as cell array
%        contents{get(hObject,'Value')} returns selected item from N_EndNode

% --- Executes during object creation, after setting all properties.
function N_EndNode_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N_EndNode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end

function N_FileName_Callback(hObject, eventdata, handles)
% hObject    handle to N_FileName (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of N_FileName as text
%        str2double(get(hObject,'String')) returns contents of N_FileName as a double

% --- Executes during object creation, after setting all properties.
function N_FileName_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N_FileName (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in N_Export.
function N_Export_Callback(hObject, eventdata, handles)
% hObject    handle to N_Export (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    filename=get(handles.N_FileName,'String');
    if ~isempty(filename)
        if isempty(strfind(filename,'.ten'))
            filename=[filename,'.ten'];
        end
        savetensegrity(handles.ten_top,filename);
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

% --- Executes on button press in ConnMatrix.
function ConnMatrix_Callback(hObject, eventdata, handles)
% hObject    handle to ConnMatrix (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
try
    connmatrix=genconnmatrix(handles.ten_top);
    connmatrix
catch
    error=lasterror;    
    errordlg(error.message);
    return;
end

function C_NumNodes_Callback(hObject, eventdata, handles)
% hObject    handle to C_NumNodes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of C_NumNodes as text
%        str2double(get(hObject,'String')) returns contents of C_NumNodes as a double

% --- Executes during object creation, after setting all properties.
function C_NumNodes_CreateFcn(hObject, eventdata, handles)
% hObject    handle to C_NumNodes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% funcion propies
function UpdateInfo(hObject,handles)

try
    dim=handles.ten_top.dimension;
    tensegrity=handles.ten_top;
    if dim==2
        if get(handles.N_Dim2,'Value')~=get(handles.N_Dim2,'Max')
            set(handles.N_Dim2,'Value',1);
        end
        if get(handles.N_Dim3,'Value')~=get(handles.N_Dim3,'Min')
            set(handles.N_Dim3,'Value',0);
        end
    else
        if get(handles.N_Dim2,'Value')~=get(handles.N_Dim2,'Min')
            set(handles.N_Dim2,'Value',0);
        end
        if get(handles.N_Dim3,'Value')~=get(handles.N_Dim3,'Max')
            set(handles.N_Dim3,'Value',1);
        end
    end
    set(handles.N_Class,'String',tensegrity.class);
    set(handles.N_Nodes,'String',tensegrity.num_nodes);
    set(handles.N_Struts,'String',tensegrity.num_struts);
    set(handles.N_Cables,'String',tensegrity.num_cables);
    % omplir la llista de nodes
    if tensegrity.num_nodes>0
        node_names='';
    else
        node_names='none';
    end
    nodes=tensegrity.nodes;
    for i=1:1:tensegrity.num_nodes
        node_names=strvcat(node_names,nodes(i).name);
    end
    % carregar la llista dels nodes
    set(handles.N_NodeNames,'String',node_names);
    node_names=strvcat('none',node_names);
    set(handles.N_OriginNode,'String',node_names);
    set(handles.N_EndNode,'String',node_names);
    set(handles.N_NodeNames,'Value',handles.sel_node);
    % omplir la llista d'arestes
    if tensegrity.num_edges>0
        edge_names='';
    else
        edge_names='none';
    end
    edges=tensegrity.edges;
    for i=1:1:tensegrity.num_edges
        edge_names=strvcat(edge_names,edges(i).name);
    end
    % carregar la llista dels nodes
    set(handles.N_EdgeNames,'String',edge_names);
    set(handles.N_EdgeNames,'Value',handles.sel_edge);
    % omplir la configuraci� del node seleccionat
    if tensegrity.num_nodes>0
        set(handles.N_NumEdges,'String',num2str(tensegrity.nodes(handles.sel_node).num_edges));
        % llista de les arestes incidents
        names='';
        for i=1:1:tensegrity.nodes(handles.sel_node).num_edges
            names=strvcat(names,tensegrity.nodes(handles.sel_node).inc_edges(i).name);
        end
        set(handles.N_IncidentEdges,'String',names);
        set(handles.N_IncidentEdges,'Value',1);
    else
        set(handles.N_NumEdges,'String',num2str(0));
        set(handles.N_IncidentEdges,'String',[]);
        set(handles.N_IncidentEdges,'Value',1);
    end
    % llista de totes les arestes disponibles
    edge_names='';
    for i=1:1:tensegrity.num_edges
        if strcmp(tensegrity.edges(i).origin,'none') || strcmp(tensegrity.edges(i).end,'none')
            edge_names=strvcat(edge_names,tensegrity.edges(i).name);
        end
    end
    set(handles.N_AllEdges,'String',edge_names);
    set(handles.N_AllEdges,'Value',1);
    % omplir la configuraci� de l'aresta seleccionada
    if tensegrity.num_edges>0
        if strcmp(tensegrity.edges(handles.sel_edge).type,'cable')
            set(handles.N_CableButton,'value',1);
            set(handles.N_StrutButton,'value',0);
        else
            set(handles.N_CableButton,'value',0);
            set(handles.N_StrutButton,'value',1);
        end
        % node d'origen
        set(handles.N_OriginNode,'Value',1);
        set(handles.N_EndNode,'Value',1);
        for i=1:1:tensegrity.num_nodes
            if strcmp(tensegrity.edges(handles.sel_edge).origin,tensegrity.nodes(i).name)
                set(handles.N_OriginNode,'Value',i+1);
            else
                if strcmp(tensegrity.edges(handles.sel_edge).end,tensegrity.nodes(i).name)
                    set(handles.N_EndNode,'Value',i+1);
                end
            end
        end
    else
        set(handles.N_OriginNode,'Value',1);
        set(handles.N_EndNode,'Value',1);
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
uiresume(handles.Topology);

