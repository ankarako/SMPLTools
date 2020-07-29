#include <Load.hpp>
#include <Config.hpp>
#include <PyHelpers.hpp>

namespace smpl {
namespace detail {
///	The path to the python module for loading pickle files
static constexpr const char* k_LoadPicklePath = SMPLTOOLS_RESOURCES_DIR"/Python";
}	///	!namespace detail
///	\brief Load an SMPL model
///	\param	filepath	The filepath to load
///	\return The loaded model
SMPLModel LoadSMPLX(const std::string& filepath)
{
	
	/// Initialize the python interpreter
	util::CPyInstance pyInstance;
	/// results
	SMPLModel model;

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
				util::PyList1Vec3ui::Load(value, model.Faces);
			}
			/// Get Vertices
			if (nKey == "Vertices")
			{
				util::PyList1Vec3f::Load(value, model.Vertices);
			}
			/// Get Joint Positions
			if (nKey == "JointNames")
			{
				util::PyDictStrui::Load(value, model.JointNames);
			}
			if (nKey == "PartNames")
			{
				util::PyDictStrui::Load(value, model.PartNames);
			}
			if (nKey == "SkinningWeights")
			{
				util::PyList2d::Load(value, model.SkinningWeights);
			}
			if (nKey == "JRegressor")
			{
				util::PyList2d::Load(value, model.JRegressor);
			}
			if (nKey == "HandsComponentsL")
			{
				util::PyList2d::Load(value, model.HandsComponentsL);
			}
			if (nKey == "HandsComponentsR")
			{
				util::PyList2d::Load(value, model.HandsComponentsR);
			}
			if (nKey == "HandsCoefficientsL")
			{
				util::PyList2d::Load(value, model.HandCoefficientsL);
			}
			if (nKey == "HandsCoefficientsR")
			{
				util::PyList2d::Load(value, model.HandCoefficientsR);
			}
			if (nKey == "DynamicLMKFacesIdx")
			{
				util::PyList2ui::Load(value, model.DynamicLMKFacesIdx);
			}
			if (nKey == "DynamicLMKBaryCoords")
			{
				util::PyList2Vec3d::Load(value, model.DynamicLMKBaryCoords);
			}
			if (nKey == "HandsMeanL")
			{
				util::PyList1d::Load(value, model.HandsMeanL);
			}
			if (nKey == "HandsMeanR")
			{
				util::PyList1d::Load(value, model.HandsMeanR);
			}
			if (nKey == "ShapeDirections")
			{
				util::PyList3d::Load(value, model.ShapeDirections);
			}
			if (nKey == "LMKFacesIdx")
			{
				util::PyList1ui::Load(value, model.LMKFacesIdx);
			}
			if (nKey == "PoseDirections")
			{
				util::PyList3d::Load(value, model.PoseDirections);
			}
			if (nKey == "LMKBaryCoords")
			{
				util::PyList1Vec3d::Load(value, model.LMKBaryCoords);
			}
			if (nKey == "KinematicTree")
			{
				util::PyList2ui::Load(value, model.KinematicTree);
			}
		}
	}
	return model;
}
}	///	!namespace smpl