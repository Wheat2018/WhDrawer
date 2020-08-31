#pragma once
#include "MatrixNd.h"
#include "VectorAlgorithm.h"

/// <summary>
/// MatrixAlgorithm的默认矩阵元素枚举方法。
/// </summary>
struct DefaultMatrixIter
{
	template<typename _Mat>
	static inline constexpr auto& At(_Mat& container, int row, int col) { return container[row][col]; }

	template<typename _Mat>
	static inline constexpr size_t Rows(_Mat& container) { return container.rows; }

	template<typename _Mat>
	static inline constexpr size_t Cols(_Mat& container) { return container.cols; }
};

/// <summary>
/// 矩阵算术类。提供各类矩阵算法。
/// <para>注：使用类静态算法需提供矩阵元素枚举方法、矩阵元素类型推导方法及浮点判零方法，并且实际矩阵类需支持默认构造。</para>
/// <para>矩阵元素枚举方法：要求一个包含静态方法At(T&amp;, int)和Length(T&amp;)的类，其中T为矩阵容器类型。</para>
/// <para>矩阵元素类型推导方法：要求一个接受类型T的类型模板，其中T为矩阵容器类型，模板推导出矩阵容器的元素类型。</para>
/// <para>浮点判零方法：要求一个包含静态方法IsZero(T)的类，方法返回所给数字是否为0的布尔值。</para>
/// </summary>
/// <typeparam name="IterTy">矩阵元素枚举方法。</typeparam>
/// <typeparam name="DataTyInference">矩阵元素类型推导方法。</typeparam>
/// <typeparam name="FloatZeroJudger">浮点判零方法。</typeparam>
template<
	typename IterTy = DefaultMatrixIter,
	template<typename> typename DataTyInference = iterator_data_t,
	typename FloatZeroJudger = DefaultFloatZeroJudger
>
class MatrixAlgorithm
{
public:
	template<typename MatTy> using _DataOf = DataTyInference<MatTy>;
	using _Itr = IterTy;
	using _Mth = _Math<FloatZeroJudger>;

	//Operator
	/// <summary>
	/// 矩阵和。
	/// </summary>
	/// <typeparam name="RM">结果矩阵容器类型。</typeparam>
	/// <typeparam name="M1">矩阵1容器类型。</typeparam>
	/// <typeparam name="M2">矩阵2容器类型。</typeparam>
	/// <param name="r">结果矩阵。</param>
	/// <param name="m1">矩阵1。</param>
	/// <param name="m2">矩阵2。</param>
	/// <returns>元素对应相加结果矩阵的引用。</returns>
	template<typename RM, typename M1, typename M2> _StaIn RM& Add(RM& r, const M1& m1, const M2& m2)
	{
		Debug::Assert(_Mth::Equal(_Itr::Rows(r), _Itr::Rows(m1), _Itr::Rows(m2))
			&& _Mth::Equal(_Itr::Cols(r), _Itr::Cols(m1), _Itr::Cols(m2)),
			"MatrixAlgorithm::Add: 矩阵大小不匹配！");
		ForEach(_Add<_DataOf<RM>, _DataOf<M1>, _DataOf<M2>>, r, m1, m2);
		return r;
	}
	/// <summary>
	/// 矩阵差。
	/// </summary>
	/// <typeparam name="RM">结果矩阵容器类型。</typeparam>
	/// <typeparam name="M1">矩阵1容器类型。</typeparam>
	/// <typeparam name="M2">矩阵2容器类型。</typeparam>
	/// <param name="m1">矩阵1。</param>
	/// <param name="m2">矩阵2。</param>
	/// <returns>元素对应相减结果矩阵的引用。</returns>
	template<typename RM, typename M1, typename M2> _StaIn RM& Sub(RM& r, const M1& m1, const M2& m2)
	{
		Debug::Assert(_Mth::Equal(_Itr::Rows(r), _Itr::Rows(m1), _Itr::Rows(m2))
			&& _Mth::Equal(_Itr::Cols(r), _Itr::Cols(m1), _Itr::Cols(m2)),
			"MatrixAlgorithm::Sub: 矩阵大小不匹配！");
		ForEach(_Sub<_DataOf<RM>, _DataOf<M1>, _DataOf<M2>>, r, m1, m2);
		return r;
	}
	/// <summary>
	/// 矩阵基本积。（哈达玛积、智能乘积、元素积）
	/// </summary>
	/// <typeparam name="RM">结果矩阵容器类型。</typeparam>
	/// <typeparam name="M1">矩阵1容器类型。</typeparam>
	/// <typeparam name="M2">矩阵2容器类型。</typeparam>
	/// <param name="m1">矩阵1。</param>
	/// <param name="m2">矩阵2。</param>
	/// <returns>元素对应相乘结果矩阵的引用。</returns>
	template<typename RM, typename M1, typename M2> _StaIn RM& Mul(RM& r, const M1& m1, const M2& m2)
	{
		Debug::Assert(_Mth::Equal(_Itr::Rows(r), _Itr::Rows(m1), _Itr::Rows(m2))
			&& _Mth::Equal(_Itr::Cols(r), _Itr::Cols(m1), _Itr::Cols(m2)),
			"MatrixAlgorithm::Mul: 矩阵大小不匹配！");
		ForEach(_Mul<_DataOf<RM>, _DataOf<M1>, _DataOf<M2>>, r, m1, m2);
		return r;
	}
	/// <summary>
	/// 矩阵商。
	/// </summary>
	/// <typeparam name="RM">结果矩阵容器类型。</typeparam>
	/// <typeparam name="M1">矩阵1容器类型。</typeparam>
	/// <typeparam name="M2">矩阵2容器类型。</typeparam>
	/// <param name="m1">矩阵1。</param>
	/// <param name="m2">矩阵2。</param>
	/// <returns>元素对应相除结果矩阵的引用。</returns>
	template<typename RM, typename M1, typename M2> _StaIn RM& Div(RM& r, const M1& m1, const M2& m2)
	{
		Debug::Assert(_Mth::Equal(_Itr::Rows(r), _Itr::Rows(m1), _Itr::Rows(m2))
			&& _Mth::Equal(_Itr::Cols(r), _Itr::Cols(m1), _Itr::Cols(m2)),
			"MatrixAlgorithm::Div: 矩阵大小不匹配！");
		ForEach(_Div<_DataOf<RM>, _DataOf<M1>, _DataOf<M2>>, r, m1, m2);
		return r;
	}

