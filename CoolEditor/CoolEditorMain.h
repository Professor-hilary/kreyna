/***************************************************************
 * Name:      CoolEditorMain.h
 * Purpose:   Defines Application Frame
 * Author:    prof hilary (profesorhilary@outlook.com)
 * Created:   2024-07-14
 * Copyright: prof hilary ()
 * License:
 **************************************************************/

#ifndef COOLEDITORMAIN_H
#define COOLEDITORMAIN_H

//(*Headers(CoolEditorFrame)
#include <wx/aui/aui.h>
#include <wx/filepicker.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
#include <wx/treectrl.h>
//*)

// My Includes
#include <wx/stc/stc.h>
#include <vector>

class CoolEditorFrame: public wxFrame {
  public:

    CoolEditorFrame( wxWindow* parent, wxWindowID id = -1 );
    virtual ~CoolEditorFrame();

  private:

    //(*Handlers(CoolEditorFrame)
    void OnQuit( wxCommandEvent& event );
    void OnAbout( wxCommandEvent& event );
    void OnDirPickerCtrlDirChanged( wxFileDirPickerEvent& event );
    void OncontrolTextCtrlTextEnter( wxCommandEvent& event );
    void OnRichTextEditorChanged( wxCommandEvent& event );
    //*)

    //(*Identifiers(CoolEditorFrame)
    static const long ID_TEXTCTRL1;
    static const long ID_AUINOTEBOOK3;
    static const long ID_PANEL_HOME;
    static const long ID_PANEL_EDIT;
    static const long ID_PANEL_VIEW;
    static const long ID_PANEL_LAYOUT;
    static const long ID_PANEL_PROJECT;
    static const long ID_PANEL_BUILD;
    static const long ID_PANEL_DEBUG;
    static const long ID_PANEL_EDITOR;
    static const long ID_PANEL_SETTING;
    static const long ID_PANEL_HELP;
    static const long ID_AUINOTEBOOK4;
    static const long ID_DIRPICKERCTRL1;
    static const long ID_TREECTRL_FILELIST;
    static const long ID_PANEL2;
    static const long ID_AUINOTEBOOK2;
    static const long ID_AUINOTEBOOK1;
    static const long ID_PANEL1;
    static const long ID_AUINOTEBOOK5;
    static const long ID_STATUSBAR1;
    //*)

    //(*Declarations(CoolEditorFrame)
    wxAuiManager* ParentAuiManager;
    wxAuiNotebook* AuiNotebookAside;
    wxAuiNotebook* AuiNotebookConsolePane;
    wxAuiNotebook* AuiNotebookEditors;
    wxAuiNotebook* AuiNotebookManagement;
    wxAuiNotebook* AuiNotebookToolBar;
    wxDirPickerCtrl* DirPickerCtrl1;
    wxPanel* Panel1;
    wxPanel* Panel2;
    wxPanel* PanelBuild;
    wxPanel* PanelDebug;
    wxPanel* PanelEdit;
    wxPanel* PanelEditor;
    wxPanel* PanelHelp;
    wxPanel* PanelHome;
    wxPanel* PanelLayout;
    wxPanel* PanelProject;
    wxPanel* PanelSetting;
    wxPanel* PanelView;
    wxStatusBar* StatusBar1;
    wxTextCtrl* controlTextCtrl;
    wxTreeCtrl* treeCtrl;
    //*)

    void setCppStyling( wxString );
    wxStyledTextCtrl *stc;
    std::vector<wxString> fileNames;
    wxString ProcessCommand(const wxString& command);
    void OnTextChange( wxCommandEvent& event );
    void OnUpdateUI(wxStyledTextEvent& event);
    void SimulateDirChangeEvent(const wxString& path) ;

    // wxTextCtrl* controlTextCtrl;
    wxTextCtrl* resultTextCtrl;
    wxString promptText;

    // Toolbar ribon methods
    void CreateRibbonToolbar();
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnPrint(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);



    DECLARE_EVENT_TABLE()
};

#endif // COOLEDITORMAIN_H
