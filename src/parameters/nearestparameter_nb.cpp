#include "parameters/nearestparameter_nb.h"

#include "engine/api/nearest_parameters.hpp"
#include "utility/param_utility.h"

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_NearestParameters(nb::module_& m) {
    using osrm::engine::api::BaseParameters;
    using osrm::engine::api::NearestParameters;

    nb::class_<NearestParameters, BaseParameters>(m, "NearestParameters")
        .def("__init__", [](NearestParameters* t,
                std::vector<osrm::util::Coordinate> coordinates,
                std::vector<boost::optional<osrm::engine::Hint>> hints,
                std::vector<boost::optional<double>> radiuses,
                std::vector<boost::optional<osrm::engine::Bearing>> bearings,
                const std::vector<boost::optional<osrm::engine::Approach>>& approaches,
                bool generate_hints,
                std::vector<std::string> exclude,
                const BaseParameters::SnappingType snapping
            ) {
                new (t) NearestParameters();
                
                osrm_nb_util::assign_baseparameters(t,
                                                    coordinates,
                                                    hints,
                                                    radiuses,
                                                    bearings,
                                                    approaches,
                                                    generate_hints,
                                                    exclude,
                                                    snapping);
            },
                "coordinates"_a = std::vector<osrm::util::Coordinate>(),
                "hints"_a = std::vector<boost::optional<osrm::engine::Hint>>(),
                "radiuses"_a = std::vector<boost::optional<double>>(),
                "bearings"_a = std::vector<boost::optional<osrm::engine::Bearing>>(),
                "approaches"_a = std::vector<std::string*>(),
                "generate_hints"_a = true,
                "exclude"_a = std::vector<std::string>(),
                "snapping"_a = std::string()
            )
        .def_rw("number_of_results", &NearestParameters::number_of_results)
        .def("IsValid", &NearestParameters::IsValid);
}