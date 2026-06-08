#pragma once
#include "CZadanieDlgBase.h"

class CEdytujZadanieDlg : public CZadanieDlgBase
{
    DECLARE_DYNAMIC(CEdytujZadanieDlg)

public:
    CEdytujZadanieDlg(Database* pDb, const Zadanie& zadanie, CWnd* pParent = nullptr);
    virtual ~CEdytujZadanieDlg();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    virtual void OnBtnZapisz();
    afx_msg void OnBnClickedBtnZapisz();
    DECLARE_MESSAGE_MAP()

private:
    Zadanie       m_zadanie;
    CComboBox     m_comboStatus;
};