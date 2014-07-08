#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/python.hpp>
#include <pupiltracker_pythonwrapper/conversion.h>
#include <pupiltracker/PupilTracker.h>
#include <pupiltracker/cvx.h>
#include <vector>

namespace py = boost::python;

py::list findPupil(PyObject *mat, int radius_min = 3, int radius_max = 8, double canny_blur = 1,
		double canny_threshold = 20, double canny_threshold2 = 40, int starburst_points = 0,
		int percentage_inliers = 30, int inlier_iterations = 2, bool image_aware_support = true,
		int early_termination_percentage = 95, bool early_rejection = true, int seed = -1)
{
	//Extract list of doubles in std::vector
	/*std::vector<double> param_vec;
	for (int i = 0; i < py::len(parameters); ++i)
    	{
        	param_vec.push_back(py::extract<double>(parameters[i]));
    	}*/

	//Convert ndarray image into cv::Mat
	NDArrayConverter cvt;
	cv::Mat m = cvt.toMat(mat);

	//Initialize pupiltracker
	pupiltracker::TrackerParams params;
        params.Radius_Min = radius_min; //int(param_vec[0]); //Default = 3
        params.Radius_Max = radius_max; //int(param_vec[1]); //Default = 8

        params.CannyBlur = canny_blur; //param_vec[2]; //Default = 1
        params.CannyThreshold1 = canny_threshold; //param_vec[3]; //Default = 20
        params.CannyThreshold2 = canny_threshold2; //param_vec[4]; //Default = 40
        params.StarburstPoints = starburst_points; //int(param_vec[5]); //Default = 0

        params.PercentageInliers = percentage_inliers; //int(param_vec[6]); //Default = 30
        params.InlierIterations = inlier_iterations; //int(param_vec[7]); //Default = 2
        params.ImageAwareSupport = image_aware_support;
        params.EarlyTerminationPercentage = early_termination_percentage; //int(param_vec[8]); //Default = 95
        params.EarlyRejection = early_rejection;
        params.Seed = seed; //int(param_vec[9]); //Default = -1

        pupiltracker::findPupilEllipse_out out;
        pupiltracker::tracker_log log;
        pupiltracker::findPupilEllipse(params, m, out, log);

	py::list to_ret;
	to_ret.append(out.elPupil.center.x);
	to_ret.append(out.elPupil.center.y);
	to_ret.append(out.elPupil.size.width);
	to_ret.append(out.elPupil.size.height);
	to_ret.append(out.elPupil.angle);	
	
	return to_ret;
}

static void init()
{
	Py_Initialize();
	import_array();
}

BOOST_PYTHON_MODULE(PupilTrackerPythonWrapper)
{
	init();
	py::def("findPupil", findPupil, (
		py::arg("mat"),
		py::arg("radius_min")=3,
		py::arg("radius_max")=8,
		py::arg("canny_blur")=1,
		py::arg("canny_threshold1")=20,
		py::arg("canny_threshold2")=40,
		py::arg("starburst_points")=0,
		py::arg("percentage_inliers")=30,
		py::arg("inlier_iterations")=2,
		py::arg("image_aware_support")=true,
		py::arg("early_termination_percentage")=95,
		py::arg("early_rejection")=true,
		py::arg("seed")=-1),
		"Find the pupil in an image. Returns center xy, width, height, and angle");
}
