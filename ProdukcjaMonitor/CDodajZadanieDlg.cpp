#include "pch.h"
#include "ProdukcjaMonitor.h"
#include "CDodajZadanieDlg.h"

IMPLEMENT_DYNAMIC(CDodajZadanieDlg, CDialogEx)

CDodajZadanieDlg::CDodajZadanieDlg(Database* pDb, CWnd* pParent)
    : CDialogEx(IDD_DODAJZADANIEDLG, pParent)
    , m_pDb(pDb)
{
}

CDodajZadanieDlg::~CDodajZadanieDlg()
{
}

void CDodajZadanieDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_OPERATOR, m_comboOperator);
    DDX_Control(pDX, IDC_COMBO_MASZYNA, m_comboMaszyna);
    DDX_Control(pDX, IDC_COMBO_ZLECENIE, m_comboZlecenie);
    DDX_Control(pDX, IDC_DTP_DATA, m_dtpData);
}

BOOL CDodajZadanieDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    std::vector<Operator> operatorzy = m_pDb->GetOperatorzy();
    for (auto& op : operatorzy)
    {
        CString nazwa;
        nazwa.Format(_T("%s %s"), (LPCTSTR)op.Imie, (LPCTSTR)op.Nazwisko);
        int idx = m_comboOperator.AddString(nazwa);
        m_comboOperator.SetItemData(idx, op.ID_Operatora);
    }

    std::vector<Maszyna> maszyny = m_pDb->GetMaszyny();
    for (auto& m : maszyny)
    {
        int idx = m_comboMaszyna.AddString(m.Nazwa);
        m_comboMaszyna.SetItemData(idx, m.ID_Maszyny);
    }

    std::vector<Zlecenie> zlecenia = m_pDb->GetZlecenia();
    for (auto& z : zlecenia)
    {
        int idx = m_comboZlecenie.AddString(z.Nazwa);
        m_comboZlecenie.SetItemData(idx, z.ID_Zlecenia);
    }

    return TRUE;
}

BEGIN_MESSAGE_MAP(CDodajZadanieDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_ZAPISZ, &CDodajZadanieDlg::OnBnClickedBtnZapisz)
END_MESSAGE_MAP()
void CDodajZadanieDlg::OnBnClickedBtnZapisz()
{
    // Sprawdź czy użytkownik wybrał wszystkie pola
    if (m_comboOperator.GetCurSel() == CB_ERR)
    {
        MessageBox(_T("Wybierz operatora!"), _T("Uwaga"), MB_ICONWARNING);
        return;
    }
    if (m_comboMaszyna.GetCurSel() == CB_ERR)
    {
        MessageBox(_T("Wybierz maszynę!"), _T("Uwaga"), MB_ICONWARNING);
        return;
    }
    if (m_comboZlecenie.GetCurSel() == CB_ERR)
    {
        MessageBox(_T("Wybierz zlecenie!"), _T("Uwaga"), MB_ICONWARNING);
        return;
    }

    // Pobierz ID wybranych elementów
    Zadanie z;
    z.ID_Operatora = (int)m_comboOperator.GetItemData(m_comboOperator.GetCurSel());
    z.ID_Maszyny = (int)m_comboMaszyna.GetItemData(m_comboMaszyna.GetCurSel());
    z.ID_Zlecenia = (int)m_comboZlecenie.GetItemData(m_comboZlecenie.GetCurSel());
    z.Status = _T("Nowe");

    // Pobierz datę z DateTimePicker
    CTime time;
    m_dtpData.GetTime(time);
    z.DataRozpoczecia.Format(_T("%04d-%02d-%02d %02d:%02d"),
        time.GetYear(), time.GetMonth(), time.GetDay(),
        time.GetHour(), time.GetMinute());

    // Zapisz do bazy
    if (m_pDb->AddZadanie(z))
        EndDialog(IDOK);
    else
        MessageBox(_T("Błąd zapisu zadania!"), _T("Błąd"), MB_ICONERROR);
}
