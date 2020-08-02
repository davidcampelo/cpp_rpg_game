

#ifndef INPUT_HPP
#define INPUT_HPP

#include <SFML/Window/Joystick.hpp>
#include <string>
#include <array>

namespace Game {

struct Joystick
{
  unsigned int id;
  std::string name;
  unsigned int buttonCount;
  std::array<bool, sf::Joystick::ButtonCount> buttonState;
  std::array<float, sf::Joystick::AxisCount> axisPosition;
};


Joystick loadJoystick(unsigned int id)
{
  const auto identification = sf::Joystick::getIdentification(id);
  Joystick js{ id, static_cast<std::string>(identification.name), sf::Joystick::getButtonCount(id), {}, {} };

  for (unsigned int button = 0; button < js.buttonCount; ++button) {
    js.buttonState[button] = sf::Joystick::isButtonPressed(js.id, button);
  }

  for (unsigned int axis = 0; axis < sf::Joystick::AxisCount; ++axis) {
    js.axisPosition[axis] = sf::Joystick::getAxisPosition(js.id, static_cast<sf::Joystick::Axis>(axis));
  }

  return js;
}

constexpr std::string_view toString(sf::Joystick::Axis axis)
{
  switch (axis) {
  case sf::Joystick::PovX:
    return "PovX";
  case sf::Joystick::PovY:
    return "PovY";
  case sf::Joystick::R:
    return "R";
  case sf::Joystick::U:
    return "U";
  case sf::Joystick::V:
    return "V";
  case sf::Joystick::X:
    return "X";
  case sf::Joystick::Y:
    return "Y";
  case sf::Joystick::Z:
    return "Z";
  default:
    break;
  }
  abort();
}

Joystick &joystickById(std::vector<Joystick> &joysticks, unsigned int id)
{
  auto joystick = std::find_if(begin(joysticks), end(joysticks), [id](const auto &j) { return j.id == id; });

  if (joystick == joysticks.end()) {
    joysticks.push_back(loadJoystick(id));
    return joysticks.back();
  } else {
    return *joystick;
  }
}

}// namespace Game
#endif// INPUT_HPP