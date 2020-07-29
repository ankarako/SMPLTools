#ifndef __LIB_PUBLIC_SAVE_HPP__
#define __LIB_PUBLIC_SAVE_HPP__

#include <Model.hpp>
#include <string>

namespace smpl {
///	\brief Save an SMPLModel as an FBX file
///	\param	filepath	The path to save the fbx file
///	\param	model		The smpl model to save
void SaveFBX(const std::string& filepath, const SMPLModel& model);
}	///	!namespace smpl
#endif	///	!__LIB_PUBLIC_SAVE_HPP__