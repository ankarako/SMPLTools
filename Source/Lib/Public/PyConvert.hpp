#ifndef __LIB_PUBLIC_PYCONVERT_HPP__
#define __LIB_PUBLIC_PYCONVERT_HPP__

#include <Python.h>
#include <cassert>
#include <climits>

#include <functional>
#include <memory>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <typeinfo>

#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

namespace util {
/// FromTuple and FromDict are used to build cutsom and complex objects
/// based on dicts or classes
/// Syntax:
///    CppBuilder<FromTuple<MyClass, accessors' types...>>
///    CppBuilder<FromDict<MyClass, accessors' types...>>
///	\struct FromTuple
///	\tparam	OBJ
///	\tparam	Args
template <typename OBJ, typename... Args> 
struct FromTuple { };
///	\struct FromDict
///	\tparam	OBJ
///	\tparam	Args
template <typename OBJ, typename... Args>
struct FromDict { };
/// \struct CppBuilder
/// CppBuilder<T> implements the following methods:
/// * bool operator() (PyObject*): build the C++ object <T> corresponding to PyObject*
/// * bool eligible(PyObject*)   : true if the PyObject is eligible to build the object type
///                                equivalent to CppBuilder does not throw std::invalid_argument for that PyObject
template <typename T>
struct CppBuilder;
///
///	Internal Structures
///
template <typename T>
struct ToBuildable : T { };
///	\struct CppBuilder
///	Identity builder
template <>
struct CppBuilder<PyObject*>
{
	typedef PyObject* ValueType;
	
	ValueType operator() (PyObject* py) const
	{
		assert(py);
		return py;
	}

	bool Eligible(PyObject* py) const
	{
		return true;
	}
};
///	\struct ToBuildable
///	\brief Identity specialization
template <>
struct ToBuildable<PyObject*> : CppBuilder<PyObject*> { };
///========================
/// Primitive Type Builders
///========================
///	\struct CppBuilder
///	\brief bool specialization
template <>
struct CppBuilder<bool>
{
	typedef bool ValueType;

	ValueType operator()(PyObject* py) const
	{
		assert(py);
		if (PyBool_Check(py))
		{
			return py == Py_True;
		}
		throw std::invalid_argument("Not a PyBool Instance.");
	}

	bool Eligible(PyObject* py) const
	{
		return PyBool_Check(py);
	}
};
///	\struct CppBuilder
///	\brief int specialization
template <>
struct CppBuilder<int>
{
	typedef int ValueType;

	ValueType operator()(PyObject* py) const
	{
		assert(py);
		if (PyLong_Check(py))
		{
			long v{ PyLong_AsLong(py) };
			if (v < INT_MIN || v > INT_MAX)
			{
				throw std::overflow_error("Out of <int> boundaries");
			}
			return static_cast<int>(v);
		}
		throw std::invalid_argument("Not a PyLong Instance.");
	}

	bool Eligible(PyObject* py) const
	{
		return PyLong_Check(py);
	}
};

template <>
struct ToBuildable<int> : CppBuilder<int> { };
///	\struct CppBuilder
///	\brief unsigned int specialization
template <>
struct CppBuilder<unsigned int>
{
	typedef unsigned int ValueType;

	ValueType operator()(PyObject* py) const
	{
		assert(py);
		if (PyLong_Check(py))
		{
			unsigned long v{ PyLong_AsUnsignedLong(py) };
			if (!!PyErr_Occurred() && !!PyErr_ExceptionMatches(PyExc_OverflowError))
			{
				PyErr_Clear();
				throw std::overflow_error("Out of <unsigned int> boundaries.");
			}
			if (v > UINT_MAX)
			{
				throw std::overflow_error("Out of <unsigned int> boundaries.");
			}
			return static_cast<unsigned int>(v);
		}
		throw std::invalid_argument("Not a PyLong Instance.");
	}

	bool Eligible(PyObject* py) const
	{
		return PyLong_Check(py);
	}
};

template <>
struct ToBuildable<unsigned int> : CppBuilder<unsigned int> { };
///	\struct CppBuilder
///	\brief int specialization
template <>
struct CppBuilder<long>
{
	typedef long ValueType;

	ValueType operator()(PyObject* py) const
	{
		assert(py);
		if (PyLong_Check(py))
		{
			long v{ PyLong_AsLong(py) };
			if (v < INT_MIN || v > INT_MAX)
			{
				throw std::overflow_error("Out of <int> boundaries");
			}
			return static_cast<long>(v);
		}
		throw std::invalid_argument("Not a PyLong Instance.");
	}

	bool Eligible(PyObject* py) const
	{
		return PyLong_Check(py);
	}
};

template <>
struct ToBuildable<long> : CppBuilder<long> { };
///	\struct CppBuilder
///	\brief unsigned int specialization
template <>
struct CppBuilder<unsigned long>
{
	typedef unsigned long ValueType;

