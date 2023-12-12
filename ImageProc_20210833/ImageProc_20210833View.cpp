
// ImageProc_20210833View.cpp: CImageProc20210833View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProc_20210833.h"
#endif

#include "ImageProc_20210833Doc.h"
#include "ImageProc_20210833View.h"
#include "COpenCVDlg.h"

#include <vfw.h> //기본라이브에 포함되어있는거라 <>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProc20210833View

IMPLEMENT_DYNCREATE(CImageProc20210833View, CScrollView)

BEGIN_MESSAGE_MAP(CImageProc20210833View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageProc20210833View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PRINT_HELLO, &CImageProc20210833View::OnPrintHello)
	ON_COMMAND(ID_REGION_SMOTHING, &CImageProc20210833View::OnRegionSmothing)
	ON_COMMAND(ID_REGON_PREWITT, &CImageProc20210833View::OnRegonPrewitt)
	ON_COMMAND(ID_REGON_SOBEL, &CImageProc20210833View::OnRegonSobel)
	ON_COMMAND(ID_REGON_ROBERTS, &CImageProc20210833View::OnRegonRoberts)
	ON_COMMAND(ID_REGION_AVERAGE_FILTERING, &CImageProc20210833View::OnRegionAverageFiltering)
	ON_COMMAND(ID_REGION_MEDIAN_FILTERING, &CImageProc20210833View::OnRegionMedianFiltering)
	ON_COMMAND(ID_MORPHOLOGY_COLOR_GRAY, &CImageProc20210833View::OnMorphologyColorGray)
	ON_COMMAND(ID_MOPOLOGY_COLOR_GRAY, &CImageProc20210833View::OnMopologyColorGray)
	ON_COMMAND(ID_MOPOLOGY_BINARIZATION, &CImageProc20210833View::OnMopologyBinarization)
	ON_COMMAND(ID_MORPHOLOGY_EROSION, &CImageProc20210833View::OnMorphologyErosion)
	ON_COMMAND(ID_MORPHOLOGY_OPENING, &CImageProc20210833View::OnMorphologyOpening)
	ON_COMMAND(ID_MOPHOLOGY_OPENING, &CImageProc20210833View::OnMophologyOpening)
	ON_COMMAND(ID_MOPHOLOGY_DITRON, &CImageProc20210833View::OnMophologyDitron)
	ON_COMMAND(ID_MOPHOLOGY_CLOSING, &CImageProc20210833View::OnMophologyClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CImageProc20210833View::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_INTERPOLATION, &CImageProc20210833View::OnGeometryZoominInterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_small, &CImageProc20210833View::OnGeometryZoominPixelsmall)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CImageProc20210833View::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MAEN_SUB, &CImageProc20210833View::OnGeometryZoomoutMaenSub)
	ON_COMMAND(ID_GEOMETRY_AVG_FILTERING, &CImageProc20210833View::OnGeometryAvgFiltering)
	ON_COMMAND(ID_GEOMETRY_ROTATION, &CImageProc20210833View::OnGeometryRotation)
	ON_COMMAND(GeometryVerticalFlip, &CImageProc20210833View::OnGeometryverticalflip)
	ON_COMMAND(GeometryWrping, &CImageProc20210833View::OnGeometrywrping)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(GeometryWarping, &CImageProc20210833View::OnGeometrywarping)
	ON_COMMAND(ID_OPENCV, &CImageProc20210833View::OnOpencv)
	ON_COMMAND(ID_PIXEL_ADD, &CImageProc20210833View::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_MUL, &CImageProc20210833View::OnPixelMul)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CImageProc20210833View::OnPixelTwoImageAdd)
END_MESSAGE_MAP()

// CImageProc20210833View 생성/소멸

CImageProc20210833View::CImageProc20210833View() noexcept
{
	bAviMode = false;

}

CImageProc20210833View::~CImageProc20210833View()
{
}

BOOL CImageProc20210833View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageProc20210833View 그리기

void CImageProc20210833View::OnDraw(CDC* pDC)
{
	CImageProc20210833Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int x, y;

	if (bAviMode)
	{
		//재생
		LoadAviFile(pDC);
		bAviMode = false;
		return;
	}

	if (pDoc->InputImg != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->InputImg[y][x], pDoc->InputImg[y][x], pDoc->InputImg[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->InputImg[y][3 * x + 0], pDoc->InputImg[y][3 * x + 1], pDoc->InputImg[y][3 * x + 2]));
		}
	}
	if (pDoc->ResultImg != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->ResultImg[y][x], pDoc->ResultImg[y][x], pDoc->ResultImg[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->ResultImg[y][3 * x + 0], pDoc->ResultImg[y][3 * x + 1], pDoc->ResultImg[y][3 * x + 2]));
		}
	}

	if (pDoc->InputImg2 != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel((pDoc->ImageWidth + 20) * 2 + x, y, RGB(pDoc->InputImg2[y][x], pDoc->InputImg2[y][x], pDoc->InputImg2[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel((pDoc->ImageWidth + 20) * 2 + x, y, RGB(pDoc->InputImg2[y][3 * x + 0], pDoc->InputImg2[y][3 * x + 1], pDoc->InputImg2[y][3 * x + 2]));
		}
	}

	if (pDoc->gResultImg != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(x, pDoc->ImageWidth + 20 + y, RGB(pDoc->gResultImg[y][x], pDoc->gResultImg[y][x], pDoc->gResultImg[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->ImageHeight; y++)
				for (x = 0; x < pDoc->ImageWidth; x++)
					pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->gResultImg[y][3 * x + 0], pDoc->gResultImg[y][3 * x + 1], pDoc->gResultImg[y][3 * x + 2]));
		}
	}
}

