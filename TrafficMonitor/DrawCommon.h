//��װ�Ļ�ͼ��
#pragma once
#include "CommonData.h"
class CDrawCommon
{
public:

	//����ģʽ
	enum class StretchMode
	{
		STRETCH,		//���죬��ı����
		FILL,			//��䣬���ı��������ü�����
		FIT			//��Ӧ������ı���������ü�
	};

	CDrawCommon();
	~CDrawCommon();

	void Create(CDC* pDC, CWnd* pMainWnd);
	void SetFont(CFont* pfont);		//���û����ı�������
	void SetDC(CDC* pDC);		//���û�ͼ��DC
	CDC* GetDC() { return m_pDC; }
	void SetBackColor(COLORREF back_color) { m_back_color = back_color; }

	void DrawWindowText(CRect rect, LPCTSTR lpszString, COLORREF color, Alignment align = Alignment::LEFT, bool draw_back_ground = false, bool multi_line = false);	//��ָ���ľ��������ڻ����ı�

	void SetDrawRect(CRect rect);		//���û�ͼ��������
	static void SetDrawRect(CDC* pDC, CRect rect);

	//����һ��λͼ
	//��ע�⣺��stretch_mode����ΪStretchMode::FILL����䣩ʱ�������û�ͼ�����������֮����Ҫ��������ͼ�Σ�
	//��Ҫ�������û�ͼ�������򣬷���ͼƬ���������޷����ƣ�
	void DrawBitmap(CBitmap& bitmap, CPoint start_point, CSize size, StretchMode stretch_mode = StretchMode::STRETCH);
	void DrawBitmap(UINT bitmap_id, CPoint start_point, CSize size, StretchMode stretch_mode = StretchMode::STRETCH);
	void DrawBitmap(HBITMAP hbitmap, CPoint start_point, CSize size, StretchMode stretch_mode = StretchMode::STRETCH);

	//��ͼƬ���쵽ָ���ߴ�(https://blog.csdn.net/sichuanpb/article/details/22986877)
	static void BitmapStretch(CImage *pImage, CImage *ResultImage, CSize size);

	void FillRect(CRect rect, COLORREF color);		//�ô�ɫ������
	void FillRectWithBackColor(CRect rect);			//ʹ�ñ���ɫ������
	void DrawRectOutLine(CRect rect, COLORREF color, int width = 1, bool dot_line = false);	//���ƾ��α߿����dot_lineΪtrue����Ϊ����

	//��ͼ�񴴽�����������ص������С��threshold��ȡֵΪ0~255��0Ϊ��ɫ��255Ϊ��ɫ����������ص���������
	//https://blog.csdn.net/tajon1226/article/details/6589180
	static void GetRegionFromImage(CRgn& rgn, CBitmap &cBitmap, int threshold);

private:
	CDC* m_pDC{};		//���ڻ�ͼ��CDC���ָ��
	CWnd* m_pMainWnd{};	//��ͼ���ڵľ��
	CFont* m_pfont{};
	COLORREF m_back_color{};

	static int GetColorBritness(COLORREF color);
};

