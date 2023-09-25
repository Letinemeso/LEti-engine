#include <Transformation_Data.h>

using namespace LEti;


void Transformation_Data::set_position(const glm::vec3& _position)
{
    m_changes_made = true;  //  some code duplicacy here, but who cares

    m_position = _position;
}
void Transformation_Data::move(const glm::vec3& _vec)
{
    m_changes_made = true;

    m_position += _vec;
}
void Transformation_Data::set_rotation(const glm::vec3& _rotation)
{
    m_changes_made = true;

    m_rotation = _rotation;
}
void Transformation_Data::rotate(const glm::vec3& _vec)
{
    m_changes_made = true;

    m_rotation += _vec;
}
void Transformation_Data::set_scale(const glm::vec3& _scale)
{
    m_changes_made = true;

    m_scale = _scale;
}



glm::mat4x4 Transformation_Data::translation_matrix() const
{
    glm::mat4x4 translation_matrix
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        position().x, position().y, position().z, 1.0f
    };

    return translation_matrix;
}

glm::mat4x4 Transformation_Data::rotation_matrix() const
{
    glm::mat4x4 rotation_matrix
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    for(unsigned int i=0; i<3; ++i)
    {
        glm::vec3 axis(0.0f, 0.0f, 0.0f);
        axis[i] = 1.0f;

        glm::mat4x4 rotation_around_axis = glm::rotate(rotation()[i], axis);

        rotation_matrix *= rotation_around_axis;
    }

    return rotation_matrix;
}

glm::mat4x4 Transformation_Data::scale_matrix() const
{
    glm::mat4x4 scale_matrix
    {
        scale().x, 0.0f, 0.0f, 0.0f,
        0.0f, scale().y, 0.0f, 0.0f,
        0.0f, 0.0f, scale().z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    return scale_matrix;
}



void Transformation_Data::update_matrix()
{
    if(!m_changes_made)
        return;

    m_matrix = translation_matrix() * rotation_matrix() * scale_matrix();

    m_changes_made = false;
}



glm::vec3 Transformation_Data::get_position_for_ratio(const Transformation_Data& _previous_state, const Transformation_Data& _current_state, float _ratio)
{
    L_ASSERT(_ratio > -0.0001f && _ratio < 1.0001f);

    glm::vec3 curr_pos = _current_state.position();
    glm::vec3 prev_pos = _previous_state.position();
    glm::vec3 diff = curr_pos - prev_pos;
    diff *= _ratio;

    return diff + prev_pos;
}

glm::vec3 Transformation_Data::get_rotation_for_ratio(const Transformation_Data& _previous_state, const Transformation_Data& _current_state, float _ratio)
{
    L_ASSERT(_ratio > -0.0001f && _ratio < 1.0001f);

    glm::vec3 curr_rotation = _current_state.rotation();
    glm::vec3 prev_rotation = _previous_state.rotation();
    glm::vec3 diff = curr_rotation - prev_rotation;
    diff *= _ratio;

    return diff + prev_rotation;
}

glm::vec3 Transformation_Data::get_scale_for_ratio(const Transformation_Data& _previous_state, const Transformation_Data& _current_state, float _ratio)
{
    L_ASSERT(_ratio > -0.0001f && _ratio < 1.0001f);

    glm::vec3 curr_scale = _current_state.scale();
    glm::vec3 prev_scale = _previous_state.scale();
    glm::vec3 diff = curr_scale - prev_scale;
    diff *= _ratio;

    return diff + prev_scale;
}


glm::mat4x4 Transformation_Data::get_translation_matrix_for_ratio(const Transformation_Data &_previous_state, const Transformation_Data &_current_state, float _ratio)
{
    glm::vec3 diff = get_position_for_ratio(_previous_state, _current_state, _ratio);

    glm::mat4x4 result
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        diff.x, diff.y, diff.z, 1.0f
    };

    return result;
}

glm::mat4x4 Transformation_Data::get_translation_matrix_inversed_for_ratio(const Transformation_Data &_previous_state, const Transformation_Data &_current_state, float _ratio)
{
    L_ASSERT(_ratio > -0.0001f && _ratio < 1.0001f);

    glm::vec3 curr_pos = _current_state.position();
    glm::vec3 prev_pos = _previous_state.position();
    glm::vec3 diff = curr_pos - prev_pos;
    diff *= _ratio;

    diff = curr_pos - diff;

    glm::mat4x4 result
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        diff.x, diff.y, diff.z, 1.0f
    };

    return result;
}

glm::mat4x4 Transformation_Data::get_rotation_matrix_for_ratio(const Transformation_Data &_previous_state, const Transformation_Data &_current_state, float _ratio)
{
    glm::vec3 diff = get_rotation_for_ratio(_previous_state, _current_state, _ratio);

    glm::mat4x4 result
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    for(unsigned int i=0; i<3; ++i)
    {
        glm::vec3 axis(0.0f, 0.0f, 0.0f);
        axis[i] = 1.0f;

        glm::mat4x4 rotation_around_axis = glm::rotate(diff[i], axis);

        result *= rotation_around_axis;
    }

    return result;
}

glm::mat4x4 Transformation_Data::get_rotation_matrix_inversed_for_ratio(const Transformation_Data &_previous_state, const Transformation_Data &_current_state, float _ratio)
{
    glm::vec3 diff = get_rotation_for_ratio(_previous_state, _current_state, _ratio);

    glm::mat4x4 result
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    for(unsigned int i=0; i<3; ++i)
    {
        glm::vec3 axis(0.0f, 0.0f, 0.0f);
        axis[i] = -1.0f;

        glm::mat4x4 rotation_around_axis = glm::rotate(diff[i], axis);

        result *= rotation_around_axis;
    }

    return result;
}

glm::mat4x4 Transformation_Data::get_scale_matrix_for_ratio(const Transformation_Data &_previous_state, const Transformation_Data &_current_state, float _ratio)
{
    glm::vec3 diff = get_scale_for_ratio(_previous_state, _current_state, _ratio);

    glm::mat4x4 result
    {
        diff.x, 0.0f, 0.0f, 0.0f,
        0.0f, diff.y, 0.0f, 0.0f,
        0.0f, 0.0f, diff.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    return result;
}

glm::mat4x4 Transformation_Data::get_scale_matrix_inversed_for_ratio(const Transformation_Data &_previous_state, const Transformation_Data &_current_state, float _ratio)
{
    glm::vec3 curr_scale = _current_state.scale();
    glm::vec3 prev_scale = _previous_state.scale();
    glm::vec3 diff = curr_scale - prev_scale;
    diff *= _ratio;

    diff = curr_scale - diff;

    glm::mat4x4 result
    {
        diff.x, 0.0f, 0.0f, 0.0f,
        0.0f, diff.y, 0.0f, 0.0f,
        0.0f, 0.0f, diff.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    return result;
}