void CImageProc20210833View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 2048;
	sizeTotal.cy = 2048;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProc20210833View 인쇄


void CImageProc20210833View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProc20210833View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProc20210833View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProc20210833View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CImageProc20210833View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageProc20210833View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageProc20210833View 진단

#ifdef _DEBUG
void CImageProc20210833View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProc20210833View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProc20210833Doc* CImageProc20210833View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProc20210833Doc)));
	return (CImageProc20210833Doc*)m_pDocument;
}
#endif //_DEBUG


// CImageProc20210833View 메시지 처리기


void CImageProc20210833View::OnPixelAdd()
{
	CImageProc20210833Doc*pDoc=GetDocument();
	if (pDoc->InputImg == NULL)	return;

	int x, y;
	int value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = pDoc->InputImg[y][x] + 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImg[y][x] = value;
			}
			else
			{
				value = pDoc->InputImg[y][3 * x + 0] + 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImg[y][3 * x + 0] = value;

				value = pDoc->InputImg[y][3 * x + 1] + 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImg[y][3 * x + 1] = value;

				value = pDoc->InputImg[y][3 * x + 2] + 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImg[y][3 * x + 2] = value;
			}

		}

	Invalidate();

}



void CImageProc20210833View::OnPixelMul()
{
	CImageProc20210833Doc* pDoc = GetDocument();

	int x, y;
	int value;

	for(y=0; y<256; y++)
		for (x = 0; x < 256; x++)
		{
			value = pDoc->InputImg[y][x] * 1.5;
			if (value > 255)	value = 255;
			else if (value < 0)	value = 0;
			pDoc->ResultImg[y][x] = value;

		}
	Invalidate();
}


void CImageProc20210833View::OnPrintHello()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}




void CImageProc20210833View::OnPixelTwoImageAdd()
{

	CFileDialog dlg(true);
	CFile file;

	if (dlg.DoModal() == IDOK)
	{
		CImageProc20210833Doc* pDoc = GetDocument();

		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);
		file.Close();

		int x, y;

		for (y = 0; y < pDoc->ImageHeight; y++)
			for (x = 0; x < pDoc->ImageWidth; x++)
			{
				if (pDoc->depth == 1)
				{
					pDoc->ResultImg[y][x] = 0.5 * pDoc->InputImg[y][x] + 0.5 * pDoc->InputImg2[y][x];
				}
				else
				{
					pDoc->ResultImg[y][3 * x + 0] = 0.5 * pDoc->InputImg[y][3 * x + 0] + 0.5 * pDoc->InputImg2[y][3 * x + 0];
					pDoc->ResultImg[y][3 * x + 1] = 0.5 * pDoc->InputImg[y][3 * x + 1] + 0.5 * pDoc->InputImg2[y][3 * x + 1];
					pDoc->ResultImg[y][3 * x + 2] = 0.5 * pDoc->InputImg[y][3 * x + 2] + 0.5 * pDoc->InputImg2[y][3 * x + 2];
				}
			}

		Invalidate();
	}

}



/*

	LoadTwoImage();

	int x,y,value;
	for(y=0; y<256; y++)
		for(x=0; x<256; x++)
		{
			value = 0.7*pDoc->InputImag[y][x]+0.3*pDoc->InputImg2[y][x]; //0.7 0.3곱한건 비율을 뭐 이렇게 섞겠다.
			if(value>255)	value=255;
			else if(value<0)	value=0;
			pDoc->ResultImg[y][x]=value;
		}

	Invalidate();

	/////// 엥 다지움 loadTwoimage()로 옮겨감
	CFileDialog dlg(TRUE); //ture 대문자 소문자 가능

	dlg.DoModal();

	if(dlg.DoModal()==IDOK)
	{
		CFile file;
		file.Open(dlg.getpathName(),CFile::modeRead);//getpathName=선택한 파일의 경로명,이름,확장자.. 다 넘기는거?
		file.Read(pDoc->InputImg2,256*256);
		file.Close();
	}

	Invalidate();
	//////////
*/


void CImageProc20210833View::LoadTwoimage()
{

	CFileDialog dlg(TRUE);
	CFile file;
	file.Open(dlg.GetPathName(), CFile::modeRead);
	file.Read(pDoc->InputImg2, 256 * 256);
	file.Close();
}

