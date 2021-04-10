
// Ray castingView.cpp: CRaycastingView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Ray casting.h"
#endif

#include "Ray castingDoc.h"
#include "Ray castingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRaycastingView

IMPLEMENT_DYNCREATE(CRaycastingView, CView)

BEGIN_MESSAGE_MAP(CRaycastingView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_SAVE, &CRaycastingView::OnFileSave)
END_MESSAGE_MAP()

// CRaycastingView 构造/析构

CRaycastingView::CRaycastingView() noexcept
{
	// TODO: 在此处添加构造代码

}

CRaycastingView::~CRaycastingView()
{
}

BOOL CRaycastingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	return CView::PreCreateWindow(cs);
}

// CRaycastingView 绘图

void CRaycastingView::OnDraw(CDC* pDC)
{
	CRaycastingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CRect rect;//定义客户区矩形
	GetClientRect(&rect);//获得客户区的信息
	world.vp.hres = rect.Width();
	world.vp.vres = rect.Height() + 80;
	world.pDC = pDC;
	
	//w.render_scene();//正交投影
	//w.render_perspective();//透视投影

	//渲染计时器

	unsigned int time1 = ::GetTickCount();
	world.build();
	world.camera_ptr->render_scene(world);//针孔相机渲染图像
	unsigned int time2 = ::GetTickCount();

	CString tex;
	int time = (time2 - time1) / 1000;
	tex.Format(_T("%d分，%d秒"), time / 60, time % 60);
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->TextOut(0, 0, tex);
}

// CRaycastingView 打印

BOOL CRaycastingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CRaycastingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CRaycastingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CRaycastingView 诊断

#ifdef _DEBUG
void CRaycastingView::AssertValid() const
{
	CView::AssertValid();
}

void CRaycastingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRaycastingDoc* CRaycastingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRaycastingDoc)));
	return (CRaycastingDoc*)m_pDocument;
}
#endif //_DEBUG


// CRaycastingView 消息处理程序


void CRaycastingView::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码
	CRect rect;
	GetClientRect(&rect);
	//将文件保存为命名
	CFileDialog dialog(FALSE, L"Bitmap File(*.bmp)|*.bmp|All Files (*.*)|*.*||", NULL, NULL, L"Bitmap File(*.bmp)|*.bmp|All Files (*.*)|*.*||", this);
	//False指定为保存文件，.bmp指定为保存文件扩展名
	CString pathName = 0/*, fileHead, fileName*/;
	if (dialog.DoModal() == IDOK) {
		pathName = dialog.GetPathName();//获取文件名（路径）
		CImage image;
		image.Create(rect.Width(), rect.Height(), 32);//图像的长和宽
		CDC* pDC = GetDC();
		CDC dstDC;
		dstDC.CreateCompatibleDC(pDC);
		dstDC.SelectObject(image);
		dstDC.StretchBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
		image.Save(pathName);
	}
}