	ValueType operator()(PyObject* py) const
	{
		assert(py);
		if (PyLong_Check(py))
		{
			unsigned long v{ PyLong_AsUnsignedLong(py) };
			if (!!PyErr_Occurred() && !!PyErr_ExceptionMatches(PyExc_OverflowError))
			{
				PyErr_Clear();
				throw std::overflow_error("Out of <unsigned int> boundaries.");
			}
			if (v > UINT_MAX)
			{
				throw std::overflow_error("Out of <unsigned int> boundaries.");
			}
			return static_cast<unsigned long>(v);
		}
		throw std::invalid_argument("Not a PyLong Instance.");
	}

	bool Eligible(PyObject* py) const
	{
		return PyLong_Check(py);
	}
};

template <>
struct ToBuildable<unsigned long> : CppBuilder<unsigned long> { };
///	\struct CppBuilder
///	\brief long long specialization
template <>
struct CppBuilder<long long>
{
	typedef long long ValueType;

	ValueType operator()(PyObject* py) const
	{
		assert(py);
		if (PyLong_Check(py))
		{
			long long v{ PyLong_AsLongLong(py) };
			if (!!PyErr_Occurred() && !!PyErr_ExceptionMatches(PyExc_OverflowError))
			{
				throw std::overflow_error("Out of <long long> boundaries");
			}
			return static_cast<long long>(v);
		}
		throw std::invalid_argument("Not a PyLongLong Instance.");
	}

	bool Eligible(PyObject* py) const
	{
		return PyLong_Check(py);
	}
};

template <>
struct ToBuildable<long long> : CppBuilder<long long> { };

///	\struct CppBuilder
///	\brief long long specialization
template <>
struct CppBuilder<unsigned long long>
{
	typedef unsigned long long ValueType;

	ValueType operator()(PyObject* py) const
	{
		assert(py);
		if (PyLong_Check(py))
		{
			unsigned long long v{ PyLong_AsUnsignedLongLong(py) };
			if (!!PyErr_Occurred() && !!PyErr_ExceptionMatches(PyExc_OverflowError))
			{
				throw std::overflow_error("Out of <unsigned long long> boundaries");
			}
			return static_cast<unsigned long long>(v);
		}
		throw std::invalid_argument("Not a PyUnsignedLongLong Instance.");
	}

	bool Eligible(PyObject* py) const
	{
		return PyLong_Check(py);
	}
};

template <>
struct ToBuildable<unsigned long long> : CppBuilder<unsigned long long> { };

template <>
struct CppBuilder<double>
{
	typedef double ValueType;

	ValueType operator()(PyObject* py) const
	{
		assert(py);
		if (PyFloat_Check(py))
		{
			double v{ PyFloat_AsDouble(py) };
			if (v == INFINITY || v == -INFINITY)
			{
				PyErr_Clear();
				throw std::overflow_error("Out of <double> boundaries.");
			}
			return v;
		}
		throw std::invalid_argument("Not a PyFloat instance.");
	}

	bool Eligible(PyObject* py) const
	{
		return PyFloat_Check(py);
	}
};

template <>
struct ToBuildable<double> : CppBuilder<double> { };
///================
/// String Builders
///================
template <>
struct CppBuilder<std::string>
{
	typedef std::string ValueType;

	ValueType operator()(PyObject* py) const
	{
		assert(py);
		if (PyUnicode_Check(py))
		{
			Py_ssize_t size{ PyUnicode_GET_LENGTH(py) };
			if (size < 0)
			{
				throw std::runtime_error("Unable to retrieve Python string as string");
			}
			return std::string(PyUnicode_AsUTF8(py));
		}
		throw std::invalid_argument("Not a PyUnicode instance.");
	}

	bool Eligible(PyObject* py) const
	{
		return PyUnicode_Check(py);
	}
};

template <>
struct ToBuildable<std::string> : CppBuilder<std::string> { };
///===============
/// Vector Builder
///===============
template <typename T>
struct CppBuilder<std::vector<T>>
{
	typedef std::vector<typename ToBuildable<T>::ValueType> ValueType;

	ValueType operator()(PyObject* py) const
	{
		assert(py);

		if (PyList_Check(py))
		{
			unsigned int i{ 0 };
			ValueType v{ size_t(PyList_Size(py)) };
			for (ValueType::iterator it = v.begin(); it != v.end(); ++it, ++i)
			{
				//*it = ToBuildable<T>(PyList_GetItem(py, i));
			}
			return v;
		}
	}

	bool Eligible(PyObject* py) const
	{
		if (!PyList_Check(py))
		{
			return false;
		}
		for (Py_ssize_t i = 0; i != PyList_Size(py); ++i)
		{
			if (!ToBuildable<T>.Eligible(PyList_GetItem(py, i)))
			{
				return false;
			}
		}
		return true;
	}
};

template <typename T>
struct ToBuildable<std::vector<T>> : CppBuilder<std::vector<T>> { };
}	///	!namespace util
#endif	///	!__LIB_PUBLIC_PYCONVERT_HPP__