void CImageProc20210833View::OnPixelTwoImageSub()
{

	CImageProc20210833Doc* pDoc = GetDocument();
	
	LoadTwoImage();

	int x,y,value;
	for(y=0; y<256; y++)
		for(x=0; x<256; x++)
		{
			value =abs(pDoc-> InputImag[y][x]-pDoc->InputImg2[y][x];
			if(value>64)	value=255;
			else			value=0;
			if(value>255)	value=255; //여기부터 밑에두개는 꼭 필요없대 
			else if(value<0)	value=0;
			pDoc->ResultImg[y][x]=value;
		}

	Invalidate();

}

/*
void CImageProc20210833View::OnRegionSmothing()
{
	CImageProc20210833Doc* pDoc = GetDocument();

	float kernal[3][3] = { {1/9.0,1/9.0,1/9.0},
							{1/9.0,1/9.0,1/9.0},
							{1/9.0,1/9.0,1/9.0} };
	Convolve(pDoc->InputImg, pDoc->ResultImg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}

/*OnRegionSharpening()
* cimage 학번 = GetDocument();
* 
* float kernel[3][3]={0,-1,0
* -1,5,-1
* 0,-1,0}
*/


/*
void CImageProc20210833View::Convolve(unsigned char** InImg, unsigned char** OutImg, int cols, int rows, float mask[][3] , int bias, int depth)
{
	int x, y, value,i,j;
	float sum;

	for(y=1; y<rows-1; y++)
		for (x = 1; x < cols-1; x++)
		{
			sum = 0;
			for(j=0; j<3; j++)
				for (i = 0; i < 3; i++)
				{
					sum += InImg[y - 1 + j][x - 1 + i] * mask[j][i];
				}
			OutImg[y][x] = sum;
		}
}


void CImageProc20210833View::OnRegonPrewitt()
{
	float HMask[3][3] = { {-1 , -1  -1 },
						{0 , 0 , 0},
						{1 , 1 , 1 } };
	float VMask[3][3] = { {-1 , 0, 1 },
						{-1,0 , 0},
						{-1 , 0 , 1 } };

	unsigned char** Ec, **Er;
	int x, y, value;

	//메모리 할당
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->ImageHeiht; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}
	Convolve(pDoc->InputImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, HMask, 0, pDoc->depth);
	Convolve(pDoc->InputImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, VMask, 0, pDoc->depth);

	for (y=0; y<pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth*pDoc->depth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][x] = value;
			}
			else {
				value = sqrt(Er[y][3*x+0] * Er[y][3*x+0] + Ec[y][3*x+0] * Ec[y][3*x+0]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3*x+0] = value;

				value = sqrt(Er[y][3 * x + 1] * Er[y][3 * x + 1] + Ec[y][3 * x + 1] * Ec[y][3 * x + 1]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 1] = value;

				value = sqrt(Er[y][3 * x + 2] * Er[y][3 * x + 2] + Ec[y][3 * x + 2] * Ec[y][3 * x + 2]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 2] = value;

				value = sqrt(pDoc->ResultImg[y][3 * x + 0] * pDoc->ResultImg[y][3 * x + 0] +
					pDoc->ResultImg[y][3 * x + 1] * pDoc->ResultImg[y][3 * x + 1]+
					pDoc->ResultImg[y][3 * x + 2] * pDoc->ResultImg[y][3 * x + 2]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->ResultImg[y][3 * x + 0] = value;
				pDoc->ResultImg[y][3 * x + 1] = value;
				pDoc->ResultImg[y][3 * x + 2] = value;
			}
		}

	//메모리 해제
	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CImageProc20210833View::OnRegonSobel()
{
	// 다 똑같고 mask만 다르다 ppt에 있는거ㅓ 해보면 될듯 
}


void CImageProc20210833View::OnRegonRoberts()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProc20210833View::OnRegionAverageFiltering()
{
	CImageProc20210833Doc* pDoc = GetDocument();
	int x, y,i,j;
	int xcor, ycor;
	int sum, count, rsum, gsum, bsum;

	for(y=0; y<pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth==1 ) {
				sum = 0;
				count = 0;

				for (j = -2; j < 2; j++)
					for (i = -2; i <= 2; i++)
					{
						ycor = y + j;
						xcor = x + i;
						if (0 <= ycor && ycor <= pDoc->ImageHeight - 1 && 0 <= xcor && xcor <= pDoc->ImageWidth - 1)
						{
							sum += pDoc->InputImg[ycor][xcor];
							count++;
						}
					}
				pDoc->ResultImg[y][x] = sum / count;
			}
			else
			{
				rsum = gsum = bsum = 0;
				count = 0;

				for (j = -1; j < 1; j++)
					for (i = -1; i <= 1; i++)
					{
						ycor = y + j;
						xcor = x + i;
						if (0 <= ycor && ycor <= pDoc->ImageHeight - 1 && 0 <= xcor && xcor <= pDoc->ImageWidth - 1)
						{
							rsum += pDoc->InputImg[ycor][3 * xcor + 0];
							gsum += pDoc->InputImg[ycor][3 * xcor + 1];
							bsum += pDoc->InputImg[ycor][3 * xcor + 2];
							count++;
						}
					}
				pDoc->ResultImg[y][3 * x + 0] = rsum / count;
				pDoc->ResultImg[y][3 * x + 1] = gsum / count;
				pDoc->ResultImg[y][3 * x + 2] = bsum / count;

			}
		}
	Invalidate();
}


void CImageProc20210833View::OnRegionMedianFiltering()
{
	CImageProc20210833Doc* pDoc = GetDocument();
	int x, y, i, j;
	int n[9],temp;

	for(y=1; y<pDoc->ImageHeight-1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			if (pDoc->depth == 1) {
				n[0] = pDoc->InputImg[y - 1][x - 1];
				n[1] = pDoc->InputImg[y - 1][x - 0];
				n[2] = pDoc->InputImg[y - 1][x + 1];
				n[3] = pDoc->InputImg[y - 0][x - 1];
				n[4] = pDoc->InputImg[y - 0][x - 0];
				n[5] = pDoc->InputImg[y - 0][x + 1];
				n[6] = pDoc->InputImg[y - 1][x - 1];
				n[7] = pDoc->InputImg[y - 1][x - 0];
				n[8] = pDoc->InputImg[y - 1][x + 1];

				//sorting
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[i] = temp;
						}
				pDoc->ResultImg[y][x] = n[4];
			}
			else
			{
				n[0] = pDoc->InputImg[y - 1][3 * (x - 1) + 0];
				n[1] = pDoc->InputImg[y - 1][3 * (x - 0) + 0];
				n[2] = pDoc->InputImg[y - 1][3 * (x + 1) + 0];
				n[3] = pDoc->InputImg[y - 0][3 * (x - 1) + 0];
				n[4] = pDoc->InputImg[y - 0][3 * (x - 0) + 0];
				n[5] = pDoc->InputImg[y - 0][3 * (x + 1) + 0];
				n[6] = pDoc->InputImg[y + 1][3 * (x - 1) + 0];
				n[7] = pDoc->InputImg[y + 1][3 * (x - 0) + 0];
				n[8] = pDoc->InputImg[y + 1][3 * (x + 1) + 0];

				//sorting
for (i = 8; i > 0; i--)
for (j = 0; j < i; j++)
	if (n[j] > n[j + 1])
	{
		temp = n[j + 1];
		n[j + 1] = n[j];
		n[i] = temp;
	}
pDoc->ResultImg[y][3 * x + 0] = n[4];

n[0] = pDoc->InputImg[y - 1][3 * (x - 1) + 1];
n[1] = pDoc->InputImg[y - 1][3 * (x - 0) + 1];
n[2] = pDoc->InputImg[y - 1][3 * (x + 1) + 1];
n[3] = pDoc->InputImg[y - 0][3 * (x - 1) + 1];
n[4] = pDoc->InputImg[y - 0][3 * (x - 0) + 1];
n[5] = pDoc->InputImg[y - 0][3 * (x + 1) + 1];
n[6] = pDoc->InputImg[y + 1][3 * (x - 1) + 1];
n[7] = pDoc->InputImg[y + 1][3 * (x - 0) + 1];
n[8] = pDoc->InputImg[y + 1][3 * (x + 1) + 1];

//sorting
for (i = 8; i > 0; i--)
for (j = 0; j < i; j++)
	if (n[j] > n[j + 1])
	{
		temp = n[j + 1];
		n[j + 1] = n[j];
		n[i] = temp;
	}
pDoc->ResultImg[y][3 * x + 1] = n[4];

n[0] = pDoc->InputImg[y - 1][3 * (x - 1) + 2];
n[1] = pDoc->InputImg[y - 1][3 * (x - 0) + 2];
n[2] = pDoc->InputImg[y - 1][3 * (x + 1) + 2];
n[3] = pDoc->InputImg[y - 0][3 * (x - 1) + 2];
n[4] = pDoc->InputImg[y - 0][3 * (x - 0) + 2];
n[5] = pDoc->InputImg[y - 0][3 * (x + 1) + 2];
n[6] = pDoc->InputImg[y + 1][3 * (x - 1) + 2];
n[7] = pDoc->InputImg[y + 1][3 * (x - 0) + 2];
n[8] = pDoc->InputImg[y + 1][3 * (x + 1) + 2];

//sorting
for (i = 8; i > 0; i--)
for (j = 0; j < i; j++)
	if (n[j] > n[j + 1])
	{
		temp = n[j + 1];
		n[j + 1] = n[j];
		n[i] = temp;
	}
pDoc->ResultImg[y][3 * x + 2] = n[4];
			}

		}
		Invalidate();
}



void CImageProc20210833View::OnMopologyColorGray()
{
	CImageProc20210833Doc* pDoc = GetDocument();
	if (pDoc->depth == 1) return;

	int x, y;
	int gray;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			gray = (pDoc->InputImg[y][3 * x + 0] + pDoc->InputImg[y][3 * x + 1] + pDoc->InputImg[y][3 * x + 2]) / 3;
			pDoc->InputImg[y][3 * x + 0] = gray;
			pDoc->InputImg[y][3 * x + 1] = gray;
			pDoc->InputImg[y][3 * x + 2] = gray;
		}
	Invalidate();
}



void CImageProc20210833View::OnMopologyBinarization()
{
	CImageProc20210833Doc* pDoc = GetDocument();

	int x, y;
	int thresh = 128;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				if (pDoc->InputImg[y][x] > thresh)
					pDoc->InputImg[y][x] = 255;
				else
					pDoc->InputImg[y][x] = 0;
			}
			else
			{
				if ((pDoc->InputImg[y][3 * x + 0] + pDoc->InputImg[y][3 * x + 1] + pDoc->InputImg[y][3 * x + 2]) / 3 > thresh)
				{
					pDoc->InputImg[y][3 * x + 0] = 255;
					pDoc->InputImg[y][3 * x + 1] = 255;
					pDoc->InputImg[y][3 * x + 2] = 255;
				}
				else
				{
					pDoc->InputImg[y][3 * x + 0] = 0;
					pDoc->InputImg[y][3 * x + 1] = 0;
					pDoc->InputImg[y][3 * x + 2] = 0;
				}
			}
		}

	Invalidate();
}


void CImageProc20210833View::OnMorphologyErosion()
{
	CImageProc20210833Doc* pDoc = GetDocument();

	int x, y,i,j;
	int min,rmin,gmin,bmin = 255;

	for(y=1; y<pDoc->ImageHeight-1;y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			if (pDoc->depth==1)
			{
				min = 255;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InputImg[y + j][x + i] < min)
							min = pDoc->InputImg[y + j][x + i];
					}
				pDoc->ResultImg[y][x] = min;
			}
			else
			{
				rmin = 255; gmin = 255; bmin = 255;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InputImg[y + j][3 * (x + i) + 0] < rmin)
							rmin = pDoc->InputImg[y + j][3 * (x + i) + 0];
						if (pDoc->InputImg[y + j][3 * (x + i) + 1] < gmin)
							gmin = pDoc->InputImg[y + j][3 * (x + i) + 1];
						if (pDoc->InputImg[y + j][3 * (x + i) + 2] < bmin)
							bmin = pDoc->InputImg[y + j][3 * (x + i) + 2];
					}
				pDoc->ResultImg[y][3 * x + 0] = rmin;
				pDoc->ResultImg[y][3 * x + 1] = gmin;
				pDoc->ResultImg[y][3 * x + 2] = bmin;

			}
			
		}
	Invalidate();
}

void CImageProc20210833View::OnMophologyDitron()
{

	CImageProc20210833Doc* pDoc = GetDocument();

	int x, y, i, j;
	int max, rmax, gmax, bmax = 255;

	for (y = 1; y < pDoc->ImageHeight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			if (pDoc->depth==1)
			{
				max = 0;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InputImg[y + j][x + i] > max)
							max = pDoc->InputImg[y + j][x + i];
					}
				pDoc->ResultImg[y][x] = max;
			}
			else
			{
				rmax = 0; gmax = 0; bmax = 0;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InputImg[y + j][3 * (x + i) + 0] > rmax)
							rmax = pDoc->InputImg[y + j][3 * (x + i) + 0];
						if (pDoc->InputImg[y + j][3 * (x + i) + 1] > gmax)
							gmax = pDoc->InputImg[y + j][3 * (x + i) + 1];
						if (pDoc->InputImg[y + j][3 * (x + i) + 2] > bmax)
							bmax = pDoc->InputImg[y + j][3 * (x + i) + 2];
					}
				pDoc->ResultImg[y][3 * x + 0] = rmax;
				pDoc->ResultImg[y][3 * x + 1] = gmax;
				pDoc->ResultImg[y][3 * x + 2] = bmax;

			}

		}
	Invalidate();
}



void CImageProc20210833View::OnMophologyOpening()
{
	OnMorphologyErosion();
	//CopyResultToInput();
	OnMorphologyErosion();
	//CopyResultToInput();
	OnMorphologyErosion();
	//CopyResultToInput();

	//CopyResultToInput();
	OnMophologyDitron();
	//CopyResultToInput();
	OnMophologyDitron();
	//CopyResultToInput();
	OnMophologyDitron();
}

void CImageProc20210833View::CopyResultToInput()
{
	CImageProc20210833Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			pDoc->InputImg[y][x] = pDoc->ResultImg[y][x];
		}

}



void CImageProc20210833View::OnMophologyClosing()
{

	OnMophologyDitron();
	CopyResultToInput();
	OnMophologyDitron();
	CopyResultToInput();
	OnMophologyDitron();
	CopyResultToInput();


	CopyResultToInput();
	OnMorphologyErosion();
	CopyResultToInput();
	OnMorphologyErosion();
	CopyResultToInput();
	OnMorphologyErosion();
	
}

void CImageProc20210833View::OnGeometryZoominPixelCopy()
{
	CImageProc20210833Doc* pDoc = GetDocument();

	int x, y;

	int xscale = 3;
	int yscale = 2;

	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale;
	pDoc->gImageHeight = pDoc->ImageHeight * yscale;

	//메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}
	
	for(y=0; y<pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if(pDoc->depth==1)
				pDoc->gResultImg[y][x] = pDoc->InputImg[y/yscale][x/xscale];
			else
			{
				pDoc->gResultImg[y][3 * x + 0] = pDoc->InputImg[y / yscale][3 * (x / xscale) + 0];
				pDoc->gResultImg[y][3 * x + 0] = pDoc->InputImg[y / yscale][3 * (x / xscale) + 1];
				pDoc->gResultImg[y][3 * x + 0] = pDoc->InputImg[y / yscale][3 * (x / xscale) + 2];
			}

		}

/*
	//전방향사상
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			pDoc->gResultImg[y * yscale][x * xscale] = pDoc->InputImg[y][x];
		}
		
	Invalidate();
}*/


void CImageProc20210833View::OnGeometryZoominInterpolation()
{
	CImageProc20210833Doc* pDoc = GetDocument();

	int x, y;

	float xscale = 2.3;
	float yscale = 1.5;
	float src_x, src_y;
	float alpha, beta;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
	int E, F;

	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale + 0.5;
	pDoc->gImageHeight = pDoc->ImageHeight * yscale + 0.5;

	//메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			src_x = x / xscale;
			src_y = y / yscale;
			alpha = src_x - (int)src_x;
			beta = src_y - (int)src_y;

			Ax = (int)src_x;
			Ay = (int)src_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ay + 1;
			Dy = Ay + 1;


			if(Bx<pDoc>iame) //5장 보간법 확대
			E = (1 - alpha) * pDoc->InputImg[Ay][Ax] + alpha * pDoc->InputImg[By][Bx];
			F = (1 - alpha) * pDoc->InputImg[Cy][Cx] + alpha * pDoc->InputImg[By][Bx];
			

			pDoc -> gResultImg[y][x] = (1 - beta) * E + beta * F;
		}
	Invalidate();
}


