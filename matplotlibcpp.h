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

#include "matplotlibcpp/_python.h"
#include "matplotlibcpp/interpreter.h"
#include "matplotlibcpp/helpers.h"
#include "matplotlibcpp/annotate.h"
#include "matplotlibcpp/_numpy.h"
#include "matplotlibcpp/plot.h"
#include "matplotlibcpp/stem.h"
#include "matplotlibcpp/fill_between.h"
#include "matplotlibcpp/hist.h"
#include "matplotlibcpp/log.h"
#include "matplotlibcpp/errorbar.h"
#include "matplotlibcpp/utilities.h"
#include "matplotlibcpp/imshow.h"
