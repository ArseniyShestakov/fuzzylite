// #BEGIN_LICENSE
// fuzzylite: a fuzzy logic control library in C++
// Copyright (C) 2014  Juan Rada-Vilela
// 
// This file is part of fuzzylite.
//
// fuzzylite is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// fuzzylite is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with fuzzylite.  If not, see <http://www.gnu.org/licenses/>.
// #END_LICENSE

/*
 * LargestOfMaximum.cpp
 *
 *  Created on: 2/12/2012
 *      Author: jcrada
 */

#include "fl/defuzzifier/LargestOfMaximum.h"

#include "fl/term/Term.h"

#include "fl/Exception.h"




namespace fl {

    LargestOfMaximum::LargestOfMaximum(int resolution)
    : IntegralDefuzzifier(resolution) {
    }

    LargestOfMaximum::~LargestOfMaximum() {
    }

    std::string LargestOfMaximum::className() const {
        return "LargestOfMaximum";
    }

    scalar LargestOfMaximum::defuzzify(const Term* term, scalar minimum, scalar maximum) const {
        if (not fl::Op::isFinite(minimum + maximum)) {
            return fl::nan;
        }
        if (maximum - minimum > _resolution) {
            FL_LOG("[accuracy warning] the resolution <" << _resolution << "> "
                    "is smaller than the range <" << minimum << ", " << maximum << ">. In order to "
                    "improve the accuracy, the resolution should be at least equal to the range.");
        }
        scalar dx = (maximum - minimum) / _resolution;
        scalar x, y;
        scalar ymax = -1.0, xlargest = maximum;
        for (int i = 0; i < _resolution; ++i) {
            x = minimum + (i + 0.5) * dx;
            y = term->membership(x);

            if (Op::isGE(y, ymax)) {
                ymax = y;
                xlargest = x;
            }
        }
        return xlargest;
    }

    LargestOfMaximum* LargestOfMaximum::clone() const {
        return new LargestOfMaximum(*this);
    }

    Defuzzifier* LargestOfMaximum::constructor() {
        return new LargestOfMaximum;
    }

}
