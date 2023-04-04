#ifndef __Dynamic_Physics_Module_2D
#define __Dynamic_Physics_Module_2D

#include "Physics_Module_Base.h"

#include "../../Physics/Physical_Model_2D.h"


namespace LEti
{

    class Dynamic_Physics_Module_2D_Stub : public Physics_Module_Base_Stub
    {
    public:
        DECLARE_VARIABLE;

    public:
        unsigned int coords_count = 0;
        float* coords = nullptr;

        bool* collision_permissions = nullptr;

    protected:
        LV::Variable_Base* M_construct_product() const override;
        void M_init_constructed_product(LV::Variable_Base* /*_product*/) const override;

    public:
        virtual ~Dynamic_Physics_Module_2D_Stub();
    };

    class Dynamic_Physics_Module_2D : public Physics_Module_Base
	{
    public:
        DECLARE_VARIABLE;

    private:
		LEti::Physical_Model_2D* m_physical_model = nullptr;
        LEti::Physical_Model_2D::Imprint* m_physical_model_prev_state = nullptr;
        LEti::Geometry_2D::Rectangular_Border m_rectangular_border;

	public:
        Dynamic_Physics_Module_2D();
        ~Dynamic_Physics_Module_2D();

    public:
        void init_physical_model(const float* _raw_coords, unsigned int _raw_coords_count, const bool* _collision_permissions);

	public:
		void update_previous_state() override;
        void update(const glm::mat4x4 &_translation, const glm::mat4x4 &_rotation, const glm::mat4x4 &_scale) override;

	public:
        inline LEti::Physical_Model_2D* get_physical_model() { return m_physical_model; }
        inline LEti::Physical_Model_2D::Imprint* get_physical_model_prev_state() { return m_physical_model_prev_state; }
        inline const LEti::Physical_Model_2D* get_physical_model() const { return m_physical_model; }
        inline const LEti::Physical_Model_2D::Imprint* get_physical_model_prev_state() const { return m_physical_model_prev_state; }
        inline const LEti::Geometry_2D::Rectangular_Border& rectangular_border() const { return m_rectangular_border; }

	};

}


#endif // __Dynamic_Physics_Module_2D
