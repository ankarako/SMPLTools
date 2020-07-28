#include <PyHelpers.hpp>

namespace util {
/// \brief Default constructor
///	Initializes the Python Interpreter
CPyInstance::CPyInstance()
{
	Py_Initialize();
}
///	\brief Destructor
///	Destroys the python interpreter
CPyInstance::~CPyInstance()
{
	Py_Finalize();
}
/// \brief default constructor
///	Initializes PyObject pointer to null
CPyObject::CPyObject()
	: m_Ptr(nullptr)
{ }
///	\brief Construct from existing PyObject
///	\param	p	The PyObject pointer to construct from
CPyObject::CPyObject(PyObject* p)
	: m_Ptr(p)
{ }
///	\brief Destructor
///	Sets PyObject pointer to null
CPyObject::~CPyObject()
{
	Release();
}
///	\brief Get the PyObject pointer
///	\return The PyObject pointer
PyObject* CPyObject::GetObject()
{
	return m_Ptr;
}
///	\brief Set the PyObject pointer
///	\param	p	The pointer to set
///	\return	The PyObject pointer
PyObject* CPyObject::SetObject(PyObject* p)
{
	m_Ptr = p;
	return m_Ptr;
}
///	\brief add a reference to the PyObject's reference counter
///	\return The PyObject pointer
PyObject* CPyObject::AddRef()
{
	if (m_Ptr)
	{
		Py_INCREF(m_Ptr);
	}
	return m_Ptr;
}
///	\brief decrease the reference counter of the PyObject
///	Also sets the PyObject pointer to null
void CPyObject::Release()
{
	if (m_Ptr)
	{
		Py_DECREF(m_Ptr);
	}
	m_Ptr = nullptr;
}
///	\brief dereference operator
/// \return	The PyObject pointer
PyObject* CPyObject::operator->()
{
	return m_Ptr;
}
///	\brief assignment operator
///	Assign a pointer to the PyObject
///	\return The PyObject pointer
PyObject* CPyObject::operator=(PyObject* p)
{
	m_Ptr = p;
	return m_Ptr;
}
///	\brief Check if the PyObject pointer is not null
///	return true if the pointer is not null, false otherwise
CPyObject::operator bool()
{
	return m_Ptr ? true : false;
}
}	///	!namespace util