void CImageProc20210833View::OnGeometryZoomoutSubsampling()
{

	CImageProc20210833Doc* pDoc = GetDocument();

	int xscale = 3;		//1/3
	int yscale = 2;		//1/2
	int x, y;

	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;
	//메모리 할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i]= (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}
	//역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->ResultImg[y][x] = pDoc->InputImg[y * yscale][x * xscale];
			else
			{
				pDoc->ResultImg[y][3 * x + 0] = pDoc->InputImg[y * yscale][3 * (x * xscale) + 0];
				pDoc->ResultImg[y][3 * x + 1] = pDoc->InputImg[y * yscale][3 * (x * xscale) + 1];
				pDoc->ResultImg[y][3 * x + 2] = pDoc->InputImg[y * yscale][3 * (x * xscale) + 2];
			}

		}
	Invalidate();
}


void CImageProc20210833View::OnGeometryZoomoutMaenSub()
{
	OnRegionSmothing();
	CopyResultToInput();
	OnGeometryZoomoutMaenSub();
}


void CImageProc20210833View::OnGeometryAvgFiltering()
{


	CImageProc20210833Doc* pDoc = GetDocument();

	int xscale = 3;		//1/3
	int yscale = 2;		//1/2
	int x, y, i, j;
	int sum;
	int src_x, src_y;

	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;
	//메모리 할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}
	//전방향 사상
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			sum = 0, 0;
			for (i = 0; i < xscale; i++)
			{
				src_x += pDoc ->< input;
			}
			
		}
	Invalidate();
}

