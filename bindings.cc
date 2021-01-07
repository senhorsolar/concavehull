#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <vector>

#include "concavehull.hpp"

namespace py = pybind11;

py::array_t<double> pyconcavehull(py::array_t<double> pts, double chi_factor) {
	py::buffer_info buf = pts.request();
	
	if (buf.ndim != 2) {
		throw std::runtime_error("Number of dimensions must be two");
	}
	
	if (buf.shape[1] != 2) {
		throw std::runtime_error("Second dimension's size must be two");
	}

	auto result = py::array_t<double>(buf);

	py::buffer_info bufres = result.request();

	double *ptr = static_cast<double *>(buf.ptr);

	bufres.ptr = concavehull({ptr, ptr+buf.size}, chi_factor).data();

	return result;
}

PYBIND11_MODULE(concavehull, m) {
	m.def("concavehull", &pyconcavehull, "Find concave hull from array of 2D points");
}
