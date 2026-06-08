#pragma once
#include "Database.h"

class CZadanieDlgBase : public CDialogEx
{
    DECLARE_DYNAMIC(CZadanieDlgBase)

public:
    CZadanieDlgBase(UINT nIDTemplate, Database* pDb, CWnd* pParent = nullptr);
    virtual ~CZadanieDlgBase();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    virtual void OnBtnZapisz() = 0;

    void WypelnijListy();
    bool Waliduj();

    Database* m_pDb;
    CComboBox     m_comboOperator;
    CComboBox     m_comboMaszyna;
    CComboBox     m_comboZlecenie;
    CDateTimeCtrl m_dtpData;

    DECLARE_MESSAGE_MAP()
};