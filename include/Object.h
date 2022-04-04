#ifndef __OBJECT
#define __OBJECT

#include "../include/Shader.h"
#include "../include/Texture.h"
#include "../include/Vertices.h"
#include "../include/Camera.h"
#include "../include/Resource_Loader.h"
#include "../include/Buffer.h"

#include "../OpenGL/GLM/mat4x4.hpp"
#include "../OpenGL/GLM/gtx/transform.hpp"


namespace LEti {

	class Object
	{
	private:
		bool is_3d = true;

	private:
		unsigned int vertex_array = 0;
		unsigned int buffer[2] = { 0 };

        LEti::Buffer cbuf, tcbuf;

		LEti::Texture texture;
		LEti::Vertices vertices;

		glm::mat4x4 translation_matrix, rotation_matrix, scale_matrix;
		glm::vec3 rotation_axis;
		float rotation_angle = 0.0f;

	public:
		Object();
		~Object();

	public:
		virtual void init_texture(const char* _tex_path, const float* const tex_coords, unsigned int _tex_coords_count);
		virtual void init_vertices(const float* const _coords, unsigned int _coords_count);
		virtual void init(const char* _object_name);

	protected:
		void set_texture(const char* _path);
		void set_texture_coords(const float* _tc, unsigned int _tc_count);

	public:
		virtual void draw() const;
        virtual void update(float _dt);

	public:
		void set_is_3d(bool _is_3d);

		void set_pos(float _x, float _y, float _z);
		void move(float _x, float _y, float _z);

		void set_rotation_axis(float _x, float _y, float _z);
		void set_rotation_angle(float _angle);
		void set_rotation_data(float _axis_x, float _axis_y, float _axis_z, float _angle);
		void rotate(float _angle);

		void set_scale(float _scale_x, float _scale_y, float _scale_z);
		void set_overall_scale(float _scale);

	};

}	//LEti

#endif
