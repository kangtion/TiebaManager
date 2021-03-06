// ConfirmDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TiebaManager.h"
#include "ConfirmDlg.h"
#include "afxdialogex.h"


// CConfirmDlg 对话框

IMPLEMENT_DYNAMIC(CConfirmDlg, CDialog)

CConfirmDlg::CConfirmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfirmDlg::IDD, pParent)
{
	m_operation = NULL;
}

CConfirmDlg::CConfirmDlg(Operation* operation, CWnd* pParent)
	: CDialog(CConfirmDlg::IDD, pParent)
{
	m_operation = operation;
}

#pragma region MFC
CConfirmDlg::~CConfirmDlg()
{
}

void CConfirmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_contentEdit);
	DDX_Control(pDX, IDC_STATIC1, m_static);
	DDX_Control(pDX, IDOK, m_yesButton);
	DDX_Control(pDX, IDCANCEL, m_noButton);
}


BEGIN_MESSAGE_MAP(CConfirmDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()
#pragma endregion

// CConfirmDlg 消息处理程序

#pragma region UI
// 限制最小尺寸
void CConfirmDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 455;
	lpMMI->ptMinTrackSize.y = 362;

	CDialog::OnGetMinMaxInfo(lpMMI);
}

// 改变尺寸
void CConfirmDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (m_contentEdit.m_hWnd == NULL)
		return;

	CRect rect;
	GetClientRect(&rect); // 默认737 * 519
	m_contentEdit.SetWindowPos(NULL, 0, 0, rect.Width() - 23, rect.Height() - 56, SWP_NOMOVE | SWP_NOREDRAW);
	int y = rect.Height() - 35;
	m_static.SetWindowPos(NULL, 11, y, 0, 0, SWP_NOSIZE | SWP_NOREDRAW);
	m_yesButton.SetWindowPos(NULL, rect.Width() - 212, y, 0, 0, SWP_NOSIZE | SWP_NOREDRAW);
	m_noButton.SetWindowPos(NULL, rect.Width() - 100, y, 0, 0, SWP_NOSIZE | SWP_NOREDRAW);

	Invalidate();
}
#pragma endregion

// 初始化
BOOL CConfirmDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_operation != NULL)
	{
		SetWindowText(m_operation->title);
		m_contentEdit.SetWindowText(m_operation->msg + _T("\r\n\r\n作者：") + m_operation->author);
	}
	MessageBeep(MB_ICONQUESTION);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