#define PI 3.1416926521

#include "CAngleDialog.h"
void CImageProc20210833View::OnGeometryRotation()
{

	CImageProc20210833Doc* pDoc = GetDocument();
	CAngleDialog dlg;

	int angle = 30;		//degree
	float radian;
	int  Hy;
	int Cx, Cy;
	int x,y,xdiff, ydiff;
	int x_source, y_source;

	dlg.m_iAngle = angle;
	if (dlg.DoModal() == IDCANCEL) return;
	angle = dlg.m_iAngle;


	radian = PI / 180 * angle;
	//y의 마지막
	Hy = pDoc->ImageHeight - 1;
	//중심점
	Cx = pDoc->ImageWidth / 2;
	Cy = pDoc->ImageHeight / 2;

	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageHeight *fabs(cos(PI/2-radian))+pDoc->gImageWidth*fabs(cos(radian));
	pDoc->gImageHeight = pDoc->ImageHeight * fabs(cos(radian)) + pDoc->ImageWidth * fabs(cos(PI / 2 - radian));
	//메모리 할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	xdiff = (pDoc->gImageWidth - pDoc->ImageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->ImageHeight) / 2;

	for(y=-ydiff; y<pDoc->gImageHeight-ydiff; y++)
		for (x = -xdiff; x < pDoc->gImageWidth - xdiff; x++)
		{
			x_source = (Hy - x - Cx) * sin(radian) + (x - Cx) * cos(radian) + Cx;
			y_source = Hy - ((Hy - y - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy);

			if (pDoc->depth == 1)
			{
				if (x_source<0 || x_source>pDoc->ImageWidth - 1 ||
				y_source<0 || y_source>pDoc->ImageHeight - 1)
				pDoc->gResultImg[y + ydiff][x + xdiff] = 255;
			else
				pDoc->gResultImg[y+ydiff][x+xdiff]=pDoc->InputImg[y_source][x_source];

			}
			else
			{
				if (x_source<0 || x_source>pDoc->ImageWidth - 1 ||
					y_source<0 || y_source>pDoc->ImageHeight - 1)
				{
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = 255;
				}
					
				else
					pDoc->gResultImg[y + ydiff][x + xdiff] = pDoc->InputImg[y_source][x_source];
			}
			
		}
	Invalidate();
}

/* OnGeometryHolixantialFilip
{
	CImageProc20210833Doc* pDoc = GetDocument();
	int x,y;

	for(y=0; y<pDoc->ImageHeight; y++)
		for(x=0; x<pDoc->ImageWidth; x++)
		{
			if(pDoc->depth==1)
				pDoc->ResultImg[y][x]=pDoc->InputImg[y][pDoc->ImageWidth-1];
			else
			{
				pDoc->ResultImg[y][3*x+0]=pDoc->InputImg[y][3*(pDoc->ImageWidth-1-x)+0];
				pDoc->ResultImg[y][3*x+1]=pDoc->InputImg[y][3*(pDoc->ImageWidth-1-x)+1];
				pDoc->ResultImg[y][3*x+2]=pDoc->InputImg[y][3*(pDoc->ImageWidth-1-x)+2];
			}
		}
		Invalidate();	
}*/

/* 
상하대칭이동 각자 작성
*/

/*
void CImageProc20210833View::OnGeometryverticalflip()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

typedef struct
{
	int Px;
	int Py;
	int Qx;
	int Qy;
}control_line;

control_line mctrl_source = { 100,100,15.,150 };
control_line mcrl_dest = { 100,100,200,200 };
void CImageProc20210833View::OnGeometrywarping()
{
	CImageProc20210833Doc* pDoc = GetDocument();

	control_line source_lines[5] = { {100,100,150,150},
		{0,0,pDoc->ImageWidth - 1,0},{pDoc->ImageWidth - 1,0,pDoc->ImageWidth - 1,pDoc->ImageHeight - 1},
		{pDoc->ImageWidth - 1,pDoc->ImageHeight - 1,0,pDoc->ImageHeight - 1},{0,pDoc->ImageHeight - 1,0,0} };
	control_line dest_lines[5] = { {100,100,200,200},
		{0,0,pDoc->ImageWidth - 1,0},{pDoc->ImageWidth - 1,0,pDoc->ImageWidth - 1,pDoc->ImageHeight - 1},
		{pDoc->ImageWidth - 1,pDoc->ImageHeight - 1,0,pDoc->ImageHeight - 1},{0,pDoc->ImageHeight - 1,0,0} };

	int x, y;

	double u;	//수직 교차점의 위치
	double h;	//제어선으로부터 픽셀의 수의 수직 변위
	double d;	//제어선과 픽셀 사이의 거리
	double tx, ty;	//결과영상 픽셀에 대응되는 입력 영상 픽셀 사이의 변위의 합
	double xp, yp;	//각 제어선에 대해 계산된 입력 영상의 대응되는 픽셀 위치
	double weight;	//각 제어선의 가중치
	double totalweight;	//가중치의 합
	double a = 0.001;	//0가 나오는걸 막기위한 작은 숫자
	double b = 2.0;
	double p = 0.75;

	int x1,y1, x2, y2;
	int src_x1, src_y1, src_x2, src_y2;
	double src_line_length, dest_line_length;

	int num_lines = 5;	//제어선의 개수
	int line;
	int source_x, source_y;
	int last_row, last_col;

	last_col = pDoc->ImageWidth - 1;
	last_row = pDoc->ImageHeight - 1;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			tx = 0.0;
			ty = 0.0;
			totalweight = 0.0;

			for (line = 0; line < num_lines; line++)
			{
				x1 = dest_lines[line].Px;
				y1 = dest_lines[line].Py;
				x2 = dest_lines[line].Qx;
				y2 = dest_lines[line].Qy;

				dest_line_length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				u = (double)((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) /
					(double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				h = ((y - y1) * (x2 - x1) - (x - x1) * (y2 - y1)) / dest_line_length;

				if (u < 0)			d = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
				else if (u > 1)		d = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
				else				d = fabs(h);

				src_x1 = source_lines[line].Px;
				src_y1 = source_lines[line].Py;
				src_x2 = source_lines[line].Qx;
				src_y2 = source_lines[line].Qy;

				src_line_length = sqrt((src_x2 - src_x1) * (src_x2 - src_x1) + (src_y2 - src_y1) * (src_y2 - src_y1));

				xp = src_x1 + u * (src_x2 - src_x1) - h * (src_y2 - src_y1) / src_line_length;
				yp = src_y1 + u * (src_y2 - src_y1) + h * (src_x2 - src_x1) / src_line_length;

				weight = pow(pow(dest_line_length, p) / (a + d), b);

				tx += (xp - x) * weight;
				ty += (yp - y) * weight;
				totalweight += weight;
			}

			source_x = x + (tx / totalweight);
			source_y = y + (ty / totalweight);

			if (source_x < 0)			source_x = 0;
			if (source_x > last_col)	source_x = last_col;
			if (source_y < 0)			source_y = 0;
			if (source_y > last_row)	source_y = last_row;

			pDoc->ResultImg[y][x] = pDoc->InputImg[source_y][source_x];
		}
}

CPoint mpos_st, mpos_end;
void CImageProc20210833View::OnLButtonDown(UINT nFlags, CPoint point)
{
	mpos_st = point;

	CScrollView::OnLButtonDown(nFlags, point);
}



void CImageProc20210833View::OnLButtonUp(UINT nFlags, CPoint point)
{
	mpos_end = point;

	CDC* pDC = GetDC();
	CPen rpen;
	rpen.CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	pDC->SelectObject(&rpen);

	pDC->MoveTo(mpos_st);
	pDC->LineTo(mpos_end);
	ReleaseDC(pDC);

	CScrollView::OnLButtonUp(nFlags, point);
}


void CImageProc20210833View::OnGeometrywarping()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
*/

/* OnAviView()
{
	CFileDialog dlg(true,"","",OFN_HIDREADONLY|OFN_OVER\RITEPROMP,
	"Avi화일(*.avi)|*.avi|모든화일|*.*|");

	if(dlg.DoModal()==IDOK)
	{
		AviFileName=dlg.GetPathName();
		bAviMode=true;
		Invalidate();
	}
}

*/

/*
void CImageProc20210833View::LoadAviFile(CDC* pDC)
{
	PAVIFILE pavi;
	AVIFILEINFO fi;
	int stm;
	PAVISTREAM pstm = NULL;
	AVISTREAMINFO si;
	PGETFRAME pfrm = NULL;
	int frame;
	LPBITMAPINFOHEADER pbmpih;
	unsigned char* image;
	int x, y;

	AVIFileInit();
	AVIFileOpen(&pavi, AviFileName, OF_READ | OF_SHARE_DENY_NONE, NULL);
	AVIFileInfo(pavi, &fi, sizeof(AVIFILEINFO));

	for (stm = 0; stm < fi.dwStreams; stm++)
	{
		AVIFileGetStream(pavi, &pstm, 0, stm);
		AVIStreamInfo(pstm, &si, sizeof(si));
		if (si.fccType == streamtypeVIDEO)
		{
			pfrm=AVIStreamGetFrameOpen(pstm, NULL);
			for (frame = 0; frame < si.dwLength; frame++)	//si.dwLength 이 프라임수, 줄였어 다시 안줄였아 ㅋ
			{
				pbmpih=(LPBITMAPINFOHEADER)AVIStreamGetFrame(pfrm, frame);
				if (!pbmpih)		continue;

				image = (unsigned char*)((LPSTR)pbmpih + (WORD)pbmpih->biSize);

				/*
				for(y=0;y<fi.dwHeight;y++)
					for (x = 0; x < fi.dwWidth; x++)
					{
						pDC->SetPixel(x, fi.dwWidth-1-y,	//영상이 뒤집혀서 나오니까 y를 어케 바꿔줌
							RGB(image[3 * (y * fi.dwWidth + x) +2],
								image[3 * (y * fi.dwWidth + x) + 1],
								image[3 * (y * fi.dwWidth + x) + 0]));	//BGR로 받아서 0 1 2더하는거 바꿔서 RGB로 만듦
						
					}
				
				::SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, fi.dwWidth, fi.dwHeight,
					0, 0, 0, fi.dwWidth, image, (BITMAPINFO*)pbmpih, DIB_RGB_COLORS);
				Sleep(33);
			}
		}
	}

	AVIStreamGetFrameClose(pfrm);
	AVIStreamRelease(pstm);
	AVIFileRelease(pavi);
	AVIFileExit();

}
*/

void CImageProc20210833View::OnOpencv()
{
	COpenCVDlg dlg;

	dlg.DoModal();
}

/*
COpenCVDlg.cpp파일에 넣어야됨 밑에도 22
#include "opencv2/opencv.hpp"

ButtonfileSelect()
{
	CFileDialog dlg(true, "", "", OFN_HIDREACONLY | OFN_OVERWRITEPOMPT,
		"JPG화일(*.jpg) | *.jpg | 모든화일(*.*) |*.*|");

	if (dlg.DoModal() == IDOK)
	{
		cv::Mat frame;
		frame=cv::imread((LPSTR)(LPCTSTR)dlg.GetPathName(),1);

		cv::imshow("Image",frame);
		cv::waitkey(0);
	}
}
*/

/*ButtonVideo()
{
	CFileDialog dlg(true, "", "", OFN_HIDREACONLY | OFN_OVERWRITEPOMPT,
		"AVI화일(*.avi) | *.avi | 모든화일(*.*) |*.*|");

	if (dlg.DoModal() == IDOK)
	{
		cv::VideoCapture cap((LPSTR)(SPCTSTR)dlg.GetPathName());

		cv::Mat frame;
		
		while(1)
		{
			cap.read(frame);
			if (frame.empty())
				break;

			cv::imshow("Video",frame);
			if(cv::waitKey(30)=='q')
				break;
		}
		cv::destoryWindow("Video");
	}
}

/*camera()
* {
* }
*/
