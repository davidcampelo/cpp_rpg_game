#ifndef CPP_RPG_GAME_HELPERS_HPP
#define CPP_RPG_GAME_HELPERS_HPP

#include <imgui.h>
#include <string_view>
#include <fmt/format.h>

namespace ImGuiHelper {

template<typename... Param> static void Text(std::string_view format, Param && ... param)
{
  ImGui::TextUnformatted(fmt::format(format, std::forward<Param>(param)...).c_str());
}

}// namespace ImGuiHelper

#endif// CPP_RPG_GAME_HELPERS_HPP
