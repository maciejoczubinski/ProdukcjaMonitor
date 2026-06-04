
// ProdukcjaMonitorDlg.h: plik nagłówkowy
//

#pragma once
#include "Database.h"

// okno dialogowe CProdukcjaMonitorDlg
class CProdukcjaMonitorDlg : public CDialogEx
{
// Konstrukcja
public:
	CProdukcjaMonitorDlg(CWnd* pParent = nullptr);	// konstruktor standardowy

// Dane okna dialogowego
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRODUKCJAMONITOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// obsługa DDX/DDV


// Implementacja
protected:
	HICON m_hIcon;

	// Wygenerowano funkcje mapy komunikatów
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	Database m_db;
	DECLARE_MESSAGE_MAP()
	CListCtrl m_listZadania;
	void OdswiezListe();
};
