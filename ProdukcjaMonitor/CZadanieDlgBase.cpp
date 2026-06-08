#include "pch.h"
#include "ProdukcjaMonitor.h"
#include "CZadanieDlgBase.h"

IMPLEMENT_DYNAMIC(CZadanieDlgBase, CDialogEx)

CZadanieDlgBase::CZadanieDlgBase(UINT nIDTemplate, Database* pDb, CWnd* pParent)
    : CDialogEx(nIDTemplate, pParent)
    , m_pDb(pDb)
{
}

CZadanieDlgBase::~CZadanieDlgBase()
{
}

BOOL CZadanieDlgBase::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    WypelnijListy();
    return TRUE;
}

void CZadanieDlgBase::WypelnijListy()
{
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
}

bool CZadanieDlgBase::Waliduj()
{
    if (m_comboOperator.GetCurSel() == CB_ERR)
    {
        MessageBox(_T("Wybierz operatora!"), _T("Uwaga"), MB_ICONWARNING);
        return false;
    }
    if (m_comboMaszyna.GetCurSel() == CB_ERR)
    {
        MessageBox(_T("Wybierz maszynê!"), _T("Uwaga"), MB_ICONWARNING);
        return false;
    }
    if (m_comboZlecenie.GetCurSel() == CB_ERR)
    {
        MessageBox(_T("Wybierz zlecenie!"), _T("Uwaga"), MB_ICONWARNING);
        return false;
    }
    return true;
}
void CZadanieDlgBase::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CZadanieDlgBase, CDialogEx)
END_MESSAGE_MAP()