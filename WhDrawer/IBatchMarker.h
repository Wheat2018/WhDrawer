#pragma once

/// <summary>
/// 提供批量绘图标记方法，标记绘图任务中短时间内的大量操作。
/// <para>注：在批量绘图开始到刷新之间的任何绘图操作，将不立即呈现，以此降低刷新次数，避免闪烁。</para>
/// </summary>
struct IBatchMarker
{
	/// <summary>
	/// 开始批量绘制。
	/// </summary>
	virtual void BatchBegin() = 0;

	/// <summary>
	/// 批量绘制完成。
	/// </summary>
	virtual void BatchFinished() = 0;
};