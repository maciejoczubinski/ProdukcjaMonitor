#include "pch.h"
#include "ProdukcjaMonitor.h"
#include "CLoginDlg.h"

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(Database* pDb, CWnd* pParent)
    : CDialogEx(IDD_LOGIN_DIALOG, pParent)
    , m_pDb(pDb)
    , m_idZalogowanego(-1)
    , m_isAdmin(false)
{
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_OPERATOR, m_comboOperator);
    DDX_Control(pDX, IDC_EDIT_HASLO, m_editHaslo);
    DDX_Control(pDX, IDC_CHECK_PAMIETAJ, m_checkPamietaj);
}

BOOL CLoginDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Ustaw maskę hasła
    m_editHaslo.SetPasswordChar('*');

    // Wypełnij listę operatorów
    // Na początku dodaj admina
    int idx = m_comboOperator.AddString(_T("Administrator"));
    m_comboOperator.SetItemData(idx, 0);

    // Potem operatorów z bazy
    std::vector<Operator> operatorzy = m_pDb->GetOperatorzy();
    for (auto& op : operatorzy)
    {
        CString nazwa;
        nazwa.Format(_T("%s %s"), (LPCTSTR)op.Imie, (LPCTSTR)op.Nazwisko);
        int i = m_comboOperator.AddString(nazwa);
        m_comboOperator.SetItemData(i, op.ID_Operatora);
    }

    // Wczytaj zapisane dane z rejestru
    WczytajZRejestru();

    return TRUE;
}

void CLoginDlg::WczytajZRejestru()
{
    CWinApp* pApp = AfxGetApp();
    int savedIdx = pApp->GetProfileInt(_T("Login"), _T("OperatorIdx"), -1);
    bool pamietaj = pApp->GetProfileInt(_T("Login"), _T("Pamietaj"), 0) == 1;

    if (pamietaj && savedIdx >= 0)
    {
        m_comboOperator.SetCurSel(savedIdx);
        m_checkPamietaj.SetCheck(BST_CHECKED);
    }
}

void CLoginDlg::ZapiszDoRejestru()
{
    CWinApp* pApp = AfxGetApp();
    bool pamietaj = m_checkPamietaj.GetCheck() == BST_CHECKED;

    pApp->WriteProfileInt(_T("Login"), _T("Pamietaj"), pamietaj ? 1 : 0);
    if (pamietaj)
        pApp->WriteProfileInt(_T("Login"), _T("OperatorIdx"), m_comboOperator.GetCurSel());
    else
        pApp->WriteProfileInt(_T("Login"), _T("OperatorIdx"), -1);
}

void CLoginDlg::OnBnClickedBtnZaloguj()
{
    if (m_comboOperator.GetCurSel() == CB_ERR)
    {
        MessageBox(_T("Wybierz operatora!"), _T("Uwaga"), MB_ICONWARNING);
        return;
    }

    CString haslo;
    m_editHaslo.GetWindowText(haslo);
    if (haslo.IsEmpty())
    {
        MessageBox(_T("Wpisz hasło!"), _T("Uwaga"), MB_ICONWARNING);
        return;
    }

    int sel = m_comboOperator.GetCurSel();
    int idOperatora = (int)m_comboOperator.GetItemData(sel);

    // Sprawdź czy to admin
    if (idOperatora == 0)
    {
        if (haslo == _T("admin123"))
        {
            m_idZalogowanego = 0;
            m_nazwaZalogowanego = _T("Administrator");
            m_isAdmin = true;
            ZapiszDoRejestru();
            EndDialog(IDOK);
        }
        else
        {
            MessageBox(_T("Błędne hasło!"), _T("Błąd"), MB_ICONERROR);
        }
        return;
    }

    // Sprawdź hasło operatora
    CString hasloHash = HashHelper::SHA256(haslo);
    std::vector<Operator> operatorzy = m_pDb->GetOperatorzy();
    for (auto& op : operatorzy)
    {
        if (op.ID_Operatora == idOperatora)
        {
            if (op.Haslo == hasloHash)
            {
                m_idZalogowanego = op.ID_Operatora;
                m_nazwaZalogowanego = op.Imie + _T(" ") + op.Nazwisko;
                m_isAdmin = false;
                ZapiszDoRejestru();
                EndDialog(IDOK);
            }
            else
            {
                MessageBox(_T("Błędne hasło!"), _T("Błąd"), MB_ICONERROR);
            }
            return;
        }
    }
}

BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_ZALOGUJ, &CLoginDlg::OnBnClickedBtnZaloguj)
END_MESSAGE_MAP()