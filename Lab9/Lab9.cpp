#include "stdafx.h"
#include "MyApplication.h"

int main()
 {
	MyApplication app;
	app.startup();
	while(app.keepRunning())
	{
		app.renderOneFrame();
	}

	return 0;
}
