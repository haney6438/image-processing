
// ImageProc_20210833Doc.cpp: CImageProc20210833Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProc_20210833.h"
#endif

#include "ImageProc_20210833Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProc20210833Doc

IMPLEMENT_DYNCREATE(CImageProc20210833Doc, CDocument)

BEGIN_MESSAGE_MAP(CImageProc20210833Doc, CDocument)
END_MESSAGE_MAP()


// CImageProc20210833Doc 생성/소멸

CImageProc20210833Doc::CImageProc20210833Doc() noexcept
{
	
	InputImg = NULL;
	InputImg2 = NULL;
	ResultImg = NULL;

	gResultImg = NULL;

}

CImageProc20210833Doc::~CImageProc20210833Doc()
{
	//메모리 할당된거 지운댜 그래야 정상적으로 종료가 됨
	if (InputImg != NULL)
	{
		for (int i = 0; i < ImageHeight; i++)
			free(InputImg[i]);
		free(InputImg);
	}
	if (InputImg2 != NULL)
	{
		for (int i = 0; i < ImageHeight; i++)
			free(InputImg2[i]);
		free(InputImg2);
	}
	if (ResultImg != NULL)
	{
		for (int i = 0; i < ImageHeight; i++)
			free(ResultImg[i]);
		free(ResultImg);
	}

	if (gResultImg != NULL)
	{
		for (int i = 0; i < gImageHeight; i++)
			free(gResultImg[i]);
		free(gResultImg);
	}
}

BOOL CImageProc20210833Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProc20210833Doc serialization

void CImageProc20210833Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		//ar.Write(resultImg, 256 * 256); //3주차에 한건디 흠;;
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		CFile* fp = ar.GetFile();
		if (fp->GetLength() == 256 * 256)ar.Read(inputImg, 256 * 256);
		else AfxMessageBox("256x256 크기의 파일만 사용가능합니다.");
		// TODO: 여기에 로딩 코드를 추가합니다.
		//다지우고 수정해야댐 
	}
}

#ifdef SHARED_HANDLERS

//검색처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	//void SetSearch 어쩌구
// 축소판 그림을 지원합니다.
void CImageProc20210833Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProc20210833Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProc20210833Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}
/* 살짝ㄱ봄 이런형식이어뜸
public:
	unsigned char inputImg[256][256];
	unsigned char inputImg[256][256];
	unsigned char inputImg[256][256];
*/
#endif // SHARED_HANDLERS

// CImageProc20210833Doc 진단

#ifdef _DEBUG
void CImageProc20210833Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProc20210833Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProc20210833Doc 명령

/*
void CImageProDoc::LoadImageFile(CArchive &ar)
{
	char type[16],buf[256];
	CFile *fp=ar.GetFile();
	CString fname= fp->GetFilePath();

	if(strcmp(strchr(fname,'.'),".ppm")==0|| strcmp(strchr(fname,'.'),".PPM")==0||
		strcmp(strchr(fname,'.'),".pgm")==0|| strcmp(strchr(fname,'.'),".PGM")==0)//아스키코드 찾느건 '' 문자열은 ""
	{
		ar.ReadString(type,15);

		do{
			ar.ReadString(buf,256);
		}while(buf[0]=='#');
		scanf_s(buf,"%d %d",&ImageWidth, &ImageHeight);

		do{
			ar.ReadString(buf,256);
		}while(buf[0]=='#');
		scanf_s(buf,"%d",&maxValue);

		if (strcmp(type,"P5")==0 depth=1;
		else					 depth=3;
	}
	esle if(strcmp(strchr(fname,'.'),".raw")==0|| strcmp(strchr(fname,'.'),".RAW")==0)
	{
		if(fp->GetLength()!=256*256)
		{
			AfxMessageBox("256*256 크기의 raw 파일만 사용가능합니다.");
			return;
		}

		ImageWidth=256;
		ImageHeight=256;
		depth=1;
	}

	//메모리 할당
	InputImg** (unsigned char **)malloc(ImageHeight*sizeof(unsigned char *));
	ResultImg** (unsigned char **)malloc(ImageHeight*sizeof(unsigned char *));
	for(int i=0; i<ImageHeight; i++)
	{
		InputImg[i]=(unsigned char *)malloc(ImageWidth*depth);
		ResultImg[i]=(unsigned char *)malloc(ImageWidth*depth);
	}
	//영상데이터 읽기
	for(int i=0; i<ImageHeight;i++)
		ar.Read(intputImg[i],ImageWidth*depth);
}
*/

