#pragma once
#include "MatrixNd.h"
#include "VectorAlgorithm.h"

/// <summary>
/// MatrixAlgorithm��Ĭ�Ͼ���Ԫ��ö�ٷ�����
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
/// ���������ࡣ�ṩ��������㷨��
/// <para>ע��ʹ���ྲ̬�㷨���ṩ����Ԫ��ö�ٷ���������Ԫ�������Ƶ��������������㷽��������ʵ�ʾ�������֧��Ĭ�Ϲ��졣</para>
/// <para>����Ԫ��ö�ٷ�����Ҫ��һ��������̬����At(T&amp;, int)��Length(T&amp;)���࣬����TΪ�����������͡�</para>
/// <para>����Ԫ�������Ƶ�������Ҫ��һ����������T������ģ�壬����TΪ�����������ͣ�ģ���Ƶ�������������Ԫ�����͡�</para>
/// <para>�������㷽����Ҫ��һ��������̬����IsZero(T)���࣬�����������������Ƿ�Ϊ0�Ĳ���ֵ��</para>
/// </summary>
/// <typeparam name="IterTy">����Ԫ��ö�ٷ�����</typeparam>
/// <typeparam name="DataTyInference">����Ԫ�������Ƶ�������</typeparam>
/// <typeparam name="FloatZeroJudger">�������㷽����</typeparam>
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
	/// ����͡�
	/// </summary>
	/// <typeparam name="RM">��������������͡�</typeparam>
	/// <typeparam name="M1">����1�������͡�</typeparam>
	/// <typeparam name="M2">����2�������͡�</typeparam>
	/// <param name="r">�������</param>
	/// <param name="m1">����1��</param>
	/// <param name="m2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ��ӽ����������á�</returns>
	template<typename RM, typename M1, typename M2> _StaIn RM& Add(RM& r, const M1& m1, const M2& m2)
	{
		Debug::Assert(_Mth::Equal(_Itr::Rows(r), _Itr::Rows(m1), _Itr::Rows(m2))
			&& _Mth::Equal(_Itr::Cols(r), _Itr::Cols(m1), _Itr::Cols(m2)),
			"MatrixAlgorithm::Add: �����С��ƥ�䣡");
		ForEach(_Add<_DataOf<RM>, _DataOf<M1>, _DataOf<M2>>, r, m1, m2);
		return r;
	}
	/// <summary>
	/// ����
	/// </summary>
	/// <typeparam name="RM">��������������͡�</typeparam>
	/// <typeparam name="M1">����1�������͡�</typeparam>
	/// <typeparam name="M2">����2�������͡�</typeparam>
	/// <param name="m1">����1��</param>
	/// <param name="m2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ��������������á�</returns>
	template<typename RM, typename M1, typename M2> _StaIn RM& Sub(RM& r, const M1& m1, const M2& m2)
	{
		Debug::Assert(_Mth::Equal(_Itr::Rows(r), _Itr::Rows(m1), _Itr::Rows(m2))
			&& _Mth::Equal(_Itr::Cols(r), _Itr::Cols(m1), _Itr::Cols(m2)),
			"MatrixAlgorithm::Sub: �����С��ƥ�䣡");
		ForEach(_Sub<_DataOf<RM>, _DataOf<M1>, _DataOf<M2>>, r, m1, m2);
		return r;
	}
	/// <summary>
	/// �������������������������ܳ˻���Ԫ�ػ���
	/// </summary>
	/// <typeparam name="RM">��������������͡�</typeparam>
	/// <typeparam name="M1">����1�������͡�</typeparam>
	/// <typeparam name="M2">����2�������͡�</typeparam>
	/// <param name="m1">����1��</param>
	/// <param name="m2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ��˽����������á�</returns>
	template<typename RM, typename M1, typename M2> _StaIn RM& Mul(RM& r, const M1& m1, const M2& m2)
	{
		Debug::Assert(_Mth::Equal(_Itr::Rows(r), _Itr::Rows(m1), _Itr::Rows(m2))
			&& _Mth::Equal(_Itr::Cols(r), _Itr::Cols(m1), _Itr::Cols(m2)),
			"MatrixAlgorithm::Mul: �����С��ƥ�䣡");
		ForEach(_Mul<_DataOf<RM>, _DataOf<M1>, _DataOf<M2>>, r, m1, m2);
		return r;
	}
	/// <summary>
	/// �����̡�
	/// </summary>
	/// <typeparam name="RM">��������������͡�</typeparam>
	/// <typeparam name="M1">����1�������͡�</typeparam>
	/// <typeparam name="M2">����2�������͡�</typeparam>
	/// <param name="m1">����1��</param>
	/// <param name="m2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ��������������á�</returns>
	template<typename RM, typename M1, typename M2> _StaIn RM& Div(RM& r, const M1& m1, const M2& m2)
	{
		Debug::Assert(_Mth::Equal(_Itr::Rows(r), _Itr::Rows(m1), _Itr::Rows(m2))
			&& _Mth::Equal(_Itr::Cols(r), _Itr::Cols(m1), _Itr::Cols(m2)),
			"MatrixAlgorithm::Div: �����С��ƥ�䣡");
		ForEach(_Div<_DataOf<RM>, _DataOf<M1>, _DataOf<M2>>, r, m1, m2);
		return r;
	}

	/// <summary>
	/// �����������ڻ���
	/// </summary>
	/// <typeparam name="RM">��������������͡�</typeparam>
	/// <typeparam name="M1">����1�������͡�</typeparam>
	/// <typeparam name="M2">����2�������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>������������˽����������á�</returns>
	template<typename RM, typename M1, typename M2> _StaIn RM& Dot(RM& r, const M1& m1, const M2& m2)
	{
		Debug::Assert(_Mth::Equal(_Itr::Cols(m1), _Itr::Rows(m2))
			&& _Mth::Equal(_Itr::Rows(r), _Itr::Rows(m1))
			&& _Mth::Equal(_Itr::Cols(r), _Itr::Cols(m2))
			, "MatrixAlgorithm::Dot: �����С��ƥ�䣡");
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
	/// ����ת�á�
	/// </summary>
	/// <typeparam name="RM">��������������͡�</typeparam>
	/// <typeparam name="M">����1�������͡�</typeparam>
	/// <param name="r">�������</param>
	/// <param name="m">����</param>
	/// <returns>�������ά�ȳ˻��ĺ͡�</returns>
	template<typename RM, typename M> _StaIn RM& T(RM& r, const M& m)
	{
		Debug::Assert(_Mth::Equal(_Itr::Rows(r), _Itr::Cols(m))
			&& _Mth::Equal(_Itr::Cols(r), _Itr::Rows(m))
			, "MatrixAlgorithm::T: �����С��ƥ�䣡");
		auto rows = _Itr::Rows(r);
		auto cols = _Itr::Cols(r);
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				_Itr::At(r, i, j) = _Itr::At(m, j, i);
		return r;
	}


	/// <summary>
	/// ͬʱ����n������ʵ��������n������Ԫ�ص�������������ѭ���������һ�����󳤶���ͬ��
	/// ע������Ԫ��������iterator_data_t&lt;MatTy&gt;�Ƶ�ֵΪ׼������MatTy�Ǿ����������͡�
	/// </summary>
	/// <typeparam name="MatTy">�����������͡�</typeparam>
	/// <typeparam name="Func">Ӧ�÷������͡�</typeparam>
	/// <typeparam name="...ArgsT">���Ͱ���</typeparam>
	/// <param name="apply">Ӧ�÷�����</param>
	/// <param name="mat">��һ������</param>
	/// <param name="...args">n-1������</param>
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
	/// ͬʱ����n������ʵ��������n������Ԫ�ص�������������ѭ����������Χ���С�
	/// ע������Ԫ��������iterator_data_t&lt;MatTy&gt;�Ƶ�ֵΪ׼������MatTy�Ǿ����������͡�
	/// </summary>
	/// <typeparam name="MatTy">�����������͡�</typeparam>
	/// <typeparam name="Func">Ӧ�÷������͡�</typeparam>
	/// <typeparam name="...ArgsT">���Ͱ���</typeparam>
	/// <param name="row_begin">����ʼ������Ӧ��С���㡣</param>
	/// <param name="row_end">����ֹ����������������Ϊ�������Ծ����������ǡ�</param>
	/// <param name="col_begin">����ʼ������Ӧ��С���㡣</param>
	/// <param name="col_end">����ֹ����������������Ϊ�������Ծ����������ǡ�</param>
	/// <param name="apply">Ӧ�÷�����</param>
	/// <param name="mat">��һ������</param>
	/// <param name="...args">n-1������</param>
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
	/// ͬʱ����n������ʵ��������n������Ԫ�ص��������������ۼӷ�������ֵ��ѭ���������һ�����󳤶���ͬ��
	/// ע������Ԫ��������iterator_data_t&lt;MatTy&gt;�Ƶ�ֵΪ׼������MatTy�Ǿ����������͡�����ֵ������������������ֵ������ͬ��
	/// </summary>
	/// <typeparam name="MatTy">�����������͡�</typeparam>
	/// <typeparam name="Func">Ӧ�÷������͡�</typeparam>
	/// <typeparam name="...ArgsT">���Ͱ���</typeparam>
	/// <param name="apply">Ӧ�÷�����</param>
	/// <param name="mat">��һ������</param>
	/// <param name="...args">n-1������</param>
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
	/// ͬʱ����n������ʵ��������n������Ԫ�ص��������������ۼӷ�������ֵ��ѭ����������Χ���С�
	/// ע������Ԫ��������iterator_data_t&lt;MatTy&gt;�Ƶ�ֵΪ׼������MatTy�Ǿ����������͡�
	/// </summary>
	/// <typeparam name="MatTy">�����������͡�</typeparam>
	/// <typeparam name="Func">Ӧ�÷������͡�</typeparam>
	/// <typeparam name="...ArgsT">���Ͱ���</typeparam>
	/// <param name="begin">��ʼ������Ӧ��С���㡣</param>
	/// <param name="end">��ֹ����������������Ϊ�������Ծ��󳤶ȸ��ǡ�</param>
	/// <param name="apply">Ӧ�÷�����</param>
	/// <param name="mat">��һ������</param>
	/// <param name="...args">n-1������</param>
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
/// ���������ࡣ�ṩ��������㷨��
/// </summary>
typedef MatrixAlgorithm<> MatAlgo;
