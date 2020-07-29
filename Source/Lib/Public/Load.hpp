#ifndef __LIB_PUBLIC_LOAD_HPP__
#define __LIB_PUBLIC_LOAD_HPP__

#include <Model.hpp>
#include <string>

namespace smpl {
///	\brief Load an SMPL model
///	\param	filepath	The filepath to load
///	\return The loaded model
SMPLModel LoadSMPLX(const std::string& filepath);
}	///	!namespace smpl
#endif	///	!__LIB_PUBLIC_LOAD_HPP__