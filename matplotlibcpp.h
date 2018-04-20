#pragma once

#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <stdint.h> // <cstdint> requires c++11 support

#if __cplusplus > 199711L || _MSC_VER > 1800
#  include <functional>
#endif

#include "_python.h"
#include "interpreter.h"
#include "helpers.h"
#include "annotate.h"
#include "_numpy.h"
#include "plot.h"
#include "stem.h"
#include "fill_between.h"
#include "hist.h"
#include "log.h"
#include "errorbar.h"
#include "utilities.h"
