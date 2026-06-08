#pragma once
#include "Database.h"
#include "HashHelper.h"

class CLoginDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CLoginDlg)

public:
    CLoginDlg(Database* pDb, CWnd* pParent = nullptr);
    virtual ~CLoginDlg();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_LOGIN_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedBtnZaloguj();
    DECLARE_MESSAGE_MAP()

public:
    int     m_idZalogowanego;
    CString m_nazwaZalogowanego;
    bool    m_isAdmin;

private:
    Database* m_pDb;
    CComboBox     m_comboOperator;
    CEdit         m_editHaslo;
    CButton       m_checkPamietaj;

    void ZapiszDoRejestru();
    void WczytajZRejestru();
};