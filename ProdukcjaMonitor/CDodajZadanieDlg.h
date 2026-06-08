#pragma once
#include "CZadanieDlgBase.h"

class CDodajZadanieDlg : public CZadanieDlgBase
{
    DECLARE_DYNAMIC(CDodajZadanieDlg)

public:
    CDodajZadanieDlg(Database* pDb, CWnd* pParent = nullptr);
    virtual ~CDodajZadanieDlg();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual void OnBtnZapisz();
    afx_msg void OnBnClickedBtnZapisz();
    afx_msg void OnCbnSelchangeComboOperator();
    DECLARE_MESSAGE_MAP()
};