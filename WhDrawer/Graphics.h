#pragma once
#include "IShapeDrawable.h"
#include "IBatchMarker.h"

/// <summary>
/// 形状绘图实现。
/// </summary>
class Graphics : public IShapeDrawable
{
public:
	//Constructor
	/// <summary>
	/// 注入一个基本绘图依赖，构造形状绘图实例。
	/// 注意：Graphics不负责基本绘图实例的构造与析构。
	/// </summary>
	/// <param name="base_graphic">指向基本绘图依赖的指针。</param>
	/// <returns></returns>
	Graphics(IBaseDrawable* p_base_graphic);

	// 通过 IShapeDrawable 继承

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

