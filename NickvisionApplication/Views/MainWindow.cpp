#include "MainWindow.h"
#include <fstream>
#include <dwmapi.h>
#include <wx/busyinfo.h>
#include "../Models/Configuration.h"
#include "../Models/Update/Updater.h"
#include "SettingsDialog.h"

namespace NickvisionApplication::Views
{
	using namespace NickvisionApplication::Models;
	using namespace NickvisionApplication::Models::Update;
	using namespace NickvisionApplication::Controls;

	MainWindow::MainWindow() : wxFrame(nullptr, IDs::WINDOW, "NickvisionApplication", wxDefaultPosition, wxSize(800, 600))
	{
		Configuration configuration;
		m_isLightTheme = configuration.PreferLightTheme();
		//==Window Settings==//
		Maximize();
		//==Menu==//
		m_menuBar = new wxMenuBar();
		//File
		m_menuFile = new wxMenu();
		m_menuFile->Append(IDs::MENU_NEW_FILE, _("&New File\tCtrl+N"));
		Connect(IDs::MENU_NEW_FILE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::NewFile));
		m_menuFile->Append(IDs::MENU_OPEN_FILE, _("&Open File\tCtrl+O"));
		Connect(IDs::MENU_OPEN_FILE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OpenFile));
		m_menuFile->AppendSeparator();
		m_menuFile->Append(IDs::MENU_EXIT, _("E&xit\tAlt+F4"));
		Connect(IDs::MENU_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::Exit));
		m_menuBar->Append(m_menuFile, _("&File"));
		//Edit
		m_menuEdit = new wxMenu();
		m_menuEdit->Append(IDs::MENU_SETTINGS, _("&Settings\tCtrl+."));
		Connect(IDs::MENU_SETTINGS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::Settings));
		m_menuBar->Append(m_menuEdit, _("&Edit"));
		//Help
		m_menuHelp = new wxMenu();
		m_menuHelp->Append(IDs::MENU_CHECK_FOR_UPDATES, _("&Check for Updates"));
		Connect(IDs::MENU_CHECK_FOR_UPDATES, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::CheckForUpdates));
		m_menuHelp->AppendSeparator();
		m_menuHelp->Append(IDs::MENU_GITHUB_REPO, _("&GitHub Repo"));
		Connect(IDs::MENU_GITHUB_REPO, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::GitHubRepo));
		m_menuHelp->Append(IDs::MENU_REPORT_A_BUG, _("&Report a Bug"));
		Connect(IDs::MENU_REPORT_A_BUG, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::ReportABug));
		m_menuHelp->AppendSeparator();
		m_menuHelp->Append(IDs::MENU_CHANGELOG, _("Change&log"));
		Connect(IDs::MENU_CHANGELOG, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::Changelog));
		m_menuHelp->Append(IDs::MENU_ABOUT, _("&About Application\tF1"));
		Connect(IDs::MENU_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::About));
		m_menuBar->Append(m_menuHelp, _("&Help"));
		SetMenuBar(m_menuBar);
		//==ToolBar==//
		m_toolBar = new wxToolBar(this, IDs::TOOLBAR, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL);
		m_toolBar->AddTool(IDs::TOOL_OPEN_FILE, "", wxBitmap("OPENED_FOLDER", wxBITMAP_TYPE_PNG_RESOURCE))->SetShortHelp(_("Open Folder"));
		Connect(IDs::TOOL_OPEN_FILE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainWindow::OpenFile));
		m_toolBar->AddSeparator();
		m_toolBar->AddTool(IDs::TOOL_SETTINGS, "", wxBitmap("SETTINGS", wxBITMAP_TYPE_PNG_RESOURCE))->SetShortHelp(_("Settings"));
		Connect(IDs::TOOL_SETTINGS, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainWindow::Settings));
		m_toolBar->AddTool(IDs::TOOL_CHECK_FOR_UPDATES, "", wxBitmap("CHECK_FOR_UPDATES", wxBITMAP_TYPE_PNG_RESOURCE))->SetShortHelp(_("Check for Updates"));
		Connect(IDs::TOOL_CHECK_FOR_UPDATES, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainWindow::CheckForUpdates));
		m_toolBar->Realize();
		SetToolBar(m_toolBar);
		//==StatusBar==//
		m_statusBar = new StatusBar(this, IDs::STATUSBAR, m_isLightTheme);
		SetStatusBar(m_statusBar);
		//==InfoBar==//
		m_infoBar = new InfoBar(this, IDs::INFOBAR, m_isLightTheme);
		//==First Name==//
		m_lblFirstName = new wxStaticText(this, IDs::LBL_FIRST_NAME, _("First Name"));
		m_txtFirstName = new wxTextCtrl(this, IDs::TXT_FIRST_NAME, "", wxDefaultPosition, { 320, 24 }, m_isLightTheme ? 0 : wxNO_BORDER);
		m_txtFirstName->SetHint(_("Enter first name here"));
		//==Last Name==//
		m_lblLastName = new wxStaticText(this, IDs::LBL_LAST_NAME, _("Last Name"));
		m_txtLastName = new wxTextCtrl(this, IDs::TXT_LAST_NAME, "", wxDefaultPosition, { 320, 24 }, m_isLightTheme ? 0 : wxNO_BORDER);
		m_txtLastName->SetHint(_("Enter last name here"));
		//==Layout==//
		m_mainBox = new wxBoxSizer(wxVERTICAL);
		m_mainBox->Add(m_infoBar, 0, wxEXPAND);
		m_mainBox->Add(m_lblFirstName, 0, wxLEFT | wxTOP, 6);
		m_mainBox->Add(m_txtFirstName, 0, wxLEFT | wxTOP, 6);
		m_mainBox->Add(m_lblLastName, 0, wxLEFT | wxTOP, 6);
		m_mainBox->Add(m_txtLastName, 0, wxLEFT | wxTOP, 6);
		SetSizer(m_mainBox);
		//==Theme==//
		if (m_isLightTheme) //Light
		{
			//Window
			SetBackgroundColour({ 243, 243, 243 });
			//ToolBar
			m_toolBar->SetBackgroundColour({ 251, 251, 251 });
			//First Name
			m_txtFirstName->SetBackgroundColour({ 251, 251, 251 });
			//Last Name
			m_txtLastName->SetBackgroundColour({ 251, 251, 251 });
		}
		else //Dark
		{
			//Dark Title Bar
			BOOL enabled = TRUE;
			DwmSetWindowAttribute(GetHWND(), DWMWA_USE_IMMERSIVE_DARK_MODE, &enabled, sizeof(enabled));
			//Window
			SetBackgroundColour({ 32, 32, 32 });
			//ToolBar
			m_toolBar->SetBackgroundColour({ 43, 43, 43 });
			m_toolBar->SetForegroundColour(*wxWHITE);
			//First Name
			m_lblFirstName->SetForegroundColour(*wxWHITE);
			m_txtFirstName->SetBackgroundColour({ 43, 43, 43 });
			m_txtFirstName->SetForegroundColour(*wxWHITE);
			//Last Name
			m_lblLastName->SetForegroundColour(*wxWHITE);
			m_txtLastName->SetBackgroundColour({ 43, 43, 43 });
			m_txtLastName->SetForegroundColour(*wxWHITE);
		}
	}

	MainWindow::~MainWindow()
	{
		//==Save Config==//
		Configuration configuration;
		configuration.Save();
	}

	void MainWindow::NewFile(wxCommandEvent& WXUNUSED(event))
	{
		wxFileDialog newFileDialog(this, _("New File"), "", "", "Text Files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (newFileDialog.ShowModal() == wxID_OK)
		{
			std::string path(newFileDialog.GetPath());
			m_statusBar->SetMessage(path);
			std::ofstream file(path);
			if (file.is_open())
			{
				file << "" << std::endl;
			}
		}
	}

	void MainWindow::OpenFile(wxCommandEvent& WXUNUSED(event))
	{
		wxFileDialog openFileDialog(this, _("Open File"), "", "", "Text Files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
		if (openFileDialog.ShowModal() == wxID_OK)
		{
			m_statusBar->SetMessage(openFileDialog.GetPath());
		}
	}

	void MainWindow::Exit(wxCommandEvent& WXUNUSED(event))
	{
		Close();
	}

	void MainWindow::Settings(wxCommandEvent& WXUNUSED(event))
	{
		SettingsDialog settingsDialog(this, m_isLightTheme);
		settingsDialog.ShowModal();
	}

	void MainWindow::CheckForUpdates(wxCommandEvent& WXUNUSED(event))
	{
		Updater updater("https://raw.githubusercontent.com/nlogozzo/NickvisionApplication/main/UpdateConfig.json", { "2022.2.0" });
		wxBusyInfo busyChecking(wxBusyInfoFlags()
			.Parent(this)
			.Title(_("<b>Please Wait</b>"))
			.Text(_("Checking for updates..."))
			.Background(m_isLightTheme ? *wxWHITE : *wxBLACK)
			.Foreground(m_isLightTheme ? *wxBLACK : *wxWHITE)
			.Transparency(4 * wxALPHA_OPAQUE / 5));
		updater.CheckForUpdates();
		busyChecking.~wxBusyInfo();
		if (updater.UpdateAvailable())
		{
			int result = wxMessageBox(_("Update Available\n\n===V" + updater.GetLatestVersion()->ToString() + " Changelog===\n" + updater.GetChangelog() + "\n\nNickvisionApplication will automatically download and install the update. Please save all work before continuing. Are you ready to update?"), _("Update Available"), wxICON_INFORMATION | wxYES_NO, this);
			if (result == wxYES)
			{
				bool updateSuccess = false;
				wxBusyInfo busyUpdating(wxBusyInfoFlags()
					.Parent(this)
					.Title(_("<b>Please Wait</b>"))
					.Text(_("Downloading and installing the update..."))
					.Background(m_isLightTheme ? *wxWHITE : *wxBLACK)
					.Foreground(m_isLightTheme ? *wxBLACK : *wxWHITE)
					.Transparency(4 * wxALPHA_OPAQUE / 5));
				updateSuccess = updater.Update(this);
				busyUpdating.~wxBusyInfo();
				if (!updateSuccess)
				{
					m_infoBar->ShowMessage(_("There was an error downloading and install the update. Please try again and if the error continues, file a bug report."), wxICON_ERROR);
				}
			}
		}
		else
		{
			m_infoBar->ShowMessage(_("There is no update available at this time. Please try again later."), wxICON_WARNING);
		}
	}

	void MainWindow::GitHubRepo(wxCommandEvent& WXUNUSED(event))
	{
		wxLaunchDefaultBrowser("https://github.com/nlogozzo/NickvisionApplication");
	}

	void MainWindow::ReportABug(wxCommandEvent& WXUNUSED(event))
	{
		wxLaunchDefaultBrowser("https://github.com/nlogozzo/NickvisionApplication/issues/new");
	}

	void MainWindow::Changelog(wxCommandEvent& WXUNUSED(event))
	{
		wxMessageBox(_("What's New?\n\n- Initial Release"), _("Changelog"), wxICON_INFORMATION, this);
	}

	void MainWindow::About(wxCommandEvent& WXUNUSED(event))
	{
		wxMessageBox(_("About NickvisionApplication\n\nVersion 2022.2.0\nA template for creating Nickvision applications.\n\nBuilt with C++, wxWidgets, and Icons8\n(C) Nickvision 2021-2022"), _("About"), wxICON_INFORMATION, this);
	}
}