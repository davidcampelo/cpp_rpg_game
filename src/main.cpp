#include <iostream>
#include <array>

#include <spdlog/spdlog.h>

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <docopt/docopt.h>

#include "Input.hpp"
#include "ImGuiHelpers.hpp"

static constexpr auto WINDOW_FRAME_RATE = 60;
static constexpr auto MIN_SCALE_FACTOR = 1;
static constexpr auto MAX_SCALE_FACTOR = 5;
static constexpr auto USAGE =
  R"(RPG Game

    Usage:
          game [options]

  Options:
          -h --help         Show this screen.
          --width=WIDTH     Screen width in pixels [default: 1024].
          --height=HEIGHT   Screen height in pixels [default: 768].
          --scale=SCALE     Scaling factor [default: 2].
)";


int main(int argc, const char **argv)
{
  std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
    { std::next(argv), std::next(argv, argc) },
    true,// show help if requested
    "Game 0.5");// version string

  const auto width = args["--width"].asLong();
  const auto height = args["--height"].asLong();
  const auto scale = args["--scale"].asLong();

  if (width < 0 || height < 0 || scale < MIN_SCALE_FACTOR || scale > MAX_SCALE_FACTOR) {
    spdlog::error("Command line options are out of reasonable range.");
    for (auto const &arg : args) {
      if (arg.second.isString()) { spdlog::info("Parameter set: {}='{}'", arg.first, arg.second.asString()); }
    }
    abort();
  }


  spdlog::set_level(spdlog::level::debug);
  // Use the default logger (stdout, multi-threaded, colored)
  spdlog::info("Hello, {}!", "World");


  sf::RenderWindow window(
    sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height)), "RPG Game");
  window.setFramerateLimit(WINDOW_FRAME_RATE);
  ImGui::SFML::Init(window);

  const auto scale_factor = static_cast<float>(scale);
  ImGui::GetStyle().ScaleAllSizes(scale_factor);
  ImGui::GetIO().FontGlobalScale = scale_factor;

  constexpr std::array steps = { "The Plan",
    "Getting Started",
    "Finding Errors As Soon As Possible",
    "Handling Command Line Parameters",
    "Reading SFML Joystick States",
    "Displaying Joystick States",
    "Dealing With Game Events",
    "Reading SFML Keyboard States",
    "Reading SFML Mouse States",
    "Reading SFML Touchscreen States",
    "C++ 20 So Far",
    "Managing Game State",
    "Making Our Game Testable",
    "Making Game State Allocator Aware",
    "Add Logging To Game Engine",
    "Draw A Game Map",
    "Dialog Trees",
    "Porting From SFML To SDL" };

  std::array<bool, steps.size()> states{};


  std::vector<Game::Joystick> joySticks;


  sf::Clock deltaClock;

  bool joystickEvent{false};

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);

      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::JoystickConnected: {
        joystickEvent = true;
        break;
      }
      case sf::Event::JoystickDisconnected: {
        joystickEvent = true;
        break;
      }
      case sf::Event::JoystickButtonPressed: {
        auto &js = Game::joystickById(joySticks, event.joystickButton.joystickId);
        joystickEvent = true;
        js.buttonState[event.joystickButton.button] = true;
        break;
      }
      case sf::Event::JoystickButtonReleased: {
        auto &js = Game::joystickById(joySticks, event.joystickButton.joystickId);
        joystickEvent = true;
        js.buttonState[event.joystickButton.button] = false;
        break;
      }
      case sf::Event::JoystickMoved: {
        auto &js = Game::joystickById(joySticks, event.joystickMove.joystickId);
        joystickEvent = true;
        js.axisPosition[event.joystickMove.axis] = event.joystickMove.position;
        break;
      }

      default:
        spdlog::trace("Unhandled Event Type");
      }
    }

    ImGui::SFML::Update(window, deltaClock.restart());


    ImGui::Begin("The Plan");

    for (std::size_t index = 0; const auto &step : steps) {
      ImGui::Checkbox(fmt::format("{} : {}", index, step).c_str(), &states.at(index));
      ++index;
    }

    ImGui::End();

    ImGui::Begin("Joystick---->>");

    ImGuiHelper::Text("JS Event: {}", joystickEvent);

    if (!joySticks.empty()) {
      for (unsigned int button = 0; button < joySticks[0].buttonCount; ++button) {
        ImGuiHelper::Text("{}: {}", button, joySticks[0].buttonState[button]);
      }

      for (unsigned int axis = 0; axis < sf::Joystick::AxisCount; ++axis) {
        ImGuiHelper::Text(
          "{}: {}", Game::toString(static_cast<sf::Joystick::Axis>(axis)), joySticks[0].axisPosition[axis]);
      }
    }

    ImGui::End();

    window.clear();
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();

  return 0;
}
