/***************************************************************
 * Name:      CoolEditorMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    prof hilary (profesorhilary@outlook.com)
 * Created:   2024-07-14
 * Copyright: prof hilary ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "CoolEditorMain.h"
#include <wx/msgdlg.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/regex.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/sstream.h>

#include <wx/imaglist.h>
#include <wx/artprov.h>

//(*InternalHeaders(CoolEditorFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f
};

enum {
    ID_OPEN = 1,
    ID_SAVE,
    ID_PRINT,
    ID_EXIT
};

wxString wxbuildinfo( wxbuildinfoformat format ) {
    wxString wxbuild( wxVERSION_STRING );

    if ( format == long_f ) {
        #if defined(__WXMSW__)
        wxbuild << _T( "-Windows" );
        #elif defined(__UNIX__)
        wxbuild << _T( "-Linux" );
        #endif

        #if wxUSE_UNICODE
        wxbuild << _T( "-Unicode build" );
        #else
        wxbuild << _T( "-ANSI build" );
        #endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(CoolEditorFrame)
const long CoolEditorFrame::ID_TEXTCTRL1 = wxNewId();
const long CoolEditorFrame::ID_AUINOTEBOOK3 = wxNewId();
const long CoolEditorFrame::ID_PANEL_HOME = wxNewId();
const long CoolEditorFrame::ID_PANEL_EDIT = wxNewId();
const long CoolEditorFrame::ID_PANEL_VIEW = wxNewId();
const long CoolEditorFrame::ID_PANEL_LAYOUT = wxNewId();
const long CoolEditorFrame::ID_PANEL_PROJECT = wxNewId();
const long CoolEditorFrame::ID_PANEL_BUILD = wxNewId();
const long CoolEditorFrame::ID_PANEL_DEBUG = wxNewId();
const long CoolEditorFrame::ID_PANEL_EDITOR = wxNewId();
const long CoolEditorFrame::ID_PANEL_SETTING = wxNewId();
const long CoolEditorFrame::ID_PANEL_HELP = wxNewId();
const long CoolEditorFrame::ID_AUINOTEBOOK4 = wxNewId();
const long CoolEditorFrame::ID_DIRPICKERCTRL1 = wxNewId();
const long CoolEditorFrame::ID_TREECTRL_FILELIST = wxNewId();
const long CoolEditorFrame::ID_PANEL2 = wxNewId();
const long CoolEditorFrame::ID_AUINOTEBOOK2 = wxNewId();
const long CoolEditorFrame::ID_AUINOTEBOOK1 = wxNewId();
const long CoolEditorFrame::ID_PANEL1 = wxNewId();
const long CoolEditorFrame::ID_AUINOTEBOOK5 = wxNewId();
const long CoolEditorFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE( CoolEditorFrame, wxFrame )
    //(*EventTable(CoolEditorFrame)
    //*)
    EVT_BUTTON( ID_OPEN, CoolEditorFrame::OnOpen )
    EVT_BUTTON( ID_SAVE, CoolEditorFrame::OnSave )
    EVT_BUTTON( ID_PRINT, CoolEditorFrame::OnPrint )
    EVT_BUTTON( ID_EXIT, CoolEditorFrame::OnExit )
END_EVENT_TABLE()

CoolEditorFrame::CoolEditorFrame( wxWindow* parent, wxWindowID id ) {
    //(*Initialize(CoolEditorFrame)
    wxBoxSizer* BoxSizer1;

    Create( parent, wxID_ANY, _( "Kreyna" ), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE | wxSYSTEM_MENU | wxMAXIMIZE_BOX | wxMINIMIZE_BOX, _T( "wxID_ANY" ) );
    SetClientSize( wxSize( 980, 500 ) );
    ParentAuiManager = new wxAuiManager( this, wxAUI_MGR_DEFAULT );
    AuiNotebookConsolePane = new wxAuiNotebook( this, ID_AUINOTEBOOK3, wxDefaultPosition, wxSize( 0, 300 ), wxAUI_NB_WINDOWLIST_BUTTON );
    controlTextCtrl = new wxTextCtrl( AuiNotebookConsolePane, ID_TEXTCTRL1, _( "PS C:\\Users\\home> " ), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_AUTO_URL | wxTE_CHARWRAP | wxBORDER_NONE, wxDefaultValidator, _T( "ID_TEXTCTRL1" ) );
    AuiNotebookConsolePane->AddPage( controlTextCtrl, _( "Console" ) );
    ParentAuiManager->AddPane( AuiNotebookConsolePane, wxAuiPaneInfo().Name( _T( "ConsolePane" ) ).DefaultPane().Caption( _( "Logs" ) ).CaptionVisible().MinimizeButton().Position( 1 ).Bottom().TopDockable( false ).BestSize( wxSize( 0, 300 ) ).DestroyOnClose() );
    AuiNotebookToolBar = new wxAuiNotebook( this, ID_AUINOTEBOOK4, wxDefaultPosition, wxSize( 0, 150 ), wxAUI_NB_WINDOWLIST_BUTTON | wxBORDER_NONE | wxCLIP_CHILDREN | wxFULL_REPAINT_ON_RESIZE );
    PanelHome = new wxPanel( AuiNotebookToolBar, ID_PANEL_HOME, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxCLIP_CHILDREN, _T( "ID_PANEL_HOME" ) );
    PanelEdit = new wxPanel( AuiNotebookToolBar, ID_PANEL_EDIT, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T( "ID_PANEL_EDIT" ) );
    PanelView = new wxPanel( AuiNotebookToolBar, ID_PANEL_VIEW, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T( "ID_PANEL_VIEW" ) );
    PanelLayout = new wxPanel( AuiNotebookToolBar, ID_PANEL_LAYOUT, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T( "ID_PANEL_LAYOUT" ) );
    PanelProject = new wxPanel( AuiNotebookToolBar, ID_PANEL_PROJECT, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T( "ID_PANEL_PROJECT" ) );
    PanelBuild = new wxPanel( AuiNotebookToolBar, ID_PANEL_BUILD, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T( "ID_PANEL_BUILD" ) );
    PanelDebug = new wxPanel( AuiNotebookToolBar, ID_PANEL_DEBUG, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T( "ID_PANEL_DEBUG" ) );
    PanelEditor = new wxPanel( AuiNotebookToolBar, ID_PANEL_EDITOR, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T( "ID_PANEL_EDITOR" ) );
    PanelSetting = new wxPanel( AuiNotebookToolBar, ID_PANEL_SETTING, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T( "ID_PANEL_SETTING" ) );
    PanelHelp = new wxPanel( AuiNotebookToolBar, ID_PANEL_HELP, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T( "ID_PANEL_HELP" ) );
    AuiNotebookToolBar->AddPage( PanelHome, _( "Home" ), true );
    AuiNotebookToolBar->AddPage( PanelEdit, _( "Edit" ) );
    AuiNotebookToolBar->AddPage( PanelView, _( "View" ) );
    AuiNotebookToolBar->AddPage( PanelLayout, _( "Layout" ) );
    AuiNotebookToolBar->AddPage( PanelProject, _( "Project" ) );
    AuiNotebookToolBar->AddPage( PanelBuild, _( "Build" ) );
    AuiNotebookToolBar->AddPage( PanelDebug, _( "Debug" ) );
    AuiNotebookToolBar->AddPage( PanelEditor, _( "Editor" ) );
    AuiNotebookToolBar->AddPage( PanelSetting, _( "Settings" ) );
    AuiNotebookToolBar->AddPage( PanelHelp, _( "Help" ) );
    ParentAuiManager->AddPane( AuiNotebookToolBar, wxAuiPaneInfo().Name( _T( "ToolBar" ) ).DefaultPane().Caption( _( "Tool Bar" ) ).CaptionVisible( false ).PinButton().Layer( 1 ).Top().DockFixed().BestSize( wxSize( 0, 150 ) ) );
    AuiNotebookManagement = new wxAuiNotebook( this, ID_AUINOTEBOOK2, wxDefaultPosition, wxSize( 300, 0 ), wxAUI_NB_SCROLL_BUTTONS | wxAUI_NB_WINDOWLIST_BUTTON );
    Panel2 = new wxPanel( AuiNotebookManagement, ID_PANEL2, wxPoint( -3, -50 ), wxDefaultSize, wxTAB_TRAVERSAL, _T( "ID_PANEL2" ) );
    BoxSizer1 = new wxBoxSizer( wxVERTICAL );
    DirPickerCtrl1 = new wxDirPickerCtrl( Panel2, ID_DIRPICKERCTRL1, _T( "C:\\Users\\home\\Documents" ), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST | wxDIRP_USE_TEXTCTRL | wxDIRP_SMALL, wxDefaultValidator, _T( "ID_DIRPICKERCTRL1" ) );
    BoxSizer1->Add( DirPickerCtrl1, 0, wxALL | wxEXPAND, 5 );
    treeCtrl = new wxTreeCtrl( Panel2, ID_TREECTRL_FILELIST, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS | wxTR_TWIST_BUTTONS | wxTR_LINES_AT_ROOT | wxTR_DEFAULT_STYLE, wxDefaultValidator, _T( "ID_TREECTRL_FILELIST" ) );
    BoxSizer1->Add( treeCtrl, 1, wxALL | wxEXPAND, 5 );
    Panel2->SetSizer( BoxSizer1 );
    BoxSizer1->Fit( Panel2 );
    BoxSizer1->SetSizeHints( Panel2 );
    AuiNotebookManagement->AddPage( Panel2, _( "Files" ) );
    ParentAuiManager->AddPane( AuiNotebookManagement, wxAuiPaneInfo().Name( _T( "LeftPane" ) ).DefaultPane().Caption( _( "Management" ) ).CaptionVisible().Layer( 1 ).Left().TopDockable( false ).BestSize( wxSize( 300, 0 ) ) );
    AuiNotebookEditors = new wxAuiNotebook( this, ID_AUINOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxAUI_NB_SCROLL_BUTTONS | wxAUI_NB_WINDOWLIST_BUTTON | wxAUI_NB_DEFAULT_STYLE );
    ParentAuiManager->AddPane( AuiNotebookEditors, wxAuiPaneInfo().Name( _T( "MainViewPane" ) ).DefaultPane().Caption( _( "Editors" ) ).CaptionVisible().MinimizeButton().MaximizeButton().CloseButton( false ).Center().DockFixed().TopDockable( false ).DestroyOnClose() );
    AuiNotebookAside = new wxAuiNotebook( this, ID_AUINOTEBOOK5, wxDefaultPosition, wxSize( 300, 0 ), wxAUI_NB_WINDOWLIST_BUTTON | wxFULL_REPAINT_ON_RESIZE );
    Panel1 = new wxPanel( AuiNotebookAside, ID_PANEL1, wxPoint( 19, 270 ), wxDefaultSize, wxTAB_TRAVERSAL, _T( "ID_PANEL1" ) );
    AuiNotebookAside->AddPage( Panel1, _( "Aside" ) );
    ParentAuiManager->AddPane( AuiNotebookAside, wxAuiPaneInfo().Name( _T( "Aside" ) ).DefaultPane().Caption( _( "Side Pane" ) ).CaptionVisible().MinimizeButton().MaximizeButton().PinButton().CloseButton( false ).Right().TopDockable( false ).BestSize( wxSize( 300, 0 ) ) );
    ParentAuiManager->Update();
    StatusBar1 = new wxStatusBar( this, ID_STATUSBAR1, 0, _T( "ID_STATUSBAR1" ) );
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount( 1, __wxStatusBarWidths_1 );
    StatusBar1->SetStatusStyles( 1, __wxStatusBarStyles_1 );
    SetStatusBar( StatusBar1 );
    Center();

    Connect( ID_DIRPICKERCTRL1, wxEVT_COMMAND_DIRPICKER_CHANGED, ( wxObjectEventFunction )&CoolEditorFrame::OnDirPickerCtrlDirChanged );
    //*)

    // Set the initial size and position
    SetSize( wxGetClientDisplayRect() ); // Optional: Set size to the full screen size

    // Show the frame maximized
    Show( true );
    Maximize( true );

    fileNames = std::vector<wxString> {
        wxString( "CoolEditorMain.cpp" ),
        wxString( "CoolEditorMain.h" ),
        wxString( "CoolEditorApp.h" ),
        wxString( "CoolEditorApp.cpp" ),
        wxString( "wx_pch.h" )
    };
    int fileIndex = 0;

    for ( auto file = fileNames.begin(); file != fileNames.end(); file++ ) {
        stc = new wxStyledTextCtrl( AuiNotebookEditors, 10000 + ( fileIndex++ ), wxDefaultPosition, wxSize( -1, -1 ), 0 );
        setCppStyling( *file );
    }

    // Bind the Enter key event to the handler
    Bind( wxEVT_TEXT_ENTER, &CoolEditorFrame::OncontrolTextCtrlTextEnter, this );
    // Bind the TextUpdated event to handle text changes
    Bind( wxEVT_TEXT, &CoolEditorFrame::OnTextChange, this, controlTextCtrl->GetId() );

    // Set the default directory path (current working directory or any specific path)
    wxString defaultPath = wxGetCwd(); // Gets the current working directory
    // Simulate a directory picker event with the default path
    SimulateDirChangeEvent( defaultPath );


    CreateRibbonToolbar();
}

void CoolEditorFrame::CreateRibbonToolbar() {
    //////////////////////////////////////////////////////// File Ribon //////////////////////////////////////////////////////////
    // Create a box sizer to arrange buttons horizontally
    wxBoxSizer* fileSizer = new wxBoxSizer( wxHORIZONTAL );

    // Create a vertical sizer for each button and its label
    wxBoxSizer* openSizer = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer* saveSizer = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer* printSizer = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer* exitSizer = new wxBoxSizer( wxVERTICAL );

    // Load bitmap images for the buttons
    wxBitmap openBitmap( wxT( "open.png" ), wxBITMAP_TYPE_PNG );
    wxBitmap saveBitmap( wxT( "save.png" ), wxBITMAP_TYPE_PNG );
    wxBitmap printBitmap( wxT( "print.png" ), wxBITMAP_TYPE_PNG );
    wxBitmap exitBitmap( wxT( "exit.png" ), wxBITMAP_TYPE_PNG );

    // Create bitmap buttons for the "File" tab commands
    wxBitmapButton* openButton = new wxBitmapButton( PanelHome, ID_OPEN, openBitmap );
    wxBitmapButton* saveButton = new wxBitmapButton( PanelHome, ID_SAVE, saveBitmap );
    wxBitmapButton* printButton = new wxBitmapButton( PanelHome, ID_PRINT, printBitmap );
    wxBitmapButton* exitButton = new wxBitmapButton( PanelHome, ID_EXIT, exitBitmap );

    // Add buttons and labels to the vertical sizers
    openSizer->Add( openButton, 0, wxALL, 5 );
    openSizer->Add( new wxStaticText( PanelHome, wxID_ANY, wxT( "Open" ) ), 0, wxALIGN_CENTER );

    saveSizer->Add( saveButton, 0, wxALL, 5 );
    saveSizer->Add( new wxStaticText( PanelHome, wxID_ANY, wxT( "Save" ) ), 0, wxALIGN_CENTER );

    printSizer->Add( printButton, 0, wxALL, 5 );
    printSizer->Add( new wxStaticText( PanelHome, wxID_ANY, wxT( "Print" ) ), 0, wxALIGN_CENTER );

    exitSizer->Add( exitButton, 0, wxALL, 5 );
    exitSizer->Add( new wxStaticText( PanelHome, wxID_ANY, wxT( "Exit" ) ), 0, wxALIGN_CENTER );

    // Add vertical sizers to the main horizontal sizer
    fileSizer->Add( openSizer, 0, wxALL, 5 );
    fileSizer->Add( saveSizer, 0, wxALL, 5 );
    fileSizer->Add( printSizer, 0, wxALL, 5 );
    fileSizer->Add( exitSizer, 0, wxALL, 5 );

    // Set the sizer for the panel
    PanelHome->SetSizer( fileSizer );

    //////////////////////////////////////////////////////// Debug Ribon //////////////////////////////////////////////////////////
    // Create a box sizer to arrange buttons horizontally
    wxBoxSizer* debugSizer = new wxBoxSizer( wxHORIZONTAL );

    // Create a vertical sizer for each button and its label
    wxBoxSizer* openSizer = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer* saveSizer = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer* printSizer = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer* exitSizer = new wxBoxSizer( wxVERTICAL );

    // Load bitmap images for the buttons
    wxBitmap openBitmap( wxT( "open.png" ), wxBITMAP_TYPE_PNG );
    wxBitmap saveBitmap( wxT( "save.png" ), wxBITMAP_TYPE_PNG );
    wxBitmap printBitmap( wxT( "print.png" ), wxBITMAP_TYPE_PNG );
    wxBitmap exitBitmap( wxT( "exit.png" ), wxBITMAP_TYPE_PNG );

    // Create bitmap buttons for the "File" tab commands
    wxBitmapButton* openButton = new wxBitmapButton( PanelHome, ID_OPEN, openBitmap );
    wxBitmapButton* saveButton = new wxBitmapButton( PanelHome, ID_SAVE, saveBitmap );
    wxBitmapButton* printButton = new wxBitmapButton( PanelHome, ID_PRINT, printBitmap );
    wxBitmapButton* exitButton = new wxBitmapButton( PanelHome, ID_EXIT, exitBitmap );

    // Add buttons and labels to the vertical sizers
    openSizer->Add( openButton, 0, wxALL, 5 );
    openSizer->Add( new wxStaticText( PanelHome, wxID_ANY, wxT( "Open" ) ), 0, wxALIGN_CENTER );

    saveSizer->Add( saveButton, 0, wxALL, 5 );
    saveSizer->Add( new wxStaticText( PanelHome, wxID_ANY, wxT( "Save" ) ), 0, wxALIGN_CENTER );

    printSizer->Add( printButton, 0, wxALL, 5 );
    printSizer->Add( new wxStaticText( PanelHome, wxID_ANY, wxT( "Print" ) ), 0, wxALIGN_CENTER );

    exitSizer->Add( exitButton, 0, wxALL, 5 );
    exitSizer->Add( new wxStaticText( PanelHome, wxID_ANY, wxT( "Exit" ) ), 0, wxALIGN_CENTER );

    // Add vertical sizers to the main horizontal sizer
    debugSizer->Add( openSizer, 0, wxALL, 5 );
    debugSizer->Add( saveSizer, 0, wxALL, 5 );
    debugSizer->Add( printSizer, 0, wxALL, 5 );
    debugSizer->Add( exitSizer, 0, wxALL, 5 );

    // Set the sizer for the panel
    PanelHome->SetSizer( debugSizer );
}

void CoolEditorFrame::SimulateDirChangeEvent( const wxString& path ) {
    // Get the selected path from the DirPickerCtrl
    wxString selectedPath = path;

    // Clear existing items from the tree
    treeCtrl->DeleteAllItems();

    // Create an image list and add folder and file icons
    wxImageList* imageList = new wxImageList( 16, 16, true, 2 );
    wxIcon folderIcon;
    wxIcon fileIcon;

    wxBitmap folderBitmap = wxArtProvider::GetBitmap( wxART_FOLDER, wxART_OTHER, wxSize( 16, 16 ) );
    wxBitmap fileBitmap = wxArtProvider::GetBitmap( wxART_NORMAL_FILE, wxART_OTHER, wxSize( 16, 16 ) );

    folderIcon.CopyFromBitmap( folderBitmap );
    fileIcon.CopyFromBitmap( fileBitmap );

    imageList->Add( folderIcon );
    imageList->Add( fileIcon );

    // Associate the image list with the tree control
    treeCtrl->AssignImageList( imageList );

    // Add the root item with the selected path
    wxTreeItemId root = treeCtrl->AddRoot( selectedPath, 0 ); // Folder icon for root

    // Declare the recursive lambda function before use
    std::function<void( const wxString&, wxTreeItemId )> PopulateSubdirectories;
    PopulateSubdirectories = [&]( const wxString & path, wxTreeItemId parent ) {
        wxDir dir( path );

        if ( dir.IsOpened() ) {
            wxString filename;
            bool cont = dir.GetFirst( &filename );

            while ( cont ) {
                if ( filename != "." && filename != ".." ) {
                    wxString filepath = wxFileName::DirName( path ).GetFullPath() + wxFileName::GetPathSeparator() + filename;

                    if ( wxDirExists( filepath ) ) {
                        wxTreeItemId child = treeCtrl->AppendItem( parent, filename, 0 ); // Folder icon
                        PopulateSubdirectories( filepath, child ); // Recursively add subdirectories
                    } else {
                        treeCtrl->AppendItem( parent, filename, 1 ); // File icon
                    }
                }

                cont = dir.GetNext( &filename );
            }
        }
    };

    // Call the recursive function to populate the tree
    PopulateSubdirectories( selectedPath, root );
    treeCtrl->Expand( root );
}

void CoolEditorFrame::setCppStyling( wxString fileName ) {
    // Constants for colors and font
    const wxColour CARET_LINE_BG_COLOR( 27, 64, 66 );
    const wxColour MARGIN_BG_COLOR( 250, 0, 0 );
    const wxColour EDGE_COLOR( 90, 90, 90 );
    const wxColour BACKGROUND_COLOR( 37, 44, 46 );
    const wxColour SELECTION_BG_COLOR( 60, 60, 60 );
    const wxColour SELECTION_FG_COLOR( 255, 255, 255 );
    const wxFont FONT( 10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier New" );

    // Set the lexer for C++
    stc->SetLexer( wxSTC_LEX_CPP );

    // Set custom C++ keywords and types
    const char* keywords =
        "alignas alignof and and_eq asm auto bitand bitor bool break case catch char char16_t char32_t "
        "class compl const constexpr const_cast continue decltype default delete do double dynamic_cast "
        "else enum explicit export extern false float for friend goto if inline int long mutable namespace "
        "new noexcept not not_eq nullptr operator or or_eq private protected public register reinterpret_cast "
        "return short signed sizeof static static_assert static_cast struct switch template this thread_local "
        "throw true try typedef typeid typename union unsigned using virtual void volatile wchar_t while xor xor_eq";

    const char* types =
        "int long short char bool float double void wchar_t char16_t char32_t unsigned signed";

    stc->SetKeyWords( 0, keywords );
    stc->SetKeyWords( 1, types );

    // Set the background color for whitespace characters
    stc->SetWhitespaceBackground( true, wxColour( 37, 44, 46 ) ); // Background color to match editor's background

    // Optionally set the foreground color for whitespace characters if needed
    stc->SetWhitespaceForeground( true, wxColour( 37, 44, 46 ) ); // Matching foreground color

    // Default Settings
    stc->SetCaretLineVisible( true );
    stc->SetCaretLineBackground( wxColour( 27, 64, 66 ) );

    // Set up margins
    stc->SetMargins( 1, 0 ); // Set the margin width (1 unit for line numbers, 0 units for additional margins)

    // Configure margin 0 (line number margin)
    stc->SetMarginType( 0, wxSTC_MARGIN_NUMBER ); // Set margin type to number
    stc->SetMarginWidth( 0, 50 ); // Set margin width (adjust as needed)

    // Set margin background color
    stc->SetMarginBackground( 0, wxColour( 0, 0, 0 ) ); // Black background for the margin

    // Optional: Set margin font
    wxFont marginFont = wxFont( 10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, _T( "Courier New" ), wxFONTENCODING_DEFAULT );
    stc->StyleSetFont( wxSTC_STYLE_LINENUMBER, marginFont );

    stc->StyleSetForeground( wxSTC_STYLE_LINENUMBER, wxColour( 255, 255, 255 ) ); // White text color for line numbers
    stc->StyleSetBackground( wxSTC_STYLE_LINENUMBER, wxColour( 0, 0, 0 ) ); // Black background for line numbers

    // Add the editor to the notebook
    AuiNotebookEditors->AddPage( stc, fileName );

    // Clear previous styles and set default font
    stc->StyleClearAll();
    stc->StyleSetFont( wxSTC_STYLE_DEFAULT, FONT );

    // Background settings
    stc->StyleSetBackground( wxSTC_STYLE_DEFAULT, BACKGROUND_COLOR );
    stc->StyleSetBackground( wxSTC_CHARSET_DEFAULT, BACKGROUND_COLOR );
    stc->SetSelBackground( true, SELECTION_BG_COLOR );
    stc->SetSelForeground( true, SELECTION_FG_COLOR );

    // General styling settings
    stc->SetViewWhiteSpace( wxSTC_WS_VISIBLEALWAYS );
    stc->SetViewEOL( false );
    stc->SetWhitespaceBackground( true, BACKGROUND_COLOR );
    stc->SetWhitespaceForeground( true, BACKGROUND_COLOR );
    stc->StyleSetForeground( wxSTC_C_DEFAULT, BACKGROUND_COLOR );

    // Styling for different elements
    auto setStyle = [this, &FONT, &BACKGROUND_COLOR]( int style, const wxColour & fg, bool bold = false, bool italic = false ) {
        stc->StyleSetFont( style, FONT );
        stc->StyleSetForeground( style, fg );
        stc->StyleSetBackground( style, BACKGROUND_COLOR );
        stc->StyleSetBold( style, bold );
        stc->StyleSetItalic( style, italic );
    };

    setStyle( wxSTC_C_DEFAULT, wxColour( 240, 240, 240 ) );          // Default - Soft White
    setStyle( wxSTC_C_COMMENT, wxColour( 134, 39, 34 ), false, true ); // Comments - Deep Green, Italic
    setStyle( wxSTC_C_COMMENTLINE, wxColour( 60, 79, 113 ), false, true ); // Comment lines - Lighter Green, Italic
    setStyle( wxSTC_C_COMMENTDOC, wxColour( 246, 19, 87 ), false, true ); // Documentation comments - Different Green, Italic
    setStyle( wxSTC_C_NUMBER, wxColour( 255, 165, 0 ) );             // Numbers - Orange-Yellow
    setStyle( wxSTC_C_STRING, wxColour( 255, 165, 0 ), false, true ); // Strings - Orange, Italic
    setStyle( wxSTC_C_CHARACTER, wxColour( 255, 165, 0 ), false, true ); // Characters - Orange, Italic
    setStyle( wxSTC_C_WORD, wxColour( 0, 122, 124 ), true );         // Keywords - Soft Blue
    setStyle( wxSTC_C_WORD2, wxColour( 128, 0, 128 ) );              // Classes, types - Classic Purple
    setStyle( wxSTC_C_OPERATOR, wxColour( 255, 215, 0 ), true );     // Operators - Gold
    setStyle( wxSTC_C_PREPROCESSOR, wxColour( 135, 206, 250 ) );     // Preprocessor - Light Blue
    setStyle( wxSTC_C_IDENTIFIER, wxColour( 240, 240, 240 ) );       // Identifiers - Soft White
    setStyle( wxSTC_C_UUID, wxColour( 0, 191, 255 ) );               // UUID - Sky Blue
    setStyle( wxSTC_C_HASHQUOTEDSTRING, wxColour( 135, 206, 250 ) ); // Preprocessor quoted strings - Light Blue
    setStyle( wxSTC_C_ESCAPESEQUENCE, wxColour( 0, 255, 127 ) );     // Escape sequences - Bright Green

    // Load the file into the editor
    stc->LoadFile( fileName );

    // Connect event handlers
    stc->Bind( wxEVT_STC_UPDATEUI, &CoolEditorFrame::OnUpdateUI, this );
}

void CoolEditorFrame::OnUpdateUI( wxStyledTextEvent& event ) {
    // Regular expression to match function declarations
    wxRegEx reFunction( "\\b([a-zA-Z_][a-zA-Z0-9_]*\\s*\\([^)]*\\))" );

    // Get the entire text from the editor
    wxString text = stc->GetText();

    // Use the regular expression to find function declarations
    size_t start = 0;

    while ( reFunction.Matches( text.substr( start ) ) ) {
        size_t startPos, endPos;
        reFunction.GetMatch( &startPos, &endPos, 0 );

        // Adjust positions relative to the entire text
        startPos += start;
        endPos += start;

        // Apply custom styling to the matched function declaration
        stc->StartStyling( startPos );
        stc->SetStyling( endPos - startPos, wxSTC_STYLE_CALLTIP );

        start = endPos;
    }
}

CoolEditorFrame::~CoolEditorFrame() {
    //(*Destroy(CoolEditorFrame)
    //*)
}

void CoolEditorFrame::OnQuit( wxCommandEvent& event ) {
    Close();
}

void CoolEditorFrame::OnAbout( wxCommandEvent& event ) {
    wxString msg = wxbuildinfo( long_f );
    wxMessageBox( msg, _( "Welcome to..." ) );
}

void CoolEditorFrame::OnDirPickerCtrlDirChanged( wxFileDirPickerEvent& event ) {
    // Get the selected path from the DirPickerCtrl
    wxString selectedPath = DirPickerCtrl1->GetPath();

    // Clear existing items from the tree
    treeCtrl->DeleteAllItems();

    // Create an image list and add folder and file icons
    wxImageList* imageList = new wxImageList( 16, 16, true, 2 );
    wxIcon folderIcon;
    wxIcon fileIcon;

    wxBitmap folderBitmap = wxArtProvider::GetBitmap( wxART_FOLDER, wxART_OTHER, wxSize( 16, 16 ) );
    wxBitmap fileBitmap = wxArtProvider::GetBitmap( wxART_NORMAL_FILE, wxART_OTHER, wxSize( 16, 16 ) );

    folderIcon.CopyFromBitmap( folderBitmap );
    fileIcon.CopyFromBitmap( fileBitmap );

    imageList->Add( folderIcon );
    imageList->Add( fileIcon );

    // Associate the image list with the tree control
    treeCtrl->AssignImageList( imageList );

    // Add the root item with the selected path
    wxTreeItemId root = treeCtrl->AddRoot( selectedPath, 0 ); // Folder icon for root

    // Declare the recursive lambda function before use
    std::function<void( const wxString&, wxTreeItemId )> PopulateSubdirectories;
    PopulateSubdirectories = [&]( const wxString & path, wxTreeItemId parent ) {
        wxDir dir( path );

        if ( dir.IsOpened() ) {
            wxString filename;
            bool cont = dir.GetFirst( &filename );

            while ( cont ) {
                if ( filename != "." && filename != ".." ) {
                    wxString filepath = wxFileName::DirName( path ).GetFullPath() + wxFileName::GetPathSeparator() + filename;

                    if ( wxDirExists( filepath ) ) {
                        wxTreeItemId child = treeCtrl->AppendItem( parent, filename, 0 ); // Folder icon
                        PopulateSubdirectories( filepath, child ); // Recursively add subdirectories
                    } else {
                        treeCtrl->AppendItem( parent, filename, 1 ); // File icon
                    }
                }

                cont = dir.GetNext( &filename );
            }
        }
    };

    // Call the recursive function to populate the tree
    PopulateSubdirectories( selectedPath, root );
    treeCtrl->Expand( root );
}

wxString CoolEditorFrame::ProcessCommand( const wxString& command ) {
    // Simulate command processing and return a result
    // You can replace this with actual command processing logic
    wxString result;

    if ( command.IsEmpty() ) {
        result = "Error: No command entered.";
    } else {
        result = "Result: Processed command \"" + command + "\"";
    }

    return result;
}


void CoolEditorFrame::OncontrolTextCtrlTextEnter( wxCommandEvent& event ) {
    // Get the command text from the input control
    wxString command = controlTextCtrl->GetValue().AfterFirst( promptText.Length() );

    // Process the command and get the result
    wxString result = ProcessCommand( command );

    // Display the result in the result text control
    resultTextCtrl->AppendText( result + "\n" );

    // Clear the input text control but keep the prompt text
    controlTextCtrl->Clear();
    controlTextCtrl->AppendText( promptText );
}

void CoolEditorFrame::OnTextChange( wxCommandEvent& event ) {
    // Prevent user from deleting the prompt text
    wxString currentText = controlTextCtrl->GetValue();

    if ( currentText.StartsWith( promptText ) ) {
        // If user tries to delete prompt text, restore it
        wxString newText = promptText + currentText.AfterFirst( promptText.Length() );
        controlTextCtrl->ChangeValue( newText );
        controlTextCtrl->SetInsertionPointEnd();
    }
}

void CoolEditorFrame::OnOpen( wxCommandEvent& event ) {
    wxLogMessage( "Open command selected" );
}

void CoolEditorFrame::OnSave( wxCommandEvent& event ) {
    wxLogMessage( "Save command selected" );
}

void CoolEditorFrame::OnPrint( wxCommandEvent& event ) {
    wxLogMessage( "Print command selected" );
}

void CoolEditorFrame::OnExit( wxCommandEvent& event ) {
    Close( true );
}
