#include <Load.hpp>
#include <Config.hpp>
#include <PyHelpers.hpp>

namespace smpl {
namespace detail {
///	The path to the python module for loading pickle files
static constexpr const char* k_LoadPicklePath = SMPLTOOLS_RESOURCES_DIR"/Python";
///	\brief Copy a python list of list, in which the underlying list is a list of 3 unsigned integers
///	\param		pyList			The PyObject that represents the list of lists
///	\param[out]	nativeVector	The vector to place the copied data
void LoadList3ui(PyObject* pyList, std::vector<Vector3ui>& nativeVector)
{
	if (PyList_Check(pyList))
	{
		nativeVector = std::vector<Vector3ui>(size_t(PyList_Size(pyList)));

		for (unsigned int fpos = 0; fpos < nativeVector.size(); ++fpos)
		{
			/// The vector's components are also lists
			PyObject* face = PyList_GetItem(pyList, fpos);
			if (PyList_Check(face))
			{
				Vector3ui f;
				PyObject* x = PyList_GetItem(face, 0);
				PyObject* y = PyList_GetItem(face, 1);
				PyObject* z = PyList_GetItem(face, 2);
				f.x = PyLong_AsUnsignedLong(x);
				f.y = PyLong_AsUnsignedLong(y);
				f.z = PyLong_AsUnsignedLong(z);
				nativeVector[fpos] = f;
			}
		}
	}
}
/// \brief Copy a python list of lists, in which the underlying list is a list of 3 floats
///	\param		pyVertices		The pyobject that contains a list of lists representing the model's vertices
///	\param[out]	nativeVertices	The vector to place the vertices
void LoadList3f(PyObject* pyList, std::vector<Vector3f>& nativeVector)
{
	if (PyList_Check(pyList))
	{
		nativeVector = std::vector<Vector3f>(size_t(PyList_Size(pyList)));
		for (unsigned int vpos = 0; vpos < nativeVector.size(); ++vpos)
		{
			PyObject* vertex = PyList_GetItem(pyList, vpos);
			if (PyList_Check(vertex))
			{
				Vector3f v;
				PyObject* x = PyList_GetItem(vertex, 0);
				PyObject* y = PyList_GetItem(vertex, 1);
				PyObject* z = PyList_GetItem(vertex, 2);
				v.x = PyFloat_AsDouble(x);
				v.y = PyFloat_AsDouble(y);
				v.z = PyFloat_AsDouble(z);
				nativeVector[vpos] = v;
			}
		}
	}
}

void LoadDictStrInt(PyObject* pyDict, std::map<std::string, unsigned int>& nativeMap)
{
	if (PyDict_Check(pyDict))
	{
		PyObject* key;
		PyObject* value;
		Py_ssize_t pos = 0;

		while (PyDict_Next(pyDict, &pos, &key, &value))
		{
			std::string nKey;
			unsigned int nValue;
			/// Convert Python Key to std::string
			if (PyUnicode_Check(key))
			{
				Py_ssize_t strSize = PyUnicode_GET_LENGTH(key);
				nKey = std::string(PyUnicode_AsUTF8(key));
			}
			if (PyLong_Check(value))
			{
				nValue = PyLong_AsUnsignedLong(value);
			}
			nativeMap[nKey] = nValue;
		}
	}
}
}	///	!namespace detail
///	\brief Load an SMPL model
///	\param	filepath	The filepath to load
///	\return The loaded model
Model LoadSMPL(const std::string& filepath)
{
	
	/// Initialize the python interpreter
	util::CPyInstance pyInstance;
	/// results
	Model model;

	util::CPyObject pResult;
	
	/// Workaround for importing the module
	PyRun_SimpleString("import sys");
	std::string sysAppendCommand = "sys.path.append(\"" + std::string(detail::k_LoadPicklePath) + "\")";
	PyRun_SimpleString(sysAppendCommand.c_str());
	/// !Workaround

	util::CPyObject pModuleName = PyUnicode_FromString("LoadPickle");
	util::CPyObject pModule = PyImport_Import(pModuleName.GetObject());
	if (pModule)
	{
		util::CPyObject pFunc = PyObject_GetAttrString(pModule.GetObject(), "LoadPickle");
		if (pFunc && PyCallable_Check(pFunc.GetObject()))
		{
			util::CPyObject pArgs = PyTuple_New(1);
			util::CPyObject pValue = PyUnicode_FromString(filepath.c_str());
			PyTuple_SetItem(pArgs.GetObject(), 0, pValue.GetObject());
			pResult = PyObject_CallObject(pFunc.GetObject(), pArgs.GetObject());
		}
	}
	/// Convertt returned dicitonary
	if (pResult && PyDict_Check(pResult.GetObject()))
	{
		PyObject* key;
		PyObject* value;
		Py_ssize_t pos = 0;

		while (PyDict_Next(pResult.GetObject(), &pos, &key, &value))
		{
			std::string nKey;
			/// Convert Python Key to std::string
			if (PyUnicode_Check(key))
			{
				Py_ssize_t strSize = PyUnicode_GET_LENGTH(key);
				nKey = std::string(PyUnicode_AsUTF8(key));
			}

			/// Get the faces
			if (nKey == "Faces")
			{
				detail::LoadList3ui(value, model.Faces);
			}
			/// Get Vertices
			if (nKey == "Vertices")
			{
				detail::LoadList3f(value, model.Vertices);
			}
			/// Get Joint Positions
			if (nKey == "JointNames")
			{
				detail::LoadDictStrInt(value, model.JointNames);
			}
		}
	}
	return model;
}
}	///	!namespace smpl