	/// <summary>
	/// 矩阵点积。（内积）
	/// </summary>
	/// <typeparam name="RM">结果矩阵容器类型。</typeparam>
	/// <typeparam name="M1">矩阵1容器类型。</typeparam>
	/// <typeparam name="M2">矩阵2容器类型。</typeparam>
	/// <param name="v1">矩阵1。</param>
	/// <param name="v2">矩阵2。</param>
	/// <returns>两矩阵行列相乘结果矩阵的引用。</returns>
	template<typename RM, typename M1, typename M2> _StaIn RM& Dot(RM& r, const M1& m1, const M2& m2)
	{
		Debug::Assert(_Mth::Equal(_Itr::Cols(m1), _Itr::Rows(m2))
			&& _Mth::Equal(_Itr::Rows(r), _Itr::Rows(m1))
			&& _Mth::Equal(_Itr::Cols(r), _Itr::Cols(m2))
			, "MatrixAlgorithm::Dot: 矩阵大小不匹配！");
		auto rows = _Itr::Rows(r);
		auto cols = _Itr::Cols(r);
		auto inner = _Itr::Cols(m1);
		decltype(_Itr::At(m1, 0, 0) * _Itr::At(m2, 0, 0)) sum = 0;
		int i, j, k;
		for (i = 0; i < rows; i++)
		{
			for (j = 0; j < cols; j++)
			{
				for (k = 0, sum = 0; k < inner; k++)
					sum += _Itr::At(m1, i, k) * _Itr::At(m2, k, j);
				_Itr::At(r, i, j) = sum;
			}
		}
		return r;
	}

	/// <summary>
	/// 矩阵转置。
	/// </summary>
	/// <typeparam name="RM">结果矩阵容器类型。</typeparam>
	/// <typeparam name="M">矩阵1容器类型。</typeparam>
	/// <param name="r">结果矩阵。</param>
	/// <param name="m">矩阵。</param>
	/// <returns>两矩阵各维度乘积的和。</returns>
	template<typename RM, typename M> _StaIn RM& T(RM& r, const M& m)
	{
		Debug::Assert(_Mth::Equal(_Itr::Rows(r), _Itr::Cols(m))
			&& _Mth::Equal(_Itr::Cols(r), _Itr::Rows(m))
			, "MatrixAlgorithm::T: 矩阵大小不匹配！");
		auto rows = _Itr::Rows(r);
		auto cols = _Itr::Cols(r);
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				_Itr::At(r, i, j) = _Itr::At(m, j, i);
		return r;
	}


	/// <summary>
	/// 同时遍历n个矩阵实例，并用n个矩阵元素调用所给方法。循环次数与第一个矩阵长度相同。
	/// 注：矩阵元素类型以iterator_data_t&lt;MatTy&gt;推导值为准，其中MatTy是矩阵容器类型。
	/// </summary>
	/// <typeparam name="MatTy">矩阵容器类型。</typeparam>
	/// <typeparam name="Func">应用方法类型。</typeparam>
	/// <typeparam name="...ArgsT">类型包。</typeparam>
	/// <param name="apply">应用方法。</param>
	/// <param name="mat">第一个矩阵。</param>
	/// <param name="...args">n-1个矩阵。</param>
	template<typename MatTy, typename Func, typename... ArgsT>
	_StaInCst void ForEach(Func apply, MatTy& mat, ArgsT&... args)
	{
		auto rows = _Itr::Rows(mat);
		auto cols = _Itr::Cols(mat);
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				apply(_Itr::At(mat, i, j), _Itr::At(args, i, j)...);
	}

