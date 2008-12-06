#include <QApplication>
#include "nel/misc/app_context.h"
#include "words_dicDlg.h"


int main(int argc, char *argv[])
{

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need.
	NLMISC::CApplicationContext myApplicationContext;

	Q_INIT_RESOURCE(words_dic_Qt);
	QApplication app(argc, argv);

	CWords_dicDlg wordsDic;
	wordsDic.show();

	return app.exec();
}