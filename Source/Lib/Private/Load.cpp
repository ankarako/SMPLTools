#include <Load.hpp>
#include <Config.hpp>
#include <PyHelpers.hpp>
#include <PyConvert.hpp>

namespace smpl {
namespace detail {
///	The path to the python module for loading pickle files
static constexpr const char* k_LoadPicklePath = SMPLTOOLS_RESOURCES_DIR"/Python";
}
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
				if (PyList_Check(value))
				{
					model.Faces = std::vector<Vector3ui>(size_t(PyList_Size(value)));
					printf("%i\n", model.Faces.size());
					for (unsigned int fpos = 0; fpos < model.Faces.size(); ++fpos)
					{
						/// The vector's components are also lists
						PyObject* face = PyList_GetItem(value, fpos);
						if (PyList_Check(face))
						{
							Vector3ui f;
							PyObject* x = PyList_GetItem(face, 0);
							PyObject* y = PyList_GetItem(face, 1);
							PyObject* z = PyList_GetItem(face, 2);
							f.x = PyLong_AsUnsignedLong(x);
							f.y = PyLong_AsUnsignedLong(y);
							f.z = PyLong_AsUnsignedLong(z);
							model.Faces[fpos] = f;
						}
					}
				}
			}
			/// Get Vertices
			if (nKey == "Vertices")
			{
				if (PyList_Check(value))
				{
					model.Vertices = std::vector<Vector3f>(size_t(PyList_Size(value)));
					for (unsigned int vpos = 0; vpos < model.Vertices.size(); ++vpos)
					{
						PyObject* vertex = PyList_GetItem(value, vpos);
						if (PyList_Check(vertex))
						{
							Vector3f v;
							PyObject* x = PyList_GetItem(vertex, 0);
							PyObject* y = PyList_GetItem(vertex, 1);
							PyObject* z = PyList_GetItem(vertex, 2);
							v.x = PyFloat_AsDouble(x);
							v.y = PyFloat_AsDouble(y);
							v.z = PyFloat_AsDouble(z);
							model.Vertices[vpos] = v;
						}
					}
				}
			}
			/// Get Joint Positions
			if (nKey == "Vertices")
			{
				if (PyList_Check(value))
				{
					model.Vertices = std::vector<Vector3f>(size_t(PyList_Size(value)));
					for (unsigned int vpos = 0; vpos < model.Vertices.size(); ++vpos)
					{
						PyObject* vertex = PyList_GetItem(value, vpos);
						if (PyList_Check(vertex))
						{
							Vector3f v;
							PyObject* x = PyList_GetItem(vertex, 0);
							PyObject* y = PyList_GetItem(vertex, 1);
							PyObject* z = PyList_GetItem(vertex, 2);
							v.x = PyFloat_AsDouble(x);
							v.y = PyFloat_AsDouble(y);
							v.z = PyFloat_AsDouble(z);
							model.Vertices[vpos] = v;
						}
					}
				}
			}
		}
	}
	return model;
}
}	///	!namespace smpl