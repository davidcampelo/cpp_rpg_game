#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <imgui.h>
#include <string_view>
#include <fmt/format.h>

namespace ImGuiHelper {

template<typename... Param> static void Text(std::string_view format, Param &&... param)
{
  ImGui::TextUnformatted(fmt::format(format, std::forward<Param>(param)...).c_str());
}

}// namespace ImGuiHelper

#endif// HELPERS_HPP
