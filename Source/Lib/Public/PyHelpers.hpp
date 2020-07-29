#ifndef __LIB_PUBLIC_PYHELPERS_HPP__
#define __LIB_PUBLIC_PYHELPERS_HPP__

#include <Vector.hpp>
#include <Python.h>
#include <vector>
#include <map>
#include <string>
#include <exception>

namespace util {
///	\class CPyInstance
///	\brief An Python interpreter instance
///	\see https://www.codeproject.com/Articles/820116/Embedding-Python-program-in-a-C-Cplusplus-code
///	"RAII" object for easy initialization/termination of the python interpreter
class CPyInstance
{
public:
	/// \brief Default constructor
	///	Initializes the Python Interpreter
	CPyInstance();
	///	\brief Destructor
	///	Destroys the python interpreter
	~CPyInstance();
};	///	!class CPyInstance
/// \class CPyObject
///	\brief A wrapper around PyObject for easer instantation and destruction
///	\see https://www.codeproject.com/Articles/820116/Embedding-Python-program-in-a-C-Cplusplus-code
class CPyObject
{
public:
	/// \brief default constructor
	///	Initializes PyObject pointer to null
	CPyObject();
	///	\brief Construct from existing PyObject
	///	\param	p	The PyObject pointer to construct from
	CPyObject(PyObject* p);
	///	\brief Destructor
	///	Sets PyObject pointer to null
	~CPyObject();
	///	\brief Get the PyObject pointer
	///	\return The PyObject pointer
	PyObject* GetObject();
	///	\brief Set the PyObject pointer
	///	\param	p	The pointer to set
	///	\return	The PyObject pointer
	PyObject* SetObject(PyObject* p);
	///	\brief add a reference to the PyObject's reference counter
	///	\return The PyObject pointer
	PyObject* AddRef();
	///	\brief decrease the reference counter of the PyObject
	///	Also sets the PyObject pointer to null
	void Release();
	///	\brief dereference operator
	/// \return	The PyObject pointer
	PyObject* operator->();
	///	\brief assignment operator
	///	Assign a pointer to the PyObject
	///	\return The PyObject pointer
	PyObject* operator=(PyObject* p);
	///	\brief Check if the PyObject pointer is not null
	///	return true if the pointer is not null, false otherwise
	operator bool();
private:
	PyObject* m_Ptr;
};	///	!class CPyObject
///===================================
/// Utilities for loading Python lists
///===================================
///	\struct LoadPyList
///	\brief Utility for loading python lists
///	\tparam	Dim			The dimensionality of the list
///	\tparam	DataType	The type of the data the list holds
template <unsigned int Dim, typename DataType>
struct PyList
{
	using ValueType		= typename DataType;
	using OutputType	= std::vector<DataType>;
};
///==========================
/// Lists of Single Dimension
///==========================
///	\struct LoadPyList
///	\brief Specialization for lists of floats with one dimension
template <>
struct PyList<1, float>
{
	using ValueType		= float;
	using OutputType	= std::vector<ValueType>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, std::vector<ValueType>& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<ValueType>(size_t(PyList_Size(pyList)));
			for (unsigned int pos = 0; pos < output.size(); ++pos)
			{
				PyObject* value = PyList_GetItem(pyList, pos);
				output[pos] = static_cast<ValueType>(PyFloat_AsDouble(value));
			}
		}
	}
};	///	!struct LoadPyList
///	\struct LoadPyList
///	\brief Specialization for lists of doubles with one dimension
template <>
struct PyList<1, double>
{
	using ValueType		= double;
	using OutputType	= std::vector<ValueType>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, std::vector<ValueType>& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<ValueType>(size_t(PyList_Size(pyList)));
			for (unsigned int pos = 0; pos < output.size(); ++pos)
			{
				PyObject* value = PyList_GetItem(pyList, pos);
				output[pos] = static_cast<ValueType>(PyFloat_AsDouble(value));
			}
		}
	}
};	///	!struct LoadPyList
///	\struct LoadPyList
///	\brief Specialization for lists of longs with one dimension
template <>
struct PyList<1, long>
{
	using ValueType		= long;
	using OutputType	= std::vector<ValueType>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, std::vector<ValueType>& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<ValueType>(size_t(PyList_Size(pyList)));
			for (unsigned int pos = 0; pos < output.size(); ++pos)
			{
				PyObject* value = PyList_GetItem(pyList, pos);
				output[pos] = static_cast<ValueType>(PyLong_AsLong(value));
			}
		}
	}
};	///	!struct LoadPyList
///	\struct LoadPyList
///	\brief Specialization for lists of unsigned longs with one dimension
template <>
struct PyList<1, unsigned long>
{
	using ValueType		= unsigned long;
	using OutputType	= std::vector<ValueType>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, std::vector<ValueType>& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<ValueType>(size_t(PyList_Size(pyList)));
			for (unsigned int pos = 0; pos < output.size(); ++pos)
			{
				PyObject* value = PyList_GetItem(pyList, pos);
				output[pos] = static_cast<ValueType>(PyLong_AsUnsignedLong(value));
			}
		}
	}
};	///	!struct LoadPyList
///	\struct LoadPyList
///	\brief Specialization for lists of long longs with one dimension
template <>
struct PyList<1, long long>
{
	using ValueType		= long long;
	using OutputType	= std::vector<ValueType>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, std::vector<ValueType>& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<ValueType>(size_t(PyList_Size(pyList)));
			for (unsigned int pos = 0; pos < output.size(); ++pos)
			{
				PyObject* value = PyList_GetItem(pyList, pos);
				output[pos] = static_cast<ValueType>(PyLong_AsLongLong(value));
			}
		}
	}
};	///	!struct LoadPyList
///	\struct LoadPyList
///	\brief Specialization for lists of unsigned long longs with one dimension
template <>
struct PyList<1, unsigned long long>
{
	using ValueType		= unsigned long long;
	using OutputType	= std::vector<ValueType>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, std::vector<ValueType>& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<ValueType>(size_t(PyList_Size(pyList)));
			for (unsigned int pos = 0; pos < output.size(); ++pos)
			{
				PyObject* value = PyList_GetItem(pyList, pos);
				output[pos] = static_cast<ValueType>(PyLong_AsUnsignedLongLong(value));
			}
		}
	}
};	///	!struct LoadPyList
///	\struct LoadPyList
///	\brief Specialization for lists of ints with one dimension
template <>
struct PyList<1, int>
{
	using ValueType		= int;
	using OutputType	= std::vector<ValueType>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, std::vector<ValueType>& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<ValueType>(size_t(PyList_Size(pyList)));
			for (unsigned int pos = 0; pos < output.size(); ++pos)
			{
				PyObject* value = PyList_GetItem(pyList, pos);
				output[pos] = static_cast<ValueType>(PyLong_AsLong(value));
			}
		}
	}
};	///	!struct LoadPyList
///	\struct LoadPyList
///	\brief Specialization for lists of unsigned ints with one dimension
template <>
struct PyList<1, unsigned int>
{
	using ValueType		= unsigned int;
	using OutputType	= std::vector<ValueType>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, std::vector<ValueType>& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<ValueType>(size_t(PyList_Size(pyList)));
			for (unsigned int pos = 0; pos < output.size(); ++pos)
			{
				PyObject* value = PyList_GetItem(pyList, pos);
				output[pos] = static_cast<ValueType>(PyLong_AsUnsignedLong(value));
			}
		}
	}
};	///	!struct LoadPyList
///	\struct LoadPyList
///	\brief Specialization for lists of unsigned ints with one dimension
template <>
struct PyList<1, smpl::Vector3f>
{
	using ValueType = smpl::Vector3f;
	using OutputType = std::vector<ValueType>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, std::vector<ValueType>& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<ValueType>(size_t(PyList_Size(pyList)));
			for (unsigned int pos = 0; pos < output.size(); ++pos)
			{
				PyObject* value = PyList_GetItem(pyList, pos);
				if (PyList_Check(value))
				{
					PyObject* x = PyList_GetItem(value, 0);
					PyObject* y = PyList_GetItem(value, 1);
					PyObject* z = PyList_GetItem(value, 2);
					output[pos].x = static_cast<float>(PyFloat_AsDouble(x));
					output[pos].y = static_cast<float>(PyFloat_AsDouble(y));
					output[pos].z = static_cast<float>(PyFloat_AsDouble(z));
				}
			}
		}
	}
};	///	!struct LoadPyList
///	\struct LoadPyList
///	\brief Specialization for lists of unsigned ints with one dimension
template <>
struct PyList<1, smpl::Vector3d>
{
	using ValueType = smpl::Vector3d;
	using OutputType = std::vector<ValueType>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, std::vector<ValueType>& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<ValueType>(size_t(PyList_Size(pyList)));
			for (unsigned int pos = 0; pos < output.size(); ++pos)
			{
				PyObject* value = PyList_GetItem(pyList, pos);
				if (PyList_Check(value))
				{
					PyObject* x = PyList_GetItem(value, 0);
					PyObject* y = PyList_GetItem(value, 1);
					PyObject* z = PyList_GetItem(value, 2);
					output[pos].x = static_cast<double>(PyFloat_AsDouble(x));
					output[pos].y = static_cast<double>(PyFloat_AsDouble(y));
					output[pos].z = static_cast<double>(PyFloat_AsDouble(z));
				}
			}
		}
	}
};	///	!struct LoadPyList
///	\struct LoadPyList
///	\brief Specialization for lists of unsigned ints with one dimension
template <>
struct PyList<1, smpl::Vector3ui>
{
	using ValueType = smpl::Vector3ui;
	using OutputType = std::vector<ValueType>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, std::vector<ValueType>& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<ValueType>(size_t(PyList_Size(pyList)));
			for (unsigned int pos = 0; pos < output.size(); ++pos)
			{
				PyObject* value = PyList_GetItem(pyList, pos);
				if (PyList_Check(value))
				{
					PyObject* x = PyList_GetItem(value, 0);
					PyObject* y = PyList_GetItem(value, 1);
					PyObject* z = PyList_GetItem(value, 2);
					output[pos].x = static_cast<unsigned int>(PyLong_AsUnsignedLong(x));
					output[pos].y = static_cast<unsigned int>(PyLong_AsUnsignedLong(y));
					output[pos].z = static_cast<unsigned int>(PyLong_AsUnsignedLong(z));
					
				}
			}
		}
	}
};	///	!struct LoadPyList
///============================
/// One Dimension List Typedefs
///=============================
using PyList1f		= PyList<1, float>;
using PyList1d		= PyList<1, double>;
using PyList1l		= PyList<1, long>;
using PyList1ul		= PyList<1, unsigned long>;
using PyList1ll		= PyList<1, long long>;
using PyList1ull	= PyList<1, unsigned long long>;
using PyList1i		= PyList<1, int>;
using PyList1ui		= PyList<1, unsigned int>;
using PyList1Vec3f	= PyList<1, smpl::Vector3f>;
using PyList1Vec3d = PyList<1, smpl::Vector3d>;
using PyList1Vec3ui = PyList<1, smpl::Vector3ui>;
///========================
/// Lists of Two Dimensions
///========================
///	\struct LoadPyList
///	\brief Specialization for lists with 2 dimensions holding floats
template <>
struct PyList<2, float>
{
	using ValueType		= float;
	using OutputType	= std::vector<std::vector<ValueType>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<ValueType>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<ValueType>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						output[pos1][pos2] = static_cast<ValueType>(PyFloat_AsDouble(value));
					}
				}
			}
		}
	}
};
///	\struct LoadPyList
///	\brief Specialization for lists with 2 dimensions holding doubles
template <>
struct PyList<2, double>
{
	using ValueType = double;
	using OutputType = std::vector<std::vector<ValueType>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<ValueType>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<ValueType>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						output[pos1][pos2] = static_cast<ValueType>(PyFloat_AsDouble(value));
					}
				}
			}
		}
	}
};
///	\struct LoadPyList
///	\brief Specialization for lists with 2 dimensions holding longs
template <>
struct PyList<2, long>
{
	using ValueType = long;
	using OutputType = std::vector<std::vector<ValueType>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<ValueType>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<ValueType>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						output[pos1][pos2] = static_cast<ValueType>(PyLong_AsLong(value));
					}
				}
			}
		}
	}
};
///	\struct LoadPyList
///	\brief Specialization for lists with 2 dimensions holding unsigend longs
template <>
struct PyList<2, unsigned long>
{
	using ValueType = unsigned long;
	using OutputType = std::vector<std::vector<ValueType>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<ValueType>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<ValueType>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						output[pos1][pos2] = static_cast<ValueType>(PyLong_AsUnsignedLong(value));
					}
				}
			}
		}
	}
};
///	\struct LoadPyList
///	\brief Specialization for lists with 2 dimensions holding long longs
template <>
struct PyList<2, long long>
{
	using ValueType = long long;
	using OutputType = std::vector<std::vector<ValueType>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<ValueType>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<ValueType>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						output[pos1][pos2] = static_cast<ValueType>(PyLong_AsLongLong(value));
					}
				}
			}
		}
	}
};
///	\struct LoadPyList
///	\brief Specialization for lists with 2 dimensions holding long longs
template <>
struct PyList<2, unsigned long long>
{
	using ValueType = unsigned long long;
	using OutputType = std::vector<std::vector<ValueType>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<ValueType>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<ValueType>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						output[pos1][pos2] = static_cast<ValueType>(PyLong_AsUnsignedLongLong(value));
					}
				}
			}
		}
	}
};
///	\struct LoadPyList
///	\brief Specialization for lists with 2 dimensions holding ints
template <>
struct PyList<2, int>
{
	using ValueType = int;
	using OutputType = std::vector<std::vector<ValueType>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<ValueType>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<ValueType>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						output[pos1][pos2] = static_cast<ValueType>(PyLong_AsLong(value));
					}
				}
			}
		}
	}
};
///	\struct LoadPyList
///	\brief Specialization for lists with 2 dimensions holding ints
template <>
struct PyList<2, unsigned int>
{
	using ValueType = unsigned int;
	using OutputType = std::vector<std::vector<ValueType>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<ValueType>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<ValueType>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						output[pos1][pos2] = static_cast<ValueType>(PyLong_AsUnsignedLong(value));
					}
				}
			}
		}
	}
};
///	\struct LoadPyList
///	\brief Specialization for lists with 2 dimensions holding ints
template <>
struct PyList<2, smpl::Vector3f>
{
	using ValueType = smpl::Vector3f;
	using OutputType = std::vector<std::vector<ValueType>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<ValueType>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<ValueType>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						if (PyList_Check(value))
						{
							PyObject* x = PyList_GetItem(value, 0);
							PyObject* y = PyList_GetItem(value, 1);
							PyObject* z = PyList_GetItem(value, 2);
							output[pos1][pos2].x = static_cast<float>(PyFloat_AsDouble(x));
							output[pos1][pos2].y = static_cast<float>(PyFloat_AsDouble(y));
							output[pos1][pos2].z = static_cast<float>(PyFloat_AsDouble(z));
						}
						
					}
				}
			}
		}
	}
};
///	\struct LoadPyList
///	\brief Specialization for lists with 2 dimensions holding ints
template <>
struct PyList<2, smpl::Vector3d>
{
	using ValueType = smpl::Vector3d;
	using OutputType = std::vector<std::vector<ValueType>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<ValueType>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<ValueType>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						if (PyList_Check(value))
						{
							PyObject* x = PyList_GetItem(value, 0);
							PyObject* y = PyList_GetItem(value, 1);
							PyObject* z = PyList_GetItem(value, 2);
							output[pos1][pos2].x = static_cast<double>(PyFloat_AsDouble(x));
							output[pos1][pos2].y = static_cast<double>(PyFloat_AsDouble(y));
							output[pos1][pos2].z = static_cast<double>(PyFloat_AsDouble(z));
						}

					}
				}
			}
		}
	}
};
///	\struct LoadPyList
///	\brief Specialization for lists with 2 dimensions holding ints
template <>
struct PyList<2, smpl::Vector3ui>
{
	using ValueType = smpl::Vector3ui;
	using OutputType = std::vector<std::vector<ValueType>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<ValueType>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<ValueType>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						if (PyList_Check(value))
						{
							PyObject* x = PyList_GetItem(value, 0);
							PyObject* y = PyList_GetItem(value, 1);
							PyObject* z = PyList_GetItem(value, 2);
							output[pos1][pos2].x = static_cast<unsigned int>(PyLong_AsUnsignedLong(x));
							output[pos1][pos2].y = static_cast<unsigned int>(PyLong_AsUnsignedLong(y));
							output[pos1][pos2].z = static_cast<unsigned int>(PyLong_AsUnsignedLong(z));
						}

					}
				}
			}
		}
	}
};
///=============================
/// 2-dimensional Lists typedefs
///=============================
using PyList2f		= PyList<2, float>;
using PyList2d		= PyList<2, double>;
using PyList2l		= PyList<2, long>;
using PyList2ul		= PyList<2, unsigned long>;
using PyList2ll		= PyList<2, long long>;
using PyList2ull	= PyList<2, unsigned long long>;
using PyList2i		= PyList<2, int>;
using PyList2ui		= PyList<2, unsigned int>;
using PyList2Vec3f	= PyList<2, smpl::Vector3f>;
using PyList2Vec3d = PyList<2, smpl::Vector3d>;
using PyList2Vec3ui = PyList<2, smpl::Vector3ui>;
///=====================
/// 3-dimensional lists
///=====================
///	\struct LoadPyList
///	\brief Specialization for lists with 3 dimensions holding floats
template <>
struct PyList<3, float>
{
	using ValueType = float;
	using OutputType = std::vector<std::vector<std::vector<ValueType>>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<std::vector<ValueType>>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<std::vector<ValueType>>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						if (PyList_Check(value))
						{
							output[pos1][pos2] = std::vector<ValueType>(size_t(PyList_Size(value)));
							for (unsigned int pos3 = 0; pos3 < output[pos1][pos2].size(); ++pos3)
							{
								PyObject* val = PyList_GetItem(value, pos3);
								output[pos1][pos2][pos3] = static_cast<ValueType>(PyFloat_AsDouble(val));
							}
						}
						
					}
				}
			}
		}
	}
};
///	\struct LoadPyList
///	\brief Specialization for lists with 3 dimensions holding doubles
template <>
struct PyList<3, double>
{
	using ValueType = double;
	using OutputType = std::vector<std::vector<std::vector<ValueType>>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<std::vector<ValueType>>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<std::vector<ValueType>>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						if (PyList_Check(value))
						{
							output[pos1][pos2] = std::vector<ValueType>(size_t(PyList_Size(value)));
							for (unsigned int pos3 = 0; pos3 < output[pos1][pos2].size(); ++pos3)
							{
								PyObject* val = PyList_GetItem(value, pos3);
								output[pos1][pos2][pos3] = static_cast<ValueType>(PyFloat_AsDouble(val));
							}
						}

					}
				}
			}
		}
	}
};
///	\struct LoadPyList
///	\brief Specialization for lists with 3 dimensions holding floats
template <>
struct PyList<3, long>
{
	using ValueType = long;
	using OutputType = std::vector<std::vector<std::vector<ValueType>>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<std::vector<ValueType>>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<std::vector<ValueType>>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						if (PyList_Check(value))
						{
							output[pos1][pos2] = std::vector<ValueType>(size_t(PyList_Size(value)));
							for (unsigned int pos3 = 0; pos3 < output[pos1][pos2].size(); ++pos3)
							{
								PyObject* val = PyList_GetItem(value, pos3);
								output[pos1][pos2][pos3] = static_cast<ValueType>(PyLong_AsLong(val));
							}
						}

					}
				}
			}
		}
	}
};
///	\struct LoadPyList
///	\brief Specialization for lists with 3 dimensions holding floats
template <>
struct PyList<3, unsigned long>
{
	using ValueType = unsigned long;
	using OutputType = std::vector<std::vector<std::vector<ValueType>>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<std::vector<ValueType>>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<std::vector<ValueType>>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						if (PyList_Check(value))
						{
							output[pos1][pos2] = std::vector<ValueType>(size_t(PyList_Size(value)));
							for (unsigned int pos3 = 0; pos3 < output[pos1][pos2].size(); ++pos3)
							{
								PyObject* val = PyList_GetItem(value, pos3);
								output[pos1][pos2][pos3] = static_cast<ValueType>(PyLong_AsUnsignedLong(val));
							}
						}

					}
				}
			}
		}
	}
};
///	\struct LoadPyList
///	\brief Specialization for lists with 3 dimensions holding floats
template <>
struct PyList<3, long long>
{
	using ValueType = long long;
	using OutputType = std::vector<std::vector<std::vector<ValueType>>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<std::vector<ValueType>>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<std::vector<ValueType>>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						if (PyList_Check(value))
						{
							output[pos1][pos2] = std::vector<ValueType>(size_t(PyList_Size(value)));
							for (unsigned int pos3 = 0; pos3 < output[pos1][pos2].size(); ++pos3)
							{
								PyObject* val = PyList_GetItem(value, pos3);
								output[pos1][pos2][pos3] = static_cast<ValueType>(PyLong_AsLongLong(val));
							}
						}

					}
				}
			}
		}
	}
};
///	\struct LoadPyList
///	\brief Specialization for lists with 3 dimensions holding floats
template <>
struct PyList<3, unsigned long long>
{
	using ValueType = unsigned long long;
	using OutputType = std::vector<std::vector<std::vector<ValueType>>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<std::vector<ValueType>>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<std::vector<ValueType>>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						if (PyList_Check(value))
						{
							output[pos1][pos2] = std::vector<ValueType>(size_t(PyList_Size(value)));
							for (unsigned int pos3 = 0; pos3 < output[pos1][pos2].size(); ++pos3)
							{
								PyObject* val = PyList_GetItem(value, pos3);
								output[pos1][pos2][pos3] = static_cast<ValueType>(PyLong_AsUnsignedLongLong(val));
							}
						}

					}
				}
			}
		}
	}
};
///	\struct LoadPyList
///	\brief Specialization for lists with 3 dimensions holding floats
template <>
struct PyList<3, int>
{
	using ValueType = int;
	using OutputType = std::vector<std::vector<std::vector<ValueType>>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<std::vector<ValueType>>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<std::vector<ValueType>>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						if (PyList_Check(value))
						{
							output[pos1][pos2] = std::vector<ValueType>(size_t(PyList_Size(value)));
							for (unsigned int pos3 = 0; pos3 < output[pos1][pos2].size(); ++pos3)
							{
								PyObject* val = PyList_GetItem(value, pos3);
								output[pos1][pos2][pos3] = static_cast<ValueType>(PyLong_AsLong(val));
							}
						}

					}
				}
			}
		}
	}
};
///	\struct LoadPyList
///	\brief Specialization for lists with 3 dimensions holding floats
template <>
struct PyList<3, unsigned int>
{
	using ValueType = unsigned int;
	using OutputType = std::vector<std::vector<std::vector<ValueType>>>;
	///	\brief Load a python list of single dimension
	///	\param		pyList	The python object that represents the list
	///	\param[out]	output	The output vectpr to copy the list into
	static void Load(PyObject* pyList, OutputType& output)
	{
		if (PyList_Check(pyList))
		{
			output = std::vector<std::vector<std::vector<ValueType>>>(size_t(PyList_Size(pyList)));
			for (unsigned int pos1 = 0; pos1 < output.size(); ++pos1)
			{
				PyObject* valList = PyList_GetItem(pyList, pos1);
				if (PyList_Check(valList))
				{
					output[pos1] = std::vector<std::vector<ValueType>>(size_t(PyList_Size(valList)));
					for (unsigned int pos2 = 0; pos2 < output[pos1].size(); ++pos2)
					{
						PyObject* value = PyList_GetItem(valList, pos2);
						if (PyList_Check(value))
						{
							output[pos1][pos2] = std::vector<ValueType>(size_t(PyList_Size(value)));
							for (unsigned int pos3 = 0; pos3 < output[pos1][pos2].size(); ++pos3)
							{
								PyObject* val = PyList_GetItem(value, pos3);
								output[pos1][pos2][pos3] = static_cast<ValueType>(PyLong_AsUnsignedLong(val));
							}
						}

					}
				}
			}
		}
	}
};
///=======================
///	3-dimensional typedefs
///=======================
using PyList3f		= PyList<3, float>;
using PyList3d		= PyList<3, double>;
using PyList3l		= PyList<3, long>;
using PyList3ul		= PyList<3, unsigned long>;
using PyList3ll		= PyList<3, long long>;
using PyList3ull	= PyList<3, unsigned long long>;
using PyList3i		= PyList<3, int>;
using PyList3ui		= PyList<3, unsigned int>;
///==================
/// Dictionary Types
///==================
///	In python dictionaries can hold a very diverse amount of data
///	here we make utilities for marshalling dictionaries specific
///	to our purposes (i.e. our key types will be mostly std::strings
///	and we will specialize on the value types
///	\struct PyDict
///	\brief template does nothing
///	\tparam	KeyType		The key data type
///	\tparam	ValueType	The value data type
template <typename KType, typename VType>
struct PyDict
{
	using KeyType = KType;
	using ValueType = VType;
};
///	\struct PyDict
///	\brief Specialization for String Key Types and float values
template <>
struct PyDict<std::string, float>
{
	using KeyType	= std::string;
	using ValueType = float;
	///	\brief copy a python dictionary into an std::map<KeyType, ValueType>
	///	\param		pyDict	The python object that represents the dictionary to copy
	///	\param[out]	output	The std::map to copy the data into
	static void Load(PyObject* pyDict, std::map<KeyType, ValueType>& output)
	{
		if (PyDict_Check(pyDict))
		{
			PyObject* key;
			PyObject* value;
			Py_ssize_t pos = 0;
			while (PyDict_Next(pyDict, &pos, &key, &value))
			{
				KeyType nKey;
				ValueType nValue;
				/// Convert python key to std::string
				if (PyUnicode_Check(key))
				{
					//Py_ssize_t strSize = PyUnicode_GET_LENGTH(key);
					nKey = std::string(PyUnicode_AsUTF8(key));
				}
				if (PyFloat_Check(value))
				{
					nValue = PyFloat_AsDouble(value);
				}
				output[nKey] = nValue;
			}
		}
	}
};
///	\struct PyDict
///	\brief Specialization for String Key Types and float values
template <>
struct PyDict<std::string, unsigned int>
{
	using KeyType = std::string;
	using ValueType = unsigned int;
	///	\brief copy a python dictionary into an std::map<KeyType, ValueType>
	///	\param		pyDict	The python object that represents the dictionary to copy
	///	\param[out]	output	The std::map to copy the data into
	static void Load(PyObject* pyDict, std::map<KeyType, ValueType>& output)
	{
		if (PyDict_Check(pyDict))
		{
			PyObject* key;
			PyObject* value;
			Py_ssize_t pos = 0;
			while (PyDict_Next(pyDict, &pos, &key, &value))
			{
				KeyType nKey;
				ValueType nValue;
				/// Convert python key to std::string
				if (PyUnicode_Check(key))
				{
					//Py_ssize_t strSize = PyUnicode_GET_LENGTH(key);
					nKey = std::string(PyUnicode_AsUTF8(key));
				}
				if (PyLong_Check(value))
				{
					nValue = PyLong_AsUnsignedLong(value);
				}
				output[nKey] = nValue;
			}
		}
	}
};
///================
/// PyDict typedefs
///================
using PyDictStrf	= PyDict<std::string, float>;
using PyDictStrui	= PyDict<std::string, unsigned int>;
}	///	!namespace util
#endif	///	!__LIB_PUBLIC_PYHELPERS_HPP__