	/// <summary>
	/// 同时遍历n个矩阵实例，并用n个矩阵元素调用所给方法。循环以所给范围进行。
	/// 注：矩阵元素类型以iterator_data_t&lt;MatTy&gt;推导值为准，其中MatTy是矩阵容器类型。
	/// </summary>
	/// <typeparam name="MatTy">矩阵容器类型。</typeparam>
	/// <typeparam name="Func">应用方法类型。</typeparam>
	/// <typeparam name="...ArgsT">类型包。</typeparam>
	/// <param name="row_begin">行起始索引，应不小于零。</param>
	/// <param name="row_end">行终止索引，过长或设置为负数则以矩阵列数覆盖。</param>
	/// <param name="col_begin">列起始索引，应不小于零。</param>
	/// <param name="col_end">列终止索引，过长或设置为负数则以矩阵行数覆盖。</param>
	/// <param name="apply">应用方法。</param>
	/// <param name="mat">第一个矩阵。</param>
	/// <param name="...args">n-1个矩阵。</param>
	template<typename MatTy, typename Func, typename... ArgsT>
	_StaInCst void ForEachInRange(int row_begin, int row_end, int col_begin, int col_end, Func apply, MatTy& mat, ArgsT&... args)
	{
		auto rows = _Itr::Rows(mat);
		auto cols = _Itr::Cols(mat);
		if (row_end < 0 || row_end > rows) row_end = rows;
		if (col_end < 0 || col_end > cols) col_end = cols;
		for (int i = row_begin; i < row_end; i++)
			for (int j = col_begin; j < col_end; j++)
				apply(_Itr::At(mat, i, j), _Itr::At(args, i, j)...);
	}

	/// <summary>
	/// 同时遍历n个矩阵实例，并用n个矩阵元素调用所给方法，累加方法返回值。循环次数与第一个矩阵长度相同。
	/// 注：矩阵元素类型以iterator_data_t&lt;MatTy&gt;推导值为准，其中MatTy是矩阵容器类型。返回值类型与所给方法返回值类型相同。
	/// </summary>
	/// <typeparam name="MatTy">矩阵容器类型。</typeparam>
	/// <typeparam name="Func">应用方法类型。</typeparam>
	/// <typeparam name="...ArgsT">类型包。</typeparam>
	/// <param name="apply">应用方法。</param>
	/// <param name="mat">第一个矩阵。</param>
	/// <param name="...args">n-1个矩阵。</param>
	template<typename MatTy, typename Func, typename... ArgsT>
	_StaInCst auto SumEach(Func apply, MatTy& mat, ArgsT&... args)
	{
		decltype(apply(_Itr::At(mat, 0, 0), _Itr::At(args, 0, 0)...)) sum = 0;
		auto rows = _Itr::Rows(mat);
		auto cols = _Itr::Cols(mat);
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				sum += apply(_Itr::At(mat, i, j), _Itr::At(args, i, j)...);
		return sum;
	}

	/// <summary>
	/// 同时遍历n个矩阵实例，并用n个矩阵元素调用所给方法，累加方法返回值。循环以所给范围进行。
	/// 注：矩阵元素类型以iterator_data_t&lt;MatTy&gt;推导值为准，其中MatTy是矩阵容器类型。
	/// </summary>
	/// <typeparam name="MatTy">矩阵容器类型。</typeparam>
	/// <typeparam name="Func">应用方法类型。</typeparam>
	/// <typeparam name="...ArgsT">类型包。</typeparam>
	/// <param name="begin">开始索引，应不小于零。</param>
	/// <param name="end">终止索引，过长或设置为负数则以矩阵长度覆盖。</param>
	/// <param name="apply">应用方法。</param>
	/// <param name="mat">第一个矩阵。</param>
	/// <param name="...args">n-1个矩阵。</param>
	template<typename MatTy, typename Func, typename... ArgsT>
	_StaInCst auto SumEachInRange(int row_begin, int row_end, int col_begin, int col_end, Func apply, MatTy& mat, ArgsT&... args)
	{
		decltype(apply(_Itr::At(mat, 0, 0), _Itr::At(args, 0, 0)...)) sum = 0;
		auto rows = _Itr::Rows(mat);
		auto cols = _Itr::Cols(mat);
		if (row_end < 0 || row_end > rows) row_end = rows;
		if (col_end < 0 || col_end > cols) col_end = cols;
		for (int i = row_begin; i < row_end; i++)
			for (int j = col_begin; j < col_end; j++)
				sum += apply(_Itr::At(mat, i, j), _Itr::At(args, i, j)...);
		return sum;
	}

private:
	template<typename T1, typename T2, typename T3> _StaInCst void _Add(T1& r, const T2& a, const T3& b) { r = a + b; }
	template<typename T1, typename T2, typename T3> _StaInCst void _Sub(T1& r, const T2& a, const T3& b) { r = a - b; }
	template<typename T1, typename T2, typename T3> _StaInCst void _Mul(T1& r, const T2& a, const T3& b) { r = a * b; }
	template<typename T1, typename T2, typename T3> _StaInCst void _Div(T1& r, const T2& a, const T3& b) { r = a / b; }

};

/// <summary>
/// 矩阵算术类。提供各类矩阵算法。
/// </summary>
typedef MatrixAlgorithm<> MatAlgo;
