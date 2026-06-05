
// ProdukcjaMonitorDlg.cpp: plik implementacji
//

#include "pch.h"
#include "framework.h"
#include "ProdukcjaMonitor.h"
#include "ProdukcjaMonitorDlg.h"
#include "CDodajZadanieDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Okno dialogowe CAboutDlg używane na potrzeby informacji o aplikacji

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dane okna dialogowego
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // obsługa DDX/DDV

// Implementacja
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// okno dialogowe CProdukcjaMonitorDlg



CProdukcjaMonitorDlg::CProdukcjaMonitorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRODUKCJAMONITOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProdukcjaMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ZADANIA, m_listZadania);
}

BEGIN_MESSAGE_MAP(CProdukcjaMonitorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ODSWIEZ, &CProdukcjaMonitorDlg::OnBnClickedBtnOdswiez)
	ON_BN_CLICKED(IDC_BTN_USUN, &CProdukcjaMonitorDlg::OnBnClickedBtnUsun)
	ON_BN_CLICKED(IDC_BTN_DODAJ, &CProdukcjaMonitorDlg::OnBnClickedBtnDodaj)
END_MESSAGE_MAP()


// Procedury obsługi komunikatów CProdukcjaMonitorDlg

BOOL CProdukcjaMonitorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Dodaj pozycję „Informacje...” do menu systemowego.

	// Element IDM_ABOUTBOX musi należeć do zakresu poleceń systemowych.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Ustaw ikonę dla tego okna dialogowego. Struktura wykonuje to automatycznie
	//  gdy okno główne aplikacji nie jest oknem dialogowym
	SetIcon(m_hIcon, TRUE);			// Ustaw duże ikony
	SetIcon(m_hIcon, FALSE);		// Ustaw małe ikony

	// TODO: Dodaj tutaj dodatkowe inicjowanie
	if (!m_db.Connect())
	{
		MessageBox(_T("Błąd połączenia z bazą danych!"), _T("Błąd"), MB_ICONERROR);
	}
	
	// Inicjacja kolumn listy
	m_listZadania.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listZadania.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 40);
	m_listZadania.InsertColumn(1, _T("Operator"), LVCFMT_LEFT, 150);
	m_listZadania.InsertColumn(2, _T("Maszyna"), LVCFMT_LEFT, 150);
	m_listZadania.InsertColumn(3, _T("Zlecenie"), LVCFMT_LEFT, 150);
	m_listZadania.InsertColumn(4, _T("Data rozpoczęcia"), LVCFMT_LEFT, 130);
	m_listZadania.InsertColumn(5, _T("Status"), LVCFMT_LEFT, 100);

	// Załaduj dane
	OdswiezListe();

	return TRUE;  // zwracaj wartość TRUE, dopóki fokus nie zostanie ustawiony na formant
}

void CProdukcjaMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Jeśli dodasz przycisk minimalizacji do okna dialogowego, będziesz potrzebować poniższego kodu
//  aby narysować ikonę. Dla aplikacji MFC używających modelu dokumentu/widoku
//  to jest wykonywane automatycznie przez strukturę.

void CProdukcjaMonitorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // kontekst urządzenia dotyczący malowania

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Wyśrodkuj ikonę w prostokącie klienta
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Rysuj ikonę
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// System wywołuje tę funkcję, aby uzyskać kursor wyświetlany podczas przeciągania przez użytkownika
//  zminimalizowane okno.
HCURSOR CProdukcjaMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CProdukcjaMonitorDlg::OdswiezListe()
{
	//czyścimy listę przed załadowaniem
	m_listZadania.DeleteAllItems();
	// pobieramy wszystkie zadania z bazy do wektora. wywołujemy metode z Database
	std::vector<Zadanie> zadania = m_db.GetZadania();

	for (int i = 0; i < (int)zadania.size(); i++)
	{
		CString id;
		id.Format(_T("%d"), zadania[i].ID_Zadania);

		m_listZadania.InsertItem(i, id);
		m_listZadania.SetItemText(i, 1, zadania[i].NazwaOperatora);
		m_listZadania.SetItemText(i, 2, zadania[i].NazwaMaszyny);
		m_listZadania.SetItemText(i, 3, zadania[i].NazwaZlecenia);
		m_listZadania.SetItemText(i, 4, zadania[i].DataRozpoczecia);
		m_listZadania.SetItemText(i, 5, zadania[i].Status);
		//gdzie i to numer wiersza a id numer kolumny
	}
}


void CProdukcjaMonitorDlg::OnBnClickedBtnOdswiez()
{
	OdswiezListe();
}

void CProdukcjaMonitorDlg::OnBnClickedBtnUsun()
{
	//Sprawdzamy czy zaznaczone
	int nSelected = m_listZadania.GetNextItem(-1, LVNI_SELECTED);
	if (nSelected == -1)
	{
		MessageBox(_T("Wybierz zadanie do usunięcia!"), _T("Uwaga"), MB_ICONWARNING);
		return;
	}

	//Pobieramy id zaznaczonego zadania
	CString strId = m_listZadania.GetItemText(nSelected, 0);
	int idZadania = _ttoi(strId);

	//Potwierdzenie
	if (MessageBox(_T("Czy na pewno chcesz usunąć to zadanie?"), _T("Potwierdzenie"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		if (m_db.DeleteZadanie(idZadania))
			OdswiezListe();
		else
			MessageBox(_T("Błąd usuwania zadania!"), _T("Błąd"), MB_ICONERROR);
	}
}

void CProdukcjaMonitorDlg::OnBnClickedBtnDodaj()
{
	CDodajZadanieDlg dlg(&m_db, this);
	if (dlg.DoModal() == IDOK)
	{
		OdswiezListe();
	}
}
