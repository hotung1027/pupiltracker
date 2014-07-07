#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/python.hpp>
#include <pupiltracker-pythonwrapper/conversion.h>
#include <pupiltracker/PupilTracker.h>
#include <pupiltracker/cvx.h>

namespace py = boost::python;

PyObject*
findPupil(PyObject *params, PyObject *mat)
{

	NDArrayConverter cvt;
	cv::Mat m = cvt.toMat(mat);

	pupiltracker::TrackerParams params;
        params.Radius_Min = 3;
        params.Radius_Max = 8;

        params.CannyBlur = 1;
        params.CannyThreshold1 = 20;
        params.CannyThreshold2 = 40;
        params.StarburstPoints = 0;

        params.PercentageInliers = 30;
        params.InlierIterations = 2;
        params.ImageAwareSupport = true;
        params.EarlyTerminationPercentage = 95;
        params.EarlyRejection = true;
        params.Seed = -1;

        pupiltracker::findPupilEllipse_out out;
        pupiltracker::tracker_log log;
        pupiltracker::findPupilEllipse(params, m, out, log);

	PyObject* to_ret = cvt.toNDArray(out);

	return to_ret;
}

static void init()
{
	Py_Initialize();
	import_array();
}
