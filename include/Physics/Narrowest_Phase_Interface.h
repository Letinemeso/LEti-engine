#ifndef __NARROWEST_PHASE_INTERFACE
#define __NARROWEST_PHASE_INTERFACE

#include "../../include/Physics/Physical_Model_2D.h"
#include "../../include/Math_Stuff.h"


namespace LEti {

	class Narrowest_Phase_Interface
	{
	public:
		Narrowest_Phase_Interface();
		virtual ~Narrowest_Phase_Interface();

	public:
		virtual Geometry::Intersection_Data collision__model_vs_point(const Physical_Model_2D& _model, const glm::vec3& _point) const = 0;

		virtual Geometry::Intersection_Data collision__model_vs_model(const Physical_Model_2D& _1, const Physical_Model_2D& _2) const = 0;	//	this might be a poor decision for interface, but it should do for now
		virtual Geometry::Intersection_Data collision__model_vs_model(const Physical_Model_2D::Imprint& _1, const Physical_Model_2D::Imprint& _2) const = 0;
		virtual Geometry::Intersection_Data collision__model_vs_model(const Physical_Model_2D::Imprint& _impr, const Physical_Model_2D& _model) const = 0;
		virtual Geometry::Intersection_Data collision__model_vs_model(const Physical_Model_2D& _model, const Physical_Model_2D::Imprint& _impr) const = 0;

	};

}


#endif // __NARROWEST_PHASE_INTERFACE