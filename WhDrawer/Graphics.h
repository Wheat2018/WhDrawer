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
	inline virtual void Clean(Color color = Color()) override { return pBaseGraphic->Clean(color); }
	inline virtual IBaseDrawable* BaseDrawable() override { return pBaseGraphic; }
	inline virtual void SetDefaultColor(Color color) override { defaultColor = color; }
	virtual void DrawLine(Point p1, Point p2, IBrush1D * brush) override;
	virtual void DrawPolygon(const Point ps[], int ps_num, IBrush1D * brush) override;
	virtual void FillPolygon(const Point ps[], int ps_num, IBrush2D * brush) override;

private:
	IBaseDrawable* pBaseGraphic;
	Color defaultColor;

};

