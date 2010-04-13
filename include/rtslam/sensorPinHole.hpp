/**
 * \file sensorPinHole.hpp
 *
 * Header file for pin-hole sensor.
 *
 * \date 14/02/2010
 *  \author jsola
 *
 * \ingroup rtslam
 */

#ifndef SENSORPINHOLE_HPP_
#define SENSORPINHOLE_HPP_

//#include "image/Image.hpp"
#include "rtslam/rtSlam.hpp"

#include "rtslam/sensorAbstract.hpp"
#include "rtslam/gaussian.hpp"
#include "iostream"

namespace jafar {
	namespace rtslam {

		class SensorPinHole;

		typedef boost::shared_ptr<SensorPinHole> pinhole_ptr_t;


		/**
		 * Class for pin-hole cameras.
		 * This model accepts radial distortion model
		 * \ingroup rtslam
		 */
		class SensorPinHole: public SensorAbstract {

			public:

				/**
				 * Constructor for selectable LOCAL or REMOTE pose, from robot and selector flag.
				 * \param _rob the robot to install to.
				 * \param inFilter flag indicating in the sensor pose is filtered or not.
				 */
				SensorPinHole(const robot_ptr_t & _robPtr, bool inFilter = false);

				jblas::vec2 imgSize;
				jblas::vec4 intrinsic;
				jblas::vec distortion;
				jblas::vec correction;

				/**
				 * Pin-hole sensor setup.
				 * \param k the vector of intrinsic parameters <c>k = [u_0, v_0, a_u, a_v]</c>.
				 * \param d the radial distortion parameters vector <c>d = [d_2, d_4, ...] </c>.
				 * \param c the radial distortion correction parameters vector <c>c = [c_2, c_4, ...] </c>.
				 * \param hsize the horizontal image size.
				 * \param vsize the vertical image size.
				 */
				void set_parameters(const jblas::vec4 & k, const jblas::vec & d, const jblas::vec & c);

				static size_t size(void) {
					return 7;
				}

				/**
				 * Project a point into a pin-hole camera with radial distortion
				 * \param v the 3D point to project, or the 3D director vector
				 * \return the projected and distorted point
				 */
				vec2 projectPoint(const vec3 & v);

				/**
				 * Project a point into a pin-hole camera with radial distortion
				 * \param v the 3D point to project, or the 3D director vector
				 * \param u the projected and distorted point
				 * \param U_v the Jacobian of \a u wrt \a v
				 */
				void projectPoint(const vec3 & v, vec2 & u, mat23 & U_v);

		};

	}
}

#endif /* SENSORPINHOLE_HPP_ */
