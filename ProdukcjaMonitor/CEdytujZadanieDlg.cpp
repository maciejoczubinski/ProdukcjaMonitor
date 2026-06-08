#include "pch.h"
#include "ProdukcjaMonitor.h"
#include "CEdytujZadanieDlg.h"

IMPLEMENT_DYNAMIC(CEdytujZadanieDlg, CZadanieDlgBase)

CEdytujZadanieDlg::CEdytujZadanieDlg(Database* pDb, const Zadanie& zadanie, CWnd* pParent)
    : CZadanieDlgBase(IDD_EDYTUJZADANIEDLG, pDb, pParent)
    , m_zadanie(zadanie)
{
}

CEdytujZadanieDlg::~CEdytujZadanieDlg()
{
}

void CEdytujZadanieDlg::DoDataExchange(CDataExchange* pDX)
{
    CZadanieDlgBase::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_OPERATOR, m_comboOperator);
    DDX_Control(pDX, IDC_COMBO_MASZYNA, m_comboMaszyna);
    DDX_Control(pDX, IDC_COMBO_ZLECENIE, m_comboZlecenie);
    DDX_Control(pDX, IDC_DTP_DATA, m_dtpData);
    DDX_Control(pDX, IDC_COMBO_STATUS, m_comboStatus);
}

BOOL CEdytujZadanieDlg::OnInitDialog()
{
    CZadanieDlgBase::OnInitDialog();

    // Wype³nij status
    m_comboStatus.AddString(_T("Nowe"));
    m_comboStatus.AddString(_T("W trakcie"));
    m_comboStatus.AddString(_T("Zakoñczone"));

    // Zaznacz aktualny status
    int idx = m_comboStatus.FindStringExact(-1, m_zadanie.Status);
    if (idx != CB_ERR) m_comboStatus.SetCurSel(idx);

    // Zaznacz aktualnego operatora
    for (int i = 0; i < m_comboOperator.GetCount(); i++)
    {
        if ((int)m_comboOperator.GetItemData(i) == m_zadanie.ID_Operatora)
        {
            m_comboOperator.SetCurSel(i);
            break;
        }
    }

    // Zaznacz aktualn¹ maszynê
    for (int i = 0; i < m_comboMaszyna.GetCount(); i++)
    {
        if ((int)m_comboMaszyna.GetItemData(i) == m_zadanie.ID_Maszyny)
        {
            m_comboMaszyna.SetCurSel(i);
            break;
        }
    }

    // Zaznacz aktualne zlecenie
    for (int i = 0; i < m_comboZlecenie.GetCount(); i++)
    {
        if ((int)m_comboZlecenie.GetItemData(i) == m_zadanie.ID_Zlecenia)
        {
            m_comboZlecenie.SetCurSel(i);
            break;
        }
    }

    return TRUE;
}

void CEdytujZadanieDlg::OnBtnZapisz()
{
    if (!Waliduj()) return;

    Zadanie z;
    z.ID_Zadania = m_zadanie.ID_Zadania;
    z.ID_Operatora = (int)m_comboOperator.GetItemData(m_comboOperator.GetCurSel());
    z.ID_Maszyny = (int)m_comboMaszyna.GetItemData(m_comboMaszyna.GetCurSel());
    z.ID_Zlecenia = (int)m_comboZlecenie.GetItemData(m_comboZlecenie.GetCurSel());

    int statusIdx = m_comboStatus.GetCurSel();
    if (statusIdx != CB_ERR)
        m_comboStatus.GetLBText(statusIdx, z.Status);

    if (m_pDb->UpdateStatus(z.ID_Zadania, z.Status))
        EndDialog(IDOK);
    else
        MessageBox(_T("B³¹d zapisu!"), _T("B³¹d"), MB_ICONERROR);
}

void CEdytujZadanieDlg::OnBnClickedBtnZapisz()
{
    OnBtnZapisz();
}

BEGIN_MESSAGE_MAP(CEdytujZadanieDlg, CZadanieDlgBase)
    ON_BN_CLICKED(IDC_BTN_ZAPISZ, &CEdytujZadanieDlg::OnBnClickedBtnZapisz)
END_MESSAGE_MAP()