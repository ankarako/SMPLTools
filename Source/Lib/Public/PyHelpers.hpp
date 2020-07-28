#ifndef __LIB_PUBLIC_PYHELPERS_HPP__
#define __LIB_PUBLIC_PYHELPERS_HPP__

#include <Python.h>

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
}	///	!namespace util
#endif	///	!__LIB_PUBLIC_PYHELPERS_HPP__