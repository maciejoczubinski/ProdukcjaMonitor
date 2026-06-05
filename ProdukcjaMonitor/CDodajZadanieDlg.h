#pragma once
#include "Database.h"

class CDodajZadanieDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDodajZadanieDlg)

public:
    CDodajZadanieDlg(Database* pDb, CWnd* pParent = nullptr);
    virtual ~CDodajZadanieDlg();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DODAJZADANIEDLG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

public:
    CComboBox m_comboOperator;
    CComboBox m_comboMaszyna;
    CComboBox m_comboZlecenie;
    CDateTimeCtrl m_dtpData;

private:
    Database* m_pDb;
public:
    afx_msg void OnBnClickedBtnZapisz();
};