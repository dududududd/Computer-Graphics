
// Ray castingView.h: CRaycastingView 类的接口
//

#pragma once
#include"World.h"


class CRaycastingView : public CView
{
protected: // 仅从序列化创建
	CRaycastingView() noexcept;
	DECLARE_DYNCREATE(CRaycastingView)

// 特性
public:
	CRaycastingDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CRaycastingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:World world;//世界类对象

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileSave();
};

#ifndef _DEBUG  // Ray castingView.cpp 中的调试版本
inline CRaycastingDoc* CRaycastingView::GetDocument() const
   { return reinterpret_cast<CRaycastingDoc*>(m_pDocument); }
#endif

