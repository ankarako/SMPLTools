#include <Load.hpp>
#include <Config.hpp>
#include <PyHelpers.hpp>
#include <map>

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
		util::CPyObject key;
		util::CPyObject value;
		Py_ssize_t pos = 0;

		while (PyDict_Next(pResult.GetObject(), &pos, &key.GetObject(), &value.GetObject()))
	}
	return model;
}
}	///	!namespace smpl