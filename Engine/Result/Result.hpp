#ifndef RAYCAST_RESULT_HPP
#define RAYCAST_RESULT_HPP

#include <string>

#include "BaseResult.hpp"

namespace fsanvr {

    template<typename T>
class Result : public BaseResult<T, std::string> {};

} //namespace fsanvr

#endif //RAYCAST_RESULT_HPP
