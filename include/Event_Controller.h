#ifndef __EVENT_CONTROLLER
#define __EVENT_CONTROLLER

#include "../OpenGL/GLEW/include/glew.h"
#include "../OpenGL/GLFW/include/glfw3.h"

#include "../Debug.h"

#include <chrono>


namespace LEti {

	class Event_Controller
	{
	private:
		static GLFWwindow* window;
		
	private:
		static float desirable_fps;
		static float time_before_update;
		static float dt;

		static unsigned int times_to_update;

		static std::chrono::time_point<std::chrono::steady_clock> current_time_point;
		static std::chrono::time_point<std::chrono::steady_clock> prev_time_point;

	private:
		static bool keys_pressed_before[GLFW_KEY_LAST + 1];

	private:

	public:
		Event_Controller() = delete;
		Event_Controller(const LEti::Event_Controller&) = delete;
		Event_Controller(Event_Controller&&) = delete;

	public:
		static void init_and_create_window(unsigned int _width, unsigned int _height, const char* _name);

	public:
		static bool window_should_close();
		static void swap_buffers();
		static void process_events();

	public:
		static void update();
		static unsigned int get_times_to_update();

		static bool is_key_down(unsigned int _key);
		static bool is_key_up(unsigned int _key);
		static bool key_was_pressed(unsigned int _key);
		static bool key_was_released(unsigned int _key);

	};

}

#endif 