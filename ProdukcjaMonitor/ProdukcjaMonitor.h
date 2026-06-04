
// ProdukcjaMonitor.h: główny plik nagłówkowy aplikacji PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "dołącz nagłówek „pch.h” przed dołączeniem tego pliku na potrzeby optymalizacji PCH"
#endif

#include "resource.h"		// główne symbole


// CProdukcjaMonitorApp:
// Aby uzyskać implementację klasy, zobacz ProdukcjaMonitor.cpp
//

class CProdukcjaMonitorApp : public CWinApp
{
public:
	CProdukcjaMonitorApp();

// Przesłania
public:
	virtual BOOL InitInstance();

// Implementacja

	DECLARE_MESSAGE_MAP()
};

extern CProdukcjaMonitorApp theApp;