/*void CImageProc학번view::OnPixelTwoImageAdd()
 {
 CImageProc학번Doc*pDoc=GetDocument();
 CFileDialog dlg(TRUE);

 if(dlg.DoModal()==IDOK)
 {
	return;
 }
	CFlie file;
	file.Open(dlg.GetpathName(),CFile::modeRead);
	CArchive ar(&file,CArchive::load);
	pDoc->LoadSecondImageFile(ar);
	file.Close();

	int x,y,value;
	for(y=0; y<pDoc->ImageHeight; y++)
		for(x=0; x<pDoc->ImageWidth; x++)
		{
			value;=0.3*pDoc->

int maxvalue;
char type[16], buf[256];
CFile* fp=ar.GetFile();
CStruing frame = fp->GetFilePath();


if(strcmp(strchr(frame,'.'),".ppm")==. 응 꺼져

if(imgw!=ImageWidth || imgh!=!ImageHeight || imgd!=depth)
{
	AfxMessageBox("동일한 크기의 화일만 읽어들일 수 있습니다.");
	return; 
}

//메모리할당
InputImg2=(unsigned char**)malloc(ImageHeight*sizeof(unsigned char*));
for (int i=0; i<ImageHeight; i++)
{
	InputImg2[i]=(usigned char*)malloc(ImgWidth*depth);
}
//영상데이터 읽기
	for(int i=0; i<ImageHeight;i++)
		ar.Read(intputImg[i],ImageWidth*depth);
위에 있는 부분인ㄷ듯하옵다
*/


/*뭐한느건지 몰겟;;*/
/*do {
	ar.ReadString(buf,256);
	}whille (buf[0]=='%'_;
	 

	bitmap tnemshlh bmth;
	ar.Read(HPstr)&bmth, sized(bmth);
	if (bmth.bfType != (WORD)('B'|('M'<<8))) return;

	//bitmap info header  읽기
	BITMAPINFOHEADER bih;
	ar.Read((LPSTR)za

=	*/

/* Load 어쩌구 위에 있는건가..*/
/* 
//영상 데이터 읽기
if(!sbmp)
{
	for(int i=0; i<ImageHeight; i++)
		ar.Read(InputImg[i], ImageWidth *depth);
}
else
{
//파일에서 읽어서 저장
	BYTE nu [4*3];
	int withfile;
	widthfile=(ImageWidth*8*32)/32*4; //4의 배수로 읽아들이는 부분?
	for(int j=0; j<ImageHeight; j++)
	{
		if(depth==1) //흑백
			ar.Read(InputImg[ImageHeight-1-j], ImageWidth *depth); //ImageHeight에사 1빼면 젤마지막 위치고 i빼는건.. ㄱㅡㄹ쎄요 //위아래 뒤집는거
		else //컬러
		{
			for(int i=0;i<ImageWidth; i++)
			{
				BYTE r,g,b;
				ar.Read(&b, 1); ar.Read(&g, 1); ar.Read(&r, 1);

				inputImg[ImageHeight-1-j][3*i+0]=r;
				inputImg[ImageHeight-1-j][3*i+1]=g;
				inputImg[ImageHeight-1-j][3*i+2]=b;
			}
		}

		if((widthfile- ImageWidth)!=0)
		{
			ar.Read(nu,(widthfile- ImageWidth)*depth);
		}
	}
}
*/

/*loadsecond file수정.. 애초에 이걸 안해둠;;*/
/*


*/