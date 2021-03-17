#pragma once

#include <cereal/archives/binary.hpp>
#include <cereal/cereal.hpp>
#include <fstream>

using input_archive = cereal::BinaryInputArchive;
using output_archive = cereal::BinaryOutputArchive;
