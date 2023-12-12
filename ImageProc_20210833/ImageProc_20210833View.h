
// ImageProc_20210833View.h: CImageProc20210833View 클래스의 인터페이스
//

#pragma once


class CImageProc20210833View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImageProc20210833View() noexcept;
	DECLARE_DYNCREATE(CImageProc20210833View)

// 특성입니다.
public:
	CImageProc20210833Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImageProc20210833View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPrintHello();
	void LoadTwoimage();
	afx_msg void OnRegionSmothing();
	//void Convolve(unsigned char** InImg, unsigned char** OutImg, int cols, int rows, float[][3] mask, int bias, int depth);
	afx_msg void OnRegonPrewitt();
	afx_msg void OnRegonSobel();
	afx_msg void OnRegonRoberts();
	afx_msg void OnRegionAverageFiltering();
	afx_msg void OnRegionMedianFiltering();
	afx_msg void OnMorphologyColorGray();
	afx_msg void OnMopologyColorGray();
	afx_msg void OnMopologyBinarization();
	afx_msg void OnMorphologyErosion();
	afx_msg void OnMorphologyOpening();
	afx_msg void OnMophologyOpening();
	afx_msg void OnMophologyDitron();
	afx_msg void OnMophologyClosing();
	void CopyResultToInput();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominInterpolation();
	afx_msg void OnGeometryZoominPixelsmall();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryZoomoutMaenSub();
	afx_msg void OnGeometryAvgFiltering();
	afx_msg void OnGeometryRotation();
	afx_msg void OnGeometryverticalflip();
	afx_msg void OnGeometrywrping();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnGeometrywarping();
	bool bAviMode;
	CString AviFileName;
	void LoadAviFile(CDC* pDC);
	afx_msg void OnOpencv();
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelTwoImageAdd();
};

#ifndef _DEBUG  // ImageProc_20210833View.cpp의 디버그 버전
inline CImageProc20210833Doc* CImageProc20210833View::GetDocument() const
   { return reinterpret_cast<CImageProc20210833Doc*>(m_pDocument); }
#endif

