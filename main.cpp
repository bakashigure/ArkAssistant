
#include "ArkAssistant.h"

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ArkAssistant w;
	w.init();
	w.show();
	return a.exec();
}
