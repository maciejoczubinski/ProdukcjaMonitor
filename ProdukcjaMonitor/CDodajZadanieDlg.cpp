#include "pch.h"
#include "ProdukcjaMonitor.h"
#include "CDodajZadanieDlg.h"

IMPLEMENT_DYNAMIC(CDodajZadanieDlg, CZadanieDlgBase)

CDodajZadanieDlg::CDodajZadanieDlg(Database* pDb, CWnd* pParent)
    : CZadanieDlgBase(IDD_DODAJZADANIEDLG, pDb, pParent)
{
}

CDodajZadanieDlg::~CDodajZadanieDlg()
{
}

void CDodajZadanieDlg::DoDataExchange(CDataExchange* pDX)
{
    CZadanieDlgBase::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_OPERATOR, m_comboOperator);
    DDX_Control(pDX, IDC_COMBO_MASZYNA, m_comboMaszyna);
    DDX_Control(pDX, IDC_COMBO_ZLECENIE, m_comboZlecenie);
    DDX_Control(pDX, IDC_DTP_DATA, m_dtpData);
}

void CDodajZadanieDlg::OnBtnZapisz()
{
    if (!Waliduj()) return;

    Zadanie z;
    z.ID_Operatora = (int)m_comboOperator.GetItemData(m_comboOperator.GetCurSel());
    z.ID_Maszyny = (int)m_comboMaszyna.GetItemData(m_comboMaszyna.GetCurSel());
    z.ID_Zlecenia = (int)m_comboZlecenie.GetItemData(m_comboZlecenie.GetCurSel());
    z.Status = _T("Nowe");

    CTime time;
    m_dtpData.GetTime(time);
    z.DataRozpoczecia.Format(_T("%04d-%02d-%02d %02d:%02d"),
        time.GetYear(), time.GetMonth(), time.GetDay(),
        time.GetHour(), time.GetMinute());

    if (m_pDb->AddZadanie(z))
        EndDialog(IDOK);
    else
        MessageBox(_T("Błąd zapisu zadania!"), _T("Błąd"), MB_ICONERROR);
}

void CDodajZadanieDlg::OnBnClickedBtnZapisz()
{
    OnBtnZapisz();
}

void CDodajZadanieDlg::OnCbnSelchangeComboOperator()
{
    int sel = m_comboOperator.GetCurSel();
    if (sel == CB_ERR) return;

    int idOperatora = (int)m_comboOperator.GetItemData(sel);

    // Wyczyść i odśwież listę maszyn
    m_comboMaszyna.ResetContent();

    std::vector<Maszyna> maszyny = m_pDb->GetMaszynyOperatora(idOperatora);
    for (auto& m : maszyny)
    {
        int idx = m_comboMaszyna.AddString(m.Nazwa);
        m_comboMaszyna.SetItemData(idx, m.ID_Maszyny);
    }
}

BEGIN_MESSAGE_MAP(CDodajZadanieDlg, CZadanieDlgBase)
    ON_BN_CLICKED(IDC_BTN_ZAPISZ, &CDodajZadanieDlg::OnBnClickedBtnZapisz)
    ON_CBN_SELCHANGE(IDC_COMBO_OPERATOR, &CDodajZadanieDlg::OnCbnSelchangeComboOperator)
END_MESSAGE_MAP()