#pragma once
#include "IShapeDrawable.h"
#include "IBatchMarker.h"

/// <summary>
/// ��״��ͼʵ�֡�
/// </summary>
class Graphics : public IShapeDrawable
{
public:
	//Constructor
	/// <summary>
	/// ע��һ��������ͼ������������״��ͼʵ����
	/// ע�⣺Graphics�����������ͼʵ���Ĺ�����������
	/// </summary>
	/// <param name="base_graphic">ָ�������ͼ������ָ�롣</param>
	/// <returns></returns>
	Graphics(IBaseDrawable* p_base_graphic);

	// ͨ�� IShapeDrawable �̳�

	inline virtual const size_t Rows() override { return pBaseGraphic->Rows(); }
	inline virtual const size_t Cols() override { return pBaseGraphic->Cols(); }
	inline virtual void DrawPixel(int x, int y, Color color) override { pBaseGraphic->DrawPixel(x, y, color); }
	inline virtual Color GetPixel(int x, int y) override { return pBaseGraphic->GetPixel(x, y); }
	inline virtual IBaseDrawable* BaseDrawable() override { return pBaseGraphic; }
	virtual void Line(Point p1, Point p2, const IBrush1D& brush) override;
	virtual void Polygon(Point ps[], int ps_num, const IBrush1D& brush) override;
	virtual void FillPolygon(Point ps[], int ps_num, const IBrush1D& brush) override;

private:
	IBaseDrawable* pBaseGraphic;
};

