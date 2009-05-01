#include "nel_launcher_dlg.h"
#include "connection.h"

#include <QtGui/QMessageBox>

NLMISC::CConfigFile ConfigFile;

CNelLauncherDlg::CNelLauncherDlg(QWidget *parent)
{
	displayerAdded = false;
	verboseLog = false;

	// Set up the Qt UI.
	setupUi(this);

	// Connect singals/slots.
	connect( pbLogin, SIGNAL( clicked() ), this, SLOT( clickedLogin() ) );

	// Set up the table.
	QStringList tableLabels;
	tableLabels << "Nb Players" << "Version" << "Status" << "Shard Name";
	tblShardList->setColumnCount(4);
	tblShardList->setHorizontalHeaderLabels(tableLabels);

	// Set up the NeL stuff.
	fileDisplayer = new NLMISC::CFileDisplayer("nel_launcher.log", true);
        NLMISC::createDebug();
        NLMISC::DebugLog->addDisplayer(fileDisplayer);
        NLMISC::InfoLog->addDisplayer(fileDisplayer);
        NLMISC::WarningLog->addDisplayer(fileDisplayer);
        NLMISC::ErrorLog->addDisplayer(fileDisplayer);
        NLMISC::AssertLog->addDisplayer(fileDisplayer);
        displayerAdded = true;

        nlinfo("Loading config file");

        ConfigFile.load("nel_launcher.cfg");

	if(ConfigFile.exists("VerboseLog"))
		verboseLog =  ConfigFile.getVar("VerboseLog").asBool();

	if(verboseLog) nlinfo("Using verbose log mode");

}

CNelLauncherDlg::~CNelLauncherDlg()
{
	if(displayerAdded)
	{
		NLMISC::createDebug();
		NLMISC::DebugLog->removeDisplayer(fileDisplayer);
		NLMISC::InfoLog->removeDisplayer(fileDisplayer);
		NLMISC::WarningLog->removeDisplayer(fileDisplayer);
		NLMISC::ErrorLog->removeDisplayer(fileDisplayer);
		NLMISC::AssertLog->removeDisplayer(fileDisplayer);
	}
}

void CNelLauncherDlg::clickedSignUp()
{

}

void CNelLauncherDlg::clickedLogin()
{
	std::string username = leUsername->text().toStdString();
	std::string password = lePassword->text().toStdString();

	nlinfo("received login attempt for %s with %s", username.c_str(), password.c_str());

	// Set Registry Key or home settings.
	// TODO

	// Disable buttons while logging in.
	// TODO

	// Check the login and password.
	CNelLauncherConnection connection;
	//string res = checkLogin(l, p, ConfigFile.getVar("Application").asString(0));
	std::string res = connection.checkLogin(username, password, ConfigFile.getVar("Application").asString(0));
	if(res.empty()) // successful login
	{
		;
	}
	else
	{
		QMessageBox::about(this, "Failed Login", "Failed to log in to Login Service: " + QString(res.c_str()));
	}
}
